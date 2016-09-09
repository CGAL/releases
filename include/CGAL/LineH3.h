// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : LineH3.fw
// file          : include/CGAL/LineH3.h
// package       : H3 (1.5)
// revision      : 1.5
// revision_date : 15 Dec 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_LINEH3_H
#define CGAL_LINEH3_H

#ifndef CGAL_PVDH3_H
#include <CGAL/PVDH3.h>
#endif // CGAL_PVDH3_H
#ifndef CGAL_SEGMENTH3_H
#include <CGAL/SegmentH3.h>
#endif // CGAL_SEGMENTH3_H
#ifndef CGAL_RAYH3_H
#include <CGAL/RayH3.h>
#endif // CGAL_RAYH3_H
#ifndef PREDICATES_ON_POINTSH3_H
#include <CGAL/predicates_on_pointsH3.h>
#endif // PREDICATES_ON_POINTSH3_H

template < class FT, class RT >
class CGAL__Line_repH3 : public CGAL_Rep
{
public:
  CGAL__Line_repH3() {}
  CGAL__Line_repH3( const CGAL_PointH3<FT,RT>& p,
                    const CGAL_DirectionH3<FT,RT> d)
  {
      basepoint = p;
      direction = d;
  }
  ~CGAL__Line_repH3() {}

friend class CGAL_LineH3<FT,RT>;

private:
    CGAL_PointH3<FT,RT>       basepoint;
    CGAL_DirectionH3<FT,RT>   direction;
};


template < class FT, class RT >
class CGAL_LineH3 : public CGAL_Handle
{
public:
  CGAL_LineH3();
  CGAL_LineH3(const CGAL_LineH3<FT,RT> & tbc);
  CGAL_LineH3(const CGAL_PointH3<FT,RT>& p,
              const CGAL_PointH3<FT,RT>& q);
  CGAL_LineH3(const CGAL_SegmentH3<FT,RT>& s);
  CGAL_LineH3(const CGAL_RayH3<FT,RT>& r);
  CGAL_LineH3(const CGAL_PointH3<FT,RT>& p,
              const CGAL_DirectionH3<FT,RT>& d);
  ~CGAL_LineH3();

  CGAL_LineH3<FT,RT>&  operator=(const CGAL_LineH3<FT,RT> & l);

  CGAL_PlaneH3<FT,RT>
                   perpendicular_plane(const CGAL_PointH3<FT,RT>& p) const;
  CGAL_LineH3<FT,RT>   opposite() const;
  CGAL_PointH3<FT,RT>  point() const;
  CGAL_PointH3<FT,RT>  point(int i) const;

  CGAL_PointH3<FT,RT>  projection(const CGAL_PointH3<FT,RT>& p) const;

  CGAL_DirectionH3<FT,RT>
                       direction() const;

  bool                 has_on( const CGAL_PointH3<FT,RT>& p ) const;
  bool                 is_degenerate() const;

  bool                 operator==(const CGAL_LineH3<FT,RT>& l) const ;
  bool                 operator!=(const CGAL_LineH3<FT,RT>& l) const ;
  bool                 identical(const CGAL_LineH3<FT,RT>& l)  const ;
  int                  id() const;

  CGAL_LineH3<FT,RT>
                   transform(const CGAL_Aff_transformationH3<FT,RT>&) const;

protected:
  CGAL__Line_repH3<FT,RT>*  ptr() const;
};

template < class FT, class RT >
inline
bool
CGAL_LineH3<FT,RT>::operator!=(const CGAL_LineH3<FT,RT>& l) const
{ return !(*this == l); }
template < class FT, class RT >
inline
CGAL__Line_repH3<FT,RT>*
CGAL_LineH3<FT,RT>::ptr() const
{ return (CGAL__Line_repH3<FT,RT>*)PTR; }


#ifndef CGAL_PLANEH3_H
#include <CGAL/PlaneH3.h>
#endif // CGAL_PLANEH3_H

