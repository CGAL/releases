 
// Source: ParabolaC2.h
// Author: Andreas.Fabri@sophia.inria.fr


#ifndef CGAL_PARABOLAC2_H
#define CGAL_PARABOLAC2_H

#include <CGAL/solve.h>
#include <CGAL/SegmentC2.h>
#include <CGAL/Aff_transformationC2.h>

 
template <class FT>
class CGAL__ParabolaC2 : public CGAL_Handle_rep
{
public:
  CGAL_PointC2<FT>  _base;
  CGAL_VectorC2<FT> _vector;
  FT  _curvature;

  CGAL__ParabolaC2()
    {}

  CGAL__ParabolaC2(const CGAL_PointC2<FT> &base,
                   const CGAL_VectorC2<FT> &vector,
                   const FT & curvature) :
    _base(base), _vector(vector), _curvature(curvature)
    {}

  ~CGAL__ParabolaC2()
    {}
};
 


 
template < class FT >
class CGAL_ParabolaC2 : public CGAL_Handle_base
{
public:
                       CGAL_ParabolaC2();
                       CGAL_ParabolaC2(const CGAL_ParabolaC2  &l);

                       CGAL_ParabolaC2(const CGAL_PointC2<FT> &p,
                                       const CGAL_VectorC2<FT> &v,
                                       const FT &c);

                       CGAL_ParabolaC2(const CGAL_LineC2<FT> &l,
                                       const CGAL_PointC2<FT> &p);

                       ~CGAL_ParabolaC2();

  CGAL_ParabolaC2<FT>  &operator=(const CGAL_ParabolaC2<FT> &l);

  bool                 operator==(const CGAL_ParabolaC2<FT> &l) const;
  bool                 operator!=(const CGAL_ParabolaC2<FT> &l) const;
  bool                 identical(const CGAL_ParabolaC2<FT> &l) const;


  CGAL_PointC2<FT>     base() const;
  CGAL_PointC2<FT>     focus() const;
  CGAL_LineC2<FT>      director() const;
  CGAL_VectorC2<FT>    vector() const;
  FT                   curvature() const;

  CGAL_ParabolaC2<FT>  opposite() const;

  int                  lambdas_at_x(const FT &x,
                                    FT &lambda1,
                                    FT &lambda2) const;
  int                  lambdas_at_y(const FT &y,
                                    FT &lambda1,
                                    FT &lambda2) const;
  FT                   x_at_lambda(const FT &lambda) const;
  FT                   y_at_lambda(const FT &lambda) const;

  CGAL_PointC2<FT>     projection(const CGAL_PointC2<FT> &p) const;

  CGAL_PointC2<FT>     projection(const CGAL_PointC2<FT> &p,
                                  FT &lambda) const;

  CGAL_PointC2<FT>     operator()(const FT &lambda) const;

  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 is_degenerate() const;

  /*
  CGAL_ParabolaC2<FT>  transform(const CGAL_Aff_transformationC2<FT> &t) const;
  */

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_CHECK_PRECONDITIONS


  CGAL_DirectionC2<FT> direction() const;
private:

  CGAL__ParabolaC2<FT>* ptr() const;

  void                 new_rep(const CGAL_PointC2<FT> &p,
                               const CGAL_VectorC2<FT> &v,
                               const FT &c);

};
 


 

template < class FT >
inline CGAL__ParabolaC2<FT>* CGAL_ParabolaC2<FT>::ptr() const
{
  return (CGAL__ParabolaC2<FT>*)PTR;
}


template < class FT >
inline void CGAL_ParabolaC2<FT>::new_rep(const CGAL_PointC2<FT> &p,
                                         const CGAL_VectorC2<FT> &v,
                                         const FT &c)
{
  PTR = new CGAL__ParabolaC2<FT> (p, v, c);

  CGAL_nondegeneracy_assertion;
}
 



 
template < class FT >
CGAL_ParabolaC2<FT>::CGAL_ParabolaC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__ParabolaC2<FT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_ParabolaC2<FT>::CGAL_ParabolaC2(const CGAL_ParabolaC2<FT>  &l) :
  CGAL_Handle_base((const CGAL_Handle_base&)l)
{}

