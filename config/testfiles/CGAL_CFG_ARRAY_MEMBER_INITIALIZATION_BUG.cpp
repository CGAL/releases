// Copyright (c) 2009  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Installation/config/testfiles/CGAL_CFG_ARRAY_MEMBER_INITIALIZATION_BUG.cpp $
// $Id: CGAL_CFG_ARRAY_MEMBER_INITIALIZATION_BUG.cpp 51248 2009-08-14 11:39:14Z spion $
//
// Author(s)     : Sylvain Pion

//| g++ 4.4.0 and 4.4.1 have a bug here.  Most probably VC++ as well.

struct M
{
  M() {}
  ~M() {}
};

struct S
{
  M m[1];

  S ()
   : m ((M[1]) { M () }) {}
};

int main()
{
  S s;
  return 0;
}
