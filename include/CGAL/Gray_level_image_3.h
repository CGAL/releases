// Copyright (c) 2005-2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Surface_mesher/include/CGAL/Gray_level_image_3.h $
// $Id: Gray_level_image_3.h 37876 2007-04-03 13:59:17Z lrineau $
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H
#define CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H

#include <CGAL/basic.h>

#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
#include <boost/format.hpp>
#endif

/* Copy-paste from <imageio/ImageIO.h> */
struct point_image;
typedef struct point_image _image;

extern void printSupportedFileFormat();
extern _image* _readImage(const char *name);
extern void _freeImage(_image *im);
extern void _get_image_bounding_box(_image*,
			     float*, float*, float*,
			     float*, float*, float*); 
extern void convertImageTypeToFloat(_image* image);
extern float triLinInterp(_image* image,float posx, float posy, float posz);
/* End of copy-paste from <imageio/ImageIO.h> */

namespace CGAL {

  template <typename FT, typename Point>
class Gray_level_image_3
{
  _image *image;
  float isovalue;
  float min_x, min_y, min_z;
  float max_x, max_y, max_z;
  bool is_valid;

public:
  Gray_level_image_3(const char* file, float isoval)
    : image(0),
      isovalue(isoval),
      min_x(0.f),
      min_y(0.f),
      min_z(0.f),
      max_x(0.f),
      max_y(0.f),
      max_z(0.f),
      is_valid(false)
  {
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
    std::cerr << 
      ::boost::format("Constructing a Gray_level_image_3(\"%1%\")... ") % file;
#endif
    image = ::_readImage(file);
    if( image != 0 )
    {
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
      std::cerr << ::boost::format(" = %1%\n") % image;
#endif
      is_valid = true;
      ::convertImageTypeToFloat(image);
      isovalue=isoval;
      ::_get_image_bounding_box(image,
				&min_x, &min_y, &min_z,
				&max_x, &max_y, &max_z);
    }
  }

  // BUG
  /** @FIXME This destructor should call ::freeImage(), but objects of type
      Gray_level_image_3 are copied a lot of time during the execution of
      the Surface_mesher algorithm. image should perhaps be a smart
      pointer. We need to bench if the handling of smart pointer has a
      cost.
   */
  ~Gray_level_image_3()
  {
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
      std::cerr << ::boost::format("~Gray_level_image_3() image=%1%\n") % image;
#endif
  }

  static void print_supported_file_format()
  {
    ::printSupportedFileFormat();
  }

  bool inside(const float X, const float Y, const float Z) const
  {
    return ( X>=min_x && Y>=min_y && Z>=min_z && 
             X<=max_x && Y<=max_y && Z<=max_z );
  }

  FT operator()(Point p) const
  {
    const float X=static_cast<float>(to_double(p.x()));
    const float Y=static_cast<float>(to_double(p.y()));
    const float Z=static_cast<float>(to_double(p.z()));

    if (!inside(X,Y,Z))
      return FT(1);
    else{
      float value = ::triLinInterp(image, X, Y, Z); 

      if (value > isovalue) // inside
	return FT(-1);
      else if (value < isovalue) // outside
	return FT(1);
      else
	return FT(0);
    }
  }
}; // end Gray_level_image_3
 
} // end namespace CGAL

#endif // CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H
