//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_LINE_H
#define C_3D_RENDERING_ENGINE_LINE_H
#include "engine/Mesh/mesh.h"
#include "engine/object/object.h"
#include "engine/vec3/vec3.h"
#include "engine/vec2/vec2.h"

typedef struct {
    vec3 from;
    vec3 to;
} Line;

Line *init_line(vec3 from, vec3 to);
Object *getLineObject(Line *line);
Mesh *get_line_mesh(Line *line);

#endif //C_3D_RENDERING_ENGINE_LINE_H