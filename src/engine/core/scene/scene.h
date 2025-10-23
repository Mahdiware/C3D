//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_SCENE_H
#define C_3D_RENDERING_ENGINE_SCENE_H
#include "engine/Mesh/mesh.h"
#include "engine/object/object.h"


typedef  struct {
    int totalObjects;
    Mesh **objects;
}Scene;

Scene *initialize_scene();
void add_mesh(Scene *scene, Mesh *mesh);
void remove_mesh(Scene *scene, Mesh *mesh);

#endif //C_3D_RENDERING_ENGINE_SCENE_H