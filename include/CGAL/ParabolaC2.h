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
// file          : include/CGAL/ParabolaC2.h
// package       : C2 (2.1.4)
// source        : web/ParabolaC2.fw
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



#ifndef CGAL_PARABOLAC2_H
#define CGAL_PARABOLAC2_H

#ifndef CGAL_SOLVE_H
#include <CGAL/solve.h>
#endif // CGAL_SOLVE_H
#ifndef CGAL_SEGMENTC2_H
#include <CGAL/SegmentC2.h>
#endif // CGAL_SEGMENTC2_H
#ifndef CGAL_AFF_TRANSFORMATIONC2_H
#include <CGAL/Aff_transformationC2.h>
#endif // CGAL_AFF_TRANSFORMATIONC2_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class _ParabolaC2 : public Rep
{
public:
  PointC2<FT>  _base;
  VectorC2<FT> _vector;
  FT  _curvature;

  _ParabolaC2()
    {}

  _ParabolaC2(const PointC2<FT> &base,
              const VectorC2<FT> &vector,
              const FT & curvature) :
  _base(base), _vector(vector), _curvature(curvature)
    {}

  ~_ParabolaC2()
    {}
};

template < class FT >
class ParabolaC2 : public Handle
{
public:
                  ParabolaC2();
                  ParabolaC2(const ParabolaC2<FT>  &l);

                  ParabolaC2(const PointC2<FT> &p,
                             const VectorC2<FT> &v,
                             const FT &c);

                  ParabolaC2(const LineC2<FT> &l,
                             const PointC2<FT> &p);

                  ~ParabolaC2();

  ParabolaC2<FT>  &operator=(const ParabolaC2<FT> &l);

  bool            operator==(const ParabolaC2<FT> &l) const;
  bool            operator!=(const ParabolaC2<FT> &l) const;
  int             id() const;


  PointC2<FT>     base() const;
  PointC2<FT>     focus() const;
  LineC2<FT>      director() const;
  VectorC2<FT>    vector() const;
  FT              curvature() const;

  ParabolaC2<FT>  opposite() const;

  int             lambdas_at_x(const FT &x,
                               FT &lambda1,
                               FT &lambda2) const;
  int             lambdas_at_y(const FT &y,
                               FT &lambda1,
                               FT &lambda2) const;
  FT              x_at_lambda(const FT &lambda) const;
  FT              y_at_lambda(const FT &lambda) const;

  PointC2<FT>     projection(const PointC2<FT> &p) const;

  PointC2<FT>     projection(const PointC2<FT> &p,
                             FT &lambda) const;

  PointC2<FT>     operator()(const FT &lambda) const;


  Oriented_side   oriented_side(const PointC2<FT> &p) const;
  bool            has_on_boundary(const PointC2<FT> &p) const;
  bool            has_on_positive_side(const PointC2<FT> &p) const;
  bool            has_on_negative_side(const PointC2<FT> &p) const;

  bool            is_degenerate() const;


  ParabolaC2<FT>  transform(const Aff_transformationC2<FT> &t) const;



  DirectionC2<FT> direction() const;
private:

  _ParabolaC2<FT>* ptr() const;

  void            new_rep(const PointC2<FT> &p,
                          const VectorC2<FT> &v,
                          const FT &c);

};


template < class FT >
inline _ParabolaC2<FT>* ParabolaC2<FT>::ptr() const
{
  return (_ParabolaC2<FT>*)PTR;
}


template < class FT >
inline void ParabolaC2<FT>::new_rep(const PointC2<FT> &p,
                                    const VectorC2<FT> &v,
                                    const FT &c)
{
  PTR = new _ParabolaC2<FT> (p, v, c);
}

template < class FT >
ParabolaC2<FT>::ParabolaC2()
{
  PTR = new _ParabolaC2<FT>;
}

template < class FT >
ParabolaC2<FT>::ParabolaC2(const ParabolaC2<FT>  &l) :
  Handle((const Handle&)l)
{}

template < class FT >
ParabolaC2<FT>::ParabolaC2(const PointC2<FT> &p,
                           const VectorC2<FT> &v,
                           const FT &c)
{
  new_rep(p, v, c);
}


