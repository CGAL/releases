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
// file          : include/CGAL/Alpha_shape_cell_base_3.h
// package       : Alpha_shapes_3 (3.6)
// source        : $RCSfile: Alpha_shape_cell_base_3.h,v $
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/07/23 12:14:31 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef ALPHA_SHAPE_CELL_BASE_3_H
#define ALPHA_SHAPE_CELL_BASE_3_H

#include <vector>
#include <CGAL/triple.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template < class Gt, class Df >
class Alpha_shape_cell_base_3 : public Df
{
public:

  typedef typename Gt::Rep Rp;               // A corriger avec Monique
  typedef typename Rp::FT Coord_type;        // A corriger avec Monique
  typedef triple<Coord_type, Coord_type , Coord_type> Interval3;

  //-------------------------------------------------------------------
private:

  Interval3 vec_facet[4];
  Interval3 vec_edge[4][4];
  Coord_type A;

  //-------------------------------------------------------------------
public:
  
  Alpha_shape_cell_base_3() 
    : Df()
    {}
  
  Alpha_shape_cell_base_3(void* v0, void* v1, void* v2, void* v3)
    : Df( v0, v1, v2, v3)
    {}
  
  Alpha_shape_cell_base_3(void* v0, void* v1, void* v2, void* v3,
			  void* n0, void* n1, void* n2, void* n3)
    : Df(v0,  v1,  v2, v3,
	 n0,  n1,  n2, n3)
    {}

  //-------------------------------------------------------------------

  inline Coord_type get_alpha()
    {
      return A;
    }
  
  inline void set_alpha(Coord_type AA)
    {
      A = AA;
    }

  inline Interval3 get_facet_ranges(const int& i)
    {
      return vec_facet[i];
    }

  inline void set_facet_ranges(const int& i, const Interval3& Inter)
    {
      vec_facet[i]=Inter;
    }
  
  inline Interval3 get_edge_ranges(const int& i, const int& j)
    {
      return vec_edge[i][j];
    }

  inline void set_edge_ranges(const int& i, const int& j, 
			      const Interval3& Inter)
    {
      vec_edge[i][j]=Inter;
    }
  
};

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //ALPHA_SHAPE_CELL_BASE_3_H
