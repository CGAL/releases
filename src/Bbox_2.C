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

#include <CGAL/Bbox_2.h>

CGAL_Bbox_2::CGAL_Bbox_2()
{
  PTR = new CGAL__Fourtuple<double>();
}

CGAL_Bbox_2::CGAL_Bbox_2(const CGAL_Bbox_2 &b) :
  CGAL_Handle(b)
{}

CGAL_Bbox_2::CGAL_Bbox_2(double x_min, double y_min,
                         double x_max, double y_max)
{
  PTR = new CGAL__Fourtuple<double>(x_min, y_min, x_max, y_max);
}

CGAL_Bbox_2::~CGAL_Bbox_2()
{}

CGAL_Bbox_2 &CGAL_Bbox_2::operator=(const CGAL_Bbox_2 &b)
{
  CGAL_Handle::operator=(b);
  return *this;
}
bool CGAL_Bbox_2::operator==(const CGAL_Bbox_2 &b) const
{
  return xmin() == b.xmin() && xmax() == b.xmax()
         && ymin() == b.ymin() && ymax() == b.ymax();
}

bool CGAL_Bbox_2::operator!=(const CGAL_Bbox_2 &b) const
{
  return ! (b == *this);
}

