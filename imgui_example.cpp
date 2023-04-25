// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

#define CALC_BUFFER_SIZE 128

//-----------------------------------------------------------------------------
// [SECTION] Helpers
//-----------------------------------------------------------------------------

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

// Those light colors are better suited with a thicker font than the default one + FrameBorder
static void StyleColorsCalculator()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
	colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
	colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab]                    = ImVec4(0.76f, 0.80f, 0.84f, 0.93f);
	colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive]              = ImVec4(0.60f, 0.73f, 0.88f, 1.00f);
	colors[ImGuiCol_TabUnfocused]           = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
	colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
	colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
	colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
	colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

static void StyleRoundingCalculator()
{
	ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 12.0f;
    style.TabRounding = 12.0f;
    style.FrameRounding = 12.0f;
    style.PopupRounding = 12.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 12.0f;
    style.TabRounding = 12.0f;
    style.WindowRounding = 12.0f;
}

static void  TrimTrailingWhitespace(char* s)
{
	char* str_end = s + strlen(s); 
	while (str_end > s && str_end[-1] == ' ') 
		str_end--; 
	*str_end = 0; 
}

static int CalculatorOutputCallback(ImGuiInputTextCallbackData* data)
{
	int return_value = 0;
	
	switch (data->EventFlag)
	{
		case ImGuiInputTextFlags_CallbackCharFilter:
		{
			if (data->EventChar < 256 && strchr("0123456789.+-*/^() ", (char)data->EventChar))
			{
				return_value = 0;
				break;
			}
			return_value = 1;
			break;
		}
		// could later do other tyoes of inputs here
	}
	
	return return_value;
}

static int append_char(char * buf, char c)
{
	int len = strlen(buf);
	//don't forget you need a null pointer and space for the new character
	if((len + 2) < CALC_BUFFER_SIZE)
	{
		buf[len] = c; //this should be the null character '\0'
		buf[len+1] = '\0';
	}
	else
	{
		return 1; // no room left
	}
	return 0;
}

static void ExecCommand(char * calcBuf, char * ansBuf, bool isPolish)
{
	// simple history
	// TODO: clean up whitespace and standardize/display interpreted formatted input instead of just copying it over
	strcpy(ansBuf, calcBuf);
	
	// Make a tree of the operators and operands based on polish or not just like in the object-oriented C book
}

// Main code
int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Window* window = SDL_CreateWindow("Cross-Platform Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    /*ImFont* defaultFont = */io.Fonts->AddFontFromFileTTF("fonts/UbuntuMono-R.ttf", 18.0f);
    ImFont* buttonFont = io.Fonts->AddFontFromFileTTF("fonts/UbuntuMono-R.ttf", 36.0f);
    ImFont* outputFont = io.Fonts->AddFontFromFileTTF("fonts/Ubuntu-R.ttf", 24.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

	// Set the style to our custom style
    StyleColorsCalculator();
    StyleRoundingCalculator();

    // Our state
    bool show_demo_window = true;
    bool show_diagnostics_window = false;
    bool reverse_polish = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    const float BUTTON_HEIGHT = 90.0f;
    float button_width; // to be initialized before first use
    static char calcBuf[CALC_BUFFER_SIZE] = ""; 
    static char calcAnswer[CALC_BUFFER_SIZE] = "";

    // Main loop
    bool done = false;
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. This is our main calculator window, eventually this will be moved to its own file & function to clean up the main function
        {
			// Always start with a begin call
            ImGui::Begin("Calculator Output");

			// Here is out main output and keyboard input field, along with a (?) tip
			// Set width and font for output
			ImGui::PushItemWidth(-35.0f);
			ImGui::PushFont(outputFont);
			// Here we add a bunch of flags
			ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCharFilter;
            bool reclaim_focus = false;
            // Enter returns true allows you to easily act on it like this
            if(ImGui::InputText("##CalculatorOutput", calcBuf, CALC_BUFFER_SIZE, input_text_flags, CalculatorOutputCallback))
            {
				char* s = calcBuf;
		        TrimTrailingWhitespace(s); //trim trailing whitespace
		        if (s[0]) //if not null
		            ExecCommand(s, calcAnswer, reverse_polish); //do something
		        strcpy(s, "");
		        reclaim_focus = true;
			}
			// Auto-focus on window apparition
		    ImGui::SetItemDefaultFocus();
		    if (reclaim_focus)
		        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
		
            float calc_width = ImGui::GetItemRectSize().x;
            ImGui::PopItemWidth();
            ImGui::PopFont();
            ImGui::SameLine(); HelpMarker("Main input/output of the calculator. You can input numbers, spaces, and the standard operators +-*/^()");
            
            // answer line
            ImGui::Text("%s",calcAnswer);
            
            // For buttons we'll render them in a larger font instead of default
            ImGui::PushFont(buttonFont);
            
            // Button width calculation
            button_width = (calc_width/4.0f) - ((3.0f/4.0f) * ImGui::GetStyle().ItemSpacing.x);
            
            // Row 1 of buttons
            if (ImGui::Button("7", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'7');}
            ImGui::SameLine(); if (ImGui::Button("8", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'8');}
            ImGui::SameLine(); if (ImGui::Button("9", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'9');}
            ImGui::SameLine(); if (ImGui::Button("/", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'/');}
            
            // Row 2 of buttons
            if (ImGui::Button("4", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'4');}
            ImGui::SameLine(); if (ImGui::Button("5", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'5');}
            ImGui::SameLine(); if (ImGui::Button("6", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'6');}
            ImGui::SameLine(); if (ImGui::Button("*", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'*');}
            
            // Row 3 of buttons
            if (ImGui::Button("1", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'1');}
            ImGui::SameLine(); if (ImGui::Button("2", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'2');}
            ImGui::SameLine(); if (ImGui::Button("3", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'3');}
            ImGui::SameLine(); if (ImGui::Button("-", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'-');}
            
            // Row 4 of buttons
            if (ImGui::Button("0", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'0');}
            ImGui::SameLine(); if (ImGui::Button(".", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'.');}
            ImGui::SameLine(); if (ImGui::Button("+", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,'+');}
            ImGui::SameLine(); if (ImGui::Button("_", ImVec2(button_width, BUTTON_HEIGHT))){append_char(calcBuf,' ');}
            
            // Return to default font
            ImGui::PopFont();
            
            
            ImGui::Checkbox("Show Calculator Diagnostics Window", &show_diagnostics_window);
            ImGui::SameLine(); HelpMarker("Checking this box will open the diagnostics window, which shows useful debug and \"under the hood\" calculation information");
            ImGui::Checkbox("Reverse Polish Notation", &reverse_polish);
            ImGui::SameLine(); HelpMarker("Reverse Polish Notation is a different style of calculation that handles precedence explicitly.\n\n"
            								"3 * (2 + 7)\n\nis written instead as\n\n2 7 + 3 *\n\nfor example. Visit the wikipedia page to learn more!");

            if (ImGui::Button("Calculate"))
            {
            	char* s = calcBuf;
		        TrimTrailingWhitespace(s); //trim trailing whitespace
		        if (s[0]) //if not null
		            ExecCommand(s, calcAnswer, reverse_polish); //do something
		        strcpy(s, "");
            }
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_diagnostics_window)
        {
            ImGui::Begin("Calculator Diagnostics", &show_diagnostics_window);
            ImGui::Text("Current Calculator Output Buffer String: \"%s\"", calcBuf);
            ImGui::Text("strlen() of Calculator Output Buffer String: %ld", strlen(calcBuf));
            if (ImGui::Button("Close"))
                show_diagnostics_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
