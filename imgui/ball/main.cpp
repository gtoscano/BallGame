// Ball — Dear ImGui version. Arrow keys move the ball, ESC quits.
// If the ball leaves the window, it is drawn outside the visible area: it disappears.
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cstdio>
#include <format>

int main() {
    // ---------- setup: window (GLFW) + GUI (ImGui) ----------
    if (!glfwInit()) {
        std::printf("Could not start GLFW. Is there a display?\n");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 450, "Ball", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float ballX = 400;     // start in the middle
    float ballY = 225;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. input: move while the key is held
        if (ImGui::IsKeyDown(ImGuiKey_UpArrow))    ballY -= 4;
        if (ImGui::IsKeyDown(ImGuiKey_DownArrow))  ballY += 4;
        if (ImGui::IsKeyDown(ImGuiKey_LeftArrow))  ballX -= 4;
        if (ImGui::IsKeyDown(ImGuiKey_RightArrow)) ballX += 4;
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))  glfwSetWindowShouldClose(window, true);

        // 2. paint
        ImDrawList& canvas = *ImGui::GetBackgroundDrawList();
        canvas.AddRectFilled(ImVec2(300, 400), ImVec2(500, 420), IM_COL32(0, 120, 255, 255));  // the bar
        canvas.AddCircleFilled(ImVec2(ballX, ballY), 20, IM_COL32(230, 40, 40, 255));         // the ball
        canvas.AddText(ImVec2(10, 10), IM_COL32_WHITE,
                       std::format("Ball at ({:.0f}, {:.0f})", ballX, ballY).c_str());     // C++20

        // 3. show the frame
        ImGui::Render();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// TRY THIS (in "2. paint"):
// 1. Draw 5 balls in a row:  for (int i = 0; i < 5; ++i) canvas.AddCircleFilled(ImVec2(100 + i * 60, 100), 20, IM_COL32(255, 220, 0, 255));
// 2. Draw a wall of bricks with two nested for loops (rows and columns).
// 3. Add a slider to change the ball size:
//        static float size = 20;  ImGui::SliderFloat("Size", &size, 5, 80);
// 4. Change the ball's color when it touches the bar.
// 5. Make the ball come back on the other side when it leaves the window.
