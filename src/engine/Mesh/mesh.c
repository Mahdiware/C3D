//
// Created by arjun on 10/23/25.
//
#include "mesh.h"

#include <stdlib.h>
#include <string.h>

void mesh_update(void *mesh_o, double time) {
    Mesh *mesh = (Mesh *)mesh_o;
    for (int i = 0; i < mesh->num_objects; i++) {
        Object *object = (mesh->objects[i]);
        object->update(object, time);
    }
    if (mesh->customUpdate) {
        mesh->customUpdate(mesh, time);
    }
}
void mesh_customUpdate(void *mesh, double time) {

}

Mesh *initialize_mesh() {
    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->num_objects = 0;
    mesh->objects = NULL;
    mesh->update = mesh_update;
    mesh->customUpdate = mesh_customUpdate;
    return mesh;
}
void add_object(Mesh *mesh, Object *object){
     mesh->objects = realloc(mesh->objects, sizeof(Object) * (mesh->num_objects + 1));
    if (!mesh->objects) {
        mesh->num_objects = 0;
        return;
    }
    // Copy the new Object into the array
    mesh->objects[mesh->num_objects] = object;
    mesh->num_objects++;
}

void add_objects(Mesh *scene, Object **objects, int num_objects) {
    for (int i = 0; i < num_objects; i++) {
        add_object(scene, objects[i]);
    }
}
void remove_object(Mesh *mesh, Object *object) {
    if (!object ||mesh->num_objects == 0) return;

    int found_index = -1;
    for (int i = 0; i <mesh->num_objects; i++) {
        if (memcmp(&mesh->objects[i], object, sizeof(Object)) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) return;
    for (int i = found_index; i <mesh->num_objects - 1; i++) {
        mesh->objects[i] = mesh->objects[i + 1];
    }

    mesh->num_objects--;
    if (object->total_vertices > 0) {
        mesh->objects = realloc(mesh->objects, sizeof(Object) *mesh->num_objects);
    } else {
        free(mesh->objects);
        mesh->objects = NULL;
    }
}

void on_update_mesh(Mesh *mesh ,update_function function) {
    mesh->customUpdate = function;
}