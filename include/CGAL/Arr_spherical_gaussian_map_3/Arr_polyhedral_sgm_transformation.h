// Copyright (c) 2009 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Arrangement_on_surface_2/include/CGAL/Arr_spherical_gaussian_map_3/Arr_polyhedral_sgm_transformation.h $
// $Id: Arr_polyhedral_sgm_transformation.h 56667 2010-06-09 07:37:13Z sloriot $
// 
// Author(s)     : Naama mayer         <naamamay@post.tau.ac.il>


#ifndef CGAL_ARR_POLYHEDRAL_SGM_TRANSFORMATION_H
#define CGAL_ARR_POLYHEDRAL_SGM_TRANSFORMATION_H

namespace CGAL {

/* This function rotates the face when the arrangement is Arr_polyhedral_sgm */

template <class Arrangement, class Transformation_3>
class Arr_polyhedral_sgm_transformation
{
public:

  typedef typename Arrangement::Face_handle   Face_handle;

  void rotate_face(Face_handle f, const Transformation_3 & aff)
  {			
    //Transform all the vertices of the original polyhedron.
    f->set_point(aff.transform(f->point()));
  }
};

} //namespace CGAL

#endif
