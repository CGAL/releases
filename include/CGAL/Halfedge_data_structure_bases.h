// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Halfedge_data_structure_bases.h
// package       : Halfedge_DS (2.4)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/04/07 19:29:14 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Base Classes for Vertices, Edges, Facets.
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifdef CGAL_REP_CLASS_DEFINED
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif
#endif  // CGAL_REP_CLASS_DEFINED

CGAL_BEGIN_NAMESPACE

class Vertex_min_base {
    // defines the minimal vertex functionality with no data at all.
public:
    typedef Tag_false Supports_vertex_point;
    typedef Tag_false Supports_vertex_halfedge;
    typedef void*     Point;
};

class Halfedge_min_base {
    // defines the minimal halfedge functionality with next and opposite
    // pointers.
protected:
    void* opp;
    void* nxt;
public:
    typedef Tag_false Supports_halfedge_prev;
    typedef Tag_false Supports_halfedge_vertex;
    typedef Tag_false Supports_halfedge_facet;

    void*       opposite()       { return opp;}
    const void* opposite() const { return opp;}
    void*       next()           { return nxt;}
    const void* next() const     { return nxt;}
        // the next halfedge along the facet.

    bool is_border() const { return false;}
        // is always false since facets are not supported here.

    void  set_opposite( void* h)  { opp = h;}
    void  set_next( void* h)      { nxt = h;}
};

class Facet_min_base {
    // defines the minimal facet functionality with no data at all.
public:
    typedef Tag_false Supports_facet_plane;
    typedef Tag_false Supports_facet_normal;
    typedef Tag_false Supports_facet_halfedge;
    typedef void*     Plane;
    typedef void*     Normal;
};

template <class Pt>
class Vertex_max_base {
    // defines the maximal vertex functionality including halfedge pointer
    // and a template parameter for the point.
protected:
    void* hdg;
    Pt    pt;
public:
    typedef Tag_true  Supports_vertex_point;
    typedef Tag_true  Supports_vertex_halfedge;
    typedef Pt        Point;

    Vertex_max_base() {}
    Vertex_max_base( const Pt& p) : pt(p) {}

    void*       halfedge()               { return hdg;}
    const void* halfedge() const         { return hdg;}
    void        set_halfedge( void* h)   { hdg = h;}
        // an incident halfedge pointing to `v'.

    Point&       point()       { return pt;}
    const Point& point() const { return pt;}
};

class Halfedge_max_base : public  Halfedge_min_base{
    // defines the maximal halfedge functionality including previous,
    // vertex and facet pointers.
protected:
    void* prv;
    void* v;
    void* f;
public:
    typedef Halfedge_min_base Base;
    typedef Tag_true  Supports_halfedge_prev;
    typedef Tag_true  Supports_halfedge_vertex;
    typedef Tag_true  Supports_halfedge_facet;

    Halfedge_max_base() : f(NULL) {}

    void*       prev()       { return prv;}
    const void* prev() const { return prv;}
        // the previous halfedge along the facet.

    void*       vertex()       { return v;}
    const void* vertex() const { return v;}
        // the incident vertex.

    void*       facet()       { return f;}
    const void* facet() const { return f;}
        // the facet to the left.

    bool is_border() const { return f == NULL;}
        // is true if `h' is a border halfedge).

    void  set_prev( void* h)        { prv = h;}
    void  set_vertex( void* _v)     { v = _v;}
    void  set_facet( void* _f)      { f = _f;}

    // Avoids unnecessary matchings with base class. (g++ 2.7.2 bug)
    void*       opposite()       { return Base::opposite();}
    const void* opposite() const { return Base::opposite();}
    void*       next()           { return Base::next();}
    const void* next() const     { return Base::next();}
};

class Facet_max_base {
    // defines the maximal facet functionality including halfedge pointer
    // but no geometry.
protected:
    void* hdg;
public:
    typedef Tag_false Supports_facet_plane;
    typedef Tag_false Supports_facet_normal;
    typedef Tag_true  Supports_facet_halfedge;
    typedef void*     Plane;
    typedef void*     Normal;

    void*       halfedge()       { return hdg;}
    const void* halfedge() const { return hdg;}
        // an incident halfedge pointing to `f'.

    void set_halfedge( void* h)  { hdg = h;}
};

#ifdef CGAL_REP_CLASS_DEFINED
template < class _R >
class Polyhedron_facet_base_3 : public Facet_max_base {
    // defines the maximal facet functionality including halfedge pointer,
    // plane equation and normal vector.
public:
    typedef Tag_true     Supports_facet_plane;
    typedef Tag_true     Supports_facet_normal;
    typedef _R           R;
    typedef Vector_3<R>  Normal;
    typedef Plane_3<R>   Plane;
protected:
    Plane   pln;
public:
    Normal        normal() const { return pln.orthogonal_vector();}
    Plane&        plane()        { return pln;}
    const Plane&  plane() const  { return pln;}
};
#endif  // CGAL_REP_CLASS_DEFINED

CGAL_END_NAMESPACE
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H //
// EOF //
