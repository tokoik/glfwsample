#include <GL/glfw.h>

int main(int argc, const char * argv[])
{
  glfwInit();

  glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

  while (glfwGetWindowParam(GLFW_OPENED))
  {
    /*
    ** ここで OpenGL による描画を行う
    */

    glfwSwapBuffers();
  }

  glfwTerminate();

  return 0;
}
