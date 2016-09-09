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


// Source: TetrahedronC3.h
// Author: Andreas Fabri

#ifndef CGAL_TETRAHEDRONC3_H
#define CGAL_TETRAHEDRONC3_H

#include <CGAL/Fourtuple.h>
#include <CGAL/PlaneC3.h>
#include <CGAL/solveC3.h>

template <class FT>
class CGAL_TetrahedronC3 : public CGAL_Handle
{
public:
                      CGAL_TetrahedronC3();
                      CGAL_TetrahedronC3(const CGAL_TetrahedronC3<FT> &t);
                      CGAL_TetrahedronC3(const CGAL_PointC3<FT> &p,
                                         const CGAL_PointC3<FT> &q,
                                         const CGAL_PointC3<FT> &r,
                                         const CGAL_PointC3<FT> &s);
                      ~CGAL_TetrahedronC3();

  CGAL_TetrahedronC3<FT> &operator=(const CGAL_TetrahedronC3<FT> &t);

  CGAL_PointC3<FT>    vertex(int i) const;
  CGAL_PointC3<FT>    operator[](int i) const;

  bool                operator==(const CGAL_TetrahedronC3<FT> &t) const;
  bool                operator!=(const CGAL_TetrahedronC3<FT> &t) const;
  int                 id() const;

  CGAL_Bbox_3         bbox() const;


  CGAL_TetrahedronC3<FT>  
                      transform(const CGAL_Aff_transformationC3<FT> &t) const;

  CGAL_Orientation    orientation() const;
  CGAL_Oriented_side  oriented_side(const CGAL_PointC3<FT> &p) const;
  CGAL_Bounded_side   bounded_side(const CGAL_PointC3<FT> &p) const;

  bool                has_on_boundary(const CGAL_PointC3<FT> &p) const;
  bool                has_on_positive_side(const CGAL_PointC3<FT> &p) const;
  bool                has_on_negative_side(const CGAL_PointC3<FT> &p) const;
  bool                has_on_bounded_side(const CGAL_PointC3<FT> &p) const;
  bool                has_on_unbounded_side(const CGAL_PointC3<FT> &p) const;


  bool                is_degenerate() const;

private:
  CGAL__Fourtuple< CGAL_PointC3<FT> >*   ptr() const;
};


