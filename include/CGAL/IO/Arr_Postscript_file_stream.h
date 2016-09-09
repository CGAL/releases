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
// $Source: /CVSROOT/CGAL/Packages/Arrangement/include/CGAL/IO/Arr_Postscript_file_stream.h,v $
// $Revision: 1.4 $ $Date: 2003/09/18 10:19:46 $
// $Name: current_submission $
//
// Author(s)     : Eti Ezra <estere@post.tau.ac.il>

#ifndef CGAL_IO_ARR_POSTSCRIPT_FILE_STREAM_H
#define CGAL_IO_ARR_POSTSCRIPT_FILE_STREAM_H

#ifndef CGAL_POSTSCRIPT_FILE_STREAM_H
#include <CGAL/IO/Postscript_file_stream.h>
#endif

#ifndef CGAL_ARRANGEMENT_2_H
#include <CGAL/Arrangement_2.h>
#endif

/*
#ifndef CGAL_IO_PM_BOUNDING_BOX_BASE_WINDOW_STREAM_H
#include <CGAL/IO/Pm_bounding_box_base_Window_stream.h>
#endif
*/

#ifndef CGAL_IO_FILE_DRAWER_H
#include <CGAL/IO/Pm_drawer.h>
#endif

#ifndef CGAL_IO_DRAW_PM_H
#include <CGAL/IO/draw_pm.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Dcel,class Traits, class Base_node>
Postscript_file_stream& operator << (Postscript_file_stream & ps,  
                                     const Arrangement_2<Dcel, Traits, 
                                     Base_node>& arr)
{

  Pm_drawer<  Arrangement_2<Dcel,Traits, Base_node> , 
    Postscript_file_stream>  drawer(ps);
  
  draw_pm(arr, drawer, ps);

  return ps;
}  

CGAL_END_NAMESPACE

#endif

