// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/Pm_bops_default_dcel.h
// package       : PmOverlay (2.0.2)
// source        : CGAL/progs/ovl/ovl-for-bops1.3/Pm_bops_default_dcel.h 
// revision      : 1.0.1
// revision_date : $14 Dec 1998$
// author(s)     : Petru Pau
//
// coordinator   : RISC Linz (Sabine Stifter) 
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_BOPS_DEFAULT_DCEL_H
#define CGAL_PM_BOPS_DEFAULT_DCEL_H 

#ifndef CGAL_PM_DEFAULT_DCEL_H
#include <CGAL/Pm_default_dcel.h>
#endif

#define CGAL_Pm_ovl_color 	 	_Pmcol_
#define CGAL_Pm_ovl_three_colors  	_Pm3col_
#define CGAL_Pm_bops_vertex_base 	_Pmbvb_
#define CGAL_Pm_bops_halfedge_base 	_Pmbhb_
#define CGAL_Pm_bops_face_base 		_Pmbfb_
#define CGAL_Pm_bops_default_dcel	_Pmbdd_

enum CGAL_Pm_ovl_color{
  CGAL_Pm_ovl_NO_COLOR 	= 0,   // the unbounded face will have NO_COLOR 
  CGAL_Pm_ovl_RED	= 1,   // first planar map
  CGAL_Pm_ovl_BLACK 	= 2,   // second planar map
  CGAL_Pm_ovl_RED_AND_BLACK = 3,
  CGAL_Pm_ovl_UNCOLORED = -1   // faces that have not been yet colored
};

struct CGAL_Pm_ovl_three_colors
  {
    CGAL_Pm_ovl_color map_color;
    CGAL_Pm_ovl_color edge_color;
    CGAL_Pm_ovl_color left_face_color;
  };

template <class Pt>
class CGAL_Pm_bops_vertex_base : public CGAL_Pm_vertex_base<Pt>{
public:
  typedef CGAL_Pm_ovl_color Info_vertex;

protected:
  Info_vertex v_info;
 
public:

  CGAL_Pm_bops_vertex_base() {}
  CGAL_Pm_bops_vertex_base( const Pt& p ) : CGAL_Pm_vertex_base<Pt>(p) { }
  
  void set_info(const Info_vertex& c)   {  v_info = c;   }
  Info_vertex info() const   		{  return v_info;   }
  
};



template <class X_curve>
class CGAL_Pm_bops_halfedge_base : public CGAL_Pm_halfedge_base<X_curve>{
public:
  typedef CGAL_Pm_ovl_three_colors Info_edge;
  
protected:
  Info_edge e_info;

public:
  CGAL_Pm_bops_halfedge_base() {}
  CGAL_Pm_bops_halfedge_base(const X_curve& c) : CGAL_Pm_halfedge_base<X_curve>(c) { }

  void set_info(const Info_edge& c)   	{  e_info = c;   }
  Info_edge info()     const   		{  return e_info;   }

};


class CGAL_Pm_bops_face_base :  public CGAL_Pm_face_base {
public:
  typedef CGAL_Pm_ovl_color Info_face;

protected:
  Info_face f_info;

public:
  CGAL_Pm_bops_face_base() : CGAL_Pm_face_base() {};

  void set_info(const Info_face& c)   	{  f_info = c;   }
  Info_face info()	       const 	{  return f_info;   }

};



///////////////////////////////////////////////////////////////
//               DEFAULT BOPS DCEL
///////////////////////////////////////////////////////////////

template <class Traits>
class CGAL_Pm_bops_default_dcel
  : public CGAL_Pm_dcel<
CGAL_Pm_bops_vertex_base<typename Traits::Point>,
CGAL_Pm_bops_halfedge_base<typename Traits::X_curve>,
CGAL_Pm_bops_face_base
> 
{
public:  // CREATION  
  typedef CGAL_Pm_bops_vertex_base<typename Traits::Point>::
    Info_vertex Info_vertex;
  typedef CGAL_Pm_bops_face_base::
    Info_face Info_face;
  typedef CGAL_Pm_bops_halfedge_base<typename Traits::X_curve>::
    Info_edge Info_edge;
  

  CGAL_Pm_bops_default_dcel() {}
  
};




#endif 
// EOF //









