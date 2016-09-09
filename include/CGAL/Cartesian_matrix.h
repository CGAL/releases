// ======================================================================
//
// Copyright (c) 1998, 1999, 2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian_matrix.h
// package       : Matrix_search (1.43)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.43 $
// revision_date : $Date: 2000/09/15 07:25:29 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH
//
// A Representation for Cartesian Matrices
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#if ! (CGAL_CARTESIAN_MATRIX_H)
#define CGAL_CARTESIAN_MATRIX_H 1

#include <CGAL/basic.h>
#include <CGAL/Optimisation/assertions.h>

CGAL_BEGIN_NAMESPACE

template < class Operation,
           class RandomAccessIC_row,
           class RandomAccessIC_column >
class Cartesian_matrix {
public:
  typedef typename Operation::result_type           Value;
  typedef typename Operation::first_argument_type   RowValue;
  typedef typename Operation::second_argument_type  ColumnValue;

  Cartesian_matrix(RandomAccessIC_row r_f,
                   RandomAccessIC_row r_l,
                   RandomAccessIC_column c_f,
                   RandomAccessIC_column c_l)
  : row_vec(r_f),
    column_vec(c_f),
    n_rows(r_l - r_f),
    n_columns(c_l - c_f)
  {}

  Cartesian_matrix(RandomAccessIC_row r_f,
                   RandomAccessIC_row r_l,
                   RandomAccessIC_column c_f,
                   RandomAccessIC_column c_l,
                   const Operation& o)
  : row_vec(r_f),
    column_vec(c_f),
    n_rows(r_l - r_f),
    n_columns(c_l - c_f),
    op(o)
  {}

  int
  number_of_rows() const
  { return n_rows; }

  int
  number_of_columns() const
  { return n_columns; }

  Value
  operator()(int r, int c) const
  {
    CGAL_optimisation_precondition(r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition(c >= 0 && c < number_of_columns());
    return op(row_vec[r], column_vec[c]);
  }

protected:
  RandomAccessIC_row     row_vec;
  RandomAccessIC_column  column_vec;
  int                    n_rows;
  int                    n_columns;
  Operation              op;
}; // class Cartesian_matrix< ... >

template < class Operation,
           class RandomAccessIC_row,
           class RandomAccessIC_column >
inline
Cartesian_matrix< Operation,
                       RandomAccessIC_row,
                       RandomAccessIC_column >
cartesian_matrix( RandomAccessIC_row r_f,
                       RandomAccessIC_row r_l,
                       RandomAccessIC_column c_f,
                       RandomAccessIC_column c_l,
                       const Operation& o)
{
  return
  Cartesian_matrix< Operation,
                         RandomAccessIC_row,
                         RandomAccessIC_column >
  ( r_f, r_l, c_f, c_l, o);
}

CGAL_END_NAMESPACE

#endif // ! (CGAL_CARTESIAN_MATRIX_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

