// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/basic.h
// package       : Kernel_basic (3.53)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/20 13:07:30 $
// author(s)     : Lutz Kettner
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_BASIC_H
#define CGAL_BASIC_H

#include <CGAL/config.h>

#define CGAL_NTS CGAL::NTS::

#if ((__GNUC__ == 2) && (__GNUC_MINOR__ == 95))
#include <cmath>
#endif  // gcc 2.95

#include <iostream>
#include <cstdlib>


// Big endian or little endian machine.
// ====================================
#ifdef CGAL_CFG_NO_BIG_ENDIAN
#define CGAL_LITTLE_ENDIAN 1
#else
#define CGAL_BIG_ENDIAN 1
#endif


#ifdef CGAL_USE_LEDA
#  ifndef CGAL_PROTECT_LEDA_BASIC_H
#    if ( __LEDA__ < 380 )
#      define Max leda_Max
#      define Min leda_Min
#    endif // __LEDA__ < 380
#    include <LEDA/basic.h>
#    if ( __LEDA__ < 380 )
#      undef Max
#      undef Min
#    endif // __LEDA__ < 380
#    define CGAL_PROTECT_LEDA_BASIC_H
#  endif // CGAL_PROTECT_LEDA_BASIC_H
#else
   // set flag for libCGALWin
#  define CGAL_USE_CGAL_WINDOW
#endif  // CGAL_USE_LEDA

// CGAL uses std::min and std::max
// (see ISO C++ 25.3.7, page 562),
// if feasible
#include <algorithm>

namespace CGAL {

#if !defined(CGAL_CFG_USING_USING_BUG) && !defined(CGAL_CFG_BROKEN_USING)

 using std::min;
 using std::max;

#else

 template <class NT>
 inline
 NT
 // const NT&
 min(const NT& x, const NT& y)
 { return (y < x) ? y : x; }

 template <class NT>
 inline
 NT
 // const NT&
 max(const NT& x, const NT& y)
 { return (x < y) ? y : x; }

#endif // CGAL_CFG_BROKEN_USING
} // namespace CGAL


#include <CGAL/assertions.h>
#include <CGAL/kernel_assertions.h>
#include <CGAL/Handle.h>
#include <CGAL/Object.h>
#include <CGAL/enum.h>
#include <CGAL/tags.h>
#include <CGAL/number_type_basic.h>
#include <CGAL/IO/io.h>
#include <CGAL/kernel_basic.h>
#include <CGAL/known_bit_size_integers.h>

CGAL_BEGIN_NAMESPACE

// Two struct's to denote boolean compile time decisions.
// ======================================================
struct Tag_true  {};
struct Tag_false {};

inline bool check_tag( Tag_true)  {return true;}
inline bool check_tag( Tag_false) {return false;}

// A function that asserts a specific compile time tag
// forcing its two arguments to have equal type.
// It is encapsulated with #ifdef since it will be defined also elsewhere.
// ======================================================
#ifndef CGAL_ASSERT_COMPILE_TIME_TAG
#define CGAL_ASSERT_COMPILE_TIME_TAG 1
template <class Base>
struct Assert_tag_class
{
    void match_compile_time_tag( const Base&) const {}
};

template <class Tag, class Derived>
inline
void
Assert_compile_time_tag( const Tag&, const Derived& b)
{
  Assert_tag_class<Tag> x;
  x.match_compile_time_tag(b);
}
#endif // CGAL_ASSERT_COMPILE_TIME_TAG

template < class T>
inline
void
assert_equal_types( const T&, const T&) {}

// Symbolic constants to tailor inlining. Inlining Policy.
// =======================================================
#ifndef CGAL_MEDIUM_INLINE
#  define CGAL_MEDIUM_INLINE inline
#endif

#ifndef CGAL_LARGE_INLINE
#  define CGAL_LARGE_INLINE
#endif

#ifndef CGAL_HUGE_INLINE
#  define CGAL_HUGE_INLINE
#endif

CGAL_END_NAMESPACE

#endif // CGAL_BASIC_H
