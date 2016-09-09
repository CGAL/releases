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
// source        : basic.fw
// file          : include/CGAL/basic.h
// package       : Kernel_basic (2.0.11)
// revision      : 2.0.11
// revision_date : 06 May 1999 
// author(s)     : Lutz Kettner
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_BASIC_H
#define CGAL_BASIC_H

#ifndef CGAL_CONFIG_H
#  include <CGAL/config.h>
#endif // CGAL_CONFIG_H

#include <iostream>
#include <cstdlib>

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
#endif  // CGAL_USE_LEDA


#ifndef CGAL_ASSERTIONS_H
#include <CGAL/assertions.h>
#endif // CGAL_ASSERTIONS_H
#ifndef CGAL_KERNEL_ASSERTIONS_H
#include <CGAL/kernel_assertions.h>
#endif // CGAL_KERNEL_ASSERTIONS_H
#ifndef CGAL_HANDLE_H
#include <CGAL/Handle.h>
#endif // CGAL_HANDLE_H
#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif // CGAL_OBJECT_H
#ifndef CGAL_ENUM_H
#include <CGAL/enum.h>
#endif // CGAL_ENUM_H
#ifndef CGAL_TAGS_H
#include <CGAL/tags.h>
#endif // CGAL_TAGS_H
#ifndef CGAL_MISC_H
#include <CGAL/misc.h>
#endif // CGAL_MISC_H
#ifndef CGAL_NUMBER_TYPE_BASIC_H
#include <CGAL/number_type_basic.h>
#endif // CGAL_NUMBER_TYPE_BASIC_H
#ifndef CGAL_IO_IO_H
#include <CGAL/IO/io.h>
#endif // CGAL_IO_IO_H
#ifndef CGAL_KERNEL_BASIC_H
#include <CGAL/kernel_basic.h>
#endif // CGAL_KERNEL_BASIC_H

#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#include <CGAL/known_bit_size_integers.h>
#endif // CGAL_KNOWN_BIT_SIZE_INTEGERS_H

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
struct _Assert_tag_class
{
    void match_compile_time_tag( const Base&) const {}
};

template <class Tag, class Derived>
inline
void
Assert_compile_time_tag( const Tag&, const Derived& b)
{
  _Assert_tag_class<Tag> x;
  x.match_compile_time_tag(b);
}
#endif // CGAL_ASSERT_COMPILE_TIME_TAG

template < class T>
inline
void
assert_equal_types( const T&, const T&) {}



// Big endian or little endian machine.
// ====================================
#ifdef CGAL_CFG_NO_BIG_ENDIAN
#define CGAL_LITTLE_ENDIAN 1
#else
#define CGAL_BIG_ENDIAN 1
#endif


// Symbolic constants to tailor inlining. Inlining Policy.
// =======================================================
#ifndef CGAL_MEDIUM_INLINE
#define CGAL_MEDIUM_INLINE inline
#endif
#ifndef CGAL_LARGE_INLINE
#define CGAL_LARGE_INLINE
#endif
#ifndef CGAL_HUGE_INLINE
#define CGAL_HUGE_INLINE
#endif

CGAL_END_NAMESPACE



#endif // CGAL_BASIC_H
