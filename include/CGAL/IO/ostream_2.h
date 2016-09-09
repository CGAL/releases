 
// Source: ostream_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_OSTREAM_2_H
#define CGAL_OSTREAM_2_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/IO/ostreamH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/IO/ostreamC2.h>
#endif // CGAL_CARTESIAN_H

 

#ifdef CGAL_Z_H
inline ostream& operator<<(ostream& os, const CGAL_Z &z)
{
  char *str = new char [mpz_sizeinbase(z.ptr()->mpZ,10) + 2];
  str = mpz_get_str(str, 10, z.ptr()->mpZ);
  os << str ;
  delete str;
  return os;
}
#endif // CGAL_Z_H
 


 

#ifdef CGAL_POINT_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Point_2<R> &p)
{

  os << "Point_2(" << p.hx() << ", " << p.hy() << ", " << p.hw() << ")";
  return os;
}

#endif // CGAL_POINT_2_H
 


 

#ifdef CGAL_VECTOR_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Vector_2<R> &v)
{

  os << "Vector_2(" << v.hx() << ", " << v.hy() << ", " << v.hw() << ")";
  return os;
}

#endif // CGAL_VECTOR_2_H
 


 

#ifdef CGAL_DIRECTION_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Direction_2<R> &d)
{

  CGAL_Vector_2<R> v = d.vector();
  os << "Direction_2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif // CGAL_DIRECTION_2_H
 


 

#ifdef CGAL_LINE_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Line_2<R> &l)
{

  os << "Line_2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif // CGAL_LINE_2_H
 


 

#ifdef CGAL_RAY_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Ray_2<R> &r)
{

  os << "Ray_2(" << r.source() <<  ", " << r.direction() << ")";
  return os;
}

#endif // CGAL_RAY_2_H
 


 

#ifdef CGAL_SEGMENT_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Segment_2<R> &s)
{

  os << "Segment_2(" << s.source() <<  ", " << s.target() << ")";
  return os;
}

#endif // CGAL_SEGMENT_2_H
 


 

#ifdef CGAL_TRIANGLE_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Triangle_2<R> &t)
{
  os << "Triangle_2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif // CGAL_TRIANGLE_2_H
 


 

#ifdef CGAL_ISO_RECTANGLE_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Iso_rectangle_2<R> &r)
{
  os << "Iso_rectangle_2(" << r.vertex(0) <<  ", " << r.vertex(2) << ")";
  return os;
}

#endif // CGAL_ISO_RECTANGLE_2_H
 


 

#ifdef CGAL_BBOX_2_H

inline ostream &operator<<(ostream &os, const CGAL_Bbox_2 &bbox)
{
  os << "Bbox_2((" << bbox.xmin() << ", " << bbox.ymin() << "), (";
  os <<               bbox.xmax() << ", " << bbox.ymax() << "))";
  return os;
}

#endif // CGAL_BBOX_2_H
 


 
#ifdef CGAL_PARABOLA_2_H
template < class R >
ostream &operator<<(ostream &os, const CGAL_Parabola_2<R> &p)
{
  os << "Parabola_2((" << p.base() << ", " << p.direction() 
     << ", " << p.curvature()  << "),";
  return os;
}
#endif // CGAL_PARABOLA_2_H
 


 

#ifdef CGAL_CIRCLE_2_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Circle_2<R> &t)
{
  os << "Circle_2(" << t.center() <<  ", " << t.squared_radius()  <<")";
  return os;
}

#endif // CGAL_CIRCLE_2_H
 


 
#ifdef CGAL_AFF_TRANSFORMATION_2_H
template < class R >
ostream &operator<<(ostream &os, const CGAL_Aff_transformation_2<R> &t)
{
  os << R::Aff_transformation_2(t);
  return os;
}
#endif // CGAL_AFF_TRANSFORMATION_2_H
 


#endif // CGAL_OSTREAM_2_H
