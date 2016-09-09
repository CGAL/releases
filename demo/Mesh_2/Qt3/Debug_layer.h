// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_2/demo/Mesh_2/Qt3/Debug_layer.h $
// $Id: Debug_layer.h 56247 2010-05-14 14:05:51Z afabri $
//
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_DEBUG_LAYER_H
#define CGAL_DEBUG_LAYER_H

#include <CGAL/IO/Qt_widget_layer.h>
#include <iostream>

namespace CGAL {

class Debug_layer : public Qt_widget_layer
{
  std::ostream& stream;

public:

  Debug_layer(std::ostream& s = std::cerr) : stream(s)
  {
  }

  void draw()
  {
    stream << "redraw()" << std::endl;
  }
}; // end class Debug_layer

} // end namespace CGAL

#endif // CGAL_DEBUG_LAYER_H
