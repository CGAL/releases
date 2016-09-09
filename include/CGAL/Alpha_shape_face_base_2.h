// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Alpha_shape_face_base_2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: Alpha_shape_face_base_2.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/11/05 16:37:22 $
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

#include <CGAL/triple.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template < class Gt, class Df >
class Alpha_shape_face_base_2 : public Df
{

public:
  typedef typename Gt::Coord_type Coord_type;
  typedef triple<Coord_type, Coord_type , Coord_type> Interval_3;

public:  
  Alpha_shape_face_base_2() 
    : Df() 
    {}
  
  
  Alpha_shape_face_base_2(void* v0, void* v1, void* v2)
    : Df( v0, v1, v2) 
    {}
 
  
  
  Alpha_shape_face_base_2(void* v0, void* v1, void* v2,
			  void* n0, void* n1, void* n2)
    :  Df(v0,  v1,  v2,
	  n0,  n1,  n2) 
    {}
  
private:

  Interval_3 vec_edge[3];
  Coord_type A;

public:
  inline Coord_type get_alpha() 
    {
      return A;
    }
  
  inline void set_alpha(Coord_type AA)
    {    
      A = AA;
    }

  inline Interval_3 get_ranges(int i)
    {
      return vec_edge[i];
    }

  inline void set_ranges(int i, Interval_3 Inter)
    {
      vec_edge[i]=Inter;
    }

};

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //ALPHA_SHAPE_FACE_BASE_2_H
