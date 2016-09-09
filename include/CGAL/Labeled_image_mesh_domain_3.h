// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Labeled_image_mesh_domain_3.h $
// $Id: Labeled_image_mesh_domain_3.h 56231 2010-05-14 09:46:02Z afabri $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description :
//
//
//******************************************************************************

#ifndef CGAL_LABELED_IMAGE_MESH_DOMAIN_3_H
#define CGAL_LABELED_IMAGE_MESH_DOMAIN_3_H


#include <CGAL/Mesh_3/Labeled_mesh_domain_3.h>
#include <CGAL/Mesh_3/Image_to_labeled_function_wrapper.h>


namespace CGAL {

/**
 * @class Labeled_image_mesh_domain_3
 *
 *
 */
template<class Image,
         class BGT,
         class Wrapper = Mesh_3::Image_to_labeled_function_wrapper<Image, BGT> >
class Labeled_image_mesh_domain_3
: public Mesh_3::Labeled_mesh_domain_3<Wrapper, BGT>
{
public:
  typedef Mesh_3::Labeled_mesh_domain_3<Wrapper, BGT> Base;

  typedef typename Base::Sphere_3 Sphere_3;
  typedef typename Base::FT FT;
  typedef BGT Geom_traits;
  typedef CGAL::Bbox_3 Bbox_3;

  /// Constructor
  Labeled_image_mesh_domain_3(const Image& image,
                              const FT& error_bound = FT(1e-3))
    : Base(Wrapper(image),
           compute_bounding_box(image),
           error_bound)
  {}

  /// Destructor
  virtual ~Labeled_image_mesh_domain_3() {}


private:
  /// Returns a box enclosing image \c im
  Bbox_3 compute_bounding_box(const Image& im) const
  {
    return Bbox_3(-1,-1,-1,
                  im.xdim()*im.vx()+1, im.ydim()*im.vy()+1, im.zdim()*im.vz()+1);
  }

private:
  // Disabled copy constructor & assignment operator
  typedef Labeled_image_mesh_domain_3<Image, BGT> Self;
  Labeled_image_mesh_domain_3(const Self& src);
  Self& operator=(const Self& src);

};  // end class Labeled_image_mesh_domain_3



}  // end namespace CGAL



#endif // CGAL_LABELED_IMAGE_MESH_DOMAIN_3_H
