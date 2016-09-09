// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/d_utils.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/03/18 20:34:03 $
// author        : Herve Broennimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_D_UTILS_H
#define CGAL_CARTESIAN_D_UTILS_H

#include <CGAL/copy_n.h>
#include <iterator>
#include <algorithm>
#include <functional>

CGAL_BEGIN_NAMESPACE

// Small object utility for printing objects
// with separators depending on the ostream mode
template < class Object >
struct print_d
{
  const char *  _separator;
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
