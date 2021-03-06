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
#include "sora_stdafx.h"
#include "render_state.h"
#include "gl_render_state.h"

#include "shader.h"
#include "texture.h"
#include "material.h"
#include "mesh.h"

#include "matrix_stack.h"
#include <glm/gtc/matrix_inverse.hpp>

#include "device.h"
#include "draw_2d_manager.h"
#include "matrix_helper.h"
#include "sys_font.h"

using namespace glm;

namespace sora {;
RenderStateInterface::RenderStateInterface()
: win_width_(640),
win_height_(480),
model_mat_stack_(new MatrixStack()), 
projection_mat_(glm::mat4(1.0f)),
view_mat_(glm::mat4(1.0f)) {
}

RenderStateInterface::~RenderStateInterface() {
}
RenderStateInterface *RenderStateInterface::Create() {
  return new sora::gl::GLRenderState();
}
void RenderStateInterface::ResetAllMatrix() {
  ResetProjectionMat();
  ResetViewMat();
  ResetModelMat();
}
void RenderStateInterface::ResetProjectionMat() {
  projection_mat_ = glm::mat4(1.0f);
}
void RenderStateInterface::ResetViewMat() {
  view_mat_ = glm::mat4(1.0f);
}
void RenderStateInterface::ResetModelMat() {
  model_mat_stack_->Clear();
}
const glm::mat4 &RenderStateInterface::model_mat() const {
  return model_mat_stack_->Top();
}

glm::mat4 RenderStateInterface::GetMVPMatrix() const {
  mat4 mvp(1.0f);
  mvp *= projection_mat();
  mvp *= view_mat();
  mvp *= model_mat();
  return mvp;
}

glm::vec2 RenderStateInterface::GetClipPlanes3D() const {
  return glm::vec2(0.1f, 100.0f); 
}

glm::mat4 RenderStateInterface::GetProjection3D() const {
  float win_w = (float)win_width();
  float win_h = (float)win_height();
  vec2 clip_plane = GetClipPlanes3D();
  float z_near = clip_plane.x;
  float z_far = clip_plane.y;
  glm::mat4 projection = glm::perspective(45.0f, win_w/ win_h, z_near, z_far);
  return projection;
}
glm::mat4 RenderStateInterface::GetProjection2D() const {
  float win_w = (float)win_width();
  float win_h = (float)win_height();
  glm::mat4 projection = glm::ortho(0.0f, win_w, 0.0f, win_h);
  return projection;
    
}

void RenderState::DumpViewInfo(float x, float y) {
  Draw2DManager *draw_2d_mgr = Device::GetInstance()->draw_2d();

  const mat4 &view = view_mat();
  const glm::vec3 eye = MatrixHelper::ViewPos(view);
  const glm::vec3 up = MatrixHelper::ViewUpVec(view);
  const glm::vec3 dir = MatrixHelper::ViewDirVec(view);
  glm::vec3 view_side = glm::cross(dir, up);

  const sora::vec4ub &color = Color4ub::Red();
  char buf[128];
  float scale = 1.0f;
  float font_width = SysFont::kFontSize * scale;

  sprintf(buf, "ViewPos:%.4f, %.4f, %.4f", eye.x, eye.y, eye.z);
  draw_2d_mgr->AddString(glm::vec2(x, y), buf, color, scale);

  sprintf(buf, "ViewDir:%.4f, %.4f, %.4f", dir.x, dir.y, dir.z);
  draw_2d_mgr->AddString(glm::vec2(x, y - font_width), buf, color, scale);
}

} //namespace sora