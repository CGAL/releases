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
// file          : include/CGAL/HalfedgeDS_halfedge_base.h
// package       : HalfedgeDS (3.21)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds_bases.fw
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/18 04:46:19 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Base Classes for Halfedges.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGEDS_HALFEDGE_BASE_H
#define CGAL_HALFEDGEDS_HALFEDGE_BASE_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

template < class Refs, class TP, class TV, class TF>
struct HalfedgeDS_halfedge_base_base {
    // Base_base will be used to access set_opposite(), which is
    // made private in the normal halfedge bases. Since halfedges
    // come always in pairs, managed by the HDS, the set_opposite()
    // member function is protected from the user.
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_halfedge_base_base<Refs,TP,TV,TF> Base_base;
    typedef TP                                   Supports_halfedge_prev;
    typedef TV                                   Supports_halfedge_vertex;
    typedef TF                                   Supports_halfedge_face;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Face                  Face;
private:
    Halfedge_handle  opp;
    Halfedge_handle  nxt;
public:
    Halfedge_handle       opposite()                        { return opp;}
    Halfedge_const_handle opposite() const                  { return opp;}
    void                  set_opposite( Halfedge_handle h)  { opp = h;}
    Halfedge_handle       next()                            { return nxt;}
    Halfedge_const_handle next() const                      { return nxt;}
    void                  set_next( Halfedge_handle h)      { nxt = h;}

    bool is_border() const { return false;}
        // is always false as long as faces are not supported.
};

template < class Refs, class TP = Tag_true,
                       class TV = Tag_true,
                       class TF = Tag_true>
class HalfedgeDS_halfedge_base;

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_false,  // prev
                                Tag_false,  // vertex
                                Tag_false>  // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_false, Tag_false, Tag_false>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_false,Tag_false,Tag_false>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_false,Tag_false,Tag_false>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_true,   // prev
                                Tag_false,  // vertex
                                Tag_false>  // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_true, Tag_false, Tag_false>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_true,Tag_false,Tag_false>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_true,Tag_false,Tag_false>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Halfedge_handle  prv;
public:
    // the previous halfedge along the face.
    Halfedge_handle       prev()                       { return prv; }
    Halfedge_const_handle prev() const                 { return prv; }
    void                  set_prev( Halfedge_handle h) { prv = h; }
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_false,  // prev
                                Tag_true,   // vertex
                                Tag_false>  // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_false, Tag_true, Tag_false>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_false,Tag_true,Tag_false>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_false,Tag_true,Tag_false>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Vertex_handle    v;
public:
    // the incident vertex.
    Vertex_handle         vertex()                     { return v; }
    Vertex_const_handle   vertex() const               { return v; }
    void                  set_vertex( Vertex_handle w) { v = w; }
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_false,  // prev
                                Tag_false,  // vertex
                                Tag_true>   // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_false, Tag_false, Tag_true>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_false,Tag_false,Tag_true>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_false,Tag_false,Tag_true>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Face_handle      f;
public:
    // Explicit initialization of f to denote border halfedges
    // is needed if Face_handle is a C style pointer.
    HalfedgeDS_halfedge_base() : f( Face_handle()) {}

    // the face to the left.
    Face_handle           face()                       { return f; }
    Face_const_handle     face() const                 { return f; }
    void                  set_face( Face_handle g)     { f = g; }

    bool is_border() const { return f == Face_handle();}
        // is true if `h' is a border halfedge.
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_true,   // prev
                                Tag_true,   // vertex
                                Tag_false>  // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_true, Tag_true, Tag_false>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_true,Tag_true,Tag_false>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_true,Tag_true,Tag_false>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Halfedge_handle  prv;
    Vertex_handle    v;
public:
    // the previous halfedge along the face.
    Halfedge_handle       prev()                       { return prv; }
    Halfedge_const_handle prev() const                 { return prv; }
    void                  set_prev( Halfedge_handle h) { prv = h; }

    // the incident vertex.
    Vertex_handle         vertex()                     { return v; }
    Vertex_const_handle   vertex() const               { return v; }
    void                  set_vertex( Vertex_handle w) { v = w; }
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_true,   // prev
                                Tag_false,  // vertex
                                Tag_true>   // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_true, Tag_false, Tag_true>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_true,Tag_false,Tag_true>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_true,Tag_false,Tag_true>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Halfedge_handle  prv;
    Face_handle      f;
public:
    // Explicit initialization of f to denote border halfedges
    // is needed if Face_handle is a C style pointer.
    HalfedgeDS_halfedge_base() : f( Face_handle()) {}

    // the previous halfedge along the face.
    Halfedge_handle       prev()                       { return prv; }
    Halfedge_const_handle prev() const                 { return prv; }
    void                  set_prev( Halfedge_handle h) { prv = h; }

    // the face to the left.
    Face_handle           face()                       { return f; }
    Face_const_handle     face() const                 { return f; }
    void                  set_face( Face_handle g)     { f = g; }

    bool is_border() const { return f == Face_handle();}
        // is true if `h' is a border halfedge.
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_false,  // prev
                                Tag_true,   // vertex
                                Tag_true>   // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_false, Tag_true, Tag_true>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_false,Tag_true,Tag_true>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_false,Tag_true,Tag_true>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Vertex_handle    v;
    Face_handle      f;
