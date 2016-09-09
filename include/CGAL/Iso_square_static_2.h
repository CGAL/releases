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
// file          : include/CGAL/Iso_square_static_2.h
// package       : Matrix_search (1.17)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1999/06/01 14:08:05 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2D Iso-squares with static radius
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (ISO_SQUARE_STATIC_2_H)
#define ISO_SQUARE_STATIC_2_H 1

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H

CGAL_BEGIN_NAMESPACE

// class Iso_square_static_2 represents a square with center and radius.
// all objects have the same radius ==> radius is a static member
// no handle-rep stuff

template < class _R >
class Iso_square_static_2 {
public:
  typedef _R                       R;
  typedef typename _R::Point_2     Point_2;
  typedef typename _R::FT          FT;

  Iso_square_static_2() {}

  Iso_square_static_2( const Point_2& p)
  : _center( p)
  {}

  const Point_2&
  center() const
  { return _center; }

  FT
  radius() const
  { return _radius; }

  static void
  set_radius( FT r)
  {
    CGAL_optimisation_precondition( r >= 0);
    _radius = r;
  }

  FT
  xmin() const
  { return center().x() - radius(); }

  FT
  xmax() const
  { return center().x() + radius(); }

  FT
  ymin() const
  { return center().y() - radius(); }

  FT
  ymax() const
  { return center().y() + radius(); }

  bool
  has_on_bounded_side( const Point_2& p) const
  {
    return p.x() > xmin() && p.x() < xmax() &&
      p.y() > ymin() && p.y() < ymax();
  }

  bool
  has_on_unbounded_side( const Point_2& p) const
  {
    return p.x() < xmin() || p.x() > xmax() ||
      p.y() < ymin() || p.y() > ymax();
  }

private:
  Point_2      _center;
  static FT    _radius;
};

// for output to ostream:
template< class R >
ostream& operator<<( ostream& os,
                     const Iso_square_static_2< R >& s)
{
  switch(os.iword(IO::mode)) {
  case IO::ASCII :
    return os << s.center() << ' ' << s.radius();
  case IO::BINARY :
    os << s.center() << s.radius();
    // write(os, s.radius());
    return os;
  default:
    return os << "Iso_square_static_2(" << s.center() << ", "
              << s.radius() << ')';
  }
}

// for input from istream:
template < class R >
istream&
operator>>( istream& is,
            Iso_square_static_2< R >& s)
{
  typename R::Point_2  c;
  typename R::FT       r;

  is >> c >> r;

  s = Iso_square_static_2< R >( c);
  s.set_radius( r);
  return is;
}

#ifdef CGAL_WINDOW_STREAM_H

// for output to Window_stream:
template< class R >
Window_stream&
operator<<( Window_stream& w,
            const Iso_square_static_2< R >& s)
{
  w.draw_rectangle( to_double( s.xmin()),
                    to_double( s.ymin()),
                    to_double( s.xmax()),
                    to_double( s.ymax()));
  return w;
}

// for input from Window_stream:
template< class R >
Window_stream&
operator>>( Window_stream& w,
            Iso_square_static_2< R >& r)
{
  Window_stream W;
  drawing_mode old_mode( W.set_mode( leda_xor_mode));
  leda_color old_color( W.set_color( leda_red));

  // get center:
  double c_x, c_y;
  do {}
  while ( W.get_mouse( c_x, c_y) == NO_BUTTON);

  // get radius:
  double x, y, rad( 0), r_old;
  int i;
  do {
    i = W.get_mouse( x, y);
    r_old = rad;
    rad = max( fabs( x - c_x), fabs( y - c_y));
    if ( r_old != rad) {
      W.draw_rectangle( c_x - r_old, c_y - r_old,
                        c_x + r_old, c_y + r_old);
      W.draw_rectangle( c_x - rad, c_y - rad,
                        c_x + rad, c_y + rad);
    }
  } while ( i != MOUSE_BUTTON( 1));

  W.draw_rectangle( c_x - rad, c_y - rad,
                    c_x + rad, c_y + rad);
  W.set_mode( old_mode);
  W.set_color( old_color);

  r = Iso_square_static_2< R >( c_x, c_y);
  r.set_radius( rad);
  return w << r;
}

#endif // CGAL_WINDOW_STREAM_H

// the static radius of all Iso_square_static_2< R >:
template < class R >
Iso_square_static_2< R >::FT
Iso_square_static_2< R >::_radius;

CGAL_END_NAMESPACE


#endif // ! (ISO_SQUARE_STATIC_2_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

