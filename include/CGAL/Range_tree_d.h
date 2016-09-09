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
// file          : include/CGAL/Range_tree_d.h
// package       : Range_segment_trees (1.8)
// source        : include/CGAL/Range_tree_d.h
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:15:00 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_Range_tree_d__
#define CGAL_Range_tree_d__

#include <algo.h>
#include <iterator.h>
#include <function.h>
#include <CGAL/Tree_base.h>
#include <list.h>
#include <vector.h>

// A d-dimensional Range Tree or a multilayer tree consisting of Range 
// and other trees that are derived public 
// CGAL_Tree_base<_Data, _Window, _Interface>
// can be constructed within this class.
// _Data: container class which contains the d-dimensional data the tree holds.
// _Window: Query window -- a d-dimensional interval
// _Interface: Interface for the class with functions that allow to 
// access the data.
// cf. file Tree_interface.h, class CGAL_point_interface for the requirements.


template <class _Data, class _Window, class _Interface>
class CGAL_Range_tree_d: public CGAL_tree_base< _Data,  _Window>
{
 private:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef typename _Interface::Key Key;
  typedef  _Interface Interface;
protected:
  typedef CGAL_Range_tree_d< _Data,  _Window,  _Interface> rT_d;
  tree_base_type *sublayer_tree;
   _Interface interface;
  int is_build;
 
  // A vertex is of this type:
  struct range_tree_node;

friend range_tree_node;
  struct range_tree_node: public CGAL_tree_node_base
  {
    friend rT_d;

    range_tree_node() 
    {
      sublayer = (tree_base_type *)0; 
    }

    range_tree_node( range_tree_node    * _left,
                     range_tree_node    * _right,
                     const  Data & _obj,
                     const  Key  & _key ) :
      object( _obj ), key( _key )
    {
      left_link = _left;
      right_link = _right;
      sublayer = (tree_base_type *)0; 
    }

    range_tree_node( range_tree_node    * _left,
                     range_tree_node    * _right,
                     const  Key  & _key ) :
      key( _key )
    {
      left_link = _left;
      right_link = _right;
      sublayer = (tree_base_type *)0; 
    }
    virtual ~range_tree_node()
    {
      if (sublayer != (tree_base_type *)0)
	delete sublayer;
    }

    Data object;
     Key key;
    tree_base_type *sublayer;
  };
  typedef range_tree_node *link_type;

  static link_type& left(link_type x) { 
    return CGAL__static_cast(link_type&, (*x).left_link);
  }
  static link_type& right(link_type x) {
     return CGAL__static_cast(link_type&, (*x).right_link); 
   }
  static link_type& parent(link_type x) {
    return CGAL__static_cast(link_type&, (*x).parent_link);
  }

  link_type header;
  link_type node;
  link_type rightmost(){return right(header);}
  link_type leftmost(){return left(header);}
  link_type root(){if(header!=CGAL__NIL)
		     return parent(header);
		 else return CGAL__NIL;}

  bool is_less_equal(const Key  x, const Key  y)
  {
    return (!interface.comp(y,x));
  }  
  
  // this tree is not a recursion anchor
  bool is_anchor(){return false;}

  // returns true, if the object lies inside of win
  bool is_inside( _Window const &win,  _Data const& object)
  {
    if(is_less_equal(interface.get_left(win), interface.get_key(object)) 
       && interface.comp(interface.get_key(object),interface.get_right(win)))
   //half open
//       && is_less_equal(interface.get_key(object),interface.get_right(win)))
   //closed interval
    {
      return sublayer_tree->is_inside(win,object);
    }
    else
      return false;
  }


  // merge sort algorithms that takes O(n) time if the sequence to
  // be sorted consists of two sorted subsequences.
  void dynamic_merge(list<Data>::iterator & first, list<Data>::iterator & last)
  {
    list<Data>::iterator prev, current=first;
    list<Data>::iterator current_first, current_middle, current_last;

    list<list<Data>::iterator> startpoints, tmp_startpoints;
    startpoints.push_back(current);
    prev = current++;

    while(current!=last)
    {
      if (interface.comp(interface.get_key(*current),interface.get_key(*prev)))
	startpoints.push_back(current);
      prev = current++;
    }
    while(startpoints.size()>1)
    {
      while(startpoints.size()>1)
      {
	current_first = startpoints.front();
	startpoints.erase(startpoints.begin());
	current_middle = startpoints.front();
	startpoints.erase(startpoints.begin());
	if(startpoints.size()>0)
	  current_last = startpoints.front();
	else 
	  current_last = last;
	tmp_startpoints.push_back(current_first);
	inplace_merge(current_first, current_middle, current_last, 
		      interface.key_comp);
      }
      if(startpoints.size()>0)
      {
	tmp_startpoints.push_back(startpoints.front());
	startpoints.erase(startpoints.begin());
      }
      startpoints.swap(tmp_startpoints);
    }
  }

#ifdef stlvector
  // merge sort algorithms that takes O(n) time if the sequence to
  // be sorted consists of two sorted subsequences.

