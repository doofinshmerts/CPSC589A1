/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Geometry.h"

// List of vertices and colour using std::vector and glm::vec3
struct GeometryData {
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> cols;
};

class GraphicsManager;

/**
 * Geometry manager manages the geometry of the spirograph program
 */
class GeometryManager
{
    private: 

    const int NUM_POINTS = 100;
    const int INPUT_POINTS = 4;
    const float SELECT_BOUND = 0.001f;

    std::vector<glm::vec3> points; // always the same number of points
    std::vector<glm::vec3> points_translated;
    std::vector<glm::vec3> points_colors;
    std::vector<glm::vec3> points_translated_colors;

    GeometryData poly_curve;
    GeometryData bezier_curve;
    GeometryData axis;

    GPU_Geometry input_points;
    GPU_Geometry translated_points;
    GPU_Geometry poly_curve_gpu;
    GPU_Geometry bezier_curve_gpu;
    GPU_Geometry axis_gpu;

    bool point_selected = false;
    int  selected_point = 0; // the id of the selected point for moving
    bool apply_transform = false;
    bool use_bezier = false;

    float x_translate = 0.1f;
    float y_translate = -0.4f;

    public:

    /**
     * constructor for the geometry manager, initalizes the geometry when called
     */
    GeometryManager();
    
    /**
     * renders the geometry
     */
    void Render();

    void AttemptSelectPoint(float x, float y);
    void UnselectPoint();
    void MovePoint(float _new_x, float _new_y);

    void UpdateXTranslate(float _x);
    void UpdateYTranslate(float _y);

    void SetBezier(bool _use);
    void SetTranslate(bool _translate);

    private:

    void GeneratePolyCurve();
    void GenerateBezierCurve();
    void TranslatePoints();
};