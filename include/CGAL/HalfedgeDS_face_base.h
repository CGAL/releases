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
// file          : include/CGAL/HalfedgeDS_face_base.h
// package       : HalfedgeDS (3.33)
// chapter       : Halfedge Data Structures
//
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/12/18 13:01:45 $
//
// author(s)     : Lutz Kettner
// coordinator   : MPI Saarbruecken
//
// Halfedge Data Structure Base Classes for Faces.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGEDS_FACE_BASE_H
#define CGAL_HALFEDGEDS_FACE_BASE_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

CGAL_BEGIN_NAMESPACE

#if ! defined( CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION) \
 && ! defined( CGAL_CFG_SUNPRO_PARTIAL_SPEC_BUG)

// We use Tag_false to indicate that no plane type is provided.

template < class Refs, class T = Tag_true, class Pln = Tag_false>
class HalfedgeDS_face_base;

template < class Refs >
class HalfedgeDS_face_base< Refs, Tag_false, Tag_false> {
public:
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_face_base< Refs, Tag_false, Tag_false>  Base;
    typedef Tag_false                            Supports_face_halfedge;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Halfedge              Halfedge;
    // Additional tags required by Polyhedron.
    typedef Tag_false                            Supports_face_plane;
    struct Plane_not_supported {};
    typedef Plane_not_supported                  Plane;
    // No longer required.
    // typedef Tag_false                            Supports_face_normal;
};

template < class Refs >
class HalfedgeDS_face_base< Refs, Tag_true, Tag_false> {
public:
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_face_base< Refs, Tag_true, Tag_false>   Base;
    typedef Tag_true                             Supports_face_halfedge;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Halfedge              Halfedge;
    // Additional tags required by Polyhedron.
    typedef Tag_false                            Supports_face_plane;
    struct Plane_not_supported {};
    typedef Plane_not_supported                  Plane;
    // No longer required.
    //typedef Tag_false                            Supports_face_normal;
private:
    Halfedge_handle hdg;
public:
    Halfedge_handle       halfedge()                        { return hdg; }
    Halfedge_const_handle halfedge() const                  { return hdg; }
    void                  set_halfedge( Halfedge_handle h)  { hdg = h; }
};

template < class Refs, class Pln >
class HalfedgeDS_face_base< Refs, Tag_false, Pln> {
public:
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_face_base< Refs, Tag_false, Pln>     Base;
    typedef Tag_false                            Supports_face_halfedge;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Halfedge              Halfedge;
    // Additional tags and types required by Polyhedron.
    typedef Tag_true                             Supports_face_plane;
    typedef Pln                                  Plane;
    // No longer required.
    //typedef Tag_true                             Supports_face_normal;
    //typedef Trts                                 Traits;
    //typedef typename Traits::Normal              Normal;
    //typedef typename Traits::Plane               Plane;
private:
    Plane  pln;
public:
    HalfedgeDS_face_base() {}
    HalfedgeDS_face_base( const Plane& g) : pln(g) {}
    Plane&                plane()                           { return pln; }
    const Plane&          plane() const                     { return pln; }
    // No longer required.
    // Normal              normal() const { return pln.orthogonal_vector();}
};

template < class Refs, class Pln >
class HalfedgeDS_face_base< Refs, Tag_true, Pln> {
public:
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_face_base< Refs, Tag_true, Pln>      Base;
    typedef Tag_true                             Supports_face_halfedge;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Halfedge              Halfedge;
    // Additional tags and types required by Polyhedron.
    typedef Tag_true                             Supports_face_plane;
    typedef Pln                                  Plane;
    // No longer required.
    //typedef Tag_true                             Supports_face_normal;
    //typedef Trts                                 Traits;
    //typedef typename Traits::Normal              Normal;
    //typedef typename Traits::Plane               Plane;
private:
    Halfedge_handle hdg;
    Plane           pln;
public:
    HalfedgeDS_face_base() {}
    HalfedgeDS_face_base( const Plane& g) : pln(g) {}
    Halfedge_handle       halfedge()                        { return hdg; }
    Halfedge_const_handle halfedge() const                  { return hdg; }
    void                  set_halfedge( Halfedge_handle h)  { hdg = h; }
    Plane&                plane()                           { return pln; }
    const Plane&          plane() const                     { return pln; }
    // No longer required.
    //Normal                normal() const { return pln.orthogonal_vector();}
};