  void dynamic_merge(vector<Data>::iterator & first, 
		     vector<Data>::iterator & last)
  {
    vector<Data>::iterator prev, current=first;
    vector<Data>::iterator current_first, current_middle, current_last;

    list<vector<Data>::iterator> startpoints, tmp_startpoints;
    startpoints.push_back(current);
    prev = current++;

    while(current!=last)
    {
      if (interface.comp(interface.get_key(*current), 
			 interface.get_key(*prev)))
	startpoints.push_back(current);
      prev = current++;
    }
    while(startpoints.size()>1)
    {
      while(startpoints.size()>1)
      {
	current_first = startpoints.front();
	startpoints.erase(startpoints.begin());
	current_middle = startpoints.front();
	startpoints.erase(startpoints.begin());
	if(startpoints.size()>0)
	  current_last = startpoints.front();
	else 
	  current_last = last;
	tmp_startpoints.push_back(current_first);
	inplace_merge(current_first, current_middle, current_last, 
		      interface.key_comp);
      }
      if(startpoints.size()>0)
      {
	tmp_startpoints.push_back(startpoints.front());
	startpoints.erase(startpoints.begin());
      }
      startpoints.swap(tmp_startpoints);
    }
  }
#endif
#ifdef carray
  // merge sort algorithms that takes O(n) time if the sequence to
  // be sorted consists of two sorted subsequences.
  void dynamic_merge( _Data * first,  _Data * last)
  {
    Data * prev;
    Data * current=first;
    Data * current_first;
    Data * current_middle;
    Data * current_last;

    list<Data *> startpoints, tmp_startpoints;
    startpoints.push_back(current);
    prev = current++;

    while(current!=last)
    {
      if (interface.comp(interface.get_key(*current), 
			 interface.get_key(*prev)))
	startpoints.push_back(current);
      prev = current++;
    }
    while(startpoints.size()>1)
    {
      while(startpoints.size()>1)
      {
	current_first = startpoints.front();
	startpoints.erase(startpoints.begin());
	current_middle = startpoints.front();
	startpoints.erase(startpoints.begin());
	if(startpoints.size()>0)
	  current_last = startpoints.front();
	else 
	  current_last = last;
	tmp_startpoints.push_back(current_first);
	inplace_merge(current_first, current_middle, current_last, 
		      interface.key_comp);
      }
      if(startpoints.size()>0)
      {
	tmp_startpoints.push_back(startpoints.front());
	startpoints.erase(startpoints.begin());
      }
      startpoints.swap(tmp_startpoints);
    }
  }
#endif

  // recursive function 
  // (current,last) describe an interval of length n of sorted elements,
  // for this interval a tree is build containing these elements.
  // the most left child is returend in prevchild.

