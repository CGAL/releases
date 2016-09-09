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
// file          : config/testfiles/CGAL_CFG_DYNAMIC_CAST_BUG.C
// package       : Configuration (2.4)
// source        :
// revision      : 1.11
// revision_date : 29 Mar 1998
// author(s)     : various
//
// coordinator   : Utrecht University
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// CGAL_CFG_DYNAMIC_CAST_BUG.C
// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by cgal_configure.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| When a dynamic cast involves a pointer to a not yet instantiated 
//| template class, some compilers give an error.
//| This program is used to detect this problem.

class B
{
public:
  virtual ~B() {}
};

template <class T>
class W : public B
{
public:
  T obj;
};

template <class T>
class L
{
public:
  T nt;
};

template <class T>
class P
{
public:
  T nt;
};

int
main()
{
  W< P<int> > wp;
  W< L<int> >* wl_ptr = dynamic_cast<W< L<int> >* >( &wp );

  return 0;
}
  
//| "CGAL_CFG_DYNAMIC_CAST_BUG.C", line 45: error(3105): the type in a
//|           dynamic_cast must be a pointer or reference to a complete class
//|           type, or void *
//|     W< L<int> >* wl_ptr = dynamic_cast<W< L<int> >* >( &wp );
//|                                        ^

