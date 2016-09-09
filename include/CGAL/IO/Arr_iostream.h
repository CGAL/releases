// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/IO/Arr_iostream.h
// package       : Arrangement (2.52)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ARR_IOSTREAM_H
#define CGAL_ARR_IOSTREAM_H

#include <CGAL/basic.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/IO/Arr_file_writer.h>
#include <CGAL/IO/write_arr.h>
#include <iostream>

CGAL_BEGIN_NAMESPACE

template <class Dcel, class Traits, class Base_node> inline
::std::ostream & operator << (::std::ostream & o, 
                              const Arrangement_2<Dcel,Traits,Base_node> & arr)
{
  typedef Arrangement_2<Dcel,Traits,Base_node>        Arr_2;
  typedef Arr_file_writer<Arr_2>                      Writer;

  //print_OFF(o, arr);
  
  Writer writer(o, arr);
  write_arr<Arr_2,Writer>(arr, writer, o);
  return o;
}

template <class Dcel, class Traits, class Base_node> inline
::std::istream & operator >> (std::istream & in, 
                              Arrangement_2<Dcel,Traits, Base_node> & arr)
{
  // reads a polyhedron from `in' and appends it to P.
  arr.read(in);
  return in;
}

CGAL_END_NAMESPACE

#endif
