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
// file          : include/CGAL/IO/Planar_map_iostream.h
// package       : Planar_map (5.73)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#include <iostream>

CGAL_BEGIN_NAMESPACE

template <class Dcel, class Traits>
::std::ostream& operator<<(::std::ostream& o, 
const Planar_map_2<Dcel,Traits>& pm) 
{
  o << "Vertices ---------------" << std::endl;
  typename Planar_map_2<Dcel,Traits>::Vertex_const_iterator vi;
  for (vi = pm.vertices_begin(); vi != pm.vertices_end(); ++vi)
    {
      o << "(" << vi->point() << ")" << std::endl;
      }
  
  o << "Halfedges ------------------" << std::endl;
  typename Planar_map_2<Dcel,Traits>::Halfedge_const_iterator ei;
  for (ei = pm.halfedges_begin(); ei != pm.halfedges_end(); ++ei)
    {
      o << "{" << ei->curve() << "}" << std::endl;
    } 
  
  o << "Faces ------------------" << std::endl;
  typename Planar_map_2<Dcel,Traits>::Face_const_iterator fi;
  
  typename Planar_map_2<Dcel,Traits>::Holes_const_iterator iccbit;
  //typename Planar_map_2<Dcel,Traits>::Holes_iterator iccbit;
  
  
  typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator ccb_circ;
  //typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator ccb_circ;
  int ck;
  int fc_counter;
  for (fc_counter=0,fi = pm.faces_begin(); fi != pm.faces_end(); 
       ++fi,fc_counter++)
    {
      o << "Face " << fc_counter << " :\n";
      o << "outer ccb: " ;
      
      if (fi->is_unbounded())
        {
          o << "UNBOUNDED"  << std::endl;
        }
      else {
        //        typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator 
        typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator 
          first = fi->outer_ccb(), iter = first;
        
        o << "[";
        do
          {
            o << "(" << iter->source()->point() << ")-";
            ++iter;
          } while (iter != first);
        o << "(" << first->source()->point() << ")]" << std::endl;    
        }
      
      
      
      for (ck=0, iccbit = (*fi).holes_begin(); iccbit != (*fi).holes_end();
           ++iccbit, ck++)
        {
          o << "inner ccb " << ck << ": " ;
          ccb_circ = (*iccbit);
          typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_const_circulator 
          //typename Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator 
            iter = ccb_circ;
          
          o << "[";
          do
            {
              o << "(" << iter->source()->point() << ")-";
              ++iter;
              } while (iter != ccb_circ);
          o << "(" << ccb_circ->source()->point() << ")]" ;
          
        }
      o << std::endl;
    }
  return o;
}

CGAL_END_NAMESPACE













