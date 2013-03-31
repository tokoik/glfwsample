/*
** ゲームグラフィックス特論用補助プログラム for GLFW
**

Copyright (c) 2011, 2012 Kohe Tokoi. All Rights Reserved.

Permission is hereby granted, free of charge,  to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction,  including without limitation the rights 
to use, copy,  modify, merge,  publish, distribute,  sublicense,  and/or sell 
copies or substantial portions of the Software.

The above  copyright notice  and this permission notice  shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR 
IMPLIED,  INCLUDING  BUT  NOT LIMITED  TO THE WARRANTIES  OF MERCHANTABILITY, 
FITNESS  FOR  A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN  NO EVENT  SHALL 
KOHE TOKOI  BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY,  WHETHER IN 
AN ACTION  OF CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM,  OUT OF  OR  IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**
*/

#include <cstdlib>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "gg.h"

/*
** ゲームグラフィックス特論の都合にもとづく初期化
*/
void gg::ggInit(void)
{
  // バージョンチェック
  if (atof(reinterpret_cast<const char *>(glGetString(GL_VERSION))) < 2.1)
  {
#if defined(WIN32)
    MessageBox(NULL, L"OpenGL Version 2.1 以降に対応したビデオカードが必要です", L"GG特論", MB_OK);
#else
    std::cerr << "Error: This program requires OpenGL 2.1 or lator." << std::endl;
#endif
    exit(EXIT_FAILURE);
  }

#if defined(WIN32)
  if (glewInit() != GLEW_OK)
  {
    MessageBox(NULL, L"GLEW の初期化に失敗しました", L"GG特論", MB_OK);
    exit(EXIT_FAILURE);
  }
#endif

  // Swap Interval の設定
  glfwSwapInterval(1);
}

/*
** OpenGL のエラーチェック
*/
void gg::ggError(const char *msg)
{
  GLenum error = glGetError();

  if (error != GL_NO_ERROR)
  {
    if (msg) std::cerr << msg << ": ";

    switch (error)
    {
    case GL_INVALID_ENUM:
      std::cerr << "An unacceptable value is specified for an enumerated argument" << std::endl;
      break;
    case GL_INVALID_VALUE:
      std::cerr << "A numeric argument is out of range" << std::endl;
      break;
    case GL_INVALID_OPERATION:
      std::cerr << "The specified operation is not allowed in the current state" << std::endl;
      break;
    case GL_OUT_OF_MEMORY:
      std::cerr << "There is not enough memory left to execute the command" << std::endl;
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      std::cerr << "The specified operation is not allowed current frame buffer" << std::endl;
      break;
    default:
      std::cerr << "An OpenGL error has occured: " << std::hex << std::showbase << error << std::endl;
      break;
    }
  }
}

/*
** FBO のエラーチェック
*/
void gg::ggFBOError(const char *msg)
{
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    if (msg) std::cerr << msg << ": ";

    switch (status)
    {
    case GL_FRAMEBUFFER_UNSUPPORTED:
      std::cerr << "Unsupported framebuffer internal" << std::endl;
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      std::cerr << "Framebuffer incomplete, missing attachment" << std::endl;
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      std::cerr << "Framebuffer incomplete, duplicate attachment" << std::endl;
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      std::cerr << "Framebuffer incomplete, missing draw buffer" << std::endl;
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      std::cerr << "Framebuffer incomplete, missing read buffer" << std::endl;
      break;
    default:
      std::cerr << "Programming error; will fail on all hardware: " << std::hex << std::showbase << status << std::endl;
      break;
    }
  }
}

/*
** 配列の内容を TGA ファイルに保存
*/
bool gg::ggSaveTga(GLsizei sx, GLsizei sy, unsigned int depth, const GLubyte *buffer, const char *name)
{
  // ファイルを開く
  std::ofstream file(name, std::ios::binary);
  if (file.fail())
  {
    // 開けなかった
    std::cerr << "Waring: Can't open file: " << name << std::endl;
    return false;
  }

  // ヘッダの書き込み
  const unsigned char header[18] =
  {
    0,          // ID length
    0,          // Color map type (none)
    (depth == 3) ? 2 : 3, // Image Type (2:RGB, 3:Grayscale)
    0, 0,       // Offset into the color map table
    0, 0,       // Number of color map entries
    0,          // Number of a color map entry bits per pixel
    0, 0,       // Horizontal image position
    0, 0,       // Vertical image position
    static_cast<unsigned char>(sx & 0xff),
    static_cast<unsigned char>(sx >> 8),
    static_cast<unsigned char>(sy & 0xff),
    static_cast<unsigned char>(sy >> 8),
    8 * depth,  // Pixel depth (bits per pixel)
    0           // Image descriptor
  };
  file.write(reinterpret_cast<const char *>(header), sizeof header);
  if (file.bad())
  {
    // ヘッダの書き込みに失敗した
    std::cerr << "Waring: Can't write file header: " << name << std::endl;
    file.close();
    return 0;
  }

  // データの書き込み
  file.write(reinterpret_cast<const char *>(buffer), sx * sy * depth);

  // フッタの書き込み
  static const char footer[] = "\0\0\0\0\0\0\0\0TRUEVISION-XFILE.";
  file.write(footer, sizeof footer);

  // 書き込みチェック
  if (file.bad())
  {
    // 書き込みに失敗した
    std::cerr << "Waring: Can't write image data: " << name << std::endl;
  }

  // ファイルを閉じる
  file.close();

  return true;
}

/*
** カラーバッファの内容を TGA ファイルに保存
*/
bool gg::ggSaveColor(const char *name)
{
  // 現在のビューポートのサイズを得る
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  // ビューポートのサイズ分のメモリを確保する
  size_t size = viewport[2] * viewport[3] * 3;
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // メモリ確保に失敗した
    std::cerr << "Waring: Can't allocate memory to write file: " << name << std::endl;
    return false;
  }

  // 画面表示の完了を待つ
  glFinish();

  // カラーバッファの読み込み
  glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3],
    GL_BGR, GL_UNSIGNED_BYTE, buffer);

  // 読み込んだデータをファイルに書き込む
  bool ret = ggSaveTga(viewport[2], viewport[3], 3, buffer, name);

  // メモリの解放
  delete[] buffer;
  
  return ret;
}

/*
** デプスバッファの内容を TGA ファイルに保存
*/
bool gg::ggSaveDepth(const char *name)
{
  // 現在のビューポートのサイズを得る
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  // ビューポートのサイズ分のメモリを確保する
  size_t size = viewport[2] * viewport[3];
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // メモリ確保に失敗した
    std::cerr << "Waring: Can't allocate memory to write file: " << name << std::endl;
    return false;
  }

  // 画面表示の完了を待つ
  glFinish();

  // デプスバッファの読み込み
  glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3],
    GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, buffer);
    
  // 読み込んだデータをファイルに書き込む
  bool ret = ggSaveTga(viewport[2], viewport[3], 1, buffer, name);

  // メモリの解放
  delete[] buffer;
  
  return ret;
}

