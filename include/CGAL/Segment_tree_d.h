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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Segment_tree_d.h
// package       : Range_segment_trees (1.9)
// source        : include/CGAL/Segment_tree_d.h
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/02/03 13:15:11 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_Segment_tree_d__
#define CGAL_Segment_tree_d__

#include <iostream.h>
#include <iterator.h>
#include <algo.h>
#include <list.h>
#include <vector.h>
#include <CGAL/Tree_base.h>

// A d-dimensional Segment Tree or a multilayer tree consisting of a Segment
// and other trees that are derived public CGAL_Tree_base<_Data, _Window, 
// _Interface> can be constructed within this class.
// _Data: container class which contains the d-dimensional data the tree holds.
// _Window: Query window -- a d-dimensional interval
// _Interface: Interface for the class with functions that allow to access the 
//             data. cf. file _interface.h for the requirements.

template <class _Data, class _Window, class _Interface>
class CGAL_Segment_tree_d: public CGAL_tree_base< _Data,  _Window>
{
private:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef  typename _Interface::Key Key;
  typedef  _Interface Interface;
protected:
  typedef CGAL_Segment_tree_d< _Data,  _Window,  _Interface> sT_d;
  tree_base_type *sublayer_tree; 

  // type of a vertex
  struct segment_tree_node;
friend segment_tree_node;
  struct segment_tree_node: public CGAL_tree_node_base{
friend sT_d;
    list< _Data> objects;
    Key left_key;
    Key right_key;
    tree_base_type *sublayer;
  public:
    segment_tree_node(){
      sublayer = (tree_base_type *)0;
      left_link = CGAL__NIL;
      right_link = CGAL__NIL;
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
      sublayer = (tree_base_type *)0; 
    } 

    ~segment_tree_node(){
      objects.erase(objects.begin(), objects.end());
      if (sublayer != (tree_base_type *)0)
	delete sublayer;
    }
  };

  _Interface interface;
  bool is_build;

