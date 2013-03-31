/*
** �Q�[���O���t�B�b�N�X���_�p�⏕�v���O���� for GLFW
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
** �Q�[���O���t�B�b�N�X���_�̓s���ɂ��ƂÂ�������
*/
void gg::ggInit(void)
{
  // �o�[�W�����`�F�b�N
  if (atof(reinterpret_cast<const char *>(glGetString(GL_VERSION))) < 2.1)
  {
#if defined(WIN32)
    MessageBox(NULL, L"OpenGL Version 2.1 �ȍ~�ɑΉ������r�f�I�J�[�h���K�v�ł�", L"GG���_", MB_OK);
#else
    std::cerr << "Error: This program requires OpenGL 2.1 or lator." << std::endl;
#endif
    exit(EXIT_FAILURE);
  }

#if defined(WIN32)
  if (glewInit() != GLEW_OK)
  {
    MessageBox(NULL, L"GLEW �̏������Ɏ��s���܂���", L"GG���_", MB_OK);
    exit(EXIT_FAILURE);
  }
#endif

  // Swap Interval �̐ݒ�
  glfwSwapInterval(1);
}

/*
** OpenGL �̃G���[�`�F�b�N
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
** FBO �̃G���[�`�F�b�N
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
** �z��̓��e�� TGA �t�@�C���ɕۑ�
*/
bool gg::ggSaveTga(GLsizei sx, GLsizei sy, unsigned int depth, const GLubyte *buffer, const char *name)
{
  // �t�@�C�����J��
  std::ofstream file(name, std::ios::binary);
  if (file.fail())
  {
    // �J���Ȃ�����
    std::cerr << "Waring: Can't open file: " << name << std::endl;
    return false;
  }

  // �w�b�_�̏�������
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
    // �w�b�_�̏������݂Ɏ��s����
    std::cerr << "Waring: Can't write file header: " << name << std::endl;
    file.close();
    return 0;
  }

  // �f�[�^�̏�������
  file.write(reinterpret_cast<const char *>(buffer), sx * sy * depth);

  // �t�b�^�̏�������
  static const char footer[] = "\0\0\0\0\0\0\0\0TRUEVISION-XFILE.";
  file.write(footer, sizeof footer);

  // �������݃`�F�b�N
  if (file.bad())
  {
    // �������݂Ɏ��s����
    std::cerr << "Waring: Can't write image data: " << name << std::endl;
  }

  // �t�@�C�������
  file.close();

  return true;
}

/*
** �J���[�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
*/
bool gg::ggSaveColor(const char *name)
{
  // ���݂̃r���[�|�[�g�̃T�C�Y�𓾂�
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  // �r���[�|�[�g�̃T�C�Y���̃��������m�ۂ���
  size_t size = viewport[2] * viewport[3] * 3;
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // �������m�ۂɎ��s����
    std::cerr << "Waring: Can't allocate memory to write file: " << name << std::endl;
    return false;
  }

  // ��ʕ\���̊�����҂�
  glFinish();

  // �J���[�o�b�t�@�̓ǂݍ���
  glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3],
    GL_BGR, GL_UNSIGNED_BYTE, buffer);

  // �ǂݍ��񂾃f�[�^���t�@�C���ɏ�������
  bool ret = ggSaveTga(viewport[2], viewport[3], 3, buffer, name);

  // �������̉��
  delete[] buffer;
  
  return ret;
}

/*
** �f�v�X�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
*/
bool gg::ggSaveDepth(const char *name)
{
  // ���݂̃r���[�|�[�g�̃T�C�Y�𓾂�
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  
  // �r���[�|�[�g�̃T�C�Y���̃��������m�ۂ���
  size_t size = viewport[2] * viewport[3];
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // �������m�ۂɎ��s����
    std::cerr << "Waring: Can't allocate memory to write file: " << name << std::endl;
    return false;
  }

  // ��ʕ\���̊�����҂�
  glFinish();

  // �f�v�X�o�b�t�@�̓ǂݍ���
  glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3],
    GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, buffer);
    
  // �ǂݍ��񂾃f�[�^���t�@�C���ɏ�������
  bool ret = ggSaveTga(viewport[2], viewport[3], 1, buffer, name);

  // �������̉��
  delete[] buffer;
  
  return ret;
}

/*
** TGA �t�@�C�� (8/16/24/32bit) �̓ǂݍ���
*/
GLubyte *gg::ggLoadTga(const char *name, GLsizei &width, GLsizei &height, GLenum &format)
{
  // �t�@�C�����J��
  std::ifstream file(name, std::ios::binary);
  if (file.fail())
  {
    // �J���Ȃ�����
    std::cerr << "Waring: Can't open file: " << name << std::endl;
    return 0;
  }

  // �w�b�_�̓ǂݍ���
  unsigned char header[18];
  file.read(reinterpret_cast<char *>(header), sizeof header);
  if (file.bad())
  {
    // �w�b�_�̓ǂݍ��݂Ɏ��s����
    std::cerr << "Waring: Can't read file header: " << name << std::endl;
    file.close();
    return 0;
  }

  // ���ƍ���
  width = header[13] << 8 | header[12];
  height = header[15] << 8 | header[14];

  // �[�x
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

  // �f�[�^�T�C�Y
  size_t size = width * height * depth;

  // �������̊m��
  GLubyte *buffer = 0;
  try
  {
    buffer = new GLubyte[size];
  }
  catch (std::bad_alloc e)
  {
    // ������������Ȃ�����
    std::cerr << "Waring: Too large file: " << name << std::endl;
    file.close();
    return 0;
  }

  // �f�[�^�̓ǂݍ���
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
    // �񈳏k
    file.read(reinterpret_cast<char *>(buffer), size);
  }

  // �ǂݍ��݃`�F�b�N
  if (file.bad())
  {
    // �ǂݍ��݂Ɏ��s����
    std::cerr << "Waring: Can't read image data: " << name << std::endl;
  }

  // �t�@�C�������
  file.close();

  return buffer;
}

