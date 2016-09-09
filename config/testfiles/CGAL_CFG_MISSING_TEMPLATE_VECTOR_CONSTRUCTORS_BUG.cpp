// Copyright (c) 2003  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_MISSING_TEMPLATE_VECTOR_CONSTRUCTORS_BUG.cpp $
// $Id: CGAL_CFG_MISSING_TEMPLATE_VECTOR_CONSTRUCTORS_BUG.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : Radu Ursu

// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| The flag CGAL_CFG_MISSING_TEMPLATE_VECTOR_CONSTRUCTORS_BUG is set,
//| if the std::vector class does not have defined template constructors.
//| This is a feature of SunPro 5.5.


#include <list>
#include <vector>

int main() {
  std::list<int> l;
  l.push_back(2);
  std::vector<int> v(l.begin(), l.end());
  return 0;
}
