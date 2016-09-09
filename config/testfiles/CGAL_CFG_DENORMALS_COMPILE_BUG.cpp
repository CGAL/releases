// Copyright (c) 2004  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_DENORMALS_COMPILE_BUG.cpp $
// $Id: CGAL_CFG_DENORMALS_COMPILE_BUG.cpp 49022 2009-04-29 20:03:21Z spion $
// 
//
// Author(s)     : Sylvain Pion

//| This flag is set if the compiler bugs when handling denormal values at
//| compile time.  At least PGCC 7.1-2 has the bug.

#undef NDEBUG
#include <cassert>

int main()
{
  double d = 5e-324;
  assert(d != 0);
  return 0;
}
