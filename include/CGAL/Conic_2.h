// ======================================================================
//
// Copyright (c) 1997,1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Conic_2.h
// package       : Min_ellipse_2 (3.1.1)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
//
// source        : web/Optimisation/Conic_2.aw
// revision      : $Revision: 5.2 $
// revision_date : $Date: 1998/11/11 09:59:19 $
// author(s)     : Bernd Gärtner
//                 Sven Schönherr
//
// coordinator   : ETH Zürich (Bernd Gärtner)
//
// implementation: 2D Conic
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CONIC_2_H
#define CGAL_CONIC_2_H

#ifndef CGAL_REP_CLASS_DEFINED
#  error  no representation class defined
#endif // CGAL_REP_CLASS_DEFINED

#ifdef CGAL_HOMOGENEOUS_H
#  include <CGAL/ConicHPA2.h>
#endif

#ifdef CGAL_CARTESIAN_H
#  include <CGAL/ConicCPA2.h>
#endif

#ifndef CGAL_POINT_2_H
#  include <CGAL/Point_2.h>
#endif

#ifndef CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H
#include <CGAL/IO/forward_decl_window_stream.h>
#endif

template < class _R >
class CGAL_Optimisation_ellipse_2;

template < class _R >
CGAL_Window_stream&
operator << ( CGAL_Window_stream&, const CGAL_Optimisation_ellipse_2<_R>&);

template < class _R>
class CGAL_Conic_2 : public _R::Conic_2 {

    friend  class CGAL_Optimisation_ellipse_2<_R>;

    friend  CGAL_Window_stream&  operator << CGAL_NULL_TMPL_ARGS (
        CGAL_Window_stream&, const CGAL_Optimisation_ellipse_2<_R>&);

  public:

    // types
    typedef  _R                    R;
    typedef  typename _R::RT       RT;
    typedef  typename _R::FT       FT;
    typedef  typename _R::Conic_2  Conic_2;

    // construction
    CGAL_Conic_2 ()
    {}
    
    CGAL_Conic_2 (RT r, RT s, RT t, RT u, RT v, RT w)
        : R::Conic_2 (r, s, t, u, v, w)
    {}
    
    

    // general access
    RT r () const
    {
        return Conic_2::r();
    }
    
    RT s () const
    {
        return Conic_2::s();
    }
    
    RT t () const
    {
        return Conic_2::t();
    }
    
    RT u () const
    {
        return Conic_2::u();
    }
    
    RT v () const
    {
        return Conic_2::v();
    }
    
    RT w () const
    {
        return Conic_2::w();
    }
    
    CGAL_Point_2<R> center () const
    {
        return Conic_2::center();
    }
    
    

    // type related access
    CGAL_Conic_type conic_type () const
    {
        return Conic_2::conic_type();
    }
    
    bool is_hyperbola () const
    {
        return Conic_2::is_hyperbola();
    }
    
    bool is_parabola () const
    {
        return Conic_2::is_parabola();
    }
    
    bool is_ellipse () const
    {
        return Conic_2::is_ellipse();
    }
    
    bool is_empty () const
    {
        return Conic_2::is_empty();
    }
    
    bool is_trivial () const
    {
        return Conic_2::is_trivial();
    }
    
    bool is_degenerate () const
    {
        return Conic_2::is_degenerate();
    }
    
    

    // orientation related access
    CGAL_Orientation orientation () const
    {
        return Conic_2::orientation ();
    }
    
