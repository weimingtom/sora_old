﻿/*  Copyright (C) 2011-2012 by if1live */
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
#include "sora/vertex.h"

using namespace std;
using namespace sora;

TEST(VertexInfo, Vertex2D) {
  VertexInfo &info = VertexInfoHolder<Vertex2D>::Get();
  EXPECT_EQ(sizeof(Vertex2D), info.size);
  EXPECT_EQ(0, info.pos_offset);
  EXPECT_EQ(kTypeFloat, info.pos_type);
}

TEST(VertexInfo, Vertex) {
  VertexInfo &info = VertexInfoHolder<Vertex>::Get();
  EXPECT_EQ(sizeof(Vertex), info.size);
  EXPECT_EQ(0, info.pos_offset);
  EXPECT_EQ(kTypeFloat, info.pos_type);
}

TEST(VertexInfo, TangentVertex) {
  VertexInfo &info = VertexInfoHolder<TangentVertex>::Get();
  EXPECT_EQ(sizeof(TangentVertex), info.size);
  EXPECT_EQ(0, info.pos_offset);
  EXPECT_EQ(kTypeFloat, info.pos_type);
}

TEST(VertexInfo, Get) {
  const VertexInfo &vert_info = VertexInfo::Info(kVertex);
  EXPECT_EQ(true, VertexInfoHolder<Vertex>::Get() == vert_info);

  const VertexInfo &pos2d_info = VertexInfo::Info(kVertexPos2D);
  EXPECT_EQ(true, VertexInfoHolder<glm::vec2>::Get() == pos2d_info);
}