A "simple" .obj loader and renderer.
This project is part of the 42 curriculum, aiming to explore graphics programming using OpenGL.

The main goals of the project are:
- Parsing .obj files (and .mtl as part of my bonus)
- Rendering textures on the triangles

For this project I had to learn how to use OpenGL and thus GLSL shaders.

As part of my bonuses I also added many additional features:
- A whole UI system (Sliders and buttons)
- Proper handling of .mtl files (Though I did not parse the whole material)
- Normal maps
- Light (Basic Phong lighting)
- A camera that can move in the 3d world
- A skybox
- A terminal in the window (Used to change some additional settings that didnt fit in the UI)

Quite a lot of bonuses as the subject said we could add our own :)

To compile and run this project you can just use make to create the binary file used to launch the program, then just pass a .obj model as argument. (and optionally a .bmp file for the texture)

And here are a few screenshots to showcase the project:

![image](https://github.com/user-attachments/assets/f96174f0-0fa1-441d-b7c6-30b4e6402960)

![Screenshot from 2025-05-16 21-17-48](https://github.com/user-attachments/assets/dd9f8e17-a560-407c-8b78-bee19b98a547)