/*
** TGA ファイル (8/16/24/32bit) の読み込み
*/
GLubyte *gg::ggLoadTga(const char *name, GLsizei &width, GLsizei &height, GLenum &format)
{
  // ファイルを開く
  std::ifstream file(name, std::ios::binary);
  if (file.fail())
  {
    // 開けなかった
    std::cerr << "Waring: Can't open file: " << name << std::endl;
    return 0;
  }

  // ヘッダの読み込み
  unsigned char header[18];
  file.read(reinterpret_cast<char *>(header), sizeof header);
  if (file.bad())
  {
    // ヘッダの読み込みに失敗した
    std::cerr << "Waring: Can't read file header: " << name << std::endl;
    file.close();
    return 0;
  }

  // 幅と高さ
  width = header[13] << 8 | header[12];
  height = header[15] << 8 | header[14];

  // 深度
  size_t depth = header[16] / 8;
  switch (depth)
  {
    case 1:
      format = GL_RED;
      break;
    case 2:
      format = GL_RG;
      break;
    case 3:
      format = GL_BGR;
      break;
    case 4:
      format = GL_BGRA;
      break;
    default:
      std::cerr << "Waring: Unusable format: " << depth << std::endl;
      file.close();
      return 0;
  }

  // データサイズ
  size_t size = width * height * depth;

  // メモリの確保
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // メモリが足らなかった
    std::cerr << "Waring: Too large file: " << name << std::endl;
    file.close();
    return 0;
  }

  // データの読み込み
  if (header[2] & 8)
  {
    // RLE
    size_t p = 0;
    char c;
    while (file.get(c))
    {
      if (c & 0x80)
      {
        // run-length packet
        size_t count = (c & 0x7f) + 1;
        if (p + count * depth > size) break;
        char tmp[4];
        file.read(tmp, depth);
        for (size_t i = 0; i < count; ++i)
        {
          memcpy(reinterpret_cast<char *>(buffer + p), tmp, depth);
          p += depth;
        }
      }
      else
      {
        // raw packet
        size_t count = (c + 1) * depth;
        if (p + count > size) break;
        file.read(reinterpret_cast<char *>(buffer + p), count);
        p += count;
      }
    }
  }
  else
  {
    // 非圧縮
    file.read(reinterpret_cast<char *>(buffer), size);
  }

  // 読み込みチェック
  if (file.bad())
  {
    // 読み込みに失敗した
    std::cerr << "Waring: Can't read image data: " << name << std::endl;
  }

  // ファイルを閉じる
  file.close();

  return buffer;
}

/*
** テクスチャマッピング用のデータの読み込み
*/
void gg::ggLoadTexture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLvoid *image)
{
  // アルファチャンネルがついていれば 4 バイト境界に設定
  glPixelStorei(GL_UNPACK_ALIGNMENT, (format == GL_BGRA || format == GL_RGBA) ? 4 : 1);

  // テクスチャを割り当てる
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_BYTE, image);

  // バイリニア（ミップマップなし），エッジでクランプ
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

/*
** テクスチャマッピング用の TGA 画像ファイルの読み込み
*/
bool gg::ggLoadImage(const char *name, GLenum internal)
{
  // 画像サイズ
  GLsizei width, height;

  // 画像フォーマット
  GLenum format;

  // 画像の読み込み先
  GLubyte *image = ggLoadTga(name, width, height, format);

  // テクスチャメモリへの読み込み
  ggLoadTexture(width, height, internal, format, image);

  // 読み込みに使ったメモリを開放する
  delete[] image;

  return true;
}

/*
** 高さマップ用の TGA 画像ファイルの読み込んで法線マップを作成する
*/
bool gg::ggLoadHeight(const char *name, float nz)
{
  // 画像サイズ
  GLsizei width, height;

  // 画像フォーマット
  GLenum format;

  // 画像の読み込み先
  GLubyte *hmap = ggLoadTga(name, width, height, format);

  // 画像が読み込めなかったら戻る
  if (hmap == 0) return false;

  // 作成する法線マップ
  GLfloat (*nmap)[4] = 0;

  // メモリサイズ
  GLsizei maxsize = width * height;

  // メモリを確保する
  try
  {
    nmap = new GLfloat[maxsize][4];
  }
  catch (std::bad_alloc e)
  {
    delete[] hmap;
    return false;
  }

  // 法線マップの作成
  for (GLsizei i = 0; i < maxsize; ++i)
  {
    int x = i % width, y = i - x;

    // 隣接する画素との値の差を法線の成分に用いる
    float nx = static_cast<float>(hmap[y + (x + 1) % width] - hmap[i]);
    float ny = static_cast<float>(hmap[(y + width) % maxsize + x] - hmap[i]);

    // 法線の長さを求めておく
    float nl = sqrt(nx * nx + ny * ny + nz * nz);

    // 法線を求める
    nmap[i][0] = nx * 0.5f / nl + 0.5f;
    nmap[i][1] = ny * 0.5f / nl + 0.5f;
    nmap[i][2] = nz * 0.5f / nl + 0.5f;
    nmap[i][3] = hmap[i] * 0.0039215686f; // == 1/255
  }

  // 高さマップの読み込みに使ったメモリを開放する
  delete[] hmap;

  // nmap が GLfloat なので 4 バイト境界に設定
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  // テクスチャを割り当てる
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nmap);

  // バイリニア（ミップマップなし），エッジでクランプ
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  // 法線マップの作成に使ったメモリを解放する
  delete[] nmap;

  return true;
}

/*
** 三角形分割された OBJ ファイルを読み込む
*/
bool gg::ggLoadObj(const char *name, GLuint &nv, GLfloat (*&vert)[3], GLfloat (*&norm)[3], GLuint &nf, GLuint (*&face)[3], bool normalize)
{
  // OBJ ファイルの読み込み
  std::ifstream file(name, std::ios::binary);
  if (file.fail())
  {
    std::cerr << "Error: Can't open OBJ file: " << name << std::endl;
    return false;
  }

  // 一行読み込み用のバッファ
  std::string line;

  // データの数と座標値の最小値・最大値
  float xmin, xmax, ymin, ymax, zmin, zmax;
  xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);
  nv = nf = 0;

  // データを読み込む
  while (std::getline(file, line))
  {
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // 頂点位置
      float x, y, z;

      // 頂点位置はスペースで区切られている
      str >> x >> y >> z;

      // 位置の最大値と最小値を求める (AABB)
      if (x < xmin) xmin = x;
      if (x > xmax) xmax = x;

      if (y < ymin) ymin = y;
      if (y > ymax) ymax = y;

      if (z < zmin) zmin = z;
      if (z > zmax) zmax = z;

      // 頂点数のカウント
      ++nv;
    }
    else if (op == "f")
    {
      // 面数のカウント
      ++nf;
    }
  }

  // メモリの確保
  GLfloat (*fnorm)[3] = 0;
  vert = norm = 0;
  face = 0;
  try
  {
    vert = new GLfloat[nv][3];
    norm = new GLfloat[nv][3];
    face = new GLuint[nf][3];
    fnorm = new GLfloat[nf][3];
  }
  catch (std::bad_alloc e)
  {
    delete[] vert;
    delete[] norm;
    delete[] face;
    vert = norm = 0;
    face = 0;
    file.close();
    return false;
  }

  // 位置と大きさの正規化のための係数
  GLfloat scale, cx, cy, cz;
  if (normalize)
  {
    float sx = xmax - xmin;
    float sy = ymax - ymin;
    float sz = zmax - zmin;
    scale = sx;
    if (sy > scale) scale = sy;
    if (sz > scale) scale = sz;
    scale = (scale != 0.0f) ? 2.0f / scale : 1.0f;
    cx = (xmax + xmin) * 0.5f;
    cy = (ymax + ymin) * 0.5f;
    cz = (zmax + zmin) * 0.5f;
  }
  else
  {
    scale = 1.0f;
    cx = cy = cz = 0.0f;
  }

  // ファイルの巻き戻し
  file.clear();
  file.seekg(0L, std::ios::beg);

  // データの読み込み
  nv = nf = 0;
  while (std::getline(file, line))
  {
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // 頂点位置
      float x, y, z;

      // 頂点位置はスペースで区切られている
      str >> x >> y >> z;

      // 位置と大きさの正規化
      vert[nv][0] = (x - cx) * scale;
      vert[nv][1] = (y - cy) * scale;
      vert[nv][2] = (z - cz) * scale;

      // 頂点数のカウント
      ++nv;
    }
    else if (op == "f")
    {
      // 頂点座標番号
      std::string l, m, n;

      // 頂点座標番号/テクスチャ座標番号/法線番号の組を取り出す
      str >> l >> m >> n;

      // 頂点座標番号だけ整数化する
      face[nf][0] = atoi(l.c_str()) - 1;
      face[nf][1] = atoi(m.c_str()) - 1;
      face[nf][2] = atoi(n.c_str()) - 1;

      // 面数のカウント
      ++nf;
    }
  }

  // ファイルの読み込みチェック
  if (file.bad())
  {
    // うまく読み込めなかった
    std::cerr << "Warning: Can't read OBJ file: " << name << std::endl;
  }
  file.close();

  // 面法線の算出
  for (GLuint f = 0; f < nf; ++f)
  {
    GLuint v0 = face[f][0], v1 = face[f][1], v2 = face[f][2];

    // v1 - v0, v2 - v0 を求める
    GLfloat dx1 = vert[v1][0] - vert[v0][0];
    GLfloat dy1 = vert[v1][1] - vert[v0][1];
    GLfloat dz1 = vert[v1][2] - vert[v0][2];
    GLfloat dx2 = vert[v2][0] - vert[v0][0];
    GLfloat dy2 = vert[v2][1] - vert[v0][1];
    GLfloat dz2 = vert[v2][2] - vert[v0][2];

    // 外積により面法線を求める
    fnorm[f][0] = dy1 * dz2 - dz1 * dy2;
    fnorm[f][1] = dz1 * dx2 - dx1 * dz2;
    fnorm[f][2] = dx1 * dy2 - dy1 * dx2;
  }

  // 頂点法線の値を 0 にしておく
  for (GLuint v = 0; v < nv; ++v)
  {
    norm[v][0] = norm[v][1] = norm[v][2] = 0.0f;
  }

  // 頂点法線の算出
  for (GLuint f = 0; f < nf; ++f)
  {
    // 頂点座標番号
    GLuint v0 = face[f][0], v1 = face[f][1], v2 = face[f][2];

    // 面法線
    GLfloat x = fnorm[f][0];
    GLfloat y = fnorm[f][1];
    GLfloat z = fnorm[f][2];

    // 面法線を頂点法線に積算する
    norm[v0][0] += x;
    norm[v0][1] += y;
    norm[v0][2] += z;

    norm[v1][0] += x;
    norm[v1][1] += y;
    norm[v1][2] += z;

    norm[v2][0] += x;
    norm[v2][1] += y;
    norm[v2][2] += z;
  }

  // 頂点法線の正規化
  for (GLuint v = 0; v < nv; ++v)
  {
    // 頂点法線の長さ
    GLfloat a = sqrt(norm[v][0] * norm[v][0] + norm[v][1] * norm[v][1] + norm[v][2] * norm[v][2]);

    // 頂点法線の正規化
    if (a != 0.0)
    {
      norm[v][0] /= a;
      norm[v][1] /= a;
      norm[v][2] /= a;
    }
  }

  return true;
}

