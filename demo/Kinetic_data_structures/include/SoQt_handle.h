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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/demo/Kinetic_data_structures/include/SoQt_handle.h $
// $Id: SoQt_handle.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_IO_COIN_POINTER_H
#define CGAL_KINETIC_IO_COIN_POINTER_H
#include <CGAL/basic.h>
#include <boost/intrusive_ptr.hpp>
#include <Inventor/nodes/SoNode.h>

//class SoNode;
void intrusive_ptr_add_ref(SoNode *n)
{
  n->ref();
}


void intrusive_ptr_release(SoNode *n)
{
  n->unref();
}


CGAL_BEGIN_NAMESPACE;

//! A reference counting pointer for storing pointers to Inventor objects.
/*!  Inventor objects already have reference counts built in, so I
  have to use the existing reference count.
*/
template <class T>
class SoQt_handle: public boost::intrusive_ptr<T>
{
private:
  typedef boost::intrusive_ptr<T> P;
public:
  //! Pointer constructor
  SoQt_handle(T* t): P(t){}
  //! default constructor
  SoQt_handle(): P(){}
};

CGAL_END_NAMESPACE
#endif
