#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PI 3.14159265358979323846

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

double total_time, time, velocity = 70, gravity = 9.8, y = 0, time_s, start_time;

int main(void){
	GLFWwindow *window;

	// Initialize the library
	if (!glfwInit()){
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

	if (!window){
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	// Make the window's context current
	glfwMakeContextCurrent(window);
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	total_time = 2 * velocity / gravity * 1000;
	start_time = glfwGetTime();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)){
		glClearColor(0.8941176470588236, 0.8941176470588236, 0.8941176470588236, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		time = glfwGetTime() - start_time;
		time_s = time / 1000;

		if (time <= total_time) {
			y = velocity * time - 0.5 * gravity * time * time;
		}

		// render OpenGL here
		glColor3f(0, 0.5, 1);

		glPushMatrix();
		if(y >= 50)
			glTranslatef(0.0f, y, 0.0f);
		drawCircle(SCREEN_WIDTH / 2, 50, 0, 25);
		glPopMatrix();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius){

	GLfloat twicePi = 2.0f * PI;

	GLfloat circleVerticesX[102];
	GLfloat circleVerticesY[102];
	GLfloat circleVerticesZ[102];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < 102; i++){
		circleVerticesX[i] = x + (radius * cos(i *  twicePi / 100));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / 100));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(102) * 3];

	for (int i = 0; i < 102; i++){
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 102);
	glDisableClientState(GL_VERTEX_ARRAY);
}