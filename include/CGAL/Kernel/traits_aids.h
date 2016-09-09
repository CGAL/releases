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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// source        : Traits_helpers.lw
// file          : include/CGAL/Kernel/traits_aids.h
// package       : Kernel_basic (3.14)
// revision      : 0.95
// revision_date : 22 Feb 2000
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_KERNEL_TRAITS_AIDS_H
#define CGAL_KERNEL_TRAITS_AIDS_H

namespace CGAL {

template <class Leftturn>
class Rightturn_by_leftturn
{
  public:
    Rightturn_by_leftturn(const Leftturn& l) : leftturn(l) {}

    template <class Point>
    bool
    operator()(const Point& p, const Point& q, const Point& r) const
    { return  leftturn( q, p, r); }
    
  private:
    Leftturn   leftturn;
};
template <class BinaryPredicate>
class Invert_binary
{
  public:
    Invert_binary(const BinaryPredicate& p) : pred(p) {}

    template <class Arg1, class Arg2>
    bool
    operator()(const Arg1& a1, const Arg2& a2)
    { return !pred(a1,a2); }

  protected:
    BinaryPredicate  pred;
};

} // namespace CGAL

#endif // CGAL_KERNEL_TRAITS_AIDS_H
