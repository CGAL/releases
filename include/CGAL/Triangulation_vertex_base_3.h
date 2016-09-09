// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_vertex_base_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.16 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_VERTEX_BASE_3_H
#define CGAL_TRIANGULATION_VERTEX_BASE_3_H

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class GT > class Triangulation_vertex_base_3;
template < class GT >
std::istream& operator >> (std::istream&, Triangulation_vertex_base_3<GT>&);
  
template < class GT >
class Triangulation_vertex_base_3
{
  friend std::istream& operator >> CGAL_NULL_TMPL_ARGS
  (std::istream&, Triangulation_vertex_base_3<GT>&);

public:
  typedef typename GT::Point Point;
  
  // CONSTRUCTORS
  
  inline 
  Triangulation_vertex_base_3()
    : _p(), _c(NULL)
  {}
  
  inline 
  Triangulation_vertex_base_3(const Point & p)
    :  _p(p), _c(NULL)
  {}
    
  inline 
  Triangulation_vertex_base_3(const Point & p, void* c)
    :  _p(p), _c(c)
  {}

  inline 
  Triangulation_vertex_base_3(void* c)
    :  _p(), _c(c)
  {}

  // ACCES 

  inline 
  Point point() const
  { return _p; }
    
  inline 
  void* cell() const
  { return _c; }

  // SETTING

  inline 
  void set_point(const Point & p)
  { _p = p; }
    
  inline 
  void set_cell(void* c)
  { _c = c; }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool, int ) const
  { 
    //return true; 
    return( cell() != NULL );
  }


private:
  Point _p;
  void * _c;
  
};

template < class GT >
std::istream& operator >>
(std::istream& is, Triangulation_vertex_base_3<GT> & v)
  // non combinatorial information. Default = point
{
  typedef typename GT::Point Point;
  //  Point p;
  //  is >> p;
  is >> v._p;
  //  v.set_point(p);
  return is;
}
template < class GT >
std::ostream& operator<<
(std::ostream& os, const Triangulation_vertex_base_3<GT> & v)
  // non combinatorial information. Default = point
{
  os << v.point();
  //  if(is_ascii(os)){
  //    os << endl;
  //  }
  return os;
}

template < class GT >
class Triangulation_vertex_base_pointer_3;
template < class GT >
std::istream& operator >> 
(std::istream&, Triangulation_vertex_base_pointer_3<GT>&);

template < class GT >
class Triangulation_vertex_base_pointer_3
{
  friend std::istream& operator >> CGAL_NULL_TMPL_ARGS
  (std::istream&, Triangulation_vertex_base_pointer_3<GT>&);

public:
  typedef typename GT::Point Point;
  
  // CONSTRUCTORS
  
  inline 
  Triangulation_vertex_base_pointer_3()
    : _p(NULL), _c(NULL)
  {}
  
  inline 
  Triangulation_vertex_base_pointer_3(const Point & p)
    :  _p(&p), _c(NULL)
  {
    //    const Point * q =  &p;
    //    _p = q;
  }
    
  inline 
  Triangulation_vertex_base_pointer_3(const Point & p, void* c)
    :  _p(p), _c(c)
  {}

  inline 
  Triangulation_vertex_base_pointer_3(void* c)
    :  _p(NULL), _c(c)
  {}

  // ACCES 

  inline 
  const Point & point() const
  { return *_p; }
    
  inline 
  void* cell() const
  { return _c; }

  // SETTING

//   inline 
//   void set_point(Point * p)
//   {     
//     const Point * q =  &p;
//     p = q; 
//   }
    
  inline 
  void set_point(const Point & p)
  {     
    //    const Point * q =  &p;
    _p = &p; 
  }
    
  inline 
  void set_cell(void* c)
  { _c = c; }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool, int ) const
  { 
    //return true; 
    return( cell() != NULL );
  }


private:
  const Point * _p;
  void * _c;
  
};

template < class GT >
std::istream& operator >>
(std::istream& is, Triangulation_vertex_base_pointer_3<GT> & v)
  // non combinatorial information. Default = point
{ 
  typedef typename GT::Point Point;
  Point q;
  is >> q;
  const Point * p = new Point(q);
  v._p = p;
  return is;
}
template < class GT >
std::ostream& operator<<
(std::ostream& os, const Triangulation_vertex_base_pointer_3<GT> & v)
  // non combinatorial information. Default = point
{
  os << v.point();
  //  if(is_ascii(os)){
  //    os << endl;
  //  }
  return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_VERTEX_BASE_3_H
