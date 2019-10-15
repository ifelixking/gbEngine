#pragma once

// library import
#ifdef _WIN32
#define API __declspec(dllimport)
#else
#define API
#endif

#define NAMESPACE_BEGIN namespace gbEngine {
#define NAMESPACE_END }

#include "../source/math/math.h"
#include "../source/engine/env/EnvBasic.h"

