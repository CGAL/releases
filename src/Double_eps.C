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
// source        : Double_eps.fw
// file          : src/Double_eps.C
// package       : Number_types (2.7.1)
// revision      : 2.7.1
// revision_date : 04 Dec 1999 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif // CGAL_BASIC_H
#ifndef CGAL_DOUBLE_EPS_H
#include <CGAL/Double_eps.h>
#endif // CGAL_DOUBLE_EPS_H

CGAL_BEGIN_NAMESPACE

double Double_eps::_eps = 0.0;


double set_eps(double eps)
  {
    double e = Double_eps::_eps;
    Double_eps::_eps = eps;
    return e;
  }

Double_eps sqrt(const Double_eps &de)
  {
    return Double_eps(sqrt(de.d()));
  }

std::ostream&
operator<<(std::ostream& os, const Double_eps &de)
{
  os << de.d();
  return os;
}

std::istream&
operator>>(std::istream& is, Double_eps &de)
{
  is >> de._d;
  return is;
}
CGAL_END_NAMESPACE

