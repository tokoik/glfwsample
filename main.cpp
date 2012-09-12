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

// �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // �R���p�C�����ʂ��擾����
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
  
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
  
  return (GLboolean)status;
}
 
// �v���O�����I�u�W�F�N�g�̃����N���ʂ�\������
static GLboolean printProgramInfoLog(GLuint program)
{
  // �����N���ʂ��擾����
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error" << std::endl;

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
  
  return (GLboolean)status;
}

// �v���O�����I�u�W�F�N�g�̍쐬
static GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc)
{
  // �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vobj, 1, &vsrc, NULL);
  glCompileShader(vobj);
  printShaderInfoLog(vobj, "vertex shader");

  // �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g�̍쐬
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fobj, 1, &fsrc, NULL);
  glCompileShader(fobj);
  printShaderInfoLog(fobj, "fragment shader");

  // �v���O�����I�u�W�F�N�g�̍쐬
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // �v���O�����I�u�W�F�N�g�̃����N
  glBindAttribLocation(program, 0, pv);
  glBindFragDataLocation(program, 0, fc);
  glLinkProgram(program);
  printProgramInfoLog(program);

  return program;
}

// ���_�z��I�u�W�F�N�g�̍쐬
static GLuint createObject(GLuint vertices, const GLfloat (*position)[2])
{
  // ���_�z��I�u�W�F�N�g
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�o�b�t�@�I�u�W�F�N�g
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 2 * vertices, position, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� attribute �ϐ�����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // ���_�o�b�t�@�I�u�W�F�N�g�ƒ��_�z��I�u�W�F�N�g�̌�������������
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return vao;
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
  static const GLchar vsrc[] =
    "#version 150 core\n"
    "in vec4 pv;\n"
    "void main(void)\n"
    "{\n"
    "  gl_Position = pv;\n"
    "}\n";
  
  // �t���O�����g�V�F�[�_�̃\�[�X�v���O����
  static const GLchar fsrc[] =
    "#version 150 core\n"
    "out vec4 fc;\n"
    "void main(void)\n"
    "{\n"
    "  fc = vec4(1.0, 0.0, 0.0, 0.0);\n"
    "}\n";
  
  // �v���O�����I�u�W�F�N�g�̍쐬
  GLuint program = createProgram(vsrc, "pv", fsrc, "fc");

  // �}�`�f�[�^
  static const GLfloat position[][2] =
  {
    { -0.9f, -0.9f },
    {  0.9f, -0.9f },
    {  0.9f,  0.9f },
    { -0.9f,  0.9f }
  };
  static const int vertices = sizeof position / sizeof position[0];

  // ���_�z��I�u�W�F�N�g�̍쐬
  GLuint vao = createObject(vertices, position);

  // �}�`��\������
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p
    glUseProgram(program);

    // �}�`�̕`��
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, vertices);
    glBindVertexArray(0);

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