// マテリアル
struct rgb { float r, g, b; };
struct mat
{
  rgb ka;       // ambient
  rgb kd;       // diffuse
  rgb ks;       // specular
  float kshi;   // shininess
};

// 読み込み用のテンポラリデータの形式
struct vec      // ベクトル
{
  float x, y, z;
};
struct vtx      // 頂点属性
{
  vec pos;      // 頂点位置
  vec norm;     // 頂点法線
};
struct fac      // 面データ
{
  GLuint v[3];  // 頂点番号
  GLuint n[3];  // 法線番号
  vec norm;     // 面法線
};
struct grp      // 面グループ
{
  GLuint b;     // 面グループの開始番号
  GLuint c;     // 面グループの頂点数
  const mat *m; // 面グループのマテリアル
  grp(GLuint begin, GLuint count, const mat &material)
  {
    b = begin;
    c = count;
    m = &material;
  }
};

/*
** 三角形分割された OBJ ファイルと MTL ファイルを読み込む
*/
bool gg::ggLoadObj(const char *name, GLuint &ng, GLuint (*&group)[2],
  GLfloat (*&ka)[4], GLfloat (*&kd)[4], GLfloat (*&ks)[4], GLfloat *&kshi,
  GLuint &nv, GLfloat (*&vert)[3], GLfloat (*&norm)[3], bool normalize)
{
  // ファイルパスからディレクトリ名を取り出す
  std::string path(name);
  size_t pos = path.find_last_of("/\\");
  std::string dirname = (pos == std::string::npos) ? "" : path.substr(pos + 1);

  // OBJ ファイルの読み込み
  std::ifstream file(path.c_str());
  if (file.fail())
  {
    std::cerr << "Error: Can't open OBJ file: " << path << std::endl;
    return false;
  }

  // マテリアル
  std::map<std::string, mat> mtl;
  static const char defmtl[] = "Default";
  std::string mtlname(defmtl);

  // デフォルトのマテリアル
  mtl[mtlname].ka.r = 0.1f;
  mtl[mtlname].ka.g = 0.1f;
  mtl[mtlname].ka.b = 0.1f;
  mtl[mtlname].kd.r = 0.6f;
  mtl[mtlname].kd.g = 0.6f;
  mtl[mtlname].kd.b = 0.6f;
  mtl[mtlname].ks.r = 0.3f;
  mtl[mtlname].ks.g = 0.3f;
  mtl[mtlname].ks.b = 0.3f;
  mtl[mtlname].kshi = 40.0f;

  // 読み込み用の一時記憶領域
  std::vector<vec> _norm;
  std::vector<vtx> _vert;
  std::vector<fac> _face;
  std::vector<grp> _group;

  // 座標値の最小値・最大値
  GLuint groupbegin = 0;
  float xmin, xmax, ymin, ymax, zmin, zmax;
  xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);

  // 一行読み込み用のバッファ
  std::string line;

  // データの読み込み
  while (std::getline(file, line))
  {
    // １行取り出して最初のトークンを命令 (op) とみなす
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // 頂点位置
      vtx v;

      // 頂点位置はスペースで区切られている
      str >> v.pos.x >> v.pos.y >> v.pos.z;

      // 頂点位置の最小値と最大値を求める
      if (v.pos.x < xmin) xmin = v.pos.x;
      if (v.pos.x > xmax) xmax = v.pos.x;

      if (v.pos.y < ymin) ymin = v.pos.y;
      if (v.pos.y > ymax) ymax = v.pos.y;

      if (v.pos.z < zmin) zmin = v.pos.z;
      if (v.pos.z > zmax) zmax = v.pos.z;

      // 頂点位置を記録する
      _vert.push_back(v);
    }
    else if (op == "vn")
    {
      // 頂点法線
      vec norm;

      // 頂点法線はスペースで区切られている
      str >> norm.x >> norm.y >> norm.z;

      // 頂点法線を記録する
      _norm.push_back(norm);
    }
    else if (op == "f")
    {
      // 面 (三角形) データ
      fac f;

      //　三頂点のそれぞれについて
      for (int i = 0; i < 3; ++i)
      {
        // １項目取り出す
        std::string tmp;
        str >> tmp;

        // 項目の最初の要素は頂点座標番号 (0 から始まる)
        f.v[i] = atoi(tmp.c_str()) - 1;
        f.n[i] = 0;

        // 残りの項目を取り出す
        size_t pos = tmp.find('/', 0);
        if (pos != std::string::npos)
        {
          // 二つ目の項目は飛ばす
          pos = tmp.find('/', pos + 1);
          if (pos != std::string::npos)
          {
            // 三つ目の項目は法線番号 (0 なら法線の割り当てなし)
            f.n[i] = atoi(tmp.substr(pos + 1).c_str());
          }
        }
      }

      // 面データの記録ｊ
      _face.push_back(f);
    }
    else if (op == "usemtl")
    {
      // 面グループの面数
      GLuint groupcount = static_cast<GLuint>(_face.size()) * 3 - groupbegin;
      if (groupcount > 0)
      {
        // 面グループの頂点データの開始番号と数，およびそのマテリアルを記録する
        grp b(groupbegin, groupcount, mtl[mtlname]);
        _group.push_back(b);

        // 次の面グループの開始番号を求めておく
        groupbegin += groupcount;
      }

      // マテリアル名の取り出し
      str >> mtlname;

      // マテリアルの存在チェック
      if (mtl.find(mtlname) == mtl.end())
      {
        std::cerr << "Warning: Undefined material: " << mtlname << std::endl;
        mtlname = defmtl;
      }
      else
      {
        std::cerr << "usemtl: " << mtlname << std::endl;
      }
    }
    else if (op == "mtllib")
    {
      // MTL ファイルのパス名を作る
      str >> std::ws;
      std::string mtlpath;
      std::getline(str, mtlpath);
      mtlpath = dirname + mtlpath;

      // MTL ファイルの読み込み
      std::ifstream mtlfile(mtlpath.c_str(), std::ios::binary);
      if (mtlfile.fail())
      {
        std::cerr << "Warning: Can't open MTL file: " << mtlpath << std::endl;
      }
      else
      {
        // 一行読み込み用のバッファ
        std::string mtlline;

        // マテリアルデータを読み込む
        while (std::getline(mtlfile, mtlline))
        {
          std::istringstream mtlstr(mtlline);
          std::string mtlop;
          mtlstr >> mtlop;

          if (mtlop == "newmtl")
          {
            // 新規マテリアル名を出力する
            mtlstr >> mtlname;
            std::cerr << "newmtl: " << mtlname << std::endl;
          }
          else if (mtlop == "Ka")
          {
            // 環境光の反射係数を登録する
            mtlstr >> mtl[mtlname].ka.r >> mtl[mtlname].ka.g >> mtl[mtlname].ka.b;
          }
          else if (mtlop == "Kd")
          {
            // 拡散反射係数を登録する
            mtlstr >> mtl[mtlname].kd.r >> mtl[mtlname].kd.g >> mtl[mtlname].kd.b;
          }
          else if (mtlop == "Ks")
          {
            // 鏡面反射係数を登録する
            mtlstr >> mtl[mtlname].ks.r >> mtl[mtlname].ks.g >> mtl[mtlname].ks.b;
          }
          else if (mtlop == "Ns")
          {
            // 輝き係数を登録する
            float kshi;
            mtlstr >> kshi;
            mtl[mtlname].kshi = kshi * 0.1f;
          }
        }

        // MTL ファイルの読み込みチェック
        if (mtlfile.bad())
        {
          // MTL ファイルをうまく読み込めなかった
          std::cerr << "Warning: Can't read MTL file: " << mtlpath << std::endl;
        }
        mtlfile.close();
      }
    }
  }

  // ファイルの読み込みチェック
  if (file.bad())
  {
    // OBJ ファイルをうまく読み込めなかった
    std::cerr << "Warning: Can't read OBJ file: " << path << std::endl;
  }
  else
  {
    // 最後の面グループの面数
    GLuint groupcount = static_cast<GLuint>(_face.size()) * 3 - groupbegin;
    if (groupcount > 0)
    {
      // 最後の面グループの頂点データの開始番号と数，およびそのマテリアルを記録する
      grp b(groupbegin, groupcount, mtl[mtlname]);
      _group.push_back(b);
    }
  }
  file.close();

  // 必要な面数，頂点数，グループ数
  GLuint nf = static_cast<GLuint>(_face.size());
  nv = nf * 3;
  ng = static_cast<GLuint>(_group.size());

  // メモリの確保
  group = 0;
  ka = kd = ks = 0;
  kshi = 0;
  vert = norm = 0;
  try
  {
    group = new GLuint[ng][2];
    ka = new GLfloat[ng][4];
    kd = new GLfloat[ng][4];
    ks = new GLfloat[ng][4];
    kshi = new GLfloat[ng];
    vert = new GLfloat[nv][3];
    norm = new GLfloat[nv][3];
  }
  catch (std::bad_alloc e)
  {
    delete[] group;
    delete[] ka;
    delete[] kd;
    delete[] ks;
    delete[] kshi;
    delete[] vert;
    delete[] norm;
    group = 0;
    ka = kd = ks = 0;
    kshi = 0;
    vert = norm = 0;
    return false;
  }

  // 位置と大きさを正規化するための係数
  GLfloat scale, cx, cy, cz;
  if (normalize)
  {
    float sx = xmax - xmin;
    float sy = ymax - ymin;
    float sz = zmax - zmin;
    scale = sx;
    if (sy > scale) scale = sy;
    if (sz > scale) scale = sz;
    scale = (scale != 0.0f) ? 2.0f / scale : 1.0f;
    cx = (xmax + xmin) * 0.5f;
    cy = (ymax + ymin) * 0.5f;
    cz = (zmax + zmin) * 0.5f;
  }
  else
  {
    scale = 1.0f;
    cx = cy = cz = 0.0f;
  }

  // 面法線の算出
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // 頂点座標番号
    GLuint v0 = f->v[0], v1 = f->v[1], v2 = f->v[2];

    // v1 - v0, v2 - v0 を求める
    GLfloat dx1 = _vert[v1].pos.x - _vert[v0].pos.x;
    GLfloat dy1 = _vert[v1].pos.y - _vert[v0].pos.y;
    GLfloat dz1 = _vert[v1].pos.z - _vert[v0].pos.z;
    GLfloat dx2 = _vert[v2].pos.x - _vert[v0].pos.x;
    GLfloat dy2 = _vert[v2].pos.y - _vert[v0].pos.y;
    GLfloat dz2 = _vert[v2].pos.z - _vert[v0].pos.z;

    // 外積により面法線を求める
    f->norm.x = dy1 * dz2 - dz1 * dy2;
    f->norm.y = dz1 * dx2 - dx1 * dz2;
    f->norm.z = dx1 * dy2 - dy1 * dx2;
  }

  // 頂点法線の値を 0 にしておく
  for (std::vector<vtx>::iterator v = _vert.begin(); v != _vert.end(); ++v)
  {
    v->norm.x = v->norm.y = v->norm.z = 0.0f;
  }

  // 頂点法線の算出
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // 頂点座標番号
    GLuint v0 = f->v[0], v1 = f->v[1], v2 = f->v[2];

    // 面法線
    GLfloat x = f->norm.x;
    GLfloat y = f->norm.y;
    GLfloat z = f->norm.z;

    // 面法線を頂点法線に積算する
    _vert[v0].norm.x += x;
    _vert[v0].norm.y += y;
    _vert[v0].norm.z += z;

    _vert[v1].norm.x += x;
    _vert[v1].norm.y += y;
    _vert[v1].norm.z += z;

    _vert[v2].norm.x += x;
    _vert[v2].norm.y += y;
    _vert[v2].norm.z += z;
  }

  // 頂点法線の正規化
  for (std::vector<vtx>::iterator v = _vert.begin(); v != _vert.end(); ++v)
  {
    // 頂点法線の長さ
    GLfloat a = sqrt(v->norm.x * v->norm.x + v->norm.y * v->norm.y + v->norm.z * v->norm.z);

    // 頂点法線を正規化する
    if (a != 0.0)
    {
      v->norm.x /= a;
      v->norm.y /= a;
      v->norm.z /= a;
    }
  }

  // 面ごとの頂点データの作成
  nv = 0;
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // 面法線
    GLfloat x = f->norm.x, y = f->norm.y, z = f->norm.z;

    // 面法線の長さ
    GLfloat a = sqrt(x * x + y * y + z * z);

    // 面法線の正規化
    if (a != 0.0)
    {
      x /= a;
      y /= a;
      z /= a;
    }

    // 三頂点のそれぞれについて
    for (int i = 0; i < 3; ++i)
    {
      // 頂点座標番号と頂点法線番号
      GLuint fv = f->v[i], fn = f->n[i];

      // 頂点座標を正規化して登録
      vert[nv][0] = (_vert[fv].pos.x - cx) * scale;
      vert[nv][1] = (_vert[fv].pos.y - cy) * scale;
      vert[nv][2] = (_vert[fv].pos.z - cz) * scale;

      // 法線番号が 0 なら
      if (fn == 0)
      {
        // 頂点法線を保存する
        norm[nv][0] = _vert[fv].norm.x;
        norm[nv][1] = _vert[fv].norm.y;
        norm[nv][2] = _vert[fv].norm.z;
      }
      else
      {
        // 読み込まれた頂点法線を使う
        --fn;
        norm[nv][0] = _norm[fn].x;
        norm[nv][1] = _norm[fn].y;
        norm[nv][2] = _norm[fn].z;
      }

      // 頂点数のカウント
      ++nv;
    }
  }

  // 面グループデータの作成
  ng = 0;
  for (std::vector<grp>::iterator g = _group.begin(); g != _group.end(); ++g)
  {
    // 面グループの最初の頂点位置番号
    group[ng][0] = g->b;

    // 面グループの頂点データの数
    group[ng][1] = g->c;

    // 面グループの環境光に対する反射係数
    ka[ng][0] = g->m->ka.r;
    ka[ng][1] = g->m->ka.g;
    ka[ng][2] = g->m->ka.b;
    ka[ng][3] = 1.0f;

    // 面グループの拡散反射係数
    kd[ng][0] = g->m->kd.r;
    kd[ng][1] = g->m->kd.g;
    kd[ng][2] = g->m->kd.b;
    kd[ng][3] = 1.0f;

    // 面グループの鏡面反射係数
    ks[ng][0] = g->m->ks.r;
    ks[ng][1] = g->m->ks.g;
    ks[ng][2] = g->m->ks.b;
    ks[ng][3] = 1.0f;

    // 面グループの輝き係数
    kshi[ng] = g->m->kshi;

    // 面グループの数
    ++ng;
  }

  return true;
}

