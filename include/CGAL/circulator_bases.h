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
// file          : include/CGAL/circulator_bases.h
// package       : Circulator (2.6)
// chapter       : $CGAL_Chapter: Circulators $
// source        : circulator.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1999/04/28 23:22:58 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Base classes and tags to build own circulators.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_BASES_H
#define CGAL_CIRCULATOR_BASES_H 1

#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif

CGAL_BEGIN_NAMESPACE

struct Circulator_tag {};                   // any circulator.
struct Iterator_tag   {};                   // any iterator.

struct Forward_circulator_tag
    : public CGAL_STD::forward_iterator_tag       {};
struct Bidirectional_circulator_tag
    : public CGAL_STD::bidirectional_iterator_tag {};
struct Random_access_circulator_tag
    : public CGAL_STD::random_access_iterator_tag {};
template <class T, class Dist, class Size>
struct Forward_circulator_base {
    typedef T                            value_type;
    typedef Dist                         difference_type;
    typedef Size                         size_type;
    typedef T*                           pointer;
    typedef T&                           reference;
    typedef Forward_circulator_tag       iterator_category;
};
template <class T, class Dist, class Size>
struct Bidirectional_circulator_base {
    typedef T                            value_type;
    typedef Dist                         difference_type;
    typedef Size                         size_type;
    typedef T*                           pointer;
    typedef T&                           reference;
    typedef Bidirectional_circulator_tag iterator_category;
};
template <class T, class Dist, class Size>
struct Random_access_circulator_base {
    typedef T                            value_type;
    typedef Dist                         difference_type;
    typedef Size                         size_type;
    typedef T*                           pointer;
    typedef T&                           reference;
    typedef Random_access_circulator_tag iterator_category;
};
template < class Category,
           class T,
#ifndef CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS
               class Distance  = std::ptrdiff_t,
               class Size      = std::size_t,
               class Pointer   = T*,
               class Reference = T&>
#else // CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS //
               class Distance, class Size, class Pointer, class Reference>
#endif // CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS //
    struct Circulator_base {
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Size      size_type;
        typedef Pointer   pointer;
        typedef Reference reference;
    };

// variant base classes
// ---------------------
template <class T, class Dist, class Size>
class Forward_circulator_ptrbase         // forward circulator.
{
    protected:
        void* _ptr;
    public:
        typedef Forward_circulator_tag  iterator_category;
        typedef T                       value_type;
        typedef Dist                    difference_type;
        typedef Size                    size_type;
        typedef T*                      pointer;
        typedef T&                      reference;
        Forward_circulator_ptrbase()        : _ptr(NULL) {}
        Forward_circulator_ptrbase(void* p) : _ptr(p) {}
};
template <class T, class Dist, class Size>
class Bidirectional_circulator_ptrbase   // bidirectional circulator.
{
    protected:
        void* _ptr;
    public:
        typedef Bidirectional_circulator_tag  iterator_category;
        typedef T                             value_type;
        typedef Dist                          difference_type;
        typedef Size                          size_type;
        typedef T*                            pointer;
        typedef T&                            reference;
        Bidirectional_circulator_ptrbase()        : _ptr(NULL) {}
        Bidirectional_circulator_ptrbase(void* p) : _ptr(p) {}
};
template <class T, class Dist, class Size>
class Random_access_circulator_ptrbase   // random access circulator.
{
    protected:
        void* _ptr;
    public:
        typedef Random_access_circulator_tag iterator_category;
        typedef T                            value_type;
        typedef Dist                         difference_type;
        typedef Size                         size_type;
        typedef T*                           pointer;
        typedef T&                           reference;
        Random_access_circulator_ptrbase()        : _ptr(NULL) {}
        Random_access_circulator_ptrbase(void* p) : _ptr(p) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_CIRCULATOR_BASES_H //
// EOF //
