# Designing the Simple Calculator

## The end goal

Let's just remind ourselves that the simple goal is something like this

![Simple Calculator](https://play-lh.googleusercontent.com/942KbwPIon7xQet0Qv5F0Orj70Ob3zlGq48NWbWQgx1RkE7MXJ_5Arz5tEclNiRMwYK3)

## Exploring the Dear ImGui feature set

The first step is to explore and note what it is that we can do. Luckily, the test example compiled in the 
[installation step](https://github.com/meowFlute/ImGui_cross-platform_calculator/blob/main/docs/INSTALL.md)
is a great place to do that, even before you start to familiarize yourself with the software. 

***Screenshot of the program goes here***

In my case, I am going to be attempting to make a program that pops open a single window that shows something that looks sort of like a calculator.
No sub-windows are required for this, so I'll plan on using a fullscreen window as shown in the `Fullscreen window` example

***Screenshot of the example being selected goes here***

Compared to the calculator app included with Ubuntu, this seems like a reasonable place to start 

***Screenshot of the side-by-side***

At that point, I plan on arranging my window to arrange the various buttons and input fields and such. 
The display seems like it should be able to double as a "Filtered Text Input"

***Screenshot of the filtered text input***

## Implementation

My first crack at doing what is described here will get the v1.0 tag, at which point I'll attempt to create a release that includes binaries for
Ubuntu, Windows, and Mac.
