 
// Source: ostream_3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_OSTREAM_3_H
#define CGAL_OSTREAM_3_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/IO/ostreamH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/IO/ostreamC3.h>
#endif // CGAL_CARTESIAN_H

 

#ifdef CGAL_POINT_3_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Point_3<R> &p)
{

  os << "Point_3(" << p.x() << ", " << p.y() << ", " << p.z() << ")";
  return os;
}

#endif // CGAL_POINT_3_H
 

 

#ifdef CGAL_VECTOR_3_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Vector_3<R> &v)
{

  os << "Vector_3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  return os;
}

#endif // CGAL_VECTOR_3_H
 

 

#ifdef CGAL_DIRECTION_3_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Direction_3<R> &d)
{
  CGAL_Vector_3<R> v = d.vector();
  os << "Direction_3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  return os;
}

#endif // CGAL_DIRECTION_3_H
 


 

#ifdef CGAL_Line_3_H

template < class R >
ostream &operator<<(ostream &os, CGAL_Line_3<R> &l)
{
  os << "Line_3(" << l.point() << ", " << l.direction() << ")";
  return os;
}
#endif //CGAL_Line_3_H
 

 

#ifdef CGAL_Ray_3_H

template < class R >
ostream &operator<<(ostream &os, CGAL_Ray_3<R> &r)
{
  os << "Ray_3(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif // CGAL_Ray_3_H
 

 

#ifdef CGAL_SEGMENT_3_H

template < class R >
ostream &operator<<(ostream &os, CGAL_Segment_3<R> &s)
{


  os << "Segment_3(" << s.start() <<  ", " << s.end() << ")";
  return os;
}

#endif // CGAL_SEGMENT_3_H
 


 

#ifdef CGAL_PLANE_3_H

template < class R >
ostream &operator<<(ostream &os, CGAL_Plane_3<R> &p)
{
  os << "Plane_3(" << p.a() <<  ", " << p.b() <<   ", " ;
  os << p.c() << ", " << p.d() <<")";
  return os;
}
#endif  // CGAL_PLANE_3_H
 

 

#ifdef CGAL_TRIANGLE_3_H

template < class R >
ostream &operator<<(ostream &os, CGAL_Triangle_3<R> &t)
{
  os << "Triangle_3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif // CGAL_TRIANGLE_3_H
 

 

#ifdef CGAL_TETRAHEDRON_3_H

template < class R >
ostream &operator<<(ostream &os, const CGAL_Tetrahedron_3<R> &t)
{
  os << "Tetrahedron_3(" << t[0] <<  ", " << t[1] <<   ", " ;
  os << t[2] <<  ", " << t[3] << ")";
  return os;
}

#endif  // CGAL_TETRAHEDRON_3_H
 


 

#ifdef CGAL_BBOX_3_H

inline ostream &operator<<(ostream &os, const CGAL_Bbox_3 &bbox)
{
  os << "Bbox_3((" << bbox.xmin() 
     << ", "       << bbox.ymin() 
     << ", "       << bbox.zmin() << "), (";
  os <<               bbox.xmax()
     << ", "       << bbox.ymax() 
     << ", "       << bbox.zmax() << "))";
  return os;
}

#endif // CGAL_BBOX_3_H
 


#endif // CGAL_OSTREAM_3_H
