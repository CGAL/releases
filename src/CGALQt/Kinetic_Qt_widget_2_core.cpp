// Copyright (c) 2005  Stanford University (USA).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/src/CGALQt/Kinetic_Qt_widget_2_core.cpp $
// $Id: Kinetic_Qt_widget_2_core.cpp 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#include <CGAL/basic.h>
#include <CGAL/Kinetic/IO/internal/Qt_widget_2_core.h>

#include "Kinetic_Qt_widget_2_core.moc"

namespace CGAL { namespace Kinetic { namespace internal {
void Qt_widget_2_core::redraw() {
  lock();
  clear();
  //std::cout << "size of drawables = " << drawable_s.size() << std::endl;
  is_drawn_=false;
  CGAL_KINETIC_NOTIFY(PICTURE_IS_CURRENT);
  //if (drawable_!= NULL) drawable_->new_notification(Listener::PICTURE_IS_CURRENT);
  is_drawn_=true;
  unlock();
  //::CGAL::Qt_widget::redraw();
}

Qt_widget_2_core::Qt_widget_2_core(QMainWindow *parent): ::CGAL::Qt_widget(parent) {
  //drawable_=NULL;
  is_drawn_=false;
}
} } } //namespace CGAL::Kinetic::internal
