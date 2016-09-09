/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: PlaneH3.h
// Author: Stefan Schirra

#ifndef CGAL_PLANEH3_H
#define CGAL_PLANEH3_H

#include <CGAL/PointH2.h>
#include <CGAL/PointH3.h>
#include <CGAL/LineH3.h>
#include <CGAL/RayH3.h>
#include <CGAL/SegmentH3.h>



template < class FT, class RT >
class CGAL_PlaneH3 : public CGAL_Handle
{
 public:
                        CGAL_PlaneH3();

                        CGAL_PlaneH3(const CGAL_PlaneH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& ,
                                     const CGAL_PointH3<FT,RT>& ,
                                     const CGAL_PointH3<FT,RT>& );

                        CGAL_PlaneH3(const RT& a, const RT& b,
                                     const RT& c, const RT& d );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& ,
                                     const CGAL_RayH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& ,
                                     const CGAL_LineH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& ,
                                     const CGAL_SegmentH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_LineH3<FT,RT>& ,
                                     const CGAL_PointH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_SegmentH3<FT,RT>& ,
                                     const CGAL_PointH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_RayH3<FT,RT>& ,
                                     const CGAL_PointH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>&,
                                     const CGAL_DirectionH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>&,
                                     const CGAL_VectorH3<FT,RT>& );

                        CGAL_PlaneH3(const CGAL_PointH3<FT,RT>&,
                                     const CGAL_DirectionH3<FT,RT>&,
                                     const CGAL_DirectionH3<FT,RT>& );

                        ~CGAL_PlaneH3();

    CGAL_PlaneH3<FT,RT>&
                        operator=(const CGAL_PlaneH3<FT,RT> & pl);

    RT                  a() const;
    RT                  b() const;
    RT                  c() const;
    RT                  d() const;

    bool                operator==( const CGAL_PlaneH3<FT,RT>& )    const;
    bool                operator!=( const CGAL_PlaneH3<FT,RT>& )    const;
    bool                identical ( const CGAL_PlaneH3<FT,RT>& )    const;
    int                 id() const;

    CGAL_LineH3<FT,RT>  perpendicular_line(const CGAL_PointH3<FT,RT>& ) const;
    CGAL_PlaneH3<FT,RT> opposite() const;  // plane with opposite orientation

    CGAL_PointH3<FT,RT> point() const;     // same point on the plane
    CGAL_DirectionH3<FT,RT>
                        orthogonal_direction() const;
    CGAL_VectorH3<FT,RT>
                        orthogonal_vector() const;

    CGAL_Oriented_side  oriented_side(const CGAL_PointH3<FT,RT> &p) const;
    bool                has_on(const CGAL_PointH3<FT,RT> &p) const;
    bool                has_on(const CGAL_LineH3<FT,RT> &p) const;
    bool                has_on_boundary(const CGAL_PointH3<FT,RT> &p) const;
    bool                has_on_boundary(const CGAL_LineH3<FT,RT> &p) const;
    bool                has_on_positive_side(const CGAL_PointH3<FT,RT>&l) const;
    bool                has_on_negative_side(const CGAL_PointH3<FT,RT>&l) const;

    bool                is_degenerate() const;

    CGAL_PlaneH3<FT,RT> transform(const CGAL_Aff_transformationH3<FT,RT>& )
                                                                         const;


    CGAL_Aff_transformationH3<FT,RT>
                          transform_to_2d() const;
    CGAL_PointH2<FT,RT>   to_2d(const CGAL_PointH3<FT,RT>& )  const;
    CGAL_PointH3<FT,RT>   to_3d(const CGAL_PointH2<FT,RT>& )  const;
    CGAL_VectorH3<FT,RT>  base1() const;
    CGAL_VectorH3<FT,RT>  base2() const;

protected:

    CGAL_PointH3<FT,RT>   point1() const;   // same point different from point()
    CGAL_PointH3<FT,RT>   point2() const;   // same point different from point()
                                            // and point1()

    CGAL__Fourtuple<RT>*  ptr() const;


    void                  new_rep(const CGAL_PointH3<FT,RT> &p,
                                  const CGAL_PointH3<FT,RT> &q,
                                  const CGAL_PointH3<FT,RT> &r);

    void                  new_rep(const RT &a, const RT &b,
                                  const RT &c, const RT &d);
};

