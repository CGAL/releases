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

// file  : include/CGAL/Interval_k.h
// source: include/CGAL/Interval_k.h
// author: Gabriele Neyer
// $Revision: 1.1.1.1 $
// $Date: 1997/05/16 11:18:52 $

#ifndef CGAL_Interval_k
#define CGAL_Interval_k

// container class for a one dimensional interval.
// Ti defines the type of the i-st dimension.
template<class _T1>
class CGAL_Interval_1
{
public:
  typedef _T1 T1;
private:
  T1 low1, high1;
public:
  CGAL_Interval_1(){}
  CGAL_Interval_1(T1 l1, T1 r1):low1(l1), high1(r1){}
  T1 low_1() const { return low1;}
  T1 high_1() const { return high1;}
};

//--------------------------------------------------------------------------
// container class for a two dimensional interval.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2>
class CGAL_Interval_2
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
private:
  T1 low1, high1;
  T2 low2, high2;
public:
  CGAL_Interval_2(){}
  CGAL_Interval_2(T1 l1, T1 r1, 
		  T2 l2, T2 r2):low1(l1), high1(r1), low2(l2), high2(r2){}
  T1 low_1() const { return low1;}
  T1 high_1() const { return high1;}
  T2 low_2() const { return low2;}
  T2 high_2() const { return high2;}
};

//--------------------------------------------------------------------------
// container class for a three dimensional interval.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2, class _T3>
class CGAL_Interval_3
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
private:
  T1 low1, high1;
  T2 low2, high2;
  T3 low3, high3;
public:
  CGAL_Interval_3(){}
  CGAL_Interval_3(T1 l1, T1 r1, 
		 T2 l2, T2 r2,
		 T3 l3, T3 r3):low1(l1), high1(r1), low2(l2), high2(r2), low3(l3), high3(r3){}
  T1 low_1() const { return low1;}
  T1 high_1() const { return high1;}
  T2 low_2() const { return low2;}
  T2 high_2() const { return high2;}
  T3 low_3() const { return low3;}
  T3 high_3() const { return high3;}
};

//--------------------------------------------------------------------------
// container class for a four dimensional interval.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2, class _T3, class _T4>
class CGAL_Interval_4
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _T4 T4;
private:
  T1 low1, high1;
  T2 low2, high2;
  T3 low3, high3;
  T4 low4, high4;
public:
  CGAL_Interval_4(){}
  CGAL_Interval_4(T1 l1, T1 r1, 
		 T2 l2, T2 r2,
		 T3 l3, T3 r3, 
		 T4 l4, T4 r4):low1(l1), high1(r1), low2(l2), high2(r2), low3(l3), high3(r3), low4(l4), high4(r4){}
  T1 low_1() const { return low1;}
  T1 high_1() const { return high1;}
  T2 low_2() const { return low2;}
  T2 high_2() const { return high2;}
  T3 low_3() const { return low3;}
  T3 high_3() const { return high3;}
  T4 low_4() const { return low4;}
  T4 high_4() const { return high4;}
};



// container class for a one dimensional interval and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1>
class CGAL_Interval_item_1
{
public:
  typedef _T1 T1;
  typedef _V V;
private:
  T1 low1, high1;
  V v;
public:
  CGAL_Interval_item_1(){}
  CGAL_Interval_item_1(V va, T1 l1, T1 r1):low1(l1), high1(r1), v(va){}
  T1 low_1(){ return low1;}
  T1 high_1(){ return high1;}
  V value(){ return v;}
};

//--------------------------------------------------------------------------
// container class for a two dimensional interval and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1, class _T2>
class CGAL_Interval_item_2
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _V V;
private:
  T1 low1, high1;
  T2 low2, high2;
  V v;
public:
  CGAL_Interval_item_2(){}
  CGAL_Interval_item_2(V va, T1 l1, T1 r1, 
	     T2 l2, T2 r2):low1(l1), high1(r1), low2(l2), high2(r2), v(va){}
  T1 low_1(){ return low1;}
  T1 high_1(){ return high1;}
  T2 low_2(){ return low2;}
  T2 high_2(){ return high2;}
  V value(){ return v;}
};

//--------------------------------------------------------------------------
// container class for a three dimensional interval and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type,
template<class _V, class _T1, class _T2, class _T3>
class CGAL_Interval_item_3
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _V V;
private:
  T1 low1, high1;
  T2 low2, high2;
  T3 low3, high3;
  V v;
public:
  CGAL_Interval_item_3(){}
  CGAL_Interval_item_3(V va, T1 l1, T1 r1, 
		 T2 l2, T2 r2,
		 T3 l3, T3 r3):low1(l1), high1(r1), low2(l2), high2(r2), low3(l3), high3(r3), v(va){}
  T1 low_1(){ return low1;}
  T1 high_1(){ return high1;}
  T2 low_2(){ return low2;}
  T2 high_2(){ return high2;}
  T3 low_3(){ return low3;}
  T3 high_3(){ return high3;}
  V value(){ return v;}
};

//--------------------------------------------------------------------------
// container class for a four dimensional interval and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1, class _T2, class _T3, class _T4>
class CGAL_Interval_item_4
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _T4 T4;
  typedef _V V;
private:
  T1 low1, high1;
  T2 low2, high2;
  T3 low3, high3;
  T4 low4, high4;
  V v;
public:
  CGAL_Interval_item_4(){}
  CGAL_Interval_item_4(V va, T1 l1, T1 r1, 
		 T2 l2, T2 r2,
		 T3 l3, T3 r3, 
		 T4 l4, T4 r4):low1(l1), high1(r1), low2(l2), high2(r2), low3(l3), high3(r3), low4(l4), high4(r4), v(va){}
  T1 low_1(){ return low1;}
  T1 high_1(){ return high1;}
  T2 low_2(){ return low2;}
  T2 high_2(){ return high2;}
  T3 low_3(){ return low3;}
  T3 high_3(){ return high3;}
  T4 low_4(){ return low4;}
  T4 high_4(){ return high4;}
  V value(){ return v;}
};



#endif
