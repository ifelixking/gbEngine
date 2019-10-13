#pragma once

// library import
#ifdef _WIN32
#define API __declspec(dllimport)
#else
#define API
#endif

#include "../source/math/math.h"
#include "../source/engine/env/EnvBasic.h"