  void build_range_tree(int n, link_type& leftchild, 
			link_type& rightchild,
			link_type& prevchild, 
			link_type& leftmostlink,
			list<Data>::iterator& current, 
			list<Data>::iterator& last,
			list<Data>::iterator& sublevel_first,
			list<Data>::iterator& sublevel_last)
  {
    // only two elements ==> two leaves and a parent is constructed
    if (n==2)
    {
      sublevel_first = current;

      link_type  vleft = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vleft != CGAL__NIL);

      ++current;
      link_type  vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vright != CGAL__NIL );
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != CGAL__NIL );

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == CGAL__NIL)
	leftmostlink = leftchild;

      tree_base_type *g = sublayer_tree->clone();
      
      list<Data>::iterator sub_first = sublevel_first;
      list<Data>::iterator sub_last = sublevel_last;
   
      g->make_tree(sub_first, sub_last);
      
      vparent->sublayer= g;
    }
    else
      // only one element ==> one leaf is constructed
      if(n==1)
      {
	sublevel_first = current;
	link_type vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
	                           (*current), interface.get_key(*current) );
        CGAL_Tree_assertion( vright != CGAL__NIL );
                                                ;
	current++;
	sublevel_last = current;
	prevchild = vright;
	rightchild = vright;
      }
      else
      {
	// recursiv call for the construction. the interval is devided.
	list<Data>::iterator sublevel_left, sublevel_right;
	build_range_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, last, 
			 sublevel_first, sublevel_left);
	link_type vparent = new range_tree_node( prevchild, CGAL__NIL,
                                        rightchild->key );
        CGAL_Tree_assertion( vparent != CGAL__NIL );

	prevchild->parent_link = vparent;

	build_range_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, 
			 last, sublevel_right, sublevel_last);
	vparent->right_link = prevchild;
	prevchild->parent_link = vparent;
	prevchild = vparent;
	tree_base_type *g = sublayer_tree->clone();
	list<Data>::iterator sub_first = sublevel_first;
	list<Data>::iterator sub_last = sublevel_last;
	g->make_tree(sub_first, sub_last);
	vparent->sublayer = g;
      }
  }

#ifdef stlvector
  // recursive function 
  // (current,last) describe an interval of length n of sorted elements,
  // for this interval a tree is build containing these elements.
  // the most left child is returend in prevchild.
  void build_range_tree(int n, link_type& leftchild, 
			link_type& rightchild,
			link_type& prevchild, 
			link_type& leftmostlink,
			vector<Data>::iterator& current, 
			vector<Data>::iterator& last,
			vector<Data>::iterator& sublevel_first,
			vector<Data>::iterator& sublevel_last)
  {
    // only two elements ==> two leaves and a parent is constructed
    if (n==2)
    {
      sublevel_first = current;

      link_type  vleft = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vleft != CGAL__NIL );

      ++current;
      link_type  vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vright != CGAL__NIL );
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != CGAL__NIL );

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == CGAL__NIL)
	leftmostlink = leftchild;

      tree_base_type *g = sublayer_tree->clone();
      
      vector<Data>::iterator sub_first = sublevel_first;
      vector<Data>::iterator sub_last = sublevel_last;
   
      g->make_tree((vector<Data>::iterator&)sub_first, 
		   (vector<Data>::iterator&)sub_last);
      
      vparent->sublayer= g;
    }
    else
      // only one element ==> one leaf is constructed
      if(n==1)
      {
	sublevel_first = current;
	link_type vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
	                           (*current), interface.get_key(*current) );
        CGAL_Tree_assertion( vright != CGAL__NIL );
                                                ;
	current++;
	sublevel_last = current;
	prevchild = vright;
	rightchild = vright;
      }
      else
      {
	// recursiv call for the construction. the interval is devided.
	vector<Data>::iterator sublevel_left, sublevel_right;
	build_range_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, last, 
			 (vector<Data>::iterator&)sublevel_first, 
			 (vector<Data>::iterator&)sublevel_left);
	link_type vparent = new range_tree_node( prevchild, CGAL__NIL,
                                        rightchild->key );
        CGAL_Tree_assertion( vparent != CGAL__NIL );

	prevchild->parent_link = vparent;

	build_range_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, 
			 last, (vector<Data>::iterator&)sublevel_right, 
			 (vector<Data>::iterator&)sublevel_last);
	vparent->right_link = prevchild;
	prevchild->parent_link = vparent;
	prevchild = vparent;
	tree_base_type *g = sublayer_tree->clone();
        vector<Data>::iterator sub_first = sublevel_first;
	vector<Data>::iterator sub_last = sublevel_last;
	g->make_tree((vector<Data>::iterator&)sub_first, 
		     (vector<Data>::iterator&)sub_last);
	vparent->sublayer = g;
      }
  }
