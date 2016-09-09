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
// file          : include/CGAL/Triangulation_vertex_base_3.h
// package       : Triangulation_3 (1.83)
// revision      : $Revision: 1.21 $
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_VERTEX_BASE_3_H
#define CGAL_TRIANGULATION_VERTEX_BASE_3_H

#include <CGAL/basic.h>
#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class GT >
class Triangulation_vertex_base_3
{
public:
  typedef typename GT::Point_3 Point;
  
  // CONSTRUCTORS
  
  Triangulation_vertex_base_3()
    : _p(), _c(NULL)
  {}
  
  Triangulation_vertex_base_3(const Point & p)
    :  _p(p), _c(NULL)
  {}
    
  Triangulation_vertex_base_3(const Point & p, void* c)
    :  _p(p), _c(c)
  {}

  Triangulation_vertex_base_3(void* c)
    :  _p(), _c(c)
  {}

  // ACCES 

  const Point & point() const
  { return _p; }
    
  void* cell() const
  { return _c; }

  // SETTING

  void set_point(const Point & p)
  { _p = p; }
    
  void set_cell(void* c)
  { _c = c; }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool, int ) const
  { 
    return cell() != NULL;
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
  typename GT::Point_3 p;
  is >> p;
  v.set_point(p);
  return is;
}

template < class GT >
std::ostream& operator<<
(std::ostream& os, const Triangulation_vertex_base_3<GT> & v)
  // non combinatorial information. Default = point
{
  os << v.point();
  return os;
}

template < class GT >
class Triangulation_vertex_base_pointer_3
{
public:
  typedef typename GT::Point_3 Point;
  
  // CONSTRUCTORS
  
  Triangulation_vertex_base_pointer_3()
    : _p(NULL), _c(NULL)
  {}
  
  Triangulation_vertex_base_pointer_3(const Point & p)
    : _p(&p), _c(NULL)
  {}
    
  Triangulation_vertex_base_pointer_3(const Point & p, void* c)
    : _p(p), _c(c)
  {}

  Triangulation_vertex_base_pointer_3(void* c)
    : _p(NULL), _c(c)
  {}

  // ACCES 

  const Point & point() const
  { return *_p; }
    
  void* cell() const
  { return _c; }

  // SETTING

  void set_point(const Point & p)
  {     
    _p = &p; 
  }
    
  void set_cell(void* c)
  { _c = c; }

  // CHECKING

  // the following trivial is_valid allows
  // the user of derived cell base classes 
  // to add their own purpose checking
  bool is_valid(bool, int ) const
  { 
    return cell() != NULL;
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
  typedef typename GT::Point_3 Point;
  Point * q = new Point();
  is >> *q;
  v.set_point(*q);
  return is;
}

template < class GT >
std::ostream& operator<<
(std::ostream& os, const Triangulation_vertex_base_pointer_3<GT> & v)
  // non combinatorial information. Default = point
{
  os << v.point();
  return os;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_VERTEX_BASE_3_H
