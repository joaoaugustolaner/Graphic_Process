#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
int shaderSelected = 11;
int stickerSelected = 8;
float rgb[]  = {1.0, 0.0, 0.0};
float rgb1[] = {1.0, 0.0, 0.0};
int limiar1 = 84;
int limiar2 = 84;
int limiar3 = 84;
bool load = false;
int figures[8];
bool enter = false, z = false;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();
}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Filters", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Adicionando os shaders
	addShader("../shaders/vertexShader.vs", "../shaders/canaisSeparados.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/grayScale.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/colorizacao.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/inversao.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/binarizacao.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/vignette.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/binColorInvertion.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/binarizacaoGreenBlack.frag");
	addShader("../shaders/vertexShader.vs", "../shaders/fragShader.frag");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	//CONFIGURAÇÃO
	setupScene();
	resized = true;
}

void SceneManager::addShader(string vFilename, string fFilename)
{
	Shader *shader = new Shader (vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		enter = true;
		printf(" \nSticker succesfully saved!");
	}
}

void SceneManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		
		glfwGetCursorPos(window, &xpos, &ypos);
		
		
		if (xpos < 80 && ypos < 72) {shaderSelected = 9;}
		if (xpos < 80 && ypos > 72 && ypos < 144) {shaderSelected = 8;}
		if (xpos < 80 && ypos > 144 && ypos < 216) {shaderSelected = 7;}			
		if (xpos < 80 && ypos > 216 && ypos < 288) {shaderSelected = 6;}			
		if (xpos < 80 && ypos > 288 && ypos < 360) {shaderSelected = 5;}			
		if (xpos < 80 && ypos > 360 && ypos < 432) {shaderSelected = 4;}			
		if (xpos < 80 && ypos > 432 && ypos < 504) {shaderSelected = 3;}			
		if (xpos < 80 && ypos > 504 && ypos < 576) {shaderSelected = 2;}			
		if (xpos < 80 && ypos > 576 && ypos < 648) {shaderSelected = 1;}			
		if (xpos < 80 && ypos > 648 && ypos < 720) {shaderSelected = 0;}
		if (xpos > 80 && xpos < 160 && ypos < 72) {shaderSelected = 10;}
		if (xpos > 80 && xpos < 160 && ypos > 72 && ypos < 144) {shaderSelected = 11;}


		if (xpos > 950 && ypos < 125) {stickerSelected = 1;}
		if (xpos > 950 && ypos > 125 && ypos < 250) { stickerSelected = 0; }
		if (xpos > 950 && ypos > 250 && ypos < 375) { stickerSelected = 2; }
		if (xpos > 950 && ypos > 375 && ypos < 500) { stickerSelected = 3; }
		if (xpos > 950 && ypos > 500 && ypos < 625) { stickerSelected = 4; }
		if (xpos > 950 && ypos > 625){ stickerSelected = 5; }
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	//alter o angulo do primeiro objeto
	//objects[0]->setAngle((float)glfwGetTime());
}

