#include <CGAL/Bbox_2.h>

CGAL_Bbox_2::CGAL_Bbox_2()
{
  PTR = new CGAL__Fourtuple<double>();
}

CGAL_Bbox_2::CGAL_Bbox_2(const CGAL_Bbox_2 &b) :
  handle_base(b)
{}

CGAL_Bbox_2::CGAL_Bbox_2(double x_min, double y_min, double x_max, double y_max)
{
  PTR = new CGAL__Fourtuple<double>(x_min, y_min, x_max, y_max);
}

CGAL_Bbox_2::~CGAL_Bbox_2()
{}

CGAL_Bbox_2 &CGAL_Bbox_2::operator=(const CGAL_Bbox_2 &b)
{
  handle_base::operator=(b);
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

