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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_NO_CPP0X_RVALUE_REFERENCE.cpp $
// $Id: CGAL_CFG_NO_CPP0X_RVALUE_REFERENCE.cpp 49022 2009-04-29 20:03:21Z spion $
//
// Author(s)     : Sylvain Pion

//| If a compiler does not support rvalue references (from C++0x)
//| CGAL_CFG_NO_RVALUE_REFERENCE is set. 

struct A {
  A () {}

  // copy semantics
  A (const A&) {}
  A& operator=(const A&) { return *this; }

  // move semantics
  A (A&&) {}
  A& operator=(A&&) { return *this; }

  ~A () {}
};

A f()
{
  return A();
}

int main()
{
  A a = f();
  A b;
  b = a;
  b = f();
  return 0;
}
