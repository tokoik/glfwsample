#include <GL/glfw.h>

int main(int argc, const char * argv[])
{
  glfwInit();

  glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

  while (glfwGetWindowParam(GLFW_OPENED))
  {
    /*
    ** ������ OpenGL �ɂ��`����s��
    */

    glfwSwapBuffers();
  }

  glfwTerminate();

  return 0;
}
