// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// file          : examples/PmOverlay/example.C
// source        : test/PmOverlay/test_homogeneous.h
// revision      : $Revision: 1.0.1 $
// revision_date : $14/07/98 $
// author(s)     : Petru Pau
//
// coordinator   : RISC Linz (Sabine Stifter)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/Homogeneous.h>
#include <CGAL/Pm_segment_exact_traits.h>
#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>
#include <iostream>

#include <CGAL/Pm_overlay_for_bops.h>

typedef double			 		Basetype;
typedef CGAL::Homogeneous<Basetype>	    	Rep_class;
typedef CGAL::Pm_segment_exact_traits<Rep_class>	Pmtraits;

typedef Pmtraits::Point 		Point;
typedef Pmtraits::X_curve		Curve;

typedef CGAL::Pm_default_dcel<Pmtraits>      	Pmdcel;
typedef CGAL::Planar_map_2<Pmdcel, Pmtraits>	Planar_map;

typedef CGAL::Pm_bops_default_dcel<Pmtraits>  	Bops_dcel;
typedef CGAL::Planar_map_2<Bops_dcel, Pmtraits> 	Bops_planar_map;

int main()
{

  Planar_map pm1;
  Planar_map pm2;
  Bops_planar_map pm3;
  
  Point A[3];
  A[0] = Point(0, 0, 1);
  A[1] = Point(4, 0, 1);
  A[2] = Point(0, 4, 1);
  
  pm1.insert(Curve(A[0], A[1]));
  pm1.insert(Curve(A[1], A[2]));
  pm1.insert(Curve(A[2], A[0]));

  A[0] = Point(1, 1, 1);
  A[1] = Point(4, 2, 1);
  A[2] = Point(2, 4, 1);
  
  pm2.insert(Curve(A[0], A[1]));
  pm2.insert(Curve(A[1], A[2]));
  pm2.insert(Curve(A[2], A[0]));

  CGAL::Pm_overlay_for_bops<Pmtraits>(pm1, pm2, pm3);

  if (pm3.is_valid()){
    Bops_planar_map::Halfedge_iterator hi;
    Bops_planar_map::Vertex_iterator vi;
    Bops_planar_map::Face_iterator fi;

    std::cout << "Successfully computed the overlay:\n\n";
    
    std::cout << "Vertices" << std::endl;
    
    for (vi=pm3.vertices_begin(); vi!=pm3.vertices_end(); ++vi){
      std::cout << "(" << (*vi).point() << ")" ;
      
      switch((int)(*vi).info()){
      case 1: std::cout << " - Red" << std::endl;
	break;
      case 2: std::cout << " - Black" << std::endl;
	break;
      case 3: std::cout << " - Red and Black" << std::endl;
      }
    }

    std::cout << "------------------" << std::endl;
    std::cout << "Edges " << std::endl;
    
    for (hi=pm3.halfedges_begin(); hi!=pm3.halfedges_end(); ++hi){
      if ((*hi).source()->point().x()< (*hi).target()->point().x() ||
	  (*hi).source()->point().x()==(*hi).target()->point().x() &&
	  (*hi).source()->point().y()< (*hi).target()->point().y()){
	std::cout << "(" << (*hi).source()->point() << ") - (" 
                  << (*hi).target()->point() << ")";
	switch((int)(*hi).info().edge_color){
	case 1: std::cout << " - Red" << std::endl;
	  break;
	case 2: std::cout << " - Black" << std::endl;
	  break;
	case 3: std::cout << " - Red and Black" << std::endl;
	}
      }
    }

    std::cout << "------------------" << std::endl;
    std::cout << "Faces " << std::endl;

    Bops_planar_map::Halfedge_handle he, he_next;

    for (fi=pm3.faces_begin(); fi!=pm3.faces_end(); ++fi){
       if (!(*fi).is_unbounded()){
	 he = (*fi).halfedge_on_outer_ccb();
	 he_next = he;
	
	 do{
	   std::cout << "(" << (*he_next).source()->point() << ") -";
	   he_next = (*he_next).next_halfedge();
	 } while (he!=he_next);
	
	 switch((int)(*fi).info()){
	 case 0: std::cout << " No color" << std::endl;
	   break;
	 case 1: std::cout << " Red" << std::endl;
	   break;
	 case 2: std::cout << " Black" << std::endl;
	   break;
	 case 3: std::cout << " Red and Black" << std::endl;
	 }
       }
       else
	 std::cout << "Unbounded face - No color" << std::endl;
       }

  }
  else {
    std::cout << "The overlay is not a valid planar map!\n";
    return -1;
  }

  return 0;
  
}
