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

// Source: Bbox_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_BBOX_2_H
#define CGAL_BBOX_2_H


#include <CGAL/basic.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/Fourtuple.h>

class CGAL_Bbox_2 : public CGAL_Handle
{
public:
                         CGAL_Bbox_2();
                         CGAL_Bbox_2(const CGAL_Bbox_2 &);
                         CGAL_Bbox_2(double x_min, double y_min,
                                   double x_max, double y_max);
                         ~CGAL_Bbox_2();
  CGAL_Bbox_2            &operator=(const CGAL_Bbox_2 &b);
  bool                   operator==(const CGAL_Bbox_2 &b) const;
  bool                   operator!=(const CGAL_Bbox_2 &b) const;

  int                    dimension() const;
  double                 xmin() const;
  double                 ymin() const;
  double                 xmax() const;
  double                 ymax() const;

  double                 max(int i) const;
  double                 min(int i) const;

  CGAL_Bbox_2              operator+(const CGAL_Bbox_2 &b) const;

private:
  inline CGAL__Fourtuple<double>*   ptr() const;
};



inline CGAL__Fourtuple<double>* CGAL_Bbox_2::ptr() const
{
  return (CGAL__Fourtuple<double>*)PTR;
}

inline int CGAL_Bbox_2::dimension() const
{
  return 2;
}

inline double CGAL_Bbox_2::xmin() const
{
  return ptr()->e0;
}

inline double CGAL_Bbox_2::ymin() const
{
  return ptr()->e1;
}

inline double CGAL_Bbox_2::xmax() const
{
  return ptr()->e2;
}

inline double CGAL_Bbox_2::ymax() const
{
  return ptr()->e3;
}

inline double CGAL_Bbox_2::min(int i) const
{
  CGAL_kernel_precondition( (i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return xmin();
  }
  return ymin();
}

inline double CGAL_Bbox_2::max(int i) const
{
  CGAL_kernel_precondition( (i == 0 ) || ( i == 1 ) );
  if(i == 0) {
    return xmax();
  }
  return ymax();
}
inline CGAL_Bbox_2 CGAL_Bbox_2::operator+(const CGAL_Bbox_2 &b) const
{
  return CGAL_Bbox_2(CGAL_min(xmin(), b.xmin()),
                     CGAL_min(ymin(), b.ymin()),
                     CGAL_max(xmax(), b.xmax()),
                     CGAL_max(ymax(), b.ymax()));
}
inline bool CGAL_do_overlap(const CGAL_Bbox_2 &bb1, const CGAL_Bbox_2 &bb2)
{
    // check for emptiness ??
    if (bb1.xmax() < bb2.xmin() || bb2.xmax() < bb1.xmin())
        return false;
    if (bb1.ymax() < bb2.ymin() || bb2.ymax() < bb1.ymin())
        return false;
    return true;
}

#endif // CGAL_BBOX_2_H
