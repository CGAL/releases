// Copyright (c) 2002  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Alpha_shapes_2/demo/Alpha_shapes_2/Qt_widget_move_point.cpp $
// $Id: Qt_widget_move_point.cpp 45379 2008-09-08 13:10:50Z lrineau $
//
//
// Author(s)     : Laurent Rineau


#include <CGAL/basic.h>

#include "Qt_widget_move_point.h"

void Qt_widget_movepoint_helper::delete_point() { delete_pointi(); };
void Qt_widget_movepoint_helper::move_point() { move_pointi(); };
void Qt_widget_movepoint_helper::stateChanged(int i){
  if(i==2)
    activate();
  else if(i == 0)
    deactivate();
}
#include "Qt_widget_move_point.moc"
