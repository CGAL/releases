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
// file          : include/CGAL/Nef_2/geninfo.h
// package       : Nef_2 (0.9.25)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/Basic_extensions.lw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/21 15:28:31 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: generic pointer access
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef GENINFO_H
#define GENINFO_H

#include <memory>

/*{\Moptions outfile=geninfo.man}*/
/*{\Moptions constref=yes}*/
/*{\Manpage {geninfo} {T} {Information association via GenPtr} {}}*/    

template <typename T>
struct geninfo {
  typedef void* GenPtr;

/*{\Mdefinition |\Mname| encapsulates information association via
generic pointers of type |GenPtr (=void*)|. An object |t| of type |T|
is stored directly in a variable |p| of type |GenPtr| if |sizeof(T)|
is not larger than |sizeof(GenPtr)| (also called word size). Otherwise
|t| is allocated on the heap and referenced via |p|. This class
encapsulates the technicalities, however the user always has to obey
the order of its usage: |create|-|access/const_access|-|clear|. On
misuse memory problems occur.}*/

/*{\Moperations 2 1}*/

#ifdef __BORLANDC__
#pragma option -w-rch -w-eff -w-ccc
#endif

  static void create(GenPtr& p) 
  /*{\Mstatic create a slot for an object of type |T| referenced 
    via |p|.}*/
  { if (sizeof(T) <= sizeof(GenPtr)) new((void*)(&p)) T;
    if (sizeof(T) >  sizeof(GenPtr)) p = (GenPtr) new T;
  }

  static T& access(GenPtr& p)
  /*{\Mstatic access an object of type |T| via |p|.
    \precond |p| was initialized via |create| and was not cleared 
    via |clear|.}*/
  { if (sizeof(T) <= sizeof(GenPtr)) return *(T*)(&p);
    else                             return *(T*)p;
  }

  static const T& const_access(const GenPtr& p) 
  /*{\Mstatic read-only access of an object of type |T| via |p|.
    \precond |p| was initialized via |create| and was not cleared 
    via |clear|.}*/
  { if (sizeof(T) <= sizeof(GenPtr)) return *(const T*)(&p);
    else                             return *(const T*)p; 
  }

  static void clear(GenPtr& p) 
  /*{\Mstatic clear the memory used for the object of type |T| via
     |p|. \precond |p| was initialized via |create|.}*/
  { if (sizeof(T) <= sizeof(GenPtr)) ((T*)(&p))->~T();
    if (sizeof(T) >  sizeof(GenPtr)) delete (T*) p;
    p=0;
  }

};

/*{\Mexample In the first example we store a pair of boolean values
which normally fit into one word. Thus there will no heap allocation
take place.
\begin{Mverb}
  struct A { bool a,b };
  GenPtr a;
  geninfo<A>::create(a);
  A& a_access = geninfo<A>::access(a);
  geninfo<A>::clear(a);
\end{Mverb}
The second example uses the heap scheme as two longs do not fit into
one word.
\begin{Mverb}
  struct B { long a,b };
  GenPtr b;
  geninfo<B>::create(b);
  B& b_access = geninfo<B>::access(b);
  geninfo<B>::clear(b);
\end{Mverb}
Note that usage of the scheme takes away with the actual check for the
type size. Even more important this size might depend on the platform
which is used to compile the code and thus the scheme enables platform
independent programming.}*/

#endif //GENINFO_H


