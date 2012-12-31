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
#  pragma comment(lib, "GLFW.lib")
#  include <GL/glfw.h>
#  include "glext.h"

extern PFNGLBLENDCOLORPROC glBlendColor;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;
extern PFNGLCOLORTABLEPROC glColorTable;
extern PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv;
extern PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv;
extern PFNGLCOPYCOLORTABLEPROC glCopyColorTable;
extern PFNGLGETCOLORTABLEPROC glGetColorTable;
extern PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv;
extern PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv;
extern PFNGLCOLORSUBTABLEPROC glColorSubTable;
extern PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable;
extern PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D;
extern PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D;
extern PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf;
extern PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv;
extern PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri;
extern PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv;
extern PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D;
extern PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D;
extern PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter;
extern PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv;
extern PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv;
extern PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter;
extern PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D;
extern PFNGLGETHISTOGRAMPROC glGetHistogram;
extern PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv;
extern PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv;
extern PFNGLGETMINMAXPROC glGetMinmax;
extern PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv;
extern PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv;
extern PFNGLHISTOGRAMPROC glHistogram;
extern PFNGLMINMAXPROC glMinmax;
extern PFNGLRESETHISTOGRAMPROC glResetHistogram;
extern PFNGLRESETMINMAXPROC glResetMinmax;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC glSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;
extern PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;
extern PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
extern PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;
extern PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC glPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
extern PFNGLFOGCOORDFPROC glFogCoordf;
extern PFNGLFOGCOORDFVPROC glFogCoordfv;
extern PFNGLFOGCOORDDPROC glFogCoordd;
extern PFNGLFOGCOORDDVPROC glFogCoorddv;
extern PFNGLFOGCOORDPOINTERPROC glFogCoordPointer;
extern PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b;
extern PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv;
extern PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d;
extern PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv;
extern PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f;
extern PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv;
extern PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i;
extern PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv;
extern PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s;
extern PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv;
extern PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub;
extern PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv;
extern PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui;
extern PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv;
extern PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us;
extern PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv;
extern PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer;
extern PFNGLWINDOWPOS2DPROC glWindowPos2d;
extern PFNGLWINDOWPOS2DVPROC glWindowPos2dv;
extern PFNGLWINDOWPOS2FPROC glWindowPos2f;
extern PFNGLWINDOWPOS2FVPROC glWindowPos2fv;
extern PFNGLWINDOWPOS2IPROC glWindowPos2i;
extern PFNGLWINDOWPOS2IVPROC glWindowPos2iv;
extern PFNGLWINDOWPOS2SPROC glWindowPos2s;
extern PFNGLWINDOWPOS2SVPROC glWindowPos2sv;
extern PFNGLWINDOWPOS3DPROC glWindowPos3d;
extern PFNGLWINDOWPOS3DVPROC glWindowPos3dv;
extern PFNGLWINDOWPOS3FPROC glWindowPos3f;
extern PFNGLWINDOWPOS3FVPROC glWindowPos3fv;
extern PFNGLWINDOWPOS3IPROC glWindowPos3i;
extern PFNGLWINDOWPOS3IVPROC glWindowPos3iv;
extern PFNGLWINDOWPOS3SPROC glWindowPos3s;
extern PFNGLWINDOWPOS3SVPROC glWindowPos3sv;
extern PFNGLGENQUERIESPROC glGenQueries;
extern PFNGLDELETEQUERIESPROC glDeleteQueries;
extern PFNGLISQUERYPROC glIsQuery;
extern PFNGLBEGINQUERYPROC glBeginQuery;
extern PFNGLENDQUERYPROC glEndQuery;
extern PFNGLGETQUERYIVPROC glGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLISBUFFERPROC glIsBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
extern PFNGLMAPBUFFERPROC glMapBuffer;
extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC glGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC glIsProgram;
extern PFNGLISSHADERPROC glIsShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;
extern PFNGLCOLORMASKIPROC glColorMaski;
extern PFNGLGETBOOLEANI_VPROC glGetBooleani_v;
extern PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
extern PFNGLENABLEIPROC glEnablei;
extern PFNGLDISABLEIPROC glDisablei;
extern PFNGLISENABLEDIPROC glIsEnabledi;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;
extern PFNGLCLAMPCOLORPROC glClampColor;
extern PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender;
extern PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender;
extern PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i;
extern PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i;
extern PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i;
extern PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv;
extern PFNGLGETUNIFORMUIVPROC glGetUniformuiv;
extern PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC glUniform1ui;
extern PFNGLUNIFORM2UIPROC glUniform2ui;
extern PFNGLUNIFORM3UIPROC glUniform3ui;
extern PFNGLUNIFORM4UIPROC glUniform4ui;
extern PFNGLUNIFORM1UIVPROC glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC glUniform4uiv;
extern PFNGLTEXPARAMETERIIVPROC glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv;
extern PFNGLCLEARBUFFERIVPROC glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC glClearBufferfi;
extern PFNGLGETSTRINGIPROC glGetStringi;
extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
extern PFNGLTEXBUFFERPROC glTexBuffer;
extern PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;
extern PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;
extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;
extern PFNGLMINSAMPLESHADINGPROC glMinSampleShading;
extern PFNGLBLENDEQUATIONIPROC glBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC glBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei;
extern PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
extern PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC glIsVertexArray;
extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;
extern PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName;
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
extern PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex;
extern PFNGLPROVOKINGVERTEXPROC glProvokingVertex;
extern PFNGLFENCESYNCPROC glFenceSync;
extern PFNGLISSYNCPROC glIsSync;
extern PFNGLDELETESYNCPROC glDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC glClientWaitSync;
extern PFNGLWAITSYNCPROC glWaitSync;
extern PFNGLGETINTEGER64VPROC glGetInteger64v;
extern PFNGLGETSYNCIVPROC glGetSynciv;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC glSampleMaski;
extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed;
extern PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex;
extern PFNGLGENSAMPLERSPROC glGenSamplers;
extern PFNGLDELETESAMPLERSPROC glDeleteSamplers;
extern PFNGLISSAMPLERPROC glIsSampler;
extern PFNGLBINDSAMPLERPROC glBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv;
extern PFNGLQUERYCOUNTERPROC glQueryCounter;
extern PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v;
extern PFNGLVERTEXP2UIPROC glVertexP2ui;
extern PFNGLVERTEXP2UIVPROC glVertexP2uiv;
extern PFNGLVERTEXP3UIPROC glVertexP3ui;
extern PFNGLVERTEXP3UIVPROC glVertexP3uiv;
extern PFNGLVERTEXP4UIPROC glVertexP4ui;
extern PFNGLVERTEXP4UIVPROC glVertexP4uiv;
extern PFNGLTEXCOORDP1UIPROC glTexCoordP1ui;
extern PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv;
extern PFNGLTEXCOORDP2UIPROC glTexCoordP2ui;
extern PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv;
extern PFNGLTEXCOORDP3UIPROC glTexCoordP3ui;
extern PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv;
extern PFNGLTEXCOORDP4UIPROC glTexCoordP4ui;
extern PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv;
extern PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui;
extern PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv;
extern PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui;
extern PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv;
extern PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui;
extern PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv;
extern PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui;
extern PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv;
extern PFNGLNORMALP3UIPROC glNormalP3ui;
extern PFNGLNORMALP3UIVPROC glNormalP3uiv;
extern PFNGLCOLORP3UIPROC glColorP3ui;
extern PFNGLCOLORP3UIVPROC glColorP3uiv;
extern PFNGLCOLORP4UIPROC glColorP4ui;
extern PFNGLCOLORP4UIVPROC glColorP4uiv;
extern PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui;
extern PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv;
extern PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui;
extern PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv;
extern PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui;
extern PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv;
extern PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui;
extern PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv;
extern PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui;
extern PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv;
extern PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;
extern PFNGLUNIFORM1DPROC glUniform1d;
extern PFNGLUNIFORM2DPROC glUniform2d;
extern PFNGLUNIFORM3DPROC glUniform3d;
extern PFNGLUNIFORM4DPROC glUniform4d;
extern PFNGLUNIFORM1DVPROC glUniform1dv;
extern PFNGLUNIFORM2DVPROC glUniform2dv;
extern PFNGLUNIFORM3DVPROC glUniform3dv;
extern PFNGLUNIFORM4DVPROC glUniform4dv;
extern PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv;
extern PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv;
extern PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv;
extern PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv;
extern PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv;
extern PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv;
extern PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv;
extern PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv;
extern PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv;
extern PFNGLGETUNIFORMDVPROC glGetUniformdv;
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation;
extern PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName;
extern PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName;
extern PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv;
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv;
extern PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv;
extern PFNGLPATCHPARAMETERIPROC glPatchParameteri;
extern PFNGLPATCHPARAMETERFVPROC glPatchParameterfv;
extern PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream;
extern PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed;
extern PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed;
extern PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv;
extern PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;
extern PFNGLSHADERBINARYPROC glShaderBinary;
extern PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;
extern PFNGLDEPTHRANGEFPROC glDepthRangef;
extern PFNGLCLEARDEPTHFPROC glClearDepthf;
extern PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;
extern PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv;
extern PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d;
extern PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv;
extern PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d;
extern PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv;
extern PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d;
extern PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv;
extern PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d;
extern PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv;
extern PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv;
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog;
extern PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d;
extern PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d;
extern PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d;
extern PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d;
extern PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv;
extern PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv;
extern PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv;
extern PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv;
extern PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer;
extern PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv;
extern PFNGLVIEWPORTARRAYVPROC glViewportArrayv;
extern PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf;
extern PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv;
extern PFNGLSCISSORARRAYVPROC glScissorArrayv;
extern PFNGLSCISSORINDEXEDPROC glScissorIndexed;
extern PFNGLSCISSORINDEXEDVPROC glScissorIndexedv;
extern PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv;
extern PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed;
extern PFNGLGETFLOATI_VPROC glGetFloati_v;
extern PFNGLGETDOUBLEI_VPROC glGetDoublei_v;
extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance;
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced;
extern PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ;
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv;
extern PFNGLBINDIMAGETEXTUREPROC glBindImageTexture;
extern PFNGLMEMORYBARRIERPROC glMemoryBarrier;
extern PFNGLTEXSTORAGE1DPROC glTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC glTexStorage3D;
extern PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC glPopDebugGroup;
extern PFNGLOBJECTLABELPROC glObjectLabel;
extern PFNGLGETOBJECTLABELPROC glGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;
extern PFNGLCLEARBUFFERDATAPROC glClearBufferData;
extern PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData;
extern PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect;
extern PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData;
extern PFNGLTEXTUREVIEWPROC glTextureView;
extern PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat;
extern PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor;
extern PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv;
extern PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v;
extern PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage;
extern PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage;
extern PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData;
extern PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData;
extern PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect;
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect;
extern PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation;
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding;
extern PFNGLTEXBUFFERRANGEPROC glTexBufferRange;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample;

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
  extern GLuint loadShader(             // �V�F�[�_�v���O�����̃v���O������
    const char *vert,                   // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
    const char *frag = 0,               // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
    const char *geom = 0,               // �W�I���g���V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
    int nvarying = 0,                   // �t�B�[�h�o�b�N���� varying �ϐ��̐��i0 �Ȃ�s�g�p�j
    const char **varyings = 0           // �t�B�[�h�o�b�N���� varying �ϐ��̃��X�g
    );

  /*
  ** �J���[�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
  */
  extern bool saveColor(                // �ǂݍ��݂ł����� true
    const char *name                    // �ۑ�����t�@�C����
    );

  /*
  ** �f�v�X�o�b�t�@�̓��e�� TGA �t�@�C���ɕۑ�
  */
  extern bool saveDepth(                // �ۑ��ł����� true
    const char *name                    // �ۑ�����t�@�C����
    );

  /*
  ** TGA �t�@�C�� (8/16/24/32bit) �̓ǂݍ���
  */
  extern GLubyte *loadTga(              // �ǂݍ��񂾉摜�f�[�^�̃|�C���^��Ԃ� (�g�p�� delete ����)
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLsizei &width,                     // �ǂݍ��� TGA �t�@�C���̕�
    GLsizei &height,                    // �ǂݍ��� TGA �t�@�C���̍���
    GLenum &format                      // �ǂݍ��� TGA �t�@�C���̏��� (GL_R, GL_RG, GL_BGR, GL_BGRA)
    );

  /*
  ** �e�N�X�`���������̊m��
  */
  extern void loadTexture(
    GLsizei width,                      // �m�ۂ���e�N�X�`���������̕�
    GLsizei height,                     // �m�ۂ���e�N�X�`���������̍���
    GLenum internal,                    // �m�ۂ���e�N�X�`���������̓�������
    GLenum format = GL_RGBA,            // image �̏���
    const GLvoid *image = 0
    );

  /*
  ** TGA �t�@�C�����e�N�X�`���������ɓǂݍ���
  */
  extern bool loadImage(                // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    GLenum internal                     // �e�N�X�`���������̓����t�H�[�}�b�g
    );

  /*
  ** TGA �摜�t�@�C���̍����}�b�v�ǂݍ���Ńe�N�X�`���������ɖ@���}�b�v���쐬����
  */
  extern bool loadHeight(               // �ǂݍ��݂ł����� true
    const char *name,                   // �ǂݍ��ރt�@�C����
    float nz                            // �@���� z ���̒���
    );

  /*
  ** �O�p�`�������ꂽ OBJ �t�@�C����ǂݍ��� (Elements �`��)
  */
  extern bool loadObj(                  // �ǂݍ��݂ł����� true
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
  extern bool loadObj(                  // �ǂݍ��݂ł����� true
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
      loadTexture(width, height, internal, format, image);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    GgTexture(const char *name, GLenum internal = GL_RGBA)
    {
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      loadImage(name, internal);
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
      loadHeight(name, nz);
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
      : program(loadShader(vert, frag, geom, nvarying, varyings)) {}
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
      program = loadShader(vert, frag, geom, nvarying, varyings);
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
