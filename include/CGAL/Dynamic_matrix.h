// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Dynamic_matrix.h
// package       : Matrix_search (1.54)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.52 $
// revision_date : $Date: 2002/03/25 15:04:54 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// A Representation for Dynamic Matrices
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_DYNAMIC_MATRIX_H)
#define CGAL_DYNAMIC_MATRIX_H 1

#include <CGAL/Optimisation/assertions.h>

CGAL_BEGIN_NAMESPACE

template < class Matrix >
class Dynamic_matrix
// adaptor for a matrix class
// to allow replacement of columns in constant time
// and extraction of all even rows in linear time
{
public:
  typedef std::vector< int >        CoordContainer;
  typedef Dynamic_matrix< Matrix >  ThisMatrixClass;
  typedef typename Matrix::Value    Value;

  Dynamic_matrix( const Matrix& m, int r_p = 0)
  : matrix( &m),
    column_indices( m.number_of_columns()),
    row_power( r_p),
    row_offset( (1 << r_p) - 1)
  {
    for ( unsigned int i( 0); i < column_indices.size(); ++i)
      column_indices[i] = i;
  }

  int
  number_of_rows() const
  {
    return ( matrix->number_of_rows() + row_offset) >> row_power;
  }

  int
  number_of_columns() const
  { return column_indices.size(); }

  Value
  operator()( int r, int c) const
  {
    CGAL_optimisation_precondition( r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition( c >= 0 && c < number_of_columns());
    return (*matrix)( r << row_power, column_indices[c]);
  }

  Value
  operator()( std::pair< int, int > p) const
  {
    return (*this)( p.first, p.second);
  }

  void
  replace_column( int o, int n)
  {
    CGAL_optimisation_precondition( o >= 0 && o < number_of_columns());
    CGAL_optimisation_precondition( n >= 0 && n < number_of_columns());
    column_indices[o] = column_indices[n];
  }

  void
  shrink_to_quadratic_size()
  {
    CGAL_optimisation_precondition( number_of_columns() >= number_of_rows());
    column_indices.erase( column_indices.begin() + number_of_rows(),
                          column_indices.end());
    CGAL_optimisation_postcondition( number_of_columns() == number_of_rows());
  }

private:
  Dynamic_matrix( const Matrix* m, const CoordContainer& c_i, int r_p)
  : matrix( m),
    column_indices( c_i),
    row_power( r_p),
    row_offset( (1 << r_p) - 1)
  {}

public:
  ThisMatrixClass*
  extract_all_even_rows() const
  {
    return new ThisMatrixClass( matrix, column_indices, row_power + 1);
  }

private:
  const Matrix*  matrix;
  CoordContainer column_indices;
  int            row_power;
  int            row_offset;
};

template < class Matrix >
inline
Dynamic_matrix< Matrix >
dynamic_matrix( const Matrix& m)
{ return Dynamic_matrix< Matrix >( m); }

CGAL_END_NAMESPACE

#endif // ! (CGAL_DYNAMIC_MATRIX_H)
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

