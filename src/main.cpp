#include <iostream>

#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "Window.hpp"
#include "OpenGLContext.hpp"
#include "Scene.hpp"
#include "MeshFactory.hpp"
#include "Mesh.hpp"

using namespace std;

void handleInputs(Window& window) {
    // Key repeat delay input
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window.requestClose();
        }

        SDL_Scancode key_scancode = event.key.keysym.scancode;
        if (key_scancode == SDL_SCANCODE_ESCAPE) {
            window.requestClose();
        }

    }

}

int main(int argc, char* argv[]) {

    Viewport viewport(800, 600);
    Window window(viewport, false);
    OpenGLContext gl_context(4, 1, window);

    float aspect_ratio = viewport.getAspectRatio();
    Scene scene = Scene::fromFile("res/scenes/test_scene.json");

    // Display loop
    while(window.isOpen()) {
        window.clearBuffers();
        handleInputs(window);

        scene.update();

        window.display();
    }

    // Close the window
    window.close();

    // Nothing went wrong!
    return 0;
}
