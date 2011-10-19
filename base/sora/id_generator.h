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
#ifndef BASE_SORA_ID_GENERATOR_H_
#define BASE_SORA_ID_GENERATOR_H_

namespace sora {;
template<typename T>
class IdGenerator {
 public:
  IdGenerator() : id_(next_id_++) {
  }
  IdGenerator(const IdGenerator &o) : id_(o.id_) {
  }
  IdGenerator& operator=(const IdGenerator &o) {
    this->id_ = o.id_;
  }
  ~IdGenerator() {}
  int id() const { return id_; }
 private:
  int id_;
  static int next_id_;
};

template<typename T>
int IdGenerator<T>::next_id_ = 1;
}

#endif  // BASE_SORA_ID_GENERATOR_H_