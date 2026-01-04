/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 14:09:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <atomic>
#include <deque>
#include <functional>
#include <condition_variable>

#include "Chunk.hpp"

class	ChunkGenerator
{
	public:
		ChunkGenerator(uint32_t workers, MeshCache &cache) : _cache(cache)
		{
			for (uint32_t i = 0; i < workers; ++i)
				_workers.emplace_back(std::bind(&ChunkGenerator::_generatorWorker, this));
		}
		~ChunkGenerator()
		{
			std::unique_lock<std::mutex> latch(_queue_mutex);
			_stop = true;
			_cv_task.notify_all();
			latch.unlock();

			for (auto& thread : _workers)
				thread.join();
		}

		void	gen(std::shared_ptr<Chunk> chunk)
		{
			std::unique_lock<std::mutex> lock(_queue_mutex);
			_tasks.emplace_back(chunk);
			_cv_task.notify_one();
		}
	private:
		void	_generatorWorker()
		{
			while (true)
			{
				std::unique_lock<std::mutex> latch(_queue_mutex);
				_cv_task.wait(latch, [this](){ return _stop || !_tasks.empty(); });
				if (!_tasks.empty())
				{
					std::shared_ptr<Chunk>	chunk = _tasks.front();
					_tasks.pop_front();

					latch.unlock();

					chunk->generate();
					chunk->genMesh(_cache);

					latch.lock();
				}
				else if (_stop)
				{
					break ;
				}
			}
		}

		std::vector<std::thread>			_workers;
		std::deque<std::shared_ptr<Chunk>>	_tasks;
		std::mutex							_queue_mutex;
		std::condition_variable 			_cv_task;
		bool								_stop = false;
		MeshCache 							&_cache;
};
