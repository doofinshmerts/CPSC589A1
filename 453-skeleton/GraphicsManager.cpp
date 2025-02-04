/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#include "GraphicsManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> // glfw is library that provides tools for creating an OpenGl context, defineing window parameters, and handling user input
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowManager.h"
#include "ShaderProgram.h"
#include "InputManager.h"
#include "GeometryManager.h"
#include <cmath>
#include <chrono>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GraphicsManager::StartGraphics()
{
    // setup the graphics manager
    if (SetupGraphicsManager())
    {
        // if the graphics manager was setup correctly then start the render loop
        StartRenderLoop();
    }

    // delete everything that was created with the new command
    Clean();
}

bool GraphicsManager::SetupGraphicsManager()
{
    // initialize the window manager
    window_manager = new WindowManager(SCR_WIDTH, SCR_HEIGHT);

    // setup the window manager
    if (!window_manager->SetupWindow())
    {
        return false;
    }

   

    input_manager = new InputManager();

    // give the window manager a reference to the input manager
    window_manager->SetInputManager(input_manager);

    // give the input manager the screen dimensions
    input_manager->HandleWindowResize(SCR_WIDTH, SCR_HEIGHT);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_manager->GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // SHADERS
    standardShader = new ShaderProgram("shaders/test.vert", "shaders/test.frag");
    standardShader->use();
    
    // create the geometry manager
    geometry_manager = new GeometryManager();

    input_manager->SetGeometryManager(geometry_manager);
    
    return true;
}

void GraphicsManager::StartRenderLoop()
{


    std::cout << "starting render loop" << std::endl;

    // loop while the window is not closed
    while (!window_manager->ShoudWindowClose())
    {

        glfwPollEvents();

        standardShader->use();

        glEnable(GL_FRAMEBUFFER_SRGB);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        geometry_manager->Render();
        glDisable(GL_FRAMEBUFFER_SRGB); // disable sRGB for things like imgui

        input_manager->RenderGUI();

        glfwSwapBuffers(window_manager->GetWindowPointer());
    }
}

void GraphicsManager::Clean()
{
    glfwTerminate();

    if (window_manager != nullptr)
    {
        delete window_manager;
    }

    if (input_manager != nullptr)
    {
        delete input_manager;
    }

    if( geometry_manager != nullptr)
    {
        delete geometry_manager;
    }
}