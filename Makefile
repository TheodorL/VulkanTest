STB_INCLUDE_PATH = /home/theodor/libraries/stb
CFLAGS = -std=c++17 -I$(STB_INCLUDE_PATH) -I$(ENGINE_INCLUDE_PATH) -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

window.o: engine/Window.cpp
	clang++ -c -o build/window.o engine/Window.cpp

VulkanApp: main.cpp window.o
	clang++ $(CFLAGS) -o VulkanApp main.cpp build/window.o $(LDFLAGS)

Shaders: shaders/shader.vert shaders/shader.frag
	./compile.sh

.PHONY: test clean

test: VulkanApp Shaders
	./VulkanApp

clean:
	rm -f VulkanApp
	rm -f build/*.o
