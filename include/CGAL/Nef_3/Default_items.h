//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Nef_3/include/CGAL/Nef_3/Default_items.h $
// $Id: Default_items.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Andreas Fabri <andreas.fabri@geometryfactory.com>

#ifndef CGAL_NEF_DEFAULT_ITEMS_H
#define CGAL_NEF_DEFAULT_ITEMS_H

#include <CGAL/Nef_3/SNC_items.h>
#include <CGAL/Nef_3/SNC_indexed_items.h>
#include <CGAL/Extended_homogeneous.h>
#include <CGAL/Extended_cartesian.h>

namespace CGAL {

template<class Kernel>
struct Default_items {
  typedef CGAL::SNC_indexed_items Items;
};

template<typename NT>
struct Default_items<CGAL::Extended_homogeneous<NT> > {
  typedef CGAL::SNC_items Items;
};

template<typename NT>
struct Default_items<CGAL::Extended_cartesian<NT> > {
  typedef CGAL::SNC_items Items;
};

} //namespace CGAL
#endif