//
//  a() * X + b() * Y + c() * Z() + d() * W() == 0
//
//      |    X        Y       Z       W     |
//      |  p.hx()   p.hy()  p.hz()  p.hw()  |
//      |  q.hx()   q.hy()  q.hz()  q.hw()  |
//      |  r.hx()   r.hy()  r.hz()  r.hw()  |
//
//  CGAL__Fourtuple<RT> ( a(), b(), c(), d() )

template < class FT, class RT >
inline
void
CGAL_PlaneH3<FT,RT>::new_rep(const CGAL_PointH3<FT,RT> &p,
                             const CGAL_PointH3<FT,RT> &q,
                             const CGAL_PointH3<FT,RT> &r)
{
 RT phx = p.hx();
 RT phy = p.hy();
 RT phz = p.hz();
 RT phw = p.hw();

 RT qhx = q.hx();
 RT qhy = q.hy();
 RT qhz = q.hz();
 RT qhw = q.hw();

 RT rhx = r.hx();
 RT rhy = r.hy();
 RT rhz = r.hz();
 RT rhw = r.hw();

 PTR = new CGAL__Fourtuple<RT> (
              phy*( qhz*rhw - qhw*rhz )
            - qhy*( phz*rhw - phw*rhz )     // * X
            + rhy*( phz*qhw - phw*qhz ),

            - phx*( qhz*rhw - qhw*rhz )
            + qhx*( phz*rhw - phw*rhz )     // * Y
            - rhx*( phz*qhw - phw*qhz ),

              phx*( qhy*rhw - qhw*rhy )
            - qhx*( phy*rhw - phw*rhy )     // * Z
            + rhx*( phy*qhw - phw*qhy ),

            - phx*( qhy*rhz - qhz*rhy )
            + qhx*( phy*rhz - phz*rhy )     // * W
            - rhx*( phy*qhz - phz*qhy ) );
}

template < class FT, class RT >
inline
void
CGAL_PlaneH3<FT,RT>::new_rep(const RT &a, const RT &b, const RT &c, const RT &d)
{
  PTR = new CGAL__Fourtuple<RT>(a, b, c, d);
}
template < class FT, class RT >
inline
bool
CGAL_PlaneH3<FT,RT>::operator!=(const CGAL_PlaneH3<FT,RT>& l) const
{
 return !(*this == l);
}

template < class FT, class RT >
inline
CGAL__Fourtuple<RT>*
CGAL_PlaneH3<FT,RT>::ptr() const
{
 return (CGAL__Fourtuple<RT>*)PTR;
}


