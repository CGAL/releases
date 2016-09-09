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

// Source: Twotuple_Rep.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__TWOTUPLE_H
#define CGAL__TWOTUPLE_H


template < class T >
class CGAL__Twotuple : public CGAL_Rep
{
public:
  T  e0;
  T  e1;

  CGAL__Twotuple()
  {}

  CGAL__Twotuple(const T & a0, const T &a1)
  : e0(a0), e1(a1)
  {}

  ~CGAL__Twotuple()
  {}
};


#endif // CGAL__TWOTUPLE_H