template < class FT >
ParabolaC2<FT>::ParabolaC2(const LineC2<FT> &l,
                           const PointC2<FT> &p)
{
  VectorC2<FT> v = p - l.projection(p);
  PointC2<FT> base_point = p - v/FT(2);
  FT d = sqrt(v*v);

  if (l.oriented_side(p) == NEGATIVE)
    d = -d;
  VectorC2<FT> w = l.direction().vector();
  FT lw = sqrt(w*w);

  new_rep(base_point, w/lw , FT(1)/(FT(2)*d));
}


template < class FT >
ParabolaC2<FT>::~ParabolaC2()
{}


template < class FT >
ParabolaC2<FT> &ParabolaC2<FT>::operator=(const ParabolaC2<FT> &l)
{

  Handle::operator=(l);
  return *this;
}
template < class FT >
bool ParabolaC2<FT>::operator==(const ParabolaC2<FT> &p) const
{
  return (base() == p.base()) &&
         (vector().direction() == p.vector().direction()) &&
         (curvature() == p.curvature());
}

template < class FT >
bool ParabolaC2<FT>::operator!=(const ParabolaC2<FT> &p) const
{
  return !(*this == p);
}

template < class FT >
int ParabolaC2<FT>::id() const
{
  return (int) PTR ;
}

template < class FT >
PointC2<FT> ParabolaC2<FT>::base() const
{
  return  ptr()->_base;
}

template < class FT >
DirectionC2<FT> ParabolaC2<FT>::direction() const
{
  return  vector().direction();
}

template < class FT >
VectorC2<FT> ParabolaC2<FT>::vector() const
{
  return  ptr()->_vector;
}

template < class FT >
FT ParabolaC2<FT>::curvature() const
{
  return ptr()->_curvature;
}
template < class FT >
ParabolaC2<FT>  ParabolaC2<FT>::opposite() const
{
  return ParabolaC2<FT>(base(), -vector(), -curvature());
}

template < class FT >
PointC2<FT> ParabolaC2<FT>::focus() const
{
  VectorC2<FT> v = vector();

  v = v / sqrt(v*v);
  return base() + (FT(1)/(FT(4)*curvature())) *
                  v.perpendicular(COUNTERCLOCKWISE);
}


template < class FT >
LineC2<FT> ParabolaC2<FT>::director() const
{
  VectorC2<FT> v = vector();

  v = v / sqrt(v*v);
  return LineC2<FT>(base() + (FT(1)/(FT(4)*curvature()))
                             * v.perpendicular(CLOCKWISE),
                    direction());
}


template < class FT >
int ParabolaC2<FT>::lambdas_at_x(const FT &x,
                                 FT &lambda1,
                                 FT &lambda2) const
{

  VectorC2<FT> v = vector();
  if (v.y() != FT(0)) {
    const FT a = - v.x()/(curvature()*  v.y());
    const FT b = (base().x()-x)/(curvature() * v.y());

    FT s = square(a)/4 + b;

    if (s < FT(0))
      return 0;

    s = sqrt(s);

    lambda1 = -a/FT(2) - s;
    lambda2 = -a/FT(2) + s;
    return 2;
  } else {
    lambda1 = (x - base().x())/v.x();
    lambda2 = lambda1;
  }
  return 1;
}

template < class FT >
int ParabolaC2<FT>::lambdas_at_y(const FT &y,
                                 FT &lambda1,
                                 FT &lambda2) const
{

  VectorC2<FT> v = vector();
  if(v.x() != FT(0)){
    const FT a = v.y()/(curvature() * v.x());
    const FT b = (base().y() - y)/(curvature() * v.x());

    FT s = square(a)/4 - b;

    if (s < FT(0))
      return 0;

    s = sqrt(s);

    lambda1 = -a/FT(2) - s;
    lambda2 = -a/FT(2) + s;
    return 2;
  }else{
    lambda1 = (y - base().y())/v.y();
    lambda2 = lambda1;
  }
  return 1;
}



