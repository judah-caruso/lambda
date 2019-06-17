#include "_Entry.hpp"

Editor* editor = nullptr;
MenuBar* menu_main = nullptr;

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Decide GL+GLSL versions
	set_platform_gl_attributes();
	if (glsl_version == "") { 
		std::cerr << "Unable to get proper glsl version!" << std::endl;
		return 1;
	}

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_WindowFlags window_flags	= (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window				= SDL_CreateWindow(AUTOMATA_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	SDL_GLContext gl_context		= SDL_GL_CreateContext(window);
	SDL_Renderer* renderer			= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
	bool err = gl3wInit() != 0;
	if (err) {
		std::cerr << "Failed to initialize OpenGL" << std::endl;
		return 1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsLight();
	//ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version.c_str());

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Do UI initializations here
	editor		= new Editor("editor_tileset", window, renderer);
	menu_main	= new MenuBar(editor);

	// Main loop
	bool window_should_close = false;
	while (!window_should_close) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				window_should_close = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				window_should_close = true;
		}

		menu_main->handle_keybinds();
		if (menu_main->program_should_exit())
			window_should_close = true;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		editor->render();
		menu_main->render();

		ImGui::ShowDemoWindow();
		ImGui::ShowMetricsWindow();

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			ImGui::Begin("Debug");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			/*int tmp_x; int tmp_y;
			SDL_GetMouseState(&tmp_x, &tmp_y);
			editor->set_mouse_pos(tmp_x, tmp_y);

			SDL_GetWindowSize(window, &tmp_x, &tmp_y);
			editor->set_window_size(tmp_x, tmp_y);
			*/

			ImGui::Text("Mouse: %d, %d", (int)editor->get_mouse_pos().x, (int)editor->get_mouse_pos().y);	
			ImGui::Text("Coords: %d, %d", (int)editor->mouse_prev.x, (int)editor->mouse_prev.y);
			
			if (ImGui::Button("Toggle Grid"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				editor->flag_display_grid = !editor->flag_display_grid;

			ImGui::End();
		}

		// Frame Rendering
		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
