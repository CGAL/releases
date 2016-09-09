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
// file          : include/CGAL/IO/Arr_iostream.h
// package       : Arrangement (2.18)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ARR_IOSTREAM_H
#define CGAL_ARR_IOSTREAM_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_ARRANGEMENT_2_H
#include <CGAL/Arrangement_2.h>
#endif

#ifndef CGAL_IO_ARR_FILE_WRITER_H
#include <CGAL/IO/Arr_file_writer.h>
#endif // CGAL_IO_ARR_FILE_WRITER_H

#ifndef CGAL_IO_WRITE_ARR_H
#include <CGAL/IO/write_arr.h>
#endif // CGAL_IO_WRITE_ARR_H


#include <iostream>

CGAL_BEGIN_NAMESPACE

template <class Dcel, class Traits, class Base_node> inline
::std::ostream& operator << (::std::ostream& o, 
                             const Arrangement_2<Dcel,Traits, 
                             Base_node>& arr) 
{
  //print_OFF(o, arr);
  
  Arr_file_writer< Arrangement_2<Dcel,Traits, Base_node> >  writer(o, arr);
  
  write_arr(arr, writer, o);
  
  return o;
}
 
template <class Dcel, class Traits, class Base_node> inline
::std::istream& operator>>( std::istream& in, 
                            Arrangement_2<Dcel,Traits, Base_node>& arr) {
  // reads a polyhedron from `in' and appends it to P.
  
  arr.read(in);
  
  return in;
}


CGAL_END_NAMESPACE

#endif








