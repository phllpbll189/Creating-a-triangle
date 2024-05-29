#define FRAG_SHADER_INCLUDE
#define VERT_SHADER_INCLUDE
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image/stb_image.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <cmath>
#include <shader.fs>
#include <shader.vs>

#define VERTICAL 1
#define HORIZONTAL 0

using namespace std;

void processInput(GLFWwindow* window);

float vertices[] = {
	//postion				//colors	     	//texture coord
     0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,  	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 	1.0f, 1.0f, 0.0f,	0.0f, 1.0f
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {

	//glfw: init and configure 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGl", NULL, NULL);
	if (window == NULL) {
		cout << "failed to create glfw window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	Shader shader(vert_shader_src, frag_shader_src);

	//BUFFERS
	unsigned int VAO, VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//TEXTURE STUFF
	unsigned int texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	unsigned char *data = stbi_load("C:\\Users\\phill\\Documents\\PB_data\\code\\Creating-a-triangle\\textures\\container.jpg", &width, &height, &nrChannels, 0);

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("C:\\Users\\phill\\Documents\\PB_data\\code\\Creating-a-triangle\\textures\\awesomeface.png", &width, &height, &nrChannels, 0);
	
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}

	shader.use();	
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);


	stbi_image_free(data);
	//render loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);



	//terminate after loop
	glfwTerminate();
	return 0;
}

//takes input and sets window close if esc is pressed.
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}