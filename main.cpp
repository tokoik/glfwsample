#include <iostream>

// 補助プログラム
#include "gg.h"
using namespace gg;

//
// ウィンドウのサイズ変更時の処理
//
static void GLFWCALL resize(int w, int h)
{
  // ウィンドウ全体をビューポートにする
  glViewport(0, 0, w, h);
}

//
// 初期設定
//
static void init(void)
{
  // 背景色
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

//
// シェーダのコンパイル結果の表示
//
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

  return static_cast<GLboolean>(status);
}

//
// シェーダのリンク結果の表示
//
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

  return static_cast<GLboolean>(status);
}

//
// プログラムオブジェクトの作成
//
static GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc)
{
  // バーテックスシェーダのシェーダオブジェクト
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vobj, 1, &vsrc, 0);
  glCompileShader(vobj);
  printShaderInfoLog(vobj, "vertex shader");

  // フラグメントシェーダのシェーダオブジェクトの作成
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fobj, 1, &fsrc, 0);
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

//
// 頂点配列オブジェクトの作成
//
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
  glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat[2]) * vertices, position, GL_STATIC_DRAW);

  // 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // 頂点バッファオブジェクトと頂点配列オブジェクトの結合を解除する
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return vao;
}

//
// メインプログラム
//
int main(int argc, const char * argv[])
{
  // GLFW を初期化する
  if (glfwInit() == GL_FALSE)
  {
    // 初期化に失敗した
    std::cerr << "Error: Failed to initialize GLFW." << std::endl;
    return 1;
  }

  // OpenGL Version 3.2 Core Profile を選択する
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ウィンドウを開く
  if (glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) == GL_FALSE)
  {
    // ウィンドウが開けなかった
    std::cerr << "Error: Failed to open GLFW window." << std::endl;
    return 1;
  }

  // 開いたウィンドウに対する設定
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // ウィンドウのサイズ変更時に呼び出す処理の設定
  glfwSetWindowSizeCallback(resize);

  // 補助プログラムによる初期化
  ggInit();

  // 初期設定
  init();

  // バーテックスシェーダのソースプログラム
  static const GLchar vsrc[] =
    "#version 150 core\n"
    "#extension GL_ARB_explicit_attrib_location: enable\n"
    "layout (location = 0) in vec4 pv;\n"
    "void main(void)\n"
    "{\n"
    "  gl_Position = pv;\n"
    "}\n";

  // フラグメントシェーダのソースプログラム
  static const GLchar fsrc[] =
    "#version 150 core\n"
    "#extension GL_ARB_explicit_attrib_location: enable\n"
    "layout (location = 0) out vec4 fc;\n"
    "void main(void)\n"
    "{\n"
    "  fc = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

  // プログラムオブジェクトの作成
  GLuint program = createProgram(vsrc, "pv", fsrc, "fc");

  // 頂点属性
  static const GLfloat position[][2] =
  {
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f }
  };
  static const int vertices = sizeof position / sizeof position[0];

  // 頂点配列オブジェクトの作成
  GLuint vao = createObject(vertices, position);

  // ウィンドウが開いている間くり返し描画する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT);

    // シェーダプログラムの使用開始
    glUseProgram(program);

    // 図形描画
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, vertices);
    glBindVertexArray(0);

    // シェーダプログラムの使用終了
    glUseProgram(0);

    // バッファを入れ替える
    glfwSwapBuffers();
  }

  return 0;
}
