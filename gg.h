/*
** �Q�[���O���t�B�b�N�X���_�p�⏕�v���O���� GLFW ��
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
  ** �Q�[���O���t�B�b�N�X���_�̓s���ɂ��ƂÂ�������
  **
  **     OpenGL �̃����_�����O�R���e�L�X�g�쐬��Ɏ��s����
  */
  extern void ggInit(void);

  /*
  ** OpenGL �̃G���[�`�F�b�N
  **
  **     OpenGL �� API ���Ăяo������Ɏ��s����΃G���[�̂���Ƃ��Ƀ��b�Z�[�W��\������
  */
  extern void ggError(
    const char *msg = 0                 // �o�͂��郁�b�Z�[�W�̐擪�ɒǉ����镶����
    );

  /*
  ** FBO �̃G���[�`�F�b�N
  **
  **     FBO �� API ���Ăяo������Ɏ��s����΃G���[�̂���Ƃ��Ƀ��b�Z�[�W��\������
  */
  extern void ggFBOError(
    const char *msg = 0                 // �o�͂��郁�b�Z�[�W�̐擪�ɒǉ����镶����
    );

  /*
  ** �V�F�[�_�[�\�[�X�t�@�C���̓ǂݍ���
  */
  extern GLuint ggLoadShader(           // �V�F�[�_�v���O�����̃v���O������
    const char *vert,                   // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
    const char *frag = 0,               // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
    const char *geom = 0,               // �W�I���g���V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
    int nvarying = 0,                   // �t�B�[�h�o�b�N���� varying �ϐ��̐��i0 �Ȃ�s�g�p�j
    const char **varyings = 0           // �t�B�[�h�o�b�N���� varying �ϐ��̃��X�g
    );

  /*
  ** �z��̓��e�� TGA �t�@�C���ɕۑ�
  */
  bool ggSaveTga(                       // �ۑ��ł����� true
    GLsizei sx,                         // �z��̍s�����̑傫��
    GLsizei sy,                         // �z��̗�����̑傫��
    unsigned int depth,                 // �z��̗v�f�̃o�C�g��
    const GLubyte *buffer,              // �ۑ�����z��
    const char *name                    // �ۑ�����t�@�C����
    );

  /*
  ** �J���[�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
  */
  extern bool ggSaveColor(              // �ۑ��ł����� true
    const char *name                    // �ۑ�����t�@�C����
    );

  /*
  ** �f�v�X�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
  */
  extern bool ggSaveDepth(              // �ۑ��ł����� true
    const char *name                    // �ۑ�����t�@�C����
    );

  /*
  ** TGA �t�@�C�� (8/16/24/32bit) �̓ǂݍ���
  */
  extern GLubyte *ggLoadTga(            // �ǂݍ��񂾉摜�f�[�^�̃|�C���^��Ԃ� (�g�p�� delete ����)
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLsizei &width,                     // �ǂݍ��� TGA �t�@�C���̕�
    GLsizei &height,                    // �ǂݍ��� TGA �t�@�C���̍���
    GLenum &format                      // �ǂݍ��� TGA �t�@�C���̏��� (GL_R, GL_RG, GL_BGR, GL_BGRA)
    );

  /*
  ** �e�N�X�`���������̊m��
  */
  extern void ggLoadTexture(
    GLsizei width,                      // �m�ۂ���e�N�X�`���������̕�
    GLsizei height,                     // �m�ۂ���e�N�X�`���������̍���
    GLenum internal,                    // �m�ۂ���e�N�X�`���������̓�������
    GLenum format = GL_RGBA,            // image �̏���
    const GLvoid *image = 0
    );

  /*
  ** TGA �t�@�C�����e�N�X�`���������ɓǂݍ���
  */
  extern bool ggLoadImage(              // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLenum internal                     // �e�N�X�`���������̓����t�H�[�}�b�g
    );

  /*
  ** TGA �摜�t�@�C���̍����}�b�v�ǂݍ���Ńe�N�X�`���������ɖ@���}�b�v���쐬����
  */
  extern bool ggLoadHeight(             // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    float nz                            // �@���� z ���̒���
    );

  /*
  ** �O�p�`�������ꂽ OBJ �t�@�C����ǂݍ��� (Elements �`��)
  */
  extern bool ggLoadObj(                // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLuint &nv,                         // �ǂݍ��񂾃f�[�^�̒��_��
    GLfloat (*&vert)[3],                // �ǂݍ��񂾃f�[�^�̒��_�ʒu
    GLfloat (*&norm)[3],                // �ǂݍ��񂾃f�[�^�̒��_�@��
    GLuint &nf,                         // �ǂݍ��񂾃f�[�^�̎O�p�`��
    GLuint (*&face)[3],                 // �ǂݍ��񂾃f�[�^�̎O�p�`�̒��_�C���f�b�N�X
    bool normalize                      // true �Ȃ�ǂݍ��񂾃f�[�^�̑傫���𐳋K������
    );

  /*
  ** �O�p�`�������ꂽ OBJ �t�@�C���� MTL �t�@�C����ǂݍ��� (Arrays �`��)
  */
  extern bool ggLoadObj(                // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLuint &ng,                         // �ǂݍ��񂾃f�[�^�̃|���S���O���[�v��
    GLuint (*&group)[2],                // �ǂݍ��񂾃f�[�^�̃|���S���O���[�v�̍ŏ��̃|���S���̃C���f�b�N�X�ƃ|���S����
    GLfloat (*&ka)[4],                  // �ǂݍ��񂾂��f�[�^�̃|���S���O���[�v���Ƃ̊����ɑ΂��锽�ˌW��
    GLfloat (*&kd)[4],                  // �ǂݍ��񂾂��f�[�^�̃|���S���O���[�v���Ƃ̊g�U���ˌW��
    GLfloat (*&ks)[4],                  // �ǂݍ��񂾂��f�[�^�̃|���S���O���[�v���Ƃ̋��ʔ��ˌW��
    GLfloat *&kshi,                     // �ǂݍ��񂾂��f�[�^�̃|���S���O���[�v���Ƃ̋P���W��
    GLuint &nv,                         // �ǂݍ��񂾃f�[�^�̒��_��
    GLfloat (*&vert)[3],                // �ǂݍ��񂾃f�[�^�̒��_�ʒu
    GLfloat (*&norm)[3],                // �ǂݍ��񂾃f�[�^�̒��_�@��
    bool normalize                      // true �Ȃ�ǂݍ��񂾃f�[�^�̑傫���𐳋K������
    );

  /*
  ** ���N���X
  */
  class Gg
  {
  protected:

    // �f�X�g���N�^
    ~Gg(void) {}

  public:

    // �R���X�g���N�^
    Gg(void) {}
  };

  /*
  ** �ϊ��s��
  */
  class GgMatrix
    : public Gg
  {
    // �ϊ��s��̗v�f
    GLfloat array[16];

    // �s�� a �ƃx�N�g�� b �̐ς��x�N�g�� c �ɑ������
    void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

    // �s�� a �ƍs�� b �̐ς��s�� c �ɑ������
    void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

  public:

    // �f�X�g���N�^
    virtual ~GgMatrix(void) {}

    // �R���X�g���N�^
    GgMatrix(void) {}
    GgMatrix(const GLfloat *a)
    {
      load(a);
    }
    GgMatrix(const GgMatrix &m)
    {
      load(m);
    }

    // ���Z�q
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

    // �ϊ��s��̓ǂݍ���
    GgMatrix &load(const GLfloat *a)
    {
      memcpy(array, a, sizeof array);
      return *this;
    }
    GgMatrix &load(const GgMatrix &m)
    {
      return load(m.array);
    }

    // �P�ʍs���ݒ肷��
    GgMatrix &loadIdentity(void);

    // ���s�ړ��̕ϊ��s���ݒ肷��
    GgMatrix &loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadTranslate(const GLfloat *t)
    {
      return loadTranslate(t[0], t[1], t[2], t[3]);
    }

    // �g��k���̕ϊ��s���ݒ肷��
    GgMatrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadScale(const GLfloat *s)
    {
      return loadScale(s[0], s[1], s[2], s[3]);
    }

    // ��]�̕ϊ��s���ݒ肷��
    GgMatrix &loadRotateX(GLfloat a);
    GgMatrix &loadRotateY(GLfloat a);
    GgMatrix &loadRotateZ(GLfloat a);
    GgMatrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgMatrix &loadRotate(const GLfloat *r)
    {
      return loadRotate(r[0], r[1], r[2], r[3]);
    }

    // ����ϊ��s���ݒ肷��
    GgMatrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // ���𓊉e�ϊ��s���ݒ肷��
    GgMatrix &loadOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // �����������e�ϊ��s���ݒ肷��
    GgMatrix &loadFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // ��p���w�肵�ē������e�ϊ��s���ݒ肷��
    GgMatrix &loadPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // �]�u�s���ݒ肷��
    GgMatrix &loadTranspose(const GgMatrix &m);

    // �t�s���ݒ肷��
    GgMatrix &loadInvert(const GgMatrix &m);

    // �@���ϊ��s���ݒ肷��
    GgMatrix &loadNormal(const GgMatrix &m);

    // ���s�ړ��ϊ����悶��
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

    // �g��k���ϊ����悶��
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

    // ��]�ϊ����悶��
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

    // ����ϊ����悶��
    GgMatrix &lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // ���𓊉e�ϊ����悶��
    GgMatrix &orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // �������e�ϊ����悶��
    GgMatrix &frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // ��p���w�肵�ē������e�ϊ����悶��
    GgMatrix &perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // �]�u�s��𓾂�
    GgMatrix transpose(void) const
    {
      GgMatrix t;
      return t.loadTranspose(*this);
    }

    // �t�s��𓾂�
    GgMatrix invert(void) const
    {
      GgMatrix t;
      return t.loadInvert(*this);
    }

    // �@���ϊ��s��𓾂�
    GgMatrix normal(void) const
    {
      GgMatrix t;
      return t.loadNormal(*this);
    }

    // �x�N�g���ɑ΂��ē��e�ϊ����s��
    void projection(GLfloat *c, const GLfloat *v) const
    {
      projection(c, array, v);
    }

    // �ϊ��s������o��
    const GLfloat *get(void) const
    {
      return array;
    }
  };

  /*
  ** �l����
  */
  class GgQuaternion
    : public Gg
  {
    // �l�����̗v�f
    GLfloat array[4];

    // �l���� p �Ǝl���� q �̘a���l���� r �ɋ��߂�
    void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� p �Ǝl���� q �̍����l���� r �ɋ��߂�
    void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� p �Ǝl���� q �̐ς��l���� r �ɋ��߂�
    void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� q ���\����]�̕ϊ��s��� m �ɋ��߂�
    void toMatrix(GLfloat *m, const GLfloat *q) const;

    // ��]�̕ϊ��s�� m ���\���l������ q �ɋ��߂�
    void toQuaternion(GLfloat *q, const GLfloat *m) const;

    // ���ʐ��`��� q �� r �� t �ŕ�Ԃ����l������ p �ɋ��߂�
    void slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const;

  public:

    // �f�X�g���N�^
    virtual ~GgQuaternion(void) {}

    // �R���X�g���N�^
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

    // ���Z�q
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

    // �l������ݒ肷��
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

    // ��]�̕ϊ��s�� m ��\���l������ݒ肷��
    GgQuaternion &loadMatrix(const GLfloat *m)
    {
      toQuaternion(array, m);
      return *this;
    }

    // �P�ʌ���ݒ肷��
    GgQuaternion &loadIdentity(void)
    {
      return load(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // (x, y, z) �����Ƃ��Ċp�x a ��]���鎑������ݒ肷��
    GgQuaternion &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgQuaternion &loadRotate(const GLfloat *v, GLfloat a)
    {
      return loadRotate(v[0], v[1], v[2], a);
    }

    // �I�C���[�p (h, p, r) �ŗ^����ꂽ��]��\���l������ݒ肷��
    GgQuaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
    GgQuaternion &loadEuler(const GLfloat *e)
    {
      return loadEuler(e[0], e[1], e[2]);
    }

    // �l�����̘a�����߂�
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

    // �l�����̍������߂�
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

    // �l�����̐ς����߂�
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

    // ���ʐ��`���
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

    // �l�����̃m���������߂�
    GLfloat norm(void) const;

    // �����l���������߂�
    GgQuaternion conjugate(void) const;

    // �l�����̋t�����߂�
    GgQuaternion invert(void) const;

    // �l�����𐳋K������
    GgQuaternion normalize(void) const;

    // �l���������o��
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

    // �l�������\����]�̍s��� m �ɋ��߂�
    void getMatrix(GLfloat *m) const
    {
      toMatrix(m, array);
    }
  };

  /*
  ** �ȈՃg���b�N�{�[������
  */
  class GgTrackball
    : public Gg
  {
    int cx, cy;       // �h���b�O�J�n�ʒu
    bool drag;        // �h���b�O�����ۂ�
    float sx, sy;     // �}�E�X�̐�Έʒu���E�B���h�E���ł̑��Έʒu�̊��Z�W��
    GgQuaternion cq;  // ��]�̏����l (�l����)
    GgQuaternion tq;  // �h���b�O���̉�] (�l����)
    GLfloat rt[16];   // ��]�̕ϊ��s��

  public:

    // �f�X�g���N�^
    virtual ~GgTrackball(void) {}

    // �R���X�g���N�^
    GgTrackball(void);

    // �g���b�N�{�[�������͈͎̔w��
    //    �E�B���h�E�̃��T�C�Y���ɌĂяo��
    void region(int w, int h);

    // �g���b�N�{�[�������̊J�n
    //    �}�E�X�̃h���b�O�J�n���i�}�E�X�{�^�����������Ƃ��j�ɌĂяo��
    void start(int x, int y);

    // ��]�̕ϊ��s��̌v�Z
    //    �}�E�X�̃h���b�O���ɌĂяo��
    void motion(int x, int y);

    // �g���b�N�{�[�������̒�~
    //    �}�E�X�̃h���b�O�I�����i�}�E�X�{�^���𗣂����Ƃ��j�ɌĂяo��
    void stop(int x, int y);

    // ���݂̉�]�̕ϊ��s������o��
    const GLfloat *get(void) const
    {
      return rt;
    }
  };

  /*
  ** �Q�ƃJ�E���^
  **
  **     �����̑����f�[�^�Ԃŋ��L����郊�\�[�X�̊m�ۂƉ�����Ǘ�����
  */
  class GgCounter
    : public Gg
  {
    friend class GgAttribute;

    // �Q�ƃJ�E���g
    unsigned int count;

    // �f�X�g���N�^
    ~GgCounter(void) {}

    // �R���X�g���N�^
    GgCounter(void)
      : count(0) {}
  };

  /*
  ** �����f�[�^
  **
  **     �e�N�X�`���ƃV�F�[�_�̊��N���X
  **     �C���X�^���X�͕����̃I�u�W�F�N�g����Q�Ƃ���邱�Ƃ�z�肷��
  **     ���̂��߂��̃N���X�ł͎Q�ƃJ�E���g���Ǘ�����
  */
  class GgAttribute
    : public Gg
  {
    // �Q�ƃJ�E���^
    GgCounter *ref;

    // �Q�ƃJ�E���g�̑���
    void inc(void)
    {
      ++ref->count;
    }

  protected:

    // �Q�ƃJ�E���g�̌���
    unsigned int dec(void)
    {
      return --ref->count;
    }

  public:

    // �f�X�g���N�^
    virtual ~GgAttribute(void)
    {
      if (ref->count == 0) delete ref;
    }

    // �R���X�g���N�^
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

    // ���
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
  ** �e�N�X�`��
  **
  **     �J���[�摜��ǂݍ���Ńe�N�X�`���}�b�v���쐬����
  */
  class GgTexture
    : public GgAttribute
  {
    // �e�N�X�`����
    GLuint texture;

  public:

    // �f�X�g���N�^
    virtual ~GgTexture(void)
    {
      if (dec() == 0) glDeleteTextures(1, &texture);
    }

    // �R���X�g���N�^
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

    // ���
    GgTexture &operator=(const GgTexture &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        texture = o.texture;
      }
      return *this;
    }

    // �e�N�X�`���I�u�W�F�N�g����������
    //     ���̃e�N�X�`�����g�p����ۂɌĂяo��
    //     unit: �g�p����e�N�X�`�����j�b�g�ԍ��i0�`�j
    void use(GLuint unit = 0) const
    {
      glActiveTexture(GL_TEXTURE0 + unit);
      glBindTexture(GL_TEXTURE_2D, texture);
    }

    // �e�N�X�`���I�u�W�F�N�g���������
    //    ���̃e�N�X�`�����g�p���Ȃ��Ȃ�����Ăяo��
    void unuse(void) const
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      glActiveTexture(GL_TEXTURE0);
    }

    // �e�N�X�`���I�u�W�F�N�g�����o��
    GLuint get(void) const
    {
      return texture;
    }
  };

  /*
  ** �@���}�b�v
  **
  **     �����}�b�v�i�O���C�X�P�[���摜�j��ǂݍ���Ŗ@���}�b�v���쐬����
  */
  class GgNormalTexture
    : public GgTexture
  {
  public:

    // �f�X�g���N�^
    virtual ~GgNormalTexture(void) {}

    // �R���X�g���N�^
    GgNormalTexture(void) {}
    GgNormalTexture(
      const char *name,                   // �摜�t�@�C�����i1 �`���l���� TGA �摜�j
      float nz = 1.0f                     // �@���}�b�v�� z �����̒l
      )
      : GgTexture()
    {
      glBindTexture(GL_TEXTURE_2D, get());
      ggLoadHeight(name, nz);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    GgNormalTexture(const GgNormalTexture &o)
      : GgTexture(o) {}

    // ���
    GgNormalTexture &operator=(const GgNormalTexture &o)
    {
      GgTexture::operator=(o);
      return *this;
    }
  };

  /*
  ** �V�F�[�_
  **
  **     �V�F�[�_�̊��N���X
  */
  class GgShader
    : public GgAttribute
  {
    // �v���O������
    GLuint program;

  public:

    // �f�X�g���N�^
    virtual ~GgShader(void)
    {
      if (dec() == 0 && program != 0) glDeleteProgram(program);
    }

    // �R���X�g���N�^
    GgShader(void)
      : program(0) {}
    GgShader(
      const char *vert,                   // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
      const char *frag = 0,               // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      const char *geom = 0,               // �W�I���g���V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      int nvarying = 0,                   // �t�B�[�h�o�b�N���� varying �ϐ��̐��i0 �Ȃ�s�g�p�j
      const char **varyings = 0           // �t�B�[�h�o�b�N���� varying �ϐ��̃��X�g
      )
      : program(ggLoadShader(vert, frag, geom, nvarying, varyings)) {}
    GgShader(const GgShader &o)
      : GgAttribute(o), program(o.program) {}

    // ���
    GgShader &operator=(const GgShader &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        program = o.program;
      }
      return *this;
    }

    // �V�F�[�_�̃\�[�X�v���O�����̓ǂݍ��݂ƃR���p�C���E�����N
    void load(
      const char *vert,                   // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
      const char *frag = 0,               // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      const char *geom = 0,               // �W�I���g���V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      GLint nvarying = 0,                 // �t�B�[�h�o�b�N���� varying �ϐ��̐��i0 �Ȃ�s�g�p�j
      const char **varyings = 0           // �t�B�[�h�o�b�N���� varying �ϐ��̃��X�g
      )
    {
      if (program != 0) glDeleteProgram(program);
      program = ggLoadShader(vert, frag, geom, nvarying, varyings);
    }

    // �V�F�[�_�v���O�����̎g�p���J�n����
    virtual void use(GLuint vert, ...) const
    {
      glUseProgram(program);
    }

    // �V�F�[�_�v���O�����̎g�p���I������
    virtual void unuse(void) const
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glUseProgram(0);
    }

    // �V�F�[�_�v���O�����������o��
    GLuint get(void) const
    {
      return program;
    }
  };

  /*
  ** �o�b�t�@�I�u�W�F�N�g
  **
  **    ���_�^�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̊��N���X
  */
  template <typename T>
  class GgBuffer
    : public GgAttribute
  {
    // �o�b�t�@�I�u�W�F�N�g
    GLuint buffer;

    // �f�[�^��
    GLuint number;

  public:

    // �f�X�g���N�^
    virtual ~GgBuffer<T>(void)
    {
      if (dec() == 0) glDeleteBuffers(1, &buffer);
    }

    // �R���X�g���N�^
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

    // ���
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

    // �o�b�t�@�I�u�W�F�N�g�Ƀf�[�^���i�[����
    void load(GLenum target, GLuint n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      number = n;
      glBindBuffer(target, buffer);
      glBufferData(target, sizeof (T) * n, data, usage);
    }

    // �o�b�t�@�I�u�W�F�N�g�̃f�[�^�𕡎ʂ���
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

    // �o�b�t�@�I�u�W�F�N�g�������o��
    GLuint buf(void) const
    {
      return buffer;
    }

    // �f�[�^�̐������o��
    GLuint num(void) const
    {
      return number;
    }
  };

  /*
  ** �`��f�[�^
  **
  **    �`��f�[�^�̊��N���X
  **    ���̃N���X����g�p����V�F�[�_���Q�Ƃ���
  **    �V�F�[�_�̃C���X�^���X������������Q�ƃJ�E���g���C���N�������g����
  **    �V�F�[�_�̃C���X�^���X�̌���������������Q�ƃJ�E���g���f�N�������g���C0 �ɂȂ�����V�F�[�_���폜����
  */
  class GgShape
    : public Gg
  {
    // �V�F�[�_�[
    GgShader *shader;

  protected:

    // �`��}�`
    GLenum mode;

  public:

    // �f�X�g���N�^
    virtual ~GgShape(void) {}

    // �R���X�g���N�^
    GgShape(void)
      : shader(0), mode(GL_POINTS) {}
    GgShape(const GgShape &o)
      : shader(o.shader), mode(o.mode) {}

    // ������Z�q
    GgShape &operator=(const GgShape &o)
    {
      if (this != &o)
      {
        attachShader(o.shader);
        mode = o.mode;
      }
      return *this;
    }

    // �`��f�[�^�ɃV�F�[�_�̃C���X�^���X s ����������
    //    ����܂Ō�������Ă����V�F�[�_�̎Q�ƃJ�E���g���f�N�������g���� 0 �ɂȂ����炻�̃V�F�[�_��j������
    //    �V�����V�F�[�_ s ���������� s �̎Q�ƃJ�E���g���C���N�������g����
    void attachShader(GgShader *s)
    {
      shader = s;
    }
    void attachShader(GgShader &s)
    {
      shader = &s;
    }

    // ���̌`��f�[�^�Ŏg�p���Ă���V�F�[�_�����o��
    GgShader *getShader(void) const
    {
      return shader;
    }

    // �`��Ɏg����{�}�`��ݒ肷��
    void setMode(GLenum m)
    {
      mode = m;
    }

    // ���̌`���`�悷��葱�����I�[�o�[���C�h����
    virtual void draw(void) const = 0;
  };

  /*
  ** �|�C���g
  */
  class GgPoints
    : public GgShape
  {
    // ���_�o�b�t�@�I�u�W�F�N�g
    GgBuffer<GLfloat[3]> position;

  public:

    // �f�X�g���N�^
    virtual ~GgPoints(void) {}

    // �R���X�g���N�^
    GgPoints(void) {}
    GgPoints(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      load(n, pos, usage);
      mode = GL_POINTS;
    }
    GgPoints(const GgPoints &o)
      : GgShape(o), position(o.position) {}

    // ���
    GgPoints &operator=(const GgPoints &o)
    {
      if (&o != this)
      {
        GgShape::operator=(o);
        position = o.position;
      }
      return *this;
    }

    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ē��_���i�[����
    //    n: ���_��, pos: ���_�̈ʒu
    void load(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      position.load(GL_ARRAY_BUFFER, n, pos, usage);
    }

    // �o�b�t�@�I�u�W�F�N�g�������o��
    GLuint pbuf(void) const
    {
      return position.buf();
    }

    // �f�[�^�̐������o��
    GLuint pnum(void) const
    {
      return position.num();
    }

    // �|�C���g�̕`��
    virtual void draw(void) const;
  };

  /*
  ** �|���S��
  */
  class GgTriangles
    : public GgPoints
  {
    // ���_�̖@���x�N�g��
    GgBuffer<GLfloat[3]> normal;

  public:

    // �f�X�g���N�^
    virtual ~GgTriangles(void) {}

    // �R���X�g���N�^
    GgTriangles(void) {}
    GgTriangles(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
      : GgPoints(n, pos, usage)
    {
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
      mode = GL_TRIANGLES;
    }
    GgTriangles(const GgTriangles &o)
      : GgPoints(o), normal(o.normal) {}

    // ���
    GgTriangles &operator=(const GgTriangles &o)
    {
      if (&o != this)
      {
        GgPoints::operator=(o);
        normal = o.normal;
      }
      return *this;
    }

    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ĉʒu�Ɩ@�����i�[����
    //    n: ���_��, pos: ���_�̈ʒu, norm: ���_�̖@��
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgPoints::load(n, pos, usage);
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
    }

    // �o�b�t�@�I�u�W�F�N�g�������o��
    GLuint nbuf(void) const
    {
      return normal.buf();
    }

    // �f�[�^�̐������o��
    GLuint nnum(void) const
    {
      return normal.num();
    }

    // �O�p�`�Q��`�悷��葱��
    virtual void draw(void) const;
  };

  /*
  ** �O�p�`�̌`��f�[�^
  */
  class GgElements
    : public GgTriangles
  {
    // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
    GgBuffer<GLuint[3]> index;

  public:

    // �f�X�g���N�^
    virtual ~GgElements(void) {}

    // �R���X�g���N�^
    GgElements(void) {}
    GgElements(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
      : GgTriangles(n, pos, norm, usage)
    {
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }
    GgElements(const GgElements &o)
      : GgTriangles(o), index(o.index) {}

    // ���
    GgElements &operator=(const GgElements &o)
    {
      if (&o != this)
      {
        GgTriangles::operator=(o);
        index = o.index;
      }
      return *this;
    }

    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ĉʒu�Ɩ@���ƃC���f�b�N�X���i�[����
    //    n: ���_��, pos: ���_�̈ʒu, norm:���_�̖@��
    //    f: �ʐ�, face: ���_�̃C���f�b�N�X�f�[�^
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgTriangles::load(n, pos, norm, usage);
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }

    // �o�b�t�@�I�u�W�F�N�g�������o��
    GLuint fbuf(void) const
    {
      return index.buf();
    }

    // �f�[�^�̐������o��
    GLuint fnum(void) const
    {
      return index.num();
    }

    // �O�p�`�|���S����`�悷��葱��
    virtual void draw(void) const;
  };

  /*
  ** ����̃|�C���g
  */
  extern GgPoints *ggPointSphere(GLuint nv, GLfloat cx = 0.0f, GLfloat cy = 0.0f, GLfloat cz = 0.0f, GLfloat radius = 0.5f);

  /*
  ** ��`
  */
  extern GgTriangles *ggRectangle(GLfloat width = 1.0f, GLfloat height = 1.0f);

  /*
  ** �ȉ~
  */
  extern GgTriangles *ggEllipse(GLfloat width = 1.0f, GLfloat height = 1.0f, GLuint slices = 16);

  /*
  ** �O�p�`�������ꂽ Alias OBJ �t�@�C�� (Arrays �`��)
  */
  extern GgTriangles *ggArraysObj(const char *name, bool normalize = false);

  /*
  ** �O�p�`�������ꂽ Alias OBJ �t�@�C�� (Elements �`��)
  */
  extern GgElements *ggElementsObj(const char *name, bool normalize = false);
}

#endif
