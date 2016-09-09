// Copyright (c) 2003-2005  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Surface_mesher/include/CGAL/Robust_circumcenter_traits_3.h $
// $Id: Robust_circumcenter_traits_3.h 32134 2006-06-28 17:04:31Z lrineau $
//
//
// Author(s)     :  Mariette Yvinec <Mariette.Yvinec@sophia.inria.fr>

// This traits override Construct_circumcenter_3
// to get a robust ones when called on slivers

#ifndef CGAL_ROBUST_CIRCUMCENTER_TRAITS_3_H
#define CGAL_ROBUST_CIRCUMCENTER_TRAITS_3_H

#include <CGAL/number_utils_classes.h>
#include <CGAL/Cartesian_converter.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

CGAL_BEGIN_NAMESPACE


template < class K >
class Robust_construct_circumcenter_3
{
  typedef Exact_predicates_exact_constructions_kernel EK;
  typedef typename K::Point_3             Point_3;
  typedef typename K::Triangle_3          Triangle_3;
  typedef typename K::Tetrahedron_3       Tetrahedron_3;
  typedef typename K::Construct_vertex_3  Construct_vertex_3;

  public:
    typedef Point_3          result_type;
    typedef Arity_tag< 4 >   Arity;

  Point_3 operator() (const Point_3 & p,
		      const Point_3 & q,
		      const Point_3 & r,
		      const Point_3 & s) const
    {
      Cartesian_converter<K,EK> to_exact;
      Cartesian_converter<EK,K, To_double<EK::FT> > back_from_exact;
      //Cartesian_converter<EK,K > back_from_exact;
      EK::Construct_circumcenter_3
	exact_circumcenter = EK().construct_circumcenter_3_object();

      return back_from_exact(exact_circumcenter( to_exact(p),
						 to_exact(q),
						 to_exact(r),
						 to_exact(s)));

    }

  Point_3 operator() (const Point_3 & p,
		      const Point_3 & q,
		      const Point_3 & r) const
    {
      Cartesian_converter<K,EK> to_exact;
      Cartesian_converter<EK,K, To_double<EK::FT> > back_from_exact;
      EK::Construct_circumcenter_3
	exact_circumcenter = EK().construct_circumcenter_3_object();

      return back_from_exact(exact_circumcenter( to_exact(p),
						 to_exact(q),
						 to_exact(r)));
    }

    Point_3
    operator()(const Triangle_3& t) const
    { 
      Construct_vertex_3 vertex = this->construct_vertex_3_object();
      return this->operator()(vertex(t, 0), vertex(t, 1), vertex(t, 2));
    }

    Point_3
    operator()(const Tetrahedron_3& t) const
    { 
      Construct_vertex_3 vertex = this->construct_vertex_3_object();
      return this->operator()(vertex(t, 0), vertex(t, 1),
                              vertex(t, 2), vertex(t, 3));
    }
};




template < class K>
class Robust_circumcenter_traits_3
  : public K
{
 public:
  typedef CGAL::Robust_construct_circumcenter_3<K> Construct_circumcenter_3;

  Construct_circumcenter_3
  construct_circumcenter_3_object() const
  { return Construct_circumcenter_3(); }

};



CGAL_END_NAMESPACE

#endif //CGAL_ROBUST_CIRCUMCENTER_TRAITS_3_H
