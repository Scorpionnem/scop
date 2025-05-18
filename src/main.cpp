/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/18 15:35:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

#include "Camera.hpp"
#include "Shader.hpp"

#include "Mesh.hpp"
#include "Light.hpp"
#include "Terminal.hpp"
#include "Button.hpp"
#include "Slider.hpp"

float	SCREEN_WIDTH = 800;
float	SCREEN_HEIGHT = 800;
float	FOV = 70;
float	RENDER_DISTANCE = 360;

int	interpolate = 0;

bool	lock_fps = true;

bool	camera_toggle = false;
glm::vec3	mesh_pos;
float	mesh_roll;

void	interpolateTo(float &float1, float &float2, float deltaTime)
{
	float1 += (1.0f - float1) * 2.0f * deltaTime;
	if (float1 > 0.99f)
		float1 = 1.0f;

	float2 = 1.0f - float1;
}

void	frame_key_hook(Window &window)
{
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window.getWindowData(), true);
	
	if (isTerminalOn)
		return ;
	
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_C) == GLFW_PRESS)
		window.center();

	float cameraSpeed = 15.0f * window.getDeltaTime();

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraSpeed *= 20;
	
	if (camera_toggle)
	{
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
			pos += cameraSpeed * front;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
			pos -= cameraSpeed * front;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
			pos += cameraSpeed * up;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			pos -= cameraSpeed * up;
			
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_A) == GLFW_PRESS)
			pos -=  glm::normalize(glm::cross(front, up)) * cameraSpeed;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
			pos +=  glm::normalize(glm::cross(front, up)) * cameraSpeed;
			
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT) == GLFW_PRESS)
			yaw -= (10.0f * cameraSpeed) * 1.f;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_RIGHT) == GLFW_PRESS)
			yaw += (10.0f * cameraSpeed) * 1.f;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_UP) == GLFW_PRESS)
			pitch += (10.0f * cameraSpeed) * 1.f;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_DOWN) == GLFW_PRESS)
			pitch -= (10.0f * cameraSpeed) * 1.f;
	}
	else
	{
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_A) == GLFW_PRESS)
			mesh_pos.x -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
			mesh_pos.x += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
			mesh_pos.y += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			mesh_pos.y -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
			mesh_pos.z -= cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
			mesh_pos.z += cameraSpeed * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_UP) == GLFW_PRESS)
			mesh_roll -= cameraSpeed * 4;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_DOWN) == GLFW_PRESS)
			mesh_roll += cameraSpeed * 4;
	}

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

void	key_hook(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;

	terminal_special_keys(window, key, scancode, action, mods);
	if (isTerminalOn)
		return ;
}

void	handleButtons(GLFWwindow *window, std::vector<Button> &buttons, Shader &guiShader, std::vector<Slider> &sliders)
{
	glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	guiShader.use();
	guiShader.setMat4("projection", projection);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	
	bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    glDisable(GL_DEPTH_TEST);
	for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); it++)
	{
		it->texture.use();
		it->checkClick(glm::vec2(mouseX, mouseY), mousePressed);
		it->draw(guiShader);
	}
	for (std::vector<Slider>::iterator it = sliders.begin(); it != sliders.end(); it++)
	{
		it->checkClick(glm::vec2(mouseX, mouseY), mousePressed);
		it->drawBackground(guiShader);
		it->drawSlider(guiShader);
	}
	glEnable(GL_DEPTH_TEST);

	FOV = 80 * sliders[0].value;
}

void	toggle_camera()
{
	camera_toggle = !camera_toggle;
}

void	toggle_texture()
{
	interpolate = !interpolate;
}

void	toggle_fpscap()
{
	lock_fps = !lock_fps;
	if (lock_fps)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

#define ICON_PATH "src/assets/textures/icon.png"

#define BUTTON_PATH "src/assets/textures/button.png"
#define BUTTON_PRESSED_PATH "src/assets/textures/button_pressed.png"

#define SLIDER_BG_PATH "src/assets/textures/slider_background.png"

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Wrong argument count." << std::endl;
		return (1);
	}
	try {
		Window		window;
		Camera		camera;
		Shader		shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs");
		Shader		fb_shader("shaders/vertex_shader.vs", "shaders/full_bright.fs");
		Shader		guiShader("shaders/gui_shader.vs", "shaders/gui_shader.fs");
		Texture		texture(av[2]);

		Mesh		mesh(av[1]);
		Light		light;
		
		std::vector<Button>	buttons;
		std::vector<Slider>	sliders;

		Texture		icon_texture(ICON_PATH);
		Texture		button_texture(BUTTON_PATH);
		Texture		button_pressed_texture(BUTTON_PRESSED_PATH);
		Texture		sliderbg_texture(SLIDER_BG_PATH);
		buttons.push_back(Button(50, 50, glm::vec2(0, 0), toggle_fpscap, icon_texture, button_pressed_texture));
		buttons.push_back(Button(100, 50, glm::vec2(50, 0), toggle_camera, button_texture, button_pressed_texture));
		buttons.push_back(Button(100, 50, glm::vec2(150, 0), toggle_texture, button_texture, button_pressed_texture));

		sliders.push_back(Slider(150, 50, glm::vec2(250, 0), button_texture, button_pressed_texture, sliderbg_texture));
		sliders.back().setSlider(0.875);
		sliders.push_back(Slider(150, 16.6, glm::vec2(400, 0), button_texture, button_pressed_texture, sliderbg_texture));
		sliders.push_back(Slider(150, 16.6, glm::vec2(400, 33.3), button_texture, button_pressed_texture, sliderbg_texture));
		sliders.push_back(Slider(150, 16.6, glm::vec2(400, 16.6), button_texture, button_pressed_texture, sliderbg_texture));

		pos = glm::vec3(mesh.center.x, mesh.center.y, mesh.center.z + 5.0f);

		shader.setInt("tex0", 0);
		guiShader.setInt("tex0", 0);

		float	texIntensity = 0.0;
		float	colorIntensity = 1.0;

		while (window.up())
		{
			window.loopStart();
	
			camera.update();
			camera.setViewMatrix(shader);
			light.update(shader);
	
			if (interpolate)
				interpolateTo(texIntensity, colorIntensity, window.getDeltaTime());	
			else
				interpolateTo(colorIntensity, texIntensity, window.getDeltaTime());	
			
			shader.use();
			shader.setFloat("texIntensity", texIntensity);
			shader.setFloat("colorIntensity", colorIntensity);
			
			light.color.x = sliders[1].value - 0.25;
			light.color.y = sliders[2].value - 0.25;
			light.color.z = sliders[3].value - 0.25;

			texture.use();
			mesh.pos = mesh_pos;
			mesh.roll = mesh_roll;
			mesh.draw(shader);
			light.draw(fb_shader, camera);

			handleButtons(window.getWindowData(), buttons, guiShader, sliders);

			frame_key_hook(window);
			window.loopEnd();
		}
	} catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return (1);
	}
}