template < class FT >
CGAL_ParabolaC2<FT>::CGAL_ParabolaC2(const CGAL_PointC2<FT> &p,
                                     const CGAL_VectorC2<FT> &v,
                                     const FT &c)
{
  new_rep(p, v, c);
}


template < class FT >
CGAL_ParabolaC2<FT>::CGAL_ParabolaC2(const CGAL_LineC2<FT> &l,
                                     const CGAL_PointC2<FT> &p)
{
  CGAL_VectorC2<FT> v = p - l.projection(p);
  CGAL_PointC2<FT> base_point = p - v/FT(2);
  FT d = sqrt(v*v);

  if (l.where_is(p) == CGAL_RIGHT){
    d = -d;
  }

  new_rep(base_point, l.direction().vector(), FT(1)/(FT(2)*d));
}


template < class FT >
CGAL_ParabolaC2<FT>::~CGAL_ParabolaC2()
{}


template < class FT >
CGAL_ParabolaC2<FT> &CGAL_ParabolaC2<FT>::operator=(
                                                  const CGAL_ParabolaC2<FT> &l)
{
  CGAL_kernel_precondition(l.is_defined());
  CGAL_Handle_base::operator=(l);
  return *this;
}
 
template < class FT >
bool CGAL_ParabolaC2<FT>::operator==(const CGAL_ParabolaC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());

  return (base() == p.base()) &&
         (vector().direction() == p.vector().direction()) &&
         (curvature() == p.curvature());
}

template < class FT >
bool CGAL_ParabolaC2<FT>::operator!=(const CGAL_ParabolaC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return !(*this == p);
}

template < class FT >
bool CGAL_ParabolaC2<FT>::identical(const CGAL_ParabolaC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return ( PTR == p.PTR );
}
 

template < class FT >
CGAL_PointC2<FT> CGAL_ParabolaC2<FT>::base() const
{
  CGAL_kernel_precondition( is_defined() );
  return  ptr()->_base;
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_ParabolaC2<FT>::direction() const
{
  CGAL_kernel_precondition( is_defined() );
  return  vector().direction();
}

template < class FT >
CGAL_VectorC2<FT> CGAL_ParabolaC2<FT>::vector() const
{
  CGAL_kernel_precondition( is_defined() );
  return  ptr()->_vector;
}

template < class FT >
FT CGAL_ParabolaC2<FT>::curvature() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->_curvature;
}
 
template < class FT >
CGAL_ParabolaC2<FT>  CGAL_ParabolaC2<FT>::opposite() const
{
  CGAL_kernel_precondition( is_defined() );
  return CGAL_ParabolaC2<FT>(base(),
                             -vector(),
                             -curvature());
}

template < class FT >
CGAL_PointC2<FT> CGAL_ParabolaC2<FT>::focus() const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();

  v = v / sqrt(v*v);
  return base() + (FT(1)/(FT(4)*curvature())) *
                  v.perpendicular(CGAL_COUNTERCLOCKWISE);
}


template < class FT >
CGAL_LineC2<FT> CGAL_ParabolaC2<FT>::director() const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();

  v = v / sqrt(v*v);
  return CGAL_LineC2<FT>(base() + (FT(1)/(FT(4)*curvature()))
                                     * v.perpendicular(CGAL_CLOCKWISE),
                         direction());
}


template < class FT >
int CGAL_ParabolaC2<FT>::lambdas_at_x(const FT &x,
                                      FT &lambda1,
                                      FT &lambda2) const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();
  if(v.y() != FT(0)){
    const FT a = - v.x()/(curvature()*  v.y());
    const FT b = (base().x()-x)/(curvature() * v.y());

    FT s = a*a/4 + b;

    if (s < FT(0)){
      return 0;
    }
    s = sqrt(s);

    lambda1 = -a/FT(2) - s;
    lambda2 = -a/FT(2) + s;
    return 2;
  }else{
    lambda1 = (x - base().x())/v.x();
    lambda2 = lambda1;
  }
  return 1;
}

