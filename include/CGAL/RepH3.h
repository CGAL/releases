
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

// Source: RepH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_REPH3_H
#define CGAL_REPH3_H

template <class NT>
class CGAL__RepH3 : public CGAL_Rep
{
public:

  NT  e0;
  NT  e1;
  NT  e2;
  NT  e3;

  CGAL__RepH3()
    {
    }
  CGAL__RepH3(const NT & a0, const NT & a1, const NT & a2, const NT & a3)
    : e0(a0), e1(a1), e2(a2), e3(a3)
    {
    }
  ~CGAL__RepH3()
    {
    }

  NT    hx()
         {
           return e0;
         }
  NT    hy()
         {
           return e1;
         }
  NT    hz()
         {
           return e2;
         }
  NT    hw()
         {
           return e3;  // homogenizing component
         }

};


#endif // CGAL_REPH3_H
