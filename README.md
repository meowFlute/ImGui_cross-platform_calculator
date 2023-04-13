# ImGui_ubuntu_calculator

## Background 
For a few years I have been developing in C and obtaining a fair amount of engineering and business domain expertise. I'd really like to find a way to make something a bit more user friendly than the CLI tools I've been developing for years.

In order to get my feet wet with a C/C++ friendly, cross-platform, and "simple" GUI I did some research and settled on trying ImGui first.

## Repository Goals
The goals of this repo need to stay simple or I'll never get the projec to where I want it to be. I want to make a simple calculator with a minimal set of buttons. Something like this.

![Simple Calculator](https://play-lh.googleusercontent.com/942KbwPIon7xQet0Qv5F0Orj70Ob3zlGq48NWbWQgx1RkE7MXJ_5Arz5tEclNiRMwYK3)

## ImGui Installation Method
### Getting ImGui
One reason I'm doing this in the first place is to just get my hands on ImGui for the first time.

There isn't a lot of information on how to use ImGui correctly. The way that I am going to after checking around is by using it as a Git submodule.

After initializing my repository I just went into the folder and followed the information found in the *Starting with Submodules* portions of [this Git-SCM documentation page](https://git-scm.com/book/en/v2/Git-Tools-Submodules), which specifically meant adding the submodule by the URL 

```console
scott@scott-G3:~/ImGui_ubuntu_calculator$ git submodule add https://github.com/ocornut/imgui
scott@scott-G3:~/ImGui_ubuntu_calculator$ cd imgui/
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui$ git checkout v1.89.4
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui$ cd ..
scott@scott-G3:~/ImGui_ubuntu_calculator$ git add -A
scott@scott-G3:~/ImGui_ubuntu_calculator$ git commit -m "moved to version 1.89.4 tag for ImGui"
scott@scott-G3:~/ImGui_ubuntu_calculator$ git push
```

### Building an Example
At this point I needed to decide which backend platform and renderer to use. After [some background reading](https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md) and considering my future goals, I decided that SDL2 with an OpenGL backend was a great place to start. My machine has a discrete graphics card and I'd like to make engineering tools primarily in the future for similar machines, but the ability to cross between Mac, Windows, and Linux will hopefully prove to be very helpful. The documentation page makes those seem like very well supported options.

I installed both SDL2 and OpenGL dev kits with the folloiwng commands in Ubuntu

```console
scott@scott-G3:~$ sudo apt install libsdl2-dev
scott@scott-G3:~$ sudo apt install mesa-utils
scott@scott-G3:~$ glxinfo | grep "OpenGL version"
OpenGL version string: 4.6 (Compatibility Profile) Mesa 22.2.5
```
knowing now that I have the right tools build, I took a look at the example list to choose one

```console
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples$ ls
example_allegro5         example_glfw_opengl3    example_sdl2_opengl3      example_win32_directx9
example_android_opengl3  example_glfw_vulkan     example_sdl2_sdlrenderer  imgui_examples.sln
example_apple_metal      example_glut_opengl2    example_sdl2_vulkan       libs
example_apple_opengl2    example_null            example_sdl3_opengl3      README.txt
example_emscripten_wgpu  example_sdl2_directx11  example_win32_directx10
example_glfw_metal       example_sdl2_metal      example_win32_directx11
example_glfw_opengl2     example_sdl2_opengl2    example_win32_directx12
```

and seeing I have OpenGL version 4.6, I went with the `example_sdl2_opengl3` example

```console
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples$ cd example_sdl2_opengl3
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ ls
build_win32.bat               example_sdl2_opengl3.vcxproj.filters  Makefile             README.md
example_sdl2_opengl3.vcxproj  main.cpp                              Makefile.emscripten
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ make
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o main.o main.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui.o ../../imgui.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_demo.o ../../imgui_demo.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_draw.o ../../imgui_draw.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_tables.o ../../imgui_tables.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_widgets.o ../../imgui_widgets.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_impl_sdl2.o ../../backends/imgui_impl_sdl2.cpp
g++ -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -c -o imgui_impl_opengl3.o ../../backends/imgui_impl_opengl3.cpp
g++ -o example_sdl2_opengl3 main.o imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_sdl2.o imgui_impl_opengl3.o -std=c++11 -I../.. -I../../backends -g -Wall -Wformat `sdl2-config --cflags` -lGL -ldl `sdl2-config --libs`
Build complete for Linux
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ ls
build_win32.bat                       imgui_demo.o          imgui.o          main.o
example_sdl2_opengl3                  imgui_draw.o          imgui_tables.o   Makefile
example_sdl2_opengl3.vcxproj          imgui_impl_opengl3.o  imgui_widgets.o  Makefile.emscripten
example_sdl2_opengl3.vcxproj.filters  imgui_impl_sdl2.o     main.cpp         README.md
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ ./example_sdl2_opengl3 &
```
