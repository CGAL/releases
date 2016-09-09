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
// file          : include/CGAL/Alpha_shape_face_base_2.h
// package       : Alpha_shapes_2 (11.19)
// source        : $RCSfile: Alpha_shape_face_base_2.h,v $
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/01/22 11:02:42 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ALPHA_SHAPE_FACE_BASE_2_H
#define CGAL_ALPHA_SHAPE_FACE_BASE_2_H

#include <CGAL/utility.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Df >
class Alpha_shape_face_base_2 : public Df
{
public:
  typedef typename Gt::Coord_type Coord_type;
  typedef Triple<Coord_type, Coord_type, Coord_type> Interval_3;

  Alpha_shape_face_base_2() 
    : Df() 
    {}
  
  Alpha_shape_face_base_2(void* v0, void* v1, void* v2)
    : Df(v0, v1, v2)
    {}
  
  Alpha_shape_face_base_2(void* v0, void* v1, void* v2,
			  void* n0, void* n1, void* n2)
    : Df(v0, v1, v2, n0, n1, n2)
    {}

  const Coord_type & get_alpha() const
    {
      return A;
    }

  void set_alpha(const Coord_type & AA)
    {
      A = AA;
    }

  const Interval_3 & get_ranges(int i) const
    {
      return vec_edge[i];
    }

  void set_ranges(int i, const Interval_3& Inter)
    {
      vec_edge[i]=Inter;
    }

private:
  Interval_3 vec_edge[3];
  Coord_type A;
};

CGAL_END_NAMESPACE

#endif //ALPHA_SHAPE_FACE_BASE_2_H
