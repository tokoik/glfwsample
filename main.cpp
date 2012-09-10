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
  static const GLchar *vsrc[] =
  {
    "#version 150 core\n",
    "in vec4 pv;",
    "void main(void)",
    "{",
    "  gl_Position = pv;",
    "}",
  };

  // コンパイル／リンク結果
  GLint status;

  // バーテックスシェーダのシェーダオブジェクト
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vobj, sizeof vsrc / sizeof vsrc[0], vsrc, NULL);
  glCompileShader(vobj);

  // フラグメントシェーダのソースプログラムの作成
  static const GLchar *fsrc[] =
  {
    "#version 150 core\n",
    "out vec4 fc;",
    "void main(void)",
    "{",
    "  fc = vec4(1.0, 0.0, 0.0, 0.0);",
    "}",
  };

  // フラグメントシェーダのシェーダオブジェクトの作成
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fobj, sizeof fsrc / sizeof fsrc[0], fsrc, NULL);
  glCompileShader(fobj);

  // プログラムオブジェクトの作成
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // プログラムオブジェクトのリンク
  glBindAttribLocation(program, 1, "pv");
  glBindFragDataLocation(program, 0, "fc");
  glLinkProgram(program);

  // 図形を表示する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT);

    // シェーダプログラムの使用
    glUseProgram(program);

    /*
    ** ここで OpenGL による描画を行う
    */

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
