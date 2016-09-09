// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Segment_tree_d.h
// package       : SearchStructures (2.50)
// source        : include/CGAL/Segment_tree_d.h
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:15:11 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_Segment_tree_d__
#define CGAL_Segment_tree_d__

#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#include <vector>
#include <CGAL/Tree_base.h>

// A d-dimensional Segment Tree or a multilayer tree consisting of a Segment
// and other trees that are derived public Tree_base<_Data, _Window, 
// _Interface> can be constructed within this class.
// _Data: container class which contains the d-dimensional data the tree holds.
// _Window: Query window -- a d-dimensional interval
// _Interface: Interface for the class with functions that allow to access the 
//             data. cf. file _interface.h for the requirements.

CGAL_BEGIN_NAMESPACE

template <class _Data, class _Window, class _Interface>
class Segment_tree_d;

template <class _Data, class _Window, class _Interface>
struct segment_tree_node: public tree_node_base
{
  typedef  _Data Data;
  typedef  _Window Window;
  typedef typename _Interface::Key Key;
  typedef  _Interface Interface;
  typedef tree_base< _Data,  _Window> tree_base_type;
  typedef Segment_tree_d< _Data,  _Window,  _Interface> sT_d;
  std::list< _Data> objects;
  Key left_key;
  Key right_key;
  tree_base<_Data, _Window> *sublayer;
public:
  friend sT_d;
  
  segment_tree_node(){
    sublayer = 0; //(tree_base_type *)
		      left_link = TREE_BASE_NULL;
    right_link = TREE_BASE_NULL;
  }
  segment_tree_node(segment_tree_node * _left,
		    segment_tree_node * _right,
		    const Key _left_key,
		    const Key _right_key)
    {
      left_link =_left;
      right_link =_right;
      left_key = _left_key;
      right_key = _right_key;
      sublayer = 0; //(tree_base_type *) 
			} 
  
  ~segment_tree_node(){
    objects.erase(objects.begin(), objects.end());
    if (sublayer != 0)//(tree_base_type *)
			delete sublayer;
  }
};


template <class _Data, class _Window, class _Interface>
class Segment_tree_d: public tree_base< _Data,  _Window>
{
private:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef  typename _Interface::Key Key;
  typedef  _Interface Interface;
public:
  typedef tree_base<_Data, _Window> tbt;
protected:
  typedef Segment_tree_d< _Data,  _Window,  _Interface> sT_d;
  tree_base<_Data, _Window> *sublayer_tree; 
  
  // type of a vertex
  // struct segment_tree_node;
  
  friend segment_tree_node<_Data,_Window,_Interface>;
  typedef segment_tree_node<_Data,_Window,_Interface> segment_tree_node_t;
  typedef segment_tree_node<_Data,_Window,_Interface> *link_type;
  
  _Interface interface;
  bool is_build;


  bool is_less_equal(const Key x, const Key  y)
  {
    return (!interface.comp(y,x));
  }   
  
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
  link_type root(){
    if(header!=0)
      return CGAL__static_cast(link_type&, header->parent_link); 
    // return parent(header);
    else return 0;
  }
  
  // returns true, if the object lies inside of win
  bool is_inside( _Window const &win,  _Data const& object)
  {
    if(is_less_equal(interface.get_left_win(win), interface.get_left(object)) 
       && is_less_equal(interface.get_right(object),
			interface.get_right_win(win)))
    {
      return sublayer_tree->is_inside(win,object);
    }
    else
      return false;
  }

  // this tree is not a recursion anchor
  bool is_anchor()
  { return false;}  

  void insert_segment(link_type v,  _Data& element)
  {
    if ((is_less_equal(interface.get_left(element), (*v).left_key) && 
	 is_less_equal((*v).right_key, interface.get_right(element)))
	|| left(v)==TREE_BASE_NULL)
      (*v).objects.insert((*v).objects.end(), element);
    else
     {
       if (!is_less_equal((*left(v)).right_key, interface.get_left(element)))
	 insert_segment(left(v), element);
       if (!is_less_equal(interface.get_right(element), (*right(v)).left_key))
	 insert_segment(right(v), element);
     }	
   }
  
  // according to the list of elements at vertex v, a sublayer tree for these
  // elements is created.
   void build_next_dimension(link_type v)
   {
     if(left(v)!=TREE_BASE_NULL)
     {
       build_next_dimension(left(v));
       build_next_dimension(right(v));
     }
     if(v->objects.size()>0)
     {
       typename std::list< _Data>::iterator sub_first = v->objects.begin();
       typename std::list< _Data>::iterator sub_last = v->objects.end();

       tree_base<_Data, _Window> *g = sublayer_tree->clone();
       g->make_tree(sub_first, sub_last);
       v->sublayer = g;
       if (!v->sublayer->is_anchor())
       {
	 sub_first = v->objects.begin();
	 sub_last = v->objects.end();
	 v->objects.erase(sub_first, sub_last);
       }
     }
   }

