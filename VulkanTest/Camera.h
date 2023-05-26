#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>
#include <iostream>
#include "serial/impl/win.h"
#include "serial/serial.h"

#include "InputGatherer.h"
#include "UBO.h"


class Camera{
	GLFWwindow* Window;
	public:
		Camera();
		Camera(uint32_t width, uint32_t height, GLFWwindow* window, std::vector<double>* mousePositions, INPUTGATHERER::InputGatherer* inputGatherer);
		void MatrixOps(UBO::UniformBufferObject* ubo);
		void updateInputs();
		void collision();
		std::vector<float>* getOrientation();

		glm::vec3 getPosition() {return Position;};
		void destroy();
	private:
		uint32_t Width;
		uint32_t Height;
		float nearPlane = .1f;
		float farPlane = 100.f;

		float speed = .1f;
		float Sensitivity = 100.f;
		glm::vec3 Position = glm::vec3(-.4f,1.8f,-1.9f);
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		//glm::vec3 cameraDirection = glm::vec3(0.0f,0.0f,0.0f);
		std::vector<float> cameraDirection;
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		std::vector<double>* MousePositions;
		INPUTGATHERER::InputGatherer* InputGatherer;
		std::vector<int> inputBoolArray;

		serial::Serial* newSerialTest;

		float maxX = 1.f;
		float minX = -.7f;
		float maxY = 1.85f;
		float minY = .8f;
		float maxZ = -.3f;
		float minZ = -1.8f;

		float rotx;
		float roty;
		float rotz;
		float rotw;
};



#endif