#endif
#ifdef carray
  // recursive function 
  // (current,last) describe an interval of length n of sorted elements,
  // for this interval a tree is build containing these elements.
  // the most left child is returend in prevchild.
  void build_range_tree(int n, link_type& leftchild, 
			link_type& rightchild,
			link_type& prevchild, 
			link_type& leftmostlink,
			 _Data *& current, 
			 _Data *& last,
			 _Data *& sublevel_first,
			 _Data *& sublevel_last)
  {
    // only two elements ==> two leaves and a parent is constructed
    if (n==2)
    {
      sublevel_first = current;

      link_type  vleft = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vleft != CGAL__NIL );

      ++current;
      link_type  vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vright != CGAL__NIL );
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != CGAL__NIL );

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == CGAL__NIL)
	leftmostlink = leftchild;

      tree_base_type *g = sublayer_tree->clone();
      
      Data * sub_first = sublevel_first;
      Data * sub_last = sublevel_last;
   
      g->make_tree((Data *)sub_first,(Data *)sub_last);
      
      vparent->sublayer= g;
    }
    else
      // only one element ==> one leaf is constructed
      if(n==1)
      {
	sublevel_first = current;
	link_type vright = new range_tree_node( CGAL__NIL, CGAL__NIL,
	                           (*current), interface.get_key(*current) );
        CGAL_Tree_assertion( vright != CGAL__NIL );
	current++;
	sublevel_last = current;
	prevchild = vright;
	rightchild = vright;
      }
      else
      {
	// recursiv call for the construction. the interval is devided.
	Data * sublevel_left;
	Data * sublevel_right;
	
	build_range_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, last, 
			 sublevel_first, sublevel_left);
	Data * sub_first = sublevel_first;
	link_type vparent = new range_tree_node( prevchild, CGAL__NIL,
                                        rightchild->key );
        CGAL_Tree_assertion( vparent != CGAL__NIL );

	prevchild->parent_link = vparent;

	build_range_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, 
			 last, sublevel_right, sublevel_last);
	vparent->right_link = prevchild;
	prevchild->parent_link = vparent;
	prevchild = vparent;
	tree_base_type *g = sublayer_tree->clone();
	Data * sub_last = sublevel_last;
	g->make_tree((Data *)sub_first, (Data *)sub_last);
	vparent->sublayer = g;
      }
  }
#endif


  void delete_tree(link_type v)
  {
    if(v->left_link!=CGAL__NIL)
    { 
      delete_tree(left(v));
      delete_tree(right(v));
    }
    delete v;
  }	    
		    
  
  // the vertex from that the way from root to the left interval bound 
  // and the right interval bound splits.
  link_type findSplitNode(Window const &key)
  {
    link_type v = root();

    while(v->left_link!=CGAL__NIL)
    {
//      if(interface.comp(interface.get_right(key), v->key))
      if(is_less_equal(interface.get_right(key), v->key))
	v = left(v);
      else 
	if(interface.comp(v->key, interface.get_left(key)))
	  v = right(v);
	else
	  break;
    }

    return v;
  }

