// ============================================================================
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
// file          : sorted_matrix_search_example.C
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// package       : $CGAL_Package: Matrix_search $
// source        : fjsearch.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:07:48 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Sorted matrix search: Example Program
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif // CGAL_RANDOM_H
#ifndef CGAL_FUNCTION_OBJECTS_H
#include <CGAL/function_objects.h>
#endif // CGAL_FUNCTION_OBJECTS_H
#ifndef CGAL_CARTESIAN_MATRIX_H
#include <CGAL/Cartesian_matrix.h>
#endif // CGAL_CARTESIAN_MATRIX_H
#ifndef CGAL_SORTED_MATRIX_SEARCH_H
#include <CGAL/sorted_matrix_search.h>
#endif // CGAL_SORTED_MATRIX_SEARCH_H
#include <vector>

using namespace std;
using namespace CGAL;

typedef int                              Value;
typedef vector< Value >                  Vector;
typedef Vector::iterator                 Value_iterator;
typedef vector< Vector >                 Vector_cont;
typedef Cartesian_matrix<
  plus< int >,
  Value_iterator,
  Value_iterator >                       Matrix;

int main() {
  // set of vectors the matrices are build from:
  Vector_cont vectors;

  // generate a random vector and sort it:
  Vector a;
  int i;
  cout << "a = ( ";
  for ( i = 0; i < 5; ++i) {
    a.push_back( default_random( 100));
    cout << a.back() << " ";
  }
  cout << ")" << endl;
  sort( a.begin(), a.end(), less< Value >());

  // build a cartesian from a:
  Matrix M( a.begin(), a.end(), a.begin(), a.end());

  // search an upper bound for max(a):
  Value bound( a[4]);
  Value upper_bound(
    sorted_matrix_search(
      &M,
      &M + 1,
      sorted_matrix_search_traits_adaptor(
        bind2nd( greater_equal< Value >(), bound),
        M)));
  cout << "upper bound for " << bound << " is "
       << upper_bound << endl;

} 
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

