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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Kinetic/Erase_event.h $
// $Id: Erase_event.h 59997 2010-11-30 10:05:22Z glisse $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_MOVING_OBJECT_ERASER_H_
#define CGAL_KINETIC_MOVING_OBJECT_ERASER_H_
#include <CGAL/Kinetic/basic.h>
#include <CGAL/Kinetic/Event_base.h>

namespace CGAL { namespace Kinetic {

//! Delete a single moving object from the MOT at a particular time.
/*!
  Note that this class has not been used.
*/
template <class MOT>
class Erase_event: public Event_base<int*>
{
  typedef typename MOT::Handle Handle;
  typedef typename MOT::Key Key;
public:
  Erase_event(Key k,
	      Handle mot):mot_(mot),
			   k_(k){}
  void process() {
    CGAL_LOG(Log::SOME,"Deleting object.\n");
    mot_->erase(k_);
  }

  void* kds() const {return NULL;}
  std::ostream& write(std::ostream &out) const
  {
    out << "E" << k_;
    return out;
  }
protected:
  Handle mot_;
  Key k_;
};

template <class MH>
std::ostream &operator<<(std::ostream &out, const Erase_event<MH> &moi)
{
  moi.write(out);
  return out;
}


} } //namespace CGAL::Kinetic;
#endif