/*
** シェーダーのソースプログラムをメモリに読み込む
*/
static bool readShaderSource(GLuint shader, const char *name)
{
  bool ret = true; // 終了ステータス（true ならエラー）

  // ソースファイルを開く
  std::ifstream file(name, std::ios::binary);

  if (file.fail())
  {
    // 開けなかった
    std::cerr << "Error: Can't open source file: " << name << std::endl;
  }
  else
  {
    // ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // ファイルサイズのメモリを確保
    char *buffer = new GLchar[length];

    // ファイルを先頭から読み込む
    file.seekg(0L, std::ios::beg);
    file.read(buffer, length);

    if (file.bad())
    {
      // うまく読み込めなかった
      std::cerr << "Error: Could not read souce file: " << name << std::endl;
    }
    else {
      // シェーダのソースプログラムのシェーダオブジェクトへの読み込み
      const GLchar *source[] = { buffer };
      glShaderSource(shader, 1, source, &length);
      ret = false;
    }
    file.close();

    // 読み込みに使ったメモリを開放する
    delete[] buffer;
  }

  return ret;
}

/*
** シェーダオブジェクトのコンパイル結果を表示する
*/
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

/*
** プログラムオブジェクトのリンク結果を表示する
*/
static GLboolean printProgramInfoLog(GLuint program)
{
  // リンク結果を取得する
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

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

/*
** シェーダーソースファイルの読み込み
*/
GLuint gg::ggLoadShader(
  const char *vert,       // バーテックスシェーダのソースファイル名
  const char *frag,       // フラグメントシェーダのソースファイル名
  const char *geom,       // ジオメトリシェーダのソースファイル名
  GLint nvarying,         // Transform Feedback する varying 変数の数
  const char **varyings   // Transform Feedback する varying 変数のリスト
  )
{
  // シェーダプログラムの作成
  GLuint program = glCreateProgram();

  if (program > 0)
  {
    // バーテックスシェーダの作成
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

    // バーテックスシェーダのソースプログラムの読み込み
    if (readShaderSource(vertShader, vert))
    {
      glDeleteShader(vertShader);
      glDeleteProgram(program);
      return 0;
    }

    // バーテックスシェーダのコンパイル
    glCompileShader(vertShader);
    if (printShaderInfoLog(vertShader, vert) == GL_FALSE)
    {
      glDeleteShader(vertShader);
      glDeleteProgram(program);
      return 0;
    }

    // バーテックスシェーダシェーダプログラムへの組み込み
    glAttachShader(program, vertShader);
    glDeleteShader(vertShader);

    if (frag)
    {
      // フラグメントシェーダの作成
      GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

      // フラグメントシェーダのソースプログラムの読み込み
      if (readShaderSource(fragShader, frag))
      {
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return 0;
      }

      // フラグメントシェーダのコンパイル
      glCompileShader(fragShader);
      if (printShaderInfoLog(fragShader, frag) == GL_FALSE)
      {
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return 0;
      }

      // フラグメントシェーダシェーダプログラムへの組み込み
      glAttachShader(program, fragShader);
      glDeleteShader(fragShader);
    }

    if (geom)
    {
      // ジオメトリシェーダの作成
      GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);

      // ジオメトリシェーダのソースプログラムの読み込み
      if (readShaderSource(geomShader, geom))
      {
        glDeleteShader(geomShader);
        glDeleteProgram(program);
        return 0;
      }

      // ジオメトリシェーダのコンパイル
      glCompileShader(geomShader);
      if (printShaderInfoLog(geomShader, geom) == GL_FALSE)
      {
        glDeleteShader(geomShader);
        glDeleteProgram(program);
        return 0;
      }

      // ジオメトリシェーダのシェーダプログラムへの組み込み
      glAttachShader(program, geomShader);
      glDeleteShader(geomShader);
    }

    // feedback に使う varying 変数を指定する
    if (nvarying > 0) glTransformFeedbackVaryings(program, nvarying, varyings, GL_SEPARATE_ATTRIBS);

    // シェーダプログラムのリンク
    glLinkProgram(program);
    if (printProgramInfoLog(program) == GL_FALSE)
    {
      glDeleteProgram(program);
      return 0;
    }
  }

  return program;
}

