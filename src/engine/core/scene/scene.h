//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_SCENE_H
#define C_3D_RENDERING_ENGINE_SCENE_H
#include "engine/object/object.h"


typedef  struct {
    int totalObjects;
    Object *objects;
}Scene;

Scene *initialize_scene();
void add_object(Scene *scene, Object *object);
void remove_object(Scene *scene, Object *object);

#endif //C_3D_RENDERING_ENGINE_SCENE_H