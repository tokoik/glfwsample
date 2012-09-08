#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

int main(int argc, const char * argv[])
{
  // GLFW ������������
  if (!glfwInit())
  {
    // �������Ɏ��s����
    std::cerr << "Can't initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  // GLFW �̃E�B���h�E���J��
  if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
    // �E�B���h�E���J���Ȃ�����
    std::cerr << "Can't open GLFW window." << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // �}�`��\������
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    /*
    ** ������ OpenGL �ɂ��`����s��
    */

    glfwSwapBuffers();
  }

  // GLFW ���I������
  glfwTerminate();

  return EXIT_SUCCESS;
}
