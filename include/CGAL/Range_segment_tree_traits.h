/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// file  : include/CGAL/Range_segment_tree_traits.h
// source: include/CGAL/Range_segment_tree_traits.h
// author: Gabriele Neyer
// $Revision: 1.1 $
// $Date: 1997/06/16 13:38:29 $

#ifndef __CGAL_Range_segment_tree_traits__
#define __CGAL_Range_segment_tree_traits__

#include <CGAL/Point_2.h>
#include <CGAL/Point_3.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/predicates_on_points_3.h>
#include <pair.h>

template <class Rep, class T>
class CGAL_Range_tree_map_traits_2{
 public:
  typedef T Value;
  typedef CGAL_Point_2<Rep> Pure_key;
  typedef pair<Pure_key, T> Key;
  typedef CGAL_Point_2<Rep> Key_1;
  typedef CGAL_Point_2<Rep> Key_2;
  typedef pair<Pure_key, Pure_key> Interval;
  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)

    { return i.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.first;}
  };

  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;

};

template <class Rep, class T>
class CGAL_Range_tree_map_traits_3{
 public:
  typedef pair<CGAL_Point_3<Rep>,T> Key;
  typedef CGAL_Point_3<Rep> Pure_key;
  typedef CGAL_Point_3<Rep> Key_1;
  typedef CGAL_Point_3<Rep> Key_2;
  typedef CGAL_Point_3<Rep> Key_3;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.first;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.first;}
  };

  class _Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second.first;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.first;}
  };

  class _Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k.first;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };
  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Compare_3 compare_3;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;
  typedef _Low_3 low_3;
  typedef _High_3 high_3;
  typedef _Key_3 key_3;
};



template <class Rep, class T>
class CGAL_Segment_tree_map_traits_2{
 public:
  typedef T Value;
  typedef CGAL_Point_2<Rep> Key;
  typedef CGAL_Point_2<Rep> Key_1;
  typedef CGAL_Point_2<Rep> Key_2;
  typedef pair<Key,Key> Pure_interval;
  typedef pair<Pure_interval,T> Interval;
  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;

};


template <class Rep, class T>
class CGAL_Segment_tree_map_traits_3{
 public:
  typedef CGAL_Point_3<Rep> Key;
  typedef CGAL_Point_3<Rep> Key_1;
  typedef CGAL_Point_3<Rep> Key_2;
  typedef CGAL_Point_3<Rep> Key_3;
  typedef pair<Key,Key> Pure_interval;
  typedef pair<Pure_interval,T> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class _Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };
  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Compare_3 compare_3;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;
  typedef _Low_3 low_3;
  typedef _High_3 high_3;
  typedef _Key_3 key_3;
};


template <class Rep>
class CGAL_Range_segment_tree_set_traits_2{
 public:
  typedef CGAL_Point_2<Rep> Key;
  typedef CGAL_Point_2<Rep> Key_1;
  typedef CGAL_Point_2<Rep> Key_2;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;

};


template <class Rep>
class CGAL_Range_segment_tree_set_traits_3{
 public:
  typedef CGAL_Point_3<Rep> Key;
  typedef CGAL_Point_3<Rep> Key_1;
  typedef CGAL_Point_3<Rep> Key_2;
  typedef CGAL_Point_3<Rep> Key_3;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second;}
  };

  class _Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k;}
  };

  class _Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_x(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_y(k1,k2))
        return true;
      else 
        return false;
    }
  };

  class _Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      if(CGAL_SMALLER == CGAL_compare_z(k1,k2))
        return true;
      else 
        return false;
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Compare_3 compare_3;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;
  typedef _Low_3 low_3;
  typedef _High_3 high_3;
  typedef _Key_3 key_3;

};




#endif
