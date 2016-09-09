 
// Source: CGAL_Bbox_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_Bbox_3_H
#define CGAL_Bbox_3_H

#include <CGAL/Sixtuple.h>
#include <LEDA/misc.h>

 
class CGAL_Bbox_3 : public CGAL_Handle_base
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
  CGAL_Handle_base(b)
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
  CGAL_Handle_base::operator=(b);
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
  return CGAL_Bbox_3(Min(xmin(), b.xmin()),
                    Min(ymin(), b.ymin()),
                    Min(zmin(), b.zmin()),
                    Max(xmax(), b.xmax()),
                    Max(ymax(), b.ymax()),
                    Max(zmax(), b.zmax()));
}
 
inline CGAL__Sixtuple<double>* CGAL_Bbox_3::ptr() const
{
  return (CGAL__Sixtuple<double>*)PTR;
}
 


#endif