/*
** �e�N�X�`���}�b�s���O�p�̃f�[�^�̓ǂݍ���
*/
void gg::ggLoadTexture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLvoid *image)
{
  // �A���t�@�`�����l�������Ă���� 4 �o�C�g���E�ɐݒ�
  glPixelStorei(GL_UNPACK_ALIGNMENT, (format == GL_BGRA || format == GL_RGBA) ? 4 : 1);

  // �e�N�X�`�������蓖�Ă�
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_BYTE, image);

  // �o�C���j�A�i�~�b�v�}�b�v�Ȃ��j�C�G�b�W�ŃN�����v
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

/*
** �e�N�X�`���}�b�s���O�p�� TGA �摜�t�@�C���̓ǂݍ���
*/
bool gg::ggLoadImage(const char *name, GLenum internal)
{
  // �摜�T�C�Y
  GLsizei width, height;

  // �摜�t�H�[�}�b�g
  GLenum format;

  // �摜�̓ǂݍ��ݐ�
  GLubyte *image = ggLoadTga(name, width, height, format);

  // �e�N�X�`���������ւ̓ǂݍ���
  ggLoadTexture(width, height, internal, format, image);

  // �ǂݍ��݂Ɏg�������������J������
  delete[] image;

  return true;
}

/*
** �����}�b�v�p�� TGA �摜�t�@�C���̓ǂݍ���Ŗ@���}�b�v���쐬����
*/
bool gg::ggLoadHeight(const char *name, float nz)
{
  // �摜�T�C�Y
  GLsizei width, height;

  // �摜�t�H�[�}�b�g
  GLenum format;

  // �摜�̓ǂݍ��ݐ�
  GLubyte *hmap = ggLoadTga(name, width, height, format);

  // �摜���ǂݍ��߂Ȃ�������߂�
  if (hmap == 0) return false;

  // �쐬����@���}�b�v
  GLfloat (*nmap)[4] = 0;

  // �������T�C�Y
  GLsizei maxsize = width * height;

  // ���������m�ۂ���
  try
  {
    nmap = new GLfloat[maxsize][4];
  }
  catch (std::bad_alloc e)
  {
    delete[] hmap;
    return false;
  }

  // �@���}�b�v�̍쐬
  for (GLsizei i = 0; i < maxsize; ++i)
  {
    int x = i % width, y = i - x;

    // �אڂ����f�Ƃ̒l�̍���@���̐����ɗp����
    float nx = static_cast<float>(hmap[y + (x + 1) % width] - hmap[i]);
    float ny = static_cast<float>(hmap[(y + width) % maxsize + x] - hmap[i]);

    // �@���̒��������߂Ă���
    float nl = sqrt(nx * nx + ny * ny + nz * nz);

    // �@�������߂�
    nmap[i][0] = nx * 0.5f / nl + 0.5f;
    nmap[i][1] = ny * 0.5f / nl + 0.5f;
    nmap[i][2] = nz * 0.5f / nl + 0.5f;
    nmap[i][3] = hmap[i] * 0.0039215686f; // == 1/255
  }

  // �����}�b�v�̓ǂݍ��݂Ɏg�������������J������
  delete[] hmap;

  // nmap �� GLfloat �Ȃ̂� 4 �o�C�g���E�ɐݒ�
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  // �e�N�X�`�������蓖�Ă�
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nmap);

  // �o�C���j�A�i�~�b�v�}�b�v�Ȃ��j�C�G�b�W�ŃN�����v
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  // �@���}�b�v�̍쐬�Ɏg�������������������
  delete[] nmap;

  return true;
}