#ifdef carray
  void report_subtree(link_type v, _Data *result)
  {
    if(left(v)!=CGAL__NIL)
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
#endif
  void report_subtree(link_type v, 
		      back_insert_iterator<vector< _Data> > result)
  {
    if(left(v)!=CGAL__NIL)
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
  void report_subtree(link_type v, back_insert_iterator<list< _Data> > result)
  {
    if(left(v)!=CGAL__NIL)
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
#ifdef ostreamiterator
  void report_subtree(link_type v, ostream_iterator< _Data> result)
  {
    if(left(v)!=CGAL__NIL)
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
#endif


  bool is_valid(link_type& v, link_type&  leftmost_child, 
		link_type& rightmost_child)
  {
    link_type leftmost_child_l, rightmost_child_l,  leftmost_child_r, 
      rightmost_child_r;
    if (v->sublayer != (tree_base_type *)0)
    {
      tree_base_type *T= v->sublayer;
      if(!(*T).is_valid())
	return false;
    }
    if(left(v)!=CGAL__NIL)
    {
      if(!is_valid(left(v), leftmost_child_l, rightmost_child_l))
	return false;
      if(!is_valid(right(v), leftmost_child_r, rightmost_child_r))
	return false;
      if(interface.comp((*v).key, (*rightmost_child_l).key) || 
	 interface.comp((*rightmost_child_l).key, (*v).key))
	return false;
      rightmost_child = rightmost_child_r;
      leftmost_child = leftmost_child_l;
    }
    else
    {
      rightmost_child = v;
      leftmost_child = v;      
    }
    return true;
  }




public:

  // construction of a tree
  CGAL_Range_tree_d(CGAL_Range_tree_d const &fact, bool):
    sublayer_tree(fact.sublayer_tree->clone()), is_build(false)
  {
    header = CGAL__NIL;
  }

  // construction of a tree
  CGAL_Range_tree_d(tree_base_type const &fact):
    sublayer_tree(fact.clone()), is_build(false)
  {
    header = CGAL__NIL;
  }

  // destruction
  virtual ~CGAL_Range_tree_d()
  {
    link_type v=root();
    if(v!=CGAL__NIL)
    {
      delete_tree(v);
      delete header;
      delete sublayer_tree;
    }
  }


 // a prototype of the tree is returned
  tree_base_type *clone() const 
  { 
    return new CGAL_Range_tree_d(*this, true); 
  }
  

  // the tree is build according to the input elements in [first,last)
  bool make_tree(list<Data>::iterator& first, 
		 list<Data>::iterator& last)
  {
    link_type leftchild, rightchild, prevchild, leftmostlink;

    if(!is_build)
      is_build = true;
    else
      return false;

    int n = count_elements__C( first, last );
    if(n==0)
    {
      is_build = false;
      return true;
    }

    dynamic_merge(first, last);
    
    leftmostlink = CGAL__NIL;
    list<Data>::iterator sublevel_first, sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     sublevel_first, sublevel_last);
    
    header = new range_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    return true;
  }

#ifdef stlvector
  // the tree is build according to the input elements in [first,last)
  bool make_tree(vector<Data>::iterator& first, 
		 vector<Data>::iterator& last)
  {
    link_type leftchild, rightchild, prevchild, leftmostlink;

    if(!is_build)
      is_build = true;
    else
      return false;

    int n = count_elements__C( first, last );
    if(n==0)
    {
      is_build = false;
      return true;
    }

    dynamic_merge((vector<Data>::iterator&)first, 
		  (vector<Data>::iterator&)last);
    
    leftmostlink = CGAL__NIL;
    vector<Data>::iterator sublevel_first, sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     (vector<Data>::iterator&)sublevel_first, 
		     (vector<Data>::iterator&)sublevel_last);
    
    header = new range_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    return true;
  }
#endif

#ifdef carray
  // the tree is build according to the input elements in [first,last)
  bool make_tree( _Data * first, 
		  _Data * last)
  {
    link_type leftchild, rightchild, prevchild, leftmostlink;

    if(!is_build)
      is_build = true;
    else
      return false;

    int n = count_elements__C( first, last );
    if(n==0)
    {
      is_build = false;
      return true;
    }

    dynamic_merge((Data *)first, (Data *)last);
    
    leftmostlink = CGAL__NIL;
    Data * sublevel_first;
    Data * sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     sublevel_first, sublevel_last);
    
    header = new range_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    return true;
  }
#endif
  
  // all elements that ly in win are inserted in result
  back_insert_iterator<list< _Data> > window_query( _Window const &win,  
			     back_insert_iterator<list< _Data> > result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
       return result;
    if(root()==CGAL__NIL)
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==CGAL__NIL)
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=CGAL__NIL)
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=CGAL__NIL)
	  {
	    tree_base_type *T= (w)->sublayer;
	    if(T->is_anchor())
	      report_subtree(w,result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	    if(is_inside(win,w->object))
	      (*result++)=(w)->object;
	  v = left(v);
	}
	else
	  v = right(v);
      }                 // end while
      if(is_inside(win,v->object))
	(*result++)=v->object;
      v = right(split_node);
      while(right(v)!=CGAL__NIL)
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=CGAL__NIL)
	  {
	    tree_base_type *T= (left(v))->sublayer;
	    if(T->is_anchor())
	      report_subtree(left(v),result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	  {
	    if(is_inside(win,left(v)->object))
	      (*result++)=left(v)->object; 
	  }
	  v = right(v);
	}
	else
	  v = left(v);
      }//end while
      if(is_inside(win,v->object))
      {
	(*result++)=v->object; 
      }
    }
    return result;
  }
  // all elements that ly in win are inserted in result
   back_insert_iterator<vector< _Data> >  window_query( _Window const &win,  
			       back_insert_iterator<vector< _Data> > result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
       return result;
    if(root()==CGAL__NIL)
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==CGAL__NIL)
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=CGAL__NIL)
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=CGAL__NIL)
	  {
	    tree_base_type *T= (w)->sublayer;
	    if(T->is_anchor())
	      report_subtree(w,result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	    if(is_inside(win,w->object))
	      (*result++)=(w)->object;
	  v = left(v);
	}
	else
	  v = right(v);
      }                 // end while
      if(is_inside(win,v->object))
	(*result++)=v->object;
      v = right(split_node);
      while(right(v)!=CGAL__NIL)
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=CGAL__NIL)
	  {
	    tree_base_type *T= (left(v))->sublayer;
	    if(T->is_anchor())
	      report_subtree(left(v),result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	  {
	    if(is_inside(win,left(v)->object))
	      (*result++)=left(v)->object; 
	  }
	  v = right(v);
	}
	else
	  v = left(v);
      }//end while
      if(is_inside(win,v->object))
      {
	(*result++)=v->object; 
      }
    }
    return result;
  }

