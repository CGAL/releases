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


// Source: Handle.h
// Author: from LEDA

#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#include <CGAL/kernel_assertions.h>

#ifndef CGAL_USE_LEDA_HANDLE

class CGAL_Rep  {

  friend class CGAL_Handle;

public: // was protected:

  int  count;

  CGAL_Rep()
  {
    count = 1;
  }

  virtual ~CGAL_Rep()
  {}

};


class CGAL_Handle {

public: // was protected:

  CGAL_Rep* PTR;

public:

  CGAL_Handle() {}
  CGAL_Handle(const CGAL_Handle& x)
  {
    CGAL_kernel_precondition( x.PTR != 0 );
    PTR = x.PTR;
    PTR->count++;
  }

  ~CGAL_Handle()
  {
    if (PTR && --PTR->count == 0) {
      delete PTR;
    }
  }

  CGAL_Handle& operator=(const CGAL_Handle& x)
  {
    x.PTR->count++;
    if (PTR && --PTR->count == 0)
      {
        delete PTR; // left side may be 0
      }
    PTR = x.PTR;
    return *this;
  }

  int refs()  const { return PTR->count; }


  friend unsigned long CGAL_id(const CGAL_Handle& x);

};

inline unsigned long CGAL_id(const CGAL_Handle& x)
{
  return (unsigned long)x.PTR;
}


template < class T >
inline bool CGAL_identical(const T &t1, const T &t2)
{
   return CGAL_id(t1) == CGAL_id(t2);
}

#else

#include <LEDA/basic.h>

typedef handle_base CGAL_Handle;
typedef handle_rep  CGAL_Rep;


template < class T >
inline bool CGAL_identical(const T &t1, const T &t2)
{
  return t1.id() == t2.id();
}

#endif // CGAL_USE_LEDA_HANDLE

#endif // CGAL_HANDLE_H
