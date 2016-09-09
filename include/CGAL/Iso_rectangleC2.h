// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Iso_rectangleC2.h
// package       : C2 (2.1.4)
// source        : web/Iso_rectangleC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:31 $
// author(s)     : Andreas.Fabri
//                 Herve Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ISO_RECTANGLEC2_H
#define CGAL_ISO_RECTANGLEC2_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif // CGAL_POINTC2_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class Iso_rectangleC2 : public Handle
{
public:
                  Iso_rectangleC2();
                  Iso_rectangleC2(const Iso_rectangleC2<FT> &);
                  Iso_rectangleC2(const PointC2<FT> &p,
                                  const PointC2<FT> &q);
                  ~Iso_rectangleC2();

  Iso_rectangleC2<FT>  &operator=(const Iso_rectangleC2<FT> &r);

  bool            operator==(const Iso_rectangleC2<FT> &s) const;
  bool            operator!=(const Iso_rectangleC2<FT> &s) const;
  int             id() const;

  PointC2<FT>     min() const;
  PointC2<FT>     max() const;
  PointC2<FT>     vertex(int i) const;
  PointC2<FT>     operator[](int i) const;

  Iso_rectangleC2<FT> transform(const Aff_transformationC2<FT> &t) const;

  Bounded_side    bounded_side(const PointC2<FT> &p) const;

  bool            has_on_boundary(const PointC2<FT> &p) const;

  bool            has_on_bounded_side(const PointC2<FT> &p) const;
  bool            has_on_unbounded_side(const PointC2<FT> &p) const;

  bool            is_degenerate() const;

  Bbox_2          bbox() const;

  FT              xmin() const;
  FT              ymin() const;
  FT              xmax() const;
  FT              ymax() const;

private:
  _Twotuple< PointC2<FT> >*   ptr() const;
};

template < class FT >
inline _Twotuple< PointC2<FT> > *Iso_rectangleC2<FT>::ptr() const
{
  return (_Twotuple< PointC2<FT> >*)PTR;
}

template < class FT >
inline
Iso_rectangleC2<FT>::Iso_rectangleC2()
{
  PTR = new _Twotuple< PointC2<FT> >;
}

template < class FT >
inline
Iso_rectangleC2<FT>::Iso_rectangleC2(
                                      const Iso_rectangleC2<FT> &r) :
  Handle((Handle&)r)
{

}

template < class FT >
inline
Iso_rectangleC2<FT>::Iso_rectangleC2(const PointC2<FT> &p,
                                     const PointC2<FT> &q)
{
  FT vx0 = p.x();
  FT vy0 = p.y();
  FT vx1 = q.x();
  FT vy1 = q.y();

  bool b1 = false,
       b2 = false;
  if( (b1 = (vx0 > vx1)) || (b2 = (vy0 > vy1)) ) {
    if (b1 && b2) {
      PTR = new _Twotuple< PointC2<FT> >(q,p);
    } else {
      if (vx0 > vx1){
        FT z = vx1;
        vx1 = vx0;
        vx0 = z;
      }
      if (vy0 > vy1){
        FT z = vy1;
        vy1 = vy0;
        vy0 = z;
      }

      PTR = new _Twotuple< PointC2<FT> >(PointC2<FT>(vx0,vy0),
                                         PointC2<FT>(vx1,vy1));
    }
  }else {
    PTR = new _Twotuple< PointC2<FT> >(p,q);
  }
}


template < class FT >
inline
Iso_rectangleC2<FT>::~Iso_rectangleC2()
{}


