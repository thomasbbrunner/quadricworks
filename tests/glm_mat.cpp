#include <glm/glm.hpp>
#include "print.h"

int main()
{
    glm::mat4 trans(0.5f);

    Print::mat(trans);

    return 0;
}