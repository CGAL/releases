/******************************************************************
 * Core Library Version 1.6, June 2003
 * Copyright (c) 1995-2002 Exact Computation Project
 * 
 * File: CoreDefs.cpp
 * Synopsis:
 *	 Useful parameters for Core Library which users may change
 *
 * Written by 
 *       Chee Yap <yap@cs.nyu.edu>
 *       Chen Li <chenli@cs.nyu.edu>
 *       Zilin Du <zilin@cs.nyu.edu>
 *
 * WWW URL: http://cs.nyu.edu/exact/
 * Email: exact@cs.nyu.edu
 *
 * $Id: CoreDefs.cpp,v 1.2 2003/08/06 12:59:31 afabri Exp $
 *****************************************************************/

#include <CORE/CoreDefs.h>

CORE_BEGIN_NAMESPACE

//  Default Values

/**
 * If AbortFlag is true when invalid expression is constructed, system will abort
 */

bool AbortFlag = true;

/**
 * InvalidFlag is set to negative whenever an invalid expression is constructed.
 * The user has the responsibility to reset to non-negative value.
 */

int InvalidFlag = 0;

/**
 *  Default BigFloat Division Relative Precision
 *  -- this is used by BigFloat division when the arguments are error-free.
 */

extLong defBFdivRelPrec = 30;

/**
 *  Default BigFloat Sqrt Absolute Precision
 *  -- this is used by BigFloat sqrt when the argument is error-free.
 */

extLong defBFsqrtAbsPrec = 30;

/**
 * Escape Precision 
 *   -- we will not compare a number to precision higher than this
 *   -- if this is infinity, there there is no escape precision */
extLong EscapePrec  = CORE_posInfty;

/** this flag becomes negative if the EscapePrec is used. */
long EscapePrecFlag = 0;

/// Escape Precision Warning Flag
/** this flag is true by default, and will cause a warning to be printed
    when EscapePrec is reached */
bool EscapePrecWarning = true;

/** The Composite Precision [defAbsPrec, defRelPrec] 
 *  determines the precision to which an Expr evaluates its 
 *  (exact, implicit) constant value. */

/**  absolute precision  = 2^31 - 1 */
extLong defAbsPrec = CORE_posInfty;
/** default relative precision is 60 relative bits.
 *  Why 60?  We would really like this to be 54, so that the default
 *  conversion duplicates the IEEE double precision.  But it turns out
 *  (see README file under BUGS), we need 59 to ensure this.
 *  Chee Yap (7/1/01) */
extLong defRelPrec = 60;

/**  number of BigFloat digits to print out */
long defBigFloatOutputDigits = 10; 

/**  NORMALLY, we like to make this equal to defBigFloatOutputDigits
  *  8/3/01, Chee: re-introduced this parameter */
long defOutputDigits = defBigFloatOutputDigits;

/** String Input Precision */

/** Set this to 16 if you want machine precision. This controls the 
 *  absolute error in string decimal inputs to Real or Expr.
 *  If defInputDigits is finite, then the absolute error will be 
 *  at most 10^{-defInputDigits}.  Otherwise, the input is exactly 
 *  represented by some BigFloat or BigRat value. */
extLong defInputDigits = CORE_posInfty;

/** This controls the absolute error in converting from string to BigFloat
 *  The absolute error will be at most 10^{-defInputDigits} */
long defBigFloatInputDigits = 16;

/** Floating Point filter
 *  true = turn on floating point filter */
bool fpFilterFlag = true;

/** IncrementaL evaluation flag
 *  incremental evaluation is requested, This means, we try to use previous
 *  approximate values to improve an approximation */
bool incrementalEvalFlag = true; 

/** Progressive evaluation flag
 *  true = turn on progressive evaluation flag */
bool progressiveEvalFlag = true;

/** Initial progressive evaluation precision
 *  Used by AddSubRep */
long defInitialProgressivePrec = 64;

/** RATIONAL REDUCTION FLAG
 *  true = turn on rational reduction */
bool rationalReduceFlag = false;

#ifndef CORE_ENABLE_INLINES
#include <CORE/CoreDefs.inl>
#endif

CORE_END_NAMESPACE
