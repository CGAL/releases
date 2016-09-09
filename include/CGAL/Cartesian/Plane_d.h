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
// file          : include/CGAL/Cartesian/Plane_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/12/07 18:53:24 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_PLANE_D_H
#define CGAL_CARTESIAN_PLANE_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Cartesian/d_utils.h>
#include <CGAL/d_tuple.h>
#include <algorithm>
#include <functional>


CGAL_BEGIN_NAMESPACE

template <class _R>
class PlaneCd
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef _R                                    R;
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
  typedef const RT*                             const_iterator ;
  typedef RT*                                   iterator ;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef PlaneCd<R,Cartesian_tag>              Self;
  typedef typename R::Point_d                   Point_d;
  typedef typename R::Vector_d                  Vector_d;
  typedef typename R::Direction_d               Direction_d;
  typedef typename R::Line_d                    Line_d;
  typedef typename R::Aff_transformation_d      Aff_transformation_d;
#else
  typedef PlaneCd<R>                            Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Vector_d_base             Vector_d;
  typedef typename R::Direction_d_base          Direction_d;
  typedef typename R::Line_d_base               Line_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif

  PlaneCd(int d = 0);
  PlaneCd(const Self &p);
  PlaneCd(const Point_d &p, const Direction_d &d);
  PlaneCd(const Point_d &p, const Vector_d &d);
  template < class InputIterator >
  PlaneCd(const int d,
          const InputIterator &first, const InputIterator &last)
    {
      CGAL_kernel_assertion( last-first == d+1);
      new_rep(first,last);
    }
  template < class InputIterator >
  PlaneCd(const int d,
          const InputIterator &first, const InputIterator &last, const RT &w)
    {
      CGAL_kernel_assertion( last-first == d);
      new_rep(first,last,w);
    }
  template < class PointIterator >
  PlaneCd(const PointIterator &first, const PointIterator &last)
    { 
      Self h = plane_from_points(first->dimension(),first,last,R());
      new_rep(h.begin(),h.end());
    }
  template < class PointIterator >
  PlaneCd(const PointIterator &first, const PointIterator &last,
          const Point_d &o, Oriented_side side = POSITIVE)
    {
      Self h = plane_from_points(first->dimension(),first,last,o,side,R());
      new_rep(h.begin(),h.end());
    }
  ~PlaneCd();

  Self           &operator=(const Self &p);

  bool           operator==(const Self &p) const;
  bool           operator!=(const Self &p) const;
  long           id() const;

  RT             operator[](int i) const;
  Point_d        point(int i = 0) const;
  Point_d        projection(const Point_d &p) const;
  Vector_d       orthogonal_vector() const;
  Direction_d    orthogonal_direction() const;
  Vector_d       base(const int i) const;
  Line_d         perpendicular_line(const Point_d &p) const;
  Self           opposite() const;

  Point_d        to_plane_basis(const Point_d &p) const;

  Self           transform(const Aff_transformation_d &t) const;

  Oriented_side  oriented_side(const Point_d &p) const;
  bool           has_on_boundary(const Point_d &p) const;
  bool           has_on_positive_side(const Point_d &l) const;
  bool           has_on_negative_side(const Point_d &l) const;
  bool           has_on(const Point_d &p) const;

  bool           is_degenerate() const;

  // coordinate access
  int            dimension() const { return ptr()->d-1; }
  const_iterator begin()     const { return ptr()->e; }
  const_iterator end()       const { return ptr()->e+ptr()->d; }

// protected:
  iterator       begin()           { return ptr()->e; }
  iterator       end()             { return ptr()->e+ptr()->d; }

private:
  const _d_tuple<RT>* ptr()  const { return (const _d_tuple<RT>*)PTR; }
  _d_tuple<RT>*       ptr()        { return (_d_tuple<RT>*)PTR; }
  void new_rep(int d);
  void new_rep(const_iterator hb, const_iterator he);
  void new_rep(const_iterator hb, const_iterator he, const RT &w);
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Plane_d.C>
#endif 

#endif  // CGAL_CARTESIAN_PLANE_D_H