  typedef segment_tree_node *link_type;  

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
  link_type root(){if(header!=CGAL__NIL)
		     return parent(header);
                   else return CGAL__NIL;}
  
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
	|| left(v)==CGAL__NIL)
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
     if(left(v)!=CGAL__NIL)
     {
       build_next_dimension(left(v));
       build_next_dimension(right(v));
     }
     if(v->objects.size()>0)
     {
       list< _Data>::iterator sub_first = v->objects.begin();
       list< _Data>::iterator sub_last = v->objects.end();

       tree_base_type *g = sublayer_tree->clone();
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
       link_type vleft = new segment_tree_node
	 (CGAL__NIL, CGAL__NIL, keys[index], keys[index+1]);
       index++;
       if(index+1>last)
       {
         vright = new segment_tree_node
	   (CGAL__NIL, CGAL__NIL, keys[index], keys[index]);
       }
       else
       {
	 vright = new segment_tree_node
	   (CGAL__NIL, CGAL__NIL, keys[index], keys[index+1]);
       }
       index++;
       link_type vparent = new segment_tree_node
	 (vleft, vright, vleft->left_key, vright->right_key);

       vleft->parent_link = vparent;
       vright->parent_link = vparent;
       leftchild = vleft;
       rightchild = vright;
       prevchild = vparent;
       if(leftmostlink == CGAL__NIL)
	 leftmostlink = leftchild;
     }
     else
       // only one element ==> one leaf is constructed
       if(n==1)
       {
	 link_type vright;
	 if(index+1 > last){
	   vright = new segment_tree_node
	     (CGAL__NIL, CGAL__NIL, keys[index], keys[index]);
	 }
	 else{
	   vright = new segment_tree_node
	     (CGAL__NIL, CGAL__NIL, keys[index], keys[index+1]);
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
	 link_type vparent = new segment_tree_node
	   (prevchild, CGAL__NIL, prevchild->left_key, prevchild->left_key);
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
    if(v->left_link!=CGAL__NIL)
    { 
      delete_tree(left(v));
      delete_tree(right(v));
    }
    delete v;
  }	    


  // all elements that contain win are inserted into result
   back_insert_iterator<list< _Data> > enclosing_query( _Window const &win,
			        back_insert_iterator<list< _Data> > result,
				         		      link_type v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       list< _Data> tmp_result;
       back_insert_iterator<list< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).enclosing_query(win, tmp_back_inserter);
       list<  _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
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
  // all elements that contain win are inserted into result
   back_insert_iterator<vector< _Data> > enclosing_query( _Window const &win,
				back_insert_iterator<vector< _Data> > result,
							link_type v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       vector< _Data> tmp_result;
       back_insert_iterator<vector< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).enclosing_query(win, tmp_back_inserter);
       vector< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
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



#ifdef carray
  // all elements that contain win are inserted into result
    _Data * enclosing_query( _Window const &win,
			    _Data *result,
			   link_type v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       list< _Data> tmp_result;
       back_insert_iterator<list< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).enclosing_query(win, tmp_back_inserter);
       list< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
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

#endif
#ifdef ostreamiterator
  // all elements that contain win are inserted into result
  ostream_iterator< _Data> enclosing_query( _Window const &win,
					  ostream_iterator< _Data> result,
					  link_type v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       vector< _Data> tmp_result;
       back_insert_iterator<vector< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).enclosing_query(win, tmp_back_inserter);
       vector< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
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
#endif


  // all elements that habe non empty intersection with win are put into result
   back_insert_iterator<list< _Data> > window_query( _Window const &win,
			     back_insert_iterator<list< _Data> > result,
						   link_type& v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) || 
	is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       list< _Data> tmp_result;
       back_insert_iterator<list< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).window_query(win, tmp_back_inserter);
       list< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
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
  // all elements that habe non empty intersection with win are put into result
   back_insert_iterator<vector< _Data> > window_query( _Window const &win,
			     back_insert_iterator<vector< _Data> > result,
						     link_type& v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) || 
	is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       vector< _Data> tmp_result;
       back_insert_iterator<vector< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).window_query(win, tmp_back_inserter);
       vector< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
	 while (j!= v->objects.end())
	 {
	   if(interface.comp(interface.get_left(*j), 
			     interface.get_left_win(win)))
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

#ifdef carray
  // all elements that habe non empty intersection with win are put into result
     _Data * window_query( _Window const &win,
			   _Data *result,
			   link_type& v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) || 
	is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       list< _Data> tmp_result;
       back_insert_iterator<list< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).window_query(win, tmp_back_inserter);
       list< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
	 while (j!= v->objects.end())
	 {
	   if(interface.comp(interface.get_left(*j), 
			     interface.get_left_win(win)))
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
#endif

#ifdef ostreamiterator
  // all elements that habe non empty intersection with win are put into result
    ostream_iterator< _Data> window_query( _Window const &win,
					 ostream_iterator< _Data> result,
					 link_type& v)
   {
     if(is_less_equal(interface.get_right_win(win), (*v).left_key) 
	|| is_less_equal((*v).right_key,interface.get_left_win(win)))
       return result;
     if (v->sublayer!=(tree_base_type *)0 && (!v->sublayer->is_anchor()))
     {
       tree_base_type *T = v->sublayer;

       vector< _Data> tmp_result;
       back_insert_iterator<vector< _Data> > tmp_back_inserter = 
	 back_inserter(tmp_result);
       (*T).window_query(win, tmp_back_inserter);
       vector< _Data>::iterator tmp = tmp_result.begin();
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
	 list< _Data>::iterator j=v->objects.begin();
	 while (j!= v->objects.end())
	 {
	   if(interface.comp(interface.get_left(*j), 
			     interface.get_left_win(win)))
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
#endif

  
  bool is_valid(link_type& v)
  {
    if (v->sublayer != (tree_base_type *)0)
    {
      tree_base_type *T=v->sublayer;
      if(! (*T).is_valid())
	return false;
    }
    if(left(v)!=CGAL__NIL)
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
      list< _Data>::iterator j=v->objects.begin();
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
  CGAL_Segment_tree_d(CGAL_Segment_tree_d const &sub_tree, bool):
    sublayer_tree(sub_tree.sublayer_tree->clone()), is_build(false)
  {
    header = CGAL__NIL;
  }

  // construction of a tree, definition of the prototype of sublayer tree
  CGAL_Segment_tree_d(tree_base_type const &sub_tree):
    sublayer_tree(sub_tree.clone()), is_build(false)
  {
    header = CGAL__NIL;
  }

  // destruction 
  ~CGAL_Segment_tree_d()
  {
    link_type v=root();
    if(v!=CGAL__NIL)
    {
      delete_tree(v);
      delete header;
      delete sublayer_tree;
    }
  }
   
  // clone creates a prototype
  tree_base_type *clone() const { 
    return new CGAL_Segment_tree_d(*this, true); }

  // the tree is build according to Data [first,last)
  bool make_tree(list< _Data>::iterator& first, list< _Data>::iterator& last)
  {
    if(!is_build)
      is_build = true;
    else
      return false;

    list< _Data>::iterator count = first;
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
    sort(&keys[0], &keys[n], interface.comp);
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
    link_type leftmostlink = CGAL__NIL;

    int *start = new int(0);
    build_segment_tree(num-1, leftchild, rightchild, prevchild, 
		      leftmostlink, *start, num-1, keys2);
    delete[] keys2;
    delete start;

    header = new segment_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    prevchild->parent_link = prevchild;
    header->left_link = leftmostlink;

    list< _Data>::iterator current = first;
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
#ifdef stlvector
  // the tree is build according to interval [first,last)
  bool make_tree(vector< _Data>::iterator& first, 
		 vector< _Data>::iterator& last)
  {
    if(!is_build)
      is_build = true;
    else
      return false;

    vector< _Data>::iterator count = first;
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
	CGAL_Tree_warning_msg(interface.comp(interface.get_left(*count),
						 interface.get_right(*count)), 
				  "invalid segment ignored");
      count++;
    }

    if(n==0)
    {
      is_build = false;
      return true;
    }
    sort(&keys[0], &keys[n], interface.comp);
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
    link_type leftmostlink = CGAL__NIL;

    int *start = new int(0);
    build_segment_tree(num-1, leftchild, rightchild, prevchild, 
		      leftmostlink, *start, num-1, keys2);
    delete[] keys2;
    delete start;

    header = new segment_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    vector< _Data>::iterator current = first;
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
#endif
#ifdef carray
  // the tree is build according to Data [first,last)
  bool make_tree( _Data *first,  _Data *last)
  {
    if(!is_build)
      is_build = true;
    else
      return false;

     _Data * count = first;
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
	CGAL_Tree_warning_msg(interface.comp(interface.get_left(*count),
						 interface.get_right(*count)), 
				  "invalid segment ignored");
      count++;
    }

    if(n==0)
    {
      is_build = false;
      return true;
    }
    sort(&keys[0], &keys[n], interface.comp);
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
    link_type leftmostlink = CGAL__NIL;

    int *start = new int(0);
    build_segment_tree(num-1, leftchild, rightchild, prevchild, 
		      leftmostlink, *start, num-1, keys2);
    delete[] keys2;
    delete start;

    header = new segment_tree_node();
    header->right_link = rightchild;
    header->parent_link = prevchild;
    header->left_link = leftmostlink;

    _Data *current = first;
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
#endif

  // all elements that ly inside win are inserted into result
  back_insert_iterator<list< _Data> > window_query( _Window const &win, 
			     back_insert_iterator<list< _Data> > result)
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
    if(v!=CGAL__NIL)
      return window_query(win, result, v);  
    return result;
  }
  // all elements that ly inside win are inserted into result
   back_insert_iterator<vector< _Data> > window_query( _Window const &win, 
                               back_insert_iterator<vector< _Data> > result)
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
    if(v!=CGAL__NIL)
      return window_query(win, result, v);  
    return result;
  }
#ifdef carray
  // all elements that ly inside win are inserted into result
   _Data * window_query( _Window const &win,  _Data *result)
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
    if(v!=CGAL__NIL)
      return window_query(win, result, v);  
    return result;
  }
#endif
#ifdef ostreamiterator
  // all elements that ly inside win are inserted into result
  ostream_iterator< _Data> window_query( _Window const &win, 
					 ostream_iterator< _Data> result)
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
    if(v!=CGAL__NIL)
      return window_query(win, result, v);  
    return result;
  }
#endif

  
  // all objects that enclose win are inserted into result
  back_insert_iterator<list< _Data> > enclosing_query( _Window const &win, 
				back_insert_iterator<list< _Data> > result)
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
    if(v!=CGAL__NIL)
      return enclosing_query(win, result, v);
    return result;
  }
  // all objects that enclose win are inserted into result
  back_insert_iterator<vector< _Data> > enclosing_query( _Window const &win, 
			        back_insert_iterator<vector< _Data> > result)
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
    if(v!=CGAL__NIL)
      return enclosing_query(win, result, v);
    return result;
  }
#ifdef ostreamiterator
  // all objects that enclose win are inserted into result
  ostream_iterator< _Data> enclosing_query( _Window const &win, 
					    ostream_iterator< _Data> result)
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
    if(v!=CGAL__NIL)
      return enclosing_query(win, result, v);
    return result;
  }
#endif

#ifdef carray
  // all objects that enclose win are inserted into result
   _Data * enclosing_query( _Window const &win,  _Data *result)
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
    if(v!=CGAL__NIL)
      return enclosing_query(win, result, v);
    return result;
  }
#endif

  bool is_valid()
  {
    link_type v= root();
    if(v!=CGAL__NIL)
      return is_valid(v);
    return true;
  }

};

#endif




