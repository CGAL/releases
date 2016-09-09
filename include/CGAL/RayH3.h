// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : RayH3.fw
// file          : include/CGAL/RayH3.h
// package       : H3 (2.12)
// revision      : 2.12
// revision_date : 16 Aug 2000 
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

#ifndef CGAL_LINEH3_H
#include <CGAL/LineH3.h>
#endif // CGAL_LINEH3_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class Ray_repH3 : public Ref_counted
{
 public:
  Ray_repH3() {}
  Ray_repH3(const PointH3<FT,RT>& p, const DirectionH3<FT,RT>& d)
   : startpoint(p), direction(d)
  {}

 friend class RayH3<FT,RT>;

 private:
  PointH3<FT,RT>      startpoint;
  DirectionH3<FT,RT>  direction;
};

template < class FT, class RT >
class RayH3 : public Handle_for< Ray_repH3<FT,RT> >
{
  public:
        RayH3();
        RayH3( const PointH3<FT,RT>& sp, const PointH3<FT,RT>& secondp);
        RayH3( const PointH3<FT,RT>& sp, const DirectionH3<FT,RT>& d);

    PointH3<FT,RT> start() const;
    PointH3<FT,RT> source() const;
    PointH3<FT,RT> second_point() const;
    PointH3<FT,RT> point(int i) const;
    DirectionH3<FT,RT>
                   direction() const;
    LineH3<FT,RT>  supporting_line() const;
    RayH3<FT,RT>   opposite() const;
    RayH3<FT,RT>   transform( const Aff_transformationH3<FT,RT> & t) const;
    bool           has_on(const PointH3<FT,RT> p) const;
    bool           collinear_has_on(const PointH3<FT,RT> p) const;
    bool           is_degenerate() const;

    bool           operator==(const RayH3<FT,RT>& r) const;
    bool           operator!=(const RayH3<FT,RT>& r) const;
};

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3()
 : Handle_for< Ray_repH3<FT,RT> >( Ray_repH3<FT,RT>() )
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3( const PointH3<FT,RT>& sp,
                     const PointH3<FT,RT>& secondp)
 : Handle_for<Ray_repH3<FT,RT> >(Ray_repH3<FT,RT>(sp,(secondp-sp).direction()))
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3( const PointH3<FT,RT>& sp,
                     const DirectionH3<FT,RT>& d)
 : Handle_for<Ray_repH3<FT,RT> >( Ray_repH3<FT,RT>(sp, d ))
{}

template < class FT, class RT >
inline
PointH3<FT,RT>
RayH3<FT,RT>::source() const
{ return ptr->startpoint; }

template < class FT, class RT >
inline
PointH3<FT,RT>
RayH3<FT,RT>::start() const
{ return ptr->startpoint; }

template < class FT, class RT >
inline
DirectionH3<FT,RT>
RayH3<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH3<FT,RT>( ptr->direction );
}


template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
RayH3<FT,RT>::second_point() const
{ return start() + direction().to_vector(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
RayH3<FT,RT>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  return start() + RT(i)*(direction().to_vector() ) ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH3<FT,RT>
RayH3<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH3<FT,RT>(start(), second_point() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH3<FT,RT>
RayH3<FT,RT>::opposite() const
{ return RayH3<FT,RT>( start(), - direction() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH3<FT,RT>
RayH3<FT,RT>::transform( const Aff_transformationH3<FT,RT> & t) const
{ return RayH3<FT,RT>(t.transform(start()), t.transform(direction()) ); }


#ifndef NO_OSTREAM_INSERT_RAYH3
template < class FT, class RT >
std::ostream &operator<<(std::ostream &os, const RayH3<FT,RT> &r)
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
#endif // NO_OSTREAM_INSERT_RAYH3

#ifndef NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT  >
std::istream &operator>>(std::istream &is, RayH3<FT,RT> &r)
{
  PointH3<FT,RT> p;
  DirectionH3<FT,RT> d;
  is >> p >> d;
  r = RayH3<FT,RT>(p, d);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::has_on(const PointH3<FT,RT> p) const
{
  return ( (  p == start() )
         ||(  DirectionH3<FT,RT>(p - start()) == direction() ) );
}

template < class FT, class RT >
inline                                      /* XXX */
bool
RayH3<FT,RT>::collinear_has_on(const PointH3<FT,RT> p) const
{ return has_on(p); }

template < class FT, class RT >
inline
bool
RayH3<FT,RT>::is_degenerate() const
{ return (ptr->direction).is_degenerate() ; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::operator==(const RayH3<FT,RT>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::operator!=( const RayH3<FT,RT>& r) const
{ return !operator==(r); }



CGAL_END_NAMESPACE


#endif // CGAL_RAYH3_H
