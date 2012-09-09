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
** シェーダの情報を表示する
*/
static void printShaderInfoLog(GLuint shader)
{
  // シェーダのコンパイル時のログの長さを取得する
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
  {
    // シェーダのコンパイル時のログの内容を取得する
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }
}

/*
** プログラムの情報を表示する
*/
static void printProgramInfoLog(GLuint program)
{
  // シェーダのリンク時のログの長さを取得する
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
  {
    // シェーダのリンク時のログの内容を取得する
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }
}

// 初期設定
static void init(void)
{
  // プログラムオブジェクトの作成
  program = glCreateProgram();

  // attribute 変数 pv の場所
  //pvLoc = 0;//glGetAttribLocation(program, "pv");
  glBindAttribLocation(program, pvLoc, "pv");

  // フラグメントシェーダの出力
  glBindFragDataLocation(program, 0, "fc");
  
  // シェーダオブジェクト
  GLuint shader;
  
  // コンパイル／リンク結果
  GLint status;
  
  // バーテックスシェーダの作成
  shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader, sizeof vs / sizeof vs[0], vs, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in Vertex Shader." << std::endl;
  printShaderInfoLog(shader);
  glAttachShader(program, shader);
  glDeleteShader(shader);
  
  // フラグメントシェーダの作成
  shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader, sizeof fs / sizeof fs[0], fs, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in Fragment Shader." << std::endl;
  printShaderInfoLog(shader);
  glAttachShader(program, shader);
  glDeleteShader(shader);

  // プログラムのリンク
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
  printProgramInfoLog(program);
  
  // アレイオブジェクト
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // バッファオブジェクト
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);
  glVertexAttribPointer(pvLoc, sizeof pv[0] / sizeof pv[0][0], GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(pvLoc);

  // 背景色
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

// 終了処理
static void term(void)
{
  // GLFW を終了する
  glfwTerminate();
}

int main(int argc, const char * argv[])
{
  // GLFW を初期化する
  if (!glfwInit())
  {
    // 初期化に失敗した
    std::cerr << "Can't initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  // 終了処理を登録する
  atexit(term);

  // OpenGL Version 3.2 Core Profile を選択する
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFW のウィンドウを開く
  if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
    // ウィンドウが開けなかった
    std::cerr << "Can't open GLFW window." << std::endl;
    exit(EXIT_FAILURE);
  }

  // 補助ライブラリの初期化
  ggInit();

  // 開いたウィンドウに対する設定
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // OpenGL の初期設定
  init();

  // 図形を表示する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT);

    // 図形の描画
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, sizeof pv / sizeof pv[0]);
    glUseProgram(0);

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
