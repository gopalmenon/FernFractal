#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

/* Using the standard output for fprintf */
#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <random>

#include "Shader.hpp"
#include "Program.hpp"

GLint attribute_coord2d;
std::shared_ptr<cs5400::Program> program;
std::shared_ptr<std::vector<GLfloat> > bernsleyFernCoordinates;
std::shared_ptr<std::vector<GLfloat> > cyclosorusFernCoordinates;

void onDisplay()
{
  /* Clear the background as white */
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  /* Tell OpenGL which program to use*/
  glUseProgram(program->getHandle());
  /* Setup vertex data */
  glEnableVertexAttribArray(attribute_coord2d);

  /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
  glVertexAttribPointer(
    attribute_coord2d, // attribute
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
	bernsleyFernCoordinates->data()  // pointer to the C array
  );
 
  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_POINTS, 0, bernsleyFernCoordinates->size() / 2);
  glDisableVertexAttribArray(attribute_coord2d);

  glEnableVertexAttribArray(attribute_coord2d);

  /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
  glVertexAttribPointer(
	  attribute_coord2d, // attribute
	  2,                 // number of elements per vertex, here (x,y)
	  GL_FLOAT,          // the type of each element
	  GL_FALSE,          // take our values as-is
	  0,                 // no extra data between each position
	  cyclosorusFernCoordinates->data()  // pointer to the C array
	  );

  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_POINTS, 0, cyclosorusFernCoordinates->size() / 2);
  glDisableVertexAttribArray(attribute_coord2d);

  /* Display the result */
  glutSwapBuffers();
}

//Build cyclosorus fern coordinates
void buildCyclosorusFernCoordinates() {

	cyclosorusFernCoordinates = std::shared_ptr<std::vector<GLfloat> >(new std::vector<GLfloat>());

	//Put in the initial coordinates
	GLfloat previousXCoordinate = 0.0, previousYCoordinate = 0.0;
	cyclosorusFernCoordinates->emplace_back(previousXCoordinate + 3.0);
	cyclosorusFernCoordinates->emplace_back(previousYCoordinate);

	const int NUMBER_OF_ITERATIONS = 1000000;

	std::default_random_engine randomNumberGenerator;
	std::discrete_distribution<int> distribution{ 20000, 840000, 70000, 70000 };

	int randomNumber = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	GLfloat xCoordinate = 0.0, yCoordinate = 0.0;

	for (auto counter = 0; counter < NUMBER_OF_ITERATIONS; ++counter) {

		randomNumber = distribution(randomNumberGenerator);
		if (randomNumber == 0) {
			xCoordinate = 0.0;
			yCoordinate = 0.25 * previousYCoordinate - 0.4;
			++count1;
		}
		else if (randomNumber == 1) {
			xCoordinate = 0.95 * previousXCoordinate + 0.005 * previousYCoordinate - 0.002;
			yCoordinate = -0.005 * previousXCoordinate + 0.93 * previousYCoordinate + 0.5;
			++count2;
		}
		else if (randomNumber == 2) {
			xCoordinate = 0.035 * previousXCoordinate - 0.2 * previousYCoordinate - 0.09;
			yCoordinate = 0.16 * previousXCoordinate + 0.04 * previousYCoordinate + 0.02;
			++count3;
		}
		else if (randomNumber == 3) {
			xCoordinate = -0.04 * previousXCoordinate + 0.2 * previousYCoordinate + 0.083;
			yCoordinate = 0.16 * previousXCoordinate + 0.04 * previousYCoordinate + 0.12;
			++count4;
		}
		else {
			std::cerr << "Random number generation error" << randomNumber << std::endl;
			break;
		}

		cyclosorusFernCoordinates->emplace_back(xCoordinate + 3.0);
		cyclosorusFernCoordinates->emplace_back(yCoordinate);

		previousXCoordinate = xCoordinate;
		previousYCoordinate = yCoordinate;
	}

	std::cout << "Counts are " << count1 << ", " << count2 << ", " << count3 << " and " << count4 << std::endl;
}

//Build bernsley fern coordinates
void buildBernsleyFernCoordinates() {

	bernsleyFernCoordinates = std::shared_ptr<std::vector<GLfloat> >(new std::vector<GLfloat>());

	//Put in the initial coordinates
	GLfloat previousXCoordinate = 0.0, previousYCoordinate = 0.0;
	bernsleyFernCoordinates->emplace_back(previousXCoordinate - 3.0);
	bernsleyFernCoordinates->emplace_back(previousYCoordinate);

	const int NUMBER_OF_ITERATIONS = 1000000;

	std::default_random_engine randomNumberGenerator;
	std::discrete_distribution<int> distribution{ 10000, 850000, 70000, 70000 };

	int randomNumber = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	GLfloat xCoordinate = 0.0, yCoordinate = 0.0;

	for (auto counter = 0; counter < NUMBER_OF_ITERATIONS; ++counter) {

		randomNumber = distribution(randomNumberGenerator);
		if (randomNumber == 0) {
			xCoordinate = 0.0;
			yCoordinate = 0.16 * previousYCoordinate;
			++count1;
		}
		else if (randomNumber == 1) {
			xCoordinate = 0.85 * previousXCoordinate + 0.04 * previousYCoordinate;
			yCoordinate = -0.04 * previousXCoordinate + 0.85 * previousYCoordinate + 1.6;
			++count2;
		}
		else if (randomNumber == 2) {
			xCoordinate = 0.2 * previousXCoordinate - 0.26 * previousYCoordinate;
			yCoordinate = 0.23 * previousXCoordinate + 0.22 * previousYCoordinate + 1.6;
			++count3;
		}
		else if (randomNumber == 3) {
			xCoordinate = -0.15 * previousXCoordinate + 0.28 * previousYCoordinate;
			yCoordinate = 0.26 * previousXCoordinate + 0.24 * previousYCoordinate + 0.44;
			++count4;
		}
		else {
			std::cerr << "Random number generation error" << randomNumber << std::endl;
			break;
		}

		bernsleyFernCoordinates->emplace_back(xCoordinate - 3.0);
		bernsleyFernCoordinates->emplace_back(yCoordinate);

		previousXCoordinate = xCoordinate;
		previousYCoordinate = yCoordinate;
	}

	std::cout << "Counts are " << count1 << ", " << count2 << ", " << count3 << " and " << count4 << std::endl;
 }

int main(int argc, char* argv[])
{
  /* Glut-related initialising functions */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Bernsley and Cyclosorus Ferns");
 
  /* Extension wrangler initialising */
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK)
  {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }
 
  /* When all init functions runs without errors,
  the program can initialise the resources */
  try
  {  
    program = cs5400::make_program
      (
	cs5400::make_vertexShader("vertex.glsl")
      ,cs5400::make_fragmentShader("fragment.glsl")   
      );
    glutDisplayFunc(onDisplay);
	buildBernsleyFernCoordinates();
	buildCyclosorusFernCoordinates();
    glutMainLoop();
  }
  catch(std::exception& e)
  {
    std::cerr << e.what();
  }
  return EXIT_SUCCESS;
}