/*
** �O�p�`�������ꂽ OBJ �t�@�C����ǂݍ���
*/
bool gg::ggLoadObj(const char *name, GLuint &nv, GLfloat (*&vert)[3], GLfloat (*&norm)[3], GLuint &nf, GLuint (*&face)[3], bool normalize)
{
  // OBJ �t�@�C���̓ǂݍ���
  std::ifstream file(name, std::ios::binary);
  if (file.fail())
  {
    std::cerr << "Error: Can't open OBJ file: " << name << std::endl;
    return false;
  }

  // ��s�ǂݍ��ݗp�̃o�b�t�@
  std::string line;

  // �f�[�^�̐��ƍ��W�l�̍ŏ��l�E�ő�l
  float xmin, xmax, ymin, ymax, zmin, zmax;
  xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);
  nv = nf = 0;

  // �f�[�^��ǂݍ���
  while (std::getline(file, line))
  {
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // ���_�ʒu
      float x, y, z;

      // ���_�ʒu�̓X�y�[�X�ŋ�؂��Ă���
      str >> x >> y >> z;

      // �ʒu�̍ő�l�ƍŏ��l�����߂� (AABB)
      if (x < xmin) xmin = x;
      if (x > xmax) xmax = x;

      if (y < ymin) ymin = y;
      if (y > ymax) ymax = y;

      if (z < zmin) zmin = z;
      if (z > zmax) zmax = z;

      // ���_���̃J�E���g
      ++nv;
    }
    else if (op == "f")
    {
      // �ʐ��̃J�E���g
      ++nf;
    }
  }

  // �������̊m��
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

  // �ʒu�Ƒ傫���̐��K���̂��߂̌W��
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

  // �t�@�C���̊����߂�
  file.clear();
  file.seekg(0L, std::ios::beg);

  // �f�[�^�̓ǂݍ���
  nv = nf = 0;
  while (std::getline(file, line))
  {
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // ���_�ʒu
      float x, y, z;

      // ���_�ʒu�̓X�y�[�X�ŋ�؂��Ă���
      str >> x >> y >> z;

      // �ʒu�Ƒ傫���̐��K��
      vert[nv][0] = (x - cx) * scale;
      vert[nv][1] = (y - cy) * scale;
      vert[nv][2] = (z - cz) * scale;

      // ���_���̃J�E���g
      ++nv;
    }
    else if (op == "f")
    {
      // ���_���W�ԍ�
      std::string l, m, n;

      // ���_���W�ԍ�/�e�N�X�`�����W�ԍ�/�@���ԍ��̑g�����o��
      str >> l >> m >> n;

      // ���_���W�ԍ���������������
      face[nf][0] = atoi(l.c_str()) - 1;
      face[nf][1] = atoi(m.c_str()) - 1;
      face[nf][2] = atoi(n.c_str()) - 1;

      // �ʐ��̃J�E���g
      ++nf;
    }
  }

  // �t�@�C���̓ǂݍ��݃`�F�b�N
  if (file.bad())
  {
    // ���܂��ǂݍ��߂Ȃ�����
    std::cerr << "Warning: Can't read OBJ file: " << name << std::endl;
  }
  file.close();

  // �ʖ@���̎Z�o
  for (GLuint f = 0; f < nf; ++f)
  {
    GLuint v0 = face[f][0], v1 = face[f][1], v2 = face[f][2];

    // v1 - v0, v2 - v0 �����߂�
    GLfloat dx1 = vert[v1][0] - vert[v0][0];
    GLfloat dy1 = vert[v1][1] - vert[v0][1];
    GLfloat dz1 = vert[v1][2] - vert[v0][2];
    GLfloat dx2 = vert[v2][0] - vert[v0][0];
    GLfloat dy2 = vert[v2][1] - vert[v0][1];
    GLfloat dz2 = vert[v2][2] - vert[v0][2];

    // �O�ςɂ��ʖ@�������߂�
    fnorm[f][0] = dy1 * dz2 - dz1 * dy2;
    fnorm[f][1] = dz1 * dx2 - dx1 * dz2;
    fnorm[f][2] = dx1 * dy2 - dy1 * dx2;
  }

  // ���_�@���̒l�� 0 �ɂ��Ă���
  for (GLuint v = 0; v < nv; ++v)
  {
    norm[v][0] = norm[v][1] = norm[v][2] = 0.0f;
  }

  // ���_�@���̎Z�o
  for (GLuint f = 0; f < nf; ++f)
  {
    // ���_���W�ԍ�
    GLuint v0 = face[f][0], v1 = face[f][1], v2 = face[f][2];

    // �ʖ@��
    GLfloat x = fnorm[f][0];
    GLfloat y = fnorm[f][1];
    GLfloat z = fnorm[f][2];

    // �ʖ@���𒸓_�@���ɐώZ����
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

  // ���_�@���̐��K��
  for (GLuint v = 0; v < nv; ++v)
  {
    // ���_�@���̒���
    GLfloat a = sqrt(norm[v][0] * norm[v][0] + norm[v][1] * norm[v][1] + norm[v][2] * norm[v][2]);

    // ���_�@���̐��K��
    if (a != 0.0)
    {
      norm[v][0] /= a;
      norm[v][1] /= a;
      norm[v][2] /= a;
    }
  }

  return true;
}

namespace gg
{
  // �}�e���A��
  struct rgb { float r, g, b; };
  struct mat
  {
    rgb ka;       // ambient
    rgb kd;       // diffuse
    rgb ks;       // specular
    float kshi;   // shininess
  };

  // �ǂݍ��ݗp�̃e���|�����f�[�^�̌`��
  struct vec      // �x�N�g��
  {
    float x, y, z;
  };
  struct vtx      // ���_����
  {
    vec pos;      // ���_�ʒu
    vec norm;     // ���_�@��
  };
  struct fac      // �ʃf�[�^
  {
    GLuint v[3];  // ���_�ԍ�
    GLuint n[3];  // �@���ԍ�
    vec norm;     // �ʖ@��
  };
  struct grp      // �ʃO���[�v
  {
    GLuint b;     // �ʃO���[�v�̊J�n�ԍ�
    GLuint c;     // �ʃO���[�v�̒��_��
    const mat *m; // �ʃO���[�v�̃}�e���A��
    grp(GLuint begin, GLuint count, const mat &material)
    {
      b = begin;
      c = count;
      m = &material;
    }
  };
}

