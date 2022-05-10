// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <dependency/imgui/imgui.h>
#include <dependency/imgui/imgui_impl_glfw_gl3.h>
#include <shader.h>
#include <stb_image.h>
static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLFWwindow *GUIInit(void)
{
    glfwSetErrorCallback(error_callback);
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(640, 480, "My GUI", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glfwSetKeyCallback(window, key_callback);
    return window;
}

int main(int, char **)
{
    auto window = GUIInit();
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    glEnableVertexAttribArray(0);
    Shader myShader("/home/zihao/Desktop/workspace/my_gui_project/data/shader/Simple.vert",
                    "/home/zihao/Desktop/workspace/my_gui_project/data/shader/Simple.frag");
    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader

        // 1rst attribute buffer : vertices

        myShader.use();
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (!glfwWindowShouldClose(window));
    glfwDestroyWindow(window);
    glfwTerminate();
    // // Setup window
    // glfwSetErrorCallback(error_callback);
    // if (!glfwInit())
    //     return 1;
    // glfwWindowHint(GLFW_SAMPLES, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    // glfwMakeContextCurrent(window);

    // glewInit();

    // // Setup ImGui binding
    // ImGui_ImplGlfwGL3_Init(window, true);

    // // Load FontsR
    // // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    // //ImGuiIO& io = ImGui::GetIO();
    // //io.Fonts->AddFontDefault();
    // //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    // //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    // //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    // //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    // //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    // bool show_test_window = true;
    // bool show_another_window = false;
    // ImVec4 clear_color = ImColor(114, 144, 154);

    // // Main loop
    // while (!glfwWindowShouldClose(window))
    // {
    //     ImGui_ImplGlfwGL3_NewFrame();

    //     // 1. Show a simple window
    //     // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    //     {
    //         static float f = 0.0f;
    //         ImGui::Text("Hello, world!");
    //         ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    //         ImGui::ColorEdit3("clear color", (float*)&clear_color);
    //         if (ImGui::Button("Test Window")) show_test_window ^= 1;
    //         if (ImGui::Button("Another Window")) show_another_window ^= 1;
    //         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //     }

    //     // 2. Show another simple window, this time using an explicit Begin/End pair
    //     if (show_another_window)
    //     {
    //         ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
    //         ImGui::Begin("Another Window", &show_another_window);
    //         ImGui::Text("Hello");
    //         ImGui::End();
    //     }

    //     // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    //     if (show_test_window)
    //     {
    //         ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
    //         ImGui::ShowTestWindow(&show_test_window);
    //     }

    //     // Rendering
    //     int display_w, display_h;
    //     glfwGetFramebufferSize(window, &display_w, &display_h);
    //     glViewport(0, 0, display_w, display_h);
    //     glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     ImGui::Render();

    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    // // Cleanup
    // ImGui_ImplGlfwGL3_Shutdown();
    // glfwTerminate();

    // return 0;
    return 0;
}
