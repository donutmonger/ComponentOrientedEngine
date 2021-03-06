#ifndef MeshComponentManager_h
#define MeshComponentManager_h

#include <string>
#include <memory>
#include <map>

#include "Entity.hpp"
#include "Mesh.hpp"

class MeshComponentManager {
public:
    MeshComponentManager();
    Mesh& getMesh(Entity entity);

private:
    std::map<Entity, shared_ptr<Mesh>> entity_to_mesh_map;
    Mesh flat_mesh;
};

#endif
