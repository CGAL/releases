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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Range_segment_tree_traits.h
// package       : SearchStructures (2.54)
// source        : include/CGAL/Range_segment_tree_traits.h
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/02/03 13:14:57 $
// author(s)     : Gabriele Neyer
//
// coordinator   : Peter Widmayer, ETH Zurich
//
//
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
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


template<class Key_1>
  class C_Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(SMALLER == (int)compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

template<class Key_2>
  class C_Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(SMALLER == (int)compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

template<class Key_3>
  class C_Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(SMALLER == (int)compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };


template<class Key_1,class Interval>
  class C_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

template<class Key_1,class Interval>
  class C_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

template<class Key_2,class Interval>
  class C_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };
template<class Key_2,class Interval>
  class C_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second;}
  };
template<class Key_3,class Interval>
  class C_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first;}
  };
template<class Key_3,class Interval>
  class C_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second;}
  };

template<class Key_1>
  class C_Key_1{
  public:
    Key_1 operator()(const Key_1& k)
    { return k;}
  };

 template<class Key_2>
 class C_Key_2{
  public:
    Key_2 operator()(const Key_2& k)
    { return k;}
  };


template<class Key_3>
  class C_Key_3{
  public:
    Key_3 operator()(const Key_3& k)
    { return k;}
  };


template<class Key_1,class Key>
  class T_Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

template<class Key_2,class Key>
  class T_Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.first;}
  };

 template<class Key_3,class Key>
  class T_Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k.first;}
  };



template <class Rep, class T>
class Range_tree_map_traits_2{
 public:
  typedef   T Value;
  typedef Point_2< Rep> Pure_key;
  typedef std::pair<Pure_key,  T> Key;
  typedef Point_2< Rep> Key_1;
  typedef Point_2< Rep> Key_2;
  typedef std::pair<Pure_key, Pure_key> Interval;

  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef C_Low_1<Key_1,Interval> low_1;
  typedef C_High_1<Key_1,Interval> high_1;
  typedef T_Key_1<Key_1,Key> key_1;
  typedef C_Low_2<Key_2,Interval> low_2;
  typedef C_High_2<Key_2,Interval> high_2;
  typedef T_Key_2<Key_2,Key> key_2;

};

template<class Key_1,class Interval>
  class T_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_1,class Interval>
  class T_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.first;}
  };

template<class Key_2,class Interval>
  class T_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_2,class Interval>
  class T_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.first;}
  };

template<class Key_3,class Interval>
  class T_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_3,class Interval>
  class T_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second.first;}
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

  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef C_Compare_3<Key_3> compare_3;
  typedef T_Low_1<Key_1,Interval> low_1;
  typedef T_High_1<Key_1,Interval> high_1;
  typedef T_Key_1<Key_1,Key> key_1;
  typedef T_Low_2<Key_2,Interval> low_2;
  typedef T_High_2<Key_2,Interval> high_2;
  typedef T_Key_2<Key_2,Key> key_2;
  typedef T_Low_3<Key_3,Interval> low_3;
  typedef T_High_3<Key_3,Interval> high_3;
  typedef T_Key_3<Key_3,Key> key_3;
};

template<class Key_1,class Interval>
  class S_Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_1,class Interval>
  class S_High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.second;}
  };

template<class Key_2,class Interval>
  class S_Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_2,class Interval>
  class S_High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

template<class Key_3,class Interval>
  class S_Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

template<class Key_3,class Interval>
  class S_High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.second;}
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

  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef S_Low_1<Key_1,Interval> low_1;
  typedef S_High_1<Key_1,Interval> high_1;
  typedef C_Key_1<Key_1> key_1;
  typedef S_Low_2<Key_2,Interval> low_2;
  typedef S_High_2<Key_2,Interval> high_2;
  typedef C_Key_2<Key_2> key_2;

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


  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef C_Compare_3<Key_3> compare_3;
  typedef S_Low_1<Key_1,Interval> low_1;
  typedef S_High_1<Key_1,Interval> high_1;
  typedef C_Key_1<Key_1> key_1;
  typedef S_Low_2<Key_2,Interval> low_2;
  typedef S_High_2<Key_2,Interval> high_2;
  typedef C_Key_2<Key_2> key_2;
  typedef S_Low_3<Key_3,Interval> low_3;
  typedef S_High_3<Key_3,Interval> high_3;
  typedef C_Key_3<Key_3> key_3;
};




template <class Rep>
class Range_segment_tree_set_traits_3{
 public:
  typedef Point_3< Rep> Key;
  typedef Point_3< Rep> Key_1;
  typedef Point_3< Rep> Key_2;
  typedef Point_3< Rep> Key_3;
  typedef std::pair<Key,Key> Interval;

  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef C_Compare_3<Key_3> compare_3;
  typedef C_Low_1<Key_1,Interval>  low_1;
  typedef C_High_1<Key_1,Interval>  high_1;
  typedef C_Key_1<Key_1>  key_1;
  typedef C_Low_2<Key_2,Interval>  low_2;
  typedef C_High_2<Key_2,Interval> high_2;
  typedef C_Key_2<Key_2> key_2;
  typedef C_Low_3<Key_3,Interval> low_3;
  typedef C_High_3<Key_3,Interval> high_3;
  typedef C_Key_3<Key_3> key_3;

};

  


template <class Rep>
class Range_segment_tree_set_traits_2{
 public:
  typedef Point_2< Rep> Key;
  typedef Point_2< Rep> Key_1;
  typedef Point_2< Rep> Key_2;
  typedef std::pair<Key,Key> Interval;

  typedef C_Compare_1<Key_1> compare_1;
  typedef C_Compare_2<Key_2> compare_2;
  typedef C_Low_1<Key_1,Interval> low_1;
  typedef C_High_1<Key_1,Interval> high_1;
  typedef C_Key_1<Key_1> key_1;
  typedef C_Low_2<Key_2,Interval> low_2;
  typedef C_High_2<Key_2,Interval> high_2;
  typedef C_Key_2<Key_2> key_2;

};



CGAL_END_NAMESPACE
#endif