template < class FT, class RT >
inline
CGAL_LineH3<FT,RT>::~CGAL_LineH3()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3()
{ PTR = new CGAL__Line_repH3<FT,RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3(const CGAL_LineH3<FT,RT>& tbc)
  : CGAL_Handle(tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3(const CGAL_PointH3<FT,RT>& p,
                                const CGAL_PointH3<FT,RT>& q)
{ PTR = new CGAL__Line_repH3<FT,RT> ( p, (q - p).direction() ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3(const CGAL_SegmentH3<FT,RT>& s)
{ PTR = new CGAL__Line_repH3<FT,RT> ( s.start(), s.direction() ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3(const CGAL_RayH3<FT,RT>& r)
{ PTR = new CGAL__Line_repH3<FT,RT> ( r.start(), r.direction() ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_LineH3<FT,RT>::CGAL_LineH3(const CGAL_PointH3<FT,RT>& p,
                                const CGAL_DirectionH3<FT,RT>& d)
{ PTR = new CGAL__Line_repH3<FT,RT> ( p, d ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_LineH3<FT,RT>&
CGAL_LineH3<FT,RT>::operator=(const CGAL_LineH3<FT,RT>& l)
{
  CGAL_Handle::operator=( (CGAL_Handle&)l );
  return *this;
}
template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_LineH3<FT,RT>::point() const
{ return ptr()->basepoint; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL_LineH3<FT,RT>::point(int i) const
{ return point() + RT(i)*direction().vector() ; }

template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_LineH3<FT,RT>::direction() const
{ return ptr()->direction; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PlaneH3<FT,RT>
CGAL_LineH3<FT,RT>::
perpendicular_plane(const CGAL_PointH3<FT,RT>& p ) const
{ return CGAL_PlaneH3<FT,RT>( p, direction() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_LineH3<FT,RT>
CGAL_LineH3<FT,RT>::opposite() const
{ return CGAL_LineH3<FT,RT>( ptr()->basepoint, -(ptr()->direction ) ); }

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
CGAL_PointH3<FT,RT>
CGAL_LineH3<FT,RT>::projection(const CGAL_PointH3<FT,RT>& p) const
{
  if ( has_on(p) )
  {
      return p;
  }
  CGAL_VectorH3<FT,RT>  v = p - point();
  const RT  vx = v.hx();
  const RT  vy = v.hy();
  const RT  vz = v.hz();
  const RT  vw = v.hw();
  CGAL_VectorH3<FT,RT> dir = direction().vector();
  const RT  dx = dir.hx();
  const RT  dy = dir.hy();
  const RT  dz = dir.hz();
  const RT  dw = dir.hw();

  RT lambda_num = (vx*dx + vy*dy + vz*dz)*dw; // *dw
  RT lambda_den = (dx*dx + dy*dy + dz*dz)*vw; // *dw

  return point() + ( (lambda_num * dir)/lambda_den );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_LineH3<FT,RT>
CGAL_LineH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>& t) const
{ return CGAL_LineH3<FT,RT>(t.transform(point() ), t.transform(direction() )); }


#ifndef CGAL_NO_OSTREAM_INSERT_LINEH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_LineH3<FT,RT> &l)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << l.point() << ' ' << l.direction();
    case CGAL_IO::BINARY :
        return os << l.point() <<  l.direction();
    default:
        return  os << "LineH3(" << l.point() << ", " << l.direction() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_LINEH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINEH3
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_LineH3<FT,RT> &l)
{
  CGAL_PointH3<FT,RT> p;
  CGAL_DirectionH3<FT,RT> d;
  is >> p >> d;
  l = CGAL_LineH3<FT,RT>(p, d);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINEH3
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_LineH3<FT,RT>::has_on( const CGAL_PointH3<FT,RT>& p ) const
{ return CGAL_collinear(point(), point()+direction().vector(), p); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_LineH3<FT,RT>::is_degenerate() const
{ return direction().is_degenerate(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_LineH3<FT,RT>::operator==(const CGAL_LineH3<FT,RT>& l) const
{
  return  (  (l.direction() ==   ptr()->direction )
           &&(l.has_on( ptr()->basepoint ) ) );
}

template < class FT, class RT >
inline
bool
CGAL_LineH3<FT,RT>::identical(const CGAL_LineH3<FT,RT>& l) const
{ return PTR == l.PTR; }

template < class FT, class RT >
inline
int
CGAL_LineH3<FT,RT>::id() const
{ return (int)PTR; }


#endif // CGAL_LINEH3_H
