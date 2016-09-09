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
// file          : include/CGAL/Sorted_matrix_search_traits_adaptor.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : fjsearch.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:08 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// Frederickson-Johnson matrix search: traits class adaptor
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (SORTED_MATRIX_SEARCH_TRAITS_ADAPTOR_H)
#define SORTED_MATRIX_SEARCH_TRAITS_ADAPTOR_H 1

CGAL_BEGIN_NAMESPACE

template < class _FeasibilityTest, class _Matrix >
class Sorted_matrix_search_traits_adaptor {
public:
  typedef _FeasibilityTest         FeasibilityTest;
  typedef _Matrix                  Matrix;
  typedef typename _Matrix::Value  Value;
  typedef std::less< Value >       Compare_strictly;
  typedef std::less_equal< Value > Compare_non_strictly;

  Sorted_matrix_search_traits_adaptor(
    const FeasibilityTest& ft)
  : _ft( ft)
  {}

  Compare_strictly
  compare_strictly() const
  { return Compare_strictly(); }

  Compare_non_strictly
  compare_non_strictly() const
  { return Compare_non_strictly(); }

  bool
  is_feasible( Value a)
  { return _ft( a); }

protected:
  FeasibilityTest _ft;
};

//!!! with iterator traits we replace const Matrix&
// by an iterator with value type Matrix
template < class FeasibilityTest, class Matrix >
Sorted_matrix_search_traits_adaptor<
  FeasibilityTest, Matrix >
sorted_matrix_search_traits_adaptor(
  const FeasibilityTest& f, const Matrix&)
{
  typedef Sorted_matrix_search_traits_adaptor<
    FeasibilityTest, Matrix > Traits;
  return Traits( f);
} // sorted_matrix_search_traits_adaptor( ... )

CGAL_END_NAMESPACE

#endif // ! (SORTED_MATRIX_SEARCH_TRAITS_ADAPTOR_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

