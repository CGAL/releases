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
// file          : include/CGAL/RayC3.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_RAYC3_H
#define CGAL_RAYC3_H

#include <CGAL/LineC3.h>

template < class FT >
class CGAL_RayC3 : public CGAL_Handle
{
public:
                       CGAL_RayC3();
                       CGAL_RayC3(const CGAL_RayC3<FT> &r);
                       CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                                const CGAL_PointC3<FT> &secondp);
                       CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                                const CGAL_DirectionC3<FT> &d);
                       ~CGAL_RayC3();

  CGAL_RayC3<FT>       &operator=(const CGAL_RayC3<FT> &r);

  bool                 operator==(const CGAL_RayC3<FT> &r) const;
  bool                 operator!=(const CGAL_RayC3<FT> &r) const;
  int                  id() const;

  CGAL_PointC3<FT>     start() const;
  CGAL_PointC3<FT>     source() const;
  CGAL_PointC3<FT>     second_point() const;
  CGAL_PointC3<FT>     point(int i) const;

  CGAL_DirectionC3<FT> direction() const;
  CGAL_LineC3<FT>      supporting_line() const;
  CGAL_RayC3           opposite() const;

  CGAL_RayC3           transform(const CGAL_Aff_transformationC3<FT> &t) const;

  bool                 is_degenerate() const;
  bool                 has_on(const CGAL_PointC3<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC3<FT> &p) const;

private:
CGAL__Twotuple< CGAL_PointC3<FT> > *ptr() const;
};


template < class FT >
CGAL__Twotuple< CGAL_PointC3<FT> > *CGAL_RayC3<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3()
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >;
}

template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_RayC3<FT>  &r) :
  CGAL_Handle((CGAL_Handle&)r)
{}

template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                           const CGAL_PointC3<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp,secondp);
}


template < class FT >
CGAL_RayC3<FT>::CGAL_RayC3(const CGAL_PointC3<FT> &sp,
                           const CGAL_DirectionC3<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp, sp + d.vector());
}


template < class FT >
inline CGAL_RayC3<FT>::~CGAL_RayC3()
{}


template < class FT >
CGAL_RayC3<FT> &CGAL_RayC3<FT>::operator=(const CGAL_RayC3<FT> &r)
{
  CGAL_Handle::operator=(r);
  return *this;
}
template < class FT >
inline bool CGAL_RayC3<FT>::operator==(const CGAL_RayC3<FT> &r) const
{
  return ((source() == r.source()) && (direction() == r.direction()) );
}


template < class FT >
inline bool CGAL_RayC3<FT>::operator!=(const CGAL_RayC3<FT> &r) const
{
  return !(*this == r);
}


template < class FT >
int CGAL_RayC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::start() const
{
  return ptr()->e0;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::second_point() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_PointC3<FT>  CGAL_RayC3<FT>::point(int i) const
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
inline CGAL_DirectionC3<FT> CGAL_RayC3<FT>::direction() const
{
  return CGAL_DirectionC3<FT>(  second_point() - source() );
}


template < class FT >
inline CGAL_LineC3<FT> CGAL_RayC3<FT>::supporting_line() const
{
  return CGAL_LineC3<FT>(*this);
}


template < class FT >
inline CGAL_RayC3<FT> CGAL_RayC3<FT>::opposite() const
{
  return CGAL_RayC3<FT>( source(), - direction() );
}


template < class FT >
inline CGAL_RayC3<FT> CGAL_RayC3<FT>::transform(
                           const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_RayC3<FT>(t.transform(source()),
                        t.transform(second_point()));
}


template < class FT >
bool CGAL_RayC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  return ( p == source()
           || ( CGAL_collinear(source(), p, second_point())
                && ( CGAL_DirectionC3<FT>(p - source()) == direction() )));
}


template < class FT >
bool CGAL_RayC3<FT>::is_degenerate() const
{
  return (source() == second_point());
}


template < class FT >
inline bool CGAL_RayC3<FT>::collinear_has_on(const CGAL_PointC3<FT> &p) const
{
  CGAL_kernel_exactness_precondition(
        CGAL_collinear(source(), p, second_point()) );

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
            switch(CGAL_compare_z(source(), second_point())){
            case CGAL_SMALLER:
                return CGAL_compare_z(source(), p) != CGAL_LARGER;
            case CGAL_LARGER:
                return CGAL_compare_z(p, source()) != CGAL_LARGER;
            default:
                return true; // p == source()
            }
        }
    }
}


#ifndef CGAL_NO_OSTREAM_INSERT_RAYC3
template < class FT >
ostream &operator<<(ostream &os, const CGAL_RayC3<FT> &r)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << r.start() << ' ' << r.direction();
    case CGAL_IO::BINARY :
        return os<< r.start() << r.direction();
    default:
        return os << "RayC3(" << r.start() <<  ", " << r.direction() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_RAYC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_RAYC3
template < class FT >
istream &operator>>(istream &is, CGAL_RayC3<FT> &r)
{
    CGAL_PointC3<FT> p;
    CGAL_DirectionC3<FT> d;

    is >> p >> d;

    r = CGAL_RayC3<FT>(p, d);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_RAYC3



#endif
