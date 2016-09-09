// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : config/testfiles/CGAL_CFG_NO_ITERATOR_TRAITS.C
// package       : Configuration (1.16)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

// CGAL_CFG_NO_ITERATOR_TRAITS.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| Iterator traits are documented in the Dec. 1996 C++ Standard draft.
//| The following definition is set if iterator are not fully supported 
//| including their use in a template class, as a default template
//| argument and as a return type of global function.

#include <assert.h>
#include <iterator.h>
#include <vector.h>

// This class implements an iterator adaptor that forwards all
// member function calls to its template argument. It uses 
// iterator traits to derive correct types and iterator category.

template < class I, class category = iterator_traits<I>::iterator_category>
class Adaptor {
    I _i;
public:
    typedef iterator_traits<I>::value_type       value_type;
    typedef iterator_traits<I>::difference_type  difference_type;
    typedef iterator_traits<I>::reference        reference;
    typedef iterator_traits<I>::pointer          pointer;
    typedef category                             iterator_category;
    Adaptor( I i) : _i(i) {}
    Adaptor<I, category>&
    operator++() {
	++_i;
	return *this;
    }
    reference
    operator*() const {
	return *_i;
    }
};

// A global function to extract the iterator category.

template < class I> inline
iterator_traits<I>::iterator_category
query( I i) {
    return iterator_traits<I>::iterator_category();
}

// A function to match bidirectional iterators.
inline
int discr( bidirectional_iterator_tag tag) { return 42; }

int main() {
    vector<int> v;
    v.push_back(32);
    v.push_back(33);
    v.push_back(42);
    Adaptor< vector<int>::iterator> i( v.begin());
    ++i;
    assert( *i == 33);
    ++i;
    assert( *i == 42);
    assert( discr( query( i)) == 42);
    return 0;
}

// EOF //