void SceneManager::chooseRender(int i, int nObj) {
	if (i == 0) {
		objects[nObj]->setShader(shaders[0]);
		shaders[0]->setInt("code", 1);
	}
	else if (i == 1) {
		objects[nObj]->setShader(shaders[0]);
		shaders[0]->setInt("code", 2);
	}
	else if (i == 2) {
		objects[nObj]->setShader(shaders[0]);
		shaders[0]->setInt("code", 3);
	}
	else if (i == 3) {
		objects[nObj]->setShader(shaders[1]);
	}
	else if (i == 4) {
		objects[nObj]->setShader(shaders[2]);
		shaders[2]->setVec3("cor", rgb[0], rgb[1], rgb[2]);
	}
	else if (i == 5) {
		objects[nObj]->setShader(shaders[3]);
	}
	else if (i == 6) {
		objects[nObj]->setShader(shaders[4]);
		shaders[4]->setInt("limiar", limiar1);
	}
	else if (i == 7) {
		objects[nObj]->setShader(shaders[5]);
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(shaders[5]->Program, "ourTexture2"), 1);
		glBindTexture(GL_TEXTURE_2D, textureMaskID);
	}
	else if (i == 8) {
		objects[nObj]->setShader(shaders[5]);
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(shaders[5]->Program, "ourTexture2"), 1);
		glBindTexture(GL_TEXTURE_2D, textureMaskID1);
	}
	else if (i == 9) {
		objects[nObj]->setShader(shaders[6]);
		shaders[6]->setInt("limiar", limiar2);
		shaders[6]->setVec3("cor", rgb1[0], rgb1[1], rgb1[2]);
	}
	else if (i == 10) {
		objects[nObj]->setShader(shaders[7]);
		shaders[7]->setInt("limiar", limiar3);
	}
	else {
		objects[nObj]->setShader(shaders[8]);
	}
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	//atualiza e desenha os gameObjects
	if (stickerSelected != 8) {

		GameObject* obj = new GameObject;
		obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
		objects.push_back(obj);
		objects[objects.size() - 1]->setTexture(figures[stickerSelected]);
		objects[objects.size() - 1]->setShader(shaders[8]);

		cout << "\n\nClick on the place to drop the sticker and press G to save" << endl;
		
		double xpos, ypos;

		while (!enter) {
			glfwGetCursorPos(window, &xpos, &ypos);
			ypos -= 720;
			ypos = ypos < 0 ? ypos * (-1) : ypos;
			objects[objects.size() - 1]->setPosition(glm::vec3(xpos, ypos, 0.0));
			objects[objects.size() - 1]->update();
			objects[objects.size() - 1]->draw();
			glfwPollEvents();
		}

		stickerSelected = 8;
		enter = false;
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (i == 12) {
			chooseRender(shaderSelected, i);
		}
		else {
			chooseRender(i, i);
		}
		objects[i]->update();
		objects[i]->draw();
	}
	

}
	

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}


void SceneManager::setupScene()
{
	//Criação dos gameObjects iniciais -- pode-se fazer métodos de criação posteriormente
	
	//Mínimo: posicao e escala e ponteiro para o shader
	GameObject* obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 30.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 90.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 150.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f)); //rearrange sprite size when setting the GameObject
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 210.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);
	
	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 270.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj); 

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 330.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 390.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 450.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 510.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(30.0f, 570.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(90.0f, 570.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(90.0f, 510.0f, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(500.0f, 500.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 450.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 350.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 250.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 150.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	obj = new GameObject;
	obj->setPosition(glm::vec3(750.0f, 50.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	objects.push_back(obj);

	unsigned int texID;
	string picture;
	printf("Welcome to your instagram \n\n");
	printf("To use you can simply press space to test on a generic photo or you can upload your own photo, for that, you'll need to first insert your picture in the TEXTURES folder, after that you can type the word in the terminal like tyhe following example: my_picture.jpeg \n\n");
	printf("Type here the photo name you want: ");

	while (!load) {
		getline(cin, picture);
		load = true;
		if (picture.compare(" ") == 0) {
			picture = "generic.png";
		}
		texID = loadTexture("../textures/" + picture);
		printf("\n\n Image Successfully loaded!");
		printf("\n ---------------------------------------------------------------------------------------------------------");
	}

	textureMaskID = loadTexture("../textures/Vignette.png");
	textureMaskID1 = loadTexture("../textures/flowers.png");

	figures[0] = loadTexture("../stickers/crown.png");
	figures[1] = loadTexture("../stickers/clown.png");
	figures[2] = loadTexture("../stickers/love.png");
	figures[3] = loadTexture("../stickers/sleep.png");
	figures[4] = loadTexture("../stickers/fire.png");
	figures[5] = loadTexture("../stickers/hundred.png");
	
	for (int i = 0; i < objects.size(); i++)
	{
		if(i <= 12)
			objects[i]->setTexture(texID);
		else
			objects[i]->setTexture(figures[i-13]);
	}

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	//corrigindo o aspecto
	float ratio = 1.0;
	float xMin = 0.0, xMax = 800.0, yMin = 0.0, yMax = 600.0, zNear = -1.0, zFar = 1.0;

	projection = glm::ortho(xMin * ratio, xMax * ratio, yMin, yMax, zNear, zFar);


	// Get their uniform location
	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Use();
		GLint projLoc = glGetUniformLocation(shaders[i]->Program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//unsigned char *data = SOIL_load_image("../textures/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	
	if (data)
	{

		if (nrChannels == 3) //jpeg
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		load = false;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