/*
** �O�p�`�������ꂽ OBJ �t�@�C���� MTL �t�@�C����ǂݍ���
*/
bool gg::ggLoadObj(const char *name, GLuint &ng, GLuint (*&group)[2],
  GLfloat (*&ka)[4], GLfloat (*&kd)[4], GLfloat (*&ks)[4], GLfloat *&kshi,
  GLuint &nv, GLfloat (*&vert)[3], GLfloat (*&norm)[3], bool normalize)
{
  // �t�@�C���p�X����f�B���N�g���������o��
  std::string path(name);
  size_t pos = path.find_last_of("/\\");
  std::string dirname = (pos == std::string::npos) ? "" : path.substr(pos + 1);

  // OBJ �t�@�C���̓ǂݍ���
  std::ifstream file(path.c_str());
  if (file.fail())
  {
    std::cerr << "Error: Can't open OBJ file: " << path << std::endl;
    return false;
  }

  // �}�e���A��
  std::map<std::string, mat> mtl;
  static const char defmtl[] = "Default";
  std::string mtlname(defmtl);

  // �f�t�H���g�̃}�e���A��
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

  // �ǂݍ��ݗp�̈ꎞ�L���̈�
  std::vector<vec> _norm;
  std::vector<vtx> _vert;
  std::vector<fac> _face;
  std::vector<grp> _group;

  // ���W�l�̍ŏ��l�E�ő�l
  GLuint groupbegin = 0;
  float xmin, xmax, ymin, ymax, zmin, zmax;
  xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);

  // ��s�ǂݍ��ݗp�̃o�b�t�@
  std::string line;

  // �f�[�^�̓ǂݍ���
  while (std::getline(file, line))
  {
    // �P�s���o���čŏ��̃g�[�N���𖽗� (op) �Ƃ݂Ȃ�
    std::istringstream str(line);
    std::string op;
    str >> op;

    if (op == "v")
    {
      // ���_�ʒu
      vtx v;

      // ���_�ʒu�̓X�y�[�X�ŋ�؂��Ă���
      str >> v.pos.x >> v.pos.y >> v.pos.z;

      // ���_�ʒu�̍ŏ��l�ƍő�l�����߂�
      if (v.pos.x < xmin) xmin = v.pos.x;
      if (v.pos.x > xmax) xmax = v.pos.x;

      if (v.pos.y < ymin) ymin = v.pos.y;
      if (v.pos.y > ymax) ymax = v.pos.y;

      if (v.pos.z < zmin) zmin = v.pos.z;
      if (v.pos.z > zmax) zmax = v.pos.z;

      // ���_�ʒu���L�^����
      _vert.push_back(v);
    }
    else if (op == "vn")
    {
      // ���_�@��
      vec norm;

      // ���_�@���̓X�y�[�X�ŋ�؂��Ă���
      str >> norm.x >> norm.y >> norm.z;

      // ���_�@�����L�^����
      _norm.push_back(norm);
    }
    else if (op == "f")
    {
      // �� (�O�p�`) �f�[�^
      fac f;

      //�@�O���_�̂��ꂼ��ɂ���
      for (int i = 0; i < 3; ++i)
      {
        // �P���ڎ��o��
        std::string tmp;
        str >> tmp;

        // ���ڂ̍ŏ��̗v�f�͒��_���W�ԍ� (0 ����n�܂�)
        f.v[i] = atoi(tmp.c_str()) - 1;
        f.n[i] = 0;

        // �c��̍��ڂ����o��
        size_t pos = tmp.find('/', 0);
        if (pos != std::string::npos)
        {
          // ��ڂ̍��ڂ͔�΂�
          pos = tmp.find('/', pos + 1);
          if (pos != std::string::npos)
          {
            // �O�ڂ̍��ڂ͖@���ԍ� (0 �Ȃ�@���̊��蓖�ĂȂ�)
            f.n[i] = atoi(tmp.substr(pos + 1).c_str());
          }
        }
      }

      // �ʃf�[�^�̋L�^��
      _face.push_back(f);
    }
    else if (op == "usemtl")
    {
      // �ʃO���[�v�̖ʐ�
      GLuint groupcount = static_cast<GLuint>(_face.size()) * 3 - groupbegin;
      if (groupcount > 0)
      {
        // �ʃO���[�v�̒��_�f�[�^�̊J�n�ԍ��Ɛ��C����т��̃}�e���A�����L�^����
        grp b(groupbegin, groupcount, mtl[mtlname]);
        _group.push_back(b);

        // ���̖ʃO���[�v�̊J�n�ԍ������߂Ă���
        groupbegin += groupcount;
      }

      // �}�e���A�����̎��o��
      str >> mtlname;

      // �}�e���A���̑��݃`�F�b�N
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
      // MTL �t�@�C���̃p�X�������
      str >> std::ws;
      std::string mtlpath;
      std::getline(str, mtlpath);
      mtlpath = dirname + mtlpath;

      // MTL �t�@�C���̓ǂݍ���
      std::ifstream mtlfile(mtlpath.c_str(), std::ios::binary);
      if (mtlfile.fail())
      {
        std::cerr << "Warning: Can't open MTL file: " << mtlpath << std::endl;
      }
      else
      {
        // ��s�ǂݍ��ݗp�̃o�b�t�@
        std::string mtlline;

        // �}�e���A���f�[�^��ǂݍ���
        while (std::getline(mtlfile, mtlline))
        {
          std::istringstream mtlstr(mtlline);
          std::string mtlop;
          mtlstr >> mtlop;

          if (mtlop == "newmtl")
          {
            // �V�K�}�e���A�������o�͂���
            mtlstr >> mtlname;
            std::cerr << "newmtl: " << mtlname << std::endl;
          }
          else if (mtlop == "Ka")
          {
            // �����̔��ˌW����o�^����
            mtlstr >> mtl[mtlname].ka.r >> mtl[mtlname].ka.g >> mtl[mtlname].ka.b;
          }
          else if (mtlop == "Kd")
          {
            // �g�U���ˌW����o�^����
            mtlstr >> mtl[mtlname].kd.r >> mtl[mtlname].kd.g >> mtl[mtlname].kd.b;
          }
          else if (mtlop == "Ks")
          {
            // ���ʔ��ˌW����o�^����
            mtlstr >> mtl[mtlname].ks.r >> mtl[mtlname].ks.g >> mtl[mtlname].ks.b;
          }
          else if (mtlop == "Ns")
          {
            // �P���W����o�^����
            float kshi;
            mtlstr >> kshi;
            mtl[mtlname].kshi = kshi * 0.1f;
          }
        }

        // MTL �t�@�C���̓ǂݍ��݃`�F�b�N
        if (mtlfile.bad())
        {
          // MTL �t�@�C�������܂��ǂݍ��߂Ȃ�����
          std::cerr << "Warning: Can't read MTL file: " << mtlpath << std::endl;
        }
        mtlfile.close();
      }
    }
  }

  // �t�@�C���̓ǂݍ��݃`�F�b�N
  if (file.bad())
  {
    // OBJ �t�@�C�������܂��ǂݍ��߂Ȃ�����
    std::cerr << "Warning: Can't read OBJ file: " << path << std::endl;
  }
  else
  {
    // �Ō�̖ʃO���[�v�̖ʐ�
    GLuint groupcount = static_cast<GLuint>(_face.size()) * 3 - groupbegin;
    if (groupcount > 0)
    {
      // �Ō�̖ʃO���[�v�̒��_�f�[�^�̊J�n�ԍ��Ɛ��C����т��̃}�e���A�����L�^����
      grp b(groupbegin, groupcount, mtl[mtlname]);
      _group.push_back(b);
    }
  }
  file.close();

  // �K�v�Ȗʐ��C���_���C�O���[�v��
  GLuint nf = static_cast<GLuint>(_face.size());
  nv = nf * 3;
  ng = static_cast<GLuint>(_group.size());

  // �������̊m��
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

  // �ʒu�Ƒ傫���𐳋K�����邽�߂̌W��
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

  // �ʖ@���̎Z�o
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // ���_���W�ԍ�
    GLuint v0 = f->v[0], v1 = f->v[1], v2 = f->v[2];

    // v1 - v0, v2 - v0 �����߂�
    GLfloat dx1 = _vert[v1].pos.x - _vert[v0].pos.x;
    GLfloat dy1 = _vert[v1].pos.y - _vert[v0].pos.y;
    GLfloat dz1 = _vert[v1].pos.z - _vert[v0].pos.z;
    GLfloat dx2 = _vert[v2].pos.x - _vert[v0].pos.x;
    GLfloat dy2 = _vert[v2].pos.y - _vert[v0].pos.y;
    GLfloat dz2 = _vert[v2].pos.z - _vert[v0].pos.z;

    // �O�ςɂ��ʖ@�������߂�
    f->norm.x = dy1 * dz2 - dz1 * dy2;
    f->norm.y = dz1 * dx2 - dx1 * dz2;
    f->norm.z = dx1 * dy2 - dy1 * dx2;
  }

  // ���_�@���̒l�� 0 �ɂ��Ă���
  for (std::vector<vtx>::iterator v = _vert.begin(); v != _vert.end(); ++v)
  {
    v->norm.x = v->norm.y = v->norm.z = 0.0f;
  }

  // ���_�@���̎Z�o
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // ���_���W�ԍ�
    GLuint v0 = f->v[0], v1 = f->v[1], v2 = f->v[2];

    // �ʖ@��
    GLfloat x = f->norm.x;
    GLfloat y = f->norm.y;
    GLfloat z = f->norm.z;

    // �ʖ@���𒸓_�@���ɐώZ����
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

  // ���_�@���̐��K��
  for (std::vector<vtx>::iterator v = _vert.begin(); v != _vert.end(); ++v)
  {
    // ���_�@���̒���
    GLfloat a = sqrt(v->norm.x * v->norm.x + v->norm.y * v->norm.y + v->norm.z * v->norm.z);

    // ���_�@���𐳋K������
    if (a != 0.0)
    {
      v->norm.x /= a;
      v->norm.y /= a;
      v->norm.z /= a;
    }
  }

  // �ʂ��Ƃ̒��_�f�[�^�̍쐬
  nv = 0;
  for (std::vector<fac>::iterator f = _face.begin(); f != _face.end(); ++f)
  {
    // �ʖ@��
    GLfloat x = f->norm.x, y = f->norm.y, z = f->norm.z;

    // �ʖ@���̒���
    GLfloat a = sqrt(x * x + y * y + z * z);

    // �ʖ@���̐��K��
    if (a != 0.0)
    {
      x /= a;
      y /= a;
      z /= a;
    }

    // �O���_�̂��ꂼ��ɂ���
    for (int i = 0; i < 3; ++i)
    {
      // ���_���W�ԍ��ƒ��_�@���ԍ�
      GLuint fv = f->v[i], fn = f->n[i];

      // ���_���W�𐳋K�����ēo�^
      vert[nv][0] = (_vert[fv].pos.x - cx) * scale;
      vert[nv][1] = (_vert[fv].pos.y - cy) * scale;
      vert[nv][2] = (_vert[fv].pos.z - cz) * scale;

      // �@���ԍ��� 0 �Ȃ�
      if (fn == 0)
      {
        // ���_�@����ۑ�����
        norm[nv][0] = _vert[fv].norm.x;
        norm[nv][1] = _vert[fv].norm.y;
        norm[nv][2] = _vert[fv].norm.z;
      }
      else
      {
        // �ǂݍ��܂ꂽ���_�@�����g��
        --fn;
        norm[nv][0] = _norm[fn].x;
        norm[nv][1] = _norm[fn].y;
        norm[nv][2] = _norm[fn].z;
      }

      // ���_���̃J�E���g
      ++nv;
    }
  }

  // �ʃO���[�v�f�[�^�̍쐬
  ng = 0;
  for (std::vector<grp>::iterator g = _group.begin(); g != _group.end(); ++g)
  {
    // �ʃO���[�v�̍ŏ��̒��_�ʒu�ԍ�
    group[ng][0] = g->b;

    // �ʃO���[�v�̒��_�f�[�^�̐�
    group[ng][1] = g->c;

    // �ʃO���[�v�̊����ɑ΂��锽�ˌW��
    ka[ng][0] = g->m->ka.r;
    ka[ng][1] = g->m->ka.g;
    ka[ng][2] = g->m->ka.b;
    ka[ng][3] = 1.0f;

    // �ʃO���[�v�̊g�U���ˌW��
    kd[ng][0] = g->m->kd.r;
    kd[ng][1] = g->m->kd.g;
    kd[ng][2] = g->m->kd.b;
    kd[ng][3] = 1.0f;

    // �ʃO���[�v�̋��ʔ��ˌW��
    ks[ng][0] = g->m->ks.r;
    ks[ng][1] = g->m->ks.g;
    ks[ng][2] = g->m->ks.b;
    ks[ng][3] = 1.0f;

    // �ʃO���[�v�̋P���W��
    kshi[ng] = g->m->kshi;

    // �ʃO���[�v�̐�
    ++ng;
  }

  return true;
}

