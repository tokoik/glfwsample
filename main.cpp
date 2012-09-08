#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

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

  // GLFW のウィンドウを開く
  if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
    // ウィンドウが開けなかった
    std::cerr << "Can't open GLFW window." << std::endl;
    exit(EXIT_FAILURE);
  }

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
