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
// file          : include/CGAL/basic_lk.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_BASIC_LK_H
#define CGAL_BASIC_LK_H 1
// Numbertypes with known number of bits.
// ======================================
#if (defined(__sparc__) || defined(__sparc) || defined(sparc)) || \
    (defined(__sgi__)   || defined(__sgi)   || defined(sgi)) || \
    (defined(__i386__)  || defined(__i386)  || defined(i386))
    typedef  signed char             CGAL_Integer8;
    typedef  short                   CGAL_Integer16;
    typedef  int                     CGAL_Integer32;
    typedef  long long int           CGAL_Integer64;
    typedef  unsigned char           CGAL_UInteger8;
    typedef  unsigned short          CGAL_UInteger16;
    typedef  unsigned int            CGAL_UInteger32;
    typedef  unsigned long long int  CGAL_UInteger64;
#else
#  error "patch this"
#endif

// Two struct's to denote boolean compile time decisions.
// ======================================================
struct CGAL_Tag_true  {};
struct CGAL_Tag_false {};

inline bool CGAL_check_tag( CGAL_Tag_true)  {return true;}
inline bool CGAL_check_tag( CGAL_Tag_false) {return false;}


// A function that asserts a specific compile time tag
// forcing its two arguments to have equal type.
// It is encapsulated with #ifdef since it will be defined also elsewhere.
#ifndef CGAL_ASSERT_COMPILE_TIME_TAG
#define CGAL_ASSERT_COMPILE_TIME_TAG 1
template <class Base>
struct CGAL__Assert_tag_class {
    void match_compile_time_tag( const Base&) const {}
};
template< class Tag, class Derived>
inline void CGAL_Assert_compile_time_tag( const Tag&, const Derived& b) {
    CGAL__Assert_tag_class<Tag> x;
    x.match_compile_time_tag(b);
}
// template< class Tag>
// inline void CGAL_Assert_compile_time_tag( const Tag&, const Tag&) {}
#endif

template < class T> inline
void CGAL_assert_equal_types( const T&, const T&) {}


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


// Big endian or little endian machine.
// ====================================
#ifdef CGAL_CFG_NO_BIG_ENDIAN
#define CGAL_LITTLE_ENDIAN 1
#else
#define CGAL_BIG_ENDIAN 1
#endif


// Mathematical Functions.
// =======================
template < class T >
inline
bool CGAL_is_even( T x) {
    return !(x & 1);
}

template < class T >
inline
bool CGAL_is_odd( T x) {
    return (x & 1);
}
#endif // CGAL_BASIC_LK_H //
// EOF //