    CGAL_Oriented_side oriented_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::oriented_side (p);
    }
    
    bool has_on_positive_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on_positive_side (p);
    }
    
    bool has_on_negative_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on_negative_side (p);
    }
    
    bool has_on_boundary (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on_boundary (p);
    }
    
    bool has_on (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on (p);
    }
    
    CGAL_Convex_side convex_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::convex_side (p);
    }
    
    bool has_on_convex_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on_convex_side (p);
    }
    
    bool has_on_nonconvex_side (const CGAL_Point_2<R> &p) const
    {
        return Conic_2::has_on_nonconvex_side (p);
    }
    
    

    // comparisons
    bool operator == ( const CGAL_Conic_2<_R>& c) const
    {
        return Conic_2::operator == ( (Conic_2)c);
    }
    
    bool operator != ( const CGAL_Conic_2<_R>& c) const
    {
        return( ! operator == ( c));
    }

    // set methods
    void set (RT r, RT s, RT t,
              RT u, RT v, RT w)
    {
        Conic_2::set (r, s, t, u, v, w);
    }
    
    void set_opposite ()
    {
        Conic_2::set_opposite();
    }
    
    void set_linepair (const CGAL_Point_2<R> &p1, const CGAL_Point_2<R> &p2,
                       const CGAL_Point_2<R> &p3, const CGAL_Point_2<R> &p4)
    {
        Conic_2::set_linepair (p1, p2, p3, p4);
    }
    
    void set_ellipse (const CGAL_Point_2<R> &p1, const CGAL_Point_2<R> &p2,
                      const CGAL_Point_2<R> &p3)
    {
        Conic_2::set_ellipse (p1, p2, p3);
    }
    
    void set_ellipse (const CGAL_Point_2<R> &p1, const CGAL_Point_2<R> &p2,
                      const CGAL_Point_2<R> &p3, const CGAL_Point_2<R> &p4,
                      CGAL_Orientation o = CGAL_POSITIVE)
    {
        Conic_2::set_ellipse (p1, p2, p3, p4, o);
    }
    
    void set (const CGAL_Point_2<R> &p1, const CGAL_Point_2<R> &p2,
              const CGAL_Point_2<R> &p3, const CGAL_Point_2<R> &p4,
              const CGAL_Point_2<R> &p5,
              CGAL_Orientation o = CGAL_POSITIVE)
    {
        Conic_2::set (p1, p2, p3, p4, p5, o);
    }
    
    

  private:
    void set_linear_combination (
        const RT &a1, const CGAL_Conic_2<R> &c1,
        const RT &a2, const CGAL_Conic_2<R> &c2)
    {
        Conic_2::set_linear_combination (a1, c1, a2, c2);
    }
    
    static void set_two_linepairs (const CGAL_Point_2<R> &p1,
                                   const CGAL_Point_2<R> &p2,
                                   const CGAL_Point_2<R> &p3,
                                   const CGAL_Point_2<R> &p4,
                                   CGAL_Conic_2<R> &pair1,
                                   CGAL_Conic_2<R> &pair2)
    {
        Conic_2::set_two_linepairs (p1, p2, p3, p4, pair1, pair2);
    }
    
    void set_ellipse (const CGAL_Conic_2<R> &pair1,
                      const CGAL_Conic_2<R> &pair2)
    {
        Conic_2::set_ellipse (pair1, pair2);
    }
    
    void set (const CGAL_Conic_2<R> &c1, const CGAL_Conic_2<R> &c2,
              const CGAL_Point_2<R> &p)
    {
        Conic_2::set( c1, c2, p);  analyse();
    }
    
    CGAL_Sign vol_derivative (RT dr, RT ds,
                              RT dt, RT du,
                              RT dv, RT dw) const
    {
        return Conic_2::vol_derivative (dr, ds, dt, du, dv, dw);
    }
    
    double vol_minimum (RT dr, RT ds,
                        RT dt, RT du,
                        RT dv, RT dw) const
    {
        return Conic_2::vol_minimum (dr, ds, dt, du, dv, dw);
    }
    
    
};



#ifndef CGAL_NO_OSTREAM_INSERT_CONIC_2
template< class _R>
ostream& operator << ( ostream& os, const CGAL_Conic_2<_R>& c)
{
    return( os << c.r() << ' ' << c.s() << ' ' << c.t() << ' '
               << c.u() << ' ' << c.v() << ' ' << c.w());
}
#endif // CGAL_NO_OSTREAM_INSERT_CONIC_2

#endif // CGAL_CONIC_2_H

// ===== EOF ==================================================================
