// Copyright (c) 2005  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_MATCHING_BUG_6.cpp $
// $Id: CGAL_CFG_MATCHING_BUG_6.cpp 54983 2010-03-29 09:12:07Z lrineau $
// 
//
// Author(s)     : Andreas Fabri

//| VC 7.3 does not recognize when an operator in a class
//| redefines the operator with the same signature in a base class
//| It happens with the regular triangulation.
//| No minimal testcase yet

#if (defined _MSC_VER && ! defined __INTEL_COMPILER) || defined __SUNPRO_CC

#error "this should not compile and that is good so"

#endif

int main()
{
  return 0;
}
