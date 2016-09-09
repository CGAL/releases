// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Interval_arithmetic/_FPU.h
// package       : Interval_arithmetic (4.15)
// revision      : $Revision: 2.31 $
// revision_date : $Date: 1999/05/04 15:52:14 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
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


#if defined(__osf__)
#undef __osf
#define __osf
#endif

#if (	!defined(__i386__)  && \
	!defined(__sparc__) && \
	!defined(__alpha__) && \
	!defined(__mips__)  && \
	!defined(__sgi)     && \
	!defined(_MSC_VER) \
	)
#error "Architecture not supported."
#endif

#if defined (__GNUC__) && ! defined (CGAL_IA_DONT_USE_ASSEMBLY)
#define CGAL_IA_USE_ASSEMBLY
#endif

#ifdef __linux__
#include <fpu_control.h>
#endif

#ifndef CGAL_IA_USE_ASSEMBLY
#ifdef __sun__
#include <ieeefp.h>
#endif // __sun__
#ifdef __osf
#include <float.h>
#endif // __osf
#ifdef __sgi
    // The 3 C functions do not work on IRIX 6.5 !!!!!
    // So we use precompiled (by gcc) binaries linked into libCGAL.
    // See revision 2.23 for the old code.
extern "C" {
  void CGAL_workaround_IRIX_set_FPU_cw (int);
  int  CGAL_workaround_IRIX_get_FPU_cw (void);
}
#endif // __sgi
#endif // CGAL_IA_USE_ASSEMBLY

CGAL_BEGIN_NAMESPACE

#define CGAL_IA_FORCE_TO_DOUBLE(x) (x)

#ifdef __i386__

// This is compulsory to have this to force the Intel processor to output a
// real double, and not Intel's doubles, because even when precision is
// explicitely set to "double", the exponent still has 15 bits, and it bugs
// when some values are in this range.
// The other possible workaround is to use intervals of "long doubles"
// directly, but I think it would be much slower.
#undef CGAL_IA_FORCE_TO_DOUBLE
#define CGAL_IA_FORCE_TO_DOUBLE(x) ( { volatile double __x = (x); __x; } )

#ifdef CGAL_IA_USE_ASSEMBLY
#define CGAL_IA_SETFPCW(CW) asm volatile ("fldcw %0" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("fstcw %0" : "=m" (CW))
#endif
typedef unsigned short FPU_CW_t;
enum {  //               rounding | def. mask
    FPU_cw_near = _FPU_RC_NEAREST | 0x127f,
    FPU_cw_zero = _FPU_RC_ZERO    | 0x127f,
    FPU_cw_up   = _FPU_RC_UP      | 0x127f,
    FPU_cw_down = _FPU_RC_DOWN    | 0x127f
};
#endif // __i386__

#ifdef __sparc__
#ifdef CGAL_IA_USE_ASSEMBLY
#define CGAL_IA_SETFPCW(CW) asm volatile ("ld %0,%%fsr" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("st %%fsr,%0" : "=m" (CW))
typedef unsigned int FPU_CW_t;
enum {  //        rounding   | precision  | def.mask
    FPU_cw_near = 0x0        | 0x20000000 | 0x1f,
    FPU_cw_zero = 0x40000000 | 0x20000000 | 0x1f,
    FPU_cw_up   = 0x80000000 | 0x20000000 | 0x1f,
    FPU_cw_down = 0xc0000000 | 0x20000000 | 0x1f
};
#else
typedef unsigned int FPU_CW_t; // fp_rnd
enum {
    FPU_cw_near = FP_RN,
    FPU_cw_zero = FP_RZ,
    FPU_cw_up   = FP_RP,
    FPU_cw_down = FP_RM
};
#endif
#endif // __sparc__

#if defined(__mips__) || defined(__sgi)
#ifdef CGAL_IA_USE_ASSEMBLY
#define CGAL_IA_SETFPCW(CW) asm volatile ("ctc1 %0,$31" : :"r" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("cfc1 %0,$31" : "=r" (CW))
#endif // CGAL_IA_USE_ASSEMBLY
typedef unsigned int FPU_CW_t;
enum {
    FPU_cw_near = 0x0,
    FPU_cw_zero = 0x1,
    FPU_cw_up   = 0x2,
    FPU_cw_down = 0x3
};
#endif // __mips__ || __sgi

