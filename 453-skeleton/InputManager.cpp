/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#include "InputManager.h"
#include "GeometryManager.h"
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void InputManager::SetGeometryManager(GeometryManager *manager)
{
    geometry_manager = manager;
}

// input handlers for the gui
void InputManager::HandleWindowResize(int _width, int _height)
{
    scr_width = _width;
    scr_height = _height;
}

void InputManager::HandleMouseButton(int button, int action, int mods)
{
    if (geometry_manager == nullptr)
    {
        return;
    }
    //std::cout << "button: " << button << ", action: " << action << std::endl;

    // check to see if the left button was pressed
    if (button == 0 && action == 1)
    {
        geometry_manager->AttemptSelectPoint(cursor_x, cursor_y);
        is_drag = true;
    }

    // check to see if the left button was released
    if (button == 0 && action == 0)
    {
        geometry_manager->UnselectPoint();
        is_drag = false;
    }
}

void InputManager::HandleCursorPositionChange(double x_pos, double y_pos)
{
    cursor_x = (x_pos / (float)scr_width) * 2.0f - 1.0f;
    cursor_y = 1.0f - (y_pos / (float)scr_height) * 2.0f;
    //std::cout << "x: " << cursor_x << ", y: " << cursor_y << std::endl;

    if (geometry_manager == nullptr)
    {
        return;
    }
    if (is_drag)
    {
        geometry_manager->MovePoint(cursor_x, cursor_y);
    }
}

void InputManager::SetY()
{
    if (y_translate > MAX_VALUE)
    {
        y_translate = MAX_VALUE;
    }
    else if (y_translate < MIN_VALUE)
    {
        y_translate = MIN_VALUE;
    }

    if (geometry_manager == nullptr)
    {
        return;
    }
    geometry_manager->UpdateYTranslate(y_translate);
}

void InputManager::SetX()
{
    if (x_translate > MAX_VALUE)
    {
        x_translate = MAX_VALUE;
    }
    else if (x_translate < MIN_VALUE)
    {
        x_translate = MIN_VALUE;
    }

    if (geometry_manager == nullptr)
    {
        return;
    }

    geometry_manager->UpdateXTranslate(x_translate);
}

void InputManager::ApplyTransform()
{
    if (geometry_manager == nullptr)
    {
        return;
    }

    geometry_manager->SetTranslate(apply_transform);
}

void InputManager::SetBezier()
{
    if (geometry_manager == nullptr)
    {
        return;
    }

    geometry_manager->SetBezier(use_bezier);
}

void InputManager::DragPoint()
{
}

void InputManager::RenderGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Control panel");

    if (!use_bezier)
    {
        if (ImGui::Checkbox("Show Bezier Q(u)", &use_bezier))
        {
            SetBezier();
        }
    }
    else
    {
        if (ImGui::Checkbox("Show P(u)", &use_bezier))
        {
            SetBezier();
        }
    }

    if (ImGui::Checkbox("Apply Translation", &apply_transform))
    {
        ApplyTransform();
    }

    ImGui::Text("Translate curve by vector (x, y)");

    if(ImGui::InputFloat("Translate x", &x_translate, 0.1f))
    {
        SetX();
    }

    if (ImGui::InputFloat("Translate y", &y_translate, 0.1f))
    {
        SetY();
    }

  

  

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Some middleware thing
}