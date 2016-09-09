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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kernel_23/include/CGAL/Kernel/Same_uncertainty.h $
// $Id: Same_uncertainty.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_SAME_UNCERTAINTY_H
#define CGAL_SAME_UNCERTAINTY_H

#include <CGAL/config.h>

namespace CGAL {

template < typename T1, typename T2 >
struct Same_uncertainty
{
  typedef T1 type;
};

template < typename T > class Uncertain;
template < typename T > struct Sgn;

template < typename T1, typename T2 >
struct Same_uncertainty < T1, Uncertain<T2> >
{
  typedef Uncertain<T1> type;
};

// Short cut to extract uncertainty from a number type directly.
template < typename T1, typename NT >
struct Same_uncertainty_nt
  : Same_uncertainty <T1, typename Sgn<NT>::result_type > {};

} //namespace CGAL

#endif // CGAL_SAME_UNCERTAINTY_H
