STB_INCLUDE_PATH = /home/theodor/libraries/stb
CFLAGS = -std=c++17 -I$(STB_INCLUDE_PATH) -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanApp: main.cpp build/window.o shaders/vert.spv shaders/frag.spv
	clang++ $(CFLAGS) -o VulkanApp main.cpp build/window.o $(LDFLAGS)

build/window.o: engine/Window.cpp
	clang++ $(CFLAGS) -c -o build/window.o engine/Window.cpp

shaders/vert.spv shaders/frag.spv: shaders/shader.vert shaders/shader.frag
	./compile.sh

.PHONY: run clean 

run: VulkanApp
	./VulkanApp

clean:
	rm -f VulkanApp
	rm -f build/*.o
