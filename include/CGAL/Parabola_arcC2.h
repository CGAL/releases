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
// file          : include/CGAL/Parabola_arcC2.h
// package       : C2 (2.1.4)
// source        : web/Parabola_arcC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:32 $
// author(s)     : Andreas.Fabri
//                 Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PARABOLA_ARCC2_H
#define CGAL_PARABOLA_ARCC2_H

#ifndef CGAL_PARABOLAC2_H
#include <CGAL/ParabolaC2.h>
#endif // CGAL_PARABOLAC2_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class _Parabola_arcC2 : public Rep
{
public:
  ParabolaC2<FT>  _par;
  FT  _lambda_source;
  FT  _lambda_target;

  _Parabola_arcC2()
    {}

  _Parabola_arcC2(const ParabolaC2<FT> &par,
                  const FT &lambda_source,
                  const FT &lambda_target)
    : _par(par), _lambda_source(lambda_source), _lambda_target(lambda_target)
    {}

  ~_Parabola_arcC2()
    {}
};

template < class FT >
class Parabola_arcC2 : public Handle
{
public:
                  Parabola_arcC2();
                  Parabola_arcC2(const Parabola_arcC2<FT>  &p);

//                Parabola_arcC2(const ParabolaC2<FT> &par,
//                                 const PointC2<FT> &p,
//                                 const PointC2<FT> &q);
//
                  Parabola_arcC2(const ParabolaC2<FT> &par,
                                 const FT &lambda1,
                                 const FT &lambda2);

                  ~Parabola_arcC2();

  Parabola_arcC2<FT>  &operator=(const Parabola_arcC2<FT> &l);

  bool            operator==(const Parabola_arcC2<FT> &l) const;
  bool            operator!=(const Parabola_arcC2<FT> &l) const;
  int             id() const;

  ParabolaC2<FT>  supporting_parabola() const;

  FT              lambda_source() const;
  FT              lambda_target() const;
  FT              lambda(int i) const;

  PointC2<FT>     source() const;
  PointC2<FT>     target() const;
  PointC2<FT>     vertex(int i) const;
  PointC2<FT>     operator[](int i) const;

  bool            is_on(const PointC2<FT> &p) const;
  bool            is_degenerate() const;

  Parabola_arcC2<FT> opposite() const;
  Bbox_2          bbox() const;

  Parabola_arcC2<FT> transform(const Aff_transformationC2<FT> &t) const;

private:
  _Parabola_arcC2<FT>* ptr() const;
};


template < class FT >
inline _Parabola_arcC2<FT>* Parabola_arcC2<FT>::ptr() const
{
  return (_Parabola_arcC2<FT>*)PTR;
}


template < class FT >
Parabola_arcC2<FT>::Parabola_arcC2()
{
  PTR = new _Parabola_arcC2<FT>;
}

template < class FT >
Parabola_arcC2<FT>::Parabola_arcC2(const Parabola_arcC2<FT>  &l)
  : Handle((Handle&)l)
{}

template < class FT >
Parabola_arcC2<FT>::Parabola_arcC2(const ParabolaC2<FT>  &par,
                                   const FT &lambda1,
                                   const FT &lambda2)
{
  PTR = new _Parabola_arcC2<FT> (par, lambda1, lambda2);
}

template < class FT >
Parabola_arcC2<FT>::~Parabola_arcC2()
{}


template < class FT >
Parabola_arcC2<FT> &Parabola_arcC2<FT>::operator=(const Parabola_arcC2<FT> &l)
{

  Handle::operator=(l);
  return *this;
}
template < class FT >
bool Parabola_arcC2<FT>::operator==(const Parabola_arcC2<FT> &l) const
{
  return (supporting_parabola() == l.supporting_parabola()) &&
         (lambda_source() == l.lambda_source()) &&
         (lambda_target() == l.lambda_target());

}

template < class FT >
bool Parabola_arcC2<FT>::operator!=(const Parabola_arcC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
int Parabola_arcC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
ParabolaC2<FT> Parabola_arcC2<FT>::supporting_parabola() const
{
  return ptr()->_par;
}

template < class FT >
FT Parabola_arcC2<FT>::lambda_source() const
{
  return ptr()->_lambda_source;
}

template < class FT >
FT Parabola_arcC2<FT>::lambda_target() const
{
  return ptr()->_lambda_target;
}

template < class FT >
FT Parabola_arcC2<FT>::lambda(int i)  const
{
  return (i&1 == 0) ? lambda_source() : lambda_target();
}


template < class FT >
PointC2<FT> Parabola_arcC2<FT>::source() const
{
  return supporting_parabola()(lambda_source());
}

template < class FT >
PointC2<FT> Parabola_arcC2<FT>::target() const
{
  return supporting_parabola()(lambda_target());
}


template < class FT >
PointC2<FT> Parabola_arcC2<FT>::vertex(int i) const
{
  return (i%2 == 0) ? source() : target();
}

template < class FT >
PointC2<FT> Parabola_arcC2<FT>::operator[](int i) const
{
  return vertex(i);
}

template < class FT >
bool Parabola_arcC2<FT>::is_on(const PointC2<FT> &p) const
{
  ParabolaC2<FT> par = supporting_parabola();
  FT lambda1, lambda2;
  switch (par.lambdas_at_x(p.x(), lambda1, lambda2)) {
  case 2:
    return (par.y_at_lambda(lambda1)==p.y()) ||
           (par.y_at_lambda(lambda2)==p.y());
  case 1:
    return (par.y_at_lambda(lambda1)==p.y());
  }
  return false;
}


template < class FT >
bool Parabola_arcC2<FT>::is_degenerate() const
{
  return (supporting_parabola().curvature() == FT(0)) ;
}

template < class FT >
Parabola_arcC2<FT> Parabola_arcC2<FT>::opposite() const
{
  return Parabola_arcC2<FT>(supporting_parabola().opposite(),
                            -lambda_target(),
                            -lambda_source());
}

template < class FT >
Bbox_2  Parabola_arcC2<FT>::bbox() const
{
  return supporting_parabola().base().bbox() +
         source().bbox() + target().bbox();
}


template < class FT >
Parabola_arcC2<FT> Parabola_arcC2<FT>::transform(
                                  const Aff_transformationC2<FT> &t) const
{
  ParabolaC2<FT> par = supporting_parabola().transform(t);
  return Parabola_arcC2<FT>(par,
                            lambda_source(),
                            lambda_target());
}



CGAL_END_NAMESPACE

#endif // CGAL_PARABOLA_ARCC2_H
