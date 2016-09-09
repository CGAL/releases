// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Alpha_shapes_3/include/CGAL/Weighted_alpha_shape_euclidean_traits_3.h $
// $Id: Weighted_alpha_shape_euclidean_traits_3.h 52648 2009-10-20 17:56:12Z sloriot $
// 
//
// Author(s)     : Tran Kai Frank DA <Frank.Da@sophia.inria.fr>

#ifndef CGAL_WEIGHTED_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H
#define CGAL_WEIGHTED_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H 

#include <CGAL/Regular_triangulation_euclidean_traits_3.h>

CGAL_BEGIN_NAMESPACE


   
//------------------ Traits class -------------------------------------

#ifndef CGAL_NO_DEPRECATED_CODE

template <class K>
class Weighted_alpha_shape_euclidean_traits_3 : public 
Regular_triangulation_euclidean_traits_3<K>
{};

CGAL_END_NAMESPACE
#endif //CGAL_NO_DEPRECATED_CODE
  
  
#endif //CGAL_WEIGHTED_ALPHA_SHAPE_EUCLIDEAN_TRAITS_3_H 
