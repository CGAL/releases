 
// Source: Bbox_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_BBOX_2_H
#define CGAL_BBOX_2_H

#include <CGAL/cartesian_classes.h>
#include <CGAL/Handle.h>
#include <CGAL/Fourtuple.h>
#include <LEDA/misc.h>

 
class CGAL_Bbox_2 : public CGAL_Handle_base
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

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

private:
  inline CGAL__Fourtuple<double>*   ptr() const;
};
 


 
#ifdef CGAL_CHECK_PRECONDITIONS
inline bool CGAL_Bbox_2::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS


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
  CGAL_kernel_precondition((i == 0 || i == 1 ) && is_defined());
  if(i == 0) {
    return xmin();
  }
  return ymin();
}

inline double CGAL_Bbox_2::max(int i) const
{
  CGAL_kernel_precondition((i == 0 || i == 1 ) && is_defined());
  if(i == 0) {
    return xmax();
  }
  return ymax();
}
 
inline CGAL_Bbox_2 CGAL_Bbox_2::operator+(const CGAL_Bbox_2 &b) const
{
  return CGAL_Bbox_2(Min(xmin(), b.xmin()),
                    Min(ymin(), b.ymin()),
                    Max(xmax(), b.xmax()),
                    Max(ymax(), b.ymax()));
}
 
inline bool do_overlap(const CGAL_Bbox_2 &bb1, const CGAL_Bbox_2 &bb2)
{
    // check for emptiness ??
    if (bb1.xmax() < bb2.xmin() || bb2.xmax() < bb1.xmin())
        return false;
    if (bb1.ymax() < bb2.ymin() || bb2.ymax() < bb1.ymin())
        return false;
    return true;
}
 

#endif // CGAL_BBOX_2_H
