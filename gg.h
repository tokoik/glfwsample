/*
** ゲームグラフィックス特論用補助プログラム GLFW 版
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

#ifndef __GG_H__
#define __GG_H__

#include <cstring>

#define GLFW_NO_GLU
#if defined(WIN32)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  pragma warning(disable:4996)
#  pragma comment(lib, "OpenGL32.lib")
#  pragma comment(lib, "glew32.lib")
#  pragma comment(lib, "GLFW.lib")
#  include "glew.h"
#  include "wglew.h"
#  include "glfw.h"
#elif defined(__APPLE__)
#  define GLFW_INCLUDE_GL3
#  include <GL/glfw.h>
#  include <OpenGL/glext.h>
#  include <OpenGL/gl3ext.h>
#else
#  define GL_GLEXT_PROTOTYPES
#  include <GL/glfw.h>
#  include <GL/glext.h>
#endif

namespace gg
{
  /*
  ** ゲームグラフィックス特論の都合にもとづく初期化
  **
  **     OpenGL のレンダリングコンテキスト作成後に実行する
  */
  extern void ggInit(void);

  /*
  ** OpenGL のエラーチェック
  **
  **     OpenGL の API を呼び出し直後に実行すればエラーのあるときにメッセージを表示する
  */
  extern void ggError(
    const char *msg = 0                 // 出力するメッセージの先頭に追加する文字列
    );

  /*
  ** FBO のエラーチェック
  **
  **     FBO の API を呼び出し直後に実行すればエラーのあるときにメッセージを表示する
  */
  extern void ggFBOError(
    const char *msg = 0                 // 出力するメッセージの先頭に追加する文字列
    );

  /*
  ** シェーダーソースファイルの読み込み
  */
  extern GLuint ggLoadShader(           // シェーダプログラムのプログラム名
    const char *vert,                   // バーテックスシェーダのソースファイル名
    const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
    const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
    int nvarying = 0,                   // フィードバックする varying 変数の数（0 なら不使用）
    const char **varyings = 0           // フィードバックする varying 変数のリスト
    );

  /*
  ** 配列の内容を TGA ファイルに保存
  */
  bool ggSaveTga(                       // 保存できたら true
    GLsizei sx,                         // 配列の行方向の大きさ
    GLsizei sy,                         // 配列の列方向の大きさ
    unsigned int depth,                 // 配列の要素のバイト数
    const GLubyte *buffer,              // 保存する配列
    const char *name                    // 保存するファイル名
    );

  /*
  ** カラーバッファの内容を TGA ファイルに保存
  */
  extern bool ggSaveColor(              // 保存できたら true
    const char *name                    // 保存するファイル名
    );

  /*
  ** デプスバッファの内容を TGA ファイルに保存
  */
  extern bool ggSaveDepth(              // 保存できたら true
    const char *name                    // 保存するファイル名
    );

  /*
  ** TGA ファイル (8/16/24/32bit) の読み込み
  */
  extern GLubyte *ggLoadTga(            // 読み込んだ画像データのポインタを返す (使用後 delete する)
    const char *name,                   // 読み込むファイル名
    GLsizei &width,                     // 読み込んだ TGA ファイルの幅
    GLsizei &height,                    // 読み込んだ TGA ファイルの高さ
    GLenum &format                      // 読み込んだ TGA ファイルの書式 (GL_R, GL_RG, GL_BGR, GL_BGRA)
    );

  /*
  ** テクスチャメモリの確保
  */
  extern void ggLoadTexture(
    GLsizei width,                      // 確保するテクスチャメモリの幅
    GLsizei height,                     // 確保するテクスチャメモリの高さ
    GLenum internal,                    // 確保するテクスチャメモリの内部書式
    GLenum format = GL_RGBA,            // image の書式
    const GLvoid *image = 0
    );

  /*
  ** TGA ファイルをテクスチャメモリに読み込む
  */
  extern bool ggLoadImage(              // 読み込みできたら true
    const char *name,                   // 読み込むファイル名
    GLenum internal                     // テクスチャメモリの内部フォーマット
    );

  /*
  ** TGA 画像ファイルの高さマップ読み込んでテクスチャメモリに法線マップを作成する
  */
  extern bool ggLoadHeight(             // 読み込みできたら true
    const char *name,                   // 読み込むファイル名
    float nz                            // 法線の z 軸の長さ
    );

  /*
  ** 三角形分割された OBJ ファイルを読み込む (Elements 形式)
  */
  extern bool ggLoadObj(                // 読み込みできたら true
    const char *name,                   // 読み込むファイル名
    GLuint &nv,                         // 読み込んだデータの頂点数
    GLfloat (*&vert)[3],                // 読み込んだデータの頂点位置
    GLfloat (*&norm)[3],                // 読み込んだデータの頂点法線
    GLuint &nf,                         // 読み込んだデータの三角形数
    GLuint (*&face)[3],                 // 読み込んだデータの三角形の頂点インデックス
    bool normalize                      // true なら読み込んだデータの大きさを正規化する
    );

  /*
  ** 三角形分割された OBJ ファイルと MTL ファイルを読み込む (Arrays 形式)
  */
  extern bool ggLoadObj(                // 読み込みできたら true
    const char *name,                   // 読み込むファイル名
    GLuint &ng,                         // 読み込んだデータのポリゴングループ数
    GLuint (*&group)[2],                // 読み込んだデータのポリゴングループの最初のポリゴンのインデックスとポリゴン数
    GLfloat (*&ka)[4],                  // 読み込んだっデータのポリゴングループごとの環境光に対する反射係数
    GLfloat (*&kd)[4],                  // 読み込んだっデータのポリゴングループごとの拡散反射係数
    GLfloat (*&ks)[4],                  // 読み込んだっデータのポリゴングループごとの鏡面反射係数
    GLfloat *&kshi,                     // 読み込んだっデータのポリゴングループごとの輝き係数
    GLuint &nv,                         // 読み込んだデータの頂点数
    GLfloat (*&vert)[3],                // 読み込んだデータの頂点位置
    GLfloat (*&norm)[3],                // 読み込んだデータの頂点法線
    bool normalize                      // true なら読み込んだデータの大きさを正規化する
    );

  /*
  ** 基底クラス
  */
  class Gg
  {
  protected:

    // デストラクタ
    ~Gg(void) {}

  public:

    // コンストラクタ
    Gg(void) {}
  };

  /*
  ** 変換行列
  */
  class GgMatrix
    : public Gg
  {
    // 変換行列の要素
    GLfloat array[16];

    // 行列 a とベクトル b の積をベクトル c に代入する
    void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

    // 行列 a と行列 b の積を行列 c に代入する
    void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

  public:

    // デストラクタ
    virtual ~GgMatrix(void) {}

    // コンストラクタ
    GgMatrix(void) {}
    GgMatrix(const GLfloat *a)
    {
      load(a);
    }
    GgMatrix(const GgMatrix &m)
    {
      load(m);
    }

    // 演算子
    GgMatrix &multiply(const GgMatrix &m, const GgMatrix &n)
    {
      multiply(array, m.array, n.array);
      return *this;
    }
    GgMatrix &multiply(const GgMatrix &m, const GLfloat *a)
    {
      multiply(array, m.array, a);
      return *this;
    }
    GgMatrix &multiply(const GLfloat *a)
    {
      GLfloat t[16];
      multiply(t, array, a);
      memcpy(array, t, sizeof array);
      return *this;
    }
    GgMatrix &multiply(const GgMatrix &m)
    {
      return multiply(m.array);
    }
    GgMatrix &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgMatrix &operator=(const GgMatrix &m)
    {
      return load(m);
    }
    GgMatrix operator*(const GLfloat *a) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgMatrix operator*(const GgMatrix &m) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, m.array);
      return t;
    }
    GgMatrix &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgMatrix &operator*=(const GgMatrix &m)
    {
      return multiply(m);
    }

    // 変換行列の読み込み
    GgMatrix &load(const GLfloat *a)
    {
      memcpy(array, a, sizeof array);
      return *this;
    }
    GgMatrix &load(const GgMatrix &m)
    {
      return load(m.array);
    }

    // 単位行列を設定する
    GgMatrix &loadIdentity(void);

    // 平行移動の変換行列を設定する
    GgMatrix &loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadTranslate(const GLfloat *t)
    {
      return loadTranslate(t[0], t[1], t[2], t[3]);
    }

    // 拡大縮小の変換行列を設定する
    GgMatrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadScale(const GLfloat *s)
    {
      return loadScale(s[0], s[1], s[2], s[3]);
    }

    // 回転の変換行列を設定する
    GgMatrix &loadRotateX(GLfloat a);
    GgMatrix &loadRotateY(GLfloat a);
    GgMatrix &loadRotateZ(GLfloat a);
    GgMatrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgMatrix &loadRotate(const GLfloat *r)
    {
      return loadRotate(r[0], r[1], r[2], r[3]);
    }

    // 視野変換行列を設定する
    GgMatrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // 直交投影変換行列を設定する
    GgMatrix &loadOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 透視透視投影変換行列を設定する
    GgMatrix &loadFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 画角を指定して透視投影変換行列を設定する
    GgMatrix &loadPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // 転置行列を設定する
    GgMatrix &loadTranspose(const GgMatrix &m);

    // 逆行列を設定する
    GgMatrix &loadInvert(const GgMatrix &m);

    // 法線変換行列を設定する
    GgMatrix &loadNormal(const GgMatrix &m);

    // 平行移動変換を乗じる
    GgMatrix &translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m;
      m.loadTranslate(x, y, z, w);
      multiply(m);
      return *this;
    }
    GgMatrix &translate(const GLfloat *t)
    {
      return translate(t[0], t[1], t[2], t[3]);
    }

    // 拡大縮小変換を乗じる
    GgMatrix &scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m;
      m.loadScale(x, y, z, w);
      multiply(m);
      return *this;
    }
    GgMatrix &scale(const GLfloat *s)
    {
      return scale(s[0], s[1], s[2], s[3]);
    }

    // 回転変換を乗じる
    GgMatrix &rotateX(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateX(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateY(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateY(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateZ(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateZ(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
    {
      GgMatrix m;
      m.loadRotate(x, y, z, a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(const GLfloat *r)
    {
      return rotate(r[0], r[1], r[2], r[3]);
    }

    // 視野変換を乗じる
    GgMatrix &lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // 直交投影変換を乗じる
    GgMatrix &orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 透視投影変換を乗じる
    GgMatrix &frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 画角を指定して透視投影変換を乗じる
    GgMatrix &perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // 転置行列を得る
    GgMatrix transpose(void) const
    {
      GgMatrix t;
      return t.loadTranspose(*this);
    }

    // 逆行列を得る
    GgMatrix invert(void) const
    {
      GgMatrix t;
      return t.loadInvert(*this);
    }

    // 法線変換行列を得る
    GgMatrix normal(void) const
    {
      GgMatrix t;
      return t.loadNormal(*this);
    }

    // ベクトルに対して投影変換を行う
    void projection(GLfloat *c, const GLfloat *v) const
    {
      projection(c, array, v);
    }

    // 変換行列を取り出す
    const GLfloat *get(void) const
    {
      return array;
    }
  };

  /*
  ** 四元数
  */
  class GgQuaternion
    : public Gg
  {
    // 四元数の要素
    GLfloat array[4];

    // 四元数 p と四元数 q の和を四元数 r に求める
    void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 p と四元数 q の差を四元数 r に求める
    void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 p と四元数 q の積を四元数 r に求める
    void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 q が表す回転の変換行列を m に求める
    void toMatrix(GLfloat *m, const GLfloat *q) const;

    // 回転の変換行列 m が表す四元数を q に求める
    void toQuaternion(GLfloat *q, const GLfloat *m) const;

    // 球面線形補間 q と r を t で補間した四元数を p に求める
    void slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const;

  public:

    // デストラクタ
    virtual ~GgQuaternion(void) {}

    // コンストラクタ
    GgQuaternion(void) {}
    GgQuaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      load(x, y, z, w);
    }
    GgQuaternion(const GLfloat *a)
    {
      load(a);
    }
    GgQuaternion(const GgQuaternion &q)
    {
      load(q);
    }

    // 演算子
    GgQuaternion &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgQuaternion &operator=(const GgQuaternion &q)
    {
      return load(q);
    }
    GgQuaternion operator+(const GLfloat *a) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator+(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator+=(const GLfloat *a)
    {
      return add(a);
    }
    GgQuaternion &operator+=(const GgQuaternion &q)
    {
      return add(q);
    }
    GgQuaternion operator-(const GLfloat *a) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator-(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator-=(const GLfloat *a)
    {
      return subtract(a);
    }
    GgQuaternion &operator-=(const GgQuaternion &q)
    {
      return subtract(q);
    }
    GgQuaternion operator*(const GLfloat *a) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator*(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgQuaternion &operator*=(const GgQuaternion &q)
    {
      return multiply(q);
    }

    // 四元数を設定する
    GgQuaternion &load(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      array[0] = x;
      array[1] = y;
      array[2] = z;
      array[3] = w;
      return *this;
    }
    GgQuaternion &load(const GLfloat *a)
    {
      return load(a[0], a[1], a[2], a[3]);
    }
    GgQuaternion &load(const GgQuaternion &q)
    {
      return load(q.array);
    }

    // 回転の変換行列 m を表す四元数を設定する
    GgQuaternion &loadMatrix(const GLfloat *m)
    {
      toQuaternion(array, m);
      return *this;
    }

    // 単位元を設定する
    GgQuaternion &loadIdentity(void)
    {
      return load(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // (x, y, z) を軸として角度 a 回転する資源数を設定する
    GgQuaternion &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgQuaternion &loadRotate(const GLfloat *v, GLfloat a)
    {
      return loadRotate(v[0], v[1], v[2], a);
    }

    // オイラー角 (h, p, r) で与えられた回転を表す四元数を設定する
    GgQuaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
    GgQuaternion &loadEuler(const GLfloat *e)
    {
      return loadEuler(e[0], e[1], e[2]);
    }

    // 四元数の和を求める
    GgQuaternion &add(const GgQuaternion &p, const GgQuaternion &q)
    {
      add(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &add(const GgQuaternion &q, const GLfloat *a)
    {
      add(array, q.array, a);
      return *this;
    }
    GgQuaternion &add(const GLfloat *a)
    {
      GLfloat t[4];
      add(t, array, a);
      return load(t);
    }
    GgQuaternion &add(const GgQuaternion &q)
    {
      return add(q.array);
    }

    // 四元数の差を求める
    GgQuaternion &subtract(const GgQuaternion &p, const GgQuaternion &q)
    {
      subtract(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &subtract(const GgQuaternion &q, const GLfloat *a)
    {
      subtract(array, q.array, a);
      return *this;
    }
    GgQuaternion &subtract(const GLfloat *a)
    {
      GLfloat t[4];
      subtract(t, array, a);
      return load(t);
    }
    GgQuaternion &subtract(const GgQuaternion &q)
    {
      return subtract(q.array);
    }

    // 四元数の積を求める
    GgQuaternion &multiply(const GgQuaternion &p, const GgQuaternion &q)
    {
      multiply(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &multiply(const GgQuaternion &q, const GLfloat *a)
    {
      multiply(array, q.array, a);
      return *this;
    }
    GgQuaternion &multiply(const GLfloat *a)
    {
      GLfloat t[4];
      multiply(t, array, a);
      return load(t);
    }
    GgQuaternion &multiply(const GgQuaternion &q)
    {
      return multiply(q.array);
    }

    // 球面線形補間
    GgQuaternion &slerp(const GgQuaternion &q, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, q.array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &q, const GLfloat *b, GLfloat t)
    {
      slerp(array, q.array, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, a, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GLfloat *b, GLfloat t)
    {
      slerp(array, a, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &r, GLfloat t)
    {
      slerp(array, array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(GLfloat *b, GLfloat t)
    {
      slerp(array, array, b, t);
      return *this;
    }

    // 四元数のノルムを求める
    GLfloat norm(void) const;

    // 共役四元数を求める
    GgQuaternion conjugate(void) const;

    // 四元数の逆を求める
    GgQuaternion invert(void) const;

    // 四元数を正規化する
    GgQuaternion normalize(void) const;

    // 四元数を取り出す
    const GLfloat *get(void) const
    {
      return array;
    }
    void get(GLfloat *a) const
    {
      a[0] = array[0];
      a[1] = array[1];
      a[2] = array[2];
      a[3] = array[3];
    }

    // 四元数が表す回転の行列を m に求める
    void getMatrix(GLfloat *m) const
    {
      toMatrix(m, array);
    }
  };

  /*
  ** 簡易トラックボール処理
  */
  class GgTrackball
    : public Gg
  {
    int cx, cy;       // ドラッグ開始位置
    bool drag;        // ドラッグ中か否か
    float sx, sy;     // マウスの絶対位置→ウィンドウ内での相対位置の換算係数
    GgQuaternion cq;  // 回転の初期値 (四元数)
    GgQuaternion tq;  // ドラッグ中の回転 (四元数)
    GLfloat rt[16];   // 回転の変換行列

  public:

    // デストラクタ
    virtual ~GgTrackball(void) {}

    // コンストラクタ
    GgTrackball(void);

    // トラックボール処理の範囲指定
    //    ウィンドウのリサイズ時に呼び出す
    void region(int w, int h);

    // トラックボール処理の開始
    //    マウスのドラッグ開始時（マウスボタンを押したとき）に呼び出す
    void start(int x, int y);

    // 回転の変換行列の計算
    //    マウスのドラッグ中に呼び出す
    void motion(int x, int y);

    // トラックボール処理の停止
    //    マウスのドラッグ終了時（マウスボタンを離したとき）に呼び出す
    void stop(int x, int y);

    // 現在の回転の変換行列を取り出す
    const GLfloat *get(void) const
    {
      return rt;
    }
  };

  /*
  ** 参照カウンタ
  **
  **     複数の属性データ間で共有されるリソースの確保と解放を管理する
  */
  class GgCounter
    : public Gg
  {
    friend class GgAttribute;

    // 参照カウント
    unsigned int count;

    // デストラクタ
    ~GgCounter(void) {}

    // コンストラクタ
    GgCounter(void)
      : count(0) {}
  };

  /*
  ** 属性データ
  **
  **     テクスチャとシェーダの基底クラス
  **     インスタンスは複数のオブジェクトから参照されることを想定する
  **     そのためこのクラスでは参照カウントを管理する
  */
  class GgAttribute
    : public Gg
  {
    // 参照カウンタ
    GgCounter *ref;

    // 参照カウントの増加
    void inc(void)
    {
      ++ref->count;
    }

  protected:

    // 参照カウントの減少
    unsigned int dec(void)
    {
      return --ref->count;
    }

  public:

    // デストラクタ
    virtual ~GgAttribute(void)
    {
      if (ref->count == 0) delete ref;
    }

    // コンストラクタ
    GgAttribute(void)
      : ref(new GgCounter)
    {
      inc();
    }
    GgAttribute(const GgAttribute &o)
      : ref(o.ref)
    {
      inc();
    }

    // 代入
    GgAttribute &operator=(const GgAttribute &o)
    {
      if (&o != this)
      {
        ref = o.ref;
        inc();
      }
      return *this;
    }
  };

  /*
  ** テクスチャ
  **
  **     カラー画像を読み込んでテクスチャマップを作成する
  */
  class GgTexture
    : public GgAttribute
  {
    // テクスチャ名
    GLuint texture;

  public:

    // デストラクタ
    virtual ~GgTexture(void)
    {
      if (dec() == 0) glDeleteTextures(1, &texture);
    }

    // コンストラクタ
    GgTexture(void)
    {
      glGenTextures(1, &texture);
    }
    GgTexture(GLsizei width, GLsizei height, GLenum internal = GL_RGBA, GLenum format = GL_RGBA, const GLvoid *image = 0)
    {
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      ggLoadTexture(width, height, internal, format, image);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    GgTexture(const char *name, GLenum internal = GL_RGBA)
    {
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      ggLoadImage(name, internal);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    GgTexture(const GgTexture &o)
      : GgAttribute(o), texture(o.texture) {}

    // 代入
    GgTexture &operator=(const GgTexture &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        texture = o.texture;
      }
      return *this;
    }

    // テクスチャオブジェクトを結合する
    //     このテクスチャを使用する際に呼び出す
    //     unit: 使用するテクスチャユニット番号（0～）
    void use(GLuint unit = 0) const
    {
      glActiveTexture(GL_TEXTURE0 + unit);
      glBindTexture(GL_TEXTURE_2D, texture);
    }

    // テクスチャオブジェクトを解放する
    //    このテクスチャを使用しなくなったら呼び出す
    void unuse(void) const
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      glActiveTexture(GL_TEXTURE0);
    }

    // テクスチャオブジェクトを取り出す
    GLuint get(void) const
    {
      return texture;
    }
  };

  /*
  ** 法線マップ
  **
  **     高さマップ（グレイスケール画像）を読み込んで法線マップを作成する
  */
  class GgNormalTexture
    : public GgTexture
  {
  public:

    // デストラクタ
    virtual ~GgNormalTexture(void) {}

    // コンストラクタ
    GgNormalTexture(void) {}
    GgNormalTexture(
      const char *name,                   // 画像ファイル名（1 チャネルの TGA 画像）
      float nz = 1.0f                     // 法線マップの z 成分の値
      )
      : GgTexture()
    {
      glBindTexture(GL_TEXTURE_2D, get());
      ggLoadHeight(name, nz);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    GgNormalTexture(const GgNormalTexture &o)
      : GgTexture(o) {}

    // 代入
    GgNormalTexture &operator=(const GgNormalTexture &o)
    {
      GgTexture::operator=(o);
      return *this;
    }
  };

  /*
  ** シェーダ
  **
  **     シェーダの基底クラス
  */
  class GgShader
    : public GgAttribute
  {
    // プログラム名
    GLuint program;

  public:

    // デストラクタ
    virtual ~GgShader(void)
    {
      if (dec() == 0 && program != 0) glDeleteProgram(program);
    }

    // コンストラクタ
    GgShader(void)
      : program(0) {}
    GgShader(
      const char *vert,                   // バーテックスシェーダのソースファイル名
      const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
      const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
      int nvarying = 0,                   // フィードバックする varying 変数の数（0 なら不使用）
      const char **varyings = 0           // フィードバックする varying 変数のリスト
      )
      : program(ggLoadShader(vert, frag, geom, nvarying, varyings)) {}
    GgShader(const GgShader &o)
      : GgAttribute(o), program(o.program) {}

    // 代入
    GgShader &operator=(const GgShader &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        program = o.program;
      }
      return *this;
    }

    // シェーダのソースプログラムの読み込みとコンパイル・リンク
    void load(
      const char *vert,                   // バーテックスシェーダのソースファイル名
      const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
      const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
      GLint nvarying = 0,                 // フィードバックする varying 変数の数（0 なら不使用）
      const char **varyings = 0           // フィードバックする varying 変数のリスト
      )
    {
      if (program != 0) glDeleteProgram(program);
      program = ggLoadShader(vert, frag, geom, nvarying, varyings);
    }

    // シェーダプログラムの使用を開始する
    virtual void use(GLuint vert, ...) const
    {
      glUseProgram(program);
    }

    // シェーダプログラムの使用を終了する
    virtual void unuse(void) const
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glUseProgram(0);
    }

    // シェーダプログラム名を取り出す
    GLuint get(void) const
    {
      return program;
    }
  };

  /*
  ** バッファオブジェクト
  **
  **    頂点／インデックスバッファオブジェクトの基底クラス
  */
  template <typename T>
  class GgBuffer
    : public GgAttribute
  {
    // バッファオブジェクト
    GLuint buffer;

    // データ数
    GLuint number;

  public:

    // デストラクタ
    virtual ~GgBuffer<T>(void)
    {
      if (dec() == 0) glDeleteBuffers(1, &buffer);
    }

    // コンストラクタ
    GgBuffer<T>(void)
      : number(0)
    {
      glGenBuffers(1, &buffer);
    }
    GgBuffer<T>(GLenum target, GLuint n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      glGenBuffers(1, &buffer);
      load(target, n, data, usage);
    }
    GgBuffer<T>(const GgBuffer<T> &o)
      : GgAttribute(o), buffer(o.buffer), number(o.number) {}

    // 代入
    GgBuffer<T> &operator=(const GgBuffer<T> &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        buffer = o.buffer;
        number = o.number;
      }
      return *this;
    }

    // バッファオブジェクトにデータを格納する
    void load(GLenum target, GLuint n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      number = n;
      glBindBuffer(target, buffer);
      glBufferData(target, sizeof (T) * n, data, usage);
    }

    // バッファオブジェクトのデータを複写する
    void copy(GLuint buf)
    {
      const size_t size = sizeof (T) * number;
#ifdef __APPLE__
      T *temp = new T[number];
      glBindBuffer(GL_ARRAY_BUFFER, buf);
      glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, temp);
      glBindBuffer(GL_ARRAY_BUFFER, buffer);
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, temp);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      delete[] temp;
#else
      glBindBuffer(GL_COPY_READ_BUFFER, buf);
      glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
      glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
      glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
      glBindBuffer(GL_COPY_READ_BUFFER, 0);
#endif
    }

    // バッファオブジェクト名を取り出す
    GLuint buf(void) const
    {
      return buffer;
    }

    // データの数を取り出す
    GLuint num(void) const
    {
      return number;
    }
  };

  /*
  ** 形状データ
  **
  **    形状データの基底クラス
  **    このクラスから使用するシェーダを参照する
  **    シェーダのインスタンスを結合したら参照カウントをインクリメントする
  **    シェーダのインスタンスの結合を解除したら参照カウントをデクリメントし，0 になったらシェーダを削除する
  */
  class GgShape
    : public Gg
  {
    // シェーダー
    GgShader *shader;

  protected:

    // 描画図形
    GLenum mode;

  public:

    // デストラクタ
    virtual ~GgShape(void) {}

    // コンストラクタ
    GgShape(void)
      : shader(0), mode(GL_POINTS) {}
    GgShape(const GgShape &o)
      : shader(o.shader), mode(o.mode) {}

    // 代入演算子
    GgShape &operator=(const GgShape &o)
    {
      if (this != &o)
      {
        attachShader(o.shader);
        mode = o.mode;
      }
      return *this;
    }

    // 形状データにシェーダのインスタンス s を結合する
    //    それまで結合されていたシェーダの参照カウントをデクリメントして 0 になったらそのシェーダを破棄する
    //    新しいシェーダ s を結合して s の参照カウントをインクリメントする
    void attachShader(GgShader *s)
    {
      shader = s;
    }
    void attachShader(GgShader &s)
    {
      shader = &s;
    }

    // この形状データで使用しているシェーダを取り出す
    GgShader *getShader(void) const
    {
      return shader;
    }

    // 描画に使う基本図形を設定する
    void setMode(GLenum m)
    {
      mode = m;
    }

    // この形状を描画する手続きをオーバーライドする
    virtual void draw(void) const = 0;
  };

  /*
  ** ポイント
  */
  class GgPoints
    : public GgShape
  {
    // 頂点バッファオブジェクト
    GgBuffer<GLfloat[3]> position;

  public:

    // デストラクタ
    virtual ~GgPoints(void) {}

    // コンストラクタ
    GgPoints(void) {}
    GgPoints(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      load(n, pos, usage);
      mode = GL_POINTS;
    }
    GgPoints(const GgPoints &o)
      : GgShape(o), position(o.position) {}

    // 代入
    GgPoints &operator=(const GgPoints &o)
    {
      if (&o != this)
      {
        GgShape::operator=(o);
        position = o.position;
      }
      return *this;
    }

    // バッファオブジェクトを確保して頂点を格納する
    //    n: 頂点数, pos: 頂点の位置
    void load(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      position.load(GL_ARRAY_BUFFER, n, pos, usage);
    }

    // バッファオブジェクト名を取り出す
    GLuint pbuf(void) const
    {
      return position.buf();
    }

    // データの数を取り出す
    GLuint pnum(void) const
    {
      return position.num();
    }

    // ポイントの描画
    virtual void draw(void) const;
  };

  /*
  ** ポリゴン
  */
  class GgTriangles
    : public GgPoints
  {
    // 頂点の法線ベクトル
    GgBuffer<GLfloat[3]> normal;

  public:

    // デストラクタ
    virtual ~GgTriangles(void) {}

    // コンストラクタ
    GgTriangles(void) {}
    GgTriangles(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
      : GgPoints(n, pos, usage)
    {
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
      mode = GL_TRIANGLES;
    }
    GgTriangles(const GgTriangles &o)
      : GgPoints(o), normal(o.normal) {}

    // 代入
    GgTriangles &operator=(const GgTriangles &o)
    {
      if (&o != this)
      {
        GgPoints::operator=(o);
        normal = o.normal;
      }
      return *this;
    }

    // バッファオブジェクトを確保して位置と法線を格納する
    //    n: 頂点数, pos: 頂点の位置, norm: 頂点の法線
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgPoints::load(n, pos, usage);
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
    }

    // バッファオブジェクト名を取り出す
    GLuint nbuf(void) const
    {
      return normal.buf();
    }

    // データの数を取り出す
    GLuint nnum(void) const
    {
      return normal.num();
    }

    // 三角形群を描画する手続き
    virtual void draw(void) const;
  };

  /*
  ** 三角形の形状データ
  */
  class GgElements
    : public GgTriangles
  {
    // インデックスバッファオブジェクト
    GgBuffer<GLuint[3]> index;

  public:

    // デストラクタ
    virtual ~GgElements(void) {}

    // コンストラクタ
    GgElements(void) {}
    GgElements(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
      : GgTriangles(n, pos, norm, usage)
    {
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }
    GgElements(const GgElements &o)
      : GgTriangles(o), index(o.index) {}

    // 代入
    GgElements &operator=(const GgElements &o)
    {
      if (&o != this)
      {
        GgTriangles::operator=(o);
        index = o.index;
      }
      return *this;
    }

    // バッファオブジェクトを確保して位置と法線とインデックスを格納する
    //    n: 頂点数, pos: 頂点の位置, norm:頂点の法線
    //    f: 面数, face: 頂点のインデックスデータ
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgTriangles::load(n, pos, norm, usage);
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }

    // バッファオブジェクト名を取り出す
    GLuint fbuf(void) const
    {
      return index.buf();
    }

    // データの数を取り出す
    GLuint fnum(void) const
    {
      return index.num();
    }

    // 三角形ポリゴンを描画する手続き
    virtual void draw(void) const;
  };

  /*
  ** 球状のポイント
  */
  extern GgPoints *ggPointSphere(GLuint nv, GLfloat cx = 0.0f, GLfloat cy = 0.0f, GLfloat cz = 0.0f, GLfloat radius = 0.5f);

  /*
  ** 矩形
  */
  extern GgTriangles *ggRectangle(GLfloat width = 1.0f, GLfloat height = 1.0f);

  /*
  ** 楕円
  */
  extern GgTriangles *ggEllipse(GLfloat width = 1.0f, GLfloat height = 1.0f, GLuint slices = 16);

  /*
  ** 三角形分割された Alias OBJ ファイル (Arrays 形式)
  */
  extern GgTriangles *ggArraysObj(const char *name, bool normalize = false);

  /*
  ** 三角形分割された Alias OBJ ファイル (Elements 形式)
  */
  extern GgElements *ggElementsObj(const char *name, bool normalize = false);
}

#endif
