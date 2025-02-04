/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */

#include "GeometryManager.h"
#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

GeometryManager::GeometryManager()
{
    // resize the input vectors
    points.resize(INPUT_POINTS);
    points_translated.resize(INPUT_POINTS);
    points_colors.resize(INPUT_POINTS);
    points_translated_colors.resize(INPUT_POINTS);
    axis.verts.resize(4);
    axis.cols.resize(4);

    poly_curve.verts.resize(NUM_POINTS);
    poly_curve.cols.resize(NUM_POINTS);
    bezier_curve.verts.resize(NUM_POINTS);
    bezier_curve.cols.resize(NUM_POINTS);

    // the axis to draw as a background for the curves
    axis.verts[0] = glm::vec3(-1.0f, 0.0f, 0.0f);
    axis.verts[1] = glm::vec3(1.0f, 0.0f, 0.0f);
    axis.verts[2] = glm::vec3(0.0f, -1.0f, 0.0f);
    axis.verts[3] = glm::vec3(0.0f, 1.0f, 0.0f);

    axis.cols[0] = glm::vec3(1.0f, 1.0f, 1.0f);
    axis.cols[1] = glm::vec3(1.0f, 1.0f, 1.0f);
    axis.cols[2] = glm::vec3(1.0f, 1.0f, 1.0f);
    axis.cols[3] = glm::vec3(1.0f, 1.0f, 1.0f);

    axis_gpu.setVerts(axis.verts);
    axis_gpu.setCols(axis.cols);

    // initialize the values of the input points
    points[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    points[1] = glm::vec3(0.1f, 0.2f, 0.0f);
    points[2] = glm::vec3(0.2f, 0.1f, 0.0f);
    points[3] = glm::vec3(0.3f, 0.3f, 0.0f);

    // initalize the colors
    points_colors[0] = glm::vec3(0.0f, 1.0f, 0.0f);
    points_colors[1] = glm::vec3(0.0f, 1.0f, 0.0f);
    points_colors[2] = glm::vec3(0.0f, 1.0f, 0.0f);
    points_colors[3] = glm::vec3(0.0f, 1.0f, 0.0f);

    input_points.setCols(points_colors);

    points_translated_colors[0] = glm::vec3(0.0f, 0.0f, 1.0f);
    points_translated_colors[1] = glm::vec3(0.0f, 0.0f, 1.0f);
    points_translated_colors[2] = glm::vec3(0.0f, 0.0f, 1.0f);
    points_translated_colors[3] = glm::vec3(0.0f, 0.0f, 1.0f);

    translated_points.setCols(points_translated_colors);

    for (int i = 0; i < NUM_POINTS; i++)
    {
        poly_curve.cols[i] = glm::vec3(1.0f, 0.0f, 0.0f);
        bezier_curve.cols[i] = glm::vec3(1.0f, 1.0f, 0.0f);
    }

    poly_curve_gpu.setCols(poly_curve.cols);
    bezier_curve_gpu.setCols(bezier_curve.cols);

    TranslatePoints();
}

void GeometryManager::Render()
{
    // set the size of the points
    glPointSize(5.0f);
    axis_gpu.bind();
    glDrawArrays(GL_LINES, 0, 4);
    // render the output points
    translated_points.bind();
    glDrawArrays(GL_POINTS, 0, INPUT_POINTS);

    // render the input points
    input_points.bind();
    glDrawArrays(GL_POINTS, 0, INPUT_POINTS);

    // render the curve
    if (use_bezier)
    {
        bezier_curve_gpu.bind();
        glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS);
    }
    else
    {
        poly_curve_gpu.bind();
        glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS);
    }
}

void GeometryManager::AttemptSelectPoint(float x, float y)
{
    int hit_index = -1;
    // check to see if the given point is selecting an existing point
    for (int i = 0; i < INPUT_POINTS; i++)
    {
        float x_delta = (x - points[i].x);
        float y_delta = (y - points[i].y);

        float radius = x_delta * x_delta + y_delta * y_delta;
        if (radius < SELECT_BOUND)
        {
            hit_index = i;
            break;
        }
    }

    // if a point was selected then set point selected to true
    if (hit_index > -1)
    {
        point_selected = true;
        selected_point = hit_index;
    }
}

void GeometryManager::UnselectPoint()
{
    point_selected = false;
}

void GeometryManager::MovePoint(float _new_x, float _new_y)
{
    if (point_selected)
    {
        points[selected_point] = glm::vec3(_new_x, _new_y, 0.0f);
        TranslatePoints();
    }
}

void GeometryManager::UpdateXTranslate(float _x)
{
    x_translate = _x;
    TranslatePoints();
}

void GeometryManager::UpdateYTranslate(float _y)
{
    y_translate = _y;
    TranslatePoints();
}

void GeometryManager::SetBezier(bool _use)
{
    use_bezier = _use;
}

void GeometryManager::SetTranslate(bool _translate)
{
    apply_transform = _translate;
    GenerateBezierCurve();
    GeneratePolyCurve();
}

void GeometryManager::GeneratePolyCurve()
{
    if (apply_transform)
    {
        float step = 1.0f / NUM_POINTS;
        for (int i = 0; i < NUM_POINTS; i++)
        {
            float u = step * (float)i;
            poly_curve.verts[i] = points_translated[0] + u * points_translated[1] + u * u * points_translated[2] + u * u * u * points_translated[3];
        }
    }
    else
    {
        float step = 1.0f / NUM_POINTS;
        for (int i = 0; i < NUM_POINTS; i++)
        {
            float u = step * (float)i;
            poly_curve.verts[i] = points[0] + u * points[1] + u * u * points[2] + u * u * u * points[3];
        }
    }

    poly_curve_gpu.setVerts(poly_curve.verts);
}

void GeometryManager::GenerateBezierCurve()
{
    // this is used for calculating the de Casteljau algorithm
    std::vector<glm::vec3> point_buffer;
    point_buffer.resize(INPUT_POINTS);
    float u_step = 1.0f / NUM_POINTS;

    // calculate the vertex value for each value of u
    for (int u = 0; u < NUM_POINTS; u++)
    {
        // make the first pass use values in c_points
        register float u_value = ((float)u) * u_step;

        // use translated points if the points have been translated
        if (apply_transform)
        {
            for (int i = 0; i < INPUT_POINTS - 1; i++)
            {
                point_buffer[i] = (1 - u_value) * points_translated[i] + u_value * points_translated[i + 1];
            }
        }
        else
        {
            for (int i = 0; i < INPUT_POINTS - 1; i++)
            {
                point_buffer[i] = (1 - u_value) * points[i] + u_value * points[i + 1];
            }
        }

        // calculate the remaining passes using only point_buffer
        for (int i = 2; i < INPUT_POINTS; i++)
        {
            for (int j = 0; j < INPUT_POINTS - i; j++)
            {
                point_buffer[j] = (1 - u_value) * point_buffer[j] + u_value * point_buffer[j + 1];
            }
        }

        // record the vertex at u
        bezier_curve.verts[u] = point_buffer[0];
    }

    bezier_curve_gpu.setVerts(bezier_curve.verts);
}

void GeometryManager::TranslatePoints()
{
    glm::vec3 translation = glm::vec3(x_translate, y_translate, 0.0f);

    points_translated[0] = translation + points[0];
    points_translated[1] = translation + points[1];
    points_translated[2] = translation + points[2];
    points_translated[3] = translation + points[3];

    input_points.setVerts(points);
    translated_points.setVerts(points_translated);

    GenerateBezierCurve();
    GeneratePolyCurve();
}
