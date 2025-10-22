

TODO:
- Add More Support
- Basic structs and rendering support

Done:
- Create a basic opengl rendering pipeline
- Added Update Function Support for each object


# Architecture 
```
[ vec2 ] -> {x, y}
[ vec3 ] -> {x, y, z}
[ Vertex ] -> { vec3 position, vec3 color }
[ Object ] -> { Vecrtex[] , type }
[ Scene ] -> { Object[] }

renderer(Scene) -> OpenGL rendering
object.update(object, time)

EXTRA: 
[ Triangle ] -> { Vertex a, b, c }

```