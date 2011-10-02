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
#ifndef RENDERING_RUNA_UBER_SHADER_H_
#define RENDERING_RUNA_UBER_SHADER_H_

#define UBER_SHADER_USE_NORMAL  0x01
#define UBER_SHADER_USE_TEXCOORD  0x02
#define UBER_SHADER_USE_COLOR 0x04

#include <string>
#include "runa/runa_enum.h"

namespace runa {;
class UberShader;
class ShaderDefineIdentifier;

class UberShader {
 public:
  typedef unsigned int FlagType;
  typedef std::tr1::unordered_map<FlagType, ShaderProgramPtr> ShaderDictType;

 public:
  UberShader(const std::string &vert_src, const std::string &frag_src);
  ~UberShader();

  ShaderProgramPtr getShader(FlagType flag);
  void CleanupUnusedShader();
 private:
  std::string orig_vert_src_;
  std::string orig_frag_src_;

  bool HasFlag(FlagType src, FlagType test) const;
  ShaderProgramPtr create(FlagType flag) const;
  std::string CreateMacroCode(FlagType flag) const;

  ShaderDictType shader_dict_;
};
}
#endif  // RENDERING_RUNA_UBER_SHADER_H_
