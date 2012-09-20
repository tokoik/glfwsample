#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

// �����ݒ�
static void init(void)
{
  // �w�i�F
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

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
    exit(EXIT_FAILURE);
  }

  // OpenGL �̏����ݒ�
  init();

  // �}�`��\������
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    ** ������ OpenGL �ɂ��`����s��
    */

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
