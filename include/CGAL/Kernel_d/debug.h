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
// file          : include/CGAL/Kernel_d/debug.h
// package       : Kernel_d (0.9.47)
// chapter       : Basic
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/07/23 06:58:22 $
//
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// implementation: debugging stuff
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_DEBUG_H
#define CGAL_DEBUG_H

#include <iostream>
#include <string>
#include <strstream>

#undef TRACE
#undef TRACEN
#undef TRACEV
#undef CTRACE
#undef CTRACEN
#undef ASSERT

static int debugthread=3141592;

#if _DEBUG>0
#define SETDTHREAD(l) debugthread=l
#else
#define SETDTHREAD(l)
#endif

#if _DEBUG>0
#define TRACE(t)   if((debugthread%_DEBUG)==0)\
 std::cerr<<" "<<t;std::cerr.flush()
#else
#define TRACE(t) 
#endif

#if _DEBUG>0
#define TRACEV(t)  if((debugthread%_DEBUG)==0)\
 std::cerr<<" "<<#t<<" = "<<(t)<<std::endl;std::cerr.flush()
#else
#define TRACEV(t) 
#endif

#if _DEBUG>0
#define TRACEN(t)  if((debugthread%_DEBUG)==0)\
 std::cerr<<" "<<t<<std::endl;std::cerr.flush()
#else
#define TRACEN(t) 
#endif

#if _DEBUG>0
#define CTRACE(b,t)  if(b) std::cerr << " " << t; else std::cerr << " 0"
#else
#define CTRACE(b,t) 
#endif

#if _DEBUG>0
#define CTRACEN(b,t)  if(b) std::cerr << " " << t << "\n"; else std::cerr << " 0\n"
#else
#define CTRACEN(b,t) 
#endif

#ifndef _ASSERT
#define  ASSERT(cond,fstr) 
#else
#define ASSERT(cond,fstr)   \
  if (!(cond)) {       \
    std::cerr << "   ASSERT:   " << #fstr << endl; \
    std::cerr << "   COND:     " << #cond << endl; \
    std::cerr << "   POSITION: " << __FILE__ << " at line " << __LINE__ << std::endl; \
    abort();           \
  }
#endif

#define forall_iterators(x,S)\
for(x = S.begin(); x != S.end(); ++x) 

namespace MSDEBUG {

template <typename C>
void print_elements(const C& container)
{ typename C::const_iterator it;
  forall_iterators(it,container)
    std::cerr << *it << " ";
}

template <typename I>
void print(I s, I e, std::ostream& os = std::cerr)
{ while(s!=e) os<<*s++<<" "; }

template <class T>
std::string make_std_string(const T& t)
{ std::ostrstream os;
  os << t;
  std::string res(os.str()); os.freeze(0); return res; }
} // MSDEBUG


#endif //CGAL_DEBUG_H


