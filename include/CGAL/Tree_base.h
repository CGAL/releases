// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Tree_base.h
// package       : SearchStructures (2.3)
// source        : include/CGAL/Tree_base.h 
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:15:18 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef __CGAL_Tree_base_d__
#define __CGAL_Tree_base_d__

#include <iterator>
#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <CGAL/assertions.h>
#include <CGAL/Tree_assertions.h>

#ifndef  USE_ARGUMENT
#define  USE_ARGUMENT( X )  (void)(X);
#endif  
#ifndef  USE_VARIABLE
#define  USE_VARIABLE( X )  (void)(&(X));
#endif  

#ifndef TREE_BASE_NULL
#define TREE_BASE_NULL 0
#endif

#ifndef CGAL__static_cast
#define CGAL__static_cast(TYPE,EXPR) (TYPE)(EXPR)
#endif

#ifndef CGAL__const_cast
#define CGAL__const_cast(TYPE,EXPR) (TYPE)(EXPR)
#endif

#ifndef CGAL__reinterpret_cast
#define CGAL__reinterpret_cast(TYPE,EXPR) (TYPE)(EXPR)
#endif

//#ifndef typename
//#define typename
//#endif

#define carray

CGAL_BEGIN_NAMESPACE

template <class InIt>
int   count_elements__C( const InIt  first, const InIt  last )
{
  InIt z=first;
  int i=0;
  
  while ( z++ != last ) {  
    i++;
  }

  return  i;
}



//link type definition of an ordinary vertex of the tree
struct tree_node_base {
  void *parent_link;
  void *left_link;
  void *right_link;
  tree_node_base(){parent_link=0; left_link=0; right_link=0;}
};


// -------------------------------------------------------------------
// pure virtual abstract base class.
// Designed according to the Prototype Design Pattern 
// A tree class has to be derived from this class.

template <class _Data, class _Window>
class tree_base
{
protected:
  typedef tree_base<_Data, _Window> tree_base_type;

  tree_base(tree_base const &); // prevent access
  void operator= (tree_base const &); // prevent access

public:
  tree_base() {}
  virtual ~tree_base() {}

  // 'clone()' returns an object which can be used as argument to 'delete'
  virtual tree_base_type   *clone() const = 0;

  // 'make_tree()' returns an object which can be used as argument to 'delete'
  virtual bool make_tree(std::list<_Data>::iterator& beg, 
			 std::list<_Data>::iterator& end) =0;
#ifdef stlvector
  virtual bool make_tree(std::vector<_Data>::iterator& beg, 
			 std::vector<_Data>::iterator& end) =0;
#endif
#ifdef carray
  virtual bool make_tree(_Data *beg, 
                         _Data *end) =0;
#endif
  virtual std::back_insert_iterator<std::list<_Data> > 
    window_query(_Window const &win, std::back_insert_iterator<
		 std::list<_Data> > out) = 0; 
  virtual std::back_insert_iterator<std::vector<_Data> >
    window_query(_Window const &win, std::back_insert_iterator<
		 std::vector<_Data> > out) = 0; 
#ifdef carray
  virtual _Data * window_query( _Window const &win, 
			        _Data * out) = 0; 
#endif
#ifdef ostreamiterator
  virtual std::ostream_iterator< _Data> window_query( _Window const &win, 
				    std::ostream_iterator< _Data> out) = 0; 
#endif
  virtual std::back_insert_iterator<std::list< _Data> > 
    enclosing_query( _Window const &win, std::back_insert_iterator<
		    std::list< _Data> > out) = 0; 
  virtual std::back_insert_iterator<std::vector< _Data> > 
    enclosing_query( _Window const &win, std::back_insert_iterator<
		    std::vector< _Data> > out) = 0; 
#ifdef carray
  virtual   _Data * enclosing_query( _Window const &win, 
				    _Data *out) = 0; 
#endif
#ifdef ostreamiterator
  virtual std::ostream_iterator< _Data> enclosing_query( _Window const &win, 
				       std::ostream_iterator< _Data> out) = 0; 
#endif
  virtual bool is_inside( _Window const &win,
			  _Data const& object)=0;  
  virtual bool is_anchor()=0;
  virtual bool is_valid()=0;
};


// -------------------------------------------------------------------
// Tree Anchor: this class is used as a recursion anchor.
// The derived tree classes can be nested. Use this class as the
// most inner class. This class is doing nothin exept stopping the recursion

template <class _Data, class _Window>
class tree_anchor: public tree_base< _Data,  _Window>
{
public:
  // Construct a factory with the given factory as sublayer
  tree_anchor() {}
  virtual ~tree_anchor(){}
  tree_base_type *clone() const { return new tree_anchor(); }

  bool make_tree(std::list< _Data>::iterator& beg, 
		 std::list< _Data>::iterator& end) 
  {
    USE_ARGUMENT(beg);
    USE_ARGUMENT(end);
    return true;
  }
#ifdef stlvector
  bool make_tree(std::vector< _Data>::iterator& beg, 
		 std::vector< _Data>::iterator& end) 
  {
    USE_ARGUMENT(beg);
    USE_ARGUMENT(end);
    return true;
  }
#endif
#ifdef carray
  bool make_tree( _Data *beg, 
                  _Data *end) 
  {
    USE_ARGUMENT(beg);
    USE_ARGUMENT(end);
    return true;
  }
#endif
   std::back_insert_iterator<std::list< _Data> > window_query( _Window const &win, 
			       std::back_insert_iterator<std::list< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
  std::back_insert_iterator<std::vector< _Data> >  window_query( _Window const &win, 
                               std::back_insert_iterator<std::vector< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#ifdef carray
   _Data * window_query( _Window const &win, 
                     _Data * out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#endif
#ifdef ostreamiterator
  std::ostream_iterator< _Data> window_query( _Window const &win, 
				       std::ostream_iterator< _Data> out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#endif
  std::back_insert_iterator<std::list< _Data> > enclosing_query( _Window const &win, 
                                  std::back_insert_iterator<std::list< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
  std::back_insert_iterator<std::vector< _Data> > enclosing_query( _Window const &win, 
                                  std::back_insert_iterator<std::vector< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out); 
    return out;
  }
#ifdef carray
   _Data * enclosing_query( _Window const &win, 
                        _Data * out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#endif
#ifdef ostreamiterator
  std::ostream_iterator< _Data> enclosing_query( _Window const &win, 
					  std::ostream_iterator< _Data> out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#endif
  bool is_valid(){ return true;}

protected:

  bool is_inside( _Window const &win, 
		  _Data const& object)
  {     
    USE_ARGUMENT(win);
    USE_ARGUMENT(object);
    return true;
  }
  bool is_anchor(){return true;}
};

CGAL_END_NAMESPACE
// -------------------------------------------------------------------
#endif
