// Copyright (c) 1997  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/IO/Planar_map_iostream.h,v $
// $Revision: 1.2 $ $Date: 2003/09/18 10:24:40 $
// $Name: current_submission $
//
// Author(s)     : Iddo Hanniel <hanniel@math.tau.ac.il>
//                 Oren Nechushtan <theoren@math.tau.ac.il>

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