template < class FT >
int CGAL_ParabolaC2<FT>::lambdas_at_y(const FT &y,
                                      FT &lambda1,
                                      FT &lambda2) const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();
  if(v.x() != FT(0)){
    const FT a = v.y()/(curvature() * v.x());
    const FT b = (base().y() - y)/(curvature() * v.x());

    FT s = a*a/4 + b;

    if (s < FT(0)){
      return 0;
    }
    s = sqrt(s);

    lambda1 = -a/FT(2) - s;
    lambda2 = -a/FT(2) + s;
    return 2;
  }else{
    lambda1 = (y - base().x())/v.y();
    lambda2 = lambda1;
  }
  return 1;
}



template < class FT >
FT CGAL_ParabolaC2<FT>::x_at_lambda(const FT &lambda) const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();
  return base().x() + lambda * (v.x() - lambda*curvature()*v.y());
}

template < class FT >
FT CGAL_ParabolaC2<FT>::y_at_lambda(const FT &lambda) const
{
  CGAL_kernel_precondition( is_defined() );
  CGAL_VectorC2<FT> v = vector();
  return base().y() + lambda * (v.y() + lambda*curvature()*v.x());
}


template < class FT >
CGAL_PointC2<FT> CGAL_ParabolaC2<FT>::operator()(const FT &lambda) const
{
  return CGAL_PointC2<FT>(x_at_lambda(lambda),
                          y_at_lambda(lambda));
}

template < class FT >
CGAL_PointC2<FT> CGAL_ParabolaC2<FT>::projection(const CGAL_PointC2<FT> &p) 
                                                                 const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  CGAL_VectorC2<FT> v = vector();
  CGAL_LineC2<FT> l(base(), direction());
  CGAL_PointC2<FT> lp(l.projection(p));
  FT lambda = (v.x()!=FT(0)) ? (lp.x()-base().x())/v.x()
                             : (lp.y()-base().y())/v.y();
  return lp +  (lambda * lambda * curvature()) * 
               v.perpendicular(CGAL_COUNTERCLOCKWISE);
}

template < class FT >
CGAL_PointC2<FT> CGAL_ParabolaC2<FT>::projection(const CGAL_PointC2<FT> &p,
                                                 FT &lambda) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  CGAL_VectorC2<FT> v = vector();
  CGAL_LineC2<FT> l(base(), direction());
  CGAL_PointC2<FT> lp(l.projection(p));
  
  lambda = (v.x()!=FT(0)) ? (lp.x()-base().x())/v.x()
                          : (lp.y()-base().y())/v.y();

  return lp +  (lambda * lambda * curvature()) * 
               v.perpendicular(CGAL_COUNTERCLOCKWISE);
}

template < class FT >
bool CGAL_ParabolaC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  CGAL_VectorC2<FT> v = vector();
  FT  lambda1, lambda2;
  
  switch (lambdas_at_x(p.x(), lambda1, lambda2)){
  case 0:
    return false;
    break;
  case 1:
    return p.y() == base().y() + lambda1 * (v.y() 
                                            + (p.x()-base().x())*curvature());
    break;
  default:
    return (p.y() == y_at_lambda(lambda1) || p.y() == y_at_lambda(lambda2));
    break;
  }
  return true;
}


template < class FT >
bool CGAL_ParabolaC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return (curvature() == FT(0)) ;
}
/*
template < class FT >
CGAL_ParabolaC2<FT> CGAL_ParabolaC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return CGAL_ParabolaC2<FT>( t.transform(point() ),
                          t.transform(direction() ));
}
*/
 



#endif // CGAL_PARABOLAC2_H
