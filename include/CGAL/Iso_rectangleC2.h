// Source: Iso_rectangleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ISO_RECTANGLEC2_H
#define CGAL_ISO_RECTANGLEC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointC2.h>

template <class FT>
class CGAL_Iso_rectangleC2 : public handle_base
{
public:
                       CGAL_Iso_rectangleC2();
                       CGAL_Iso_rectangleC2(const CGAL_Iso_rectangleC2<FT> &);
                       CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                            const CGAL_PointC2<FT> &q);
                       ~CGAL_Iso_rectangleC2();
                       operator CGAL_Iso_rectangleC2<double>() const;
  CGAL_Iso_rectangleC2<FT>  &operator=(const CGAL_Iso_rectangleC2<FT> &r);

  bool                 operator==(const CGAL_Iso_rectangleC2<FT> &s) const;
  bool                 operator!=(const CGAL_Iso_rectangleC2<FT> &s) const;
  bool                 identical(const CGAL_Iso_rectangleC2<FT> &s) const;

  CGAL_PointC2<FT>     min() const;
  CGAL_PointC2<FT>     max() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  CGAL_Iso_rectangleC2<FT> transform(const CGAL_Aff_transformation_baseC2<FT> &t) const;

  CGAL_Side            where_is(const CGAL_PointC2<FT> &p) const;
  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 is_inside(const CGAL_PointC2<FT> &p) const;
  bool                 is_outside(const CGAL_PointC2<FT> &p) const;
  bool                 is_degenerate() const;

  CGAL_Bbox_2           bbox() const;

  FT                   xmin() const;
  FT                   ymin() const;
  FT                   xmax() const;
  FT                   ymax() const;
private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_Iso_rectangleC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(const CGAL_Iso_rectangleC2<FT> &r) :
  handle_base(r)
{}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                               const CGAL_PointC2<FT> &q)
{
  FT vx0 = p.x();
  FT vy0 = p.y();
  FT vx1 = q.x();
  FT vy1 = q.y();

  bool b1 = false,
       b2 = false;
  if( (b1 = (vx0 > vx1)) || (b2 = (vy0 > vy1)) ) {
    if (b1 && b2) {
      PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(q,p);
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

      PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(CGAL_PointC2<FT>(vx0,vy0),
                                                       CGAL_PointC2<FT>(vx1,vy1));
    }
  }else {
    PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(p,q);
  }
  assert( ! is_degenerate() );
}


template < class FT >
inline CGAL_Iso_rectangleC2<FT>::~CGAL_Iso_rectangleC2()
{}

template < class FT >
CGAL_Iso_rectangleC2<FT>::operator CGAL_Iso_rectangleC2<double>() const
{
  return CGAL_Iso_rectangleC2<double>(vertex[0], vertex[1]);
}

template < class FT >
CGAL_Iso_rectangleC2<FT> &CGAL_Iso_rectangleC2<FT>::operator=(const CGAL_Iso_rectangleC2<FT> &p)
{
  handle_base::operator=(p);
  return *this;
}
template < class FT >
bool CGAL_Iso_rectangleC2<FT>::operator==(const CGAL_Iso_rectangleC2<FT> &r) const
{
  return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::operator!=(const CGAL_Iso_rectangleC2<FT> &r) const
{
  return !(*this == t);
}

template < class FT >
bool CGAL_Iso_rectangleC2<FT>::identical(const CGAL_Iso_rectangleC2<FT> &r) const
{
  return (PTR == t.PTR);
}
template < class FT >
CGAL_PointC2<FT>  CGAL_Iso_rectangleC2<FT>::min() const
{
  return  ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::max() const
{
  return  ptr()->e1;
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmin() const
{
  return  min().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymin() const
{
  return  min().y();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmax() const
{
  return  max().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymax() const
{
  return  max().y();
}



template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::vertex(int i) const
{
  switch (i%4) {
  case 0: return min();
  case 1: return CGAL_PointC2<FT>(xmax(), ymin());
  case 2: return max();
  default: return CGAL_PointC2<FT>(xmin(), ymax());
  }
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
CGAL_Side CGAL_Iso_rectangleC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{
  bool x_incr = (xmin() < p.x()) &&  (p.x() < xmax()),
       y_incr = (ymin() < p.y()) &&  (p.y() < ymax());
  if( x_incr )
    {
      if( y_incr )
        {
          return CGAL_INSIDE;
        }
      if( (p.y() == ymin()) || (ymax() == p.y()) )
        {
          return CGAL_ON;
        }
    }
  if( (p.x() == xmin()) || (xmax() == p.x()) )
    {
      if( y_incr )
        {
          return CGAL_ON;
        }
    }

  return CGAL_OUTSIDE;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_ON;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_inside(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_INSIDE;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_outside(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_OUTSIDE;
}

template < class FT >
bool CGAL_Iso_rectangleC2<FT>::is_degenerate() const
{
  return (xmin() == xmax()) || (ymin() ==ymax());
}
template < class FT >
inline CGAL_Bbox_2 CGAL_Iso_rectangleC2<FT>::bbox() const
{
  return CGAL_Bbox_2(xmin(),ymin(), xmax(),ymax());
}

template < class FT >
inline CGAL_Iso_rectangleC2<FT> CGAL_Iso_rectangleC2<FT>::transform(const CGAL_Aff_transformation_baseC2<FT> &t) const
{
  return CGAL_Iso_rectangleC2<FT>(t.transform(vertex(0)),
                                  t.transform(vertex(2)));
}



#ifdef CGAL_IO

#include <stream.h>

template < class FT >
ostream &operator<<(ostream &os, CGAL_Iso_rectangleC2<FT> &r)
{
  os << "Iso_rectangleC2(" << r[0] <<  ", " << r[1] << ")";
  return os;
}

#endif


#endif