/*
** 変換行列：行列とベクトルの積 c ← a × b
*/
void gg::GgMatrix::projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const
{
  for (int i = 0; i < 4; ++i)
  {
    c[i] = a[0 + i] * b[0] + a[4 + i] * b[1] + a[8 + i] * b[2] + a[12 + i] * b[3];
  }
}

/*
** 変換行列：行列と行列の積 c ← a × b
*/
void gg::GgMatrix::multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const
{
  for (int i = 0; i < 16; ++i)
  {
    int j = i & 3, k = i & ~3;

    c[i] = a[0 + j] * b[k + 0] + a[4 + j] * b[k + 1] + a[8 + j] * b[k + 2] + a[12 + j] * b[k + 3];
  }
}

/*
** 変換行列：単位行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadIdentity(void)
{
  array[ 1] = array[ 2] = array[ 3] = array[ 4] =
  array[ 6] = array[ 7] = array[ 8] = array[ 9] =
  array[11] = array[12] = array[13] = array[14] = 0.0f;
  array[ 0] = array[ 5] = array[10] = array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：平行移動変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  array[12] = x;
  array[13] = y;
  array[14] = z;
  array[ 0] = array[ 5] = array[10] = array[15] = w;
  array[ 1] = array[ 2] = array[ 3] = array[ 4] =
  array[ 6] = array[ 7] = array[ 8] = array[ 9] =
  array[11] = 0.0f;

  return *this;
}

/*
** 変換行列：拡大縮小変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  array[ 0] = x;
  array[ 5] = y;
  array[10] = z;
  array[15] = w;
  array[ 1] = array[ 2] = array[ 3] = array[ 4] =
  array[ 6] = array[ 7] = array[ 8] = array[ 9] =
  array[11] = array[12] = array[13] = array[14] = 0.0f;

  return *this;
}

/*
** 変換行列：x 軸中心の回転変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadRotateX(GLfloat a)
{
  GLfloat c = cos(a);
  GLfloat s = sin(a);

  array[ 0] = 1.0f; array[ 1] = 0.0f; array[ 2] = 0.0f; array[ 3] = 0.0f;
  array[ 4] = 0.0f; array[ 5] = c;    array[ 6] = s;    array[ 7] = 0.0f;
  array[ 8] = 0.0f; array[ 9] = -s;   array[10] = c;    array[11] = 0.0f;
  array[12] = 0.0f; array[13] = 0.0f; array[14] = 0.0f; array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：y 軸中心の回転変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadRotateY(GLfloat a)
{
  GLfloat c = cos(a);
  GLfloat s = sin(a);

  array[ 0] = c;    array[ 1] = 0.0f; array[ 2] = -s;   array[ 3] = 0.0f;
  array[ 4] = 0.0f; array[ 5] = 1.0f; array[ 6] = 0.0f; array[ 7] = 0.0f;
  array[ 8] = s;    array[ 9] = 0.0f; array[10] = c;    array[11] = 0.0f;
  array[12] = 0.0f; array[13] = 0.0f; array[14] = 0.0f; array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：z 軸中心の回転変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadRotateZ(GLfloat a)
{
  GLfloat c = cos(a);
  GLfloat s = sin(a);

  array[ 0] = c;    array[ 1] = s;    array[ 2] = 0.0f; array[ 3] = 0.0f;
  array[ 4] = -s;   array[ 5] = c;    array[ 6] = 0.0f; array[ 7] = 0.0f;
  array[ 8] = 0.0f; array[ 9] = 0.0f; array[10] = 1.0f; array[11] = 0.0f;
  array[12] = 0.0f; array[13] = 0.0f; array[14] = 0.0f; array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：任意軸中心の回転変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
  GLfloat d = sqrt(x * x + y * y + z * z);

  if (d > 0.0f)
  {
    GLfloat l  = x / d, m  = y / d, n  = z / d;
    GLfloat l2 = l * l, m2 = m * m, n2 = n * n;
    GLfloat lm = l * m, mn = m * n, nl = n * l;
    GLfloat c = cos(a), c1 = 1.0f - c;
    GLfloat s = sin(a);

    array[ 0] = (1.0f - l2) * c + l2;
    array[ 1] = lm * c1 + n * s;
    array[ 2] = nl * c1 - m * s;
    array[ 3] = 0.0f;

    array[ 4] = lm * c1 - n * s;
    array[ 5] = (1.0f - m2) * c + m2;
    array[ 6] = mn * c1 + l * s;
    array[ 7] = 0.0f;

    array[ 8] = nl * c1 + m * s;
    array[ 9] = mn * c1 - l * s;
    array[10] = (1.0f - n2) * c + n2;
    array[11] = 0.0f;

    array[12] = 0.0f;
    array[13] = 0.0f;
    array[14] = 0.0f;
    array[15] = 1.0f;
  }

  return *this;
}

/*
** 変換行列：転置行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadTranspose(const GgMatrix &m)
{
  array[ 0] = m.array[ 0];
  array[ 1] = m.array[ 4];
  array[ 2] = m.array[ 8];
  array[ 3] = m.array[12];
  array[ 4] = m.array[ 1];
  array[ 5] = m.array[ 5];
  array[ 6] = m.array[ 9];
  array[ 7] = m.array[13];
  array[ 8] = m.array[ 2];
  array[ 9] = m.array[ 6];
  array[10] = m.array[10];
  array[11] = m.array[14];
  array[12] = m.array[ 3];
  array[13] = m.array[ 7];
  array[14] = m.array[11];
  array[15] = m.array[15];

  return *this;
}

/*
** 変換行列：逆行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadInvert(const GgMatrix &m)
{
  GLfloat lu[20], *plu[4];
  const GLfloat *marray = m.array;

  // j 行の要素の値の絶対値の最大値を plu[j][4] に求める
  for (int j = 0; j < 4; ++j)
  {
    GLfloat max = fabs(*(plu[j] = lu + 5 * j) = *(marray++));

    for (int i = 0; ++i < 4;)
    {
      GLfloat a = fabs(plu[j][i] = *(marray++));
      if (a > max) max = a;
    }
    if (max == 0.0f) return *this;
    plu[j][4] = 1.0f / max;
  }

  // ピボットを考慮した LU 分解
  for (int j = 0; j < 4; ++j)
  {
    GLfloat max = fabs(plu[j][j] * plu[j][4]);
    int i = j;

    for (int k = j; ++k < 4;)
    {
      GLfloat a = fabs(plu[k][j] * plu[k][4]);
      if (a > max)
      {
        max = a;
        i = k;
      }
    }
    if (i > j)
    {
      GLfloat *t = plu[j];
      plu[j] = plu[i];
      plu[i] = t;
    }
    if (plu[j][j] == 0.0f) return *this;
    for (int k = j; ++k < 4;)
    {
      plu[k][j] /= plu[j][j];
      for (int i = j; ++i < 4;)
      {
        plu[k][i] -= plu[j][i] * plu[k][j];
      }
    }
  }

  // LU 分解から逆行列を求める
  for (int k = 0; k < 4; ++k)
  {
    // array に単位行列を設定する
    for (int i = 0; i < 4; ++i)
    {
      array[i * 4 + k] = (plu[i] == lu + k * 5) ? 1.0f : 0.0f;
    }
    // lu から逆行列を求める
    for (int i = 0; i < 4; ++i)
    {
      for (int j = i; ++j < 4;)
      {
        array[j * 4 + k] -= array[i * 4 + k] * plu[j][i];
      }
    }
    for (int i = 4; --i >= 0;)
    {
      for (int j = i; ++j < 4;)
      {
        array[i * 4 + k] -= plu[i][j] * array[j * 4 + k];
      }
      array[i * 4 + k] /= plu[i][i];
    }
  }

  return *this;
}

/*
** 変換行列：法線変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadNormal(const GgMatrix &m)
{
  array[ 0] = m.array[ 5] * m.array[10] - m.array[ 6] * m.array[ 9];
  array[ 1] = m.array[ 6] * m.array[ 8] - m.array[ 4] * m.array[10];
  array[ 2] = m.array[ 4] * m.array[ 9] - m.array[ 5] * m.array[ 8];
  array[ 4] = m.array[ 9] * m.array[ 2] - m.array[10] * m.array[ 1];
  array[ 5] = m.array[10] * m.array[ 0] - m.array[ 8] * m.array[ 2];
  array[ 6] = m.array[ 8] * m.array[ 1] - m.array[ 9] * m.array[ 0];
  array[ 8] = m.array[ 1] * m.array[ 6] - m.array[ 2] * m.array[ 5];
  array[ 9] = m.array[ 2] * m.array[ 4] - m.array[ 0] * m.array[ 6];
  array[10] = m.array[ 0] * m.array[ 5] - m.array[ 1] * m.array[ 4];
  array[ 3] = array[ 7] = array[11] = array[12] = array[13] = array[14] = 0.0f;
  array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：視野変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz)
{
  GLfloat l;

  // z 軸 = e - t
  tx = ex - tx;
  ty = ey - ty;
  tz = ez - tz;
  l = sqrt(tx * tx + ty * ty + tz * tz);
  if (l == 0.0f) return *this;
  array[ 2] = tx / l;
  array[ 6] = ty / l;
  array[10] = tz / l;

  // x 軸 = u x z 軸
  tx = uy * array[10] - uz * array[ 6];
  ty = uz * array[ 2] - ux * array[10];
  tz = ux * array[ 6] - uy * array[ 2];
  l = sqrt(tx * tx + ty * ty + tz * tz);
  if (l == 0.0f) return *this;
  array[ 0] = tx / l;
  array[ 4] = ty / l;
  array[ 8] = tz / l;

  // y 軸 = z 軸 x x 軸
  array[ 1] = array[ 6] * array[ 8] - array[10] * array[ 4];
  array[ 5] = array[10] * array[ 0] - array[ 2] * array[ 8];
  array[ 9] = array[ 2] * array[ 4] - array[ 6] * array[ 0];

  // 平行移動
  array[12] = -(ex * array[ 0] + ey * array[ 4] + ez * array[ 8]);
  array[13] = -(ex * array[ 1] + ey * array[ 5] + ez * array[ 9]);
  array[14] = -(ex * array[ 2] + ey * array[ 6] + ez * array[10]);

  // 残り
  array[ 3] = array[ 7] = array[11] = 0.0f;
  array[15] = 1.0f;

  return *this;
}

/*
** 変換行列：平行投影変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GLfloat dx = right - left;
  GLfloat dy = top - bottom;
  GLfloat dz = zFar - zNear;

  if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
  {
    array[ 0] =  2.0f / dx;
    array[ 5] =  2.0f / dy;
    array[10] = -2.0f / dz;
    array[12] = -(right + left) / dx;
    array[13] = -(top + bottom) / dy;
    array[14] = -(zFar + zNear) / dz;
    array[15] =  1.0f;
    array[ 1] = array[ 2] = array[ 3] = array[ 4] =
    array[ 6] = array[ 7] = array[ 8] = array[ 9] = array[11] = 0.0f;
  }

  return *this;
}

/*
** 変換行列：透視投影変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GLfloat dx = right - left;
  GLfloat dy = top - bottom;
  GLfloat dz = zFar - zNear;

  if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
  {
    array[ 0] =  2.0f * zNear / dx;
    array[ 5] =  2.0f * zNear / dy;
    array[ 8] =  (right + left) / dx;
    array[ 9] =  (top + bottom) / dy;
    array[10] = -(zFar + zNear) / dz;
    array[11] = -1.0f;
    array[14] = -2.0f * zFar * zNear / dz;
    array[ 1] = array[ 2] = array[ 3] = array[ 4] =
    array[ 6] = array[ 7] = array[12] = array[13] = array[15] = 0.0f;
  }

  return *this;
}

/*
** 変換行列：画角から透視投影変換行列を設定する
*/
gg::GgMatrix &gg::GgMatrix::loadPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
  GLfloat dz = zFar - zNear;

  if (dz != 0.0f)
  {
    GLfloat f = 1.0f / tan(fovy * 0.5f);

    array[ 0] = f / aspect;
    array[ 5] = f;
    array[10] = -(zFar + zNear) / dz;
    array[11] = -1.0f;
    array[14] = -2.0f * zFar * zNear / dz;
    array[ 1] = array[ 2] = array[ 3] = array[ 4] =
    array[ 6] = array[ 7] = array[ 8] = array[ 9] =
    array[12] = array[13] = array[15] = 0.0f;
  }

  return *this;
}

