// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Planar_map_2/Bounding_box_special_initializer.h
// package       : Planar_map (5.73)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PM_ADVANCED_BOUNDING_BOX
template <class T_>
Bounding_box_base* init_default_bounding_box(T_*) const
{
  return new Pm_unbounding_box<Self>;
}

#ifdef CGAL_PM_STRAIGHT_EXACT_TRAITS_H
template <class R_>
Bounding_box_base* init_default_bounding_box(Pm_straight_exact_traits<R_>*)
const
{
  return new Pm_dynamic_open_bounding_box<Self>;
}
template <class R_>
Bounding_box_base* 
init_default_bounding_box(const Pm_straight_exact_traits<R_>*)
const
{
  return new Pm_dynamic_open_bounding_box<Self>;
}
template <class R_>
Bounding_box_base* init_default_bounding_box(Pm_straight_exact_traits<R_>*)
{
  return new Pm_dynamic_open_bounding_box<Self>;
}
template <class R_>
Bounding_box_base* 
init_default_bounding_box(const Pm_straight_exact_traits<R_>*)
{
  return new Pm_dynamic_open_bounding_box<Self>;
}
#endif //CGAL_PM_STRAIGHT_EXACT_TRAITS_H
#else // CGAL_PM_ADVANCED_BOUNDING_BOX
template <class T_>
Bounding_box_base* init_default_bounding_box(T_*) const
{
  return new Pm_dynamic_open_bounding_box<Self>;
}

// special initializers for backward compatability.
#ifdef CGAL_PM_SEGMENT_EXACT_TRAITS_H
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_segment_exact_traits<R_>* t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_segment_exact_traits<R_>* t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_segment_exact_traits<R_>* t_) 
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_segment_exact_traits<R_>* t_) 
{
  return new Pm_unbounding_box<Self>;
}
#endif
#ifdef CGAL_PM_SEGMENT_EPSILON_TRAITS_H
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_segment_epsilon_traits<R_>*  t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_segment_epsilon_traits<R_>*  t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_segment_epsilon_traits<R_>*  t_)
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_segment_epsilon_traits<R_>*  t_)
{
  return new Pm_unbounding_box<Self>;
}
#endif
#ifdef CGAL_PM_LEDA_SEGMENT_EXACT_TRAITS_H
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_leda_segment_exact_traits<R_>* t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_leda_segment_exact_traits<R_>* t_) const
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_leda_segment_exact_traits<R_>* t_) 
{
  return new Pm_unbounding_box<Self>;
}
template <class R_> 
Bounding_box_base* init_default_bounding_box(
  Pm_leda_segment_exact_traits<R_>* t_) 
{
  return new Pm_unbounding_box<Self>;
}
#endif
#ifdef CGAL_PM_TRAITS_CHECKER_H
template <class T1_,class T2_,class C_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_traits_checker<T1_,T2_,C_>*  t_) const
{
  return init_default_bounding_box((const T1_* ) t_);
}
template <class T1_,class T2_,class C_> 
Bounding_box_base* init_default_bounding_box(
  Pm_traits_checker<T1_,T2_,C_>*  t_) const
{
  return init_default_bounding_box((T1_* ) t_);
}
template <class T1_,class T2_,class C_> 
Bounding_box_base* init_default_bounding_box(
  const Pm_traits_checker<T1_,T2_,C_>*  t_) 
{
  return init_default_bounding_box((const T1_* ) t_);
}
template <class T1_,class T2_,class C_> 
Bounding_box_base* init_default_bounding_box(
  Pm_traits_checker<T1_,T2_,C_>*  t_) 
{
  return init_default_bounding_box((T1_* ) t_);
}
#endif
#endif // CGAL_PM_ADVANCED_BOUNDING_BOX



