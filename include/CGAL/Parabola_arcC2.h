// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Parabola_arcC2.h
// package       : C2 (1.7)
// source        : web/Parabola_arcC2.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1999/01/04 06:54:14 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PARABOLA_ARCC2_H
#define CGAL_PARABOLA_ARCC2_H

#include <CGAL/ParabolaC2.h>

template <class FT>
class CGAL__Parabola_arcC2 : public CGAL_Rep
{
public:
  CGAL_ParabolaC2<FT>  _par;
  FT  _lambda_source;
  FT  _lambda_target;

  CGAL__Parabola_arcC2()
    {}

  CGAL__Parabola_arcC2(const CGAL_ParabolaC2<FT> &par,
                       const FT &lambda_source,
                       const FT &lambda_target)
    : _par(par), _lambda_source(lambda_source), _lambda_target(lambda_target)
    {}

  ~CGAL__Parabola_arcC2()
    {}
};


template < class FT >
class CGAL_Parabola_arcC2 : public CGAL_Handle
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
  int                  id() const;

  CGAL_ParabolaC2<FT>  supporting_parabola() const;

  FT                   lambda_source() const;
  FT                   lambda_target() const;
  FT                   lambda(int i) const;

  CGAL_PointC2<FT>     source() const;
  CGAL_PointC2<FT>     target() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 is_degenerate() const;

  CGAL_Parabola_arcC2<FT> opposite() const;
  CGAL_Bbox_2          bbox() const;

  CGAL_Parabola_arcC2<FT> transform(
                              const CGAL_Aff_transformationC2<FT> &t) const;

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
  PTR = new CGAL__Parabola_arcC2<FT>;
}

template < class FT >
CGAL_Parabola_arcC2<FT>::CGAL_Parabola_arcC2(const CGAL_Parabola_arcC2<FT>  &l)
  : CGAL_Handle((CGAL_Handle&)l)
{}

template < class FT >
CGAL_Parabola_arcC2<FT>::CGAL_Parabola_arcC2(const CGAL_ParabolaC2<FT>  &par,
                                             const FT &lambda1,
                                             const FT &lambda2)
{
  PTR = new CGAL__Parabola_arcC2<FT> (par, lambda1, lambda2);
}

template < class FT >
CGAL_Parabola_arcC2<FT>::~CGAL_Parabola_arcC2()
{}


template < class FT >
CGAL_Parabola_arcC2<FT> &CGAL_Parabola_arcC2<FT>::operator=(
                                              const CGAL_Parabola_arcC2<FT> &l)
{

  CGAL_Handle::operator=(l);
  return *this;
}
template < class FT >
bool CGAL_Parabola_arcC2<FT>::operator==(const CGAL_Parabola_arcC2<FT> &l) const
{
  return (supporting_parabola() == l.supporting_parabola()) &&
         (lambda_source() == l.lambda_source()) &&
         (lambda_target() == l.lambda_target());

}

template < class FT >
bool CGAL_Parabola_arcC2<FT>::operator!=(const CGAL_Parabola_arcC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
int CGAL_Parabola_arcC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_ParabolaC2<FT> CGAL_Parabola_arcC2<FT>::supporting_parabola() const
{

  return ptr()->_par;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda_source() const
{

  return ptr()->_lambda_source;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda_target() const
{

  return ptr()->_lambda_target;
}

template < class FT >
FT CGAL_Parabola_arcC2<FT>::lambda(int i)  const
{

 switch (i%2) {
  case 0: return lambda_source();
  case 1: return lambda_target();
  }
  return lambda_source();  // otherwise the SGI compiler complains
}


template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::source() const
{

  return supporting_parabola()(lambda_source());
}

template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::target() const
{

  return supporting_parabola()(lambda_target());
}


template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::vertex(int i) const
{

  switch (i%2) {
  case 0: return source();
  case 1: return target();
  }
  return source();  // otherwise the SGI compiler complains
}

template < class FT >
CGAL_PointC2<FT> CGAL_Parabola_arcC2<FT>::operator[](int i) const
{

  return vertex(i);
}

template < class FT >
bool CGAL_Parabola_arcC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
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

  return (supporting_parabola().curvature() == FT(0)) ;
}

template < class FT >
CGAL_Parabola_arcC2<FT> CGAL_Parabola_arcC2<FT>::opposite() const
{
  return CGAL_Parabola_arcC2<FT>(supporting_parabola().opposite(),
                                 -lambda_target(),
                                 -lambda_source());
}

template < class FT >
CGAL_Bbox_2  CGAL_Parabola_arcC2<FT>::bbox() const
{

  return supporting_parabola().base().bbox() +
         source().bbox() + target().bbox();
}


template < class FT >
CGAL_Parabola_arcC2<FT> CGAL_Parabola_arcC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_ParabolaC2<FT> par = supporting_parabola().transform(t);
  return CGAL_Parabola_arcC2<FT>(par,
                                 lambda_source(),
                                 lambda_target());
}




#endif // CGAL_PARABOLA_ARCC2_H
