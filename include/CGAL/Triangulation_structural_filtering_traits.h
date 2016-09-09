// Copyright (c) 2010  GeometryFactory Sarl (France).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Triangulation_2/include/CGAL/Triangulation_structural_filtering_traits.h $
// $Id: Triangulation_structural_filtering_traits.h 60298 2010-12-10 17:02:10Z lrineau $
//
// Author(s)     : Laurent Rineau <Laurent.Rineau__CGAL@normalesup.org>
// 

#ifndef TRIANGULATION_STRUCTURAL_FILTERING_TRAITS_H
#define TRIANGULATION_STRUCTURAL_FILTERING_TRAITS_H

#include <CGAL/tags.h>

namespace CGAL {

template <typename Geom_traits>
struct Triangulation_structural_filtering_traits {
  typedef Tag_false Use_structural_filtering_tag;
};

#ifdef CGAL_EXACT_PREDICATES_EXACT_CONSTRUCTIONS_KERNEL_H
template <>
struct Triangulation_structural_filtering_traits<Epeck> {
  typedef Tag_true Use_structural_filtering_tag;
};
#endif // CGAL_EXACT_PREDICATES_EXACT_CONSTRUCTIONS_KERNEL_H

#ifdef CGAL_EXACT_PREDICATES_INEXACT_CONSTRUCTIONS_KERNEL_H
template <>
struct Triangulation_structural_filtering_traits<Epick> {
  typedef Tag_true Use_structural_filtering_tag;
};
#endif // CGAL_EXACT_PREDICATES_INEXACT_CONSTRUCTIONS_KERNEL_H

} // end namespace CGAL

#endif // no TRIANGULATION_STRUCTURAL_FILTERING_TRAITS_H
