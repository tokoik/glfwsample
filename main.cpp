#include <iostream>
#include <cstdlib>
#include <GL/glfw.h>

int main(int argc, const char * argv[])
{
  // GLFW を初期化する
  if (!glfwInit())
  {
    // 初期化に失敗した
    std::cerr << "Can't initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  // GLFW のウィンドウを開く
  if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
    // ウィンドウが開けなかった
    std::cerr << "Can't open GLFW window." << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // 図形を表示する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    /*
    ** ここで OpenGL による描画を行う
    */

    glfwSwapBuffers();
  }

  // GLFW を終了する
  glfwTerminate();

  return EXIT_SUCCESS;
}
