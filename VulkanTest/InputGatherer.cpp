#include "InputGatherer.h"
#include <iostream>

static const float SENS = .001f;

InputGatherer::InputGatherer(GLFWwindow* Window, int WIDTH, int HEIGHT) {
		window = Window;
		width = WIDTH;
		height = HEIGHT;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		pMousePositionValues = std::vector<double>(2);
		setCallbacks();
	}
InputGatherer::InputGatherer(){}

void InputGatherer::gatherInputs() {
		getMouseVals();
	}

std::vector<double>* InputGatherer::getMousePositionValues() {
	return &pMousePositionValues;
}


void InputGatherer::setCallbacks() {
		glfwSetKeyCallback(window, esc_callback);
	}
void InputGatherer::esc_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			
		switch (key)
			case GLFW_KEY_ESCAPE:{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
				break;
				}
	}
void InputGatherer::getMouseVals() {
		glfwGetCursorPos(window, &pMousePositionValues[0], &pMousePositionValues[1]);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
void InputGatherer::getKeyboardVals(std::vector<int>* InputBoolArray) {
	//update movement bool array
	//std::cout<< (*InputBoolArray)[1] << (*InputBoolArray)[2] << (*InputBoolArray)[3]<< (*InputBoolArray)[4];
	//std::cout << (*InputBoolArray)[0];
	
	(*InputBoolArray)[0] = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	(*InputBoolArray)[1] = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	(*InputBoolArray)[2] = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	(*InputBoolArray)[3] = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
}
