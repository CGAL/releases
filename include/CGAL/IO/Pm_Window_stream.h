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
// $Source: /CVSROOT/CGAL/Packages/Planar_map/include/CGAL/IO/Pm_Window_stream.h,v $
// $Revision: 1.5 $ $Date: 2003/09/18 10:24:41 $
// $Name: current_submission $
//
// Author(s)     : Eti Ezra <estere@post.tau.ac.il>

#ifndef CGAL_IO_PM_WINDOW_STREAM_H
#define CGAL_IO_PM_WINDOW_STREAM_H

#ifndef CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#ifndef CGAL_IO_PM_DRAWER_H
#include <CGAL/IO/Pm_drawer.h>
#endif

#ifndef CGAL_IO_DRAW_PM_H
#include  <CGAL/IO/draw_pm.h>
#endif

#include <CGAL/IO/Window_stream.h>

CGAL_BEGIN_NAMESPACE

template <class Dcel,class Traits>
Window_stream & operator << (Window_stream & os,
                             const Planar_map_2<Dcel,Traits> & pm)
{
  Pm_drawer< Planar_map_2<Dcel,Traits>, Window_stream>  drawer(os);
  
  draw_pm(pm, drawer, os);

  return os;
}  


/*template <class Dcel,class Traits>
  Window_stream& write(Window_stream& os, Planar_map_2<Dcel,Traits> &m)
  {
  //  os << *m.get_bounding_box();
  Halfedge_iterator it = m.halfedges_begin(), end = m.halfedges_end();
  const Traits& traits=m.get_traits();
  while(it != end){
  write(os,it->curve(),traits);
  ++it;++it;
  }
  return os;
  } */ 

CGAL_END_NAMESPACE

#endif




