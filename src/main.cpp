/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/06/01 17:39:11 by mbatty           ###   ########.fr       */
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
#include "Window.hpp"
#include "Interface.hpp"
#include "Skybox.hpp"
#include "InterfaceFunctions.hpp"

float	FOV = 70;
#define MAX_FOV 100
float	SCREEN_WIDTH = 800;
float	SCREEN_HEIGHT = 800;
float	RENDER_DISTANCE = 1000;

vec3	backgroundColor(0.05, 0.05, 0.05);

vec3	mesh_pos;
float	mesh_roll;

int		interpolate = 0;
int		skybox_interpolate = 0;
float	ambientStrength = 0.2;

bool	F1 = false;
bool	F3 = false;
bool	lock_fps = true;
bool	rainbow = false;
bool	camera_toggle = false;
bool	light_move = true;
bool	apply_normal = false;
bool	mesh_spin = true;

unsigned int	TOTAL_VERTICES = 0;
unsigned int	TOTAL_TRIANGLES = 0;

bool	paused = false;
double	pause_time = 0;

int	shaderEffect = 0;
int	interface = 0;

void	interpolateTo(float &float1, float &float2, float deltaTime)
{
	float1 += (1.0f - float1) * 2.0f * deltaTime;
	if (float1 > 0.99f)
		float1 = 1.0f;

	float2 = 1.0f - float1;
}

std::string	toString(int nbr)
{
	std::stringstream	strs;
	strs << nbr;
	return (strs.str());
}

void	frame_key_hook(Window &window)
{
	if (isTerminalOn)
		return ;
	
	if (glfwGetKey(window.getWindowData(), GLFW_KEY_C) == GLFW_PRESS)
		window.center();

	float cameraSpeed = 15.0f * window.getDeltaTime();
	float	speedBoost = 1.0f;

	if (paused)
		return ;

	if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		speedBoost = 20.0f;
	
	if (camera_toggle)
	{
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
			pos = pos + front * (cameraSpeed * speedBoost);
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
			pos = pos - front * (cameraSpeed * speedBoost);
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
			pos = pos + up * (cameraSpeed * speedBoost);
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			pos = pos - up * (cameraSpeed * speedBoost);
			
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_A) == GLFW_PRESS)
			pos = pos -  front.cross(up).normalize() * (cameraSpeed * speedBoost);
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
			pos = pos + front.cross(up).normalize() * (cameraSpeed * speedBoost);
			
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
			mesh_pos.x -= (cameraSpeed * speedBoost) * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_D) == GLFW_PRESS)
			mesh_pos.x += (cameraSpeed * speedBoost) * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_SPACE) == GLFW_PRESS)
			mesh_pos.y += (cameraSpeed * speedBoost) * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			mesh_pos.y -= (cameraSpeed * speedBoost) * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_W) == GLFW_PRESS)
			mesh_pos.z -= (cameraSpeed * speedBoost) * 1;
		if (glfwGetKey(window.getWindowData(), GLFW_KEY_S) == GLFW_PRESS)
			mesh_pos.z += (cameraSpeed * speedBoost) * 1;
	}

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void	pause_render()
{
	if (!paused)
	{
		F1 = false;
		pause_time = glfwGetTime();
		paused = true;
		goto_pause_interface();
	}
	else
	{
		paused = false;
		goto_main_interface();
	}
}

void	key_hook(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		pause_render();
	}
	if (paused)
		return ;
		
	terminal_special_keys(window, key, scancode, action, mods);
	if (isTerminalOn)
		return ;
	
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		F1 = !F1;
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
		F3 = !F3;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		toggle_texture();
}