#else //    ! defined( CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION)
      // && ! defined( CGAL_CFG_SUNPRO_PARTIAL_SPEC_BUG)

// Partial specialization doesn't work. We can factor out the
// Plane parameter in a base class with full specialization
// on 'Tag_false', but we cannot get rid of the halfedge reference.
// So, we just waste the space and have it always.
//   Furthermore, is is likely to have a non-optimal memory
// price-tag for the base class as well if it is the empty base
// class for the plane type 'Tag_false', since empty structs probably
// consume at least a byte, probably a word.
//   See HalfedgeDS_face_min_base.h for an alternative.

// We use Tag_false to indicate that no plane type is provided.

template < class Pln>
struct I_HalfedgeDS_face_base_plane {
    typedef Tag_true Supports_plane;
    typedef Pln      Plane;
    // No longer required.
    //typedef Trts                                 Traits;
    //typedef typename Traits::Plane               Plane;
    //typedef typename Traits::Normal              Normal;
    Plane plane;
    I_HalfedgeDS_face_base_plane() {}
    I_HalfedgeDS_face_base_plane( const Plane& pl) : plane(pl) {}
};
template <>
struct I_HalfedgeDS_face_base_plane<Tag_false> {
    typedef Tag_false Supports_plane;
    struct Plane_not_supported {};
    typedef Plane_not_supported Plane;
    // No longer required.
    //struct Normal_not_supported {};
    //typedef Normal_not_supported Normal;
};

template < class Refs, class T = Tag_true, class Pln = Tag_false>
class HalfedgeDS_face_base : public I_HalfedgeDS_face_base_plane<Pln> {
public:
    typedef Refs                                 HalfedgeDS;
    typedef HalfedgeDS_face_base< Refs, T, Pln>  Base;
    typedef Tag_true                             Supports_face_halfedge;
    typedef typename Refs::Vertex_handle         Vertex_handle;
    typedef typename Refs::Vertex_const_handle   Vertex_const_handle;
    typedef typename Refs::Halfedge_handle       Halfedge_handle;
    typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
    typedef typename Refs::Face_handle           Face_handle;
    typedef typename Refs::Face_const_handle     Face_const_handle;
    typedef typename Refs::Vertex                Vertex;
    typedef typename Refs::Halfedge              Halfedge;
    // Additional tags and types required by Polyhedron.
    typedef I_HalfedgeDS_face_base_plane<Pln>    Plane_base;
    typedef typename Plane_base::Supports_plane  Supports_face_plane;
    typedef typename Plane_base::Plane           Plane;
    // No longer required.
    //typedef typename Plane_base::Supports_plane  Supports_face_normal;
    //typedef Trts                                 Traits;
    //typedef typename Plane_base::Normal          Normal;
private:
    Halfedge_handle hdg;
public:
    HalfedgeDS_face_base() {}
    HalfedgeDS_face_base( const Plane& g)
        : I_HalfedgeDS_face_base_plane<Pln>(g) {}
    Halfedge_handle       halfedge()                      { return hdg; }
    Halfedge_const_handle halfedge() const                { return hdg; }
    void                  set_halfedge( Halfedge_handle h){ hdg = h; }
    Plane&                plane()        { return Plane_base::plane; }
    const Plane&          plane()  const { return Plane_base::plane; }
    // No longer required.
    //Normal                normal() const {
    //                          return Plane_base::plane.orthogonal_vector();
    //}
};

#endif //    ! defined( CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION)
       // && ! defined( CGAL_CFG_SUNPRO_PARTIAL_SPEC_BUG)

CGAL_END_NAMESPACE

#endif // CGAL_HALFEDGEDS_FACE_BASE_H //
// EOF //
