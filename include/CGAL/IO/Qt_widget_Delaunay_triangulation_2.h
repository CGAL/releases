// Copyright (c) 2002-2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Qt_widget/include/CGAL/IO/Qt_widget_Delaunay_triangulation_2.h $
// $Id: Qt_widget_Delaunay_triangulation_2.h 32795 2006-07-30 16:38:54Z spion $
// 
//
// Author(s)     : Radu Ursu

#ifndef CGAL_QT_WIDGET_DELAUNAY_TRIANGULATION_2_H
#define CGAL_QT_WIDGET_DELAUNAY_TRIANGULATION_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Delaunay_triangulation_2.h>

namespace CGAL{

template < class Gt, class Tds >
Qt_widget&
operator<<(Qt_widget& w,  const Delaunay_triangulation_2<Gt,Tds> &dt)
{
  w.lock();
  dt.draw_triangulation(w);
  w.unlock();
  return w;
}

}//end namespace CGAL

#endif
