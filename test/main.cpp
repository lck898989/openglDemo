#include <glad/glad.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
typedef unsigned int uint;
typedef unsigned char uchar;
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* showWindowSomething();
// template<class T, int N>
void renderTriangle(int shaderProgram, unsigned int VAO, unsigned int VBO, unsigned int EBO,uint verticesSizeof,uint indicesSizeof,float* elementVertices,uint* indices);
void drawSomgthing();
// settings
void renderTwoTriangle(unsigned int VAO, unsigned int VBO, float* vertices, uint verticesSizeof);
// 渲染带颜色值的顶点数组
void renderObjByMoreP(unsigned int VAO, unsigned int VBO, float* vertices, uint verticesSizeof);
int dealError(GLFWwindow* window);
// 渲染纹理
void renderTexture(uint *texture1,uint *texture2);
void createTexture(uint *texture, int *width, int *height, int *nrChannels, uchar *data,const char *imgSource);
void drawMyElement(uint VAO,uint* textures,uint size,bool is3D,uint shaderProgramID);
void render2dElement();
void render3dBox();
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
uint VAO, VBO,EBO;

float vertices[] = {
	1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,0.0f,1.0f
};
// 带纹理的顶点坐标
float textVertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
// 指定绘制的顺序
uint indices[] = {
	0,1,3,
	1,2,3
};
// 控制着色器中mix函数的第三个参数
float mixNumber = 0.0;
int main()
{
	//gladLoadGLLoader();
	// 设置线框模式
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLFWwindow* window = showWindowSomething();
	// 初始化glload
	dealError(window);
	// 开启深度测试默认是关闭的
	glEnable(GL_DEPTH_TEST);
	Shader shaderItem = Shader("boxShader.vs","boxShader.fs");
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1,&EBO);
	// renderObjByMoreP(VAO,VBO,vertices,sizeof(vertices));
	
	//render2dElement();
	render3dBox();
	unsigned int texture1, texture2;
	
	/*renderTexture(GL_TEXTURE0, &texture1,&width,&height,&nrChannels,data);
	stbi_set_flip_vertically_on_load(true);
	renderTexture(GL_TEXTURE1, &texture2,&width,&height,&nrChannels,data);*/
	renderTexture(&texture1,&texture2);
	
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	shaderItem.use(); // don't forget to activate/use the shader before setting uniforms!
	// or set it via the texture class
	shaderItem.setInt("texture1",0);
	shaderItem.setInt("texture2",1);
	uint textureArr[] = {texture1,texture2};
	//textureArr.size();
	// render loop
	// -----------
	
	// 围绕y轴旋转90度
	
	// 试图矩阵
	glm::mat4 viewMatrix(1.0f);
	// 投影矩阵
	glm::mat4 projectionMatrix(1.0f);
	
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float timeVary = (float)glfwGetTime();
		glm::mat4 trans;
		// 模型矩阵
		
		// 生成变换矩阵
		// 移动到（0.5，-0.5）处
		/*trans = glm::rotate(trans, timeVary, glm::vec3(0.0f, 1.0f, 0.0f));
		trans = glm::rotate(trans, timeVary, glm::vec3(0.0f, 0.0f, 1.0f));*/
		//trans = glm::rotate(trans, timeVary, glm::vec3(1.0f, 0.0f, 0.0f));
		//trans = glm::translate(trans,glm::vec3(0.0f,0.0f,0.0f));
		//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform1f(glGetUniformLocation(shaderItem.ID, "mixNumber"), mixNumber);

		/*glUniformMatrix4fv(glGetUniformLocation(shaderItem.ID, "model"),1,GL_FALSE,glm::value_ptr(modelMatrix));*/
		glUniformMatrix4fv(glGetUniformLocation(shaderItem.ID, "view"),1,GL_FALSE,glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(shaderItem.ID, "projection"),1,GL_FALSE,glm::value_ptr(projectionMatrix));

		//double curTime = glfwGetTime();
		//shaderItem.setFloat("offsetY", 0.3);
		//shaderItem.setFloat("degree",curTime);
		//// draw
		//drawSomgthing();
		//drawMyElement(VAO,textureArr,sizeof(textureArr) / sizeof(*textureArr));
		//shaderItem.use();
		//drawMyElement(VAO,textureArr, sizeof(textureArr) / sizeof(*textureArr),false);
		drawMyElement(VAO,textureArr, sizeof(textureArr) / sizeof(*textureArr),true,shaderItem.ID);
		// -------------------------------------------------------------------------------
		//glm::mat4 trans2;
		//trans2 = glm::mat4(1.0f); // reset it to identity matrix
		//trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
		//float scaleAmount = sin(glfwGetTime());
		//trans2 = glm::scale(trans2, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderItem.ID);
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&EBO);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// 回收占用的内存
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
void drawSomgthing() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}
// 渲染2d element
void render2dElement() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), textVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
// 渲染3d盒子
void render3dBox() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
// 绘制矩形
void drawMyElement(uint VAO,uint* textures,uint size,bool is3D,uint shaderPorgramID) {
	/*for (uint i = 0; i < size; i++) {
		glActiveTexture(GL_TEXTURE + i);
		glBindTexture(GL_TEXTURE_2D,textures[i]);
	}*/
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,textures[1]);
	glBindVertexArray(VAO);
	if (!is3D) {
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	}
	else {
		for (uint i = 0; i < 10; i++) {
			float timeVary = (float)glfwGetTime();
			glm::mat4 modelMatrix(1.0f);
			modelMatrix = glm::translate(modelMatrix,cubePositions[i]);
			modelMatrix = glm::rotate(modelMatrix, timeVary, glm::vec3(1.0, 1.0f, 1.0f));
			glUniformMatrix4fv(glGetUniformLocation(shaderPorgramID,"model"),1,GL_FALSE, glm::value_ptr(modelMatrix));
			glDrawArrays(GL_TRIANGLES,0,36);
		}
	}
}
// 渲染纹理
void renderTexture(uint *texture1,uint *texture2) {
	int width, height, nrChannels;
	unsigned char* data = nullptr;
	stbi_set_flip_vertically_on_load(true);
	/*createTexture(texture1,&width,&height,&nrChannels,data,"container.jpg");
	createTexture(texture2,&width,&height,&nrChannels,data,"awesomeface.png");*/
	glGenTextures(1, texture1);
	glBindTexture(GL_TEXTURE_2D, *texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps

	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, texture2);
	glBindTexture(GL_TEXTURE_2D, *texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

}
void createTexture(uint *texture, int *width, int *height,int *nrChannels,uchar *data,const char *imgSource) {
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps

	 // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	data = stbi_load(imgSource, width, height, nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
int dealError(GLFWwindow* window) {
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}
// 渲染具体的物体对象方法
/**
   绘制三角形对象
*/
void renderTriangle(int shaderProgram, unsigned int VAO, unsigned int VBO, unsigned int EBO, uint verticesSizeof, uint indicesSizeof, float* elementVertices, uint* indices)
{
	cout << "顶点数组的sizeof is " << verticesSizeof << endl;
	// 定义顶点缓冲对象 GL_ARRAY_BUFFER
	glBindVertexArray(VAO);
	// 绑定缓冲对象 修改opengl状态机从此以后任何的缓冲调用都会来配置当前绑定的缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSizeof, elementVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeof, indices, GL_STATIC_DRAW);

	// 配置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// 链接都对象后删除着色器对象我们不在需要了
	
	// 数据已经送往了GPU内存中了可以解绑了
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
// 渲染两个相连的三角形
void renderTwoTriangle(unsigned int VAO,unsigned int VBO,float* vertices,uint verticesSizeof) {
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,verticesSizeof,vertices,GL_STATIC_DRAW);
	// 配置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
/**

	测试在顶点数组中加入更多的属性比如颜色值信息

*/
void renderObjByMoreP(unsigned int VAO,unsigned int VBO,float* vertices,uint verticesSizeof) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSizeof, vertices, GL_STATIC_DRAW);
	// 配置顶点属性指针 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
GLFWwindow* showWindowSomething() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	// glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL_GAME", NULL, NULL);
	
	return window;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (mixNumber <= 0.9) {
			mixNumber += 0.001;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (mixNumber >= 0.1) {
			mixNumber -= 0.001;
		}
	}
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	cout << "width is " << width << "height is " << height << endl;
	glViewport(0, 0, width, height);
}