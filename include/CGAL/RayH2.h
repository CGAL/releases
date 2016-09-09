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
// file          : include/CGAL/RayH2.h
// package       : H2 (2.37)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/02/14 18:34:32 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_RAYH2_H
#define CGAL_RAYH2_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Ray_repH2 : public Ref_counted
{
public:
    Ray_repH2() {}
    Ray_repH2(const PointH2<R>& fp, const PointH2<R>& sp)
	: start(fp), second(sp) {}

    PointH2<R>  start;
    PointH2<R>  second;
};

template < class R >
class Simple_Ray_repH2
{
public:
    Simple_Ray_repH2() {}
    Simple_Ray_repH2(const PointH2<R>& fp, const PointH2<R>& sp)
	: start(fp), second(sp) {}

    PointH2<R>  start;
    PointH2<R>  second;
};

template < class R_ >
class RayH2
  : public R_::Ray_handle_2
{
public:
    typedef R_                                    R;
    typedef typename R::FT                        FT;
    typedef typename R::RT                        RT;

    typedef typename R::Ray_handle_2              Ray_handle_2_;
    typedef typename Ray_handle_2_::element_type   Ray_ref_2;

    RayH2()
      : Ray_handle_2_(Ray_ref_2()) {}
    RayH2( const PointH2<R>& sp, const PointH2<R>& secondp)
      : Ray_handle_2_(Ray_ref_2(sp, secondp)) {}
    RayH2( const PointH2<R>& sp, const DirectionH2<R>& d)
      : Ray_handle_2_(Ray_ref_2(sp, sp + d.to_vector())) {}

    bool    operator==(const RayH2<R>& r) const;
    bool    operator!=(const RayH2<R>& r) const;

    PointH2<R>     start() const;
    PointH2<R>     source() const;
    PointH2<R>     second_point() const;
    PointH2<R>     point(int i) const;
    DirectionH2<R> direction() const;
    LineH2<R>      supporting_line() const;
    RayH2<R>       opposite() const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const PointH2<R> p) const;
    bool    collinear_has_on(const PointH2<R> p) const;
    bool    is_degenerate() const;

    RayH2<R> transform( const Aff_transformationH2<R> & t) const;
};


template < class R >
inline
PointH2<R>
RayH2<R>::source() const
{ return Ptr()->start; }

template < class R >
inline
PointH2<R>
RayH2<R>::start() const
{ return Ptr()->start; }

template < class R >
CGAL_KERNEL_INLINE
DirectionH2<R>
RayH2<R>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH2<R>( Ptr()->second - Ptr()->start );
}
template < class R >
inline
PointH2<R>
RayH2<R>::second_point() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Ptr()->second;
}

template < class R >
CGAL_KERNEL_INLINE
PointH2<R>
RayH2<R>::point(int i) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  CGAL_kernel_precondition( i>= 0 );
  VectorH2<R> v = direction().to_vector();
  return start() + RT(i) * v;
}

template < class R >
inline
LineH2<R>
RayH2<R>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH2<R>(*this);
}

template < class R >
inline
RayH2<R>
RayH2<R>::opposite() const
{ return RayH2<R>( Ptr()->start, - direction() ); }

template < class R >
CGAL_KERNEL_INLINE
RayH2<R>
RayH2<R>::
transform(const Aff_transformationH2<R> & t) const
{
  return RayH2<R>(t.transform(Ptr()->start),
                           t.transform(Ptr()->second) );
}

#ifndef CGAL_NO_OSTREAM_INSERT_RAYH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const RayH2<R> &r)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << r.source() << ' ' << r.second_point();
    case IO::BINARY :
        return os << r.source() << r.second_point();
    default:
       return os << "RayC2(" << r.source() <<  ", " << r.second_point() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYH2
template < class R >
std::istream &
operator>>(std::istream &is, RayH2<R> &r)
{
  PointH2<R> p, q;
  is >> p >> q;
  r = RayH2<R>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYH2

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_horizontal() const
{
  return start().hy()*second_point().hw() == second_point().hy()*start().hw();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_vertical() const
{
  return start().hx()*second_point().hw() == second_point().hx()*start().hw();
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::has_on(const PointH2<R> p) const
{
  return ( (  p == start() )
        ||(DirectionH2<R>(p - Ptr()->start) == direction() ) );
}

template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::is_degenerate() const
{ return ( (Ptr()->start == Ptr()->second) ); }

template < class R >
inline
bool
RayH2<R>::collinear_has_on(const PointH2<R> p) const
{ return has_on(p); }
template < class R >
CGAL_KERNEL_INLINE
bool
RayH2<R>::operator==(const RayH2<R>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class R >
inline
bool
RayH2<R>::operator!=( const RayH2<R>& r) const
{ return !(*this == r); }

CGAL_END_NAMESPACE

#endif // CGAL_RAYH2_H
