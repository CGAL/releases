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
// file          : include/CGAL/Alpha_shape_vertex_base_3.h
// package       : Alpha_shapes_3 (3.6)
// source        : $RCSfile: Alpha_shape_vertex_base_3.h,v $
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/07/02 08:40:54 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef ALPHA_SHAPE_VERTEX_BASE_3_H
#define ALPHA_SHAPE_VERTEX_BASE_3_H

#include <utility>
#include <CGAL/Triangulation_vertex_base_3.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template <class Gt>
class Alpha_shape_vertex_base_3 : public Triangulation_vertex_base_3<Gt>
{
public:

  typedef typename Gt::Coord_type Coord_type;
  typedef std::pair< Coord_type, Coord_type > Interval2;  
  typedef typename Gt::Point Point;

  //-------------------------------------------------------------------
private:

  Interval2 I;

  //-------------------------------------------------------------------
public:

  Alpha_shape_vertex_base_3()
    : Triangulation_vertex_base_3<Gt>()
    {}
  
  Alpha_shape_vertex_base_3(const Point& p)
    : Triangulation_vertex_base_3<Gt>(p)
    {}
  
  Alpha_shape_vertex_base_3(const Point& p, void* f)
    : Triangulation_vertex_base_3<Gt>(p, f) 
    {}

  //-------------------------------------------------------------------

  inline Interval2 get_range()
    {
      return I;
    }

  inline void set_range(Interval2 Inter)
    {
      I = Inter;
    }

};

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //ALPHA_SHAPE_VERTEX_BASE_3_H