template < class FT >
FT ParabolaC2<FT>::x_at_lambda(const FT &lambda) const
{

  VectorC2<FT> v = vector();
  return base().x() + lambda * (v.x() - lambda*curvature()*v.y());
}

template < class FT >
FT ParabolaC2<FT>::y_at_lambda(const FT &lambda) const
{

  VectorC2<FT> v = vector();
  return base().y() + lambda * (v.y() + lambda*curvature()*v.x());
}


template < class FT >
PointC2<FT> ParabolaC2<FT>::operator()(const FT &lambda) const
{
  return PointC2<FT>(x_at_lambda(lambda),
                     y_at_lambda(lambda));
}

template < class FT >
PointC2<FT> ParabolaC2<FT>::projection(const PointC2<FT> &p) const
{
  VectorC2<FT> v = vector();
  LineC2<FT> l(base(), direction());
  PointC2<FT> lp(l.projection(p));
  FT lambda = (v.x()!=FT(0)) ? (lp.x()-base().x())/v.x()
                             : (lp.y()-base().y())/v.y();
  return lp +  (lambda * lambda * curvature()) *
               v.perpendicular(COUNTERCLOCKWISE);
}

template < class FT >
PointC2<FT> ParabolaC2<FT>::projection(const PointC2<FT> &p, FT &lambda) const
{
  VectorC2<FT> v = vector();
  LineC2<FT> l(base(), direction());
  PointC2<FT> lp(l.projection(p));

  lambda = (v.x()!=FT(0)) ? (lp.x()-base().x())/v.x()
                          : (lp.y()-base().y())/v.y();

  return lp +  (lambda * lambda * curvature()) *
               v.perpendicular(COUNTERCLOCKWISE);
}

template < class FT >
Oriented_side ParabolaC2<FT>::oriented_side(const PointC2<FT> &p) const
{
  VectorC2<FT> v = vector();
  LineC2<FT> l(base(), v.direction());


  Oriented_side where = l.oriented_side(p);
  if ( (where == ON_NEGATIVE_SIDE && curvature() > FT(0))
    || (where == ON_POSITIVE_SIDE && curvature() < FT(0)) )
    return ON_NEGATIVE_SIDE;

  if ( (where == ON_ORIENTED_BOUNDARY && curvature() == FT(0))
       || p == base() )
    return ON_ORIENTED_BOUNDARY;

  PointC2<FT> lp(l.projection(p));
  FT lambda = (v.x()!=FT(0)) ? (lp.x()-base().x())/v.x()
                             : (lp.y()-base().y())/v.y();

  PointC2<FT> pp = lp +  (lambda * lambda * curvature()) *
                        v.perpendicular(COUNTERCLOCKWISE);

  if ( p == pp )
    return ON_ORIENTED_BOUNDARY;

  // lp, p and pp are pairwise unequal
  bool b = collinear_are_ordered_along_line(lp, p, pp);

  if (curvature() > FT(0))
    return  b ? ON_NEGATIVE_SIDE : ON_POSITIVE_SIDE;
  else
    return  b ? ON_POSITIVE_SIDE : ON_NEGATIVE_SIDE;
}


template < class FT >
bool ParabolaC2<FT>::has_on_positive_side(const PointC2<FT> &p) const
{
  return oriented_side(p) == ON_POSITIVE_SIDE;
}

template < class FT >
bool ParabolaC2<FT>::has_on_negative_side(const PointC2<FT> &p) const
{
  return oriented_side(p) == ON_NEGATIVE_SIDE;
}

template < class FT >
bool ParabolaC2<FT>::has_on_boundary(const PointC2<FT> &p) const
{
  VectorC2<FT> v = vector();
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
bool ParabolaC2<FT>::is_degenerate() const
{

  return (curvature() == FT(0)) ;
}

template < class FT >
ParabolaC2<FT>
ParabolaC2<FT>::transform(const Aff_transformationC2<FT> &t) const
{
  return ParabolaC2<FT>(director().transform(t),
                        focus().transform(t));
}


CGAL_END_NAMESPACE

#endif // CGAL_PARABOLAC2_H
