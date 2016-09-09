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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : TetrahedronH3.fw
// file          : include/CGAL/TetrahedronH3.h
// package       : H3 (1.3.1)
// revision      : 1.3.1
// revision_date : 30 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TETRAHEDRONH3_H
#define CGAL_TETRAHEDRONH3_H

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H
#ifndef CGAL_FOURTUPLE_H
#include <CGAL/Fourtuple.h>
#endif // CGAL_FOURTUPLE_H
#ifndef CGAL_SEGMENTH3_H
#include <CGAL/SegmentH3.h>
#endif // CGAL_SEGMENTH3_H
#ifndef CGAL_ORIENTATION_PREDICATESH3_H
#include <CGAL/orientation_predicatesH3.h>
#endif // CGAL_ORIENTATION_PREDICATESH3_H

template < class FT, class RT >
class CGAL__Tetrahedron_repH3 : public CGAL_Rep
{
public:
  CGAL__Tetrahedron_repH3();
  CGAL__Tetrahedron_repH3(const CGAL_PointH3<FT,RT> &p,
                          const CGAL_PointH3<FT,RT> &q,
                          const CGAL_PointH3<FT,RT> &r,
                          const CGAL_PointH3<FT,RT> &s );
  ~CGAL__Tetrahedron_repH3();

  friend class CGAL_TetrahedronH3<FT,RT>;

private:
    CGAL__Fourtuple< CGAL_PointH3<FT,RT> > container;
    CGAL_Orientation                       ordertype;
};

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Tetrahedron_repH3<FT,RT>::CGAL__Tetrahedron_repH3()
  : ordertype(CGAL_DEGENERATE)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL__Tetrahedron_repH3<FT,RT>::
CGAL__Tetrahedron_repH3(const CGAL_PointH3<FT,RT> &p,
                        const CGAL_PointH3<FT,RT> &q,
                        const CGAL_PointH3<FT,RT> &r,
                        const CGAL_PointH3<FT,RT> &s )
  : container(p,q,r,s), ordertype(CGAL_orientation(p,q,r,s))
{}

template < class FT, class RT >
inline
CGAL__Tetrahedron_repH3<FT,RT>::~CGAL__Tetrahedron_repH3()
{}



template < class FT, class RT >
class CGAL_TetrahedronH3 : public CGAL_Handle
{
public:
  CGAL_TetrahedronH3();
  CGAL_TetrahedronH3(const CGAL_TetrahedronH3<FT,RT> &t);
  CGAL_TetrahedronH3(const CGAL_PointH3<FT,RT> &p,
                     const CGAL_PointH3<FT,RT> &q,
                     const CGAL_PointH3<FT,RT> &r,
                     const CGAL_PointH3<FT,RT> &s);
  ~CGAL_TetrahedronH3();

  CGAL_TetrahedronH3<FT,RT> &
                         operator=(const CGAL_TetrahedronH3<FT,RT> &t);

  CGAL_PointH3<FT,RT>    vertex(int i) const;
  CGAL_PointH3<FT,RT>    operator[](int i) const;

  bool                operator==(const CGAL_TetrahedronH3<FT,RT> &t) const;
  bool                operator!=(const CGAL_TetrahedronH3<FT,RT> &t) const;
  bool                identical(const CGAL_TetrahedronH3<FT,RT> &t) const;
  int                 id() const;

  CGAL_Bbox_3         bbox() const;

  CGAL_TetrahedronH3<FT,RT>
                      transform(const CGAL_Aff_transformationH3<FT,RT> &t)
                                                                        const;
  CGAL_Orientation    orientation() const;

  CGAL_Oriented_side  oriented_side(const CGAL_PointH3<FT,RT> &p) const;
  CGAL_Bounded_side   bounded_side(const CGAL_PointH3<FT,RT> &p) const;

  bool                has_on_boundary(const CGAL_PointH3<FT,RT> &p) const;
  bool                has_on_positive_side(const CGAL_PointH3<FT,RT> &p) const;
  bool                has_on_negative_side(const CGAL_PointH3<FT,RT> &p) const;
  bool                has_on_bounded_side(const CGAL_PointH3<FT,RT> &p) const;
  bool                has_on_unbounded_side(const CGAL_PointH3<FT,RT> &p) const;

  bool                is_degenerate() const;

private:
  CGAL__Tetrahedron_repH3<FT,RT>*   ptr() const;
};