template < class FT >
CGAL__Fourtuple< CGAL_PointC3<FT> >*  CGAL_TetrahedronC3<FT>::ptr() const
{
  return (CGAL__Fourtuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_TetrahedronC3<FT>::CGAL_TetrahedronC3()
{
  PTR = new CGAL__Fourtuple< CGAL_PointC3<FT> >;
}


template < class FT >
CGAL_TetrahedronC3<FT>::CGAL_TetrahedronC3(const CGAL_TetrahedronC3<FT> &t) :
  CGAL_Handle(t)
{}


template < class FT >
CGAL_TetrahedronC3<FT>::CGAL_TetrahedronC3(const CGAL_PointC3<FT> &p,
                                           const CGAL_PointC3<FT> &q,
                                           const CGAL_PointC3<FT> &r,
                                           const CGAL_PointC3<FT> &s)
{
  PTR = new CGAL__Fourtuple< CGAL_PointC3<FT> >(p, q, r, s);
}


template < class FT >
inline CGAL_TetrahedronC3<FT>::~CGAL_TetrahedronC3()
{}


template < class FT >
CGAL_TetrahedronC3<FT> &CGAL_TetrahedronC3<FT>::operator=(
                                             const CGAL_TetrahedronC3<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT >
bool CGAL_TetrahedronC3<FT>::operator==(const CGAL_TetrahedronC3<FT> &t) const
{
  return ( vertex(0)==t.vertex(0) && vertex(1)==t.vertex(1) &&
           vertex(2)==t.vertex(2) && vertex(3)==t.vertex(3) );
}


template < class FT >
inline bool CGAL_TetrahedronC3<FT>::operator!=(
                                      const CGAL_TetrahedronC3<FT> &t) const
{
  return !(*this == t);
}


template < class FT >
int CGAL_TetrahedronC3<FT>::id() const
{
  return (int)PTR ;
}
template < class FT >
CGAL_PointC3<FT> CGAL_TetrahedronC3<FT>::vertex(int i) const
{
  switch (i%4)   // modulo 4 is a logical operation, hence cheap
    {
    case 0: return ptr()->e0;
    case 1: return ptr()->e1;
    case 2: return ptr()->e2;
    default: return ptr()->e3;
    }
}


template < class FT >
inline CGAL_PointC3<FT> CGAL_TetrahedronC3<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline bool CGAL_TetrahedronC3<FT>::has_on_boundary(
                                              const CGAL_PointC3<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_ORIENTED_BOUNDARY;
}


template < class FT >
inline bool CGAL_TetrahedronC3<FT>::has_on_positive_side(
                                              const CGAL_PointC3<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_POSITIVE_SIDE;
}


template < class FT >
inline bool CGAL_TetrahedronC3<FT>::has_on_negative_side(
                                             const CGAL_PointC3<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_NEGATIVE_SIDE;
}


template < class FT >
inline bool CGAL_TetrahedronC3<FT>::has_on_bounded_side(
                                              const CGAL_PointC3<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_BOUNDED_SIDE;
}


template < class FT >
inline bool CGAL_TetrahedronC3<FT>::has_on_unbounded_side(
                                             const CGAL_PointC3<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_UNBOUNDED_SIDE;
}
template < class FT >
CGAL_Orientation CGAL_TetrahedronC3<FT>::orientation() const
{
  return CGAL_orientation(vertex(0), vertex(1), vertex(2), vertex(3));
}
template < class FT >
CGAL_Oriented_side CGAL_TetrahedronC3<FT>::oriented_side(
                                           const CGAL_PointC3<FT> &p) const
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
 assert (!is_degenerate() );
 return CGAL_ON_ORIENTED_BOUNDARY;
}
template < class FT >
CGAL_Bounded_side CGAL_TetrahedronC3<FT>::bounded_side(
                                           const CGAL_PointC3<FT> &p) const
{
  FT alpha, beta, gamma;

  CGAL_solve(vertex(1)-vertex(0), vertex(2)-vertex(0), vertex(3)-vertex(0),
             p - vertex(0), alpha, beta, gamma);
  if ((alpha < FT(0)) || (beta < FT(0)) || (gamma < FT(0)) ||
      (((alpha + beta + gamma) - FT(1)) > FT(0)))
    {
      return CGAL_ON_UNBOUNDED_SIDE;
    }
  if (   (alpha == FT(0)) || (beta == FT(0)) || (gamma == FT(0))
      || (alpha+beta+gamma == FT(1)) )
  {
    return CGAL_ON_BOUNDARY;
  }
  return CGAL_ON_BOUNDED_SIDE;
}
template < class FT >
bool CGAL_TetrahedronC3<FT>::is_degenerate() const
{
  CGAL_PlaneC3<FT> plane(vertex(0), vertex(1), vertex(2));
  return (plane.is_degenerate()) ? true : plane.has_on_boundary(vertex(3));
}


template < class FT >
CGAL_Bbox_3 CGAL_TetrahedronC3<FT>::bbox() const
{

  return vertex(0).bbox() + vertex(1).bbox()
         + vertex(2).bbox() + vertex(3).bbox();
}


template < class FT >
inline CGAL_TetrahedronC3<FT> CGAL_TetrahedronC3<FT>::transform(
                                 const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_TetrahedronC3<FT>(t.transform(vertex(0)),
                                t.transform(vertex(1)),
                                t.transform(vertex(2)),
                                t.transform(vertex(3)));
}

#ifndef CGAL_NO_OSTREAM_INSERT_TETRAHEDRONC3
template < class FT >
ostream &operator<<(ostream &os, const CGAL_TetrahedronC3<FT> &t)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2] << ' ' << t[3];
    case CGAL_IO::BINARY :
        return os << t[0]  << t[1]  << t[2] << t[3];
    default:
        os << "TetrahedronC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] ;
        os <<  ", " << t[3] << ")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_TETRAHEDRONC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONC3
template < class FT >
istream &operator>>(istream &is, CGAL_TetrahedronC3<FT> &t)
{
    CGAL_PointC3<FT> p, q, r, s;

    is >> p >> q >> r >> s;
      
    t = CGAL_TetrahedronC3<FT>(p, q, r, s);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TETRAHEDRONC3



#endif
