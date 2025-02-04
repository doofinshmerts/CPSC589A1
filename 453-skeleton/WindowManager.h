/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#pragma once
#include <GLFW/glfw3.h>

class InputManager;

/**
 * handles creating GLFWwindow
 */
class WindowManager
{
private:
    // private variables here
    // the width and height of the window
    int width = 0;
    int height = 0;

    // pointer to the glfw window
    GLFWwindow *window = nullptr;

    // the input manager to send input to
    InputManager *input_manager = nullptr;

public:
    // public function here

    // constructor
    WindowManager(int width, int height);

    /**
     * sets up the GLFW window
     * @return: false if window could not be created
     */
    bool SetupWindow();

    /**
     * sets the input manager
     * @param _input: the pointer to the input manager
     */
    void SetInputManager(InputManager *_input);

    /**
     * @return: true if the window should close
     */
    bool ShoudWindowClose();

    /**
     * @return: a pointer to the GLFWwindow
     */
    GLFWwindow *GetWindowPointer();

private:
    // private functions here

    /**
     * callback to resize the window on window resize event
     * @param _window: the window (dummy)
     * @param width: the width of the window
     * @param height: the height of the window
     */
    static void UpdateWindowSize(GLFWwindow *_window, int _width, int _height);

    // callback function allowing input to the inputmanager
    static void KeyboardInputHandler(GLFWwindow *_window, int key, int scancode, int action, int mods);
    // callback function for the mouse button
    static void MouseButtonInputHandler(GLFWwindow *_window, int button, int action, int mods);
    // callback function for mouse position
    static void CursorPositionInputHandler(GLFWwindow *_window, double x_pos, double y_pos);
    // callback function for mouse scroll wheel
    static void ScrollWheelInputHandler(GLFWwindow *_window, double xoffset, double yoffset);
};