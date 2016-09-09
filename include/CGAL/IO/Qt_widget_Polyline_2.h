// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Arrangement_on_surface_2/include/CGAL/IO/Qt_widget_Polyline_2.h $
// $Id: Qt_widget_Polyline_2.h 39957 2007-08-22 12:30:17Z efif $
// $Date: 2007-08-22 14:30:17 +0200 (Wed, 22 Aug 2007) $
// 
//
// Author(s)     : Ron Wein  <wein@post.tau.ac.il>
//                 Efi Fogel <efif@post.tau.ac.il>

#ifndef CGAL_QT_WIDGET_POLYLINE_2_H
#define CGAL_QT_WIDGET_POLYLINE_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Arr_traits_2/Polyline_2.h>

CGAL_BEGIN_NAMESPACE

/*!
 * Export a polyline to a window stream 
 */
template <class T_SegmentTraits>
Qt_widget & operator<<(Qt_widget & ws, const _Polyline_2<T_SegmentTraits> & cv)
{
  for (unsigned int i = 0; i < cv.size(); ++i) ws << cv[i];
  return ws;
}

CGAL_END_NAMESPACE

#endif
