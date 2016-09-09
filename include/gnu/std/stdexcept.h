#ifdef RTTI_PATCH
#define exception RTTI_exception
#endif // exception

#include "/opt/gnu/lib/g++-include/std/stdexcept.h"

#ifdef RTTI_PATCH
#undef exception
#endif // exception
