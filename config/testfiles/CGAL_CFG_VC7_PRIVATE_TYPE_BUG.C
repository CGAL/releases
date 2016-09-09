// ======================================================================
//
// Copyright (c) 2002 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : config/testfiles/CGAL_CFG_VC7_PRIVATE_TYPE_BUG.C
// package       : Configuration (2.32)
// author(s)     : Sylvain Pion
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// CGAL_CFG_VC7_PRIVATE_TYPE_BUG.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| This is a test-case for a bug in VC++ 7.0 beta2 that occurs in the kernel.
//| When the bug is present, CGAL_CFG_VC7_PRIVATE_TYPE_BUG is set.

template <class R>
class A
{
  typedef typename R::B B;
public:
 
  A() :i(0) {}
 
  int i;
};
 
template <class R>
class B
: public R::A
{
public:
  typedef typename R::A base;
  B() : base() {}
};
 
template <class FT>
class RR
{
public:
  typedef ::A<RR> A;
  typedef ::B<RR> B;
};
 
int main()
{
  typedef RR<int> r;
  A<r> a;
  B<r> b;
  (void) a;
  (void) b;
  return 0;
}
