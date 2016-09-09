 
// Source: Parabola_arcC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PARABOLA_ARCC2_H
#define CGAL_PARABOLA_ARCC2_H

#include <CGAL/ParabolaC2.h>

 
template <class FT>
class CGAL__Parabola_arcC2 : public CGAL_Handle_rep
{
public:
  CGAL_ParabolaC2<FT>  _par;
  FT  _lambda_start;
  FT  _lambda_end;

  CGAL__Parabola_arcC2()
    {}

  CGAL__Parabola_arcC2(const CGAL_ParabolaC2<FT> &par,
                       const FT &lambda_start,
                       const FT &lambda_end)
    : _par(par), _lambda_start(lambda_start), _lambda_end(lambda_end)
    {}

  ~CGAL__Parabola_arcC2()
    {}
};
 


 
template < class FT >
class CGAL_Parabola_arcC2 : public CGAL_Handle_base
{
public:
                       CGAL_Parabola_arcC2();
                       CGAL_Parabola_arcC2(const CGAL_Parabola_arcC2<FT>  &p);

//                     CGAL_Parabola_arcC2(const CGAL_ParabolaC2<FT> &par,
//                                           const CGAL_PointC2<FT> &p,
//                                           const CGAL_PointC2<FT> &q);
//
                       CGAL_Parabola_arcC2(const CGAL_ParabolaC2<FT> &par,
                                           const FT &lambda1,
                                           const FT &lambda2);

                       ~CGAL_Parabola_arcC2();

  CGAL_Parabola_arcC2<FT>  &operator=(const CGAL_Parabola_arcC2<FT> &l);

  bool                 operator==(const CGAL_Parabola_arcC2<FT> &l) const;
  bool                 operator!=(const CGAL_Parabola_arcC2<FT> &l) const;
  bool                 identical(const CGAL_Parabola_arcC2<FT> &l) const;

  CGAL_ParabolaC2<FT>  supporting_parabola() const;

  FT                   lambda_start() const;
  FT                   lambda_end() const;
  FT                   lambda(int i) const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     end() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 is_degenerate() const;

  CGAL_Parabola_arcC2<FT> opposite() const;
  CGAL_Bbox_2          bbox() const;
  /*
  CGAL_Parabola_arcC2<FT> transform(
                              const CGAL_Aff_transformationC2<FT> &t) const;
  */

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_CHECK_PRECONDITIONS

private:
  CGAL__Parabola_arcC2<FT>* ptr() const;
};
 


 

template < class FT >
inline CGAL__Parabola_arcC2<FT>* CGAL_Parabola_arcC2<FT>::ptr() const
{
  return (CGAL__Parabola_arcC2<FT>*)PTR;
}

 



 
template < class FT >
CGAL_Parabola_arcC2<FT>::CGAL_Parabola_arcC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Parabola_arcC2<FT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_Parabola_arcC2<FT>::CGAL_Parabola_arcC2(const CGAL_Parabola_arcC2<FT>  &l)
  : CGAL_Handle_base((CGAL_Handle_base&)l)
{}

template < class FT >
CGAL_Parabola_arcC2<FT>::CGAL_Parabola_arcC2(const CGAL_ParabolaC2<FT>  &par,
                                             const FT &lambda1,
                                             const FT &lambda2)
{
  PTR = new CGAL__Parabola_arcC2<FT> (par, lambda1, lambda2);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_Parabola_arcC2<FT>::~CGAL_Parabola_arcC2()
{}


template < class FT >
CGAL_Parabola_arcC2<FT> &CGAL_Parabola_arcC2<FT>::operator=(
                                              const CGAL_Parabola_arcC2<FT> &l)
{
  CGAL_kernel_precondition(l.is_defined());
  CGAL_Handle_base::operator=(l);
  return *this;
}
 
template < class FT >
bool CGAL_Parabola_arcC2<FT>::operator==(const CGAL_Parabola_arcC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());

  return (supporting_parabola() == l.supporting_parabola()) &&
         (lambda_start() == l.lambda_start()) &&
         (lambda_end() == l.lambda_end());

}

template < class FT >
bool CGAL_Parabola_arcC2<FT>::operator!=(const CGAL_Parabola_arcC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());
  return !(*this == l);
}

template < class FT >
bool CGAL_Parabola_arcC2<FT>::identical(const CGAL_Parabola_arcC2<FT> &l) const
{
  CGAL_kernel_precondition(is_defined() && l.is_defined());
  return ( PTR == l.PTR );
}
 
template < class FT >
CGAL_ParabolaC2<FT> CGAL_Parabola_arcC2<FT>::supporting_parabola() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->_par;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda_start() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->_lambda_start;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda_end() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->_lambda_end;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda(int i)  const
{
  CGAL_kernel_precondition(is_defined());
 switch (i%2) {
  case 0: return lambda_start();
  case 1: return lambda_end();
  }
  return lambda_start();  // otherwise the SGI compiler complains
}


template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::start() const
{
  CGAL_kernel_precondition(is_defined());
  return supporting_parabola()(lambda_start());
}

template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::end() const
{
  CGAL_kernel_precondition(is_defined());
  return supporting_parabola()(lambda_end());
}


template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::vertex(int i) const
{
  CGAL_kernel_precondition(is_defined());
  switch (i%2) {
  case 0: return start();
  case 1: return end();
  }
  return start();  // otherwise the SGI compiler complains
}

template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::operator[](int i) const
{
  CGAL_kernel_precondition(is_defined());
  return vertex(i);
}
 

template < class FT >
bool CGAL_Parabola_arcC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  CGAL_ParabolaC2<FT> par = supporting_parabola();
  FT lambda1, lambda2;
  switch (par.lambdas_at_x(p.x(), lambda1, lambda2)) {
  case 2:
    return (par.y_at_lambda(lambda1)==p.y()) ||
           (par.y_at_lambda(lambda2)==p.y());
    break;
  case 1:
    return (par.y_at_lambda(lambda1)==p.y());
  }
  return false;
}


template < class FT >
bool CGAL_Parabola_arcC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return (supporting_parabola().curvature() == FT(0)) ;
}

template < class FT >
CGAL_Parabola_arcC2<FT> CGAL_Parabola_arcC2<FT>::opposite() const
{
  return CGAL_Parabola_arcC2<FT>(supporting_parabola().opposite(),
                                 -lambda_end(),
                                 -lambda_start());
}

template < class FT >
CGAL_Bbox_2  CGAL_Parabola_arcC2<FT>::bbox() const
{
  CGAL_kernel_precondition( is_defined() );
  return supporting_parabola().base().bbox() + start().bbox() + end().bbox();
}

/*
template < class FT >
CGAL_Parabola_arcC2<FT> CGAL_Parabola_arcC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return CGAL_Parabola_arcC2<FT>( t.transform(point() ),
                          t.transform(direction() ));
}
*/
 



#endif // CGAL_PARABOLA_ARCC2_H
