#include "Scene.hpp"

#include <iostream>
#include <fstream>

#include "includes/json.hpp"

#include "Entity.hpp"
#include "FlatDrawable.hpp"
#include "Texture.hpp"

#include "components/SpriteDrawableComponent.hpp"

using namespace std;

Scene::Scene(float aspect_ratio) : aspect_ratio(aspect_ratio) {

    Entity background = entity_manager.create();
    transform_2D_component_manager.setTransform(background, Transform2D(glm::vec2(1.0, 1.0), glm::vec2(0, 0)));
    name_component_manager.setName(background, "Background");
    sprite_drawable_component_manager.setSpriteDrawableComponent(background, SpriteDrawableComponent(Texture::createFromColor(glm::vec4(0.9, 0.9, 0.9, 1.0))));

    Entity entity_a = entity_manager.create();
    transform_2D_component_manager.setTransform(entity_a, Transform2D(glm::vec2(0.1, 0.1 * aspect_ratio), glm::vec2(0, 0)));
    name_component_manager.setName(entity_a, "Snorlax");
    sprite_drawable_component_manager.setSpriteDrawableComponent(entity_a, SpriteDrawableComponent(Texture::createFromFile("res/snorlax.png")));

    Entity entity_b = entity_manager.create();
    transform_2D_component_manager.setTransform(entity_b, Transform2D(glm::vec2(0.1, 0.1 * aspect_ratio), glm::vec2(0.5, 0)));
    name_component_manager.setName(entity_b, "Gengar");
    sprite_drawable_component_manager.setSpriteDrawableComponent(entity_b, SpriteDrawableComponent(Texture::createFromFile("res/gengar.png")));

    Entity entity_c = entity_manager.create();
    transform_2D_component_manager.setTransform(entity_c, Transform2D(glm::vec2(0.1, 0.1 * aspect_ratio), glm::vec2(-0.5, 0)));
    name_component_manager.setName(entity_c, "Eevee");
    sprite_drawable_component_manager.setSpriteDrawableComponent(entity_c, SpriteDrawableComponent(Texture::createFromFile("res/eevee.png")));

    Entity entity_d = entity_manager.create();
    transform_2D_component_manager.setTransform(entity_d, Transform2D(glm::vec2(0.1, 0.1 * aspect_ratio), glm::vec2(0, -0.5)));
    name_component_manager.setName(entity_d, "Arcanine");
    sprite_drawable_component_manager.setSpriteDrawableComponent(entity_d, SpriteDrawableComponent(Texture::createFromFile("res/arcanine.png")));


}

Scene::Scene(float aspect_ratio, string filename) : aspect_ratio(aspect_ratio) {
    ifstream scene_input(filename);
    if (!scene_input) {
        cout << "Failed to open file " << filename << "\n";
    }
    string scene_file_contents((istreambuf_iterator<char>(scene_input)), istreambuf_iterator<char>());

    // Use jsoncpp to parse the file contents
    Json::Value root;
    Json::Reader reader;
    bool parsing_successful = reader.parse(scene_file_contents, root);
    if (!parsing_successful){
        cout << "Failed to parse scene\n" << reader.getFormattedErrorMessages();
    }

    Json::Value entities_json = root["entities"];

    for (auto& entity_json : entities_json) {
        Entity entity = entity_manager.create();

        if (entity_json.isMember("transform2DComponent")) {
            Json::Value transform2D_json = entity_json["transform2DComponent"];
            glm::vec2 scale(transform2D_json["scale_x"].asFloat(), transform2D_json["scale_y"].asFloat() * aspect_ratio);
            glm::vec2 position(transform2D_json["position_x"].asFloat(), transform2D_json["position_y"].asFloat());

            Transform2D transform2D(scale, position);
            transform_2D_component_manager.setTransform(entity, transform2D);

        }

        if (entity_json.isMember("nameComponent")) {
            string name = entity_json["name"].asString();
            name_component_manager.setName(entity, name);
        }

        if (entity_json.isMember("spriteDrawableComponent")) {
            Json::Value sprite_drawable_component_json = entity_json["spriteDrawableComponent"];

            if (sprite_drawable_component_json.isMember("sprite")) {
                string sprite_filename = sprite_drawable_component_json["sprite"].asString();
                sprite_drawable_component_manager.setSpriteDrawableComponent(entity, SpriteDrawableComponent(Texture::createFromFile(sprite_filename)));

            } else if (sprite_drawable_component_json.isMember("color")) {
                Json::Value sprite_color_json = sprite_drawable_component_json["color"];
                glm::vec4 sprite_color(
                    sprite_color_json["red"].asFloat(),
                    sprite_color_json["green"].asFloat(),
                    sprite_color_json["blue"].asFloat(),
                    sprite_color_json["alpha"].asFloat()
                );
                sprite_drawable_component_manager.setSpriteDrawableComponent(entity, SpriteDrawableComponent(Texture::createFromColor(sprite_color)));

            }

        }

    }
}

Scene Scene::fromFile(string filename) {
    return Scene(4.0 / 3.0, filename);
}

void Scene::update() {
    sprite_drawable_component_manager.update(transform_2D_component_manager, mesh_component_manager, name_component_manager);
}
