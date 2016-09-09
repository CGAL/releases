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
// file          : include/CGAL/Triangulation_iterators_2.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: Triangulation_iterators_2.h,v $
// revision      : $Revision: 1.27 $
// revision_date : $Date: 2002/03/01 09:20:58 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_ITERATORS_2_H
#define CGAL_TRIANGULATION_ITERATORS_2_H

#include <utility>
#include <iterator>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_ds_iterators_2.h>

CGAL_BEGIN_NAMESPACE

template < class Triangulation>
class Triangulation_finite_faces_iterator_2
 : public Filter_iterator< typename Triangulation::All_faces_iterator, 
                           typename Triangulation::Infinite_tester >
{
public:
  typedef typename Triangulation::All_faces_iterator        All_faces_iterator;
  typedef typename Triangulation::Infinite_tester           Infinite_tester;
  typedef Filter_iterator<All_faces_iterator,Infinite_tester>  Base;
  typedef Triangulation_finite_faces_iterator_2<Triangulation> Self;
  typedef typename Triangulation::Face_handle               Face_handle;
  
  Triangulation_finite_faces_iterator_2()    : Base() {}

  Triangulation_finite_faces_iterator_2(const Triangulation* tr)
    : Base( filter_iterator(tr->all_faces_begin(), 
			    tr->all_faces_end(),
			    tr->infinite_tester())) {}

  Triangulation_finite_faces_iterator_2(const Triangulation* tr, int)
    : Base( filter_iterator(tr->all_faces_begin(), 
			    tr->all_faces_end(),
			    tr->infinite_tester(),
			    tr->all_faces_end())) {}

  operator Face_handle() const {return (*this)->handle();}
  Self&  operator++() { Base::operator++(); return *this;}
  Self&  operator--() { Base::operator--(); return *this; }
  Self   operator++(int) { Self tmp(*this); ++(*this); return tmp; }
  Self   operator--(int) { Self tmp(*this); --(*this); return tmp; }
};


template < class Triangulation>
class Triangulation_finite_vertices_iterator_2
 : public Filter_iterator< typename Triangulation::All_vertices_iterator, 
                           typename Triangulation::Infinite_tester >
{
public:
  typedef typename Triangulation::All_vertices_iterator All_vertices_iterator;
  typedef typename Triangulation::Infinite_tester       Infinite_tester;
  typedef Filter_iterator<All_vertices_iterator,Infinite_tester>  Base;
  typedef Triangulation_finite_vertices_iterator_2<Triangulation> Self;
  typedef typename Triangulation::Vertex_handle         Vertex_handle;

  Triangulation_finite_vertices_iterator_2()    :  Base() {}
           
  Triangulation_finite_vertices_iterator_2(const Triangulation *tr)
    : Base( filter_iterator(tr->all_vertices_begin(), 
			    tr->all_vertices_end(),
			    tr->infinite_tester())) {}
    
  Triangulation_finite_vertices_iterator_2(const Triangulation *tr, int )
    : Base( filter_iterator(tr->all_vertices_begin(), 
			    tr->all_vertices_end(),
			    tr->infinite_tester(),
			    tr->all_vertices_end())) {}
			    
  operator Vertex_handle() const {return (*this)->handle();}  
  Self&  operator++() { Base::operator++(); return *this;}
  Self&  operator--() { Base::operator--(); return *this;}
  Self   operator++(int) { Self tmp(*this); ++(*this); return tmp; }
  Self   operator--(int) { Self tmp(*this); --(*this); return tmp; }

};  



CGAL_END_NAMESPACE


#endif //CGAL_TRIANGULATION_ITERATORS_2_H
