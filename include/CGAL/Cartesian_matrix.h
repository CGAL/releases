// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Cartesian_matrix.h
// package       : Matrix_search (1.10)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : mon_search.aw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/11/26 16:25:25 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// A Representation for Cartesian Matrices
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_CARTESIAN_MATRIX_H)
#define CGAL_CARTESIAN_MATRIX_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H

template < class Operation,
           class RandomAccessIC_row,
           class RandomAccessIC_column >
class CGAL_Cartesian_matrix {
public:
  typedef typename Operation::result_type           Value;
  typedef typename Operation::first_argument_type   RowValue;
  typedef typename Operation::second_argument_type  ColumnValue;

  /*
  CGAL_Cartesian_matrix( Operation o = Operation())
  : op( o)
  {}
  */

  CGAL_Cartesian_matrix( RandomAccessIC_row r_f,
                         RandomAccessIC_row r_l,
                         RandomAccessIC_column c_f,
                         RandomAccessIC_column c_l)
  : row_vec( r_f),
    column_vec( c_f),
    n_rows( r_l - r_f),
    n_columns( c_l - c_f)
  {}

  CGAL_Cartesian_matrix( RandomAccessIC_row r_f,
                         RandomAccessIC_row r_l,
                         RandomAccessIC_column c_f,
                         RandomAccessIC_column c_l,
                         const Operation& o)
  : row_vec( r_f),
    column_vec( c_f),
    n_rows( r_l - r_f),
    n_columns( c_l - c_f),
    op( o)
  {}

  int
  number_of_rows() const
  { return n_rows; }

  int
  number_of_columns() const
  { return n_columns; }

  Value
  operator()( int r, int c) const
  {
    CGAL_optimisation_precondition( r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition( c >= 0 && c < number_of_columns());
    return op( row_vec[r], column_vec[c]);
  }

protected:
  RandomAccessIC_row     row_vec;
  RandomAccessIC_column  column_vec;
  int                    n_rows;
  int                    n_columns;
  Operation              op;
}; // class CGAL_Cartesian_matrix< ... >

template < class Operation,
           class RandomAccessIC_row,
           class RandomAccessIC_column >
inline
CGAL_Cartesian_matrix< Operation,
                       RandomAccessIC_row,
                       RandomAccessIC_column >
CGAL_cartesian_matrix( RandomAccessIC_row r_f,
                       RandomAccessIC_row r_l,
                       RandomAccessIC_column c_f,
                       RandomAccessIC_column c_l,
                       const Operation& o)
{
  return
  CGAL_Cartesian_matrix< Operation,
                         RandomAccessIC_row,
                         RandomAccessIC_column >
  ( r_f, r_l, c_f, c_l, o);
}

#endif // ! (CGAL_CARTESIAN_MATRIX_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

