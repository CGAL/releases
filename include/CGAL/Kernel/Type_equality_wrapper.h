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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kernel_23/include/CGAL/Kernel/Type_equality_wrapper.h $
// $Id: Type_equality_wrapper.h 46388 2008-10-21 12:29:38Z afabri $
// 
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_KERNEL_TYPE_EQUALITY_WRAPPER_H
#define CGAL_KERNEL_TYPE_EQUALITY_WRAPPER_H

#include <CGAL/user_classes.h>

CGAL_BEGIN_NAMESPACE

// This is a kernel wrapper which provides the type equality between
// Kernel::Point_2 and CGAL::Point_2<Kernel>, by deriving from
// K_base::Point_2 (and similar for the other types).

template < typename K_base, typename Kernel_ >
struct Type_equality_wrapper
  : public K_base
{
    typedef K_base                                  Kernel_base;

#define CGAL_Kernel_obj(X)   typedef CGAL::X<Kernel_> X;

#include <CGAL/Kernel/interface_macros.h>

    // Undocumented stuff.
    typedef CGAL::Conic_2<Kernel_>                   Conic_2;
    typedef CGAL::Aff_transformation_2<Kernel_>      Aff_transformation_2;
    typedef CGAL::Aff_transformation_3<Kernel_>      Aff_transformation_3;
};

CGAL_END_NAMESPACE

#endif // CGAL_KERNEL_TYPE_EQUALITY_WRAPPER_H
