// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Cartesian/Simplex_d.h
// package       : Cd (1.5)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/06/27 14:32:29 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_SIMPLEX_D_H
#define CGAL_CARTESIAN_SIMPLEX_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/d_tuple.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class SimplexCd
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<R_,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef R_                                    R;
  typedef typename R::FT                        FT;
  typedef typename R::RT                        RT;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef SimplexCd<R CGAL_CTAG>                Self;
  typedef typename R::Point_d                   Point_d;
  typedef typename R::Plane_d                   Plane_d;
  typedef typename R::Aff_transformation_d      Aff_transformation_d;
#else
  typedef SimplexCd<R>                          Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Plane_d_base              Plane_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif
  typedef const Point_d*                        const_iterator;
  typedef Point_d*                              iterator;

  SimplexCd();
  SimplexCd(const Self &t);
  template < class PointIterator >
  SimplexCd(const PointIterator &first, const PointIterator &last)
    { 
      int dimension = last-first-1;
      // kernel assertions: the following will be pruned if they're off
      CGAL_kernel_precondition( dimension>0 );
      PointIterator p;
      for (p=first; p!=last; ++p)
	CGAL_kernel_precondition( p->dimension() == dimension );
      // This is the code
      new_rep(dimension);
      std::copy(first,last,begin());
    }
  ~SimplexCd();

  Self &operator=(const Self &t);

  Point_d       vertex(int i) const;
  Point_d       operator[](int i) const;

  bool          operator==(const Self &t) const;
  bool          operator!=(const Self &t) const;
  long          id() const;

  int           dimension() const { return ptr()->d-1; }
  int           number_of_vertices() const { return ptr()->d; }

  // Bbox_d     bbox() const;
  Self       transform(const Aff_transformation_d &t) const;

  Orientation   orientation() const;
  Oriented_side oriented_side(const Point_d &p) const;
  Bounded_side  bounded_side(const Point_d &p) const;

  bool          has_on_positive_side(const Point_d &p) const;
  bool          has_on_negative_side(const Point_d &p) const;
  bool          has_on_bounded_side(const Point_d &p) const;
  bool          has_on_unbounded_side(const Point_d &p) const;
  bool          has_on_boundary(const Point_d &p) const;
  bool          has_on(const Point_d &p) const;

  bool          is_degenerate() const;

  // coordinate access
  const_iterator begin()     const { return ptr()->e; }
  const_iterator end()       const { return ptr()->e+ptr()->d; }

// protected:
  iterator       begin()           { return ptr()->e; }
  iterator       end()             { return ptr()->e+ptr()->d; }

private:
  void           new_rep(int dim)  { PTR = new _d_tuple<Point_d>(dim+1); } 
  _d_tuple< Point_d >* ptr() const { return (_d_tuple< Point_d >*)PTR; }
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Simplex_d.C>
#endif 

#endif
