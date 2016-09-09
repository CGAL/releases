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


// Source:RayC2.h
// Author: Andreas.Fabri

#ifndef CGAL_RAYC2_H
#define CGAL_RAYC2_H

#include<CGAL/PointC2.h>

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_RayC2 : public CGAL_Handle
{
public:
                       CGAL_RayC2();
                       CGAL_RayC2(const CGAL_RayC2<FT> &r);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_PointC2<FT> &secondp);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_DirectionC2<FT> &d);
                       ~CGAL_RayC2();



  CGAL_RayC2<FT>       &operator=(const CGAL_RayC2<FT> &r);

  bool                 operator==(const CGAL_RayC2<FT> &r) const;
  bool                 operator!=(const CGAL_RayC2<FT> &r) const;
  int                  id() const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     source() const;
  CGAL_PointC2<FT>     point(int i) const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_RayC2<FT>       opposite() const;

  CGAL_RayC2<FT>       transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;
  bool                 has_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC2<FT> &p) const;

  CGAL_PointC2<FT>     second_point() const;
private:

CGAL__Twotuple< CGAL_PointC2<FT> > *ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
};


/*
template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_RayC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
*/


template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_RayC2<FT>  &r) :
  CGAL_Handle((CGAL_Handle&)r)
{}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_PointC2<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, secondp);
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_DirectionC2<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, sp + d.vector());
}

template < class FT >
CGAL_RayC2<FT>::~CGAL_RayC2()
{}


template < class FT >
CGAL_RayC2<FT> &CGAL_RayC2<FT>::operator=(const CGAL_RayC2<FT> &r)
{

  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT >
bool CGAL_RayC2<FT>::operator==(const CGAL_RayC2<FT> &r) const
{
  return ((source() == r.source()) && (direction() == r.direction()) );
}

template < class FT >
bool CGAL_RayC2<FT>::operator!=(const CGAL_RayC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
int CGAL_RayC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::second_point() const
{

  return ptr()->e1;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  if (i == 0){
    return ptr()->e0;
  }
  if (i == 1){
    return ptr()->e1;
  }
  return source() + FT(i) * (second_point() - source());
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_RayC2<FT>::direction() const
{

  return CGAL_DirectionC2<FT>(  second_point() - source() );
}

template < class FT >
CGAL_LineC2<FT> CGAL_RayC2<FT>::supporting_line() const
{

  return CGAL_LineC2<FT>(*this);
}

template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::opposite() const
{

  return CGAL_RayC2<FT>( source(), - direction() );
}


template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::transform(const
                                     CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_RayC2<FT>(t.transform(source()),
                        t.transform(second_point()));
}


template < class FT >
bool CGAL_RayC2<FT>::is_horizontal() const
{

  return (source().y() ==  second_point().y());
}

template < class FT >
bool CGAL_RayC2<FT>::is_vertical() const
{

  return  (source().x() == second_point().x());
}

template < class FT >
bool CGAL_RayC2<FT>::is_degenerate() const
{

  return (source() == second_point());
}

template < class FT >
bool CGAL_RayC2<FT>::has_on(const CGAL_PointC2<FT> &p) const
{
  return ( p == source()
           || ( CGAL_collinear(source(), p, second_point())
                && ( CGAL_DirectionC2<FT>(p - source()) == direction() )));

}

template < class FT >
bool CGAL_RayC2<FT>::collinear_has_on(const CGAL_PointC2<FT> &p) const
{
    switch(CGAL_compare_x(source(), second_point())){
    case CGAL_SMALLER:
        return CGAL_compare_x(source(), p) != CGAL_LARGER;
    case CGAL_LARGER:
        return CGAL_compare_x(p, source()) != CGAL_LARGER;
    default:
        switch(CGAL_compare_y(source(), second_point())){
        case CGAL_SMALLER:
            return CGAL_compare_y(source(), p) != CGAL_LARGER;
        case CGAL_LARGER:
            return CGAL_compare_y(p, source()) != CGAL_LARGER;
        default:
            return true; // p == source()
        }
    }
}


#ifndef CGAL_NO_OSTREAM_INSERT_RAYC2
template < class FT >
ostream &operator<<(ostream &os, const CGAL_RayC2<FT> &r)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << r.source() << ' ' << r.direction();
    case CGAL_IO::BINARY :
        return os << r.source() << r.direction();
    default:
        return os << "RayC2(" << r.source() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC2
template < class FT >
istream &operator>>(istream &is, CGAL_RayC2<FT> &r)
{
    CGAL_PointC2<FT> p;
    CGAL_DirectionC2<FT> d;

    is >> p >> d;
      
    r = CGAL_RayC2<FT>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC2




#endif
