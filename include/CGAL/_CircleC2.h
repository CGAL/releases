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

// Source: _CircleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL__CIRCLEC2_H
#define CGAL__CIRCLEC2_H

template < class T >
class CGAL__CircleC2 : public CGAL_Rep
{
public:

  CGAL_PointC2<T>  center;
  T  squared_radius;
  CGAL_Orientation orientation;


  CGAL__CircleC2()
    {}

  CGAL__CircleC2(const CGAL_PointC2<T> & c,
                 const T & r,
                 const CGAL_Orientation &o)
    : center(c), squared_radius(r), orientation(o)
    {}

  ~CGAL__CircleC2()
    {}
};
#endif  // CGAL__CIRCLEC2_H
