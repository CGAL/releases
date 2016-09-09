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
// file          : include/CGAL/Cartesian/Direction_d.h
// package       : Cd (1.14)
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/06/20 21:54:59 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_DIRECTION_D_H
#define CGAL_CARTESIAN_DIRECTION_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/d_tuple.h>
#include <algorithm>
#include <functional>

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionCd CGAL_ADVANCED_KERNEL_PARTIAL_SPEC
  : public Handle
{
public:
  typedef R_                                    R;
  typedef typename R::RT                        RT;
  typedef const RT*                             const_iterator;
  typedef RT*                                   iterator;
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef DirectionCd<R CGAL_CTAG>              Self;
  typedef typename R::Vector_d                  Vector_d;
  typedef typename R::Aff_transformation_d      Aff_transformation_d;
#else
  typedef DirectionCd<R>                        Self;
  typedef typename R::Vector_d_base             Vector_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif

  DirectionCd(int d = 0);
  DirectionCd(const Self &d);
  DirectionCd(const Vector_d &v);
  ~DirectionCd();

  template < class InputIterator >
  DirectionCd(int dim, const InputIterator &first, const InputIterator &last)
  {
    CGAL_kernel_precondition( dim > 0);
    CGAL_kernel_precondition( last-first == dim );
    PTR = new _d_tuple<RT>(dim);
    std::copy_n(first,dim,begin());
  }

  Self&          operator=(const Self &d);

  bool           operator==(const Self &d) const;
  bool           operator!=(const Self &d) const;

  long           id() const;
  
  bool           is_degenerate() const;
  Vector_d       to_vector() const;
  Self           operator-() const;
  Self           transform(const Aff_transformation_d &t) const;

  RT             delta(int i) const;

  int            dimension() const { return ptr()->d; }
  const_iterator begin()     const { return ptr()->e; }
  const_iterator end()       const { return ptr()->e + dimension(); }

// protected:
  iterator       begin()           { return ptr()->e; }
  iterator       end()             { return ptr()->e + dimension(); }

private:
  const _d_tuple<RT>* ptr()  const { return (const _d_tuple<RT>*)PTR; }
  _d_tuple<RT>*       ptr()        { return (_d_tuple<RT>*)PTR; }
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Direction_d.C>
#endif 

#endif // CGAL_CARTESIAN_DIRECTION_D_H
