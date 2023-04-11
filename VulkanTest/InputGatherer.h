#pragma once
#ifndef INPUTGATHERER
#define INPUTGATHERER
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<vector>


class InputGatherer {
	GLFWwindow* window;
	public:
		InputGatherer();
		InputGatherer(GLFWwindow* Window, int WIDTH, int HEIGHT);
		std::vector<double>* getMousePositionValues();
		void gatherInputs();
		void getKeyboardVals(std::vector<int>* InputBoolArray);
		friend class HelloTriangleApplication;
	private:
		std::vector<double> pMousePositionValues;
		void setCallbacks();
		static void esc_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void getMouseVals();	
		int width;
		int height;
};

#endif