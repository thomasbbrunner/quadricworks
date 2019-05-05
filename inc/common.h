#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <random>

#include <glm/glm.hpp>

class Math
{
  public:
    static void add_to_each(std::vector<unsigned int> *vec, unsigned int value)
    {
        for (unsigned int i = 0; i < vec->size(); i++)
        {
            vec->at(i) += value;
        }
    }

    static float random(float max, float min)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(min, max);

        // Use dis to transform the random unsigned int generated by gen into a
        // double in [1, 2). Each call to dis(gen) generates a new random double

        return dis(gen);
    }

    static void normalize(std::vector<glm::vec3> *vertices)
    {
        for (unsigned int i = 0; i < vertices->size(); i++)
        {
            vertices->at(i) = glm::normalize(vertices->at(i));
        }
    }

    static void normalize2(std::vector<glm::vec3> *vertices)
    {
        for (unsigned int i = 0; i < vertices->size(); i++)
        {
            float d = vertices->at(i).x + vertices->at(i).y + vertices->at(i).z;
            glm::mat3 trans(1.0 / d);
            vertices->at(i) = d * vertices->at(i);
        }
    }

    static void multiply_by_scalar(std::vector<glm::vec3> *vertices, float d)
    {
        glm::mat3 trans(d);
        for (unsigned int i = 0; i < vertices->size(); i++)
        {
            vertices->at(i) = trans * vertices->at(i);
        }
    }
};

#endif