/*
** �V�F�[�_�[�̃\�[�X�v���O�������������ɓǂݍ���
*/
static bool readShaderSource(GLuint shader, const char *name)
{
  bool ret = true; // �I���X�e�[�^�X�itrue �Ȃ�G���[�j

  // �\�[�X�t�@�C�����J��
  std::ifstream file(name, std::ios::binary);

  if (file.fail())
  {
    // �J���Ȃ�����
    std::cerr << "Error: Can't open source file: " << name << std::endl;
  }
  else
  {
    // �t�@�C���̖����Ɉړ������݈ʒu�i���t�@�C���T�C�Y�j�𓾂�
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // �t�@�C���T�C�Y�̃��������m��
    char *buffer = new GLchar[length];

    // �t�@�C����擪����ǂݍ���
    file.seekg(0L, std::ios::beg);
    file.read(buffer, length);

    if (file.bad())
    {
      // ���܂��ǂݍ��߂Ȃ�����
      std::cerr << "Error: Could not read souce file: " << name << std::endl;
    }
    else {
      // �V�F�[�_�̃\�[�X�v���O�����̃V�F�[�_�I�u�W�F�N�g�ւ̓ǂݍ���
      const GLchar *source[] = { buffer };
      glShaderSource(shader, 1, source, &length);
      ret = false;
    }
    file.close();

    // �ǂݍ��݂Ɏg�������������J������
    delete[] buffer;
  }

  return ret;
}

