// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/Aff_transformation_rep_2.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2002/01/22 09:46:13 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H

#include <CGAL/determinant.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Aff_transformation_rep_baseC2
  : public Ref_counted_virtual
{
public:
  typedef typename R::FT                   FT;
  typedef typename R::Point_2              Point_2;
  typedef typename R::Vector_2             Vector_2;
  typedef typename R::Direction_2          Direction_2;
  typedef typename R::Aff_transformation_2 Aff_transformation_2;

  virtual ~Aff_transformation_rep_baseC2() {}

  virtual Point_2     transform(const Point_2 &p) const  = 0;
  virtual Vector_2    transform(const Vector_2 &v) const = 0;
  virtual Direction_2 transform(const Direction_2 &d) const=0;

  virtual Aff_transformation_2 operator*(
                       const Aff_transformation_rep_baseC2 &t) const = 0;

  virtual Aff_transformation_2 compose(
                       const Aff_transformation_repC2<R> &t) const  = 0;

  virtual Aff_transformation_2 compose(
                       const Translation_repC2<R> &t) const  = 0;

  virtual Aff_transformation_2 compose(
                       const Rotation_repC2<R> &t) const  = 0;

  virtual Aff_transformation_2 compose(
                       const Scaling_repC2<R> &t) const  = 0;

  virtual Aff_transformation_2 inverse() const  = 0;
  virtual bool                 is_even() const  = 0;
  virtual FT                   cartesian(int i, int j) const = 0;
  virtual std::ostream         &print(std::ostream &os) const = 0;
};

template < class R >
class Aff_transformation_repC2
  : public Aff_transformation_rep_baseC2<R>
{
public:
  typedef typename R::FT                              FT;
  typedef Aff_transformation_repC2<R>                 Self;
  typedef Aff_transformation_rep_baseC2<R>            Aff_t_base;
  typedef typename Aff_t_base::Point_2                Point_2;
  typedef typename Aff_t_base::Vector_2               Vector_2;
  typedef typename Aff_t_base::Direction_2            Direction_2;
  typedef typename Aff_t_base::Aff_transformation_2   Aff_transformation_2;

friend class Translation_repC2<R>;
friend class Rotation_repC2<R>;
friend class Scaling_repC2<R>;

  Aff_transformation_repC2()
  {}

  Aff_transformation_repC2( const FT& m11, const FT& m12,
                            const FT& m21, const FT& m22)
    : t11(m11), t12(m12), t13(0),
      t21(m21), t22(m22), t23(0)
  {}

  Aff_transformation_repC2( const FT& m11, const FT& m12, const FT& m13,
                            const FT& m21, const FT& m22, const FT& m23)
    : t11(m11), t12(m12), t13(m13),
      t21(m21), t22(m22), t23(m23)
  {}

  Point_2 transform(const Point_2& p) const // FIXME : construction
  {
    return Point_2(t11 * p.x() + t12 * p.y() + t13,
                   t21 * p.x() + t22 * p.y() + t23);
  }

  // note that a vector is not translated
  Vector_2 transform(const Vector_2& v) const // FIXME : construction
  {
    return Vector_2(t11 * v.x() + t12 * v.y(),
                    t21 * v.x() + t22 * v.y());
  }

  // note that a direction is not translated
  Direction_2 transform(const Direction_2& dir) const // FIXME : construction
  {
    Vector_2 v = dir.to_vector();
    return Direction_2(t11 * v.x() + t12 * v.y(),
                       t21 * v.x() + t22 * v.y());
  }

  // Note that Aff_transformation is not defined yet,
  // so the following 6 functions have to be implemented later...
  Aff_transformation_2 inverse() const;
  Aff_transformation_2 operator*(const Aff_t_base &t) const;
  Aff_transformation_2 compose(const Self &t) const;
  Aff_transformation_2 compose(const Translation_repC2<R> &t) const;
  Aff_transformation_2 compose(const Rotation_repC2<R> &t) const;
  Aff_transformation_2 compose(const Scaling_repC2<R> &t) const;

  bool is_even() const
  {
    return sign_of_determinant2x2(t11, t12, t21, t22) == POSITIVE;
  }

  FT cartesian(int i, int j) const
  {
    switch (i)
    {
    case 0: switch (j)
            {
              case 0: return t11;
              case 1: return t12;
              case 2: return t13;
            }
    case 1: switch (j)
            {
              case 0: return t21;
              case 1: return t22;
              case 2: return t23;
            }
    case 2: switch (j)
            {
              case 0: return FT(0);
              case 1: return FT(0);
              case 2: return FT(1);
            }
    }
    return FT(0);
  }

  std::ostream &print(std::ostream &os) const
  {
    os <<"Aff_transformationC2(" <<t11<<" "<<t12<<" "<<t13<<std::endl;
    os <<"                     " <<t21<<" "<<t22<<" "<<t23<<")";
    return os;
  }

private:
    FT   t11, t12, t13;
    FT   t21, t22, t23;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
inverse() const
{
  FT det = FT(1) / (t11 * t22 - t12 * t21);
  return Aff_transformation_2(
    det * t22,    det * (-t12), det * (t12*t23-t13*t22),
    det * (-t21), det * t11 ,   det * (t13*t21-t11*t23));
}

template < class R >
CGAL_KERNEL_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
operator*(const Aff_transformation_rep_baseC2<R> &t) const
{
  return t.compose(*this);
}
 
template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Aff_transformation_repC2<R> &t) const
{
  return Aff_transformation_2(t.t11*t11 + t.t12*t21,
                              t.t11*t12 + t.t12*t22,
                              t.t11*t13 + t.t12*t23 + t.t13,
                              t.t21*t11 + t.t22*t21,
                              t.t21*t12 + t.t22*t22,
                              t.t21*t13 + t.t22*t23 + t.t23 );
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Translation_repC2<R> &t) const
{
  return Aff_transformation_2(t11,
                              t12,
                              t13 + t.translationvector_.x(),
                              t21,
                              t22,
                              t23 + t.translationvector_.y());
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Rotation_repC2<R> &t) const
{
  return Aff_transformation_2(t.cosinus_*t11 - t.sinus_*t21,
                              t.cosinus_*t12 - t.sinus_*t22,
                              t.cosinus_*t13 - t.sinus_*t23,
                              t.sinus_*t11 + t.cosinus_*t21,
                              t.sinus_*t12 + t.cosinus_*t22,
                              t.sinus_*t13 + t.cosinus_*t23);
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Aff_transformation_repC2<R>::Aff_transformation_2
Aff_transformation_repC2<R>::
compose(const Scaling_repC2<R> &t) const
{
   return Aff_transformation_2(t.scalefactor_ * t11,
                               t.scalefactor_ * t12,
                               t.scalefactor_ * t13,
                               t.scalefactor_ * t21,
                               t.scalefactor_ * t22,
                               t.scalefactor_ * t23);
}

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H
