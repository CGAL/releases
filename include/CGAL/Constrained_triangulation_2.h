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
// file          : include/CGAL/Constrained_triangulation_2.h
// package       : Triangulation (1.23)
// source        : web/Constrained_triangulation_2.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/02/10 13:26:46 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CONSTRAINED_TRIANGULATION_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_2_H

#include <pair.h>
#include <list.h>
#include <assert.h>

#include <CGAL/Triangulation_2.h>
#include <CGAL/Constrained_triangulation_sweep.h>

template < class T >
class CGAL_Constrained_triangulation_2
  : public CGAL_Triangulation_2<T>
{
public:
  typedef T  Traits;
  typedef typename T::Point Point;
  typedef typename T::Vertex Vertex;
  typedef typename T::Face Face;
  typedef typename T::Constraint Constraint;

  typedef typename Vertex::Vertex_handle Vertex_handle;
  typedef typename Face::Face_handle Face_handle;

  typedef CGAL_Constrained_triangulation_sweep<T>  Sweep;

public:
  CGAL_Constrained_triangulation_2() : CGAL_Triangulation_2<T>() { }
  
  CGAL_Constrained_triangulation_2(const T& t) : CGAL_Triangulation_2<T>(t) { }
  
  CGAL_Constrained_triangulation_2(list<Constraint>& lc, T& t=T())
      : CGAL_Triangulation_2<T>(t)
  {
    Sweep sweep(lc,t);
    init(sweep.vertex());
    CGAL_triangulation_postcondition( is_valid() );
  }
  
  #ifdef CGAL_CFG_NO_MEMBER_TEMPLATES
  
  #if defined(LIST_H) || defined(__SGI_STL_LIST_H)
  CGAL_Constrained_triangulation_2(list<Constraint>::const_iterator first,
                                   list<Constraint>::const_iterator last,
                                   T& t=T() )
     : CGAL_Triangulation_2<T>(t)
  {
      list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,t);
      init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // LIST_H
  
  #if defined(VECTOR_H) || defined(__SGI_STL_VECTOR_H)
  CGAL_Constrained_triangulation_2(vector<Constraint>::const_iterator first,
                                   vector<Constraint>::const_iterator last,
                                   T& t=T())
      : CGAL_Triangulation_2<T>(t)
  {
      list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,t);
      init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // VECTOR_H
  
  #ifdef ITERATOR_H
  CGAL_Constrained_triangulation_2(istream_iterator<Constraint, ptrdiff_t> first,
                                   istream_iterator<Constraint, ptrdiff_t> last,
                                   T& t=T())
      : CGAL_Triangulation_2<T>(t)
  {
      list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,t);
      init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  #endif // ITERATOR_H
  
  CGAL_Constrained_triangulation_2(Constraint* first,
                                   Constraint* last,
                                   T& t=T())
      : CGAL_Triangulation_2<T>(t)
  {
      list<Constraint> lc;
      while(first != last){
          lc.push_back(*first); ++first;
      }
      Sweep sweep(lc,t);
      init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  
  #else
  
  template<class InputIterator>
  CGAL_Constrained_triangulation_2(InputIterator first,
                                   InputIterator last,
                                   T& t=T())
      : CGAL_Triangulation_2<T>(t)
  {
      list<Constraint> lc;
      while(first != last){
          lc.push_back(*first++);
      }
      Sweep sweep(lc,t);
      init(sweep.vertex());
      CGAL_triangulation_postcondition( is_valid() );
  }
  
  #endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  

  // private:
  // private part of class CGAL_Constrained_triangulation_2
};



template < class T >
ostream &
operator<<(ostream& os, const CGAL_Constrained_triangulation_2<T> &CT)
{
  return os << (const CGAL_Triangulation_2<T>&)CT;
}


#endif //CGAL_CONSTRAINED_TRIANGULATION_2_H