  // the sceleton of the segment tree is constructed here.
   void build_segment_tree(int n, link_type& leftchild, link_type& rightchild,
		   link_type& prevchild, link_type& leftmostlink,
		   int& index, int last, Key *keys)
   { 
     // only two elements ==> two leaves and a parent is constructed
     if (n==2)
     {
       link_type vright;
       link_type vleft = new segment_tree_node_t
	 (TREE_BASE_NULL, TREE_BASE_NULL, keys[index], keys[index+1]);
       index++;
       if(index+1>last)
       {
         vright = new segment_tree_node_t
	   (TREE_BASE_NULL, TREE_BASE_NULL, keys[index], keys[index]);
       }
       else
       {
	 vright = new segment_tree_node_t
	   (TREE_BASE_NULL, TREE_BASE_NULL, keys[index], keys[index+1]);
       }
       index++;
       link_type vparent = new segment_tree_node_t
	 (vleft, vright, vleft->left_key, vright->right_key);

       vleft->parent_link = vparent;
       vright->parent_link = vparent;
       leftchild = vleft;
       rightchild = vright;
       prevchild = vparent;
       if(leftmostlink == TREE_BASE_NULL)
	 leftmostlink = leftchild;
     }
     else
       // only one element ==> one leaf is constructed
       if(n==1)
       {
	 link_type vright;
	 if(index+1 > last){
	   vright = new segment_tree_node_t
	     (TREE_BASE_NULL, TREE_BASE_NULL, keys[index], keys[index]);
	 }
	 else{
	   vright = new segment_tree_node_t
	     (TREE_BASE_NULL, TREE_BASE_NULL, keys[index], keys[index+1]);
	 }
	 index++;

	 prevchild = vright;
	 rightchild = vright;
       }
       else
       {
	 // recursiv call for the construction. the interval is devided.
	 build_segment_tree(n - (int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, index, last, keys);
	 link_type vparent = new segment_tree_node_t
	   (prevchild, TREE_BASE_NULL, prevchild->left_key, prevchild->left_key);
	 prevchild->parent_link   = vparent;
	 build_segment_tree((int)n/2, leftchild, rightchild, 
			 prevchild, leftmostlink, index, last, keys);
	 vparent->right_link = prevchild;
	 prevchild->parent_link = vparent;
	 vparent->right_key = prevchild->right_key;
	 prevchild = vparent;
       }
   }

  void delete_tree(link_type v)
  {
    if(v->left_link!=TREE_BASE_NULL)
    { 
      delete_tree(left(v));
      delete_tree(right(v));
    }
    delete v;
  }	    


  // all elements that contain win are inserted into result
  template <class A>
  inline  
  A enclosing_query( _Window const &win,
		     A result,
				         		      link_type v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=0 && (!v->sublayer->is_anchor())) //(tree_base_type *)
     {
       tree_base<_Data, _Window> *T = v->sublayer;

       std::list< _Data> tmp_result;
       std::back_insert_iterator<std::list< _Data> > tmp_back_inserter = 
	 std::back_inserter(tmp_result);
       (*T).enclosing_query(win, tmp_back_inserter);
       typename std::list<  _Data>::iterator tmp = tmp_result.begin();
       while(tmp!=tmp_result.end())
       {
	 if(is_less_equal(interface.get_left(*tmp), 
			  interface.get_left_win(win)))
	 {
	   if(is_less_equal(interface.get_right_win(win), 
			    interface.get_right(*tmp)))
	     if(is_less_equal((*v).left_key, interface.get_left_win(win)))
	       *result++=(*tmp);
	 }
	 tmp++;
       }
     }
     else
     {
       if(v->objects.size()>0)
       {
	 typename std::list< _Data>::iterator j=v->objects.begin();
	 while (j!= v->objects.end())
	 {
	   if(is_less_equal(interface.get_left(*j), 
			    interface.get_left_win(win)))
	   {
	     if(is_less_equal(interface.get_right_win(win), 
			      interface.get_right(*j)))
	       if(is_less_equal((*v).left_key, interface.get_left_win(win)))
		 *result++=(*j);
	   }
	   j++;
	 }
       }
     }
     if(left(v))
     {
       enclosing_query(win, result, left(v));
       enclosing_query(win, result, right(v));
     }
     return result;
   }


