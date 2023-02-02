#pragma once

#include <limits.h>

#define TAPE_MAX 1024
#define NESTING_MAX 256

//only applies to interpreter compiler always allows
#define ALLOW_OVERFLOW 0

#define BACKING_TYPE signed char
#define BACKING_TYPE_MIN SCHAR_MIN
#define BACKING_TYPE_MAX SCHAR_MAX

