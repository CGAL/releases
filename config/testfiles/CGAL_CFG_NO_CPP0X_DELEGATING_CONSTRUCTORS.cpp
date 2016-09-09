// Copyright (c) 2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_NO_CPP0X_DELEGATING_CONSTRUCTORS.cpp $
// $Id: CGAL_CFG_NO_CPP0X_DELEGATING_CONSTRUCTORS.cpp 49022 2009-04-29 20:03:21Z spion $
//
// Author(s)     : Sylvain Pion

//| If a compiler does not support delegating constructors (from C++0x)
//| CGAL_CFG_NO_CPP0X_DELEGATING_CONSTRUCTORS is set. 

#undef NDEBUG
#include <cassert>

struct A {
  A () : A(10) {}
  A (int ii) : i(ii) {}

  int i;
};

int main()
{
  A a;
  A b(1);
  assert(a.i == 10);
  assert(b.i == 1);
  return 0;
}
