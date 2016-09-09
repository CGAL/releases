// Copyright (c) 2011 GeometryFactory (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Polyline_with_context.h $
// $Id: Polyline_with_context.h 61484 2011-03-02 14:59:51Z sloriot $
//
//
// Author(s)     : Laurent Rineau
//

#ifndef CGAL_MESH_3_POLYLINE_WITH_CONTEXT_H
#define CGAL_MESH_3_POLYLINE_WITH_CONTEXT_H

#include <set>
#include <functional>

namespace CGAL { namespace Mesh_3 {

template <typename Surface_patch_id,
          typename Curve_id_>
struct Polyline_context {
  typedef std::set<Surface_patch_id> Patches_ids;
  typedef Curve_id_ Curve_id;

  Curve_id id;
  Patches_ids adjacent_patches_ids;
};


template <typename Surface_patch_id,
          typename Curve_id,
          typename Bare_polyline_>
struct Polyline_with_context
{
  typedef Bare_polyline_ Bare_polyline;
  typedef Polyline_context<Surface_patch_id,Curve_id> Context;

  Context context;
  Bare_polyline polyline_content;
};

/**
 * @class Extract_bare_polyline
 * A functor to get bare polyline from Polyline_with_context (Pwc_).
 */
template <typename Pwc_>
struct Extract_bare_polyline :
  public std::unary_function<Pwc_, const typename Pwc_::Bare_polyline&>
{
  typedef std::unary_function<Pwc_, const typename Pwc_::Bare_polyline&> Base;
  typedef typename Base::result_type                                     result_type;
  typedef typename Base::argument_type                                   argument_type;
  
  result_type operator()(const argument_type& p) const { return p.polyline_content; }
};
  
}} // end namespaces

#endif // CGAL_MESH_3_POLYLINE_WITH_CONTEXT_H
