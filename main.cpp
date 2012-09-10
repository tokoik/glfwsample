#include <iostream>
#include <cstdlib>

// �⏕�v���O����
#include "gg.h"
using namespace gg;

// �����ݒ�
static void init(void)
{
  // �w�i�F
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

// �I������
static void term(void)
{
  // GLFW ���I������
  glfwTerminate();
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

  // �I��������o�^����
  atexit(term);

  // OpenGL Version 3.2 Core Profile ��I������
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFW �̃E�B���h�E���J��
  if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
    // �E�B���h�E���J���Ȃ�����
    std::cerr << "Can't open GLFW window." << std::endl;
    exit(EXIT_FAILURE);
  }

  // �⏕�v���O�����̏�����
  ggInit();

  // �J�����E�B���h�E�ɑ΂���ݒ�
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // OpenGL �̏����ݒ�
  init();

  // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O����
  static const GLchar *vsrc[] =
  {
    "#version 150 core\n",
    "in vec4 pv;",
    "void main(void)",
    "{",
    "  gl_Position = pv;",
    "}",
  };

  // �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vobj, sizeof vsrc / sizeof vsrc[0], vsrc, NULL);
  glCompileShader(vobj);

  // �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̍쐬
  static const GLchar *fsrc[] =
  {
    "#version 150 core\n",
    "out vec4 fc;",
    "void main(void)",
    "{",
    "  fc = vec4(1.0, 0.0, 0.0, 0.0);",
    "}",
  };

  // �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g�̍쐬
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fobj, sizeof fsrc / sizeof fsrc[0], fsrc, NULL);
  glCompileShader(fobj);

  // �v���O�����I�u�W�F�N�g�̍쐬
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // �v���O�����I�u�W�F�N�g�̃����N
  glBindAttribLocation(program, 0, "pv");
  glBindFragDataLocation(program, 0, "fc");
  glLinkProgram(program);

  // �}�`�f�[�^
  static const GLfloat pv[][2] =
  {
    { -0.9f, -0.9f },
    {  0.9f, -0.9f },
    {  0.9f,  0.9f },
    { -0.9f,  0.9f }
  };

  // ���_�o�b�t�@�I�u�W�F�N�g
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);

    // ���_�z��I�u�W�F�N�g
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glVertexAttribPointer(0, sizeof pv[0] / sizeof pv[0][0], GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // �}�`��\������
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p
    glUseProgram(program);

    // �}�`�̕`��
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, sizeof pv / sizeof pv[0]);

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