/*
** �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
*/
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // �R���p�C�����ʂ��擾����
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

  // �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return (GLboolean)status;
}

/*
** �v���O�����I�u�W�F�N�g�̃����N���ʂ�\������
*/
static GLboolean printProgramInfoLog(GLuint program)
{
  // �����N���ʂ��擾����
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

  // �V�F�[�_�̃����N���̃��O�̒������擾����
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // �V�F�[�_�̃����N���̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return (GLboolean)status;
}

/*
** �V�F�[�_�[�\�[�X�t�@�C���̓ǂݍ���
*/
GLuint gg::ggLoadShader(
  const char *vert,       // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
  const char *frag,       // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C����
  const char *geom,       // �W�I���g���V�F�[�_�̃\�[�X�t�@�C����
  GLint nvarying,         // Transform Feedback ���� varying �ϐ��̐�
  const char **varyings   // Transform Feedback ���� varying �ϐ��̃��X�g
  )
{
  // �V�F�[�_�v���O�����̍쐬
  GLuint program = glCreateProgram();

  if (program > 0)
  {
    // �o�[�e�b�N�X�V�F�[�_�̍쐬
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

    // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�����̓ǂݍ���
    if (readShaderSource(vertShader, vert))
    {
      glDeleteShader(vertShader);
      glDeleteProgram(program);
      return 0;
    }

    // �o�[�e�b�N�X�V�F�[�_�̃R���p�C��
    glCompileShader(vertShader);
    if (printShaderInfoLog(vertShader, vert) == GL_FALSE)
    {
      glDeleteShader(vertShader);
      glDeleteProgram(program);
      return 0;
    }

    // �o�[�e�b�N�X�V�F�[�_�V�F�[�_�v���O�����ւ̑g�ݍ���
    glAttachShader(program, vertShader);
    glDeleteShader(vertShader);

    if (frag)
    {
      // �t���O�����g�V�F�[�_�̍쐬
      GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

      // �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̓ǂݍ���
      if (readShaderSource(fragShader, frag))
      {
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return 0;
      }

      // �t���O�����g�V�F�[�_�̃R���p�C��
      glCompileShader(fragShader);
      if (printShaderInfoLog(fragShader, frag) == GL_FALSE)
      {
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return 0;
      }

      // �t���O�����g�V�F�[�_�V�F�[�_�v���O�����ւ̑g�ݍ���
      glAttachShader(program, fragShader);
      glDeleteShader(fragShader);
    }

    if (geom)
    {
      // �W�I���g���V�F�[�_�̍쐬
      GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);

      // �W�I���g���V�F�[�_�̃\�[�X�v���O�����̓ǂݍ���
      if (readShaderSource(geomShader, geom))
      {
        glDeleteShader(geomShader);
        glDeleteProgram(program);
        return 0;
      }

      // �W�I���g���V�F�[�_�̃R���p�C��
      glCompileShader(geomShader);
      if (printShaderInfoLog(geomShader, geom) == GL_FALSE)
      {
        glDeleteShader(geomShader);
        glDeleteProgram(program);
        return 0;
      }

      // �W�I���g���V�F�[�_�̃V�F�[�_�v���O�����ւ̑g�ݍ���
      glAttachShader(program, geomShader);
      glDeleteShader(geomShader);
    }

    // feedback �Ɏg�� varying �ϐ����w�肷��
    if (nvarying > 0) glTransformFeedbackVaryings(program, nvarying, varyings, GL_SEPARATE_ATTRIBS);

    // �V�F�[�_�v���O�����̃����N
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
** �ϊ��s��F�s��ƃx�N�g���̐� c �� a �~ b
*/
void gg::GgMatrix::projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const
{
  for (int i = 0; i < 4; ++i)
  {
    c[i] = a[0 + i] * b[0] + a[4 + i] * b[1] + a[8 + i] * b[2] + a[12 + i] * b[3];
  }
}

/*
** �ϊ��s��F�s��ƍs��̐� c �� a �~ b
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
** �ϊ��s��F�P�ʍs���ݒ肷��
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
** �ϊ��s��F���s�ړ��ϊ��s���ݒ肷��
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
** �ϊ��s��F�g��k���ϊ��s���ݒ肷��
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
** �ϊ��s��Fx �����S�̉�]�ϊ��s���ݒ肷��
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
** �ϊ��s��Fy �����S�̉�]�ϊ��s���ݒ肷��
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
** �ϊ��s��Fz �����S�̉�]�ϊ��s���ݒ肷��
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
** �ϊ��s��F�C�ӎ����S�̉�]�ϊ��s���ݒ肷��
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
** �ϊ��s��F�]�u�s���ݒ肷��
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
** �ϊ��s��F�t�s���ݒ肷��
*/
gg::GgMatrix &gg::GgMatrix::loadInvert(const GgMatrix &m)
{
  GLfloat lu[20], *plu[4];
  const GLfloat *marray = m.array;

  // j �s�̗v�f�̒l�̐�Βl�̍ő�l�� plu[j][4] �ɋ��߂�
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

  // �s�{�b�g���l������ LU ����
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

  // LU ��������t�s������߂�
  for (int k = 0; k < 4; ++k)
  {
    // array �ɒP�ʍs���ݒ肷��
    for (int i = 0; i < 4; ++i)
    {
      array[i * 4 + k] = (plu[i] == lu + k * 5) ? 1.0f : 0.0f;
    }
    // lu ����t�s������߂�
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
** �ϊ��s��F�@���ϊ��s���ݒ肷��
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
** �ϊ��s��F����ϊ��s���ݒ肷��
*/
gg::GgMatrix &gg::GgMatrix::loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz)
{
  GLfloat l;

  // z �� = e - t
  tx = ex - tx;
  ty = ey - ty;
  tz = ez - tz;
  l = sqrt(tx * tx + ty * ty + tz * tz);
  if (l == 0.0f) return *this;
  array[ 2] = tx / l;
  array[ 6] = ty / l;
  array[10] = tz / l;

  // x �� = u x z ��
  tx = uy * array[10] - uz * array[ 6];
  ty = uz * array[ 2] - ux * array[10];
  tz = ux * array[ 6] - uy * array[ 2];
  l = sqrt(tx * tx + ty * ty + tz * tz);
  if (l == 0.0f) return *this;
  array[ 0] = tx / l;
  array[ 4] = ty / l;
  array[ 8] = tz / l;

  // y �� = z �� x x ��
  array[ 1] = array[ 6] * array[ 8] - array[10] * array[ 4];
  array[ 5] = array[10] * array[ 0] - array[ 2] * array[ 8];
  array[ 9] = array[ 2] * array[ 4] - array[ 6] * array[ 0];

  // ���s�ړ�
  array[12] = -(ex * array[ 0] + ey * array[ 4] + ez * array[ 8]);
  array[13] = -(ex * array[ 1] + ey * array[ 5] + ez * array[ 9]);
  array[14] = -(ex * array[ 2] + ey * array[ 6] + ez * array[10]);

  // �c��
  array[ 3] = array[ 7] = array[11] = 0.0f;
  array[15] = 1.0f;

  return *this;
}

/*
** �ϊ��s��F���s���e�ϊ��s���ݒ肷��
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
** �ϊ��s��F�������e�ϊ��s���ݒ肷��
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
** �ϊ��s��F��p���瓧�����e�ϊ��s���ݒ肷��
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
** �ϊ��s��F����ϊ��s����悶��i���_�̈ړ��j
*/
gg::GgMatrix &gg::GgMatrix::lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz)
{
  GgMatrix m;

  m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz);
  multiply(m);

  return *this;
}

