// ======================================================================
//
// Copyright (c) 1998,1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Interval_arithmetic/_FPU.h
// package       : Interval_arithmetic (4.39)
// revision      : $Revision: 2.58 $
// revision_date : $Date: 1999/11/07 17:59:42 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_FPU_H
#define CGAL_FPU_H

// This file specifies some platform dependant functions, regarding the FPU
// directed rounding modes.  There is only support for double precision.

// Some useful constants
#define CGAL_IA_MIN_DOUBLE (5e-324) // subnormal
#define CGAL_IA_MAX_DOUBLE (1.7976931348623157081e+308)

// Macro to stop compiler optimization.
#ifdef __GNUG__
// It's slightly faster to use the following, but it's a GCC extension.
#define CGAL_IA_STOP_COMPILER_OPT(x) ({ volatile double y(x); double z=y; z; })
#else
inline double IA_force_to_double(const double x)
{ volatile double e = x; return e; }
#define CGAL_IA_STOP_COMPILER_OPT(x) IA_force_to_double(x)
#endif

// The x86 processor keeps too wide exponents (15bits) in registers, even in
// double precision mode !  It's a problem when the intervals overflow or
// underflow.  To work around that, we store the variable to memory when
// needed, using the macro below.
// Another possible workaround would be to use intervals of "long doubles"
// directly, but I think it would be much slower.
#if !defined (CGAL_IA_NO_X86_OVER_UNDER_FLOW_PROTECT) && \
    (defined __i386__ || defined _MSC_VER || defined __BORLANDC__)
#define CGAL_IA_FORCE_TO_DOUBLE(x) CGAL_IA_STOP_COMPILER_OPT(x)
#else
#define CGAL_IA_FORCE_TO_DOUBLE(x) (x)
#endif // __i386__

// We sometimes need to stop constant propagation.
// (because operations are done with a wrong rounding mode).
// With GCC, this is done using __builtin_constant_p().
// It should also be called at more specific places rather than in the ctors.
#ifndef CGAL_IA_DONT_STOP_CONSTANT_PROPAGATION
#ifdef __GNUG__
#define CGAL_IA_STOP_CPROP(x) \
    (__builtin_constant_p (x) ? CGAL_IA_STOP_COMPILER_OPT(x) : (x) )
#else
#define CGAL_IA_STOP_CPROP(x) CGAL_IA_STOP_COMPILER_OPT(x)
#endif
#else
#define CGAL_IA_STOP_CPROP(x) (x)
#endif

#ifdef __linux__
#include <fpu_control.h>
#elif defined __SUNPRO_CC
#include <ieeefp.h>
#elif defined __osf || defined __osf__ || defined __BORLANDC__
#include <float.h>
#elif defined __sgi
    // The 3 C functions do not work on IRIX 6.5 !!!!!
    // So we use precompiled (by gcc) binaries linked into libCGAL.
    // See revision 2.23 for the old code.
extern "C" {
  void CGAL_workaround_IRIX_set_FPU_cw (int);
  int  CGAL_workaround_IRIX_get_FPU_cw (void);
}
#endif

CGAL_BEGIN_NAMESPACE

#ifdef __STD_IEC_559__
// This is a version for the upcoming C9X standard, which should be portable.
// It should work with GNU libc 2.1.
#define CGAL_IA_SETFPCW(CW) fesetround(CW)
#define CGAL_IA_GETFPCW(CW) CW = fegetround()
typedef int FPU_CW_t;
#define CGAL_FE_TONEAREST    FE_TONEAREST
#define CGAL_FE_TOWARDZERO   FE_TOWARDZERO
#define CGAL_FE_UPWARD       FE_UPWARD
#define CGAL_FE_DOWNWARD     FE_DOWNWARD

#elif defined __i386__
// The GNU libc version (cf powerpc) is nicer, but doesn't work on libc 5 :(
// This one also works with CygWin.
#define CGAL_IA_SETFPCW(CW) asm volatile ("fldcw %0" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("fnstcw %0" : "=m" (CW))
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x000 | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xc00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#elif defined __powerpc__
#define CGAL_IA_SETFPCW(CW) _FPU_SETCW(CW)
#define CGAL_IA_GETFPCW(CW) _FPU_GETCW(CW)
typedef fpu_control_t FPU_CW_t;
#define CGAL_FE_TONEAREST    (_FPU_RC_NEAREST | _FPU_DEFAULT)
#define CGAL_FE_TOWARDZERO   (_FPU_RC_ZERO    | _FPU_DEFAULT)
#define CGAL_FE_UPWARD       (_FPU_RC_UP      | _FPU_DEFAULT)
#define CGAL_FE_DOWNWARD     (_FPU_RC_DOWN    | _FPU_DEFAULT)

