#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	/*****Jhon*****/
	MoveJhonX = 0.0f;
	MoveJhonY = 0.0f;
	MoveJhonZ = 0.0f;
	RotateJhonX = 0.0f;
	RotateJhonY = 0.0f;
	RotateJhonZ = 0.0f;
	MoveJhonX = 0.0f;
	MoveJhonZ = 0.0f;
	Walking = GL_FALSE;
	/***************/

	//////////Luces//////////
	LuzDj = GL_TRUE;
	LuzBarra = GL_TRUE;
	/////////////////////////
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci?n de GLFW
	if (!glfwInit())
	{
		printf("Fall? inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama?o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall? inicializaci?n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est? usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	/**********JHON**********/
	//Move
	if (key == GLFW_KEY_W)
	{
		theWindow->lastValueJhonZ = theWindow->MoveJhonZ;
		theWindow->lastValueJhonX = theWindow->MoveJhonX;
		theWindow->MoveJhonZ -= 0.5;
	}
	if (key == GLFW_KEY_S)
	{
		theWindow->lastValueJhonZ = theWindow->MoveJhonZ;
		theWindow->lastValueJhonX = theWindow->MoveJhonX;
		theWindow->MoveJhonZ += 0.5;
	}
	if (key == GLFW_KEY_D)
	{
		theWindow->lastValueJhonZ = theWindow->MoveJhonZ;
		theWindow->lastValueJhonX = theWindow->MoveJhonX;
		theWindow->MoveJhonX += 0.5;
	}
	if (key == GLFW_KEY_A)
	{
		theWindow->lastValueJhonZ = theWindow->MoveJhonZ;
		theWindow->lastValueJhonX = theWindow->MoveJhonX;
		theWindow->MoveJhonX -= 0.5;
	}
	//Rotate
	if (key == GLFW_KEY_UP)
	{
		theWindow->MoveJhonY += 1.0;
	}
	if (key == GLFW_KEY_DOWN)
	{
		theWindow->MoveJhonY -= 1.0;
	}
	if (key == GLFW_KEY_LEFT)
	{
		theWindow->RotateJhonZ += 10.0;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		theWindow->RotateJhonZ -= 10.0;
	}
	if ((key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) && action == GLFW_PRESS) {
		theWindow->Walking = GL_TRUE;
	}
	if ((key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) && action == GLFW_RELEASE) {
		theWindow->Walking = GL_FALSE;
	}
	/****************************/
	//////////Luces//////////
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		if (theWindow->LuzDj == GL_TRUE) {
			theWindow->LuzDj = GL_FALSE;
		} else if (theWindow->LuzDj == GL_FALSE) {
			theWindow->LuzDj = GL_TRUE;
		}
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		if (theWindow->LuzBarra == GL_TRUE) {
			theWindow->LuzBarra = GL_FALSE;
		}
		else if (theWindow->LuzBarra == GL_FALSE) {
			theWindow->LuzBarra = GL_TRUE;
		}
	}
	/////////////////////////

	//Camera



	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
