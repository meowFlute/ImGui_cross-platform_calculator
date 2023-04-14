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

My setup is:
- Ubuntu 22.04.2 LTS installed on an older (and worn out) Dell G3 3579
- 32GB Ram
- Intel i5-8300H @ 2.3GHz x 8
- NVidia GeForce GTX 1050 Mobile

There isn't a lot of information on how to use ImGui correctly. The way that I am going to after checking around is by using it as a Git submodule.

After initializing my repository I just went into the folder and followed the information found in the *Starting with Submodules* portions of [this Git-SCM documentation page](https://git-scm.com/book/en/v2/Git-Tools-Submodules), which specifically meant adding the submodule by the URL. 

**NOTE:** At this time, the latest release of ImGui is v1.89.4, but I enabled release notifications in github and plan on updating the release version *even if* I don't update them in the readme.

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

## Repository Build Setup
### Building the example in the top-level directory

Having been able to build the example in the ImGui folder, the next step on the path to making my own app is getting the same example to build at the top-level folder (baby steps!). To do so I simply copied the `main.cpp` and `Makefile` files from the project I wanted to emulate. **Note**: I renamed main.cpp, because I want to reserve that name for my actual project and leave this example as something that can easily be compiled for now.

```console
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ cp ./Makefile ~/ImGui_ubuntu_calculator/Makefile
scott@scott-G3:~/ImGui_ubuntu_calculator/imgui/examples/example_sdl2_opengl3$ cp ./main.cpp ~/ImGui_ubuntu_calculator/imgui_example.cpp
```

because of the way these Makefiles are structured, we don't have to change much. The following changes should compile out of the box

```make
IMGUI_DIR = imgui
```

Simple as that! Just change the imgui folder and the rest is already done for you!

### Cleaning up the top-level directory with a "build" folder

I am not a fan of having a bunch of clutter at the top-level directory after a build, so I wanted to send all of the object files to a subfolder. Git doesn't allow you to track empty folders, and this would be a folder just for temporary build files, so we'll create it if it doesn't exist and then make clean will destory it. These were the steps

1. I made a `BUILD_DIR = build` variable up by the `IMGUI_DIR` variable
2. I modified the `OBJS` variable to be `$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))`, which adds the build folder prefix to each object file name definition
3. I changed the object file target definitions to be
    - `$(BUILD_DIR)/%.o:%.cpp`
    - `$(BUILD_DIR)/%.o:$(IMGUI_DIR)/%.cpp`
    - `$(BUILD_DIR)/%.o:$(IMGUI_DIR)/backends/%.cpp`
4. I added a folders resource to `all:`, e.g. `all: folders $(EXE)` and then a folder creation set
```make
folders:
 	@echo Creating folder \"$(BUILD_DIR)\" to keep things tidy
 	@mkdir -p $(BUILD_DIR)
```
5. To the clean lines I added `rmdir $(BUILD_DIR)`
