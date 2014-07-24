#ifndef ZARATH_KATANA_VIUSALIZE_GLFW_WINDOW_H
#define ZARATH_KATANA_VISUALIZE_GLFW_WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace KaTaNA
{
	namespace Visualize
	{
		namespace GLFW
		{
			struct Hint
			{
				void apply() const 
				{
					glfwDefaultWindowHints();
				}
			};

			class WindowBase
			{
				static bool glfw_initialized;

			protected:
				static int  glfw_window_count;

				WindowBase();
				~WindowBase();
			public:
				static void Update();
			};

			class Window
				:public WindowBase
			{
				static void position(GLFWwindow*, int, int);
				static void size(GLFWwindow*, int, int);
				static void fbsize(GLFWwindow*, int, int);

				int x, y, w, h, fbw, fbh;
				std::string title;

				GLFWwindow* wnd;
				bool isEnable;

			public:
				const int &X, &Y, &Width, &Height, &fbWidth, &fbHeight;
				const std::string &Title;

				Window(int width = 640, int height = 480, const char *title = "KaTaNA Window on GLFW3", GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr, const Hint &hint = Hint());
				~Window();

				operator bool() const;

			};

			std::ostream &operator<<(std::ostream&, const Window&);
		}
	}
}

#endif
