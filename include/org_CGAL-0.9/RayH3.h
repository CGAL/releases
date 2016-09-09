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


#ifndef CGAL_RAYH3_H
#define CGAL_RAYH3_H

#include <CGAL/LineH3.h>

template < class FT, class RT >
class CGAL__Ray_repH3 : public CGAL_Rep
{

public:
        CGAL__Ray_repH3()
          {
          }
        CGAL__Ray_repH3(const CGAL_PointH3<FT,RT>& p,
                        const CGAL_DirectionH3<FT,RT>& d)
          {
            startpoint = p;
            direction  = d;
          }
        ~CGAL__Ray_repH3()
          {
          }

 friend class CGAL_RayH3<FT,RT>;

private:

    CGAL_PointH3<FT,RT>      startpoint;
    CGAL_DirectionH3<FT,RT>  direction;
};

template < class FT, class RT >
class CGAL_RayH3 : public CGAL_Handle
{
public:
        CGAL_RayH3();
        CGAL_RayH3( const CGAL_RayH3<FT,RT>& tbc);
        CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                    const CGAL_PointH3<FT,RT>& secondp);
        CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                    const CGAL_DirectionH3<FT,RT>& d);
        ~CGAL_RayH3();

    CGAL_RayH3<FT,RT>&  operator=(const CGAL_RayH3<FT,RT>& r);

    CGAL_PointH3<FT,RT> start() const;
    CGAL_PointH3<FT,RT> source() const;
    CGAL_PointH3<FT,RT> second_point() const;
    CGAL_PointH3<FT,RT> point(int i) const;
    CGAL_DirectionH3<FT,RT>
                        direction() const;
    CGAL_LineH3<FT,RT>  supporting_line() const;
    CGAL_RayH3<FT,RT>   opposite() const;
    CGAL_RayH3<FT,RT>   transform( const CGAL_Aff_transformationH3<FT,RT> & t)
                                                                         const;
    bool                has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                collinear_has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                is_degenerate() const;

    bool                operator==(const CGAL_RayH3<FT,RT>& r) const;
    bool                operator!=(const CGAL_RayH3<FT,RT>& r) const;
    bool                identical( const CGAL_RayH3<FT,RT>& r) const;

protected:

    CGAL__Ray_repH3<FT,RT>*
                        ptr() const;
};

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3()
{
 PTR = new CGAL__Ray_repH3<FT,RT>;
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3(const CGAL_RayH3<FT,RT>& tbc)
 : CGAL_Handle(tbc)
{
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                               const CGAL_PointH3<FT,RT>& secondp)
{
 PTR = new CGAL__Ray_repH3<FT,RT>(sp,(secondp - sp).direction() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                               const CGAL_DirectionH3<FT,RT>& d)
{
 PTR = new CGAL__Ray_repH3<FT,RT>(sp, d );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::~CGAL_RayH3()
{
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>&
CGAL_RayH3<FT,RT>::operator=(const CGAL_RayH3<FT,RT>& r)
{
 CGAL_Handle::operator=(r);
 return *this;
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::source() const
{
 return ptr()->startpoint;
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::start() const
{
 return ptr()->startpoint;
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_RayH3<FT,RT>::direction() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_DirectionH3<FT,RT>( ptr()->direction );
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::second_point() const
{
 return start() + direction().vector();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::point(int i) const
{
 CGAL_kernel_precondition( i >= 0 );
 return start() + RT(i)*(direction().vector() ) ;
}

template < class FT, class RT >
CGAL_LineH3<FT,RT>
CGAL_RayH3<FT,RT>::supporting_line() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_LineH3<FT,RT>(start(), second_point() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>
CGAL_RayH3<FT,RT>::opposite() const
{
 return CGAL_RayH3<FT,RT>( start(), - direction() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>
CGAL_RayH3<FT,RT>::transform( const CGAL_Aff_transformationH3<FT,RT> & t) const
{
 return CGAL_RayH3<FT,RT>(t.transform(start()), t.transform(direction()) );
}


#ifndef CGAL_NO_OSTREAM_INSERT_RAYH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_RayH3<FT,RT> &r)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << r.start() << ' ' << r.direction();
    case CGAL_IO::BINARY :
        return os<< r.start() << r.direction();
    default:
        return os << "RayH3(" << r.start() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT  >
istream &operator>>(istream &is, CGAL_RayH3<FT,RT> &r)
{
    CGAL_PointH3<FT,RT> p;
    CGAL_DirectionH3<FT,RT> d;

    is >> p >> d;
      
    r = CGAL_RayH3<FT,RT>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::has_on(const CGAL_PointH3<FT,RT> p) const
{
 return ( (  p == start() )
        ||(  CGAL_DirectionH3<FT,RT>(p - start()) == direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::collinear_has_on(const CGAL_PointH3<FT,RT> p) const
{
 return has_on(p);
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::is_degenerate() const
{
 return (ptr()->direction).is_degenerate() ;
}
template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::operator==(const CGAL_RayH3<FT,RT>& r) const
{
 return ( (start() == r.start() )&&( direction() == r.direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::operator!=( const CGAL_RayH3<FT,RT>& r) const
{
 return !operator==(r);
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::identical( const CGAL_RayH3<FT,RT>& r) const
{
 return ( PTR == r.PTR );
}
template < class FT, class RT >
CGAL__Ray_repH3<FT,RT>*
CGAL_RayH3<FT,RT>::ptr() const
{
 return (CGAL__Ray_repH3<FT,RT>*)PTR;
}


#endif // CGAL_RAYH3_H
