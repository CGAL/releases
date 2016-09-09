// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/RayH3.h
// package       : H3 (2.34)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/02/13 15:30:39 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_RAYH3_H
#define CGAL_RAYH3_H

#include <CGAL/LineH3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Ray_repH3 : public Ref_counted
{
 public:
  Ray_repH3() {}
  Ray_repH3(const PointH3<R>& p, const DirectionH3<R>& d)
   : startpoint(p), direction(d) {}

 friend class RayH3<R>;

 private:
  PointH3<R>      startpoint;
  DirectionH3<R>  direction;
};

template < class R >
class Simple_Ray_repH3
{
 public:
  Simple_Ray_repH3() {}
  Simple_Ray_repH3(const PointH3<R>& p, const DirectionH3<R>& d)
   : startpoint(p), direction(d) {}

 friend class RayH3<R>;

 private:
  PointH3<R>      startpoint;
  DirectionH3<R>  direction;
};

template < class R_ >
class RayH3
  : public R_::Ray_handle_3
{
  public:
    typedef R_                R;
    typedef typename R::RT    RT;
    typedef typename R::FT    FT;

    typedef typename R::Ray_handle_3              Ray_handle_3_;
    typedef typename Ray_handle_3_::element_type   Ray_ref_3;

    RayH3()
      : Ray_handle_3_(Ray_ref_3()) {}

    RayH3( const PointH3<R>& sp, const PointH3<R>& secondp)
      : Ray_handle_3_(Ray_ref_3(sp, (secondp-sp).direction())) {}

    RayH3( const PointH3<R>& sp, const DirectionH3<R>& d)
      : Ray_handle_3_(Ray_ref_3(sp, d)) {}

    PointH3<R> start() const;
    PointH3<R> source() const;
    PointH3<R> second_point() const;
    PointH3<R> point(int i) const;
    DirectionH3<R> direction() const;
    LineH3<R>  supporting_line() const;
    RayH3<R>   opposite() const;
    RayH3<R>   transform( const Aff_transformationH3<R> & t) const;
    bool           has_on(const PointH3<R> p) const;
    bool           collinear_has_on(const PointH3<R> p) const;
    bool           is_degenerate() const;

    bool           operator==(const RayH3<R>& r) const;
    bool           operator!=(const RayH3<R>& r) const;
};

template < class R >
inline
PointH3<R>
RayH3<R>::source() const
{ return Ptr()->startpoint; }

template < class R >
inline
PointH3<R>
RayH3<R>::start() const
{ return Ptr()->startpoint; }

template < class R >
inline
DirectionH3<R>
RayH3<R>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH3<R>( Ptr()->direction );
}


template < class R >
CGAL_KERNEL_INLINE
PointH3<R>
RayH3<R>::second_point() const
{ return start() + direction().to_vector(); }

template < class R >
CGAL_KERNEL_INLINE
PointH3<R>
RayH3<R>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  return start() + RT(i)*(direction().to_vector() ) ;
}

template < class R >
CGAL_KERNEL_INLINE
LineH3<R>
RayH3<R>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH3<R>(start(), second_point() );
}

template < class R >
CGAL_KERNEL_INLINE
RayH3<R>
RayH3<R>::opposite() const
{ return RayH3<R>( start(), - direction() ); }

template < class R >
CGAL_KERNEL_INLINE
RayH3<R>
RayH3<R>::transform( const Aff_transformationH3<R> & t) const
{ return RayH3<R>(t.transform(start()), t.transform(direction()) ); }


#ifndef CGAL_NO_OSTREAM_INSERT_RAYH3
template < class R >
std::ostream &operator<<(std::ostream &os, const RayH3<R> &r)
{
  switch(os.iword(IO::mode))
  {
      case IO::ASCII :
          return os << r.start() << ' ' << r.direction();
      case IO::BINARY :
          return os<< r.start() << r.direction();
      default:
          return os << "RayH3(" << r.start() <<  ", " << r.direction() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYH3
template < class R  >
std::istream &operator>>(std::istream &is, RayH3<R> &r)
{
  PointH3<R> p;
  DirectionH3<R> d;
  is >> p >> d;
  r = RayH3<R>(p, d);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYH3

template < class R >
CGAL_KERNEL_INLINE
bool
RayH3<R>::has_on(const PointH3<R> p) const
{
  return ( (  p == start() )
         ||(  DirectionH3<R>(p - start()) == direction() ) );
}

template < class R >
inline                                      /* XXX */
bool
RayH3<R>::collinear_has_on(const PointH3<R> p) const
{ return has_on(p); }

template < class R >
inline
bool
RayH3<R>::is_degenerate() const
{ return (Ptr()->direction).is_degenerate() ; }

template < class R >
CGAL_KERNEL_INLINE
bool
RayH3<R>::operator==(const RayH3<R>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class R >
CGAL_KERNEL_INLINE
bool
RayH3<R>::operator!=( const RayH3<R>& r) const
{ return !operator==(r); }

CGAL_END_NAMESPACE

#endif // CGAL_RAYH3_H
