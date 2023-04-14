#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>

#include "InputGatherer.h"
#include "UBO.h"


class Camera{
	GLFWwindow* Window;
	public:
		Camera();
		Camera(uint32_t width, uint32_t height, GLFWwindow* window, std::vector<double>* mousePositions, INPUTGATHERER::InputGatherer* inputGatherer);
		void MatrixOps(UBO::UniformBufferObject* ubo);
		void updateInputs();
		glm::vec3 getOrientation(){return Orientation;};
		glm::vec3 getPosition() {return Position;};
	private:
		uint32_t Width;
		uint32_t Height;
		float nearPlane = .1f;
		float farPlane = 100.f;

		float speed = .1f;
		float Sensitivity = 10.f;
		glm::vec3 Position = glm::vec3(0.0f,9.0f,-8.0f);
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		std::vector<double>* MousePositions;
		INPUTGATHERER::InputGatherer* InputGatherer;
		std::vector<int> inputBoolArray;
};



#endif