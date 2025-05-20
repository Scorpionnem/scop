/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/20 14:46:07 by mbatty           ###   ########.fr       */
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

#define RED_BUTTON_PATH "src/assets/textures/red_button.png"
#define GREEN_BUTTON_PATH "src/assets/textures/green_button.png"
#define BLUE_BUTTON_PATH "src/assets/textures/blue_button.png"

#define CAMERA_BUTTON_PATH "src/assets/textures/button_toggle_camera.png"
#define TEXTURE_BUTTON_PATH "src/assets/textures/button_toggle_texture.png"

class	Interface
{
	public:
		Interface(){}
		void	update(GLFWwindow *window, Shader &guiShader)
		{
			double mouseX, mouseY;
			bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
				
			glfwGetCursorPos(window, &mouseX, &mouseY);
				
			guiShader.use();
			glm::mat4 projection = glm::ortho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			guiShader.setMat4("projection", projection);
				
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
		}
		std::vector<Slider>	sliders;
		std::vector<Button>	buttons;
};

int	interface = 0;

void	goto_camera_interface()
{
	interface = 1;
}

void	goto_main_interface()
{
	interface = 0;
}

void	goto_model_interface()
{
	interface = 2;
}

void	goto_light_interface()
{
	interface = 3;
}

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
		Texture		icon_texture(ICON_PATH);
		Texture		button_texture(BUTTON_PATH);
		Texture		button_pressed_texture(BUTTON_PRESSED_PATH);
		Texture		sliderbg_texture(SLIDER_BG_PATH);
		Texture		red_texture(RED_BUTTON_PATH);
		Texture		green_texture(GREEN_BUTTON_PATH);
		Texture		blue_texture(BLUE_BUTTON_PATH);
		Texture		camera_texture(CAMERA_BUTTON_PATH);
		Texture		texture_texture(TEXTURE_BUTTON_PATH);
		Texture		lol("textures/mbatty.png");

		Mesh		mesh(av[1]);
		Light		light;
		
		Interface	mainInterface;
		mainInterface.buttons.push_back(Button(50, 50, glm::vec2(0, 0), goto_main_interface, icon_texture, lol));
		mainInterface.buttons.push_back(Button(75, 50, glm::vec2(50, 0), goto_camera_interface, button_texture, button_pressed_texture));
		mainInterface.buttons.push_back(Button(75, 50, glm::vec2(125, 0), goto_model_interface, button_texture, button_pressed_texture));
		mainInterface.buttons.push_back(Button(75, 50, glm::vec2(200, 0), goto_light_interface, button_texture, button_pressed_texture));

		Interface	cameraInterface;
		cameraInterface.buttons.push_back(Button(50, 50, glm::vec2(0, 0), goto_main_interface, icon_texture, lol));
		cameraInterface.buttons.push_back(Button(100, 50, glm::vec2(50, 0), toggle_camera, camera_texture, button_pressed_texture));
		cameraInterface.sliders.push_back(Slider(150, 50, glm::vec2(150, 0), button_texture, button_pressed_texture, sliderbg_texture));

		Interface	modelInterface;
		modelInterface.buttons.push_back(Button(50, 50, glm::vec2(0, 0), goto_main_interface, icon_texture, lol));
		modelInterface.buttons.push_back(Button(100, 50, glm::vec2(50, 0), toggle_texture, texture_texture, button_pressed_texture));
		modelInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(150, 0), button_texture, button_pressed_texture, sliderbg_texture));
		modelInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(150, 16.6), button_texture, button_pressed_texture, sliderbg_texture));
		modelInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(150, 33.3), button_texture, button_pressed_texture, sliderbg_texture));

		Interface	lightInterface;
		lightInterface.buttons.push_back(Button(50, 50, glm::vec2(0, 0), goto_main_interface, icon_texture, lol));
		lightInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(50, 0), red_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(50, 16.6), green_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders.push_back(Slider(150, 16.6, glm::vec2(50, 33.3), blue_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders[0].setSlider(1.0f);
		lightInterface.sliders[1].setSlider(1.0f);
		lightInterface.sliders[2].setSlider(1.0f);

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

			texture.use();
			mesh.pos = mesh_pos;
			mesh.draw(shader);
			light.draw(fb_shader, camera);

			if (interface == 0)
				mainInterface.update(window.getWindowData(), guiShader);
			if (interface == 1)
				cameraInterface.update(window.getWindowData(), guiShader);
			if (interface == 2)
				modelInterface.update(window.getWindowData(), guiShader);
			if (interface == 3)
				lightInterface.update(window.getWindowData(), guiShader);

			light.color.x = lightInterface.sliders[0].value;
			light.color.y = lightInterface.sliders[1].value;
			light.color.z = lightInterface.sliders[2].value;
			mesh.rotateX = 360 * modelInterface.sliders[0].value;
			mesh.rotateY = 360 * modelInterface.sliders[1].value;
			mesh.rotateZ = 360 * modelInterface.sliders[2].value;
			FOV = 100 * cameraInterface.sliders[0].value;
			if (FOV <= 0)
				cameraInterface.sliders[0].setSlider(0.01f);

			frame_key_hook(window);
			window.loopEnd();
		}
	} catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return (1);
	}
}
