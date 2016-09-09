// Copyright (c) 2007-09  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Surface_reconstruction_points_3/include/CGAL/IO/output_surface_facets_to_triangle_soup.h $
// $Id: output_surface_facets_to_triangle_soup.h 49454 2009-05-18 15:42:15Z lsaboret $
//
// Author(s) : Pierre Alliez

#ifndef CGAL_OUTPUT_SURFACE_FACETS_TO_TRIANGLE_SOUP_H
#define CGAL_OUTPUT_SURFACE_FACETS_TO_TRIANGLE_SOUP_H

#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Complex_2_in_triangulation_3_polyhedron_builder.h>
#include <CGAL/value_type_traits.h>

CGAL_BEGIN_NAMESPACE


/// Gets reconstructed surface out of a SurfaceMeshComplex_2InTriangulation_3 object.
///
/// This variant exports the surface as a triangle soup.
///
/// @commentheading Template Parameters:
/// @param SurfaceMeshComplex_2InTriangulation_3 model of the SurfaceMeshComplex_2InTriangulation_3 concept.
/// @param OutputIterator value_type must be convertible from Triangle_3<Kernel>.
template <class SurfaceMeshComplex_2InTriangulation_3,
          typename OutputIterator>
void
output_surface_facets_to_triangle_soup(
  const SurfaceMeshComplex_2InTriangulation_3& c2t3, ///< Input surface.
  OutputIterator output_iterator) ///< Output iterator.
{
  typedef SurfaceMeshComplex_2InTriangulation_3 C2t3;
  typedef typename C2t3::Triangulation Tr;
  typedef typename Tr::Finite_facets_iterator Finite_facets_iterator;
  typedef typename Tr::Vertex_handle Vertex_handle;
  typedef typename Tr::Point Point;

  // value_type_traits is a workaround as back_insert_iterator's value_type is void
  typedef typename value_type_traits<OutputIterator>::type Triangle;

  const Tr& tr = c2t3.triangulation();

  for(Finite_facets_iterator fit = tr.finite_facets_begin();
    fit != tr.finite_facets_end();
    ++fit)
  {
    if((*fit).first->is_facet_on_surface((*fit).second) == true)
    {
      std::vector<Point> points(3);
      unsigned int index = 0;
      for(int i=0; i<4; i++)
        if(i != (*fit).second)
          points[index++] = (*fit).first->vertex(i)->point();

      *output_iterator = Triangle(points[0],points[1],points[2]);
      output_iterator++;
    }
  }
}


CGAL_END_NAMESPACE

#endif // CGAL_OUTPUT_SURFACE_FACETS_TO_TRIANGLE_SOUP_H
