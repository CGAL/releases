// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Cartesian/Aff_transformation_rep_2.h
// package       : C2 (3.3.11)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 1999/11/05 22:29:39 $
// author(s)     : Andreas Fabri, Lutz Kettner
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H
#define CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H

CGAL_BEGIN_NAMESPACE

template < class R >
class Aff_transformation_rep_baseC2
  : public Rep
{
public:
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef typename R::Point_2                   Point_2;
  typedef typename R::Vector_2                  Vector_2;
  typedef typename R::Direction_2               Direction_2;
  typedef typename R::Aff_transformation_2      Aff_transformation_2;
#else
  typedef typename R::Point_2_base              Point_2;
  typedef typename R::Vector_2_base             Vector_2;
  typedef typename R::Direction_2_base          Direction_2;
  typedef typename R::Aff_transformation_2_base Aff_transformation_2;
#endif

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
  typedef typename R::RT                              RT;
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

  Point_2 transform(const Point_2& p) const
  {
    return Point_2(t11 * p.x() + t12 * p.y() + t13,
                   t21 * p.x() + t22 * p.y() + t23);
  }

  // note that a vector is not translated
  Vector_2 transform(const Vector_2& v) const
  {
    return Vector_2(t11 * v.x() + t12 * v.y(),
                    t21 * v.x() + t22 * v.y());
  }

  // note that a direction is not translated
  Direction_2 transform(const Direction_2& dir) const
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

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_AFF_TRANSFORMATION_REP_2_H
