// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_COMMA_BUG.cpp $
// $Id: CGAL_CFG_COMMA_BUG.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : Sylvain Pion

// ---------------------------------------------------------------------
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| This flag is set, if the compiler does not properly parse comma separated
//| expressions in a base constructor call. (e.g. g++ 3.3).

struct P {
  P() {}
};

struct B {
  B(int) {}
};

struct A {
  B j;
  A(int i) : j((P(), i)) {}
};

int main()
{
  A a(0);
  return 0;
}
