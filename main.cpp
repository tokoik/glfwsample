#include <iostream>
#include <cstdlib>
#include "gg.h"
using namespace gg;

static GLfloat pv[][2] =
{
  { -0.9f, -0.9f },
  {  0.9f, -0.9f },
  {  0.9f,  0.9f },
  { -0.9f,  0.9f }
};

static const GLchar *vs[] =
{
  "#version 150 core\n",
  "in vec4 pv;\n",
  "void main(void)\n",
  "{\n",
  "  gl_Position = pv;\n",
  "}\n"
};

static const GLchar *fs[] =
{
  "#version 150 core\n",
  "out vec4 fc;\n",
  "void main(void)\n",
  "{\n",
  "  fc = vec4(1.0, 0.0, 0.0, 0.0);\n",
  "}\n"
};

static GLuint program;
static GLint pvLoc = 1;
static GLuint vao, vbo;

/*
** �V�F�[�_�̏���\������
*/
static void printShaderInfoLog(GLuint shader)
{
  // �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
  {
    // �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }
}

/*
** �v���O�����̏���\������
*/
static void printProgramInfoLog(GLuint program)
{
  // �V�F�[�_�̃����N���̃��O�̒������擾����
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
  {
    // �V�F�[�_�̃����N���̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }
}

// �����ݒ�
static void init(void)
{
  // �v���O�����I�u�W�F�N�g�̍쐬
  program = glCreateProgram();

  // attribute �ϐ� pv �̏ꏊ
  //pvLoc = 0;//glGetAttribLocation(program, "pv");
  glBindAttribLocation(program, pvLoc, "pv");

  // �t���O�����g�V�F�[�_�̏o��
  glBindFragDataLocation(program, 0, "fc");
  
  // �V�F�[�_�I�u�W�F�N�g
  GLuint shader;
  
  // �R���p�C���^�����N����
  GLint status;
  
  // �o�[�e�b�N�X�V�F�[�_�̍쐬
  shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader, sizeof vs / sizeof vs[0], vs, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in Vertex Shader." << std::endl;
  printShaderInfoLog(shader);
  glAttachShader(program, shader);
  glDeleteShader(shader);
  
  // �t���O�����g�V�F�[�_�̍쐬
  shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader, sizeof fs / sizeof fs[0], fs, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in Fragment Shader." << std::endl;
  printShaderInfoLog(shader);
  glAttachShader(program, shader);
  glDeleteShader(shader);

  // �v���O�����̃����N
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
  printProgramInfoLog(program);
  
  // �A���C�I�u�W�F�N�g
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // �o�b�t�@�I�u�W�F�N�g
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);
  glVertexAttribPointer(pvLoc, sizeof pv[0] / sizeof pv[0][0], GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(pvLoc);

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

  // �⏕���C�u�����̏�����
  ggInit();

  // �J�����E�B���h�E�ɑ΂���ݒ�
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // OpenGL �̏����ݒ�
  init();

  // �}�`��\������
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT);

    // �}�`�̕`��
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, sizeof pv / sizeof pv[0]);
    glUseProgram(0);

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
