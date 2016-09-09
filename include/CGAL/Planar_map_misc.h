// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Planar_map_misc.h
// package       : pm (1.12.3)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//
// coordinator   : Tel-Aviv University (Dan Halperin)
// chapter       : Planar Map
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_PLANAR_MAP_MISC_H
#define CGAL_PLANAR_MAP_MISC_H


// base_class_iterator -
//    Extend the BaseIterator into a fully compatible STL iterator
//    IS there a standart class that do this job????
template <class BaseIterator, class Type>
class base_class_iterator
{
public:
  base_class_iterator()
  {}
  
  base_class_iterator(const BaseIterator &it)
    : iter(it)
  {}
  
  base_class_iterator(const base_class_iterator<BaseIterator, Type> &it)
    : iter(it.iter)
  {}
  
  base_class_iterator<BaseIterator, Type>  & operator=
    (const base_class_iterator<BaseIterator, Type> &it)
  { 
    iter = it.iter;
    return  *this;
  }
  
  base_class_iterator<BaseIterator, Type> &operator++()
  {
    ++iter; 
    return *this; 
  }
  
  base_class_iterator<BaseIterator, Type> operator++(int)
  {
    base_class_iterator<BaseIterator, Type> tmp = *this;
    ++*this;
    return tmp;
  }
  
  base_class_iterator<BaseIterator, Type> &operator--()
  {
    --iter; 
    return *this; 
  }
  
  base_class_iterator<BaseIterator, Type> operator--(int)
  { 
    base_class_iterator<BaseIterator, Type> tmp = *this;
    --*this;
    return tmp;
  }
  
  bool operator==(const base_class_iterator<BaseIterator, Type> &ici) const
  {
    return iter == ici.iter; 
  }
  
  bool operator!=(const base_class_iterator<BaseIterator, Type> &ici) const
  {
    return !(*this == ici); 
  }
  
  Type operator*() const
  { 
    return Type(*iter); 
  }
  
private:
  BaseIterator iter;
};


//--------------------------------------------------------------------------
// CGAL_Planar_map_traits_wrap - 
//     Geometric Look Up Table. This class extends the user supplied 
// interface to include various less "shallow" operations that are
// impelemented through the interface.
//--------------------------------------------------------------------------

template <class I>
class CGAL_Planar_map_traits_wrap : public I
{
public:
  typedef  typename I::Info_vertex     Info_vertex;
  typedef  typename I::Info_edge       Info_edge;
  typedef  typename I::Info_face       Info_face;
  
  typedef  typename I::X_curve         X_curve;
  typedef  typename I::Point           Point;
  
/*
#ifdef _PM_TRAITS_WITH_INTERSECTIONS
  //    typedef  I::Curve_handle    Curve_handle;
  typedef  I::Curve           Curve;
#endif
*/
  
  CGAL_Planar_map_traits_wrap() : I()
  {
  }
  
  bool is_x_smaller( const Point  & p1, const Point  & p2 )
  {
    return (compare_x(p1, p2) == CGAL_SMALLER); 
  }
  
    bool is_x_larger( const Point  & p1, const  Point  & p2 )
  {
    return (compare_x(p1, p2) == CGAL_LARGER); 
  }
  
  bool is_x_equal( const Point  & p1, const Point  & p2 )
  {
    return (compare_x(p1, p2) == CGAL_EQUAL); 
  }
  
  bool point_is_lower( const Point  & p1, const Point  & p2 )
  { 
    return (compare_y(p1, p2) == CGAL_SMALLER); 
  }
  
  bool point_is_higher( const Point  & p1, const Point  & p2 )
  {
    return (compare_y(p1, p2) == CGAL_LARGER); 
  }
  
  bool point_is_same_y( const Point  & p1, const Point  & p2 )
  {
    return (compare_y(p1, p2) == CGAL_EQUAL); 
  }
  
  bool point_is_same( const Point  & p1, const Point  & p2 )
  { 
    return ( (compare_y(p1, p2) == CGAL_EQUAL) &&
             (compare_x(p1, p2) == CGAL_EQUAL)   );	
  }
  
  bool point_is_left_low( const Point  & p1, 
                          const Point  & p2 )
  { 
    CGAL_Comparison_result k = compare_x(p1, p2);
    if (k == CGAL_SMALLER)
      return true;
    if ( (k == CGAL_EQUAL) && (point_is_lower(p1, p2)) )
      return true;
    return false;
  }
};


#else   /*CGAL_PLANAR_MAP_MISC_H */
#error  Header file Planar_map_misc.h included twice
#endif  /*CGAL_PLANAR_MAP_MISC_H */

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * Planar_map_misc.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/






















