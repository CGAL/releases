// Source: Bbox_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Bbox_H
#define CGAL_Bbox_H

#include <CGAL/Fourtuple.h>
#include <LEDA/misc.h>

class CGAL_Bbox_2 : public handle_base
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

  double                 xmin() const;
  double                 ymin() const;
  double                 xmax() const;
  double                 ymax() const;

  CGAL_Bbox_2              operator+(const CGAL_Bbox_2 &b) const;

private:
  inline CGAL__Fourtuple<double>*   ptr() const;
};


inline CGAL__Fourtuple<double>* CGAL_Bbox_2::ptr() const
{
  return (CGAL__Fourtuple<double>*)PTR;
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


#endif
