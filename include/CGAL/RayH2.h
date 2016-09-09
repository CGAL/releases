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
// file          : include/CGAL/RayH2.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_RAYH2_H
#define CGAL_RAYH2_H

template < class FT, class RT >
class CGAL__Ray_repH2 : public CGAL_Rep
{
public:
                        CGAL__Ray_repH2();
                        CGAL__Ray_repH2(const CGAL_PointH2<FT,RT>& fp,
                                        const CGAL_PointH2<FT,RT>& sp);
                        ~CGAL__Ray_repH2(){}

    CGAL_PointH2<FT,RT>  start;
    CGAL_PointH2<FT,RT>  second;
};

template < class FT, class RT >
class CGAL_RayH2 : public CGAL_Handle
{
public:
            CGAL_RayH2();
            CGAL_RayH2( const CGAL_RayH2<FT,RT>& r);
            CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                        const CGAL_PointH2<FT,RT>& secondp);
            CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                        const CGAL_DirectionH2<FT,RT>& d);
            ~CGAL_RayH2();

    CGAL_RayH2<FT,RT>&
            operator=(const CGAL_RayH2<FT,RT>& r);

    bool    operator==(const CGAL_RayH2<FT,RT>& r) const;
    bool    operator!=(const CGAL_RayH2<FT,RT>& r) const;
    bool    identical( const CGAL_RayH2<FT,RT>& r) const;
    int     id() const;

    CGAL_PointH2<FT,RT>     start() const;
    CGAL_PointH2<FT,RT>     source() const;
    CGAL_PointH2<FT,RT>     second_point() const;
    CGAL_PointH2<FT,RT>     point(int i) const;
    CGAL_DirectionH2<FT,RT> direction() const;
    CGAL_LineH2<FT,RT>      supporting_line() const;
    CGAL_RayH2<FT,RT>       opposite() const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const CGAL_PointH2<FT,RT> p) const;
    bool    collinear_has_on(const CGAL_PointH2<FT,RT> p) const;
    bool    is_degenerate() const;

    CGAL_RayH2<FT,RT>
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;
protected:

    CGAL__Ray_repH2<FT,RT>*    ptr() const;
};



template < class FT, class RT >
inline
CGAL__Ray_repH2<FT,RT>::CGAL__Ray_repH2()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Ray_repH2<FT,RT>::CGAL__Ray_repH2(const CGAL_PointH2<FT,RT>& fp,
                                        const CGAL_PointH2<FT,RT>& sp)
  : start(fp), second(sp)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_RayH2<FT,RT>::CGAL_RayH2()
{ PTR = new CGAL__Ray_repH2<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_RayH2<FT,RT>::CGAL_RayH2(const CGAL_RayH2<FT,RT>& r)
  : CGAL_Handle(r)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_RayH2<FT,RT>::CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                               const CGAL_PointH2<FT,RT>& secondp)
{ PTR = new CGAL__Ray_repH2<FT,RT>(sp,secondp); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_RayH2<FT,RT>::CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                               const CGAL_DirectionH2<FT,RT>& d)
{ PTR = new CGAL__Ray_repH2<FT,RT>(sp, sp + d.vector()); }

template < class FT, class RT >
inline
CGAL_RayH2<FT,RT>::~CGAL_RayH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_RayH2<FT,RT>&
CGAL_RayH2<FT,RT>::operator=(const CGAL_RayH2<FT,RT>& r)
{
  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::source() const
{ return ptr()->start; }

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::start() const
{ return ptr()->start; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH2<FT,RT>
CGAL_RayH2<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return CGAL_DirectionH2<FT,RT>( ptr()->second - ptr()->start );
}
template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::second_point() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return ptr()->second;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::point(int i) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  CGAL_kernel_precondition( i>= 0 );
  CGAL_VectorH2<FT,RT> v = direction().vector();
  return start() + RT(i) * v;
}

template < class FT, class RT >
inline
CGAL_LineH2<FT,RT>
CGAL_RayH2<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return CGAL_LineH2<FT,RT>(*this);
}

template < class FT, class RT >
inline
CGAL_RayH2<FT,RT>
CGAL_RayH2<FT,RT>::opposite() const
{ return CGAL_RayH2<FT,RT>( ptr()->start, - direction() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_RayH2<FT,RT>
CGAL_RayH2<FT,RT>::
transform(const CGAL_Aff_transformationH2<FT,RT> & t) const
{
  return CGAL_RayH2<FT,RT>(t.transform(ptr()->start),
                           t.transform(ptr()->second) );
}

#ifndef CGAL_NO_OSTREAM_INSERT_RAYH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_RayH2<FT,RT> &r)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << r.source() << ' ' << r.second_point();
    case CGAL_IO::BINARY :
        return os << r.source() << r.second_point();
    default:
        return os << "RayC2(" << r.source() <<  ", " << r.second_point() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_RayH2<FT,RT> &r)
{
  CGAL_PointH2<FT,RT> p, q;
  is >> p >> q;
  r = CGAL_RayH2<FT,RT>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYH2
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_RayH2<FT,RT>::is_horizontal() const
{ return start().hy()*second_point().hw() == second_point().hy()*start().hw(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_RayH2<FT,RT>::is_vertical() const
{ return start().hx()*second_point().hw() == second_point().hx()*start().hw(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_RayH2<FT,RT>::has_on(const CGAL_PointH2<FT,RT> p) const
{
  return ( (  p == start() )
        ||(CGAL_DirectionH2<FT,RT>(p - ptr()->start) == direction() ) );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_RayH2<FT,RT>::is_degenerate() const
{ return ( (ptr()->start == ptr()->second) ); }

template < class FT, class RT >
inline
bool
CGAL_RayH2<FT,RT>::collinear_has_on(const CGAL_PointH2<FT,RT> p) const
{ return has_on(p); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_RayH2<FT,RT>::operator==(const CGAL_RayH2<FT,RT>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class FT, class RT >
inline
bool
CGAL_RayH2<FT,RT>::operator!=( const CGAL_RayH2<FT,RT>& r) const
{ return !(*this == r); }   /* XXX */

template < class FT, class RT >
inline
bool
CGAL_RayH2<FT,RT>::identical( const CGAL_RayH2<FT,RT>& r) const
{ return ( PTR == r.PTR ); }

template < class FT, class RT >
inline
int
CGAL_RayH2<FT,RT>::id() const
{ return (int)PTR; }
template < class FT, class RT >
inline
CGAL__Ray_repH2<FT,RT>*
CGAL_RayH2<FT,RT>::ptr() const
{ return (CGAL__Ray_repH2<FT,RT>*)PTR; }


#endif // CGAL_RAYH2_H
