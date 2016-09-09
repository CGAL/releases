// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Matrix.h
// package       : Partition_2 (1.18)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/01/19 10:08:42 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: 2D Matrix
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef   CGAL_MATRIX_H
#define   CGAL_MATRIX_H

#include <vector>
#include <iostream>
#include <cstddef>

namespace CGAL {

template <class T>
class  Matrix : public std::vector< std::vector<T> > 
{
public:
   Matrix(size_t x = 0, size_t y = 0) : 
      std::vector< std::vector<T> > (x, std::vector<T>(y)), 
      _rows(x), _columns(y) 
   {}

   size_t rows() const { return _rows; }
   size_t columns() const { return _columns; }


protected:
   size_t _rows;
   size_t _columns;
};

template <class T> 
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
   typedef typename Matrix<T>::size_type size_type;

   for (size_type i = 0; i < m.rows(); i++) 
   {
      os << std::endl << i << " : ";
      for (size_type j = 0; j < m.columns(); j++) 
      {
         os << m[i][j] << " ";
      }
   }
   return os;
}

}

#endif // CGAL_MATRIX_H
