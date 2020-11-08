//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes


#include "latticeData3D.h"
#include "cubeLatticeScalarField3D.h"
#include "sphere.h"
#include "shaders.h"
#include "shadersDefinitions.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <algorithm>
#include <vector>
#include <array>
#include <cmath>


const size_t nX = 30;
const size_t nY = 30;
const size_t nZ = 30;


unsigned int marchingCubesShaderProgram = 0;
unsigned int lightSphereShaderProgram = 0;

unsigned int SCREEN_WIDTH = 1600;
unsigned int SCREEN_HEIGHT = 1200;




void bufferGLGridData(double isoLevel, dgr582::CubeLatticeScalarField3D<nX, nY, nZ>& gridData);
void drawGrid();
GLFWwindow* initGL();
float computeDistanceAFromBC(glm::vec3 A, glm::vec3 B, glm::vec3 C);
void assignScalarField(dgr582::LatticeData3D<float, nX, nY, nZ>& scalarField, const dgr582::Point3D& centre);

//https://math.stackexchange.com/questions/1905533/find-perpendicular-distance-from-point-to-line-in-3d
float computeDistanceAFromBC(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
	glm::vec3 d = (C - B) / glm::distance(C,B);
	glm::vec3 v = A - B;
	float t = glm::dot(v,d);
	glm::vec3 P = B + t * d;
	return glm::distance(P,A);
}


void assignScalarField(dgr582::LatticeData3D<float, nX, nY, nZ>& scalarField, const dgr582::Point3D& centre)
{
	for (size_t i = 0; i < nX; ++i)
	{
		for (size_t j = 0; j < nY; ++j)
		{
			for (size_t k = 0; k < nZ; ++k)
			{
				float dX = (i - centre[0] - float(nX) / 2.0f);
				float dY = (j - centre[1] - float(nY) / 2.0f);
				float dZ = (k - centre[2] - float(nZ) / 2.0f);
				float distSq = dX * dX + dY * dY + dZ * dZ;

				auto perpDist = computeDistanceAFromBC(glm::vec3{ dX , dY , dZ }, glm::vec3{ 0,0,0 }, glm::vec3{ 1,0,0 });

				scalarField[{i, j, k}] = float(std::max(std::exp(-0.0085 * distSq) - std::exp(-0.3* perpDist), 0.0));
			}
		}
	}

}



GLFWwindow* initGL()
{
	GLFWwindow* window;

	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DGR582: Marching cubes with OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	return window;
}



unsigned int VAO = 0;
size_t numberOfVertsToDraw = 0;

void bufferGLGridData(double isoLevel, dgr582::CubeLatticeScalarField3D<nX, nY, nZ>& gridData)
{
	auto vertices = gridData.computeVertexDrawData(isoLevel);
	numberOfVertsToDraw = vertices.size() / 6;
	if (numberOfVertsToDraw == 0)
		return;

	unsigned int VBO = 0;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawGrid()
{
	if (numberOfVertsToDraw > 0)
	{
		glUseProgram(marchingCubesShaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, GLsizei(numberOfVertsToDraw));
	}
}



int main(void)
{
	auto window = initGL();
	if (!window)
		return -1;

	//init shaders
	marchingCubesShaderProgram = dgr582::prepareShaders(dgr582::marchingCubesVertexShaderSource, dgr582::marchingCubesFragmentShaderSource);
	lightSphereShaderProgram = dgr582::prepareShaders(dgr582::lightSourceVertexShaderSource, dgr582::lightSourceFragmentShaderSource);


	//Prepare data
	dgr582::Sphere lightSphere{1.0f, 36, 18};
	lightSphere.bufferToGPU();

	dgr582::LatticeData3D<float, nX, nY, nZ> scalarField{};
	dgr582::Point3D centre{ 0.0f, 0.0f, 0.0f };
	assignScalarField(scalarField, centre);


	float gridSpacing = 1.0f;
	dgr582::CubeLatticeScalarField3D<nX, nY, nZ> grid{ gridSpacing, centre, scalarField };

	double isoLevel = 0.5;
	bufferGLGridData(isoLevel, grid); //for marching cubes


	//Set drawing data
	glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	glm::vec3 objectColor{ 0.99609375f,0.80078125f,0.31640625f };

	float cameraRotateRadius = 60.0f;
	float lightPosRadius = 25.0f;
	float camY = 8.0f;

	float cameraRotationRateModifier = 1.5f;
	float lightRotationRateModifier = 5.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	//Set projection matrices once
	glUseProgram(marchingCubesShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(marchingCubesShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUseProgram(lightSphereShaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(lightSphereShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//GL settings
	//glDisable(GL_CULL_FACE); - enable/disable depending on the type of surface you want to draw
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
    {
		//Render
		glClearColor(0.59765625f, 0.21484375f, 0.30078125f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Rotate camera
		float camX = float(sin(cameraRotationRateModifier * glfwGetTime()) * cameraRotateRadius);
		float camZ = float(cos(cameraRotationRateModifier * glfwGetTime()) * cameraRotateRadius);
		glm::vec3 viewPos{ camX, camY, camZ };

		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		view = glm::lookAt(viewPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		float lightX = float(sin(lightRotationRateModifier * glfwGetTime()) * lightPosRadius);
		float lightZ = float(cos(lightRotationRateModifier * glfwGetTime()) * lightPosRadius);

		glm::vec3 lightPos{ lightX,0.0f,lightZ };


		//Draw marching cubes
		glm::mat4 marchingCubesModelMat = glm::mat4(1.0f);

		glUseProgram(marchingCubesShaderProgram);
		glUniform3fv(glGetUniformLocation(marchingCubesShaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform3fv(glGetUniformLocation(marchingCubesShaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(marchingCubesShaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));

		glUniformMatrix4fv(glGetUniformLocation(marchingCubesShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(marchingCubesModelMat));
		glUniformMatrix4fv(glGetUniformLocation(marchingCubesShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(marchingCubesShaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));		
		drawGrid();


		//Draw light source
		glm::mat4 lightSourceModelMat = glm::mat4(1.0f);
		lightSourceModelMat = glm::translate(lightSourceModelMat, lightPos);

		glUseProgram(lightSphereShaderProgram);

		glUniform3fv(glGetUniformLocation(lightSphereShaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform3fv(glGetUniformLocation(lightSphereShaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(lightSphereShaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));

		glUniformMatrix4fv(glGetUniformLocation(lightSphereShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(lightSourceModelMat));
		glUniformMatrix4fv(glGetUniformLocation(lightSphereShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(lightSphereShaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));

		lightSphere.drawAssumingShaderReady();


		//Finalise main loop
		glfwSwapBuffers(window);
        glfwPollEvents();
    }


	glDeleteShader(marchingCubesShaderProgram);
	glDeleteShader(lightSphereShaderProgram);

	lightSphere.clearGPUBuffers();

	glDeleteVertexArrays(1, &VAO);


    glfwTerminate();
    return 0;
}