  // all elements that habe non empty intersection with win are put into result
  template <class A>
  inline 
  A window_query( _Window const &win,
		  A result,
						   link_type& v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) || 
	is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=0 && (!v->sublayer->is_anchor())) //(tree_base_type *)
     {
       tree_base<_Data, _Window> *T = v->sublayer;

       std::list< _Data> tmp_result;
       std::back_insert_iterator<std::list< _Data> > tmp_back_inserter = 
	 std::back_inserter(tmp_result);
       (*T).window_query(win, tmp_back_inserter);
       typename std::list< _Data>::iterator tmp = tmp_result.begin();
       while(tmp!=tmp_result.end())
       {
	 if(interface.comp(interface.get_left(*tmp), 
			   interface.get_left_win(win)))
	 {
	   if(is_less_equal((*v).left_key, interface.get_left_win(win))){
	     *result++=(*tmp);
	   }
	 }
	 else
	 {
	   if(is_less_equal((*v).left_key,interface.get_left(*tmp))){
	     *result++=(*tmp);
	   }
	 }
	 tmp++;
       }
     }
     else
     {
       if(v->objects.size()>0)
       {
	 typename std::list< _Data>::iterator j=v->objects.begin();
	 while (j!= v->objects.end())
	 {
	   if(interface.comp(interface.get_left(*j), interface.get_left_win(win)))
	   {
	     if(is_less_equal((*v).left_key, interface.get_left_win(win)))
	     {
	       *result++=(*j);
	     }
	   }
	   else
	     if(is_less_equal((*v).left_key,interface.get_left(*j)))
	     {
	       *result++=(*j);
	     }
	   j++;
	 }
       }
     }
     if(left(v))
     {
       window_query(win, result, left(v));
       window_query(win, result, right(v));
     }
     return result;
   }
  
  bool is_valid(link_type& v)
  {
    if (v->sublayer != 0)//(tree_base_type *)
    {
      tree_base<_Data, _Window> *T=v->sublayer;
      if(! (*T).is_valid())
	return false;
    }
    if(left(v)!=TREE_BASE_NULL)
    {
      if(!is_valid(left(v)))
	return false;
      if(!is_valid(right(v)))
	return false;
    }
    if(v->objects.size()>0)
    {
//      true falls das Object das Segment enthaelt, 
//	  der parent aber das Segmetn nicht enthaelt.
      typename std::list< _Data>::iterator j=v->objects.begin();
      link_type parent_of_v = parent(v);
      while (j!= v->objects.end())
      {
	if(!is_less_equal(interface.get_left(*j), (*v).left_key))
	  return false;
	if(!is_less_equal( (*v).right_key, interface.get_right(*j)))
	  return false;
	if (parent_of_v != root())
	  if((is_less_equal(interface.get_left(*j),(*parent_of_v).left_key))&& 
	     (is_less_equal( (*parent_of_v).right_key, 
			     interface.get_right(*j))))
	    return false;
	j++;
      }
    }
    return true;
  } 



