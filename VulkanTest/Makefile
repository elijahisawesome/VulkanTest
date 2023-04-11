CFLAGS = -std=c++17 -O2 -I$(STB_INCLUDE_PATH)
STB_INCLUDE_PATH = ./ImageLoader

LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest 
	
clean:
	rm -f VulkanTest
	make test
