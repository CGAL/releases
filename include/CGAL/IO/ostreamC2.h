 
// Source: ostreamC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_OSTREAMC2_H
#define CGAL_OSTREAMC2_H

 

#ifdef CGAL_POINTC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_PointC2<FT> &p)
{
  os << "PointC2(" << p.x() << ", " << p.y() << ")";
  return os;
}

#endif // CGAL_POINTC2_H
 


 

#ifdef CGAL_VECTORC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_VectorC2<FT> &v)
{
  os << "VectorC2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif  // CGAL_VECTORC2_H
 


 

#ifdef CGAL_DIRECTIONC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_DirectionC2<FT> &d)
{
  CGAL_VectorC2<FT> v = d.vector();
  os << "DirectionC2(" << v.x() << ", " << v.y() << ")";
  return os;
}

#endif // CGAL_DIRECTIONC2_H
 


 

#ifdef CGAL_LINEC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_LineC2<FT> &l)
{
  CGAL_kernel_precondition( l.is_defined() );
  os << "LineC2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif // CGAL_LINEC2_H
 


 

#ifdef CGAL_RAYC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_RayC2<FT> &r)
{
  CGAL_kernel_precondition(is_defined());
  os << "RayC2(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif // CGAL_RAYC2_H
 


 

#ifdef CGAL_SEGMENTC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_SegmentC2<FT> &s)
{
  CGAL_kernel_precondition(s.is_defined());
  os << "SegmentC2(" << s.start() <<  ", " << s.end() << ")";
  return os;
}

#endif // CGAL_SEGMENTC2_H
 


 

#ifdef CGAL_TRIANGLEC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_TriangleC2<FT> &t)
{
  os << "TriangleC2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif // CGAL_TRIANGLEC2_H
 


 

#ifdef CGAL_ISO_RECTANGLEC2_H

template < class FT >
ostream &operator<<(ostream &os, const CGAL_Iso_rectangleC2<FT> &r)
{
  os << "Iso_rectangleC2(" << r[0] <<  ", " << r[2] << ")";
  return os;
}

#endif // CGAL_ISO_RECTANGLEC2_H
 


 
#ifdef CGAL_PARABOLAC2_H
template < class FT >
ostream &operator<<(ostream &os, const CGAL_ParabolaC2<FT> &p)
{
  os << "ParabolaC2((" << p.base() << ", " << p.direction() 
     << ", " << p.curvature()  << "),";
  return os;
}
#endif // CGAL_PARABOLAC2_H
 


 

#ifdef CGAL_AFF_TRANSFORMATIONC2_H
template < class FT >
ostream &operator<<(ostream &os, const CGAL_Aff_transformationC2<FT> &t)
{
  return t.print(os);
}
#endif // CGAL_AFF_TRANSFORMATIONC2_H
 


#endif // CGAL_OSTREAMC2_H