/*
** �ϊ��s��F���s���e�ϊ��s����悶��
*/
gg::GgMatrix &gg::GgMatrix::orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadOrthogonal(left, right, bottom, top, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** �ϊ��s��F�������e�ϊ��s����悶��
*/
gg::GgMatrix &gg::GgMatrix::frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadFrustum(left, right, bottom, top, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** �ϊ��s��F��p���狁�߂��������e�ϊ��s����悶��
*/
gg::GgMatrix &gg::GgMatrix::perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
  GgMatrix m;

  m.loadPerspective(fovy, aspect, zNear, zFar);
  multiply(m);

  return *this;
}

/*
** �l�����F�l���� p, q �̘a�� r �ɋ��߂�
*/
void gg::GgQuaternion::add(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[0] + q[0];
  r[1] = p[1] + q[1];
  r[2] = p[2] + q[2];
  r[3] = p[3] + q[3];
}

/*
** �l�����F�l���� p, q �̍��� r �ɋ��߂�
*/
void gg::GgQuaternion::subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[0] - q[0];
  r[1] = p[1] - q[1];
  r[2] = p[2] - q[2];
  r[3] = p[3] - q[3];
}

/*
** �l�����F�l���� p, q �̐ς� r �ɋ��߂�
*/
void gg::GgQuaternion::multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const
{
  r[0] = p[1] * q[2] - p[2] * q[1] + p[0] * q[3] + p[3] * q[0];
  r[1] = p[2] * q[0] - p[0] * q[2] + p[1] * q[3] + p[3] * q[1];
  r[2] = p[0] * q[1] - p[1] * q[0] + p[2] * q[3] + p[3] * q[2];
  r[3] = p[3] * q[3] - p[0] * q[0] - p[1] * q[1] - p[2] * q[2];
}

/*
** �l�����F�l���� q ���\���ϊ��s��� m �ɋ��߂�
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
** �l�����F��]�ϊ��s�� m ���\���l������ q �ɋ��߂�
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
** �l�����F���ʐ��`��� p �� q �� r �� t �ŕ�Ԃ����l���������߂�
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
** �l�����F(x, y, z) �����Ƃ��p�x a ��]����l���������߂�
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
** �l�����F�I�C���[�p (h, p, r) �ɂ��ƂÂ��Ďl���������߂�
*/
gg::GgQuaternion &gg::GgQuaternion::loadEuler(GLfloat h, GLfloat p, GLfloat r)
{
  return loadRotate(-sin(h) * cos(p), sin(p), cos(h) * cos(p), r);
}

/*
** �l�����F�m����
*/
GLfloat gg::GgQuaternion::norm(void) const
{
  return sqrt(array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3]);
}

/*
** �l�����F�l���� q �̋����� r �ɋ��߂�
*/
gg::GgQuaternion gg::GgQuaternion::conjugate(void) const
{
  GgQuaternion t(-array[0], -array[1], -array[2], array[3]);

  return t;
}

/*
** �l�����F�l���� q �̋t�� r �ɋ��߂�
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
** �l�����F���K��
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
** �ȈՃg���b�N�{�[�������F�R���X�g���N�^
*/
gg::GgTrackball::GgTrackball(void)
{
  // �h���b�O���ł͂Ȃ�
  drag = false;

  // �P�ʃN�H�[�^�[�j�I��
  cq.loadIdentity();

  // ��]�s��̏�����
  cq.getMatrix(rt);
}

/*
** �ȈՃg���b�N�{�[�������F�g���b�N�{�[������̈�̐ݒ�
**
**    Reshape �R�[���o�b�N (resize) �̒��Ŏ��s����
**    (w, h): �E�B���h�E�T�C�Y
*/
void gg::GgTrackball::region(int w, int h)
{
  // �}�E�X�|�C���^�ʒu�̃E�B���h�E���̑��ΓI�ʒu�ւ̊��Z�p
  sx = 1.0f / static_cast<float>(w);
  sy = 1.0f / static_cast<float>(h);
}