#elif defined __SUNPRO_CC
#define CGAL_IA_SETFPCW(CW) fpsetround(fp_rnd(CW))
#define CGAL_IA_GETFPCW(CW) CW = fpgetround()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    FP_RN
#define CGAL_FE_TOWARDZERO   FP_RZ
#define CGAL_FE_UPWARD       FP_RP
#define CGAL_FE_DOWNWARD     FP_RM

#elif defined __sparc__
#define CGAL_IA_SETFPCW(CW) asm volatile ("ld %0,%%fsr" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("st %%fsr,%0" : "=m" (CW))
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0        | 0x20000000 | 0x1f)
#define CGAL_FE_TOWARDZERO   (0x40000000 | 0x20000000 | 0x1f)
#define CGAL_FE_UPWARD       (0x80000000 | 0x20000000 | 0x1f)
#define CGAL_FE_DOWNWARD     (0xc0000000 | 0x20000000 | 0x1f)

#elif defined __sgi
#define CGAL_IA_SETFPCW(CW) CGAL_workaround_IRIX_set_FPU_cw(CW)
#define CGAL_IA_GETFPCW(CW) CW = CGAL_workaround_IRIX_get_FPU_cw()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0)
#define CGAL_FE_TOWARDZERO   (0x1)
#define CGAL_FE_UPWARD       (0x2)
#define CGAL_FE_DOWNWARD     (0x3)

#elif defined __mips__ // && !defined __sgi
#define CGAL_IA_SETFPCW(CW) asm volatile ("ctc1 %0,$31" : :"r" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("cfc1 %0,$31" : "=r" (CW))
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0)
#define CGAL_FE_TOWARDZERO   (0x1)
#define CGAL_FE_UPWARD       (0x2)
#define CGAL_FE_DOWNWARD     (0x3)

#elif defined __osf || defined __osf__  // Not yet supported.
#define CGAL_IA_SETFPCW(CW) write_rnd(CW)
#define CGAL_IA_GETFPCW(CW) CW = read_rnd()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    FP_RND_RN
#define CGAL_FE_TOWARDZERO   FP_RND_RZ
#define CGAL_FE_UPWARD       FP_RND_RP
#define CGAL_FE_DOWNWARD     FP_RND_RM

#elif defined __alpha__  // Not yet supported.
#define CGAL_IA_SETFPCW(CW) asm volatile ("mt_fpcr %0; excb" : :"f" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("excb; mf_fpcr %0" : "=f" (CW))
typedef unsigned long FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0800000000000000UL)
#define CGAL_FE_TOWARDZERO   (0x0000000000000000UL)
#define CGAL_FE_UPWARD       (0x0c00000000000000UL)
#define CGAL_FE_DOWNWARD     (0x0400000000000000UL)

#elif defined _MSC_VER
// Found in http://msdn.microsoft.com/library/sdkdoc/directx/imover_7410.htm :
#define CGAL_IA_SETFPCW(CW) __asm fldcw CW
#define CGAL_IA_GETFPCW(CW) __asm fstcw CW
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0   | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xC00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#elif defined __BORLANDC__
#define CGAL_IA_SETFPCW(CW) _control87(CW,~0)
#define CGAL_IA_GETFPCW(CW) CW = _control87(0,0)
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0   | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xC00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#else
#error Architecture not supported
#endif

// User interface:

inline
FPU_CW_t
FPU_get_cw (void)
{
    FPU_CW_t cw;
    CGAL_IA_GETFPCW(cw);
    return cw;
}

inline
void
FPU_set_cw (FPU_CW_t cw)
{
    CGAL_IA_SETFPCW(cw);
}

inline
FPU_CW_t
FPU_get_and_set_cw (FPU_CW_t cw)
{
    FPU_CW_t old = FPU_get_cw();
    FPU_set_cw(cw);
    return old;
}

FPU_CW_t FPU_empiric_test(); // Only used for debug.

CGAL_END_NAMESPACE

#endif // CGAL_FPU_H
