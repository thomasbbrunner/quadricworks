
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>

#include "camera.hpp"
#include "light.hpp"
#include "opengl.hpp"
#include "scene.hpp"
#include "time.hpp"

Lighting lighting;

Camera &camera = Camera::get_instance();
OpenGL &opengl = OpenGL::get_instance();

Scene scene;
Light light1;
Light light2;
// Light sun(LIGHT_DIRECTIONAL);

Shader shader2("study41.vert", "study41.frag");

int main()
{
    // SHADERS
    quad::print::info("Building and compiling shaders");

    // GEOMETRIES
    quad::print::info("Creating geometries");

    // 1. Initialize used geometries
    // DotCube dotcube(25, 25, 25, 3);
    // Plane plane(100, 100, 1);
    // Sphere sphere(2.0f);
    // glm::mat4 sphere_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 10.0, -50.0));
    // sphere.apply_transformation(sphere_translate);
    Cube cube(15.0f);

    // 2. Add geometries to scene object
    // scene.add_geometry(plane);
    // scene.add_geometry(sphere);
    scene.add_geometry(cube);

    // (2.5 Generate buffers)
    scene.generate_buffers();

    // 3. Set scene's properties
    scene.set_shader(shader2);
    scene.set_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Lights
    // 1. Add a light source
    lighting.add_source(&light1);
    lighting.add_source(&light2);
    // 2. Set light type
    light1.set_type(Light::Type::POSITIONAL);
    light2.set_type(Light::Type::POSITIONAL);
    // (3. Add geometry to light)
    light1.add_geometry(Sphere(0.2f));
    light2.add_geometry(Sphere(0.2f));

    // Camera
    camera.set_type(camera.Type::STATIC);
    // camera.set_type(Camera::Type::ROTATE_AROUND);
    // camera.set_type(CAMERA_SPLINE);
    // camera.set_position(glm::vec3(0.0f, 20.0f, 10.0f));

    // Time
    qe::Time time{qe::Time::Type::TICKS};

    // Render loop
    quad::print::info("Starting rendering");

    while (!opengl.should_close())
    {
        // Update state
        opengl.update();
        time.update();
        camera.update(time.get());

        // camera.set_position(glm::vec3(0.0f, 0.0f, 80 * (cos(time.get()) + 0.75)));

        // Update lights
        light1.set_position(glm::vec3(0.0, 10.0, 20.0f));
        light1.set_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        light1.set_brightness(Light::Effect::FLARE);
        light1.draw();

        light2.set_position(glm::vec3(0.0, 10.0, -20.0f));
        light2.set_color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        light2.set_brightness(Light::Effect::NORMAL);
        // light.set_attenuation(0.6);
        light2.draw();
        lighting.update();

        // Draw scene
        scene.set_shader(shader2);
        scene.set_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        scene.update_shader(&lighting, time.get());
        scene.draw(Drawer::Type::FILL, 2);
    }

    // Clean up
    opengl.terminate();

    return 0;
}