/*
** �ȈՃg���b�N�{�[�������F�h���b�O�J�n���̏���
**
**    �}�E�X�{�^�����������Ƃ��Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void gg::GgTrackball::start(int x, int y)
{
  // �h���b�O�J�n
  drag = true;

  // �h���b�O�J�n�_���L�^����
  cx = x;
  cy = y;
}

/*
** �ȈՃg���b�N�{�[�������F�h���b�O���̏���
**
**    �}�E�X�̃h���b�O���Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void gg::GgTrackball::motion(int x, int y)
{
  if (drag)
  {
    float dx, dy, a;

    // �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ�
    dx = (x - cx) * sx;
    dy = (y - cy) * sy;

    // �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̋���
    a = sqrt(dx * dx + dy * dy);

    if (a != 0.0)
    {
      // ��]���Ɖ�]�p����l���������
      GgQuaternion dq;
      dq.loadRotate(dy, dx, 0.0f, a * 6.283185f);

      // ���݂̉�]�̎l�����ɍ�����l�������|���č�������
      tq = dq * cq;

      // ���������l���������]�̕ϊ��s������߂�
      tq.getMatrix(rt);
    }
  }
}

/*
** �ȈՃg���b�N�{�[�������F��~���̏���
**
**    �}�E�X�{�^���𗣂����Ƃ��Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void gg::GgTrackball::stop(int x, int y)
{
  // �h���b�O�I���_�ɂ������]�����߂�
  motion(x, y);

  // ���݂̉�]��\���l�����𐳋K�����ĕۑ�����
  cq = tq.normalize();

  // �h���b�O�I��
  drag = false;
}

/*
** �|�C���g�F�`��
*/
void gg::GgPoints::draw(void) const
{
  // �V�F�[�_�v���O�����̎g�p���J�n����
  getShader()->use(pbuf());

  // �}�`��`�悷��
  glDrawArrays(mode, 0, pnum());

  // �V�F�[�_�v���O�����̎g�p���I������
  getShader()->unuse();
}

/*
** �|���S���F�`��
*/
void gg::GgTriangles::draw(void) const
{
  // �V�F�[�_�v���O�����̎g�p���J�n����
  getShader()->use(pbuf(), nbuf());

  // �}�`��`�悷��
  glDrawArrays(mode, 0, pnum());

  // �V�F�[�_�v���O�����̎g�p���I������
  getShader()->unuse();
}

/*
** �I�u�W�F�N�g�F�`��
*/
void gg::GgElements::draw(void) const
{
  // �V�F�[�_�v���O�����̎g�p���J�n����
  getShader()->use(pbuf(), nbuf());

  // �C���f�b�N�X�Ƀo�b�t�@�I�u�W�F�N�g���w�肷��
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fbuf());

  // �}�`��`�悷��
  glDrawElements(mode, fnum() * 3, GL_UNSIGNED_INT, 0);

  // �o�b�t�@�I�u�W�F�N�g�̎w�����������
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // �V�F�[�_�v���O�����̎g�p���I������
  getShader()->unuse();
}

/*
** ����̃|�C���g
*/
gg::GgPoints *gg::ggPointSphere(GLuint nv, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat radius)
{
  // �������̊m��
  GLfloat (*vert)[3] = new GLfloat[nv][3];

  // �_�̐���
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

  // �|�C���g�̍쐬
  GgPoints *points = new gg::GgPoints(nv, vert);

  // ��Ɨp�̃������̉��
  delete[] vert;

  return points;
}

/*
** ��`
*/
gg::GgTriangles *gg::ggRectangle(GLfloat width, GLfloat height)
{
  // ��ƂȂ�`��
  static const GLfloat p[][2] =
  {
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f },
  };

  // �������̊m��
  GLfloat vert[4][3];
  GLfloat norm[4][3];

  // ���_�ʒu�̌v�Z
  for (int v = 0; v < 4; ++v)
  {
    vert[v][0] = p[v][0] * width;
    vert[v][1] = p[v][1] * height;
    vert[v][2] = 0.0f;

    norm[v][0] = 0.0f;
    norm[v][1] = 0.0f;
    norm[v][2] = 1.0f;
  }

  // �|���S���̍쐬
  GgTriangles *rectangle = new gg::GgTriangles(4, vert, norm);
  rectangle->setMode(GL_TRIANGLE_FAN);

  return rectangle;
}

/*
** �ȉ~
*/
gg::GgTriangles *gg::ggEllipse(GLfloat width, GLfloat height, GLuint slices)
{
  // �������̊m��
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

  // ���_�ʒu�̌v�Z
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

  // �|���S���̍쐬
  GgTriangles *ellipse = new gg::GgTriangles(slices, vert, norm);
  ellipse->setMode(GL_TRIANGLE_FAN);

  // ��Ɨp�̃������̉��
  delete[] vert;
  delete[] norm;

  return ellipse;
}

/*
** �O�p�`�������ꂽ Alias OBJ �t�@�C�� (Arrays �`��)
*/
gg::GgTriangles *gg::ggArraysObj(const char *name, bool normalize)
{
  GLuint ng, nv;
  GLuint (*group)[2];
  GLfloat (*ka)[4], (*kd)[4], (*ks)[4], *kshi;
  GLfloat (*vert)[3], (*norm)[3];

  if (!ggLoadObj(name, ng, group, ka, kd, ks, kshi, nv, vert, norm, normalize)) return 0;

  // �I�u�W�F�N�g�̍쐬
  GgTriangles *obj = new gg::GgTriangles(nv, vert, norm);

  // ��Ɨp�̃������̉��
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
** �O�p�`�������ꂽ Alias OBJ �t�@�C�� (Elements �`��)
*/
gg::GgElements *gg::ggElementsObj(const char *name, bool normalize)
{
  GLuint nv, nf;
  GLfloat (*vert)[3], (*norm)[3];
  GLuint (*face)[3];

  if (!ggLoadObj(name, nv, vert, norm, nf, face, normalize)) return 0;

  // �I�u�W�F�N�g�̍쐬
  GgElements *obj = new gg::GgElements(nv, vert, norm, nf, face);

  // ��Ɨp�̃������̉��
  delete[] vert;
  delete[] norm;
  delete[] face;

  return obj;
}
