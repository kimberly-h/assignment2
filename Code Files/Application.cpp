#include "Application.h"
#include "Input.h"
#include "FrameBuffer.h"

GLFWwindow* Application::m_window = nullptr;
float Application::m_prevTime = 0.0f;
float Application::m_deltaTime = 0.0f;

int Application::m_width;
int Application::m_height;

void Application::Init(const std::string& name, bool isFullscreen)
{
	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	//Window resizing
	glfwWindowHint(GLFW_RESIZABLE, false);

	//Create window
	if(isFullscreen)
		m_window = glfwCreateWindow(800, 800, name.c_str(), glfwGetPrimaryMonitor(), NULL);
	else
	{
		m_width  = 1440;
		m_height = 900;
		m_window = glfwCreateWindow(m_width, m_height, name.c_str(), nullptr, nullptr);
	}
	glfwMakeContextCurrent(m_window);

	//glfwSetKeyCallback(m_window, Input::GLFWInputCallback);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD_INIT_FAILED" << std::endl;
		glfwTerminate();
	}

	glViewport(0, 0, m_width, m_height);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	FrameBuffer::InitFullscreenQuad();
	//Disable cursor
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::DeltaTime()
{
	float t = static_cast<float>(glfwGetTime());

	m_deltaTime = t - m_prevTime;
	m_prevTime = t;
}

void Application::FrameStart()
{
	//Calculate delta time
	DeltaTime();

	//Input
	glfwPollEvents();

	//Clearwindow.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void Application::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

float Application::GetDeltaTime()
{
	return m_deltaTime;
}

GLFWwindow* Application::GetWindow()
{
	return m_window;
}

bool Application::IsExitProgram()
{
	return glfwWindowShouldClose(m_window);
}

void Application::SetClearColor(const glm::vec4& clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

int Application::GetWindowWidth()
{
	return m_width;
}

int Application::GetWindowHeight()
{
	return m_height;
}
