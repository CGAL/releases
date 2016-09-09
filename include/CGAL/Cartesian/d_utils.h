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
// file          : include/CGAL/Cartesian/d_utils.h
// package       : Cd (1.14)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/06/27 14:32:32 $
// author        : Herve Brönnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_D_UTILS_H
#define CGAL_CARTESIAN_D_UTILS_H

#include <iterator>
#include <algorithm>
#include <functional>

CGAL_BEGIN_NAMESPACE

// Small object utility for printing objects
// with separators depending on the ostream mode
template < class Object >
struct print_d
{
  char *       _separator;
  std::ostream*_os;
  bool         _print_sep;

  print_d(std::ostream *os) : _os(os), _print_sep(false)
  {
    if (_os->iword(IO::mode)==IO::ASCII) _separator = " ";
    else if (_os->iword(IO::mode)==IO::BINARY) _separator = "";
    else _separator = ", ";
  }
  void reset()
  {
    _print_sep = false;
  }
  void operator()(const Object &x) {
    if (_print_sep && _os->iword(IO::mode) != IO::BINARY)
      (*_os) << _separator;
    (*_os) << x;
    _print_sep = true;
  }
  void operator()(const int &x) {
    if (_print_sep && _os->iword(IO::mode) != IO::BINARY)
      (*_os) << _separator;
    (*_os) << x;
    _print_sep = true;
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_D_UTILS_H
