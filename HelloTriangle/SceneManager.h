#pragma once

#include "Shader.h"
#include "GameObject.h" 

// GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void initialize(GLuint width, GLuint height);
	void initializeGraphics();

	void addShader(string vFilename, string fFilename);

	//GLFW callbacks
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void resize(GLFWwindow* window, int width, int height);

	void update();
	void render();
	void run();
	void finish();
	void chooseRender(int i, int nObj);
	//int readLimitedInt();
	//void handleFilterChange(int shaderSelec);
	//void readColor(float color[3]);

	// scene
	void setupScene();
	void setupCamera2D();
	unsigned int loadTexture(string filename); 

private:
	
	//GFLW window
	GLFWwindow *window;

	//our shader program
	vector <Shader *> shaders;

	//2D Camera - Projection matrix
	glm::mat4 projection;

	//our game objects
	vector <GameObject*> objects;

	int textureMaskID, textureMaskID1;

};

