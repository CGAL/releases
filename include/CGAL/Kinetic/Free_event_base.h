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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Kinetic/Free_event_base.h $
// $Id: Free_event_base.h 36326 2007-02-15 17:48:43Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KDS_FREE_EVENT_BASE_H
#define CGAL_KDS_FREE_EVENT_BASE_H
#include <CGAL/Kinetic/basic.h>
CGAL_KINETIC_BEGIN_NAMESPACE

class Free_event_base {
public:

  Free_event_base(){}
	
  void* kds() const {
    return NULL;
  }
  
  template <class Key>
  CGAL::Comparison_result compare_concurrent(Key a,
					     Key b) const {
    if (a < b) return CGAL::SMALLER;
    else if (b < a) return CGAL::LARGER;
    else return CGAL::EQUAL;
  }	
  template <class Key>
  bool merge_concurrent(Key,
			Key) {
    return false;
  }
  template <class Key>
  void audit(Key)const{}
};

CGAL_KINETIC_END_NAMESPACE
#endif
