// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Halfedge_data_structure_bases.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

class CGAL_Vertex_min_base {
    // defines the minimal vertex functionality with no data at all.
public:
    typedef CGAL_Tag_false Supports_vertex_point;
    typedef CGAL_Tag_false Supports_vertex_halfedge;
    typedef void*        Point;
};

class CGAL_Halfedge_min_base {
    // defines the minimal halfedge functionality with next and opposite
    // pointers.
protected:
    void* opp;
    void* nxt;
public:
    typedef CGAL_Tag_false Supports_halfedge_prev;
    typedef CGAL_Tag_false Supports_halfedge_vertex;
    typedef CGAL_Tag_false Supports_halfedge_facet;

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

class CGAL_Facet_min_base {
    // defines the minimal facet functionality with no data at all.
public:
    typedef CGAL_Tag_false Supports_facet_plane;
    typedef CGAL_Tag_false Supports_facet_normal;
    typedef CGAL_Tag_false Supports_facet_halfedge;
    typedef void*        Plane;
    typedef void*        Normal;
};

template <class Pt>
class CGAL_Vertex_max_base {
    // defines the maximal vertex functionality including halfedge pointer
    // and a template parameter for the point.
protected:
    void* hdg;
    Pt    pt;
public:
    typedef CGAL_Tag_true  Supports_vertex_point;
    typedef CGAL_Tag_true  Supports_vertex_halfedge;
    typedef Pt           Point;

    CGAL_Vertex_max_base() {}
    CGAL_Vertex_max_base( const Pt& p) : pt(p) {}

    void*       halfedge()               {return hdg;}
    const void* halfedge() const         {return hdg;}
    void        set_halfedge( void* h)   { hdg = h;}
        // an incident halfedge pointing to `v'.

    Point&       point()       { return pt;}
    const Point& point() const { return pt;}
};

class CGAL_Halfedge_max_base : public  CGAL_Halfedge_min_base{
    // defines the maximal halfedge functionality including previous,
    // vertex and facet pointers.
protected:
    void* prv;
    void* v;
    void* f;
public:
    typedef CGAL_Halfedge_min_base Base;
    typedef CGAL_Tag_true  Supports_halfedge_prev;
    typedef CGAL_Tag_true  Supports_halfedge_vertex;
    typedef CGAL_Tag_true  Supports_halfedge_facet;

    CGAL_Halfedge_max_base() : f(NULL) {}

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

class CGAL_Facet_max_base {
    // defines the maximal facet functionality including halfedge pointer
    // but no geometry.
protected:
    void* hdg;
public:
    typedef CGAL_Tag_false Supports_facet_plane;
    typedef CGAL_Tag_false Supports_facet_normal;
    typedef CGAL_Tag_true  Supports_facet_halfedge;
    typedef void*        Plane;
    typedef void*        Normal;

    void*       halfedge()       { return hdg;}
    const void* halfedge() const { return hdg;}
        // an incident halfedge pointing to `f'.

    void set_halfedge( void* h)  { hdg = h;}
};

#ifdef CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H
#ifdef CGAL_REP_CLASS_DEFINED

#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif
#ifndef CGAL_PLANE_3_H
#include <CGAL/Plane_3.h>
#endif

template < class _R >
class CGAL_Polyhedron_facet_base_3 : public CGAL_Facet_max_base {
    // defines the maximal facet functionality including halfedge pointer,
    // plane equation and normal vector.
public:
    typedef CGAL_Tag_true     Supports_facet_plane;
    typedef CGAL_Tag_true     Supports_facet_normal;
    typedef _R                R;
    typedef CGAL_Vector_3<R>  Normal;
    typedef CGAL_Plane_3<R>   Plane;
protected:
    Plane   pln;
public:
    Normal        normal() const { return pln.orthogonal_vector();}
    Plane&        plane()        { return pln;}
    const Plane&  plane() const  { return pln;}
};
#endif  // CGAL_REP_CLASS_DEFINED
#else  // CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H //
// The following is part of a local project where the halfedge date
// structure has evolved from. It is not part of CGAL and not used.

template < class Pln>
class CGAL_Polyhedron_facet_base_3 : public CGAL_Facet_max_base {
    // defines the maximal facet functionality including halfedge pointer,
    // plane equation and normal vector.
public:
    typedef CGAL_Tag_true           Supports_facet_plane;
    typedef CGAL_Tag_true           Supports_facet_normal;
    typedef Pln                   Plane;
    typedef typename Pln::Normal  Normal;
protected:
    Plane   pln;
public:
    Normal&       normal()       { return pln.normal();}
    const Normal& normal() const { return pln.normal();}
    Plane&        plane()        { return pln;}
    const Plane&  plane() const  { return pln;}
};
#endif  // CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H //    
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_BASES_H //
// EOF //
