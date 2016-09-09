// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/Linear_algebra_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/12/07 18:53:22 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_LINEAR_ALGEBRA_D_H
#define CGAL_CARTESIAN_LINEAR_ALGEBRA_D_H

#include <memory>
#include <vector>
#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Cartesian/Linear_algebra_vector.h>
#include <CGAL/Cartesian/Linear_algebra_matrix.h>

CGAL_BEGIN_NAMESPACE

template < class _FT >
class Linear_algebraCd
{
public:
  typedef _FT                              FT;
  typedef _FT                              RT;
  typedef Linear_algebraCd<FT>             Self;
  typedef LA_vectorCd<Self>                Vector;
  typedef LA_matrixCd<Self>                Matrix;
  typedef const FT*                        const_iterator;
  typedef FT*                              iterator;
  
  Linear_algebraCd() {}

protected:
  // Major routines for Linear_algebra_d
  void   Gaussian_elimination(const Matrix &M,
            Matrix &L, Matrix &U,
            std::vector<int> &row_permutation,
            std::vector<int> &column_permutation,
	    FT &det, int &rank, Vector &c) const;
  void   Triangular_system_solver(const Matrix &U, const Vector &x,
            Vector &x, FT &det) const;
  void   Triangular_left_inverse(const Matrix &U,
            Matrix &Uinv) const;

public:
  std::pair<int,int> transpose(std::pair<int,int> dim) const;
  Matrix transpose(const Matrix &M) const;

  bool   inverse(const Matrix &M, Matrix &I, FT &D, Vector &c) const;
  Matrix inverse(const Matrix &M, RT &D) const;
  
  FT     determinant(const Matrix &M, Matrix &L, Matrix &U,
	     std::vector<int> &q, Vector &c) const;
  FT     determinant(const Matrix &M) const;
  Sign   sign_of_determinant(const Matrix &M) const;
  bool   verify_determinant(const Matrix &M,
             const Matrix &L, const Matrix &U, const RT &D,
             const std::vector<int> &q, const Vector &c) const;
 
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D, Matrix &spanning_vectors, Vector &c) const;
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D, Vector &c) const;
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D) const;
  bool   is_solvable(const Matrix &M, const Vector &b) const;

  bool   homogeneous_linear_solver(const Matrix &M, Vector &x) const;
  int    homogeneous_linear_solver(const Matrix &M,
             Matrix &spanning_vectors) const;

  int    rank(const Matrix &M);
  int    rank(const Matrix &M, std::vector<int> &q) const;
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Linear_algebra_d.C>
#endif 

#endif // CGAL_CARTESIAN_VECTOR_D_H
