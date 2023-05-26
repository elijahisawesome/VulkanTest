#include <glm/glm.hpp>
#include <chrono>
#include "InputGatherer.h"
#include "Camera.h"
#include "serial/impl/win.h"
#include "serial/serial.h"
#include <iostream>
#include "UBO.h"

Camera::Camera(uint32_t width, uint32_t height, GLFWwindow* window, std::vector<double>* mousePositions, INPUTGATHERER::InputGatherer* inputGatherer) {
	Width = width;
	Height = height;
	Window = window;
	MousePositions = mousePositions;
	InputGatherer = inputGatherer;
	inputBoolArray = {0,0,0,0};
	cameraDirection = {0.0f,0.0f,0.0f};
	
	newSerialTest = new serial::Serial("COM5", 9600, serial::Timeout::simpleTimeout(5));
}

Camera::Camera() {}
void Camera::MatrixOps(UBO::UniformBufferObject* ubo) {
	
	//TODO Remove this

	
	newSerialTest->flushInput();
	std::string testString = newSerialTest->readline();
		
		std::string string;
		std::string delimiter = "/";
		try {
			for (int x = 0; x < 4; x++) {
				switch (x) {
				case 0:
					string = testString.substr(0, testString.find(delimiter));
					testString.erase(0, testString.find(delimiter) + 1);
					rotx = std::stof(string);
					//std::cout << "rotx:  " << string << '\n';
					break;
				case 1:
					string = testString.substr(0, testString.find(delimiter));
					testString.erase(0, testString.find(delimiter) + 1);
					roty = std::stof(string);
					//std::cout << "roty:  " << string << '\n';
					break;
				case 2:
					string = testString.substr(0, testString.find(delimiter));
					testString.erase(0, testString.find(delimiter) + 1);
					rotz = std::stof(string);
					//std::cout << "rotz:  " << string << '\n';
					break;
				case 3:
					string = testString.substr(0, testString.find(delimiter));
					testString.erase(0, testString.find(delimiter) + 1);
					rotw = std::stof(string);
					//std::cout << "rotw:  " << string << '\n';
					break;
				}

			}
		}
		catch(std::exception e){
			//return;
		}

		
		//model = line.substr(0, line.find(delimiter));
		//line.erase(0, line.find(delimiter) + 1);
	//std::cout << "Arduino say:  " << testString << '\n';
	//std::cout << "Arduino say:  " << testString << '\n';


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

	glm::vec3 tempXOreintation = glm::rotate(
		Orientation,
		glm::radians(-rotX),
		glm::normalize(glm::cross(Orientation, Up)));

	if (!(glm::angle(tempXOreintation, Up) <= glm::radians(3.0f) || (glm::angle(tempXOreintation, -Up) <= glm::radians(3.0f)))) {
		Orientation = tempXOreintation;
	}

	glm::vec4 testvec(rotx,roty,rotz,rotw);


	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);


	Orientation = glm::rotate(testvec, glm::radians(0.f), Up);

	ubo->view = glm::lookAt(Position, Position+Orientation, Up);
	
	glm::vec3 CDirection = glm::normalize(glm::vec3(glm::inverse(ubo->view)[2]));
	cameraDirection[0] = CDirection.x;
	cameraDirection[1] = CDirection.y;
	cameraDirection[2] = CDirection.z;


	
	//UBO PROJECTION

	
	ubo->proj = glm::perspective(1.5f, (float)(Width/Height),nearPlane,farPlane);


	ubo->proj[1][1] *= -1;

	//std::cout << Position.x << " " << Position.y <<" " << Position.z << '\n';
}

void Camera::collision() {
//TODO 
//this is a really bad way to do this. Learn about collision algos later.




	if (!(Position.x < maxX && Position.x > minX)) {
		if (Position.x >= maxX) {
			Position.x = maxX;
		}
		else {
			Position.x = minX;
		}
	}
	if (!(Position.y < maxY && Position.y > minY)) {
		if (Position.y >= maxY) {
			Position.y = maxY;
		}
		else {
			Position.y = minY;
		}
	}
	if (!(Position.z < maxZ && Position.z > minZ)) {
		if (Position.z >= maxZ) {
			Position.z = maxZ;
		}
		else {
			Position.z = minZ;
		}
	}
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

std::vector<float>* Camera::getOrientation() {
	return &cameraDirection;
}
void Camera::destroy() {
	newSerialTest->close();
	delete newSerialTest;
}