#ifdef carray
  // all elements that ly in win are inserted in result
   _Data * window_query( _Window const &win,  
				 _Data * result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
       return result;
    if(root()==CGAL__NIL)
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==CGAL__NIL)
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=CGAL__NIL)
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=CGAL__NIL)
	  {
	    tree_base_type *T= (w)->sublayer;
	    if(T->is_anchor())
	      report_subtree(w,result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	    if(is_inside(win,w->object))
	      (*result++)=(w)->object;
	  v = left(v);
	}
	else
	  v = right(v);
      }                 // end while
      if(is_inside(win,v->object))
	(*result++)=v->object;
      v = right(split_node);
      while(right(v)!=CGAL__NIL)
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	   //half open interval
	{
	  if(left(left(v))!=CGAL__NIL)
	  {
	    tree_base_type *T= (left(v))->sublayer;
	    if(T->is_anchor())
	      report_subtree(left(v),result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	  {
	    if(is_inside(win,left(v)->object))
	      (*result++)=left(v)->object; 
	  }
	  v = right(v);
	}
	else
	  v = left(v);
      }//end while
      if(is_inside(win,v->object))
      {
	(*result++)=v->object; 
      }
    }
    return result;
  }
#endif
#ifdef ostreamiterator
  // all elements that ly in win are inserted in result
  ostream_iterator< _Data> window_query( _Window const &win,  
				       ostream_iterator< _Data>& result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
      return result;
    if(root()==CGAL__NIL)
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==CGAL__NIL)
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=CGAL__NIL)
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=CGAL__NIL)
	  {
	    tree_base_type *T= (w)->sublayer;
	    if(T->is_anchor())
	      report_subtree(w,result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	    if(is_inside(win,w->object))
	      (*result++)=(w)->object;
	  v = left(v);
	}
	else
	  v = right(v);
      }                 // end while
      if(is_inside(win,v->object))
	(*result++)=v->object;
      v = right(split_node);
      while(right(v)!=CGAL__NIL)
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=CGAL__NIL)
	  {
	    tree_base_type *T= (left(v))->sublayer;
	    if(T->is_anchor())
	      report_subtree(left(v),result);
	    else
	      (*T).window_query(win, result);
	  }
	  else
	  {
	    if(is_inside(win,left(v)->object))
	      (*result++)=left(v)->object; 
	  }
	  v = right(v);
	}
	else
	  v = left(v);
      }//end while
      if(is_inside(win,v->object))
      {
	(*result++)=v->object; 
      }
    }
    return result;
  }
#endif

  // a window query is performed 
   back_insert_iterator<list< _Data> > enclosing_query(  _Window const &win,  
				 back_insert_iterator<list< _Data> > result)
  {
    return window_query(win, result);
  }

  // a window query is performed 
  back_insert_iterator<vector< _Data> > enclosing_query( _Window const &win,  
			       back_insert_iterator<vector< _Data> > result)
  {
    return window_query(win, result);
  }
#ifdef carray
  // a window query is performed 
   _Data *enclosing_query( _Window const &win,  
				   _Data * result)
  {
    return window_query(win, result);
  }
#endif
#ifdef ostreamiterator
  // a window query is performed 
  ostream_iterator< _Data>  enclosing_query( _Window const &win,  
				ostream_iterator< _Data> result)
  {
    return window_query(win, result);
  }
#endif

  bool is_valid()
  {
    link_type u,v,w;
    u=v=w=root();
    if(v!=CGAL__NIL)
      return is_valid(u, v, w);
    return true;
  }
};


#endif /* CGAL_RANGE_TREE_H */


