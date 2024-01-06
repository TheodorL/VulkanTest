STB_INCLUDE_PATH = /home/theodor/libraries/stb
OBJ_INCLUDE_PATH = /home/theodor/libraries/tinyobjloader
CFLAGS = -std=c++17 -O3
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
.PHONY: run run_c clean build deps

build: VulkanApp VulkanAppCompute
	
VulkanApp: main.cpp build/window.o build/camera.o shaders/vert.spv shaders/frag.spv
	clang++ $(CFLAGS) -I$(STB_INCLUDE_PATH) -I$(OBJ_INCLUDE_PATH) -o VulkanApp main.cpp build/window.o build/camera.o $(LDFLAGS)

VulkanAppCompute: main_compute.cpp build/window.o shaders/vert.spv shaders/frag.spv
	clang++ $(CFLAGS) -I$(STB_INCLUDE_PATH) -I$(OBJ_INCLUDE_PATH) -o VulkanAppCompute main_compute.cpp build/window.o $(LDFLAGS)

build/window.o: engine/window.cpp engine/window.hpp
	clang++ $(CFLAGS) -c -o build/window.o engine/window.cpp

build/camera.o: engine/camera.cpp engine/camera.hpp
	clang++ $(CFLAGS) -c -o build/camera.o engine/camera.cpp

shaders/vert.spv shaders/frag.spv: shaders/shader.vert shaders/shader.frag shaders/comp.vert shaders/comp.frag shaders/comp.comp 
	./compile.sh



run_c: VulkanAppCompute
	./VulkanAppCompute
	
run: VulkanApp
	./VulkanApp



clean:
	rm -f VulkanApp
	rm -f build/*.o