public:

  // construction of a tree
  Segment_tree_d(Segment_tree_d const &sub_tree, bool):
    sublayer_tree(sub_tree.sublayer_tree->clone()), is_build(false)
  {
    header = TREE_BASE_NULL;
  }

  // construction of a tree, definition of the prototype of sublayer tree
  Segment_tree_d(tree_base<_Data, _Window> const &sub_tree):
    sublayer_tree(sub_tree.clone()), is_build(false)
  {
    header = TREE_BASE_NULL;
  }

  // destruction 
  ~Segment_tree_d()
  {
    link_type v=root();
    if(v!=TREE_BASE_NULL)
      delete_tree(v);
    if (header!=0)  
      delete header;
    if(sublayer_tree!=0)
      delete sublayer_tree;
  }
   
  // clone creates a prototype
  tree_base<_Data, _Window> *clone() const { 
    return new Segment_tree_d(*this, true); }

 bool make_tree(typename std::list< _Data>::iterator& beg, 
                 typename std::list< _Data>::iterator& end,
                 typename tbt::lit *dummy=0){ 
    return make_tree_impl(beg,end);
  }

  #ifdef stlvector
  bool make_tree(typename std::vector< _Data>::iterator& beg, 
                 typename std::vector< _Data>::iterator& end,
                 typename tbt::vbit *dummy=0){ 
    return make_tree_impl(beg,end);
  }
  #endif
  #ifdef carray
  bool make_tree(_Data *beg, 
                 _Data *end){
     return make_tree_impl(beg,end);
   }
  #endif

  // the tree is build according to Data [first,last)
  template<class A>
  inline 
  bool make_tree_impl(A& first,A& last)
  {
    if(!is_build)
      is_build = true;
    else
      return false;

    A count = first;
    int n=0;
    Key *keys = new Key[2*count_elements__C(first, last) + 1];
    while(count!=last)
    {
      if (interface.comp(interface.get_left(*count),
			 interface.get_right(*count)))
      { 
	keys[n++]=interface.get_left(*count);
	keys[n++]=interface.get_right(*count);
      }
      else
      {
	CGAL_Tree_warning_msg(interface.comp(interface.get_left(*count),
						 interface.get_right(*count)), 
				  "invalid segment ignored");
      }
      count++;
    }

    if(n==0)
    {
      is_build = false;
      return true;
    }
    std::sort(&keys[0], &keys[n], interface.comp);
    Key *keys2 = new Key[2*n + 1];
    int m=0;
    int num=1;
    keys2[0]=keys[0];
    for(m=1;m<n;m++)
    {
      if(interface.comp(keys[m],keys2[num-1])|| 
	 interface.comp(keys2[num-1],keys[m]))
      {
	keys2[num++]=keys[m];
      }
    }

    delete[] keys;
    link_type leftchild;
    link_type rightchild;
    link_type prevchild;
    link_type leftmostlink = TREE_BASE_NULL;

    int *start = new int(0);
    build_segment_tree(num-1, leftchild, rightchild, prevchild, 
		      leftmostlink, *start, num-1, keys2);
    delete[] keys2;
    delete start;

    header = new segment_tree_node_t();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    prevchild->parent_link = prevchild;
    header->left_link = leftmostlink;

    A current = first;
    link_type r = root();
    do
    {
      if (interface.comp(interface.get_left(*current),
			 interface.get_right(*current)))
	insert_segment(r, *current);
    }while(++current!=last);

    link_type v=root();
    build_next_dimension(v);
    return true;
  }


  std::back_insert_iterator< std::list< _Data> > window_query
          ( _Window const &win, 
            std::back_insert_iterator< std::list< _Data> > out,
            typename tbt::lbit *dummy=0){
    return window_query_impl(win,out);
  }


  std::back_insert_iterator< std::vector< _Data> > window_query
          ( _Window const &win, 
            std::back_insert_iterator< std::vector< _Data> > out,
            typename tbt::vbit *dummy=0){
    return window_query_impl(win,out);
  }
  #ifdef carray
  _Data *window_query( _Window const &win, _Data *out){
    return window_query_impl(win,out);
   }
  #endif

#ifdef ostreamiterator
  std::ostream_iterator< _Data>  window_query( _Window const &win, 
                     std::ostream_iterator< _Data> out,
                     typename tbt::oit *dummy=0){
    return window_query_impl(win,out);
  }
#endif



  // all elements that ly inside win are inserted into result
  template <class A>
  inline A window_query_impl( _Window const &win, 
			     A result,typename tbt::lbit *dummy=0)
  {
    if(is_less_equal(interface.get_right_win(win), 
		     interface.get_left_win(win)))
    { 
      CGAL_Tree_warning_msg(interface.comp(interface.get_right_win(win), 
					       interface.get_left_win(win)),
				"invalid window -- query ignored");
      return result;
    }
    link_type v = root();
    if(v!=TREE_BASE_NULL)
      return window_query(win, result, v);  
    return result;
  }

  
  std::back_insert_iterator< std::list< _Data> > enclosing_query( 
	       _Window const &win, 
               std::back_insert_iterator< std::list< _Data> > out,
               typename tbt::lbit *dummy=0){
    return enclosing_query_impl(win,out);
  }

  std::back_insert_iterator< std::vector< _Data> > enclosing_query( 
	      _Window const &win, 
              std::back_insert_iterator< std::vector< _Data> > out,
              typename tbt::vbit *dummy=0){
    return enclosing_query_impl(win,out);
  }


  #ifdef carray
  _Data *enclosing_query( _Window const &win, _Data *out){
    return enclosing_query_impl(win,out);
   }
  #endif

#ifdef ostreamiterator
  std::ostream_iterator< _Data>  enclosing_query( _Window const &win, 
                             std::ostream_iterator< _Data> out,
                             typename tbt::oit *dummy=0){
    return enclosing_query_impl(win,out);
  }
#endif



  // all objects that enclose win are inserted into result
  template <class A>
  inline
  A enclosing_query_impl( _Window const &win, 
		     A result,typename tbt::lbit *dummy=0)
  {
    if(is_less_equal(interface.get_right_win(win), 
		     interface.get_left_win(win)))
    { 
      CGAL_Tree_warning_msg(interface.comp(interface.get_right_win(win), 
					       interface.get_left_win(win)),
				"invalid window -- query ignored");
      return result;
    }
    link_type v = root();
    if(v!=TREE_BASE_NULL)
      return enclosing_query(win, result, v);
    return result;
  }

  bool is_valid()
  {
    link_type v= root();
    if(v!=TREE_BASE_NULL)
      return is_valid(v);
    return true;
  }
};
CGAL_END_NAMESPACE
#endif




