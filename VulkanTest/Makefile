CFLAGS = -std=c++17 -O2 -I$(STB_INCLUDE_PATH) -I$(SOLOUD_INCLUDE_PATH) -I./
STB_INCLUDE_PATH = ./ResourceLoaders
SOLOUD_INCLUDE_PATH = ./ResourceLoaders/soloud_20200207/soloud20200207/include
SOLOUD_OBJECT_PATH = ./ResourceLoaders/soloud_20200207/soloud20200207/build/gmake/release/Release/SoloudStatic/src/core
SOLOUD_OBJECT2_PATH = ./ResourceLoaders/soloud_20200207/soloud20200207/build/gmake/release/Release/SoloudStatic/src/audiosource/wav



LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
SMALLFLAGS = -lglfw -lpthread -ldl

VulkanTest: main.o 
	g++ -o VulkanTest main.o AudioEngine.o Camera.o InputGatherer.o ./soloudstatic.a $(CFLAGS) $(LDFLAGS)


main.o: main.cpp
	g++ -o main.o -c main.cpp $(CFLAGS) $(LDFLAGS)

#myFiles.o: AudioEngine.o Camera.o InputGatherer.o
#		g++ -o myFiles.o AudioEngine.o Camera.o InputGatherer.o $(CFLAGS) $(LDFLAGS)
AudioEngine.o: AudioEngine.cpp AudioEngine.h 
		g++ -o AudioEngine.o -c AudioEngine.cpp $(CFLAGS) $(LDFLAGS)
Camera.o: Camera.cpp Camera.h 
		g++ -o Camera.o -c Camera.cpp $(CFLAGS) $(LDFLAGS)
InputGatherer.o: InputGatherer.cpp InputGatherer.h 
		g++ -o InputGatherer.o -c InputGatherer.cpp $(CFLAGS) $(LDFLAGS)

#SoloudObjects: 

.PHONY: test clean

test: VulkanTest
	./VulkanTest 
	
clean:
	rm -f VulkanTest
	make test
