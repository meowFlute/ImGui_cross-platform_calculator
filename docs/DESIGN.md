# Designing the Simple Calculator

## The end goal

Let's just remind ourselves that the simple goal is something like this

![Simple Calculator](https://play-lh.googleusercontent.com/942KbwPIon7xQet0Qv5F0Orj70Ob3zlGq48NWbWQgx1RkE7MXJ_5Arz5tEclNiRMwYK3)

## Exploring the Dear ImGui feature set

The first step is to explore and note what it is that we can do. Luckily, the test example compiled in the 
[installation step](https://github.com/meowFlute/ImGui_cross-platform_calculator/blob/main/docs/INSTALL.md)
is a great place to do that, even before you start to familiarize yourself with the software. 

![Imgui_Example_Startup](https://user-images.githubusercontent.com/11841186/232145225-c549712d-389f-4d33-b0e1-6f3a28ec1c70.png)

In my case, I am going to be attempting to make a program that pops open a single window that shows something that looks sort of like a calculator.
No sub-windows are required for this, so I'll plan on using a fullscreen window as shown in the `Fullscreen window` example

![Imgui_select_fullsize_window](https://user-images.githubusercontent.com/11841186/232145423-ae2a98af-df82-4080-9b20-c159fd213dcd.png)

Compared to the calculator app included with Ubuntu, this seems like a reasonable place to start 

![Imgui_Compare_to_Calc](https://user-images.githubusercontent.com/11841186/232145163-581ba1a1-f940-44ad-9218-adf4cfb4f56e.png)

At that point, I plan on arranging my window to arrange the various buttons and input fields and such. 
The display seems like it should be able to double as a "Filtered Text Input"

![Imgui_select_filtered_input](https://user-images.githubusercontent.com/11841186/232145349-91dd1a17-0f91-4238-a328-11470acf5991.png)

## Implementation

My first crack at doing what is described here will get the v1.0 tag, at which point I'll attempt to create a release that includes binaries for
Ubuntu, Windows, and Mac.
