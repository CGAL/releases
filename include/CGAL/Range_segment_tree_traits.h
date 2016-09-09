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
// file          : include/CGAL/Range_segment_tree_traits.h
// package       : SearchStructures (2.3)
// source        : include/CGAL/Range_segment_tree_traits.h
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/02/03 13:14:57 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef __CGAL_Range_segment_tree_traits__
#define __CGAL_Range_segment_tree_traits__

#include <CGAL/Point_2.h>
#include <CGAL/Point_3.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicates_on_points_3.h>
#include <utility>

CGAL_BEGIN_NAMESPACE

template <class Rep, class T>
class Range_tree_map_traits_2{
 public:
  typedef   T Value;
  typedef Point_2< Rep> Pure_key;
  typedef std::pair<Pure_key,  T> Key;
  typedef Point_2< Rep> Key_1;
  typedef Point_2< Rep> Key_2;
  typedef std::pair<Pure_key, Pure_key> Interval;
  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)

    { return i.second;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.first;}
  };

  
  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;

};

template <class Rep, class T>
class Range_tree_map_traits_3{
 public:
  typedef std::pair<Point_3< Rep>, T> Key;
  typedef Point_3< Rep> Pure_key;
  typedef Point_3< Rep> Key_1;
  typedef Point_3< Rep> Key_2;
  typedef Point_3< Rep> Key_3;
  typedef std::pair<Key,Key> Interval;

  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.first;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.first;}
  };

  class T_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second.first;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.first;}
  };

  class T_Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k.first;}
  };
  
  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(SMALLER == (int)compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };
  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Compare_3 compare_3;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;
  typedef T_Low_3 low_3;
  typedef T_High_3 high_3;
  typedef T_Key_3 key_3;
};



template <class Rep, class T>
class Segment_tree_map_traits_2{
 public:
  typedef  T Value;
  typedef Point_2< Rep> Key;
  typedef Point_2< Rep> Key_1;
  typedef Point_2< Rep> Key_2;
  typedef std::pair<Key,Key> Pure_interval;
  typedef std::pair<Pure_interval, T> Interval;
  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.second;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;

};


template <class Rep, class T>
class Segment_tree_map_traits_3{
 public:
  typedef Point_3< Rep> Key;
  typedef Point_3< Rep> Key_1;
  typedef Point_3< Rep> Key_2;
  typedef Point_3< Rep> Key_3;
  typedef std::pair<Key,Key> Pure_interval;
  typedef std::pair<Pure_interval,T> Interval;

  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.second;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

  class T_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

  class T_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.second;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class T_Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k;}
  };
  
  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(SMALLER == (int)compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };
  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Compare_3 compare_3;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;
  typedef T_Low_3 low_3;
  typedef T_High_3 high_3;
  typedef T_Key_3 key_3;
};



template <class Rep>
class Range_segment_tree_set_traits_3{
 public:
  typedef Point_3< Rep> Key;
  typedef Point_3< Rep> Key_1;
  typedef Point_3< Rep> Key_2;
  typedef Point_3< Rep> Key_3;
  typedef std::pair<Key,Key> Interval;

  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class T_Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k;}
  };
  
  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(SMALLER == (int)compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Compare_3 compare_3;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;
  typedef T_Low_3 low_3;
  typedef T_High_3 high_3;
  typedef T_Key_3 key_3;

};



template <class Rep>
class Range_segment_tree_set_traits_2{
 public:
  typedef Point_2< Rep> Key;
  typedef Point_2< Rep> Key_1;
  typedef Point_2< Rep> Key_2;
  typedef std::pair<Key,Key> Interval;

  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second;}
  };

  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };
  
  class T_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class T_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef T_Compare_1 compare_1;
  typedef T_Compare_2 compare_2;
  typedef T_Low_1 low_1;
  typedef T_High_1 high_1;
  typedef T_Key_1 key_1;
  typedef T_Low_2 low_2;
  typedef T_High_2 high_2;
  typedef T_Key_2 key_2;

};



CGAL_END_NAMESPACE
#endif




