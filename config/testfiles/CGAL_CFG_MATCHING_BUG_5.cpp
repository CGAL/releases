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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_MATCHING_BUG_5.cpp $
// $Id: CGAL_CFG_MATCHING_BUG_5.cpp 54955 2010-03-26 17:19:18Z lrineau $
// 
//
// Author(s)     : Sylvain Pion

//| This flag is set, if a compiler cannot distinguish the signature
//| of overloaded function templates, which have one template parameter
//| to be passed explicitely when being called.
//| 
//| This bug appears for example on g++ 3.3 and 3.4 (but not on more recent
//| g++ version). This bug appears also on Sun CC 5.90.

template < typename T >
struct A {};

template < typename T, typename U >
T enum_cast(const U&) { return T(); }

template < typename T, typename U >
T enum_cast(const A<U>&) { return T(); }

int main()
{
  A<double> a;
  int i = enum_cast<int>(a);
  (void) i;
  return 0;
}