public:
    // Explicit initialization of f to denote border halfedges
    // is needed if Face_handle is a C style pointer.
    HalfedgeDS_halfedge_base() : f( Face_handle()) {}

    // the incident vertex.
    Vertex_handle         vertex()                     { return v; }
    Vertex_const_handle   vertex() const               { return v; }
    void                  set_vertex( Vertex_handle w) { v = w; }

    // the face to the left.
    Face_handle           face()                       { return f; }
    Face_const_handle     face() const                 { return f; }
    void                  set_face( Face_handle g)     { f = g; }

    bool is_border() const { return f == Face_handle();}
        // is true if `h' is a border halfedge.
};

template < class Refs >
class HalfedgeDS_halfedge_base< Refs,
                                Tag_true,  // prev
                                Tag_true,  // vertex
                                Tag_true>  // face
    : public HalfedgeDS_halfedge_base_base<
        Refs, Tag_true, Tag_true, Tag_true>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, Tag_true,Tag_true,Tag_true>
        Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, Tag_true,Tag_true,Tag_true>
        Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Halfedge_handle  prv;
    Vertex_handle    v;
    Face_handle      f;
public:
    // Explicit initialization of f to denote border halfedges
    // is needed if Face_handle is a C style pointer.
    HalfedgeDS_halfedge_base() : f( Face_handle()) {}

    // the previous halfedge along the face.
    Halfedge_handle       prev()                       { return prv; }
    Halfedge_const_handle prev() const                 { return prv; }
    void                  set_prev( Halfedge_handle h) { prv = h; }

    // the incident vertex.
    Vertex_handle         vertex()                     { return v; }
    Vertex_const_handle   vertex() const               { return v; }
    void                  set_vertex( Vertex_handle w) { v = w; }

    // the face to the left.
    Face_handle           face()                       { return f; }
    Face_const_handle     face() const                 { return f; }
    void                  set_face( Face_handle g)     { f = g; }

    bool is_border() const { return f == Face_handle();}
        // is true if `h' is a border halfedge.
};

#else // CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION //

// Partial specialization doesn't work. So, we cannot get rid
// of the previous halfedge, vertex, or face reference.
// So, we just waste the space and have always all of them.

template < class Refs, class TP, class TV, class TF>
struct HalfedgeDS_halfedge_base_base {
    // Base_base will be used to access set_opposite(), which is
    // made private in the normal halfedge bases. Since halfedges
    // come always in pairs, managed by the HDS, the set_opposite()
    // member function is protected from the user.
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_halfedge_base_base<Refs,TP,TV,TF> Base_base;
    typedef TP                                   Supports_halfedge_prev;
    typedef TV                                   Supports_halfedge_vertex;
    typedef TF                                   Supports_halfedge_face;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Face                  Face;
private:
    Halfedge_handle  opp;
    Halfedge_handle  nxt;
public:
    Halfedge_handle       opposite()                        { return opp;}
    Halfedge_const_handle opposite() const                  { return opp;}
    void                  set_opposite( Halfedge_handle h)  { opp = h;}
    Halfedge_handle       next()                            { return nxt;}
    Halfedge_const_handle next() const                      { return nxt;}
    void                  set_next( Halfedge_handle h)      { nxt = h;}

    bool is_border() const { return false;}
        // is always false as long as faces are not supported.
};

template < class Refs, class TP = Tag_true, // prev
                       class TV = Tag_true, // vertex
                       class TF = Tag_true> // face
class HalfedgeDS_halfedge_base
    : public HalfedgeDS_halfedge_base_base< Refs, TP, TV, TF>
{
public:
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef HalfedgeDS_halfedge_base<Refs, TP, TV, TF>       Base;
    typedef HalfedgeDS_halfedge_base_base<Refs, TP, TV, TF>  Base_base;
private:
    void  set_opposite( Halfedge_handle h)  { Base_base::set_opposite(h);}
    Halfedge_handle  prv;
    Vertex_handle    v;
    Face_handle      f;
public:
    // Explicit initialization of f to denote border halfedges
    // is needed if Face_handle is a C style pointer.
    HalfedgeDS_halfedge_base() : f( Face_handle()) {}

    // the previous halfedge along the face.
    Halfedge_handle       prev()                       { return prv; }
    Halfedge_const_handle prev() const                 { return prv; }
    void                  set_prev( Halfedge_handle h) { prv = h; }

    // the incident vertex.
    Vertex_handle         vertex()                     { return v; }
    Vertex_const_handle   vertex() const               { return v; }
    void                  set_vertex( Vertex_handle w) { v = w; }

    // the face to the left.
    Face_handle           face()                       { return f; }
    Face_const_handle     face() const                 { return f; }
    void                  set_face( Face_handle g)     { f = g; }

    bool is_border() const { return f == Face_handle();}
        // is true if `h' is a border halfedge.
};

#endif // CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION //

CGAL_END_NAMESPACE

#endif // CGAL_HALFEDGEDS_HALFEDGE_BASE_H //
// EOF //
