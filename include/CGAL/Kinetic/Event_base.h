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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Kinetic/Event_base.h $
// $Id: Event_base.h 36326 2007-02-15 17:48:43Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KDS_EVENT_BASE_H
#define CGAL_KDS_EVENT_BASE_H
#include <CGAL/Kinetic/basic.h>
CGAL_KINETIC_BEGIN_NAMESPACE

template <class KDS_ptr>
class Event_base {
public:
  typedef KDS_ptr KDS_handle;
  Event_base(KDS_ptr pt): kds_(pt){}
  Event_base(): kds_(NULL){}
	
  KDS_handle kds() const {
    return kds_;
  }
  KDS_handle kds() {
    return kds_;
  }
  template <class Key>
  CGAL::Comparison_result compare_concurrent(Key a,
					     Key b) const {
    if (a < b) return CGAL::SMALLER;
    else if (b < a) return CGAL::LARGER;
    else return CGAL::EQUAL;
    //return CGAL::compare(a,b);
  }	
  template <class Key>
  bool merge_concurrent(Key ,
			Key ) {
    return false;
  }
  template <class K>
  void audit(K ) const {}
  std::ostream &write(std::ostream &out) const {
    return out << "Event does not implement write";
  }
protected:
  KDS_handle kds_;
};

CGAL_KINETIC_END_NAMESPACE
#endif
