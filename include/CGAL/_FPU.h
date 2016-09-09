// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/_FPU.h
// author(s)     : Sylvain Pion 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_FPU_H
#define CGAL_FPU_H

/*
 * Specify some *very* platform dependant functions, regarding the FPU
 * directed rounding modes. There is only support for double precision.
 *
 * I try to make it work with gcc/g++/cc/CC.
 * And I also try to provide the equivalent assembly code for GNU C.
 *
 * TODO: Check the exception flags, according to Christoph's remarks/code.
 *        (ie should we erase all, should we save&restore, etc...)
 */

#if defined(__osf__)
#undef __osf
#define __osf
#endif

#if defined(__i386__) || defined(i386)	/* Needed by egcs */
#undef __i386
#define __i386
#endif

#if (!defined(__i386)&&!defined(__sparc)&&!defined(__alpha)&&!defined(__mips))
#error "Architecture not recognized."
#endif

#if ( (defined(__i386) || defined(__sparc) || defined(__alpha)) && \
      defined(__GNUC__))
#define __USE_ASSEMBLY
#endif

#ifndef __USE_ASSEMBLY
#ifdef __linux
#include <fpu_control.h>
#endif
#ifdef __osf
#include <float.h>
#endif
#ifdef __sgi
  /* This #define is forced for backward compatibility with Irix 5.3. */
  /* I think it slows down Irix 6.2... */
#define __SGI_ieeefph__
#ifdef __SGI_ieeefph__
#include <ieeefp.h>
#else
#include <sys/fpu.h>
#endif
#endif
#ifdef __sun
#include <ieeefp.h>
#endif
#else	/* __USE_ASSEMBLY */
#ifdef __i386
#define SETFPCW(CW) asm volatile ("fldcw %0" : : "m" (*&CW))
/* x86:                       rounding   | precision  | default mask */
static unsigned int CGAL_FPU_cw_zero = 0xC00      | 0x200      | 0x107f; 
static unsigned int CGAL_FPU_cw_near = 0x0        | 0x200      | 0x107f;
static unsigned int CGAL_FPU_cw_up   = 0x800      | 0x200      | 0x107f; 
static unsigned int CGAL_FPU_cw_down = 0x400      | 0x200      | 0x107f;
#endif
#ifdef __sparc
#define SETFPCW(CW) asm volatile ("ld %0,%%fsr" : "=m" (*&CW))
/* Sparc:                     rounding   | precision  | default mask */
static unsigned int CGAL_FPU_cw_zero = 0x40000000 | 0x20000000 | 0x1f;
static unsigned int CGAL_FPU_cw_near = 0x0        | 0x20000000 | 0x1f;
static unsigned int CGAL_FPU_cw_up   = 0x80000000 | 0x20000000 | 0x1f;
static unsigned int CGAL_FPU_cw_down = 0xc0000000 | 0x20000000 | 0x1f;
#endif
#ifdef __alpha
#define SETFPCW(CW) asm volatile ("mt_fpcr %0; excb" : : "f"(CW))
/* Alpha:                      rounding */
static unsigned long CGAL_FPU_cw_zero = 0x0000000000000000UL;
static unsigned long CGAL_FPU_cw_near = 0x0800000000000000UL;
static unsigned long CGAL_FPU_cw_up   = 0x0c00000000000000UL;
static unsigned long CGAL_FPU_cw_down = 0x0400000000000000UL;
#endif
#endif

#if !defined(__GNUC__) && !defined(__cplusplus)
#define inline /* */
#endif

static inline void CGAL_FPU_set_rounding_to_zero (void);
static inline void CGAL_FPU_set_rounding_to_nearest (void);
static inline void CGAL_FPU_set_rounding_to_infinity (void);
static inline void CGAL_FPU_set_rounding_to_minus_infinity (void);


/* Code of those inline functions: */

static inline void CGAL_FPU_set_rounding_to_zero (void)
{
#ifdef __USE_ASSEMBLY
	SETFPCW(CGAL_FPU_cw_zero);
#else
#ifdef __linux
#ifdef __i386 
        __setfpucw(0x1e72);
#else
        __setfpucw(0x1f72);	/* FIX ME */
#endif
#endif

#ifdef __osf
	write_rnd(FP_RND_RZ);
#endif

#ifdef __sun
        fpsetround(FP_RZ);
#endif

#ifdef __sgi
#ifdef __SGI_ieeefph__
	fp_rnd mode = FP_RZ;
	fpsetround(mode);
#else
	union fpc_csr fpu_ctl;
	fpu_ctl.fc_word = get_fpc_csr();
	fpu_ctl.fc_struct.rounding_mode = ROUND_TO_ZERO;
	set_fpc_csr (fpu_ctl.fc_word);
#endif
#endif
#endif
}

static inline void CGAL_FPU_set_rounding_to_nearest (void)
{
#ifdef __USE_ASSEMBLY
	SETFPCW(CGAL_FPU_cw_near);
#else
#ifdef __osf
	write_rnd(FP_RND_RN);
#endif

#ifdef __sun
	fpsetround(FP_RN);
#endif

#ifdef __linux
#ifdef __i386
	__setfpucw(0x1272);
#else
	__setfpucw(0x1372);
#endif
#endif

#ifdef __sgi
#ifdef __SGI_ieeefph__
	fp_rnd mode = FP_RN;
	fpsetround(mode);
#else
	union fpc_csr fpu_ctl;
	fpu_ctl.fc_word = get_fpc_csr();
	fpu_ctl.fc_struct.rounding_mode = ROUND_TO_NEAREST;
	set_fpc_csr (fpu_ctl.fc_word);
#endif
#endif
#endif
}

static inline void CGAL_FPU_set_rounding_to_infinity (void)
{
#ifdef __USE_ASSEMBLY
	SETFPCW(CGAL_FPU_cw_up);
#else
#ifdef __osf
	write_rnd(FP_RND_RP);
#endif

#ifdef __sun
        fpsetround(FP_RP);
#endif

#ifdef __linux
#ifdef __i386
	__setfpucw(0x1a72);
#else
	__setfpucw(0x1b72);
#endif
#endif

#ifdef __sgi
#ifdef __SGI_ieeefph__
	fp_rnd mode = FP_RP;
	fpsetround(mode);
#else
	union fpc_csr fpu_ctl;
	fpu_ctl.fc_word = get_fpc_csr();
	fpu_ctl.fc_struct.rounding_mode = ROUND_TO_PLUS_INFINITY;
	set_fpc_csr (fpu_ctl.fc_word);
#endif
#endif
#endif
}

static inline void CGAL_FPU_set_rounding_to_minus_infinity (void)
{
#ifdef __USE_ASSEMBLY
	SETFPCW(CGAL_FPU_cw_down);
#else
#ifdef __osf
	write_rnd(FP_RND_RM);
#endif

#ifdef __sun
        fpsetround(FP_RM);
#endif

#ifdef __linux
#ifdef __i386
        __setfpucw(0x1672);
#else
        __setfpucw(0x1772);
#endif
#endif

#ifdef __sgi
#ifdef __SGI_ieeefph__
	fp_rnd mode = FP_RM;
	fpsetround(mode);
#else
	union fpc_csr fpu_ctl;
	fpu_ctl.fc_word = get_fpc_csr();
	fpu_ctl.fc_struct.rounding_mode = ROUND_TO_MINUS_INFINITY;
	set_fpc_csr (fpu_ctl.fc_word);
#endif
#endif
#endif
}

#endif /* CGAL_FPU_H */
