
#pragma once

#include <glm/glm.hpp>

#include <array>

namespace qe
{
    namespace geometry
    {

        template<std::size_t num_vertices_mesh, std::size_t num_vertices_contour, std::size_t num_vertices_dots, 
        constexpr class Geometry
        {
        private:
            std::array<glm::vec3> vertex_coordinates_mesh;
            std::array<glm::vec3> vertex_coordinates_contour;
            std::array<glm::vec3> vertex_coordinates_dots;
            std::array<unsigned int> vertex_indices_mesh;
            std::array<unsigned int> vertex_indices_contour;
        };

        class Cube
        {
        private:
            Cube() {}
        };

    } // namespace geometry
} // namespace qe
