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
// file          : include/CGAL/Range_tree_d.h
// package       : SearchStructures (2.3)
// source        : include/CGAL/Range_tree_d.h
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1998/02/03 13:15:00 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_Range_tree_d__
#define CGAL_Range_tree_d__

#include <algorithm>
#include <iterator>
#include <functional>
#include <CGAL/Tree_base.h>
#include <list>
#include <vector>

// A d-dimensional Range Tree or a multilayer tree consisting of Range 
// and other trees that are derived public 
// Tree_base<_Data, _Window, _Interface>
// can be construced within this class.
// _Data: container class which contains the d-dimensional data the tree holds.
// _Window: Query window -- a d-dimensional interval
// _Interface: Interface for the class with functions that allow to 
// access the data.
// cf. file Tree_interface.h, class point_interface for the requirements.

CGAL_BEGIN_NAMESPACE

template <class _Data, class _Window, class _Interface>
class Range_tree_d;

template <class _Data, class _Window, class _Interface>
struct range_tree_node: public tree_node_base
{
  private	:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef typename _Interface::Key Key;
  typedef  _Interface Interface;
  typedef typename tree_base< _Data,  _Window>::tree_base_type tree_base_type;
protected:
  typedef Range_tree_d< _Data,  _Window,  _Interface> rT_d;
public:
  friend rT_d;
  
  range_tree_node() 
  {
    sublayer = 0;// (tree_base_type *)0; 
  }
  
  range_tree_node( range_tree_node    * _left,
		   range_tree_node    * _right,
		   const  Data & _obj,
		   const  Key  & _key ) :
    object( _obj ), key( _key )
  {
    left_link = _left;
    right_link = _right;
    sublayer = 0;//(tree_base_type *)0; 
  }
  
  range_tree_node( range_tree_node    * _left,
		   range_tree_node    * _right,
		   const  Key  & _key ) :
    key( _key )
  {
    left_link = _left;
    right_link = _right;
    sublayer = 0;//(tree_base_type *)0; 
  }
  virtual ~range_tree_node()
  {
    if (sublayer != 0) //(tree_base_type *)
      delete sublayer;
  }
  
  Data object;
  Key key;
  tree_base_type *sublayer;
};

template <class _Data, class _Window, class _Interface>
class Range_tree_d: public tree_base< _Data,  _Window>
{
 private:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef typename _Interface::Key Key;
  typedef  _Interface Interface;
protected:
  typedef Range_tree_d< _Data,  _Window,  _Interface> rT_d;
  tree_base_type *sublayer_tree;
   _Interface interface;
  int is_build;

 
  // A vertex is of this type:
  //  struct range_tree_node;

  friend range_tree_node<_Data,_Window,_Interface>;

  typedef range_tree_node<_Data,_Window,_Interface> range_tree_node2;
  typedef range_tree_node<_Data,_Window,_Interface> *link_type;

  static link_type& left(link_type x) { 
  //  link_type left(link_type x) { 
    //    if ((*x).left_link!=0) 
      return CGAL__static_cast(link_type&, (*x).left_link);
    // return (*x).left_link;
      //return 0;
  }
  static link_type& right(link_type x) {
    // if ((*x).right_link!=0) 
      return CGAL__static_cast(link_type&, (*x).right_link);   
    //  return (*x).right_link;
      // return 0; 
  }

  static link_type& parent(link_type x) {
    //if ((*x).parent_link!=0) 
      return CGAL__static_cast(link_type&, (*x).parent_link);
    // return (*x).parent_link;
      //return 0;
  }

