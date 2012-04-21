﻿/*  Copyright (C) 2011 by if1live */
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// Ŭnicode please
#include "sora_test_stdafx.h"

#include "renderer/renderer_env.h"

using namespace std;
using namespace sora;
using namespace sora::gl;
using namespace glm;

TEST(GLEnv, TypeToGLEnum) {
  EXPECT_EQ(GL_FLOAT, GLEnv::TypeToGLEnum<float>());
  EXPECT_EQ(GL_UNSIGNED_BYTE, GLEnv::TypeToGLEnum<unsigned char>());
  EXPECT_EQ(GL_BYTE, GLEnv::TypeToGLEnum<char>());
  EXPECT_EQ(GL_SHORT, GLEnv::TypeToGLEnum<short>());
  EXPECT_EQ(GL_UNSIGNED_SHORT, GLEnv::TypeToGLEnum<unsigned short>());
  EXPECT_EQ(GL_INT, GLEnv::TypeToGLEnum<int>());
  EXPECT_EQ(GL_UNSIGNED_INT, GLEnv::TypeToGLEnum<unsigned int>());

  EXPECT_EQ(GL_FLOAT, GLEnv::VecToGLEnum(vec3(0.0)));
  EXPECT_EQ(GL_INT, GLEnv::VecToGLEnum(ivec2(0.0)));

  //draw mode
  EXPECT_EQ(GL_TRIANGLES, GLEnv::TypeToGLEnum(kDrawTriangles));
  EXPECT_EQ(GL_LINES, GLEnv::TypeToGLEnum(kDrawLines));
}