/*
** 変換行列：視野変換行列を乗じる（視点の移動）
*/
gg::GgMatrix &gg::GgMatrix::lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz)
{
  GgMatrix m;

  m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz);
  multiply(m);

  return *this;
}

/*
** 変換行列：平行投影変換行列を乗じる
*/
gg::GgMatrix &gg::GgMatrix::orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadOrthogonal(left, right, bottom, top, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** 変換行列：透視投影変換行列を乗じる
*/
gg::GgMatrix &gg::GgMatrix::frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadFrustum(left, right, bottom, top, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** 変換行列：画角から求めた透視投影変換行列を乗じる
*/
gg::GgMatrix &gg::GgMatrix::perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadPerspective(fovy, aspect, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** 四元数：四元数 p, q の和を r に求める
*/
void gg::GgQuaternion::add(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[0] + q[0];
  r[1] = p[1] + q[1];
  r[2] = p[2] + q[2];
  r[3] = p[3] + q[3];
}

/*
** 四元数：四元数 p, q の差を r に求める
*/
void gg::GgQuaternion::subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[0] - q[0];
  r[1] = p[1] - q[1];
  r[2] = p[2] - q[2];
  r[3] = p[3] - q[3];
}

/*
** 四元数：四元数 p, q の積を r に求める
*/
void gg::GgQuaternion::multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[1] * q[2] - p[2] * q[1] + p[0] * q[3] + p[3] * q[0];
  r[1] = p[2] * q[0] - p[0] * q[2] + p[1] * q[3] + p[3] * q[1];
  r[2] = p[0] * q[1] - p[1] * q[0] + p[2] * q[3] + p[3] * q[2];
  r[3] = p[3] * q[3] - p[0] * q[0] - p[1] * q[1] - p[2] * q[2];
}

/*
** 四元数：四元数 q が表す変換行列を m に求める
*/
void gg::GgQuaternion::toMatrix(GLfloat *m, const GLfloat *q) const
{
  GLfloat xx = q[0] * q[0] * 2.0f;
  GLfloat yy = q[1] * q[1] * 2.0f;
  GLfloat zz = q[2] * q[2] * 2.0f;
  GLfloat xy = q[0] * q[1] * 2.0f;
  GLfloat yz = q[1] * q[2] * 2.0f;
  GLfloat zx = q[2] * q[0] * 2.0f;
  GLfloat xw = q[0] * q[3] * 2.0f;
  GLfloat yw = q[1] * q[3] * 2.0f;
  GLfloat zw = q[2] * q[3] * 2.0f;

  m[ 0] = 1.0f - yy - zz;
  m[ 1] = xy + zw;
  m[ 2] = zx - yw;
  m[ 4] = xy - zw;
  m[ 5] = 1.0f - zz - xx;
  m[ 6] = yz + xw;
  m[ 8] = zx + yw;
  m[ 9] = yz - xw;
  m[10] = 1.0f - xx - yy;
  m[ 3] = m[ 7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
  m[15] = 1.0f;
}

/*
** 四元数：回転変換行列 m が表す四元数を q に求める
*/
void gg::GgQuaternion::toQuaternion(GLfloat *q, const GLfloat *m) const
{
  GLfloat tr = m[0] + m[5] + m[10] + m[15];

  if (tr > 0.0f)
  {
    q[3] = sqrt(tr) * 0.5f;
    q[0] = (m[6] - m[9]) * 0.25f / q[3];
    q[1] = (m[8] - m[2]) * 0.25f / q[3];
    q[2] = (m[1] - m[4]) * 0.25f / q[3];
  }
}

/*
** 四元数：球面線形補間 p に q と r を t で補間した四元数を求める
*/
void gg::GgQuaternion::slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const
{
  GLfloat qr = q[0] * r[0] + q[1] * r[1] + q[2] * r[2] + q[3] * r[3];
  GLfloat ss = 1.0f - qr * qr;

  if (ss == 0.0f)
  {
    if (p != q)
    {
      p[0] = q[0];
      p[1] = q[1];
      p[2] = q[2];
      p[3] = q[3];
    }
  }
  else
  {
    GLfloat sp = sqrt(ss);
    GLfloat ph = acos(qr);
    GLfloat pt = ph * t;
    GLfloat t1 = sin(pt) / sp;
    GLfloat t0 = sin(ph - pt) / sp;

    p[0] = q[0] * t0 + r[0] * t1;
    p[1] = q[1] * t0 + r[1] * t1;
    p[2] = q[2] * t0 + r[2] * t1;
    p[3] = q[3] * t0 + r[3] * t1;
  }
}

/*
** 四元数：(x, y, z) を軸とし角度 a 回転する四元数を求める
*/
gg::GgQuaternion &gg::GgQuaternion::loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
  GLfloat l = x * x + y * y + z * z;

  if (l != 0.0)
  {
    GLfloat s = sin(a *= 0.5f) / sqrt(l);

    array[0] = x * s;
    array[1] = y * s;
    array[2] = z * s;
  }
  else
  {
    array[0] = array[1] = array[2] = 0.0f;
  }
  array[3] = cos(a);

  return *this;
}

/*
** 四元数：オイラー角 (h, p, r) にもとづいて四元数を求める
*/
gg::GgQuaternion &gg::GgQuaternion::loadEuler(GLfloat h, GLfloat p, GLfloat r)
{
  return loadRotate(-sin(h) * cos(p), sin(p), cos(h) * cos(p), r);
}

/*
** 四元数：ノルム
*/
GLfloat gg::GgQuaternion::norm(void) const
{
  return sqrt(array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3]);
}

