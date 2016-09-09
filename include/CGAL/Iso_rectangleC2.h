// Source: Iso_rectangleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_ISO_RECTANGLEC2_H
#define CGAL_ISO_RECTANGLEC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointC2.h>

template <class FT>
class CGAL_Iso_rectangleC2 : public CGAL_Handle_base
{
public:
                       CGAL_Iso_rectangleC2();
                       CGAL_Iso_rectangleC2(const CGAL_Iso_rectangleC2<FT> &);
                       CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                            const CGAL_PointC2<FT> &q);
                       ~CGAL_Iso_rectangleC2();

  CGAL_Iso_rectangleC2<FT>  &operator=(const CGAL_Iso_rectangleC2<FT> &r);

  bool                 operator==(const CGAL_Iso_rectangleC2<FT> &s) const;
  bool                 operator!=(const CGAL_Iso_rectangleC2<FT> &s) const;
  bool                 identical(const CGAL_Iso_rectangleC2<FT> &s) const;

  CGAL_PointC2<FT>     min() const;
  CGAL_PointC2<FT>     max() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  CGAL_Iso_rectangleC2<FT> transform(
                               const CGAL_Aff_transformationC2<FT> &t) const;

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


#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const;
};


#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_Iso_rectangleC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(
                                      const CGAL_Iso_rectangleC2<FT> &r) :
  CGAL_Handle_base((CGAL_Handle_base&)r)
{
  CGAL_kernel_precondition( r.is_defined() );
}

template < class FT >
CGAL_Iso_rectangleC2<FT>::CGAL_Iso_rectangleC2(const CGAL_PointC2<FT> &p,
                                               const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
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
  CGAL_nondegeneracy_assertion;
}


template < class FT >
inline CGAL_Iso_rectangleC2<FT>::~CGAL_Iso_rectangleC2()
{}


template < class FT >
CGAL_Iso_rectangleC2<FT> &CGAL_Iso_rectangleC2<FT>::operator=(
                                            const CGAL_Iso_rectangleC2<FT> &r)
{
  CGAL_kernel_precondition( r.is_defined() );
  CGAL_Handle_base::operator=(r);
  return *this;
}
template < class FT >
bool CGAL_Iso_rectangleC2<FT>::operator==(
                                  const CGAL_Iso_rectangleC2<FT> &r) const
{
  CGAL_kernel_precondition( is_defined() && r.is_defined() );
  return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::operator!=(
                                  const CGAL_Iso_rectangleC2<FT> &r) const
{
  CGAL_kernel_precondition( is_defined() && r.is_defined() );
  return !(*this == r);
}

template < class FT >
bool CGAL_Iso_rectangleC2<FT>::identical(
                                  const CGAL_Iso_rectangleC2<FT> &r) const
{
  CGAL_kernel_precondition( is_defined() && r.is_defined() );
  return (PTR == r.PTR);
}
template < class FT >
CGAL_PointC2<FT>  CGAL_Iso_rectangleC2<FT>::min() const
{
  CGAL_kernel_precondition( is_defined() );
  return  ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::max() const
{
  CGAL_kernel_precondition( is_defined() );
  return  ptr()->e1;
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmin() const
{
  CGAL_kernel_precondition( is_defined() );
  return  min().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymin() const
{
  CGAL_kernel_precondition( is_defined() );
  return  min().y();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::xmax() const
{
  CGAL_kernel_precondition( is_defined() );
  return  max().x();
}

template < class FT >
inline FT CGAL_Iso_rectangleC2<FT>::ymax() const
{
  CGAL_kernel_precondition( is_defined() );
  return  max().y();
}



template < class FT >
CGAL_PointC2<FT> CGAL_Iso_rectangleC2<FT>::vertex(int i) const
{
  CGAL_kernel_precondition( is_defined() );
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
  CGAL_kernel_precondition( is_defined() );
  return vertex(i);
}
template < class FT >
CGAL_Side CGAL_Iso_rectangleC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
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
  CGAL_kernel_precondition( is_defined() && p.is_defined());
  return where_is(p) == CGAL_ON;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_inside(
                                             const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined());
  return where_is(p) == CGAL_INSIDE;
}

template < class FT >
inline bool CGAL_Iso_rectangleC2<FT>::is_outside(
                                             const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined());
  return where_is(p) == CGAL_OUTSIDE;
}

template < class FT >
bool CGAL_Iso_rectangleC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return (xmin() == xmax()) || (ymin() ==ymax());
}
template < class FT >
inline CGAL_Bbox_2 CGAL_Iso_rectangleC2<FT>::bbox() const
{
  CGAL_kernel_precondition( is_defined() );
  return CGAL_Bbox_2(CGAL_to_double(xmin()), CGAL_to_double(ymin()),
                     CGAL_to_double(xmax()), CGAL_to_double(ymax()));
}

template < class FT >
inline CGAL_Iso_rectangleC2<FT> CGAL_Iso_rectangleC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return CGAL_Iso_rectangleC2<FT>(t.transform(vertex(0)),
                                  t.transform(vertex(2)));
}


#endif
