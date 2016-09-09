// Copyright (c) 2001  Tel-Aviv University (Israel).
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
// $Source: /CVSROOT/CGAL/Packages/Arrangement/include/CGAL/IO/Arr_Window_stream.h,v $
// $Revision: 1.5 $ $Date: 2003/09/18 10:19:46 $
// $Name: current_submission $
//
// Author(s)     : Eti Ezra <estere@post.tau.ac.il>

#ifndef CGAL_IO_ARR_WINDOW_STREAM_H
#define CGAL_IO_ARR_WINDOW_STREAM_H

#ifndef CGAL_ARRANGEMENT_2_H
#include <CGAL/Arrangement_2.h>
#endif

#ifndef CGAL_LEDA_WINDOW_H
#include <CGAL/IO/leda_window.h>
#endif

#ifndef CGAL_IO_FILE_DRAWER_H
#include <CGAL/IO/Pm_drawer.h>
#endif

#ifndef CGAL_IO_DRAW_PM_H
#include <CGAL/IO/draw_pm.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Dcel,class Traits, class Base_node>
Window_stream& operator << (Window_stream& os, 
                            const Arrangement_2<Dcel,Traits, Base_node>& arr)
{

  Pm_drawer< Arrangement_2<Dcel,Traits, Base_node> , Window_stream>  
                                                                 drawer(os);
  
  draw_pm(arr, drawer, os);

  return os;
}

CGAL_END_NAMESPACE

#endif






