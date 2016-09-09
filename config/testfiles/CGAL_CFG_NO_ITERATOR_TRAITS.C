// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : config/testfiles/CGAL_CFG_NO_ITERATOR_TRAITS.C
// package       : Configuration (2.11)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
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

#include <iterator>
#include <vector>

// This class implements an iterator adaptor that forwards all
// member function calls to its template argument. It uses 
// iterator traits to derive correct types and iterator category.

#ifdef  _MSC_VER
using namespace std; // MSC hates "using std::{blah};"....
#  if _MSC_VER < 1300
#    define typename     // preventing MSVC 6.0 "error C2899:
                     // typename cannot be used outside a template
#  endif  // MSVC 6.0
#else
using std::iterator_traits;
#endif // _MSC_VER

template < class I,
           class category = typename iterator_traits<I>::iterator_category >
class Adaptor {
    I _i;
public:
    typedef typename iterator_traits<I>::value_type       value_type;
    typedef typename iterator_traits<I>::difference_type  difference_type;
    typedef typename iterator_traits<I>::reference        reference;
    typedef typename iterator_traits<I>::pointer          pointer;
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
typename iterator_traits<I>::iterator_category
query( I) {
    return iterator_traits<I>::iterator_category();
}

// A function to match bidirectional iterators.
inline
int discr( std::bidirectional_iterator_tag ) { return 42; }

bool all_assertions_correct = true;

int main() {
    std::vector<int> v;
    v.push_back(32);
    v.push_back(33);
    v.push_back(42);
    Adaptor< std::vector<int>::iterator> i( v.begin());
    ++i;
    all_assertions_correct &= ( *i == 33);
    ++i;
    all_assertions_correct &= ( *i == 42);
    all_assertions_correct &= ( discr( query( i)) == 42);
    return !all_assertions_correct;
}