#ifdef __alpha__ // This one is not really supported [yet].
#ifdef CGAL_IA_USE_ASSEMBLY
#define CGAL_IA_SETFPCW(CW) asm volatile ("mt_fpcr %0; excb" : :"f" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("excb; mf_fpcr %0" : "=f" (CW))
typedef unsigned long FPU_CW_t;
enum { //         rounding
    // I guess it won't work, because enum == int.
    FPU_cw_zero = 0x0000000000000000UL,
    FPU_cw_near = 0x0800000000000000UL,
    FPU_cw_up   = 0x0c00000000000000UL,
    FPU_cw_down = 0x0400000000000000UL
};
#else
typedef unsigned int FPU_CW_t;
enum {
    FPU_cw_zero = FP_RND_RZ,
    FPU_cw_near = FP_RND_RN,
    FPU_cw_up   = FP_RND_RP,
    FPU_cw_down = FP_RND_RM
};
#endif
#endif // __alpha__

#ifdef _MSC_VER
enum float_round_style {
  round_indeterminate = -1,
  round_toward_zero = 0,
  round_to_nearest = 1,
  round_toward_infinity = 2,
  round_toward_neg_infinity = 3
};
typedef unsigned int FPU_CW_t;
enum {
  FPU_cw_zero = round_toward_zero,
  FPU_cw_near = round_to_nearest,
  FPU_cw_up   = round_toward_infinity,
  FPU_cw_down = round_toward_neg_infinity
};
/*
 * The enumeration describes the various methods that an implementation can
 * choose for rounding a floating-point value to an integer value:
 * 
 * round_indeterminate -- rounding method cannot be determined
 * round_toward_zero -- round toward zero
 * round_to_nearest -- round to nearest integer
 * round_toward_infinity -- round away from zero
 * round_toward_neg_infinity -- round to more negative integer
 */
#endif //_MSC_VER


// Main functions: FPU_get_cw() and FPU_set_cw();

inline FPU_CW_t FPU_get_cw (void)
{
    FPU_CW_t cw;
#ifdef CGAL_IA_USE_ASSEMBLY
    CGAL_IA_GETFPCW(cw);
#else

#ifdef __linux__
#error "It seems there's no C function in libc5 !!!"
#endif

#ifdef __sun__
    cw = fpgetround();
#endif

#ifdef __sgi
    cw = CGAL_workaround_IRIX_get_FPU_cw();
#endif

#ifdef __osf
    cw = read_rnd();
#endif

#endif // CGAL_IA_USE_ASSEMBLY
    return cw;
}

inline void FPU_set_cw (FPU_CW_t cw)
{
#ifdef CGAL_IA_USE_ASSEMBLY
    CGAL_IA_SETFPCW(cw);
#else

#ifdef __linux__
    __setfpucw(cw);
#endif

#ifdef __sun__
    fpsetround(fp_rnd(cw));
#endif

#ifdef __sgi
    CGAL_workaround_IRIX_set_FPU_cw(cw);
#endif

#ifdef __osf
    write_rnd(cw);
#endif

#endif // CGAL_IA_USE_ASSEMBLY
}

// Obscolete: wrappers for the old interface.  Will be removed after 2.0.

#if 1
inline void FPU_set_rounding_to_zero (void)
{ FPU_set_cw(FPU_cw_zero); }

inline void FPU_set_rounding_to_nearest (void)
{ FPU_set_cw(FPU_cw_near); }

inline void FPU_set_rounding_to_infinity (void)
{ FPU_set_cw(FPU_cw_up); }

inline void FPU_set_rounding_to_minus_infinity (void)
{ FPU_set_cw(FPU_cw_down); }
#endif

CGAL_END_NAMESPACE

#endif // CGAL_FPU_H
