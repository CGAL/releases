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


// Source: LineH2.h
// Author: Stefan Schirra

#ifndef CGAL_LINEH2_H
#define CGAL_LINEH2_H

#include <CGAL/PointH2.h>




template < class FT, class RT >
class CGAL_LineH2 : public CGAL_Handle
{

public:
                        CGAL_LineH2();
                        CGAL_LineH2(const CGAL_LineH2<FT,RT>& l);
                        CGAL_LineH2(const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q);
                        CGAL_LineH2(const RT& a, const RT& b, const RT& c);
                        CGAL_LineH2(const CGAL_SegmentH2<FT,RT>& s);
                        CGAL_LineH2(const CGAL_RayH2<FT,RT>& r);
                        CGAL_LineH2(const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_DirectionH2<FT,RT>& d);

    CGAL_LineH2<FT,RT>& operator=(const CGAL_LineH2<FT,RT>& l);

    bool                operator==(const CGAL_LineH2<FT,RT>& l) const ;
    bool                operator!=(const CGAL_LineH2<FT,RT>& l) const ;
    bool                identical(const CGAL_LineH2<FT,RT>& l)  const ;
    int                 id()  const ;

    RT                  a() const;
    RT                  b() const;
    RT                  c() const;

    FT                  x_at_y(FT y) const;
    FT                  y_at_x(FT x) const;

    CGAL_LineH2<FT,RT>  perpendicular(const CGAL_PointH2<FT,RT>& p ) const;
    CGAL_LineH2<FT,RT>  opposite() const;
    CGAL_PointH2<FT,RT> point() const;
    CGAL_PointH2<FT,RT> point(int i) const;
    CGAL_PointH2<FT,RT> projection(const CGAL_PointH2<FT,RT>& p) const;
    CGAL_DirectionH2<FT,RT>
                        direction() const;
    CGAL_Oriented_side  oriented_side( const CGAL_PointH2<FT,RT>& p ) const;
    bool                has_on( const CGAL_PointH2<FT,RT>& p ) const;
    bool                has_on_boundary( const CGAL_PointH2<FT,RT>& p ) const;
    bool                has_on_positive_side( const CGAL_PointH2<FT,RT>& p )
                                                                         const;
    bool                has_on_negative_side( const CGAL_PointH2<FT,RT>& p )
                                                                         const;
    bool                is_horizontal() const;
    bool                is_vertical()   const;
    bool                is_degenerate() const;

    CGAL_LineH2<FT,RT>  transform(const CGAL_Aff_transformationH2<FT,RT>&)
                                                         const;

protected:

    CGAL__Threetuple<RT>*  ptr() const;
};



template < class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_LineH2<FT,RT>::ptr() const
{
 return (CGAL__Threetuple<RT>*)PTR;
}




