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
// file          : include/CGAL/IO/Arr_leda_polyline_traits_Postscript_file_stream.h
// package       : Arrangement (2.18)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifdef CGAL_ARR_LEDA_POLYLINE_TRAITS_H
#ifndef CGAL_ARR_LEDA_POLYLINE_TRAITS_POSTSCRIPT_FILE_STREAM_H   
#define CGAL_ARR_LEDA_POLYLINE_TRAITS_POSTSCRIPT_FILE_STREAM_H  

#include <CGAL/rat_leda_in_CGAL_2.h>
#include <LEDA/rat_segment.h>
#

#ifndef CGAL_POSTSCRIPT_FILE_STREAM_H
#include <CGAL/IO/Postscript_file_stream.h>
#endif

CGAL_BEGIN_NAMESPACE

template <class Curve>
Postscript_file_stream& operator<<(Postscript_file_stream& ps, 
                                   const Curve& cv)        
{
  typedef typename Curve::value_type           Point;
  typedef typename Curve::iterator             Curve_iter;
  typedef leda_rat_segment                     Segment;
  typedef typename Curve::const_iterator       Points_iterator;
  
  ps << *(cv.begin());
  
  Points_iterator points_iter;
  for (points_iter = cv.begin(); points_iter != cv.end(); ) {
    //for (unsigned int i = 0; i < cv.size() - 1; i++){
    Points_iterator source_point = points_iter;
    
    Points_iterator target_point =  (++points_iter);
    
    if (target_point == cv.end())
      break;
    
    ps << Segment(*source_point, *target_point);
  }

  ps << *(--points_iter);

  return ps;
}

CGAL_END_NAMESPACE

#endif
#endif 









