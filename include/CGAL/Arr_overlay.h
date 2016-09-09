// Copyright (c) 2007 Max-Planck-Institute for Computer Science (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Arrangement_on_surface_2/include/CGAL/Arr_overlay.h $
// $Id: Arr_overlay.h 40377 2007-09-19 11:05:08Z ophirset $
// 
//
// Author(s)     : Eric Berberich <eric@mpi-inf.mpg.de>

#ifndef CGAL_ARR_OVERLAY_H
#define CGAL_ARR_OVERLAY_H

/*! \file
 * Helping file to include Arr_overlay_2 for backward compatibility.
 */

#if (defined __GNUC__)
  #warning Arr_overlay.h is DEPRECATED, please include Arr_overlay_2.h instead
#elif (defined _MSC_VER)
  #pragma message("Arr_overlay.h is DEPRECATED, please include Arr_overlay_2.h instead")
#endif

#include <CGAL/Arr_overlay_2.h>

#endif
