// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Polyhedron_copy_3.h
// package       : Polyhedron (3.21)
// chapter       : $CGAL_Chapter: 3D-Polyhedral Surfaces $
// source        : polyhedron_builder.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/02 20:57:44 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Copy of Polyhedral Surfaces.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POLYHEDRON_COPY_3_H
#define CGAL_POLYHEDRON_COPY_3_H 1

#include <CGAL/basic.h>
// MS Visual C++ 6.0 does not work with the new design.
#if defined( _MSC_VER) && (_MSC_VER <= 1200)
#ifndef CGAL_USE_POLYHEDRON_DESIGN_TWO
#define CGAL_USE_POLYHEDRON_DESIGN_ONE 1
#endif
#endif
#ifndef CGAL_USE_POLYHEDRON_DESIGN_ONE
#define CGAL_USE_POLYHEDRON_DESIGN_TWO 1
#endif

#include <CGAL/Modifier_base.h>
#include <CGAL/Inverse_index.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

CGAL_BEGIN_NAMESPACE

template < class Poly, class HDS >
class Polyhedron_copy_3 : public Modifier_base<HDS> {
protected:
    const Poly& source;
public:
    typedef Poly Polyhedron;
    typedef HDS  Halfedge_data_structure;
    Polyhedron_copy_3( const Polyhedron& poly) : source(poly) {}
        // creates the copy modifier and stores the `source' in its
        // internal state.
    void operator()( HDS& target);
        // copies the `source' known from creation time into the `target'.
        // Postcondition: the `target' is a valid polyhedral surface.
};

template < class Poly, class HDS>
void
Polyhedron_copy_3<Poly,HDS>:: operator()( HDS& target) {
    typedef typename Poly::Vertex_const_iterator  Vertex_const_iterator;
    typedef typename Poly::Facet_const_iterator   Facet_const_iterator;
    typedef Inverse_index< Vertex_const_iterator> Index;
    typedef typename HDS::Point                   Point;

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
    target.delete_all();
#else
    target.clear();
#endif
    Polyhedron_incremental_builder_3<HDS> B( target);
    B.begin_surface( source.size_of_vertices(),
                     source.size_of_facets(),
                     source.size_of_halfedges());
    for ( Vertex_const_iterator vi = source.vertices_begin();
          vi != source.vertices_end();
          ++vi) {
        B.add_vertex( Point( vi->point()));
    }
    Index index( source.vertices_begin(), source.vertices_end());

    for ( Facet_const_iterator fi = source.facets_begin();
          fi != source.facets_end();
          ++fi) {
        B.begin_facet();
        typedef typename Poly::Halfedge_around_facet_const_circulator
            Halfedge_around_facet_const_circulator;
        Halfedge_around_facet_const_circulator hc = fi->facet_begin();
        Halfedge_around_facet_const_circulator hc_end = hc;
        CGAL_assertion( hc != NULL);
        do {
#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
            B.add_vertex_to_facet( index[ Vertex_const_iterator(
                hc->vertex().ptr())]);
#else
            B.add_vertex_to_facet( index[ hc->vertex()]);
#endif
            ++hc;
        } while( hc != hc_end);
        B.end_facet();
    }
    B.end_surface();
    target.normalize_border();
}

CGAL_END_NAMESPACE
#endif // CGAL_POLYHEDRON_COPY_3_H //
// EOF //
