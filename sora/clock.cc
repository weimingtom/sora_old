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
#include "sora_stdafx.h"
#include "sora/clock.h"

#if SR_WIN
//http://alones.kr/tag/gettimeofday
// epoch time으로 변환할 상수
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

// for timezone
struct timezone {
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

// gettimeofday in windows
int gettimeofday(struct timeval *tv, struct timezone *tz) {
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;

  if (NULL != tv) {
    // system time을 구하기
    GetSystemTimeAsFileTime(&ft);

    // unsigned 64 bit로 만들기
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
    // 100nano를 1micro로 변환하기    tmpres /= 10;
    // epoch time으로 변환하기
    tmpres -= DELTA_EPOCH_IN_MICROSECS;    

    // sec와 micorsec으로 맞추기
    tv->tv_sec = (tmpres / 1000000UL);
    tv->tv_usec = (tmpres % 1000000UL);
  }

  // timezone 처리
  if (NULL != tz) {
    if (!tzflag) {
      _tzset();
      tzflag++;
    }
    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }

  return 0;
}
#endif

namespace sora {;
i32 Clock::GetMilliSecond() {
  //ref wolf3d timer
  struct timeval tp;
	struct timezone tzp;
	static int		secbase;

	gettimeofday( &tp, &tzp );
	
	if( ! secbase ) {
		secbase = tp.tv_sec;
		return tp.tv_usec / 1000;
	}

	curtime = (tp.tv_sec - secbase) * 1000 + tp.tv_usec / 1000;
	return curtime;
}
i32 Clock::curtime = 0;
}
