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

// file  : include/CGAL/Key_compare_k
// source: include/CGAL/Key_compare_k
// author: Gabriele Neyer
// $Revision: 1.1.1.1 $
// $Date: 1997/05/16 11:18:52 $

#ifndef CGAL_Key_compare_k
#define CGAL_Key_compare_k


template <class _T1, class _C1>
class CGAL_Key_compare_1
{
public:
  typedef _C1 C1;
  typedef _T1 T1;
  bool c1(T1 p1, T1 p2)
  {  return C1()(p1,p2);}
};

template <class _T1, class _C1, class _T2, class _C2>
class CGAL_Key_compare_2
{
public:
  typedef _C1 C1;
  typedef _C2 C2;
  typedef _T1 T1;
  typedef _T2 T2;
  bool c1(T1 const p1, T1 const p2) const
  {  return C1()(p1,p2);}
  bool c2(T2 const p1, T2 const p2) const
  {  return C2()(p1,p2);}
};

template <class _T1, class _C1, class _T2, class _C2, class _T3, class _C3>
class CGAL_Key_compare_3
{
public:
  typedef _C1 C1;
  typedef _C2 C2;
  typedef _C3 C3;
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;

  bool c1(T1 p1, T1 p2)
  {  return C1()(p1,p2);}
  bool c2(T2 p1, T2 p2)
  {  return C2()(p1,p2);}
  bool c3(T3 p1, T3 p2)
  {  return C3()(p1,p2);}
};

template <class _T1, class _C1, class _T2, class _C2, class _T3, class _C3, class _T4, class _C4>
class CGAL_Key_compare_4
{
public:
  typedef _C1 C1;
  typedef _C2 C2;
  typedef _C3 C3;
  typedef _C4 C4;
  typedef _T1 T1;
  typedef _T2 T2;
  typedef _T3 T3;
  typedef _T4 T4;

  bool c1(T1 p1, T1 p2)
  {  return C1()(p1,p2);}
  bool c2(T2 p1, T2 p2)
  {  return C2()(p1,p2);}
  bool c3(T3 p1, T3 p2)
  {  return C3()(p1,p2);}
  bool c4(T4 p1, T4 p2)
  {  return C4()(p1,p2);}
};




#endif

