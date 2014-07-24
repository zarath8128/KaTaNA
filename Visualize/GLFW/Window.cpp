#include "Window.h"
#include <KaTaNA/General/Debug.h>

namespace KaTaNA
{
	namespace Visualize
	{
		namespace GLFW
		{
			void glfw_error_function(int error_code, const char *description)
			{
				std::cerr << "ERROR! KaTaNA Window on GLFW3 is encouter GLFW3 error.\n";
				std::cerr << "Error code : " << error_code << "\n";
				std::cerr << "Description: " << description << "\n";
			}

			bool WindowBase::glfw_initialized = false;
			int  WindowBase::glfw_window_count= 0;
			
			WindowBase::WindowBase()
			{
				if(!glfw_initialized)
				{
					std::cerr << "KaTaNA Window on GLFW3 initialize GLFW3.\n";
					glfwSetErrorCallback(glfw_error_function);
					if(GL_TRUE != glfwInit())
					{
						std::cerr << "Initialiging GLFW3 is failed.\n";
						std::cerr << "Program will abort.\n";
						exit(1);
					}

					glfw_initialized = true;
					std::cerr << "done.\n\n";
				}
			}

			WindowBase::~WindowBase()
			{
				if(!glfw_window_count)
				{
					std::cerr << "KaTaNA Window on GLFW3 terminate GLFW3.\n";
					glfwTerminate();
					std::cerr << "done.\n";
				}
			}

			void WindowBase::Update()
			{
				glfwPollEvents();
			}

			void Window::position(GLFWwindow* wnd, int x, int y)
			{
				Window *w = (Window*)glfwGetWindowUserPointer(wnd);
				w->x = x;
				w->y = y;
			}
			
			void Window::size(GLFWwindow* wnd, int width, int height)
			{
				Window *w = (Window*)glfwGetWindowUserPointer(wnd);
				w->w = width;
				w->h = height;
			}

			void Window::fbsize(GLFWwindow* wnd, int width, int height)
			{
				Window *w = (Window*)glfwGetWindowUserPointer(wnd);
				w->fbw = width;
				w->fbh = height;
			}

			Window::Window(int w, int h, const char *t, GLFWmonitor *m, GLFWwindow *s, const Hint &hint)
				:isEnable(false), X(x), Y(y), Width(this->w), Height(this->h), fbWidth(fbw), fbHeight(fbh), Title(title)
			{
				hint.apply();
				if(!(wnd = glfwCreateWindow(w, h, t, m, s)))
				{
					std::cerr << "Createting Window is failed.\n";
					std::cerr << "Window '" << t << "' is not enable.\n";
					return;
				}
				glfwSetWindowUserPointer(wnd, this);
				glfwSetWindowPosCallback(wnd, position);
				glfwSetWindowSizeCallback(wnd, size);
				glfwSetFramebufferSizeCallback(wnd, fbsize);
				isEnable = true;
				++glfw_window_count;

				glfwGetWindowPos      (wnd, &x, &y);
				glfwGetWindowSize     (wnd, &this->w, &this->h);
				glfwGetFramebufferSize(wnd, &fbw, &fbh);
				title = t;
			}

			Window::~Window()
			{
				glfwDestroyWindow(wnd);
				--glfw_window_count;
			}

			Window::operator bool() const 
			{
				return isEnable;
			}

			std::ostream &operator<<(std::ostream &dest, const Window &w)
			{
				dest << "Title             :" << w.Title << "\n";
				dest << "X                 :" << w.X << "\n";
				dest << "Y                 :" << w.Y << "\n";
				dest << "Width             :" << w.Width << "\n";
				dest << "Height            :" << w.Height << "\n";
				dest << "Framebuffer Width :" << w.fbWidth << "\n";
				dest << "Framebuffer Height:" << w.fbHeight << "\n";
				return dest;
			}
		}
	}
}
