#include <iostream>
#include <cstdlib>

// 補助プログラム
#include "gg.h"
using namespace gg;

// 初期設定
static void init(void)
{
  // 背景色
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

// 終了処理
static void term(void)
{
  // GLFW を終了する
  glfwTerminate();
}

// シェーダオブジェクトのコンパイル結果を表示する
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // コンパイル結果を取得する
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
  
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
  
  return (GLboolean)status;
}
 
// プログラムオブジェクトのリンク結果を表示する
static GLboolean printProgramInfoLog(GLuint program)
{
  // リンク結果を取得する
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error" << std::endl;

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
  
  return (GLboolean)status;
}

// プログラムオブジェクトの作成
static GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc)
{
  // バーテックスシェーダのシェーダオブジェクト
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vobj, 1, &vsrc, NULL);
  glCompileShader(vobj);
  printShaderInfoLog(vobj, "vertex shader");

  // フラグメントシェーダのシェーダオブジェクトの作成
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fobj, 1, &fsrc, NULL);
  glCompileShader(fobj);
  printShaderInfoLog(fobj, "fragment shader");

  // シェーダオブジェクトの取り付け
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // プログラムオブジェクトのリンク
  glBindAttribLocation(program, 0, pv);
  glBindFragDataLocation(program, 0, fc);
  glLinkProgram(program);
  printProgramInfoLog(program);

  return program;
}

// 頂点配列オブジェクトの作成
static GLuint createObject(GLuint vertices, const GLfloat (*position)[2])
{
  // 頂点配列オブジェクト
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // 頂点バッファオブジェクト
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 2 * vertices, position, GL_STATIC_DRAW);

  // 結合されている頂点バッファオブジェクトを attribute 変数から参照できるようにする
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // 頂点バッファオブジェクトと頂点配列オブジェクトの結合を解除する
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return vao;
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

  // 補助プログラムの初期化
  ggInit();

  // 開いたウィンドウに対する設定
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // OpenGL の初期設定
  init();

  // バーテックスシェーダのソースプログラム
  static const GLchar vsrc[] =
    "#version 150 core\n"
    "in vec4 pv;\n"
    "void main(void)\n"
    "{\n"
    "  gl_Position = pv;\n"
    "}\n";
  
  // フラグメントシェーダのソースプログラム
  static const GLchar fsrc[] =
    "#version 150 core\n"
    "out vec4 fc;\n"
    "void main(void)\n"
    "{\n"
    "  fc = vec4(1.0, 0.0, 0.0, 0.0);\n"
    "}\n";
  
  // プログラムオブジェクトの作成
  GLuint program = createProgram(vsrc, "pv", fsrc, "fc");

  // 図形データ
  static const GLfloat position[][2] =
  {
    { -0.9f, -0.9f },
    {  0.9f, -0.9f },
    {  0.9f,  0.9f },
    { -0.9f,  0.9f }
  };
  static const int vertices = sizeof position / sizeof position[0];

  // 頂点配列オブジェクトの作成
  GLuint vao = createObject(vertices, position);

  // 図形を表示する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT);

    // シェーダプログラムの使用
    glUseProgram(program);

    // 図形の描画
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, vertices);
    glBindVertexArray(0);

    // シェーダプログラムの使用終了
    glUseProgram(0);

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
