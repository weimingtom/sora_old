﻿// Ŭnicode please 
#include "precompile.h"

int main(int argc, char *argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	getchar();
	return result;
}