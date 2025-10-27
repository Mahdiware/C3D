CC = gcc
CFLAGS = -Wall -std=c11 -Ilibs/glad/include -Isrc
LIBS = -lglfw -ldl -lm

SRC = src/main.c \
	  libs/glad/src/glad.c \
	  src/engine/core/renderer/renderer.c \
	  src/engine/core/shader/shader.c \
	  src/engine/core/scene/scene.c \
	  src/engine/matrix4x4/matrix4x4.c \
	  src/engine/vec3/vec3.c \
	  src/engine/object/object.c \
      src/engine/vertex/vertex.c \
      src/engine/triangle/Triangle.c \
      src/engine/helper/helper.c \
      src/engine/Mesh/mesh.c \
      src/engine/Rect/Rect.c



OBJ = $(patsubst %.c,build/%.o,$(SRC))
TARGET = opengl_gui

# Ensure build directories exist
BUILD_DIRS = $(sort $(dir $(OBJ)))

all: $(TARGET)

# Create build directories if they don't exist
$(BUILD_DIRS):
	mkdir -p $@

# Link target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o build/$@ $^ $(LIBS)

# Compile .c -> .o
build/%.o: %.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*