/*
** 四元数：四元数 q の共役を r に求める
*/
gg::GgQuaternion gg::GgQuaternion::conjugate(void) const
{
  GgQuaternion t(-array[0], -array[1], -array[2], array[3]);

  return t;
}

/*
** 四元数：四元数 q の逆を r に求める
*/
gg::GgQuaternion gg::GgQuaternion::invert(void) const
{
  GgQuaternion t = conjugate();
  GLfloat l = array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3];

  if (l > 0.0f)
  {
    t.array[0] /= l;
    t.array[1] /= l;
    t.array[2] /= l;
    t.array[3] /= l;
  }

  return t;
}

/*
** 四元数：正規化
*/
gg::GgQuaternion gg::GgQuaternion::normalize(void) const
{
  GgQuaternion t = *this;
  GLfloat l = norm();

  if (l > 0.0f)
  {
    t.array[0] /= l;
    t.array[1] /= l;
    t.array[2] /= l;
    t.array[3] /= l;
  }

  return t;
}

/*
** 簡易トラックボール処理：コンストラクタ
*/
gg::GgTrackball::GgTrackball(void)
{
  // ドラッグ中ではない
  drag = false;

  // 単位クォーターニオン
  cq.loadIdentity();

  // 回転行列の初期化
  cq.getMatrix(rt);
}

