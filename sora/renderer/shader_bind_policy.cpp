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
#include "shader_bind_policy.h"

namespace sora {;

ShaderBindPolicy::ShaderBindPolicy(GLuint shader_prog)
: shader_prog_(shader_prog) {
}
ShaderBindPolicy::ShaderBindPolicy()
: shader_prog_(0) {
}
ShaderBindPolicy::~ShaderBindPolicy() {
}

void ShaderBindPolicy::set_var(int code, const ShaderVariable &v) {
  SR_ASSERT(code >= 0);
  SR_ASSERT(code < kSemanticCount);
  var_list_[code] = v;
}
const ShaderVariable &ShaderBindPolicy::var(int code) const {
  SR_ASSERT(code >= 0);
  SR_ASSERT(code < kSemanticCount);
  return var_list_[code];
}

}
