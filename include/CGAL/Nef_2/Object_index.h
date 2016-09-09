// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Nef_2/Object_index.h
// package       : Nef_2 (0.9.25)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/PM_decorator.lw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/16 12:47:22 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Indexing of handles
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef OBJECT_INDEX_H
#define OBJECT_INDEX_H

#include <CGAL/basic.h>
#include <CGAL/Unique_hash_map.h>
#include <string>
#include <strstream>

CGAL_BEGIN_NAMESPACE

template <typename I>
class Object_index {
  char _prefix;
  CGAL::Unique_hash_map<I,int> _index;
public:
  Object_index() : _prefix('\0'), _index(-1) {}
  Object_index(I first, I beyond, char c=' ') : _prefix(c), _index(-1)
  { for(int i=0 ; first!=beyond; ++i,++first) _index[first]=i; }
  int operator[](const I& it) const { return _index[it]; } 
  int& operator[](const I& it) { return _index[it]; } 

  void index(I first, I beyond, char c=' ')
  { _prefix=c;
    for(int i=0 ; first!=beyond; ++i,++first) _index[first]=i;
  }
  std::string operator()(const I& it, bool verbose=true) const
  { if (verbose && _index[it]==-1) return "nil";
    if (verbose && _index[it]==-2) return "end";
    std::ostrstream os; 
    if (verbose) os << _prefix;
    os << _index[it] << '\0';    
    std::string res(os.str()); os.freeze(0); return res; }
 
};

CGAL_END_NAMESPACE

#endif //OBJECT_INDEX_H




