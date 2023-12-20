STB_INCLUDE_PATH = /home/theodor/libraries/stb
CFLAGS = -std=c++17 -I$(STB_INCLUDE_PATH) -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanApp: main.cpp
	clang++ $(CFLAGS) -o VulkanApp main.cpp $(LDFLAGS)

Shaders: shaders/shader.vert shaders/shader.frag
	./compile.sh

.PHONY: test clean

test: VulkanApp Shaders
	./VulkanApp

clean:
	rm -f VulkanApp
