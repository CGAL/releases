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
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : RayH2.fw
// file          : include/CGAL/RayH2.h
// package       : H2 (2.4.8)
// revision      : 2.4.8
// revision_date : 10 Dec 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_RAYH2_H
#define CGAL_RAYH2_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class _Ray_repH2 : public Rep
{
public:
                        _Ray_repH2();
                        _Ray_repH2(const PointH2<FT,RT>& fp,
                                        const PointH2<FT,RT>& sp);
                        ~_Ray_repH2(){}

    PointH2<FT,RT>  start;
    PointH2<FT,RT>  second;
};

template < class FT, class RT >
class RayH2 : public Handle
{
public:
            RayH2();
            RayH2( const RayH2<FT,RT>& r);
            RayH2( const PointH2<FT,RT>& sp,
                        const PointH2<FT,RT>& secondp);
            RayH2( const PointH2<FT,RT>& sp,
                        const DirectionH2<FT,RT>& d);
            ~RayH2();

    RayH2<FT,RT>&
            operator=(const RayH2<FT,RT>& r);

    bool    operator==(const RayH2<FT,RT>& r) const;
    bool    operator!=(const RayH2<FT,RT>& r) const;
    bool    identical( const RayH2<FT,RT>& r) const;
    int     id() const;

    PointH2<FT,RT>     start() const;
    PointH2<FT,RT>     source() const;
    PointH2<FT,RT>     second_point() const;
    PointH2<FT,RT>     point(int i) const;
    DirectionH2<FT,RT> direction() const;
    LineH2<FT,RT>      supporting_line() const;
    RayH2<FT,RT>       opposite() const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const PointH2<FT,RT> p) const;
    bool    collinear_has_on(const PointH2<FT,RT> p) const;
    bool    is_degenerate() const;

    RayH2<FT,RT>
            transform( const Aff_transformationH2<FT,RT> & t) const;
protected:

    _Ray_repH2<FT,RT>*    ptr() const;
};



template < class FT, class RT >
inline
_Ray_repH2<FT,RT>::_Ray_repH2()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
_Ray_repH2<FT,RT>::_Ray_repH2(const PointH2<FT,RT>& fp,
                                        const PointH2<FT,RT>& sp)
  : start(fp), second(sp)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH2<FT,RT>::RayH2()
{ PTR = new _Ray_repH2<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH2<FT,RT>::RayH2(const RayH2<FT,RT>& r)
  : Handle(r)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH2<FT,RT>::RayH2( const PointH2<FT,RT>& sp,
                               const PointH2<FT,RT>& secondp)
{ PTR = new _Ray_repH2<FT,RT>(sp,secondp); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH2<FT,RT>::RayH2( const PointH2<FT,RT>& sp,
                               const DirectionH2<FT,RT>& d)
{ PTR = new _Ray_repH2<FT,RT>(sp, sp + d.to_vector()); }

template < class FT, class RT >
inline
RayH2<FT,RT>::~RayH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH2<FT,RT>&
RayH2<FT,RT>::operator=(const RayH2<FT,RT>& r)
{
  Handle::operator=(r);
  return *this;
}
template < class FT, class RT >
inline
PointH2<FT,RT>
RayH2<FT,RT>::source() const
{ return ptr()->start; }

template < class FT, class RT >
inline
PointH2<FT,RT>
RayH2<FT,RT>::start() const
{ return ptr()->start; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
DirectionH2<FT,RT>
RayH2<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH2<FT,RT>( ptr()->second - ptr()->start );
}
template < class FT, class RT >
inline
PointH2<FT,RT>
RayH2<FT,RT>::second_point() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ptr()->second;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
RayH2<FT,RT>::point(int i) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  CGAL_kernel_precondition( i>= 0 );
  VectorH2<FT,RT> v = direction().to_vector();
  return start() + RT(i) * v;
}

template < class FT, class RT >
inline
LineH2<FT,RT>
RayH2<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH2<FT,RT>(*this);
}

template < class FT, class RT >
inline
RayH2<FT,RT>
RayH2<FT,RT>::opposite() const
{ return RayH2<FT,RT>( ptr()->start, - direction() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH2<FT,RT>
RayH2<FT,RT>::
transform(const Aff_transformationH2<FT,RT> & t) const
{
  return RayH2<FT,RT>(t.transform(ptr()->start),
                           t.transform(ptr()->second) );
}

#ifndef NO_OSTREAM_INSERT_RAYH2
template < class FT, class RT >
std::ostream &
operator<<(std::ostream &os, const RayH2<FT,RT> &r)
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
#endif // NO_OSTREAM_INSERT_RAYH2

#ifndef NO_ISTREAM_EXTRACT_RAYH2
template < class FT, class RT >
std::istream &
operator>>(std::istream &is, RayH2<FT,RT> &r)
{
  PointH2<FT,RT> p, q;
  is >> p >> q;
  r = RayH2<FT,RT>(p, q);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_RAYH2
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH2<FT,RT>::is_horizontal() const
{ return start().hy()*second_point().hw() == second_point().hy()*start().hw(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH2<FT,RT>::is_vertical() const
{ return start().hx()*second_point().hw() == second_point().hx()*start().hw(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH2<FT,RT>::has_on(const PointH2<FT,RT> p) const
{
  return ( (  p == start() )
        ||(DirectionH2<FT,RT>(p - ptr()->start) == direction() ) );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH2<FT,RT>::is_degenerate() const
{ return ( (ptr()->start == ptr()->second) ); }

template < class FT, class RT >
inline
bool
RayH2<FT,RT>::collinear_has_on(const PointH2<FT,RT> p) const
{ return has_on(p); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH2<FT,RT>::operator==(const RayH2<FT,RT>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class FT, class RT >
inline
bool
RayH2<FT,RT>::operator!=( const RayH2<FT,RT>& r) const
{ return !(*this == r); }   /* XXX */

template < class FT, class RT >
inline
bool
RayH2<FT,RT>::identical( const RayH2<FT,RT>& r) const
{ return ( PTR == r.PTR ); }

template < class FT, class RT >
inline
int
RayH2<FT,RT>::id() const
{ return (int)PTR; }
template < class FT, class RT >
inline
_Ray_repH2<FT,RT>*
RayH2<FT,RT>::ptr() const
{ return (_Ray_repH2<FT,RT>*)PTR; }

CGAL_END_NAMESPACE


#endif // CGAL_RAYH2_H
