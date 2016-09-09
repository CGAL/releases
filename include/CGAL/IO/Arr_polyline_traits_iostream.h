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
// file          : include/CGAL/IO/Arr_polyline_traits_iostream.h
// package       : Arrangement (2.18)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

//#ifdef CGAL_ARR_POLYLINE_TRAITS_H
#ifndef CGAL_ARR_POLYLINE_TRAITS_IOSTREAM_H   
#define CGAL_ARR_POLYLINE_TRAITS_IOSTREAM_H  

#ifndef CGAL_ARR_POLYLINE_TRAITS_H
#include <CGAL/Arr_polyline_traits.h>
#endif



CGAL_BEGIN_NAMESPACE

template <class R, class Container>
std::ostream&  operator<<(std::ostream& os,  const typename Arr_polyline_traits<R,Container>::Curve & cv)
{
  typedef typename Arr_polyline_traits<R>::Curve   Curve;
  typedef Curve::const_iterator       Points_iterator;
  
  os<<cv.size()<<std::endl;
  for (Points_iterator points_iter = cv.begin(); 
       points_iter != cv.end(); points_iter++)
    os<<" "<<*points_iter;

  return os;
}

template <class R, class Container>
std::ostream&  operator<<(std::ostream& os,  const typename Arr_polyline_traits<R,Container>::X_curve & cv)
{
  typedef typename Arr_polyline_traits<R>::Curve   Curve;
  typedef Curve::const_iterator       Points_iterator;
  
  os<<cv.size()<<std::endl;
  for (Points_iterator points_iter = cv.begin(); 
       points_iter != cv.end(); points_iter++)
    os<<" "<<*points_iter;

  return os;
}


template <class R, class Container>
std::istream&  operator>>(std::istream& in,  typename Arr_polyline_traits<R,Container>::Curve & cv)
{
  typedef typename Arr_polyline_traits<R>::Curve   Curve;
  typedef typename Curve::value_type           Point;

  std::size_t  size;

  in >> size;

  for (unsigned int i = 0; i < size; i++){
    Point  p;
    
    in >> p;
    
    cv.push_back(p);  
  }
  
  return in;
}


template <class R, class Container>
std::istream&  operator>>(std::istream& in,  typename Arr_polyline_traits<R,Container>::X_curve & cv)
{
  typedef typename Arr_polyline_traits<R>::Curve   Curve;
  typedef typename Curve::value_type           Point;

  std::size_t  size;

  in >> size;

  for (unsigned int i = 0; i < size; i++){
    Point  p;
    
    in >> p;
    
    cv.push_back(p);  
  }
  
  return in;
}



/*template <class Curve>
std::ostream&  operator<<(std::ostream& os,  const Curve& cv)
{

  typedef typename Curve::const_iterator       Points_iterator;
  
  os<<cv.size()<<std::endl;
  for (Points_iterator points_iter = cv.begin(); 
       points_iter != cv.end(); points_iter++)
    os<<" "<<*points_iter;

  return os;
}

template <class Curve>
std::istream&  operator>>(std::istream& in, Curve& cv)
{
  typedef typename Curve::value_type           Point;

  std::size_t  size;

  in >> size;

  for (unsigned int i = 0; i < size; i++){
    Point  p;
    
    in >> p;
    
    cv.push_back(p);  
  }
  
  return in;
}*/

CGAL_END_NAMESPACE

#endif
//#endif 





