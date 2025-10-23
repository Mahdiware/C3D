//
// Created by arjun on 10/23/25.
//

#include "line.h"

#include <stdlib.h>

#include "engine/helper/helper.h"


Line *init_line(vec3 from, vec3 to) {
    Line *line = malloc(sizeof(Line));
    line->from = from;
    line->to = to;
    return line;
}


Object *getLineObject(Line *line_) {
    Object *line = initialize_object();

    // on_update(triangle, rotateTriangle);

    Vertex* from = initialize_vertex(line_->from, getColor().red);
    Vertex* to = initialize_vertex(line_->to, getColor().red);

    add_vertex(line, from);
    add_vertex(line, to);

    line->mode = GL_LINES;

    return line;
}

Mesh *get_line_mesh(Line *line) {
    Mesh *mesh = initialize_mesh();
    add_object(mesh, getLineObject(line));
    return mesh;
}