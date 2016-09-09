// Copyright (c) 1999,2001  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Kernel_23/include/CGAL/Fourtuple.h,v $
// $Revision: 1.8 $ $Date: 2003/10/21 12:18:04 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Andreas Fabri

#ifndef CGAL__FOURTUPLE_H
#define CGAL__FOURTUPLE_H

CGAL_BEGIN_NAMESPACE

template < class T >
class Fourtuple
{
public:
  T  e0;
  T  e1;
  T  e2;
  T  e3;

  Fourtuple()
  {}

  Fourtuple(const T & a0, const T & a1, const T & a2, const T & a3)
    : e0(a0), e1(a1), e2(a2), e3(a3)
  {}
};

CGAL_END_NAMESPACE

#endif // CGAL__FOURTUPLE_H
