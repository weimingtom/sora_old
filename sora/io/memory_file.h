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
#ifndef SORA_MEMORY_FILE_H_
#define SORA_MEMORY_FILE_H_

#if SR_USE_PCH == 0
#include <string>
#include <boost/noncopyable.hpp>
#endif

#if SR_ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_activity.h>
#endif

namespace sora {;
#if SR_ANDROID
//안드로이드의 경우는 apk를 직접 뜯는 식으로 구현해야한다
//이부분을 ndk에서 지원하는 기능을 통해서 구현할 경우
//안드로이드 2.3부터만 지원한다(native actitivy를 써야되니까)
//2.2도 지원하기 위해서 apk를 직접 뜯는식으로 구현했다
#endif

class MemoryFile : boost::noncopyable {
public:
  MemoryFile(const char *filepath);
  MemoryFile(const std::string &filepath);
  ~MemoryFile();

  boolean Open();
  boolean IsOpened() const { return (data != NULL); }
  void Close();
  i32 GetLength() const { return end - start; }
  i32 Read(void *buf, i32 size);
  
  const std::string &filepath() const { return filepath_; }

public:
  // data
  u8 *start;
  u8 *curr;
  u8 *end;
  void *data;

  std::string filepath_;
};

}

#endif  // SORA_MEMORY_FILE_H_