  link_type header;
  link_type node;
  link_type rightmost(){return right(header);}
  link_type leftmost(){return left(header);}
  link_type root(){
    if(header!=0) //TREE_BASE_NULL
      return CGAL__static_cast(link_type&, header->parent_link);
    // return parent(header);
    else 
      return 0; //TREE_BASE_NULL
  }

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
  void dynamic_merge(std::list<Data>::iterator & first, std::list<Data>::iterator & last)
  {
    std::list<Data>::iterator prev, current=first;
    std::list<Data>::iterator current_first, current_middle, current_last;

    std::list<std::list<Data>::iterator> startpoints, tmp_startpoints;
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
	std::inplace_merge(current_first, current_middle, current_last, 
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

  void dynamic_merge(std::vector<Data>::iterator & first, 
		     std::vector<Data>::iterator & last)
  {
    std::vector<Data>::iterator prev, current=first;
    std::vector<Data>::iterator current_first, current_middle, current_last;

    std::list<std::vector<Data>::iterator> startpoints, tmp_startpoints;
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
	std::inplace_merge(current_first, current_middle, current_last, 
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

    std::list<Data *> startpoints, tmp_startpoints;
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
	std::inplace_merge(current_first, current_middle, current_last, 
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
			std::list<Data>::iterator& current, 
			std::list<Data>::iterator& last,
			std::list<Data>::iterator& sublevel_first,
			std::list<Data>::iterator& sublevel_last)
  {
    // only two elements ==> two leaves and a parent is constructed
    if (n==2)
    {
      sublevel_first = current;

      link_type  vleft = new range_tree_node2( 0, 0,
                                  (*current), interface.get_key(*current) ); 
      //CGAL_NIL CGAL_NIL first two arguments
      CGAL_Tree_assertion( vleft != 0); //TREE_BASE_NULL

      ++current;
      link_type  vright = new range_tree_node2( 0,0,
                                  (*current), interface.get_key(*current) ); 
      //CGAL_NIL CGAL_NIL first two arguments
      CGAL_Tree_assertion( vright != 0); //TREE_BASE_NULL
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node2( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != 0); //TREE_BASE_NULL

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == 0) //TREE_BASE_NULL
	leftmostlink = leftchild;

      tree_base_type *g = sublayer_tree->clone();
      
      std::list<Data>::iterator sub_first = sublevel_first;
      std::list<Data>::iterator sub_last = sublevel_last;
   
      g->make_tree(sub_first, sub_last);
      
      vparent->sublayer= g;
    }
    else
      // only one element ==> one leaf is constructed
      if(n==1)
      {
	sublevel_first = current;
	link_type vright = new range_tree_node2( 0, 0,
	                           (*current), interface.get_key(*current) );
	//CGAL_NIL CGAL_NIL first two arguments
        CGAL_Tree_assertion( vright != 0); //CGAL_NIL
	current++;
	sublevel_last = current;
	prevchild = vright;
	rightchild = vright;
      }
      else
      {
	// recursiv call for the construction. the interval is devided.
	std::list<Data>::iterator sublevel_left, sublevel_right;
	build_range_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, last, 
			 sublevel_first, sublevel_left);
	link_type vparent = new range_tree_node2( prevchild, 0,
                                        rightchild->key );
	//CGAL_NIL argument
        CGAL_Tree_assertion( vparent != 0); //TREE_BASE_NULL

	prevchild->parent_link = vparent;

	build_range_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, 
			 last, sublevel_right, sublevel_last);
	vparent->right_link = prevchild;
	prevchild->parent_link = vparent;
	prevchild = vparent;
	tree_base_type *g = sublayer_tree->clone();
	std::list<Data>::iterator sub_first = sublevel_first;
	std::list<Data>::iterator sub_last = sublevel_last;
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
			std::vector<Data>::iterator& current, 
			std::vector<Data>::iterator& last,
			std::vector<Data>::iterator& sublevel_first,
			std::vector<Data>::iterator& sublevel_last)
  {
    // only two elements ==> two leaves and a parent is constructed
    if (n==2)
    {
      sublevel_first = current;

      link_type  vleft = new range_tree_node2( 0, 0,
                                  (*current), interface.get_key(*current) ); 
      // CGAL_NIL arguments
      CGAL_Tree_assertion( vleft != 0);       // CGAL_NIL arguments

      ++current;
      link_type  vright = new range_tree_node2( 0,0,
                                  (*current), interface.get_key(*current) ); 
      // CGAL_NIL arguments
      CGAL_Tree_assertion( vright != 0);       // CGAL_NIL arguments
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node2( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != 0);       // CGAL_NIL arguments

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == 0) //TREE_BASE_NULL
	leftmostlink = leftchild;

      tree_base_type *g = sublayer_tree->clone();
      
      std::vector<Data>::iterator sub_first = sublevel_first;
      std::vector<Data>::iterator sub_last = sublevel_last;
   
      g->make_tree((std::vector<Data>::iterator&)sub_first, 
		   (std::vector<Data>::iterator&)sub_last);
      
      vparent->sublayer= g;
    }
    else
      // only one element ==> one leaf is constructed
      if(n==1)
      {
	sublevel_first = current;
	link_type vright = new range_tree_node2( 0, 0,
	                           (*current), interface.get_key(*current) );
	// CGAL_NIL arguments
        CGAL_Tree_assertion( vright != 0);      // CGAL_NIL arguments
	current++;
	sublevel_last = current;
	prevchild = vright;
	rightchild = vright;
      }
      else
      {
	// recursiv call for the construction. the interval is devided.
	std::vector<Data>::iterator sublevel_left, sublevel_right;
	build_range_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, last, 
			 (std::vector<Data>::iterator&)sublevel_first, 
			 (std::vector<Data>::iterator&)sublevel_left);
	link_type vparent = new range_tree_node2( prevchild, 0,
                                        rightchild->key );
	//TREE_BASE_NULL argument
        CGAL_Tree_assertion( vparent != 0);

	prevchild->parent_link = vparent;

	build_range_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, current, 
			 last, (std::vector<Data>::iterator&)sublevel_right, 
			 (std::vector<Data>::iterator&)sublevel_last);
	vparent->right_link = prevchild;
	prevchild->parent_link = vparent;
	prevchild = vparent;
	tree_base_type *g = sublayer_tree->clone();
        std::vector<Data>::iterator sub_first = sublevel_first;
	std::vector<Data>::iterator sub_last = sublevel_last;
	g->make_tree((std::vector<Data>::iterator&)sub_first, 
		     (std::vector<Data>::iterator&)sub_last);
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

      link_type  vleft = new range_tree_node2( 0, 0,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vleft != 0);

      ++current;
      link_type  vright = new range_tree_node2( 0, 0,
                                  (*current), interface.get_key(*current) ); 
      CGAL_Tree_assertion( vright != 0);
      current++;
      sublevel_last = current;

      link_type  vparent = new range_tree_node2( vleft, vright, vleft->key );
      CGAL_Tree_assertion( vparent != 0);

      vleft->parent_link = vparent;
      vright->parent_link = vparent;
      leftchild = vleft;
      rightchild = vright;
      prevchild = vparent;
      if ( leftmostlink == 0) //TREE_BASE_NULL
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
	link_type vright = new range_tree_node2( 0, 0,
	                           (*current), interface.get_key(*current) );
        CGAL_Tree_assertion( vright !=0 );
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
	link_type vparent = new range_tree_node2( prevchild, 0,
                                        rightchild->key );
        CGAL_Tree_assertion( vparent != 0);

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
    if (v->left_link != 0) //TREE_BASE_NULL
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

    while(v->left_link!=0) //TREE_BASE_NULL
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
    if(left(v)!=0) //TREE_BASE_NULL
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
#endif
  void report_subtree(link_type v, 
		      std::back_insert_iterator<std::vector< _Data> > result)
  {
    if(left(v)!=0) //TREE_BASE_NULL
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
  void report_subtree(link_type v, std::back_insert_iterator<std::list< _Data> > result)
  {
    if(left(v)!=0) //TREE_BASE_NULL
    {
      report_subtree(left(v), result);
      report_subtree(right(v), result);
    }
    else
      (*result++)=v->object;
  }
#ifdef ostreamiterator
  void report_subtree(link_type v, std::ostream_iterator< _Data> result)
  {
    if(left(v)!=0) //TREE_BASE_NULL
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
    if (v->sublayer != 0) //(tree_base_type *)
    {
      tree_base_type *T= v->sublayer;
      if(!(*T).is_valid())
	return false;
    }
    if(left(v)!=0) //TREE_BASE_NULL
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
  Range_tree_d(Range_tree_d const &fact, bool):
    sublayer_tree(fact.sublayer_tree->clone()), is_build(false)
  {
    header = 0; //TREE_BASE_NULL
  }

  // construction of a tree
  Range_tree_d(tree_base_type const &fact):
    sublayer_tree(fact.clone()), is_build(false)
  {
    header = 0; //TREE_BASE_NULL
  }

  // destruction
  virtual ~Range_tree_d()
  {
    link_type v=root();   

    if (v!=0)
      delete_tree(v);
      if (header!=0)
      	delete header;
      if (sublayer_tree!=0)
      	delete sublayer_tree;
  }


 // a prototype of the tree is returned
  tree_base_type *clone() const 
  { 
    return new Range_tree_d(*this, true); 
  }
  

  // the tree is build according to the input elements in [first,last)
  bool make_tree(std::list<Data>::iterator& first, 
		 std::list<Data>::iterator& last)
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
    
    leftmostlink = 0; //TREE_BASE_NULL
    std::list<Data>::iterator sublevel_first, sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     sublevel_first, sublevel_last);
    
    header = new range_tree_node2();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    return true;
  }

#ifdef stlvector
  // the tree is build according to the input elements in [first,last)
  bool make_tree(std::vector<Data>::iterator& first, 
		 std::vector<Data>::iterator& last)
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

    dynamic_merge((std::vector<Data>::iterator&)first, 
		  (std::vector<Data>::iterator&)last);
    
    leftmostlink = 0; //TREE_BASE_NULL
    std::vector<Data>::iterator sublevel_first, sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     (std::vector<Data>::iterator&)sublevel_first, 
		     (std::vector<Data>::iterator&)sublevel_last);
    
