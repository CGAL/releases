// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/IO/Arr_file_writer.h
// package       : Arrangement (2.18)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_ARR_FILE_WRITER_H
#define CGAL_IO_ARR_FILE_WRITER_H 1

#ifndef CGAL_IO_BINARY_FILE_IO_H
#include <CGAL/IO/binary_file_io.h>
#endif // CGAL_IO_BINARY_FILE_IO_H

#ifndef CGAL_IO_PM_FILE_WRITER_H
#include <CGAL/IO/Pm_file_writer.h>
#endif // CGAL_IO_PM_FILE_HEADER_H

#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif

CGAL_BEGIN_NAMESPACE


template <class Arrangement>
class Arr_file_writer : public  Pm_file_writer<Arrangement> {

public:
  //typedef Arrangement_                                           Arrangement;
  typedef typename Arrangement::Curve_iterator            Curve_iterator;
  typedef typename Arrangement::Subcurve_iterator         Subcurve_iterator;
  typedef typename Arrangement::Edge_iterator             Edge_iterator;
  typedef typename Arrangement::Curve_const_iterator      Curve_const_iterator;
  typedef typename Arrangement::Subcurve_const_iterator   
                                                    Subcurve_const_iterator;
  typedef typename Arrangement::Edge_const_iterator      Edge_const_iterator;

  Arr_file_writer(std::ostream& o, 
                  const Arrangement& arr, 
                  bool verbose = false) : 
    Pm_file_writer<Arrangement>(o, arr, verbose) {}

  Arr_file_writer(std::ostream& o, 
                  const File_header& h) : 
    Pm_file_writer<Arrangement>(o, h) {}
  

  void write_curve (Curve_iterator cv){
    out () << cv->curve() << std::endl;
  }

  void write_curve (Curve_const_iterator cv){
    out () << cv->curve() << std::endl;
  }

  void write_subcurve (Subcurve_iterator scv){
    out () << scv->curve() << std::endl;
  }

  void write_subcurve (Subcurve_const_iterator scv){
    out () << scv->curve() << std::endl;
  }
  
  void write_edge(Edge_iterator edge){
    out () << edge->curve() << std::endl;
  }
  
  void write_edge(Edge_const_iterator edge){
    out () << edge->curve() << std::endl;
  }

  //void write_edge_nodes_end() {
  //  out() << std::endl;
  // }

  /*void write_footer() {
    if (m_header.comments())
    out() << "#------------------- End of Arrangement #";
    out() << std::endl;
    } */
};
CGAL_END_NAMESPACE
#endif // CGAL_IO_FILE_WRITER_ARR_H //
// EOF //









