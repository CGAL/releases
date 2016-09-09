// Copyright (c) 2007 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Arrangement_on_surface_2/include/CGAL/Arr_tags.h $
// $Id: Arr_tags.h 41249 2007-12-19 11:25:21Z eric $
// 
//
// Author(s): Efi Fogel         <efif@post.tau.ac.il>

#ifndef CGAL_ARR_TAGS_H
#define CGAL_ARR_TAGS_H

/*! \file
 * Definition of the tags for the arrangement package.
 */

CGAL_BEGIN_NAMESPACE

struct Arr_no_boundary_tag {};
struct Arr_has_boundary_tag {};
struct Arr_bounded_boundary_tag : public virtual Arr_has_boundary_tag {};
struct Arr_unbounded_boundary_tag : public virtual Arr_has_boundary_tag {};
struct Arr_all_boundary_tag : public virtual Arr_bounded_boundary_tag,
                              public virtual Arr_unbounded_boundary_tag {};

CGAL_END_NAMESPACE

#endif

