#pragma once
#ifndef _INCLUDE_
#define _INCLUDE_
#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(size) byte MACRO_CONCAT(_pad, __COUNTER__)[size];

#define ERR(x) MessageBoxA(0, x, "", 0); return false;
#endif

#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <assert.h>
#include <winuser.h>
#include <Wincon.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <unordered_map>
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <functional>
#include <future>
#include <Shlobj.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>