/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */
#pragma once

class GeometryManager;

/**
 * 
 */
class InputManager
{
private:

    const float MAX_VALUE = 1.0f; // the maximum x y value of the affine transformation
    const float MIN_VALUE = -1.0f; // the minimum x y value of the affine transformation

    int scr_width = 800; // the screen width 
    int scr_height = 600; // the screen height

    float cursor_x = 0.0f; // the x position of the cursor, normalized to window coordinates 
    float cursor_y = 0.0f; // the y position of the cursor, normalized to window coordinates

    float last_x = 0.0f; // the last x position of the cursor
    float last_y = 0.0f; // the last y position of the cursor

    float x_translate = 0.1f; // the translation in the x coordinate
    float y_translate = -0.4f; // the translation in the y coordinate

    bool is_drag = false; // is the mouse attempting to drag a point
    bool apply_transform = false; // should the displayed curve have the transform applied to it
    bool use_bezier = false; // should the displayed curve be the bezier curve

    GeometryManager* geometry_manager = nullptr;

public:

    void SetGeometryManager(GeometryManager* manager);

    // input handlers for the gui
    void HandleWindowResize(int _width, int _height);
    void HandleMouseButton(int button, int action, int mods);
    void HandleCursorPositionChange(double x_pos, double y_pos);

    void RenderGUI();

    void SetY();
    void SetX();

    void ApplyTransform();
    void SetBezier();

    void DragPoint();
};