template < class FT >
inline
Iso_rectangleC2<FT> &Iso_rectangleC2<FT>::operator=(
                                       const Iso_rectangleC2<FT> &r)
{

  Handle::operator=(r);
  return *this;
}
template < class FT >
inline
bool Iso_rectangleC2<FT>::operator==(const Iso_rectangleC2<FT> &r) const
{
  return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT >
inline
bool Iso_rectangleC2<FT>::operator!=(const Iso_rectangleC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
inline
int Iso_rectangleC2<FT>::id() const
{
  return (int)PTR;
}
template < class FT >
inline
PointC2<FT>  Iso_rectangleC2<FT>::min() const
{

  return  ptr()->e0;
}

template < class FT >
inline
PointC2<FT> Iso_rectangleC2<FT>::max() const
{
  return  ptr()->e1;
}

template < class FT >
inline FT Iso_rectangleC2<FT>::xmin() const
{
  return  min().x();
}

template < class FT >
inline FT Iso_rectangleC2<FT>::ymin() const
{
  return  min().y();
}

template < class FT >
inline FT Iso_rectangleC2<FT>::xmax() const
{
  return  max().x();
}

template < class FT >
inline FT Iso_rectangleC2<FT>::ymax() const
{
  return  max().y();
}



template < class FT >
PointC2<FT> Iso_rectangleC2<FT>::vertex(int i) const
{
  switch (i%4) {
  case 0: return min();
  case 1: return PointC2<FT>(xmax(), ymin());
  case 2: return max();
  default: return PointC2<FT>(xmin(), ymax());
  }
}

template < class FT >
inline PointC2<FT> Iso_rectangleC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side Iso_rectangleC2<FT>::bounded_side(const PointC2<FT> &p) const
{
  bool x_incr = (xmin() < p.x()) &&  (p.x() < xmax()),
       y_incr = (ymin() < p.y()) &&  (p.y() < ymax());
  if( x_incr )
    {
      if( y_incr )
        {
          return ON_BOUNDED_SIDE;
        }
      if( (p.y() == ymin()) || (ymax() == p.y()) )
        {
          return ON_BOUNDARY;
        }
    }
  if( (p.x() == xmin()) || (xmax() == p.x()) )
    {
      if( y_incr || (p.y() == ymin()) || (ymax() == p.y()) )
        {
          return ON_BOUNDARY;
        }
    }

  return ON_UNBOUNDED_SIDE;
}

template < class FT >
inline
bool Iso_rectangleC2<FT>::has_on_boundary(const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_BOUNDARY;
}

template < class FT >
inline bool Iso_rectangleC2<FT>::has_on_bounded_side(
                                   const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_BOUNDED_SIDE;
}

template < class FT >
inline bool Iso_rectangleC2<FT>::has_on_unbounded_side(
                                   const PointC2<FT> &p) const
{
  return bounded_side(p) == ON_UNBOUNDED_SIDE;
}

template < class FT >
bool Iso_rectangleC2<FT>::is_degenerate() const
{
  return (xmin() == xmax()) || (ymin() ==ymax());
}
template < class FT >
inline
Bbox_2 Iso_rectangleC2<FT>::bbox() const
{
  return Bbox_2(CGAL::to_double(xmin()), CGAL::to_double(ymin()),
                CGAL::to_double(xmax()), CGAL::to_double(ymax()));
}

template < class FT >
inline
Iso_rectangleC2<FT> Iso_rectangleC2<FT>::transform(
                                  const Aff_transformationC2<FT> &t) const
{
  return Iso_rectangleC2<FT>(t.transform(vertex(0)),
                             t.transform(vertex(2)));
}


#ifndef CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLEC2
template < class FT >
ostream &operator<<(ostream &os, const Iso_rectangleC2<FT> &r)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << r[0] << ' ' << r[2];
    case IO::BINARY :
        return os << r[0] << r[2];
    default:
        return os << "Iso_rectangleC2(" << r[0] << ", " << r[2] << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLEC2

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLEC2
template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
istream &operator>>(istream &is, Iso_rectangleC2<FT> &r)
{
    PointC2<FT> p, q;

    is >> p >> q;

    r = Iso_rectangleC2<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLEC2



CGAL_END_NAMESPACE

#endif