template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3()
{
 PTR = new CGAL__Fourtuple<RT>();
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PlaneH3<FT,RT>& tbc)
 : CGAL_Handle(tbc)
{
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p,
                                  const CGAL_PointH3<FT,RT>& q,
                                  const CGAL_PointH3<FT,RT>& r)
{
 new_rep(p,q,r);
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const RT& a, const RT& b,
                                  const RT& c, const RT& d)
{
 new_rep(a,b,c,d);
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p ,
                                  const CGAL_LineH3<FT,RT>&  l)
{
 new_rep(p, l.point(0), l.point(1) );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p,
                                  const CGAL_SegmentH3<FT,RT>& s)
{
 new_rep(p, s.source(), s.target() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p ,
                                  const CGAL_RayH3<FT,RT>&  r)
{
 new_rep(p, r.start(), r.start() + r.direction().vector() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_LineH3<FT,RT>& l ,
                                  const CGAL_PointH3<FT,RT>& p)
{
 new_rep(l.point(0), p, l.point(1) );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_SegmentH3<FT,RT>& s,
                                  const CGAL_PointH3<FT,RT>& p)
{
 new_rep(s.source(), p, s.target() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_RayH3<FT,RT>&  r,
                                  const CGAL_PointH3<FT,RT>& p)
{
 new_rep(r.start(), p, r.start() + r.direction().vector() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p,
                                  const CGAL_DirectionH3<FT,RT>& d)
{
 CGAL_VectorH3<FT,RT> ov = d.vector();
 new_rep( ov.hx()*p.hw(),
          ov.hy()*p.hw(),
          ov.hz()*p.hw(),
          -(ov.hx()*p.hx() + ov.hy()*p.hy() + ov.hz()*p.hz() ) );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p,
                                  const CGAL_VectorH3<FT,RT>& ov)
{
 new_rep( ov.hx()*p.hw(),
          ov.hy()*p.hw(),
          ov.hz()*p.hw(),
          -(ov.hx()*p.hx() + ov.hy()*p.hy() + ov.hz()*p.hz() ) );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::CGAL_PlaneH3(const CGAL_PointH3<FT,RT>& p,
                                  const CGAL_DirectionH3<FT,RT>& d1,
                                  const CGAL_DirectionH3<FT,RT>& d2)
{
  new_rep( p, p + d1.vector(), p + d2.vector() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>::~CGAL_PlaneH3()
{
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>&
CGAL_PlaneH3<FT,RT>::operator=(const CGAL_PlaneH3<FT,RT>& pl )
{
 CGAL_Handle::operator=((CGAL_Handle&) pl);
 return *this;
}

template < class FT, class RT >
RT
CGAL_PlaneH3<FT,RT>::a() const
{
 return ptr()->e0;
}

template < class FT, class RT >
RT
CGAL_PlaneH3<FT,RT>::b() const
{
 return ptr()->e1;
}

template < class FT, class RT >
RT
CGAL_PlaneH3<FT,RT>::c() const
{
 return ptr()->e2;
}

template < class FT, class RT >
RT
CGAL_PlaneH3<FT,RT>::d() const
{
 return ptr()->e3;
}
template < class FT, class RT >
CGAL_LineH3<FT,RT>
CGAL_PlaneH3<FT,RT>::perpendicular_line(const CGAL_PointH3<FT,RT>& p) const
{
 return CGAL_LineH3<FT,RT>( p, orthogonal_direction() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL_PlaneH3<FT,RT>::opposite() const
{
 return CGAL_PlaneH3<FT,RT>(-a(), -b(), -c(), -d() );
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_PlaneH3<FT,RT>::point() const
{
 const RT RT0(0);
 if ( a() != RT0 )
 {
    return CGAL_PointH3<FT,RT>( -d(), RT0, RT0, a() );
 }
 if ( b() != RT0 )
 {
    return CGAL_PointH3<FT,RT>( RT0, -d(), RT0, b() );
 }
 CGAL_kernel_assertion ( c() != RT0);
 return CGAL_PointH3<FT,RT>( RT0, RT0, -d(), c() );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_PlaneH3<FT,RT>::base1() const
{
 // point():
 // a() != RT0 : CGAL_PointH3<FT,RT>( -d(), RT0, RT0, a() );
 // b() != RT0 : CGAL_PointH3<FT,RT>( RT0, -d(), RT0, b() );
 //            : CGAL_PointH3<FT,RT>( RT0, RT0, -d(), c() );
 // point1():
 // a() != RT0 : CGAL_PointH3<FT,RT>( -b()-d(), a(), RT0, a() );
 // b() != RT0 : CGAL_PointH3<FT,RT>( RT0, -c()-d(), b(), b() );
 //            : CGAL_PointH3<FT,RT>( c(), RT0, -a()-d(), c() );

 const RT RT0(0);
 if ( a() != RT0 )
 {
    return CGAL_VectorH3<FT,RT>( -b(), a(), RT0, a() );
 }
 if ( b() != RT0 )
 {
    return CGAL_VectorH3<FT,RT>( RT0, -c(), b(), b() );
 }
 CGAL_kernel_assertion ( c() != RT(0) );
 return CGAL_VectorH3<FT,RT>( c(), RT0, -a(), c() );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_PlaneH3<FT,RT>::base2() const
{
 return CGAL_cross_product( orthogonal_vector(), base1() );
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_PlaneH3<FT,RT>::point1() const
{
 return point() + base1();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_PlaneH3<FT,RT>::point2() const
{
 return point() + base2();
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_PlaneH3<FT,RT>::orthogonal_direction() const
{
 return CGAL_DirectionH3<FT,RT>(a(), b(), c() );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_PlaneH3<FT,RT>::orthogonal_vector() const
{
 return CGAL_VectorH3<FT,RT>(a(), b(), c() );
}

template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL_PlaneH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>& t) const
{
#ifndef CGAL_NO_PLANE_TRANSFORM_IN_AT
 return t.transform(*this);
#else
 if ( t.is_even() )
 {
     return CGAL_PlaneH3<FT,RT>(
             t.transform(point() ),
             t.transpose().inverse().transform(orthogonal_direction() ));
 }
 else
 {
     return CGAL_PlaneH3<FT,RT>(
             t.transform(point() ),
           - t.transpose().inverse().transform(orthogonal_direction() ));
 }
#endif // CGAL_NO_PLANE_TRANSFORM_IN_AT
}



#ifndef CGAL_NO_OSTREAM_INSERT_PLANE3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_PlaneH3<FT,RT> &p)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << p.a() << ' ' << p.b() <<  ' ' << p.c() << ' ' << p.d();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.a());
        CGAL_write(os, p.b());
        CGAL_write(os, p.c());
        CGAL_write(os, p.d());
        return os;
        default:
            os << "PlaneC3(" << p.a() <<  ", " << p.b() <<   ", ";
            os << p.c() << ", " << p.d() <<")";
            return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_PLANE3

#ifndef CGAL_NO_ISTREAM_EXTRACT_PLANE3
template < class FT, class RT  >
istream &operator>>(istream &is, CGAL_PlaneH3<FT,RT> &p)
{
    RT a, b, c, d;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> a >> b >> c >> d;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, a);
        CGAL_read(is, b);
        CGAL_read(is, c);
        CGAL_read(is, d);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_PlaneH3<FT,RT>(a, b, c, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_PLANE3
template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::is_degenerate() const
{
 RT RT0(0);
 return ( (a() == RT0 ) && (b() == RT0 ) && (c() == RT0 ) );
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on_positive_side( const CGAL_PointH3<FT,RT>& p) const
{
 return (a()*p.hx() + b()*p.hy() + c()*p.hz() + d()*p.hw() > RT(0) );
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on_negative_side( const CGAL_PointH3<FT,RT>& p) const
{
 return (a()*p.hx() + b()*p.hy() + c()*p.hz() + d()*p.hw() < RT(0) );
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on_boundary( const CGAL_PointH3<FT,RT>& p) const
{
 return (a()*p.hx() + b()*p.hy() + c()*p.hz() + d()*p.hw() == RT(0) );
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on( const CGAL_PointH3<FT,RT>& p) const
{
 return has_on_boundary(p);
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on_boundary( const CGAL_LineH3<FT,RT>& l) const
{
 CGAL_PointH3<FT,RT>   p   = l.point();
 CGAL_VectorH3<FT,RT>  ld  = l.direction().vector();
 CGAL_VectorH3<FT,RT>  ov  = orthogonal_vector();

 return (  ( a()*p.hx() + b()*p.hy() + c()*p.hz() + d()*p.hw()   == RT(0) )
         &&( ld.hx()*ov.hx() + ld.hy()*ov.hy() + ld.hz()*ov.hz() == RT(0) ) );
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::has_on( const CGAL_LineH3<FT,RT>& l) const
{
 return has_on_boundary(l);
}

template < class FT, class RT >
CGAL_Oriented_side
CGAL_PlaneH3<FT,RT>::oriented_side( const CGAL_PointH3<FT,RT>& p) const
{
 RT value = a()*p.hx() + b()*p.hy() + c()*p.hz() + d()*p.hw() ;
 if (value > RT(0) )
 {
    return CGAL_ON_POSITIVE_SIDE;
 }
 else
 {
    return
    (value < RT(0) ) ? CGAL_ON_NEGATIVE_SIDE : CGAL_ON_ORIENTED_BOUNDARY;
 }
}


template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::operator==(const CGAL_PlaneH3<FT,RT>& l) const
{
 if (  (a() * l.d() != l.a() * d() )
     ||(b() * l.d() != l.b() * d() )
     ||(c() * l.d() != l.c() * d() ) )
 {
    return false;
 }
 int sd  = CGAL_sign(d() );
 int sld = CGAL_sign(l.d() );
 if ( sd == sld )
 {
    if (sd == 0)
    {
        return (  (a()*l.b() == b()*l.a() )
                &&(a()*l.c() == c()*l.a() )
                &&(b()*l.c() == c()*l.b() )
                &&(CGAL_sign(a() )== CGAL_sign( l.a() ))
                &&(CGAL_sign(b() )== CGAL_sign( l.b() ))
                &&(CGAL_sign(c() )== CGAL_sign( l.c() )) );
    }
    else
    {
        return true;
    }
 }
 else
 {
    return false;
 }
}

template < class FT, class RT >
bool
CGAL_PlaneH3<FT,RT>::identical(const CGAL_PlaneH3<FT,RT>& l) const
{
 return PTR == l.PTR;
}

template < class FT, class RT >
int
CGAL_PlaneH3<FT,RT>::id() const
{
 return (int)PTR ;
}


#include <CGAL/Aff_transformationH3.h>


template < class FT, class RT >
CGAL_Aff_transformationH3<FT,RT>
CGAL_PlaneH3<FT,RT>::transform_to_2d() const
{
 RT  RT0(0);
 RT  RT1(1);
 CGAL_VectorH3<FT,RT> nov = orthogonal_vector();
 CGAL_VectorH3<FT,RT> e1v = point1()-point() ;
 CGAL_VectorH3<FT,RT> e2v = point2()-point() ;
 RT orthohx = nov.hx();
 RT orthohy = nov.hy();
 RT orthohz = nov.hz();
 RT e1phx   = e1v.hx();
 RT e1phy   = e1v.hy();
 RT e1phz   = e1v.hz();
 RT e2phx   = e2v.hx();
 RT e2phy   = e2v.hy();
 RT e2phz   = e2v.hz();


 RT t11 =  -( orthohy*e2phz - orthohz*e2phy );
 RT t12 =   ( orthohx*e2phz - orthohz*e2phx );
 RT t13 =  -( orthohx*e2phy - orthohy*e2phx );

 RT t21 =   ( orthohy*e1phz - orthohz*e1phy );
 RT t22 =  -( orthohx*e1phz - orthohz*e1phx );
 RT t23 =   ( orthohx*e1phy - orthohy*e1phx );

 RT t31 =   ( e1phy*e2phz - e1phz*e2phy );
 RT t32 =  -( e1phx*e2phz - e1phz*e2phx );
 RT t33 =   ( e1phx*e2phy - e1phy*e2phx );

 RT scale = CGAL_det3x3_by_formula( orthohx, orthohy, orthohz,
                                    e1phx,   e1phy,   e1phz,
                                    e2phx,   e2phy,   e2phz );

 CGAL_Aff_transformationH3<FT,RT>
    point_to_origin(CGAL_TRANSLATION,  - ( point() - CGAL_ORIGIN ) );
 CGAL_Aff_transformationH3<FT,RT>
    rotate_and_more( t11,    t12,   t13,   RT0,
                     t21,    t22,   t23,   RT0,
                     t31,    t32,   t33,   RT0,
                                           scale);

 CGAL_PointH3<FT,RT> ortho( orthohx, orthohy, orthohz );
 CGAL_PointH3<FT,RT> e1p( e1phx, e1phy, e1phz );
 CGAL_PointH3<FT,RT> e2p( e2phx, e2phy, e2phz );
 CGAL_kernel_assertion((   ortho.transform(rotate_and_more)
        == CGAL_PointH3<FT,RT>( RT(0.0), RT(0.0), RT(1.0)) ));
 CGAL_kernel_assertion((   e1p.transform(rotate_and_more)
        == CGAL_PointH3<FT,RT>( RT(1.0), RT(0.0), RT(0.0)) ));
 CGAL_kernel_assertion((   e2p.transform(rotate_and_more)
        == CGAL_PointH3<FT,RT>( RT(0.0), RT(1.0), RT(0.0)) ));

 return  rotate_and_more * point_to_origin;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_PlaneH3<FT,RT>::to_2d(const CGAL_PointH3<FT,RT>& p) const
{
 CGAL_PointH3<FT,RT> tp = p.transform( transform_to_2d() );
 return CGAL_PointH2<FT,RT>( tp.hw(), tp.hx(), tp.hy() );
}


template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_PlaneH3<FT,RT>::to_3d(const CGAL_PointH2<FT,RT>& p)  const
{
 CGAL_PointH3<FT,RT> hp(p.hw(), p.hx(), p.hy(), RT(0.0) );
 return hp.transform( transform_to_2d().inverse() );
}


#endif  // CGAL_PLANEH3_H
