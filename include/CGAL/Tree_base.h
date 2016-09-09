// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Tree_base.h
// author(s)     : Gabriele Neyer
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef __CGAL_Tree_base_d__
#define __CGAL_Tree_base_d__

#include <iterator.h>
#include <iostream.h>
#include <function.h>
#include <list.h>
#include <vector.h>
#include <CGAL/assertions.h>
#include <CGAL/Tree_assertions.h>

#ifndef  USE_ARGUMENT
#define  USE_ARGUMENT( X )  (void)(X);
#endif  
#ifndef  USE_VARIABLE
#define  USE_VARIABLE( X )  (void)(&(X));
#endif  

#ifndef CGAL__NIL
#define CGAL__NIL (link_type)0
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
struct CGAL_tree_node_base {
  void *parent_link;
  void *left_link;
  void *right_link;
};


// -------------------------------------------------------------------
// pure virtual abstract base class.
// Designed according to the Prototype Design Pattern 
// A tree class has to be derived from this class.

template <class _Data, class _Window>
class CGAL_tree_base
{
protected:
  typedef CGAL_tree_base<_Data, _Window> tree_base_type;

  CGAL_tree_base(CGAL_tree_base const &); // prevent access
  void operator= (CGAL_tree_base const &); // prevent access

public:
  CGAL_tree_base() {}
  virtual ~CGAL_tree_base() {}

  // 'clone()' returns an object which can be used as argument to 'delete'
  virtual tree_base_type   *clone() const = 0;

  // 'make_tree()' returns an object which can be used as argument to 'delete'
  virtual bool make_tree(list<_Data>::iterator& beg, 
			 list<_Data>::iterator& end) =0;
#ifdef stlvector
  virtual bool make_tree(vector<_Data>::iterator& beg, 
			 vector<_Data>::iterator& end) =0;
#endif
#ifdef carray
  virtual bool make_tree(_Data *beg, 
                         _Data *end) =0;
#endif
  virtual back_insert_iterator<list<_Data> > 
    window_query(_Window const &win, back_insert_iterator<
		 list<_Data> > out) = 0; 
  virtual back_insert_iterator<vector<_Data> >
    window_query(_Window const &win, back_insert_iterator<
		 vector<_Data> > out) = 0; 
#ifdef carray
  virtual _Data * window_query( _Window const &win, 
			        _Data * out) = 0; 
#endif
#ifdef ostreamiterator
  virtual ostream_iterator< _Data> window_query( _Window const &win, 
				    ostream_iterator< _Data> out) = 0; 
#endif
  virtual back_insert_iterator<list< _Data> > 
    enclosing_query( _Window const &win, back_insert_iterator<
		    list< _Data> > out) = 0; 
  virtual back_insert_iterator<vector< _Data> > 
    enclosing_query( _Window const &win, back_insert_iterator<
		    vector< _Data> > out) = 0; 
#ifdef carray
  virtual   _Data * enclosing_query( _Window const &win, 
				    _Data *out) = 0; 
#endif
#ifdef ostreamiterator
  virtual ostream_iterator< _Data> enclosing_query( _Window const &win, 
				       ostream_iterator< _Data> out) = 0; 
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
class CGAL_tree_anchor: public CGAL_tree_base< _Data,  _Window>
{
public:
  // Construct a factory with the given factory as sublayer
  CGAL_tree_anchor() {}
  virtual ~CGAL_tree_anchor(){}
  tree_base_type *clone() const { return new CGAL_tree_anchor(); }

  bool make_tree(list< _Data>::iterator& beg, 
		 list< _Data>::iterator& end) 
  {
    USE_ARGUMENT(beg);
    USE_ARGUMENT(end);
    return true;
  }
#ifdef stlvector
  bool make_tree(vector< _Data>::iterator& beg, 
		 vector< _Data>::iterator& end) 
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
   back_insert_iterator<list< _Data> > window_query( _Window const &win, 
			       back_insert_iterator<list< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
  back_insert_iterator<vector< _Data> >  window_query( _Window const &win, 
                               back_insert_iterator<vector< _Data> > out){
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
  ostream_iterator< _Data> window_query( _Window const &win, 
				       ostream_iterator< _Data> out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
#endif
  back_insert_iterator<list< _Data> > enclosing_query( _Window const &win, 
                                  back_insert_iterator<list< _Data> > out){
    USE_ARGUMENT(win);
    USE_ARGUMENT(out);
    return out;
  }
  back_insert_iterator<vector< _Data> > enclosing_query( _Window const &win, 
                                  back_insert_iterator<vector< _Data> > out){
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
  ostream_iterator< _Data> enclosing_query( _Window const &win, 
					  ostream_iterator< _Data> out){
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

// -------------------------------------------------------------------
#endif
