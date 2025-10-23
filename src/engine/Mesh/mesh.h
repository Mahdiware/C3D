//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_MESH_H
#define C_3D_RENDERING_ENGINE_MESH_H


#include "engine/object/object.h"

typedef struct {
    Object **objects;
    int num_objects;

    update_function update;
    update_function customUpdate;
} Mesh;

Mesh *initialize_mesh();
void add_object(Mesh *scene, Object *object);
void add_objects(Mesh *scene, Object **objects, int num_objects);
void remove_object(Mesh *scene, Object *object);
void on_update_mesh(Mesh *mesh, update_function function);

#endif //C_3D_RENDERING_ENGINE_MESH_H