/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#pragma once

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class WindowManager;
class InputManager;
class GeometryManager;
class ShaderProgram;

/**
 * the graphics manager is in charge of setting up opengl, and rendering graphics objects to the screen
 */
class GraphicsManager
{
private:
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;

    WindowManager *window_manager = nullptr;
    InputManager *input_manager = nullptr;
    ShaderProgram *standardShader = nullptr;
    GeometryManager *geometry_manager = nullptr;

public:
    /**
     * setup the graphics manager and start rendering stuff
     */
    void StartGraphics();

private:
    /**
     * setup the graphics manager, opengl, the camera, window, and input manager
     */
    bool SetupGraphicsManager();

    /**
     * start the render loop and loop until the window is closed by the user
     */
    void StartRenderLoop();
    /**
     * delete all things created with the new command
     */
    void Clean();
};