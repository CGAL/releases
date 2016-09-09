 
// Source: ostreamC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_OSTREAMC3_H
#define CGAL_OSTREAMC3_H

#include <stream.h>

 

#ifdef CGAL_POINTC3_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_PointC3<FT> &p)
{
  os << "PointC3(" << p.x() << ", " << p.y()  << ", " << p.z() << ")";
  return os;
}

#endif // CGAL_POINTC3_H
 

 

#ifdef CGAL_VECTORC3_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_VectorC3<FT> &v)
{
  os << "VectorC3(" << v.x() << ", " << v.y() <<  ", " << v.z() << ")";
  return os;
}

#endif  // CGAL_VECTORC3_H
 

 

#ifdef CGAL_DIRECTIONC3_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_DirectionC3<FT> &d)
{
  CGAL_VectorC3<FT> v = d.vector();
  os << "DirectionC3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  return os;
}

#endif // CGAL_DIRECTIONC3_H
 


 

#ifdef CGAL_LINEC3_H

template < class FT >
ostream &operator<<(ostream &os, CGAL_LineC3<FT> &l)
{
  CGAL_kernel_precondition( l.is_defined() );
  os << "LineC3(" << l.point() << ", " << l.direction() << ")";
  return os;
}
#endif  // CGAL_LINEC3_H
 

 

#ifdef CGAL_RAYC3_H

template < class FT >
ostream &operator<<(ostream &os, CGAL_RayC3<FT> &r)
{
  CGAL_kernel_precondition(r.is_defined());
  os << "RayC3(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif // CGAL_RAYC3_H
 

 

#ifdef CGAL_SEGMENTC3_H

template < class FT >
ostream &operator<<(ostream &os, CGAL_SegmentC3<FT> &s)
{

  CGAL_kernel_precondition( is_defined() );
  os << "SegmentC3(" << s.start() <<  ", " << s.end() << ")";
  return os;
}

#endif // CGAL_SEGMENTC3_H
 


 
#ifdef CGAL_PlaneC3_H

template < class FT >
ostream &operator<<(ostream &os, CGAL_PlaneC3<FT> &p)
{
  CGAL_kernel_precondition( p.is_defined() );
  os << "PlaneC3(" << p.a() <<  ", " << p.b() <<   ", ";
  os << p.c() << ", " << p.d() <<")";
  return os;
}

#endif  // CGAL_PlaneC3_H
 

 

#ifdef CGAL_TRIANGLEC3_H

template < class FT >
ostream &operator<<(ostream &os, CGAL_TriangleC3<FT> &t)
{
  CGAL_kernel_precondition( t.is_defined() );
  os << "TriangleC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif // CGAL_TRIANGLEC3_H
 

 

#ifdef CGAL_TETRAHEDRONC3_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_TetrahedronC3<FT> &t)
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  os << "TetrahedronC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] ;
  os <<  ", " << t[3] << ")";
  return os;
}

#endif  // CGAL_TETRAHEDRONC3_H
 




#endif // CGAL_OSTREAMC3_H
