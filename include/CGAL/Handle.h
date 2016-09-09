//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Handle.h
// Author: from LEDA
#ifndef CGAL_HANDLE_H
#define CGAL_HANDLE_H

#ifdef CGAL_HANDLE


class CGAL_Rep  {

  friend class CGAL_Handle;

protected:

  int  count;

  CGAL_Rep()
  {
    count = 1;
  }

  virtual ~CGAL_Rep()
  {}

};


class CGAL_Handle {

protected:

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

typedef handle_base CGAL_Handle;
typedef handle_rep CGAL_Rep;


template < class T >
inline bool CGAL_identical(const T &t1, const T &t2)
{
  return t1.id() == t2.id();
}


#endif // CGAL_HANDLE

#endif // CGAL_HANDLE_H
