// Copyright (c) 2015 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta1/Shape_detection/include/CGAL/Shape_detection_3.h $
// $Id: Shape_detection_3.h 57cbe09 %aI Dmitry Anisimov
// SPDX-License-Identifier: GPL-3.0+
//
//
// Author(s)     : Sven Oesau, Yannick Verdie, Clément Jamin, Pierre Alliez, Florent Lafarge, Simon Giraudot, Thien Hoang, Dmitry Anisimov
//

#ifndef CGAL_SHAPE_DETECTION_3_DEPRECATED_H
#define CGAL_SHAPE_DETECTION_3_DEPRECATED_H

#include <CGAL/license/Shape_detection.h>

#include <CGAL/Shape_detection/Efficient_RANSAC.h>

// Deprecated -->
#include <CGAL/Shape_detection/deprecated/Region_growing.h>
#include <CGAL/Shape_detection/deprecated/Shape_detection_traits.h>

#define CGAL_DEPRECATED_MESSAGE_DETAILS \
  "CGAL::Shape_detection_3 namespace has been replaced by the namespace "\
  "CGAL::Shape_detection."
  
#include <CGAL/internal/deprecation_warning.h>

namespace CGAL {
  namespace Shape_detection_3 = Shape_detection;
}
// --<

#endif // CGAL_SHAPE_DETECTION_3_DEPRECATED_H