/*
** 簡易トラックボール処理：トラックボールする領域の設定
**
**    Reshape コールバック (resize) の中で実行する
**    (w, h): ウィンドウサイズ
*/
void gg::GgTrackball::region(int w, int h)
{
  // マウスポインタ位置のウィンドウ内の相対的位置への換算用
  sx = 1.0f / static_cast<float>(w);
  sy = 1.0f / static_cast<float>(h);
}

/*
** 簡易トラックボール処理：ドラッグ開始時の処理
**
**    マウスボタンを押したときに実行する
**    (x, y): 現在のマウス位置
*/
void gg::GgTrackball::start(int x, int y)
{
  // ドラッグ開始
  drag = true;

  // ドラッグ開始点を記録する
  cx = x;
  cy = y;
}

/*
** 簡易トラックボール処理：ドラッグ中の処理
**
**    マウスのドラッグ中に実行する
**    (x, y): 現在のマウス位置
*/
void gg::GgTrackball::motion(int x, int y)
{
  if (drag)
  {
    float dx, dy, a;

    // マウスポインタの位置のドラッグ開始位置からの変位
    dx = (x - cx) * sx;
    dy = (y - cy) * sy;

    // マウスポインタの位置のドラッグ開始位置からの距離
    a = sqrt(dx * dx + dy * dy);

    if (a != 0.0)
    {
      // 回転軸と回転角から四元数を作る
      GgQuaternion dq;
      dq.loadRotate(dy, dx, 0.0f, a * 6.283185f);

      // 現在の回転の四元数に作った四元数を掛けて合成する
      tq = dq * cq;

      // 合成した四元数から回転の変換行列を求める
      tq.getMatrix(rt);
    }
  }
}

/*
** 簡易トラックボール処理：停止時の処理
**
**    マウスボタンを離したときに実行する
**    (x, y): 現在のマウス位置
*/
void gg::GgTrackball::stop(int x, int y)
{
  // ドラッグ終了点における回転を求める
  motion(x, y);

  // 現在の回転を表す四元数を正規化して保存する
  cq = tq.normalize();

  // ドラッグ終了
  drag = false;
}

/*
** ポイント：描画
*/
void gg::GgPoints::draw(void) const
{
  // シェーダプログラムの使用を開始する
  getShader()->use(pbuf());

  // 図形を描画する
  glDrawArrays(mode, 0, pnum());

  // シェーダプログラムの使用を終了する
  getShader()->unuse();
}

/*
** ポリゴン：描画
*/
void gg::GgTriangles::draw(void) const
{
  // シェーダプログラムの使用を開始する
  getShader()->use(pbuf(), nbuf());

  // 図形を描画する
  glDrawArrays(mode, 0, pnum());

  // シェーダプログラムの使用を終了する
  getShader()->unuse();
}

/*
** オブジェクト：描画
*/
void gg::GgElements::draw(void) const
{
  // シェーダプログラムの使用を開始する
  getShader()->use(pbuf(), nbuf());

  // インデックスにバッファオブジェクトを指定する
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fbuf());

  // 図形を描画する
  glDrawElements(mode, fnum() * 3, GL_UNSIGNED_INT, 0);

  // バッファオブジェクトの指定を解除する
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // シェーダプログラムの使用を終了する
  getShader()->unuse();
}

/*
** 球状のポイント
*/
gg::GgPoints *gg::ggPointSphere(GLuint nv, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat radius)
{
  // メモリの確保
  GLfloat (*vert)[3] = new GLfloat[nv][3];

  // 点の生成
  for (GLuint v = 0; v < nv; ++v)
  {
    float r = radius * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float t = 6.2831853f * static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
    float cp = 2.0f * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0f;
    float sp = sqrt(1.0f - cp * cp);
    float ct = cos(t), st = sin(t);

    vert[v][0] = r * sp * ct + cx;
    vert[v][1] = r * sp * st + cy;
    vert[v][2] = r * cp + cz;
  }

  // ポイントの作成
  GgPoints *points = new gg::GgPoints(nv, vert);

  // 作業用のメモリの解放
  delete[] vert;

  return points;
}

/*
** 矩形
*/
gg::GgTriangles *gg::ggRectangle(GLfloat width, GLfloat height)
{
  // 基準となる形状
  static const GLfloat p[][2] =
  {
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f },
  };

  // メモリの確保
  GLfloat vert[4][3];
  GLfloat norm[4][3];

  // 頂点位置の計算
  for (int v = 0; v < 4; ++v)
  {
    vert[v][0] = p[v][0] * width;
    vert[v][1] = p[v][1] * height;
    vert[v][2] = 0.0f;

    norm[v][0] = 0.0f;
    norm[v][1] = 0.0f;
    norm[v][2] = 1.0f;
  }

  // ポリゴンの作成
  GgTriangles *rectangle = new gg::GgTriangles(4, vert, norm);
  rectangle->setMode(GL_TRIANGLE_FAN);

  return rectangle;
}

/*
** 楕円
*/
gg::GgTriangles *gg::ggEllipse(GLfloat width, GLfloat height, GLuint slices)
{
  // メモリの確保
  GLfloat (*vert)[3] = 0;
  GLfloat (*norm)[3] = 0;
  try
  {
    vert = new GLfloat[slices][3];
    norm = new GLfloat[slices][3];
  }
  catch (std::bad_alloc e)
  {
    delete[] vert;
    delete[] norm;
    throw e;
  }

  // 頂点位置の計算
  for (GLuint v = 0; v < slices; ++v)
  {
    float t = 6.2831853f * static_cast<float>(v) / static_cast<float>(slices);

    vert[v][0] = cos(t) * width * 0.5f;
    vert[v][1] = sin(t) * height * 0.5f;
    vert[v][2] = 0.0f;

    norm[v][0] = 0.0f;
    norm[v][1] = 0.0f;
    norm[v][2] = 1.0f;
  } 

  // ポリゴンの作成
  GgTriangles *ellipse = new gg::GgTriangles(slices, vert, norm);
  ellipse->setMode(GL_TRIANGLE_FAN);

  // 作業用のメモリの解放
  delete[] vert;
  delete[] norm;

  return ellipse;
}

/*
** 三角形分割された Alias OBJ ファイル (Arrays 形式)
*/
gg::GgTriangles *gg::ggArraysObj(const char *name, bool normalize)
{
  GLuint ng, nv;
  GLuint (*group)[2];
  GLfloat (*ka)[4], (*kd)[4], (*ks)[4], *kshi;
  GLfloat (*vert)[3], (*norm)[3];

  if (!ggLoadObj(name, ng, group, ka, kd, ks, kshi, nv, vert, norm, normalize)) return 0;

  // オブジェクトの作成
  GgTriangles *obj = new gg::GgTriangles(nv, vert, norm);

  // 作業用のメモリの解放
  delete[] group;
  delete[] ka;
  delete[] kd;
  delete[] ks;
  delete[] kshi;
  delete[] vert;
  delete[] norm;

  return obj;
}

/*
** 三角形分割された Alias OBJ ファイル (Elements 形式)
*/
gg::GgElements *gg::ggElementsObj(const char *name, bool normalize)
{
  GLuint nv, nf;
  GLfloat (*vert)[3], (*norm)[3];
  GLuint (*face)[3];

  if (!ggLoadObj(name, nv, vert, norm, nf, face, normalize)) return 0;

  // オブジェクトの作成
  GgElements *obj = new gg::GgElements(nv, vert, norm, nf, face);

  // 作業用のメモリの解放
  delete[] vert;
  delete[] norm;
  delete[] face;

  return obj;
}
