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
// file          : include/CGAL/Tree_traits.h
// package       : SearchStructures (2.3)
// source        : include/CGAL/Tree_traits.h
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/02/03 13:15:20 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef __CGAL_tree_traits__
#define __CGAL_tree_traits__

// Implementation of a minimal tree traits for CGAL trees, derived 
// from Tree_base.h
// (e.g. Range_tree_d.h and Segment_tree_d.h).
// Any other interface must at least provide the interface of this class.

CGAL_BEGIN_NAMESPACE

// Interface as it is expected for one layer of a Range Tree
template<class _Data, class _Window, class _Key,          
         class _Data_func, class _Window_left_func, 
	 class _Window_right_func, class _Compare>
class tree_point_traits{
 public:
  typedef  _Key Key;
  typedef  _Data Data;
  typedef  _Window Window;
  typedef  _Compare Compare;

   _Key get_key(const  _Data&  dt)
    const {return  _Data_func()(dt);}
   _Key get_left(const  _Window& dt)
    const {return  _Window_left_func()(dt);}
   _Key get_right(const  _Window& dt)
    const {return  _Window_right_func()(dt);}

  static bool comp( _Key const& key1,  _Key const& key2) 
  {return  _Compare()(key1, key2);} 
  static bool key_comp( _Data const& data1,  _Data const& data2)
  {
    const Key d1= _Data_func()(data1);
    const Key d2= _Data_func()(data2);
    return  _Compare()(d1,d2);
  }
};


// Interface as it is expected for one layer of a Segment Tree
template<class _Data, class _Window, class _Key,  
         class _Data_left_func, class _Data_right_func, 
	 class _Window_left_func, class _Window_right_func, class _Compare>
class tree_interval_traits{
 public:
  typedef  _Data Data;
  typedef  _Window Window;
  typedef  _Key Key;
  typedef  _Compare Compare;
  
   _Key get_left(const  _Data&  dt)
    const {return  _Data_left_func()(dt);}
   _Key get_right(const  _Data& dt)
    const {return  _Data_right_func()(dt);}
   _Key get_left_win(const  _Window& dt)
    const {return  _Window_left_func()(dt);}
   _Key get_right_win(const  _Window& dt)
    const {return  _Window_right_func()(dt);}

  static bool comp( _Key const& key1,  _Key const& key2) 
    {return  _Compare()(key1, key2);} 
};

CGAL_END_NAMESPACE
#endif