void	displayDebug(Font &font, Shader &textShader)
{
	std::string	tmp;

	tmp = "cam " + toString(pos.x) + " " + toString(pos.y) + " " + toString(pos.z);
	font.putString(tmp, textShader, vec2(SCREEN_WIDTH - tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE * 1), vec2(tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
	
	tmp = "model " + toString(mesh_pos.x) + " " + toString(mesh_pos.y) + " " + toString(mesh_pos.z);
	font.putString(tmp, textShader, vec2(SCREEN_WIDTH - tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE * 2), vec2(tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
	
	tmp = "loaded vertices " + toString(TOTAL_VERTICES);
	font.putString(tmp, textShader, vec2(SCREEN_WIDTH - tmp.length() * TERMINAL_CHAR_SIZE, SCREEN_HEIGHT - TERMINAL_CHAR_SIZE * 1), vec2(tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
	
	tmp = "loaded triangles " + toString(TOTAL_TRIANGLES);
	font.putString(tmp, textShader, vec2(SCREEN_WIDTH - tmp.length() * TERMINAL_CHAR_SIZE, SCREEN_HEIGHT - TERMINAL_CHAR_SIZE * 2), vec2(tmp.length() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));

}

void	MyDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	(void)userParam;
	
	if (!DEBUG)
		return ;
	if (type == GL_DEBUG_TYPE_PERFORMANCE || severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		std::cout << "---WARNING---" << std::endl;
	else
		std::cout << "---ERROR---" << std::endl;
	std::cout << "source: " << source << std::endl;
	std::cout << "type: " << type << std::endl;
	std::cout << "id: " << id << std::endl;
	std::cout << "severity: " << severity << std::endl;
	std::cout << "length: " << length << std::endl;
	std::cout << "message: " << message << std::endl;
	std::cout << "-----------" << std::endl;
}

Window	*g_window;

void	close_window()
{
	glfwSetWindowShouldClose(g_window->getWindowData(), true);
}

void	resume_render()
{
	paused = false;
	interface = 0;
	glfwSetTime(pause_time);
}

void	do_nothing()
{
}

int	main(int ac, char **av)
{
	if (ac != 3 && ac != 2)
	{
		std::cerr << ERROR_WRONG_AC << std::endl;
		return (1);
	}
	try {
		Window		window;
		g_window = &window;
		
		Camera		camera;
		
		Shader		shader(MESH_VERT_SHADER, MESH_FRAG_SHADER);
		Shader		fb_shader(MESH_VERT_SHADER, MESH_FULLBRIGHT_SHADER);
		Shader		guiShader(GUI_VERT_SHADER, GUI_FRAG_SHADER);
		Shader		text_shader(TEXT_VERT_SHADER, TEXT_FRAG_SHADER);
		Shader		skybox_shader(SKYBOX_VERT_SHADER, SKYBOX_FRAG_SHADER);

		Texture		icon_texture(ICON_PATH);
		Texture		button_texture(BUTTON_PATH);
		Texture		button_pressed_texture(BUTTON_PRESSED_PATH);
		Texture		sliderbg_texture(SLIDER_BG_PATH);
		Texture		red_texture(RED_BUTTON_PATH);
		Texture		green_texture(GREEN_BUTTON_PATH);
		Texture		blue_texture(BLUE_BUTTON_PATH);
		Texture		mbatty_texture(MBATTY_TX_PATH);
		Texture		normal_test(NORMAL_TX_PATH);

		Mesh	mesh;
		if (ac == 3)
			mesh.loadOBJ(av[1], av[2]);
		else
			mesh.loadOBJ(av[1], MISSING_TEXTURE);
		Light		light;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MyDebugCallback, NULL);

		Font	font;

		Interface	mainInterface;
		mainInterface.buttons.push_back(Button("", 50, 50, vec2(0, 0), toggle_fpscap, icon_texture, mbatty_texture));
		mainInterface.buttons.push_back(Button("camera", 100, 50, vec2(50, 0), goto_camera_interface, button_texture, button_pressed_texture));
		mainInterface.buttons.push_back(Button("model", 100, 50, vec2(150, 0), goto_model_interface, button_texture, button_pressed_texture));
		mainInterface.buttons.push_back(Button("light", 100, 50, vec2(250, 0), goto_light_interface, button_texture, button_pressed_texture));
		mainInterface.buttons.push_back(Button("skybox", 100, 50, vec2(350, 0), toggle_skybox, button_texture, button_pressed_texture));

		Interface	cameraInterface;
		cameraInterface.buttons.push_back(Button("", 50, 50, vec2(0, 0), goto_main_interface, icon_texture, button_pressed_texture));
		cameraInterface.buttons.push_back(Button("movement", 75, 50, vec2(50, 0), toggle_camera, button_texture, button_pressed_texture));
		cameraInterface.sliders.push_back(Slider("fov", 150, 50, vec2(125, 0), button_texture, button_pressed_texture, sliderbg_texture));

		Interface	modelInterface;
		modelInterface.buttons.push_back(Button("", 50, 50, vec2(0, 0), goto_main_interface, icon_texture, button_pressed_texture));
		modelInterface.buttons.push_back(Button("texture", 75, 50, vec2(50, 0), toggle_texture, button_texture, button_pressed_texture));
		modelInterface.sliders.push_back(Slider("rotation", 150, 16.6, vec2(125, 0), button_texture, button_pressed_texture, sliderbg_texture));
		modelInterface.sliders.push_back(Slider("rotation", 150, 16.6, vec2(125, 16.6), button_texture, button_pressed_texture, sliderbg_texture));
		modelInterface.sliders.push_back(Slider("rotation", 150, 16.6, vec2(125, 33.3), button_texture, button_pressed_texture, sliderbg_texture));
		modelInterface.buttons.push_back(Button("shader", 50, 50, vec2(275, 0), change_shader, button_texture, button_pressed_texture));
		modelInterface.buttons.push_back(Button("spin", 50, 50, vec2(325, 0), toggle_mesh_spin, button_texture, button_pressed_texture));
		modelInterface.buttons.push_back(Button("normal", 75, 50, vec2(375, 0), toggle_apply_normal, button_texture, button_pressed_texture));

		Interface	lightInterface;
		lightInterface.buttons.push_back(Button("", 50, 50, vec2(0, 0), goto_main_interface, icon_texture, button_pressed_texture));
		lightInterface.sliders.push_back(Slider("red", 150, 16.6, vec2(50, 0), red_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders.push_back(Slider("green", 150, 16.6, vec2(50, 16.6), green_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders.push_back(Slider("blue", 150, 16.6, vec2(50, 33.3), blue_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.sliders.push_back(Slider("ambient", 150, 50, vec2(200, 0), button_texture, button_pressed_texture, sliderbg_texture));
		lightInterface.buttons.push_back(Button("move", 50, 50, vec2(350, 0), toggle_light_move, button_texture, button_pressed_texture));
		lightInterface.sliders[0].setSlider(1.0f);
		lightInterface.sliders[1].setSlider(1.0f);
		lightInterface.sliders[2].setSlider(1.0f);
		lightInterface.sliders[3].setSlider(0.2f);

		Interface	pauseInterface;
		pauseInterface.buttons.push_back(Button("", 200, 200, vec2((SCREEN_WIDTH / 2) - 100, 50), do_nothing, icon_texture, icon_texture));
		pauseInterface.buttons.push_back(Button("resume", 250, 75, vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 80), resume_render, button_texture, button_pressed_texture));
		pauseInterface.buttons.push_back(Button("settings", 250, 75, vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2)), goto_settings_interface, button_texture, button_pressed_texture));
		pauseInterface.buttons.push_back(Button("quit", 250, 75, vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) + 80), close_window, button_texture, button_pressed_texture));

		Interface	settingsInterface;
		settingsInterface.buttons.push_back(Button("", 200, 200, vec2((SCREEN_WIDTH / 2) - 100, 50), do_nothing, icon_texture, icon_texture));
		settingsInterface.sliders.push_back(Slider("render distance", 250, 75, vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 80), button_texture, button_pressed_texture, sliderbg_texture));
		settingsInterface.buttons.push_back(Button("done", 250, 75, vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2)), goto_pause_interface, button_texture, button_pressed_texture));
		settingsInterface.sliders[0].setSlider(0.5f);

		pos = vec3(mesh.center.x, mesh.center.y, mesh.center.z + 5.0f);

		Skybox	skybox({
    	    "textures/skybox/right.bmp",
    	    "textures/skybox/left.bmp",
    	    "textures/skybox/top.bmp",
    	    "textures/skybox/bottom.bmp",
    	    "textures/skybox/front.bmp",
    	    "textures/skybox/back.bmp"
    	});
		skybox_shader.use();
		skybox_shader.setInt("skybox", 0);

		shader.use();
		shader.setInt("tex0", 0);
		shader.setInt("tex1", 1);
		guiShader.use();
		guiShader.setInt("tex0", 0);
		text_shader.use();
		text_shader.setInt("tex0", 0);

		float	texIntensity = 0.0;
		float	colorIntensity = 1.0;

		float	skyboxIntensity = 0.0;
		float	backgroundIntensity = 1.0;

		while (window.up())
		{
			window.loopStart();
	
			if (paused)
				glfwSetTime(pause_time);

			camera.update();
			camera.setViewMatrix(shader);
			light.update(shader);

			if (interpolate)
				interpolateTo(texIntensity, colorIntensity, window.getDeltaTime());	
			else
				interpolateTo(colorIntensity, texIntensity, window.getDeltaTime());	

			if (skybox_interpolate)
				interpolateTo(skyboxIntensity, backgroundIntensity, window.getDeltaTime());	
			else
				interpolateTo(backgroundIntensity, skyboxIntensity, window.getDeltaTime());	

			skybox_shader.use();
			skybox_shader.setFloat("skyboxIntensity", skyboxIntensity);
			skybox_shader.setFloat("backgroundIntensity", backgroundIntensity);
			skybox_shader.setVec3("background", backgroundColor);
			text_shader.use();
			text_shader.setFloat("time", glfwGetTime());
			text_shader.setFloat("SCREEN_WIDTH", SCREEN_WIDTH);
			text_shader.setFloat("SCREEN_HEIGHT", SCREEN_HEIGHT);
			text_shader.setBool("rainbow", rainbow);
			text_shader.setBool("turbo", !lock_fps);
			text_shader.setVec3("color", vec3(1.0, 1.0, 1.0));
			shader.use();
			shader.setFloat("texIntensity", texIntensity);
			shader.setFloat("colorIntensity", colorIntensity);
			shader.setFloat("ambientStrength", ambientStrength);
			shader.setVec3("viewPos", pos);
			shader.setFloat("time", glfwGetTime());
			shader.setInt("shaderEffect", shaderEffect);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, normal_test.ID);

			skybox.draw(camera, skybox_shader);

			mesh.pos = mesh_pos;
			mesh.draw(shader);
			light.draw(fb_shader, camera);

			if (!F1)
			{
				//Positive interfaces are in render interfaces and negative ones are in the pause menu
				if (interface == 0)
					mainInterface.update(window.getWindowData(), guiShader, font, text_shader);
				if (interface == 1)
					cameraInterface.update(window.getWindowData(), guiShader, font, text_shader);
				if (interface == 2)
					modelInterface.update(window.getWindowData(), guiShader, font, text_shader);
				if (interface == 3)
					lightInterface.update(window.getWindowData(), guiShader, font, text_shader);
				
				if (interface == -1)
					pauseInterface.update(window.getWindowData(), guiShader, font, text_shader);
				if (interface == -2)
					settingsInterface.update(window.getWindowData(), guiShader, font, text_shader);
			}

			//center settings and pause menu (im too lazy to make it automatic)
			if (paused)
			{
				pauseInterface.buttons[0].pos = vec2((SCREEN_WIDTH / 2) - 100, 50);
				pauseInterface.buttons[1].pos = vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 80);
				pauseInterface.buttons[2].pos = vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2));
				pauseInterface.buttons[3].pos = vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) + 80);
				settingsInterface.buttons[0].pos = vec2((SCREEN_WIDTH / 2) - 100, 50);
				settingsInterface.buttons[1].pos = vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2));
				settingsInterface.sliders[0].pos = vec2((SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 80);
			}

			light.color.x = lightInterface.sliders[0].value;
			light.color.y = lightInterface.sliders[1].value;
			light.color.z = lightInterface.sliders[2].value;
			ambientStrength = lightInterface.sliders[3].value;
			mesh.rotateX = 360 * modelInterface.sliders[0].value;
			mesh.rotateY = 360 * modelInterface.sliders[1].value;
			mesh.rotateZ = 360 * modelInterface.sliders[2].value;
			RENDER_DISTANCE = (2000 * settingsInterface.sliders[0].value) + 10;
			FOV = (MAX_FOV * cameraInterface.sliders[0].value) + 1;
			
			light.move = light_move;
			shader.use();
			shader.setBool("applyNormal", apply_normal);
			if (!F1)
			{
				if (isTerminalOn)
				{
					std::string	tmp = terminalInput;
					tmp.insert(terminalCursor - terminalInput.begin(), 1, '_');
					font.putString(tmp, text_shader, vec2(5, SCREEN_HEIGHT - (TERMINAL_CHAR_SIZE + 5)), vec2(tmp.size() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
				}
				else if (glfwGetTime() - terminalReturnTime < 1.5)
					font.putString(terminalReturn, text_shader, vec2(5, SCREEN_HEIGHT - (TERMINAL_CHAR_SIZE + 5)), vec2(terminalReturn.size() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
				else
					font.putString(std::string(TERMINAL_POPUP), text_shader, vec2(5, SCREEN_HEIGHT - (TERMINAL_CHAR_SIZE + 5)), vec2(std::string(TERMINAL_POPUP).size() * TERMINAL_CHAR_SIZE, TERMINAL_CHAR_SIZE));
				
				if (F3)
					displayDebug(font, text_shader);	
			}

			frame_key_hook(window);
			window.loopEnd(font, text_shader);
		}
	} catch (const std::exception &e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return (1);
	}
}
