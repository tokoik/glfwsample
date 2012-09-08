#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

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

  // OpenGL の初期設定
  init();

  // 図形を表示する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    ** ここで OpenGL による描画を行う
    */

    glfwSwapBuffers();
  }

  return EXIT_SUCCESS;
}
