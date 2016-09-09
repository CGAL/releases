// Copyright (c) 2010  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_NO_CPP0X_AUTO.cpp $
// $Id: CGAL_CFG_NO_CPP0X_AUTO.cpp 57530 2010-07-18 18:03:30Z glisse $
//
// Author(s)     : Sylvain Pion

//| If a compiler does not support C++0x auto
//| CGAL_CFG_NO_CPP0X_AUTO is set. 

struct A {};

void use(A) {}

A f()
{
  return A();
}

int main()
{
  auto i = f();
  A j = i;
  use(j);
  return 0;
}
