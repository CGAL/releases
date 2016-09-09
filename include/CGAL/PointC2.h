 
// Source: PointC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_POINTC2_H
#define CGAL_POINTC2_H

#include <CGAL/Twotuple.h>
#include <CGAL/cartesian.h>

 
template < class FT >
class CGAL_PointC2 : public CGAL_Handle_base
{
#ifdef CGAL_WORKAROUND_001
friend  CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
friend  CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
#else
friend inline CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
friend inline CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                                         const CGAL_VectorC2<FT> &v);
#endif // CGAL_WORKAROUND_001
public:
                   CGAL_PointC2();
                   CGAL_PointC2(const CGAL_Origin &);
                   CGAL_PointC2(const CGAL_PointC2<FT> &p);
                   CGAL_PointC2(const FT &hx, const FT &hy,
                                const FT &hw);
                   CGAL_PointC2(const FT &x, const FT &y);
                   ~CGAL_PointC2();

  CGAL_PointC2<FT> &operator=(const CGAL_PointC2<FT> &p);

  bool             operator==(const CGAL_PointC2<FT> &p) const;
  bool             operator!=(const CGAL_PointC2<FT> &p) const;
  bool             identical(const CGAL_PointC2<FT> &p) const;

  FT               hx() const;
  FT               hy() const;
  FT               hw() const;

  FT               x() const;
  FT               y() const;
  FT               cartesian(int i) const;
  FT               operator[](int i) const;

  FT               homogeneous(int i) const;

  int              dimension() const;
  CGAL_Bbox_2      bbox() const;


  CGAL_PointC2<FT> transform(const CGAL_Aff_transformationC2<FT> &) const;


#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

protected:
                   CGAL_PointC2(const CGAL_VectorC2<FT> &v);

private:
  CGAL__Twotuple<FT>*  ptr() const;
};
 

 
#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_PointC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT >
inline CGAL__Twotuple<FT>* CGAL_PointC2<FT>::ptr() const
{
  return (CGAL__Twotuple<FT>*)PTR;
}
 


#include <CGAL/Origin.h>
#include <CGAL/VectorC2.h>

#include <CGAL/Aff_transformationC2.h>

#include <CGAL/Bbox_2.h>
#include <CGAL/number_utils.h>


 
template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple<FT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_Origin &)
{
  PTR = new CGAL__Twotuple<FT>(FT(0), FT(0));
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_PointC2<FT> &p) :
  CGAL_Handle_base((CGAL_Handle_base&)p)
{
  CGAL_kernel_precondition(p.is_defined());
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const FT &hx, const FT &hy, const FT &hw)
{
  if( hw != FT(1)){
    PTR = new CGAL__Twotuple<FT>(hx/hw, hy/hw);
  }else{
    PTR = new CGAL__Twotuple<FT>(hx, hy);
  }
}

template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const FT &x, const FT &y)
{
    PTR = new CGAL__Twotuple<FT>(x, y);
}

template < class FT >
CGAL_PointC2<FT>::~CGAL_PointC2()
{}


template < class FT >
CGAL_PointC2<FT> &CGAL_PointC2<FT>::operator=(const CGAL_PointC2<FT> &p)
{
  CGAL_kernel_precondition(p.is_defined());
  CGAL_Handle_base::operator=(p);
  return *this;
}
 
template < class FT >
CGAL_PointC2<FT>::CGAL_PointC2(const CGAL_VectorC2<FT> &v) :
  CGAL_Handle_base((CGAL_Handle_base&)v)
{}
 
template < class FT >
bool CGAL_PointC2<FT>::operator==(const CGAL_PointC2<FT>& p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return ((x() == p.x()) && (y() == p.y())) ;
}

template < class FT >
inline bool CGAL_PointC2<FT>::operator!=(const CGAL_PointC2<FT>& p) const
{
  return !(*this == p);
}

template < class FT >
bool CGAL_PointC2<FT>::identical(const CGAL_PointC2<FT>& p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return ( PTR == p.PTR );
}
 

template < class FT >
FT CGAL_PointC2<FT>::x()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC2<FT>::y()  const
{
  CGAL_kernel_precondition(is_defined());
  return  ptr()->e1 ;
}

template < class FT >
FT  CGAL_PointC2<FT>::cartesian(int i) const
{
  CGAL_kernel_precondition((i == 0 || i == 1 ) && is_defined());
  if(i == 0) {
    return x();
  }
  return y();
}

template < class FT >
inline FT  CGAL_PointC2<FT>::operator[](int i) const
{
  return cartesian(i);
}

template < class FT >
int CGAL_PointC2<FT>::dimension() const
{
  CGAL_kernel_precondition(is_defined());
  return 2;
}

template < class FT >
FT CGAL_PointC2<FT>::hx()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
FT CGAL_PointC2<FT>::hy()  const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}

template < class FT >
FT CGAL_PointC2<FT>::hw()  const
{
  CGAL_kernel_precondition(is_defined());
  return FT(1);
}

template < class FT >
FT  CGAL_PointC2<FT>::homogeneous(int i) const
{
  CGAL_kernel_precondition(is_defined() && (i>=0) && (i<=2));
  if (i<2){
    return cartesian(i);
  }
  return FT(1);
}

 
template < class FT >
inline CGAL_PointC2<FT> operator+(const CGAL_PointC2<FT> &p,
                                  const CGAL_VectorC2<FT> &v)
{
  CGAL_kernel_precondition(p.is_defined() && v.is_defined());
  return CGAL_PointC2<FT>(p.x() + v.x(), p.y() + v.y()) ;
}

template < class FT >
inline CGAL_PointC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                  const CGAL_VectorC2<FT> &v)
{
  CGAL_kernel_precondition(p.is_defined() && v.is_defined());
  return CGAL_PointC2<FT>(p.x() - v.x(), p.y() - v.y()) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_PointC2<FT> operator+(const CGAL_Origin &,
                                  const CGAL_VectorC2<FT> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  return CGAL_PointC2<FT>(v) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_PointC2<FT> operator-(const CGAL_Origin &,
                           const CGAL_VectorC2<FT> &v)
{
  CGAL_kernel_precondition(v.is_defined());
  return CGAL_PointC2<FT>(-v) ;
}

template < class FT >
inline CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q)
{
  CGAL_kernel_precondition(p.is_defined() && q.is_defined());
  return CGAL_VectorC2<FT>(p.x() - q.x(), p.y() - q.y()) ;
}

template < class FT >
#ifndef CGAL_WORKAROUND_001
inline
#endif
CGAL_VectorC2<FT> operator-(const CGAL_PointC2<FT> &p,
                            const CGAL_Origin &)
{
  CGAL_kernel_precondition(p.is_defined());
  return CGAL_VectorC2<FT>(p) ;
}

template < class FT >
inline CGAL_VectorC2<FT> operator-(const CGAL_Origin &,
                                   const CGAL_PointC2<FT> &p)
{
  CGAL_kernel_precondition(p.is_defined());
  return CGAL_VectorC2<FT>(-p.x(), -p.y()) ;
}

 

template < class FT >
CGAL_PointC2<FT> CGAL_PointC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition(is_defined() && t.is_defined());
  return t.transform(*this);
}

template < class FT >
CGAL_Bbox_2 CGAL_PointC2<FT>::bbox() const
{
  CGAL_kernel_precondition(is_defined());
  double bx = CGAL_to_double(x());
  double by = CGAL_to_double(y());
  return CGAL_Bbox_2(bx,by, bx,by);
}

 



#endif
