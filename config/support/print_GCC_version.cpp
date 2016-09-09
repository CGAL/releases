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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/support/print_GCC_version.cpp $
// $Id: print_GCC_version.cpp 58792 2010-09-22 16:02:12Z lrineau $
// 
//
// Author(s)     : Fernando Cacciola

// Print out the gcc version

#include <iostream>


//
// Just in case this is called with a non-gcc compiler such as pgCC
//
 
#ifdef __clang_version__
#  define _CGAL_GCC_VERSION "Not GNU/CC (CLANG)"
#else
#  ifndef __GNUC__
#    define _CGAL_GCC_VERSION "Not GNU/CC"
#  endif
#endif
#ifndef _CGAL_GCC_VERSION
#  ifdef __VERSION__
#    define _CGAL_GCC_VERSION __VERSION__
#  else
#    define _CGAL_GCC_VERSION "Unknown version (_CGAL_GCC_VERSION is not defined)"
#  endif
#endif

int main()
{
  std::cout << "version=" << _CGAL_GCC_VERSION << std::endl;
  return 0;
}