    header = new range_tree_node2();
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
    
    leftmostlink = 0; //TREE_BASE_NULL
    Data * sublevel_first;
    Data * sublevel_last;
    
    build_range_tree(n, leftchild, rightchild, prevchild, 
		     leftmostlink, first, last, 
		     sublevel_first, sublevel_last);
    
    header = new range_tree_node2();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    return true;
  }
#endif
  
  // all elements that ly in win are inserted in result
  std::back_insert_iterator<std::list< _Data> > window_query( _Window const &win,  
			     std::back_insert_iterator<std::list< _Data> > result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
       return result;
    if(root()==0) //TREE_BASE_NULL
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==0) //TREE_BASE_NULL
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=0) //TREE_BASE_NULL
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=0) //TREE_BASE_NULL
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
      while(right(v)!=0) //TREE_BASE_NULL
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=0) //TREE_BASE_NULL
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
   std::back_insert_iterator<std::vector< _Data> >  window_query( _Window const &win,  
			       std::back_insert_iterator<std::vector< _Data> > result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
       return result;
    if(root()==0) //TREE_BASE_NULL
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==0) //TREE_BASE_NULL
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=0) //TREE_BASE_NULL
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=0) //TREE_BASE_NULL
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
      while(right(v)!=0) //TREE_BASE_NULL
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=0) //TREE_BASE_NULL
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
    if(root()==0) //TREE_BASE_NULL
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==0) //TREE_BASE_NULL
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=0) //TREE_BASE_NULL
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=0) //TREE_BASE_NULL
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
      while(right(v)!=0) //TREE_BASE_NULL
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	   //half open interval
	{
	  if(left(left(v))!=0) //TREE_BASE_NULL
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
  std::ostream_iterator< _Data> window_query( _Window const &win,  
				       std::ostream_iterator< _Data>& result)
  {
    if(is_less_equal(interface.get_right(win), interface.get_left(win)))
      return result;
    if(root()==0) //TREE_BASE_NULL
      return result;
    link_type split_node = findSplitNode(win);
    if(left(split_node)==0) //TREE_BASE_NULL
    {
      if(is_inside(win,split_node->object))
	(*result++)=split_node->object;
    }	  
    else
    {
      link_type v = (link_type)(*split_node).left_link;

      while(left(v)!=0) //TREE_BASE_NULL
      {
	if(is_less_equal(interface.get_left(win),v->key))
	{
	  link_type w = right(v);
	  if(left(w)!=0) //TREE_BASE_NULL
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
      while(right(v)!=0) //TREE_BASE_NULL
      {
//	if(is_less_equal(v->key, interface.get_right(win))) closed interval
	if(interface.comp(v->key, interface.get_right(win))) 
	  //half open interval
	{
	  if(left(left(v))!=0) //TREE_BASE_NULL
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
   std::back_insert_iterator<std::list< _Data> > enclosing_query(  _Window const &win,  
				 std::back_insert_iterator<std::list< _Data> > result)
  {
    return window_query(win, result);
  }

  // a window query is performed 
  std::back_insert_iterator<std::vector< _Data> > enclosing_query( _Window const &win,  
			       std::back_insert_iterator<std::vector< _Data> > result)
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
  std::ostream_iterator< _Data>  enclosing_query( _Window const &win,  
				std::ostream_iterator< _Data> result)
  {
    return window_query(win, result);
  }
#endif

  bool is_valid()
  {
    link_type u,v,w;
    u=v=w=root();
    if(v!=0) //TREE_BASE_NULL
      return is_valid(u, v, w);
    return true;
  }
};

CGAL_END_NAMESPACE
#endif /* RANGE_TREE_H */
