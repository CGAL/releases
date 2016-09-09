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
// file          : include/CGAL/IO/Arr_file_scanner.h
// package       : Arrangement (2.18)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_ARR_FILE_SCANNER_H
#define CGAL_IO_ARR_FILE_SCANNER_H    1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#include <CGAL/known_bit_size_integers.h>
#endif
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H

//#ifndef CGAL_IO_FILE_HEADER_PM_H
//#include <CGAL/IO/File_header_pm.h>
//#endif // CGAL_IO_FILE_HEADER_PM_H

#ifndef CGAL_IO_PM_FILE_SCANNER_H
#include <CGAL/IO/Pm_file_scanner.h>
#endif // CGAL_IO_PM_FILE_SCANNER_H

#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

template <class Arrangement>
class Arr_file_scanner : public  Pm_file_scanner<Arrangement> {
public:
  typedef typename Arrangement::Curve_node                Curve_node;
  typedef typename Arrangement::Subcurve_node             Subcurve_node;
  typedef typename Arrangement::Edge_node                 Edge_node;
  
  typedef typename Arrangement::Traits                   Traits;
  typedef typename Traits::Point                         Point;
  typedef typename Traits::X_curve                       X_curve;
  typedef typename Traits::Curve                         Curve;

  Arr_file_scanner(std::istream& in) : Pm_file_scanner<Arrangement>(in) {}

  Arr_file_scanner(std::istream& in, const File_header& h) : 
    Pm_file_scanner<Arrangement>(in, h) {}

  void scan_Curve_node(Curve_node* cn){

    skip_comment();

    // providing default reading function.
    Curve curve;
    in() >> curve;

    cn->set_curve(curve);
  }
  
  void scan_Subcurve_node(Subcurve_node* scn){
    
    skip_comment();

    // providing default reading function.
    Curve curve;
    in() >> curve;
    
    scn->set_curve(curve);
  }
    
  void scan_Edge_node(Edge_node* en){
    
    skip_comment();

    // providing default reading function.
    Curve curve;
    in() >> curve;
    
    en->set_curve(curve);
  }

};


CGAL_END_NAMESPACE
#endif // CGAL_IO_FILE_SCANNER_PM_H //
// EOF //









