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


// file  : include/CGAL/Key_k.h
// source: include/CGAL/Key_k.h
// author: Gabriele Neyer
// $Revision: 1.1.1.1 $
// $Date: 1997/05/16 11:18:53 $

#ifndef CGAL_Key_k
#define CGAL_Key_k

//--------------------------------------------------------------------------
// container class for a one dimensional key.
// Ti defines the type of the i-st dimension.
template<class _T1>
class CGAL_Key_1
{
public:
  typedef _T1 T1;
private:
  T1 key1;
public:
  CGAL_Key_1(){}
  CGAL_Key_1(T1 k1):key1(k1){}
  T1 key_1() const { return key1;}
};

//--------------------------------------------------------------------------
// container class for a two dimensional key.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2>
class CGAL_Key_2
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
private:
  T1 key1;
  T2 key2;
public:
  CGAL_Key_2(){}
  CGAL_Key_2(T1 k1, T2 k2):key1(k1), key2(k2){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
};

//--------------------------------------------------------------------------
// container class for a three dimensional key.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2, class _T3>
class CGAL_Key_3
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
private:
  T1 key1;
  T2 key2;
  T3 key3;
public:
  CGAL_Key_3(){}
  CGAL_Key_3(T1 k1, T2 k2, T3 k3):key1(k1), key2(k2), key3(k3){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
  T3 key_3() const { return key3;}
};


//--------------------------------------------------------------------------
// container class for a four dimensional key.
// Ti defines the type of the i-st dimension.
template<class _T1, class _T2, class _T3, class _T4>
class CGAL_Key_4
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _T4 T4;
private:
  T1 key1;
  T2 key2;
  T3 key3;
  T4 key4;
public:
  CGAL_Key_4(){}
  CGAL_Key_4(T1 k1, T2 k2, T3 k3, T4 k4):key1(k1), key2(k2), key3(k3), key4(k4){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
  T3 key_3() const { return key3;}
  T4 key_4() const { return key4;}
};




//--------------------------------------------------------------------------
// container class for a one dimensional point and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1>
class CGAL_Point_item_1
{
public:
  typedef _T1 T1;
  typedef _V V;
private:
  T1 key1;
  V v;
public:
  CGAL_Point_item_1(){}
  CGAL_Point_item_1(V va,T1 k1):key1(k1), v(va){}
  T1 key_1() const { return key1;}
  V value() const { return v;}
};

//--------------------------------------------------------------------------
// container class for a two dimensional point and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1, class _T2>
class CGAL_Point_item_2
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _V V;
private:
  T1 key1;
  T2 key2;
  V v;
public:
  CGAL_Point_item_2(){}
  CGAL_Point_item_2(V va, T1 k1, T2 k2):key1(k1), key2(k2), v(va){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
  V value() const { return v;}
};

//--------------------------------------------------------------------------
// container class for a three dimensional point and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1, class _T2, class _T3>
class CGAL_Point_item_3
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _V V;
private:
  T1 key1;
  T2 key2;
  T3 key3;
  V v;
public:
  CGAL_Point_item_3(){}
  CGAL_Point_item_3(V va, T1 k1, T2 k2, T3 k3):key1(k1), key2(k2), key3(k3), v(va){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
  T3 key_3() const { return key3;}
  V value() const { return v;}
};


//--------------------------------------------------------------------------
// container class for a four dimensional point and a value.
// Ti defines the type of the i-st dimension.
// V defines the value type.
template<class _V, class _T1, class _T2, class _T3, class _T4>
class CGAL_Point_item_4
{
public:
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _T4 T4;
  typedef _V V;
private:
  T1 key1;
  T2 key2;
  T3 key3;
  T4 key4;
  V v;
public:
  CGAL_Point_item_4(){}
  CGAL_Point_item_4(V va, T1 k1, T2 k2, T3 k3, T4 k4):key1(k1), key2(k2), key3(k3), key4(k4), v(va){}
  T1 key_1() const { return key1;}
  T2 key_2() const { return key2;}
  T3 key_3() const { return key3;}
  T4 key_4() const { return key4;}
  V value() const { return v;}
};


#endif