template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2()
{
 PTR = new CGAL__Threetuple<RT>();
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const CGAL_LineH2<FT,RT>& l) :
 CGAL_Handle(l)
{
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const CGAL_PointH2<FT,RT>& p,
                                const CGAL_PointH2<FT,RT>& q)
{
 //  a() * X + b() * Y + c() * W() == 0
 //      |    X        Y       W     |
 //      |  p.hx()   p.hy()  p.hw()  |
 //      |  q.hx()   q.hy()  q.hw()  |

 PTR = new CGAL__Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );

}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const RT& a, const RT& b, const RT& c)
{
 PTR = new CGAL__Threetuple<RT>(a,b,c);
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const CGAL_SegmentH2<FT,RT>& s)
{
 CGAL_PointH2<FT,RT> p = s.start();
 CGAL_PointH2<FT,RT> q = s.end();
 PTR = new CGAL__Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const CGAL_RayH2<FT,RT>& r)
{
 CGAL_PointH2<FT,RT> p = r.start();
 CGAL_PointH2<FT,RT> q = r.second_point();
 PTR = new CGAL__Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>::CGAL_LineH2(const CGAL_PointH2<FT,RT>& p,
                                const CGAL_DirectionH2<FT,RT>& d)
{
 CGAL_PointH2<FT,RT> q = p + CGAL_VectorH2<FT,RT>(d);
 PTR = new CGAL__Threetuple<RT> (
            p.hy()*q.hw() - p.hw()*q.hy(),
            p.hw()*q.hx() - p.hx()*q.hw(),
            p.hx()*q.hy() - p.hy()*q.hx() );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>&
CGAL_LineH2<FT,RT>::operator=(const CGAL_LineH2<FT,RT>& l)
{
 CGAL_Handle::operator=(l);
 return *this;
}


template < class FT, class RT >
RT
CGAL_LineH2<FT,RT>::a() const
{
 return ptr()->e0;
}

template < class FT, class RT >
RT
CGAL_LineH2<FT,RT>::b() const
{
 return ptr()->e1;
}

template < class FT, class RT >
RT
CGAL_LineH2<FT,RT>::c() const
{
 return ptr()->e2;
}


template < class FT, class RT >
FT
CGAL_LineH2<FT,RT>::x_at_y(FT y) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return (FT(-b())*y - FT(c()) )/FT(a());
}

template < class FT, class RT >
FT
CGAL_LineH2<FT,RT>::y_at_x(FT x) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return (FT(-a())*x - FT(c()) )/FT(b());
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_LineH2<FT,RT>::perpendicular(const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_LineH2<FT,RT>( -b()*p.hw(), a()*p.hw(), b()*p.hx() - a()*p.hy() );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_LineH2<FT,RT>::opposite() const
{
 return CGAL_LineH2<FT,RT>( -a(), -b(), -c() );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_LineH2<FT,RT>::point() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 if (is_vertical() )
 {
    return CGAL_PointH2<FT,RT>(-c(), RT(0)  , a() );
 }
 else
 {
    return CGAL_PointH2<FT,RT>(RT(0)  , -c(), b() );
 }
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_LineH2<FT,RT>::point(int i) const
{
 return point() + i*direction().vector();
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_LineH2<FT,RT>::projection(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 CGAL_LineH2<FT,RT>  l( p, CGAL_DirectionH2<FT,RT>( a(), b() ));
 return CGAL_PointH2<FT,RT>( b()*l.c() - l.b()*c(),
                             l.a()*c() - a()*l.c(),
                             a()*l.b() - l.a()*b() );
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_LineH2<FT,RT>::direction() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_DirectionH2<FT,RT>( b(), -a() );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_LineH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 CGAL_PointH2<FT,RT> p = point() + direction().vector();
 return CGAL_LineH2<FT,RT>( t.transform(point() ), t.transform(p) );
}


#ifndef CGAL_NO_OSTREAM_INSERT_LINEH2
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_LineH2<FT,RT> &l)
{

    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << l.a() << ' ' << l.b() << ' ' << l.c();
    case CGAL_IO::BINARY :
        CGAL_write(os, l.a());
        CGAL_write(os, l.b());
        CGAL_write(os, l.c());
        return os;
    default:
        return os << "LineH2(" << l.a() << ", " << l.b() << ", " << l.c() <<')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_LINEH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_LINEH2
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_LineH2<FT,RT> &p)
{
    RT a, b, c;
    switch(is.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        is >> a >> b >> c;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, a);
        CGAL_read(is, b);
        CGAL_read(is, c);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = CGAL_LineH2<FT,RT>(a, b, c);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_LINEH2


template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::has_on( const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) == RT(0)   );
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::has_on_boundary( const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) == RT(0)   );
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::has_on_positive_side( const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) > RT(0)   );
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::has_on_negative_side( const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return ( ( a()*p.hx() + b()*p.hy() + c()*p.hw() ) < RT(0)   );
}

template < class FT, class RT >
CGAL_Oriented_side
CGAL_LineH2<FT,RT>::oriented_side( const CGAL_PointH2<FT,RT>& p ) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 RT v = a()*p.hx() + b()*p.hy() + c()*p.hw();
 if (v > RT(0)   )
 {
    return CGAL_ON_POSITIVE_SIDE;
 }
 else
 {
    return (v < RT(0)   ) ? CGAL_ON_NEGATIVE_SIDE : CGAL_ON_ORIENTED_BOUNDARY;
 }
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::is_horizontal() const
{
 return ( a() == RT(0)   );
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::is_vertical() const
{
 return ( b() == RT(0)   );
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::is_degenerate() const
{
 return (a() == RT(0)  )&&(b() == RT(0)  ) ;
}


template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::operator==(const CGAL_LineH2<FT,RT>& l) const
{
 if (  (a() * l.c() != l.a() * c() )
     ||(b() * l.c() != l.b() * c() ) )
 {
    return false;
 }
 int sc  = CGAL_sign(c() );
 int slc = CGAL_sign(l.c() );
 if ( sc == slc )
 {
    if (sc == 0)
    {
        return (  (a()*l.b() == b()*l.a() )
                &&(CGAL_sign(a() )== CGAL_sign( l.a() ))
                &&(CGAL_sign(b() )== CGAL_sign( l.b() )) );
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
CGAL_LineH2<FT,RT>::operator!=(const CGAL_LineH2<FT,RT>& l) const
{
 return !(*this == l);
}

template < class FT, class RT >
bool
CGAL_LineH2<FT,RT>::identical(const CGAL_LineH2<FT,RT>& l) const
{
 return PTR == l.PTR;
}

template < class FT, class RT >
int
CGAL_LineH2<FT,RT>::id() const
{
 return (int)PTR;
}


#endif // CGAL_LINEH2_H
