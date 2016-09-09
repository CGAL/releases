// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Linear_algebraCd.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2001/07/09 12:01:37 $
// author(s)     : Herve.Bronnimann
// coordinator   : Michael.Seel
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_LINEAR_ALGEBRACD_H
#define CGAL_LINEAR_ALGEBRACD_H

#include <CGAL/Kernel_d/Vector__.h>
#include <CGAL/Kernel_d/Matrix__.h>
#include <memory>
#include <vector>
#undef _DEBUG
#define _DEBUG 13
#include <CGAL/Kernel_d/debug.h>

//#define CGAL_LA_SELFTEST

CGAL_BEGIN_NAMESPACE

template < class _FT, class _AL = CGAL_ALLOCATOR(_FT) >
class Linear_algebraCd
{
public:
  typedef _FT                     FT;
  typedef _FT                     RT;
  typedef _AL                     AL;
  typedef Linear_algebraCd<FT,AL> Self;
  typedef CGALLA::Vector_<FT,AL>  Vector;
  typedef CGALLA::Matrix_<FT,AL>  Matrix;
  typedef const FT*               const_iterator;
  typedef FT*                     iterator;
  
  Linear_algebraCd() {}

protected:
  // Major routines for Linear_algebra_d
  static 
  void   Gaussian_elimination(const Matrix &M,
            Matrix &L, Matrix &U,
            std::vector<int> &row_permutation,
            std::vector<int> &column_permutation,
            FT &det, int &rank, Vector &c);
  static 
  bool Triangular_system_solver(const Matrix &U, const Matrix &L, 
            const Vector &b, int rank, Vector &x, FT &det);
  static 
  void   Triangular_left_inverse(const Matrix &U, Matrix &Uinv);

public:
  static
  std::pair<int,int> transpose(std::pair<int,int> dim)
  { std::swap(dim.first,dim.second); return dim; }
  static 
  Matrix transpose(const Matrix &M);

  static
  bool   inverse(const Matrix &M, Matrix &I, FT &D, Vector &c);

  static
  Matrix inverse(const Matrix &M, RT &D);

  static
  FT     determinant(const Matrix &M, Matrix &L, Matrix &U,
             std::vector<int> &q, Vector &c);
  static
  FT     determinant(const Matrix &M);

  static
  Sign   sign_of_determinant(const Matrix &M);

  static
  bool   verify_determinant(const Matrix &M, const RT &D,
             const Matrix &L, const Matrix &U, 
             const std::vector<int> &q, const Vector &c);
  static
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D, Matrix &spanning_vectors, Vector &c);
  static
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D, Vector &c);
  static
  bool   linear_solver(const Matrix &M, const Vector &b,
             Vector &x, RT &D);
  static
  bool   is_solvable(const Matrix &M, const Vector &b);

  static
  bool   homogeneous_linear_solver(const Matrix &M, Vector &x);
  static
  int    homogeneous_linear_solver(const Matrix &M,
             Matrix &spanning_vectors);
  static
  int rank(const Matrix &M);

  static 
  int independent_columns(const Matrix& M, std::vector<int>& columns); 

};

CGAL_END_NAMESPACE

#include <CGAL/Kernel_d/Linear_algebraCd.C>

#endif // CGAL_LINEAR_ALGEBRACD_H


