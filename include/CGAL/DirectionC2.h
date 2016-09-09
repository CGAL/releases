// Source: DirectionC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_DIRECTIONC2_H
#define CGAL_DIRECTIONC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/VectorC2.h>

template < class FT >
class CGAL_DirectionC2 : public handle_base
{
public:
                       CGAL_DirectionC2();
                       CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d);
                       CGAL_DirectionC2(const CGAL_VectorC2<FT> &v);
                       CGAL_DirectionC2(const FT &x, const FT &y, const FT &w = FT(1.0));
                       ~CGAL_DirectionC2();
                       operator CGAL_DirectionC2<double>() const;

  CGAL_DirectionC2<FT> &operator=(const CGAL_DirectionC2<FT> &d);

  bool                 operator==(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator!=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<=(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator>(const CGAL_DirectionC2<FT> &d) const;
  bool                 operator<(const CGAL_DirectionC2<FT> &d) const;
  bool                 counterclockwise_in_between(const CGAL_DirectionC2<FT> &d1,
                                                   const CGAL_DirectionC2<FT> &d2) const;
  bool                 identical(const CGAL_DirectionC2<FT> &d) const;

  CGAL_VectorC2<FT>    vector() const;
  CGAL_DirectionC2<FT> transform(const CGAL_Aff_transformationC2<FT> &t) const;
  CGAL_DirectionC2<FT> operator-() const;
  // public but hidden
  FT                   x() const;
  FT                   y() const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const;
#endif

private:
  CGAL__Twotuple<FT>*   ptr() const;
};


#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_DirectionC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT >
inline CGAL__Twotuple<FT>*   CGAL_DirectionC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}


template < class FT >
CGAL_DirectionC2<FT>::CGAL_DirectionC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple<FT>();
#endif
}

template < class FT >
inline CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_DirectionC2<FT> &d) :
  handle_base(d)
{
  CGAL_kernel_precondition(d.is_defined());
}

template < class FT >
inline CGAL_DirectionC2<FT>::CGAL_DirectionC2(const CGAL_VectorC2<FT> &v) :
  handle_base(v)
{
  CGAL_kernel_precondition(v.is_defined());
}

template < class FT >
CGAL_DirectionC2<FT>::CGAL_DirectionC2(const FT &x, const FT &y, const FT &w)
{
  PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
inline CGAL_DirectionC2<FT>:: ~CGAL_DirectionC2()
{}

template < class FT >
CGAL_DirectionC2<FT>::operator CGAL_DirectionC2<double>() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_DirectionC2<double>(x(), y());
}

template < class FT >
CGAL_DirectionC2<FT> &CGAL_DirectionC2<FT>::operator=(const CGAL_DirectionC2<FT> &d)
{
  CGAL_kernel_precondition(d.is_defined());
  handle_base::operator=(d);
  return *this;
}
template < class FT >
bool  CGAL_DirectionC2<FT>::operator==(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
    return (CGAL_sign(x()) == CGAL_sign(d.x()))
           && (CGAL_sign(y()) == CGAL_sign(d.y()))
           && (y()*d.x() == d.y()*x());
    //return (y()*d.x() == d.y()*x()) && ( (x()/d.x()) > FT(0.0)  || (y()/d.y()) > FT(0.0));
}

template < class FT >
inline bool  CGAL_DirectionC2<FT>::operator!=(const CGAL_DirectionC2<FT> &d) const
{
  return !( *this == d );
}

template < class FT >
bool  CGAL_DirectionC2<FT>::identical(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
  return ( PTR == d.PTR );
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator<(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
  int quadrant_this = (x() >= FT(0.0)) ? ((y() >= FT(0.0))?1:4)
                                        : ((y() >= FT(0.0))?2:3);
  int quadrant_d    = (d.x() >= FT(0.0)) ? ((d.y() >= FT(0.0))?1:4)
                                          : ((d.y() >= FT(0.0))?2:3);

  if(quadrant_this < quadrant_d) {
    return true;
  } else if (quadrant_this > quadrant_d){
    return false;
  }else {
    return y() * d.x() < d.y() * x();
  }
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator>(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
  return d < *this ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator>=(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
  return (d < *this) || (d == *this) ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::operator<=(const CGAL_DirectionC2<FT> &d) const
{
  CGAL_kernel_precondition(is_defined() && d.is_defined());
  return (*this < d) || (d == *this) ;
}

template < class FT >
bool  CGAL_DirectionC2<FT>::counterclockwise_in_between(const CGAL_DirectionC2<FT> &d1,
                                                        const CGAL_DirectionC2<FT> &d2) const
{
  CGAL_kernel_precondition(is_defined() && d1.is_defined() && d2.is_defined());
  return (d2 > *this) && (*this > d1) ;
}
template < class FT >
inline CGAL_VectorC2<FT> CGAL_DirectionC2<FT>::vector() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_VectorC2<FT>(*this);
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::transform(const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition(is_defined());
  return t.transform(*this);
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_DirectionC2<FT>::operator-() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_DirectionC2<FT>(-x(), -y());
}

template < class FT >
FT CGAL_DirectionC2<FT>::x() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_DirectionC2<FT>::y() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}



#ifdef CGAL_IO

#include <stream.h>

template < class FT >
ostream &operator<<(ostream &os, CGAL_DirectionC2<FT> &d)
{
  CGAL_VectorC2<FT> v = d.vector();
  os << "DirectionC2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif


#endif
