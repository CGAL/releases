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

// Source: CGAL_Bbox_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_BBOX_3_H
#define CGAL_BBOX_3_H

#include <CGAL/basic.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/Sixtuple.h>


class CGAL_Bbox_3 : public CGAL_Handle
{
public:
                         CGAL_Bbox_3();
                         CGAL_Bbox_3(const CGAL_Bbox_3 &);
                         CGAL_Bbox_3(double x_min, double y_min, double zmin,
                                    double x_max, double y_max, double z_max);
                         ~CGAL_Bbox_3();
  CGAL_Bbox_3             &operator=(const CGAL_Bbox_3 &b);

  double                 xmin() const;
  double                 ymin() const;
  double                 zmin() const;
  double                 xmax() const;
  double                 ymax() const;
  double                 zmax() const;

  CGAL_Bbox_3             operator+(const CGAL_Bbox_3 &b) const;

private:
  inline CGAL__Sixtuple<double>* ptr() const;
};


inline CGAL_Bbox_3::CGAL_Bbox_3()
{
  PTR = new CGAL__Sixtuple<double>;
}

inline CGAL_Bbox_3::CGAL_Bbox_3(const CGAL_Bbox_3 &b) :
  CGAL_Handle(b)
{}

inline CGAL_Bbox_3::CGAL_Bbox_3(double x_min, double y_min, double z_min,
                              double x_max, double y_max, double z_max)
{
  PTR = new CGAL__Sixtuple<double>(x_min, y_min, z_min, x_max, y_max, z_max);
}

inline CGAL_Bbox_3::~CGAL_Bbox_3()
{}

inline CGAL_Bbox_3 &CGAL_Bbox_3::operator=(const CGAL_Bbox_3 &b)
{
  CGAL_Handle::operator=(b);
  return *this;
}
inline double CGAL_Bbox_3::xmin() const
{
  return ptr()->e0;
}

inline double CGAL_Bbox_3::ymin() const
{
  return ptr()->e1;
}

inline double CGAL_Bbox_3::zmin() const
{
  return ptr()->e2;
}

inline double CGAL_Bbox_3::xmax() const
{
  return ptr()->e3;
}

inline double CGAL_Bbox_3::ymax() const
{
  return ptr()->e4;
}

inline double CGAL_Bbox_3::zmax() const
{
  return ptr()->e5;
}
inline CGAL_Bbox_3 CGAL_Bbox_3::operator+(const CGAL_Bbox_3 &b) const
{
  return CGAL_Bbox_3(CGAL_min(xmin(), b.xmin()),
                     CGAL_min(ymin(), b.ymin()),
                     CGAL_min(zmin(), b.zmin()),
                     CGAL_max(xmax(), b.xmax()),
                     CGAL_max(ymax(), b.ymax()),
                     CGAL_max(zmax(), b.zmax()));
}
inline bool CGAL_do_overlap(const CGAL_Bbox_3 &bb1, const CGAL_Bbox_3 &bb2)
{
    // check for emptiness ??
    if (bb1.xmax() < bb2.xmin() || bb2.xmax() < bb1.xmin())
        return false;
    if (bb1.ymax() < bb2.ymin() || bb2.ymax() < bb1.ymin())
        return false;
    if (bb1.zmax() < bb2.zmin() || bb2.zmax() < bb1.zmin())
        return false;
    return true;
}
inline CGAL__Sixtuple<double>* CGAL_Bbox_3::ptr() const
{
  return (CGAL__Sixtuple<double>*)PTR;
}


#endif // CGAL_BBOX_3_H
