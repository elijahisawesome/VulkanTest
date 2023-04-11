#include <glm/glm.hpp>
#include <chrono>
#include "InputGatherer.h"
#include "Camera.h"
#include <iostream>
#include "UBO.h"

Camera::Camera(uint32_t width, uint32_t height, GLFWwindow* window, std::vector<double>* mousePositions, INPUTGATHERER::InputGatherer* inputGatherer) {
	Width = width;
	Height = height;
	Window = window;
	MousePositions = mousePositions;
	InputGatherer = inputGatherer;
	inputBoolArray = {0,0,0,0};
}

Camera::Camera() {}
void Camera::MatrixOps(UBO::UniformBufferObject* ubo) {
	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	//UBO MODEL
	ubo->model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//UBO VIEW
	float rotY = Sensitivity * (float)((*MousePositions)[0] - (Width / 2)) / Width;
	float rotX = Sensitivity * (float)((*MousePositions)[1] - (Height / 2)) / Height;

	Orientation = glm::rotate(
		Orientation,
		glm::radians(-rotX),
		glm::normalize(glm::cross(Orientation, Up)));

	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

	ubo->view = glm::lookAt(Position, Position+Orientation, Up);
	
	//UBO PROJECTION

	
	ubo->proj = glm::perspective(1.5f, (float)(Width/Height),nearPlane,farPlane);


	ubo->proj[1][1] *= -1;

	/*
	ubo->model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo->view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f * Sensitivity, -(*MousePositions)[0] * Sensitivity, 0.0f * Sensitivity), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo->proj = glm::perspective(glm::radians(90.0f), Width / (float) Height, 0.1f, 10.0f);
	ubo->proj[1][1] *= -1;
	*/
}
void Camera::updateInputs() {
	InputGatherer->getKeyboardVals(&inputBoolArray);
	if (inputBoolArray[0]) {
		Position += speed*Orientation;
	}
	if (inputBoolArray[1]) {
		Position += speed * -glm::normalize(glm::cross(Orientation,Up));
	}
	if (inputBoolArray[2]) {
		Position += speed * -Orientation;
	}
	if (inputBoolArray[3]) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}

}