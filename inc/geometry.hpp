
#pragma once

#include "print.hpp"
#include "error.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>

#include <vector>

class Geometry
{
public:
    std::vector<glm::vec3> vertex_coordinates_mesh;
    std::vector<glm::vec3> vertex_coordinates_contour;
    std::vector<glm::vec3> vertex_coordinates_dots;
    std::vector<unsigned int> vertex_indices_mesh;
    std::vector<unsigned int> vertex_indices_contour;

    void apply_noise(float time = 0.0)
    {
        for (unsigned int i = 0; i < vertex_coordinates_dots.size(); i++)
        {
            float noise = glm::perlin(glm::vec4(vertex_coordinates_dots.at(i) / 10.0f, time));
            vertex_coordinates_dots.at(i)[1] += 10.0 * noise;
        }
    }

    // Apply transformation matrix for each vertex
    void apply_transformation(glm::mat4 transformation)
    {
        for (unsigned int i = 0; i < vertex_coordinates_mesh.size(); i++)
        {
            vertex_coordinates_mesh.at(i) = glm::vec3(transformation * glm::vec4(vertex_coordinates_mesh.at(i), 1.0));
        }
        for (unsigned int i = 0; i < vertex_coordinates_contour.size(); i++)
        {
            vertex_coordinates_contour.at(i) = glm::vec3(transformation * glm::vec4(vertex_coordinates_contour.at(i), 1.0));
        }
        for (unsigned int i = 0; i < vertex_coordinates_dots.size(); i++)
        {
            vertex_coordinates_dots.at(i) = glm::vec3(transformation * glm::vec4(vertex_coordinates_dots.at(i), 1.0));
        }
    }
};
