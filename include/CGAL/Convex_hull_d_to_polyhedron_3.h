// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Convex_hull_d_to_polyhedron_3.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2002/05/07 08:22:56 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONVEX_HULL_D_TO_POLYHEDRON_3_H
#define CGAL_CONVEX_HULL_D_TO_POLYHEDRON_3_H

#include <CGAL/Convex_hull_d.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>

CGAL_BEGIN_NAMESPACE

template <class _HDS, class _ChullType>
class Build_polyhedron_from_chull : public Modifier_base< _HDS>
{
  public:
    typedef _HDS                           HDS;
    typedef _ChullType                     ChullType;
    typedef typename HDS::Vertex           HdsVertex;
    typedef typename HdsVertex::Point      Point;
    typedef typename ChullType::Facet_const_handle  Facet_handle;
    typedef typename ChullType::Vertex_const_handle Vertex_handle;
    typedef typename ChullType::R R;
    typedef typename ChullType::Point_d Point_d;

Build_polyhedron_from_chull(const ChullType& CH) : ch(CH) {}

Point convert(const Point_d& p) const
{ return Point(p.hx(),p.hy(),p.hz(),p.hw()); }

void operator()(HDS& hds )
{
  CGAL_assertion( ch.current_dimension() == 3); 
  Polyhedron_incremental_builder_3<HDS> B(hds, true);
  B.begin_surface( ch.number_of_vertices(), 
                   ch.number_of_facets() ); 
  // would be nice to have statistical data on
  // Chull available other than print_statistics()
  Unique_hash_map<Vertex_handle, int> index( -1);
  std::list<Facet_handle> L = ch.all_facets();
  typename std::list<Facet_handle>::iterator fit;
  Facet_handle f;
  Vertex_handle v;
  int i = 0;
  for ( fit = L.begin(); fit != L.end(); ++fit) { f = *fit;
    for (int k=0; k < 3; ++k) {
       v = ch.vertex_of_facet(f,k);
       if ( index[v] == -1 ) {
         B.add_vertex( convert(ch.associated_point(v)) );
         index[v] = i++;
       }
    }
  }
  Point_d center = ch.center();
  for ( fit = L.begin(); fit != L.end(); ++fit) { f = *fit;
     B.begin_facet();
     Vertex_handle v0 = ch.vertex_of_facet(f,0);
     Vertex_handle v1 = ch.vertex_of_facet(f,1);
     Vertex_handle v2 = ch.vertex_of_facet(f,2);
     typename R::Orientation_d orientation =
       ch.kernel().orientation_d_object();
     std::vector<Point_d> V(4);
     V[0]= ch.associated_point(v0);
     V[1]= ch.associated_point(v1);
     V[2]= ch.associated_point(v2);
     V[3]= center;
     if ( orientation( V.begin(), V.end() ) == POSITIVE ) {
       B.add_vertex_to_facet( index[v0] );
       B.add_vertex_to_facet( index[v1] );
       B.add_vertex_to_facet( index[v2] );
     } else {
       B.add_vertex_to_facet( index[v0] );
       B.add_vertex_to_facet( index[v2] );
       B.add_vertex_to_facet( index[v1] );
     }
     B.end_facet();
  }
  B.end_surface();
}

private:
  const ChullType& ch;
};

/*{\Mtext \headerline{Low Dimensional Conversion Routine}
include |<CGAL/Convex_hull_d_to_polyhedron_3.h>|
\setopdims{2cm}{3cm}}*/

#if defined(_MSC_VER) && defined(CGAL_USE_POLYHEDRON_DESIGN_ONE)
template <class R, class Tr, class HDS>       
void 
convex_hull_d_to_polyhedron_3(const Convex_hull_d<R>& C,
                              Polyhedron_3<Tr,HDS>& P)
#else // non-MSVC compilers or MSVC>1200 can handle this more general interface
template <class R, class Polyhedron_3>
void convex_hull_d_to_polyhedron_3(
  const Convex_hull_d<R>& C, Polyhedron_3& P)
#endif
/*{\Mfunc converts the convex hull |C| to polyedral surface stored in 
   |P|.\\ \precond |dim == 3| and |dcur == 3|. }*/
{ typedef Convex_hull_d<R> ChullType;

#if defined(_MSC_VER) && defined(CGAL_USE_POLYHEDRON_DESIGN_ONE)  
   typedef typename Polyhedron_3<Tr, HDS>::HalfedgeDS  HDS;
#else
  typedef typename Polyhedron_3::HalfedgeDS  HDS;
#endif
  CGAL_assertion_msg(C.dimension()==3&&C.current_dimension()==3,
  "convex_hull_d_to_polyhedron_3: only full manifold can be transformed.");
  Build_polyhedron_from_chull<HDS,ChullType> get_surface(C);
  P.delegate( get_surface );
}

CGAL_END_NAMESPACE
#endif //CGAL_CONVEX_HULL_D_TO_POLYHEDRON_3_H