template < class FT, class RT >
inline
CGAL__Tetrahedron_repH3<FT,RT>*
CGAL_TetrahedronH3<FT,RT>::ptr() const
{ return (CGAL__Tetrahedron_repH3<FT,RT>*) PTR; }


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TetrahedronH3<FT,RT>::CGAL_TetrahedronH3()
{ PTR = new CGAL__Tetrahedron_repH3<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TetrahedronH3<FT,RT>::
CGAL_TetrahedronH3(const CGAL_TetrahedronH3<FT,RT> &t)
  : CGAL_Handle( (CGAL_Handle&) t)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TetrahedronH3<FT,RT>::CGAL_TetrahedronH3(const CGAL_PointH3<FT,RT> &p,
                                              const CGAL_PointH3<FT,RT> &q,
                                              const CGAL_PointH3<FT,RT> &r,
                                              const CGAL_PointH3<FT,RT> &s)
{ PTR = new CGAL__Tetrahedron_repH3<FT,RT>(p, q, r, s); }

template < class FT, class RT >
inline
CGAL_TetrahedronH3<FT,RT>::~CGAL_TetrahedronH3()
{}

template < class FT, class RT >
inline
CGAL_TetrahedronH3<FT,RT> &
CGAL_TetrahedronH3<FT,RT>::operator=(const CGAL_TetrahedronH3<FT,RT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_TetrahedronH3<FT,RT>::operator==(const CGAL_TetrahedronH3<FT,RT> &t) const
{
  if ( orientation() != t.orientation() )
  {
     return false;
  }
  int i,k;
  for ( k=0; k < 4; k++)
  {
     for ( i=0; (i < 4) && (vertex(k) != t.vertex(i) ) ; i++)
     {
     }
     if (i==4)
     {
        return false;
     }
  }
  return true;
}

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::identical(const CGAL_TetrahedronH3<FT,RT>& t) const
{ return PTR == t.PTR ; }

template < class FT, class RT >
inline
int
CGAL_TetrahedronH3<FT,RT>::id() const
{ return (int)PTR ; }

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::operator!=(const CGAL_TetrahedronH3<FT,RT> &t) const
{ return !(*this == t); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL_TetrahedronH3<FT,RT>::vertex(int i) const
{
  switch (i%4)
  {
     case 0:  return ptr()->container.e0;
     case 1:  return ptr()->container.e1;
     case 2:  return ptr()->container.e2;
     case 3:  return ptr()->container.e3;
  }
  return CGAL_PointH3<FT,RT>();
}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_TetrahedronH3<FT,RT>::operator[](int i) const
{ return vertex(i); }
template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::
has_on_boundary(const CGAL_PointH3<FT,RT> &p) const
{ return bounded_side(p) == CGAL_ON_BOUNDARY; }

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::
has_on_positive_side(const CGAL_PointH3<FT,RT> &p) const
{ return oriented_side(p) == CGAL_ON_POSITIVE_SIDE; }

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::
has_on_negative_side(const CGAL_PointH3<FT,RT> &p) const
{ return oriented_side(p) == CGAL_ON_NEGATIVE_SIDE; }

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::
has_on_bounded_side(const CGAL_PointH3<FT,RT> &p) const
{ return bounded_side(p) == CGAL_ON_BOUNDED_SIDE; }

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::
has_on_unbounded_side(const CGAL_PointH3<FT,RT> &p) const
{ return bounded_side(p) == CGAL_ON_UNBOUNDED_SIDE; }

template < class FT, class RT >
inline
CGAL_Orientation
CGAL_TetrahedronH3<FT,RT>::orientation() const
{ return ptr()->ordertype; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Oriented_side
CGAL_TetrahedronH3<FT,RT>::oriented_side(const CGAL_PointH3<FT,RT> &p) const
{
  if ( orientation() == CGAL_POSITIVE)
  {
      switch (bounded_side(p) )
      {
        case  CGAL_ON_BOUNDED_SIDE:    return CGAL_ON_POSITIVE_SIDE;
        case  CGAL_ON_BOUNDARY:        return CGAL_ON_ORIENTED_BOUNDARY;
        case  CGAL_ON_UNBOUNDED_SIDE:  return CGAL_ON_NEGATIVE_SIDE;
      }
    }
    else
    {
      switch (bounded_side(p) )
      {
        case  CGAL_ON_UNBOUNDED_SIDE:  return CGAL_ON_POSITIVE_SIDE;
        case  CGAL_ON_BOUNDARY:        return CGAL_ON_ORIENTED_BOUNDARY;
        case  CGAL_ON_BOUNDED_SIDE:    return CGAL_ON_NEGATIVE_SIDE;
      }
  }
  CGAL_kernel_assertion( !is_degenerate() );
  return CGAL_ON_ORIENTED_BOUNDARY;
}

template < class FT, class RT >
CGAL_Bounded_side
CGAL_TetrahedronH3<FT,RT>::
bounded_side(const CGAL_PointH3<FT,RT> &p) const
{
  const RT RT0(0);
  RT alpha;
  RT beta ;
  RT gamma;

  CGAL_VectorH3<FT,RT> v1 = vertex(1)-vertex(0);
  CGAL_VectorH3<FT,RT> v2 = vertex(2)-vertex(0);
  CGAL_VectorH3<FT,RT> v3 = vertex(3)-vertex(0);

  CGAL_VectorH3<FT,RT> vp =   p     - vertex(0);

  // want to solve  alpha*v1 + beta*v2 + gamma*v3 == vp
  // let vi' == vi*vi.hw()
  // we solve alpha'*v1' + beta'*v2' + gamma'*v3' == vp' / vp.hw()
  //          muliplied by vp.hw()
  // then we have  alpha = alpha'*v1.hw() / vp.hw()
  // and           beta  = beta' *v2.hw() / vp.hw()
  // and           gamma = gamma'*v3.hw() / vp.hw()

  RT v1x = v1.hx();
  RT v1y = v1.hy();
  RT v1z = v1.hz();
  RT v2x = v2.hx();
  RT v2y = v2.hy();
  RT v2z = v2.hz();
  RT v3x = v3.hx();
  RT v3y = v3.hy();
  RT v3z = v3.hz();
  RT vpx = vp.hx();
  RT vpy = vp.hy();
  RT vpz = vp.hz();

  alpha = CGAL_det3x3_by_formula( vpx, v2x, v3x,
                                  vpy, v2y, v3y,
                                  vpz, v2z, v3z );
  beta  = CGAL_det3x3_by_formula( v1x, vpx, v3x,
                                  v1y, vpy, v3y,
                                  v1z, vpz, v3z );
  gamma = CGAL_det3x3_by_formula( v1x, v2x, vpx,
                                  v1y, v2y, vpy,
                                  v1z, v2z, vpz );
  RT det= CGAL_det3x3_by_formula( v1x, v2x, v3x,
                                  v1y, v2y, v3y,
                                  v1z, v2z, v3z );

  CGAL_kernel_assertion( det != RT0 );
  if (det < RT0 )
  {
      alpha = - alpha;
      beta  = - beta ;
      gamma = - gamma;
      det   = - det  ;
  }

  bool t1 = ( alpha < RT0 );
  bool t2 = ( beta  < RT0 );
  bool t3 = ( gamma < RT0 );
            // t1 || t2 || t3 == not contained in cone

  RT lhs = alpha*v1.hw() + beta*v2.hw() + gamma*v3.hw();
  RT rhs = det * vp.hw();

  bool t4 = ( lhs > rhs );
            // alpha + beta + gamma > 1 ?
  bool t5 = ( lhs < rhs );
            // alpha + beta + gamma < 1 ?
  bool t6 = ( (alpha > RT0) && (beta > RT0) && (gamma > RT0) );

  if ( t1 || t2 || t3 || t4 )
  {
      return CGAL_ON_UNBOUNDED_SIDE;
  }
  return (t5 && t6) ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_BOUNDARY;
}

template < class FT, class RT >
inline
bool
CGAL_TetrahedronH3<FT,RT>::is_degenerate() const
{ return ( orientation() == CGAL_DEGENERATE); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Bbox_3
CGAL_TetrahedronH3<FT,RT>::bbox() const
{
  return
  vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox() + vertex(3).bbox();
}

template < class FT, class RT >
inline
CGAL_TetrahedronH3<FT,RT>
CGAL_TetrahedronH3<FT,RT>::
transform(const CGAL_Aff_transformationH3<FT,RT> &t) const
{
  return CGAL_TetrahedronH3<FT,RT>(t.transform(vertex(0)),
                                   t.transform(vertex(1)),
                                   t.transform(vertex(2)),
                                   t.transform(vertex(3)));
}


#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRONH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_TetrahedronH3<FT,RT> &t)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2] << ' ' << t[3];
    case CGAL_IO::BINARY :
        return os << t[0]  << t[1]  << t[2] << t[3];
    default:
        os << "TetrahedronH3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] ;
        os <<  ", " << t[3] << ")";
        return os;
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRONH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONH3
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_TetrahedronH3<FT,RT> &t)
{
  CGAL_PointH3<FT,RT> p, q, r, s;
  is >> p >> q >> r >> s;
  t = CGAL_TetrahedronH3<FT,RT>(p, q, r, s);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONH3


#endif // CGAL_TETRAHEDRONH3_H
