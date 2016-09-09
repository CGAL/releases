// Copyright (c) 2008 GeometryFactory, Sophia-Antipolis (France)
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/CGALimageIO/include/CGAL/Image_3_vtk_interface.h $
// $Id: Image_3_vtk_interface.h 46320 2008-10-17 08:39:19Z lrineau $
// 
// Author(s)     : Laurent Rineau

#ifndef CGAL_IMAGE_3_VTK_INTERFACE_H
#define CGAL_IMAGE_3_VTK_INTERFACE_H

#ifdef CGAL_USE_VTK
#include <CGAL/Image_3.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCharArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkShortArray.h>
#include <vtkUnsignedShortArray.h>
#include <vtkIntArray.h>
#include <vtkUnsignedIntArray.h>

#include <boost/cstdint.hpp> // for uint32_t, etc.

namespace CGAL {

template <typename Word>
struct VTK_type_generator {
};

template <>
struct VTK_type_generator<double> {
  static const vtkIdType type = VTK_DOUBLE;
  typedef vtkDoubleArray ArrayType;
};

template <>
struct VTK_type_generator<float> {
  static const vtkIdType type = VTK_FLOAT;
  typedef vtkFloatArray ArrayType;
};

template <>
struct VTK_type_generator<char> {
  static const vtkIdType type = VTK_CHAR;
  typedef vtkCharArray ArrayType;
};

template <>
struct VTK_type_generator<boost::uint8_t> {
  static const vtkIdType type = VTK_UNSIGNED_CHAR;
  typedef vtkUnsignedCharArray ArrayType;
};

template <>
struct VTK_type_generator<boost::int16_t> {
  static const vtkIdType type = VTK_SHORT;
  typedef vtkShortArray ArrayType;
};

template <>
struct VTK_type_generator<boost::uint16_t> {
  static const vtkIdType type = VTK_UNSIGNED_SHORT;
  typedef vtkUnsignedShortArray ArrayType;
};

template <>
struct VTK_type_generator<boost::int32_t> {
  static const vtkIdType type = VTK_INT;
  typedef vtkIntArray ArrayType;
};

template <>
struct VTK_type_generator<boost::uint32_t> {
  static const vtkIdType type = VTK_UNSIGNED_INT;
  typedef vtkUnsignedIntArray ArrayType;
};

::vtkImageData* vtk_image_sharing_same_data_pointer(Image_3& image)
{
  vtkImageData* vtk_image = vtkImageData::New();
  vtkDataArray* data_array = 0;
  vtkIdType type = 0;

  _image* image_ptr = image.image();

  CGAL_IMAGE_IO_CASE
    (image_ptr,
     type = VTK_type_generator<Word>::type;
     typedef VTK_type_generator<Word>::ArrayType VTKArray;
     VTKArray* array = VTKArray::New();
     array->SetArray(static_cast<Word*>(image.data()), image.size(), 1);
     data_array = array;
     );

  vtk_image->SetDimensions(image.xdim(),
                           image.ydim(),
                           image.zdim());
  vtk_image->SetWholeExtent(0, image.xdim(),
                            0, image.ydim(),
                            0, image.zdim());
  vtk_image->SetSpacing(image.vx(),
                        image.vy(),
                        image.vz());
  vtk_image->SetScalarType(type);
  vtk_image->GetPointData()->SetScalars(data_array);
  return vtk_image;
} // end vtk_image_sharing_same_data_pointer

} //end namespace CGAL

#endif // CGAL_USE_VTK


#endif // CGAL_IMAGE_3_VTK_INTERFACE_H
