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
// source        : Double_eps.fw
// file          : src/Double_eps.C
// package       : Number_types (2.1.5)
// revision      : 2.1.5
// revision_date : 09 May 1999 
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

