#include "glad/glad.h"

#include "Application.h"

#include <functional>
#include <imgui.h>
#include <string>
#include <GLFW/glfw3.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Util.h"
#include "UI/Views/LoginView.hpp"
#include "UI/Views/MainView.h"

using namespace Core;

void WindowResizeCallback(GLFWwindow* window, const int width, const int height)
{
    if (width == 0 || height == 0) return;

    glViewport(0, 0, width, height);

    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (app)
    {
    }
}

Application::Application(AppErrorCode* error) : window_(nullptr)
{
    if (!glfwInit())
    {
        // spd log. ERROR could not initialize GLFW
        if (error) *error = AppErrorCode::GLFW_INIT_FAILED;
        return;
    }

    if (error) *error = AppErrorCode::SUCCESS;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // spd log print gl version?

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

AppErrorCode Application::Init(const int width, const int height, std::string_view title)
{
    {
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        GLFWwindow* window = glfwCreateWindow(width, height, std::string(title).c_str(), nullptr, nullptr);
        if (!window)
        {
            // spd log
            return AppErrorCode::GLFW_INIT_FAILED;
        }

        window_ = window;
    }

    glfwSetWindowUserPointer(window_, this);

    //glfwSetFramebufferSizeCallback(window_, WindowResizeCallback);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // VSync, enabled for now

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        // spd log
        return AppErrorCode::GLAD_INIT_FAILED;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    std::function<void(Model::ViewType)> navCallback = [this](Model::ViewType target)
    {
        viewManager_->SwitchView(target);
    };

    viewManager_ = std::make_unique<UI::ViewManager>();
    viewManager_->RegisterView<UI::View::LoginView>(Model::ViewType::LOGIN, navCallback);
    viewManager_->RegisterView<UI::View::MainView>(Model::ViewType::MAIN, navCallback);

    return AppErrorCode::SUCCESS;
}

Application::~Application()
{
    if (ImGui::GetCurrentContext() != nullptr)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::DestroyPlatformWindows();

        if (io.BackendRendererUserData != nullptr)
            ImGui_ImplOpenGL3_Shutdown();

        if (io.BackendPlatformUserData != nullptr)
            ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();
    }

    if (window_)
    {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }

    glfwTerminate();
}

void Application::Run()
{
    viewManager_->SwitchView(Model::ViewType::LOGIN);

    while (!glfwWindowShouldClose(window_))
    {
        Update();
        Render();
    }
}

void Application::Render()
{
    PreRender();

    viewManager_->Render();

    PostRender();
}

void Application::Update()
{
    glfwPollEvents();
}

void Application::PreRender() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void Application::PostRender() const
{
    ImGui::Render();

    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    if (width == 0 || height == 0) return;

    GLCall(glViewport(0, 0, width, height));

    GLCall(glClearColor(0.10f, 0.11f, 0.13f, 1.00f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    const ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window_);
}
