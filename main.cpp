#include <GL/glfw.h>

int main(int argc, const char * argv[])
{
  glfwInit();

  glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

  while (glfwGetWindowParam(GLFW_OPENED))
  {
    /*
    ** Ç±Ç±Ç≈ OpenGL Ç…ÇÊÇÈï`âÊÇçsÇ§
    */

    glfwSwapBuffers();
  }

  glfwTerminate();

  return 0;
}
