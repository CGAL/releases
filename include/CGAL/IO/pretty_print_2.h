 
// Source: pretty_print_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PRETTY_PRINT_2_H
#define CGAL_PRETTY_PRINT_2_H

#include <ostrstream.h>

 

#ifdef CGAL_POINT_2_H
#ifndef CGAL_POINT_2_PP
#define CGAL_POINT_2_PP

char *db_pretty_print(const CGAL_Point_2< C<double> > *p,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *p << ends ;
  return os.str();
}
#endif // CGAL_POINT_2_PP
#endif // CGAL_POINT_2_H
 


 

#ifdef CGAL_VECTOR_2_H
#ifndef CGAL_VECTOR_2_PP
#define CGAL_VECTOR_2_PP

char *db_pretty_print(const CGAL_Vector_2< C<double> > *v,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *v << ends ;
  return os.str();
}
#endif // CGAL_VECTOR_2_PP
#endif // CGAL_VECTOR_2_H
 


 

#ifdef CGAL_DIRECTION_2_H
#ifndef CGAL_DIRECTION_2_PP
#define CGAL_DIRECTION_2_PP

char *db_pretty_print(const CGAL_Direction_2< C<double> > *d,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *d << ends ;
  return os.str();
}
#endif // CGAL_DIRECTION_2_PP
#endif // CGAL_DIRECTION_2_H
 


 
#ifdef CGAL_LINE_2_H
#ifndef CGAL_LINE_2_PP
#define CGAL_LINE_2_PP

char *db_pretty_print(const CGAL_Line_2< C<double> > *l,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *l << ends ;
  return os.str();
}
#endif // CGAL_LINE_2_PP
#endif // CGAL_LINE_2_H
 


 
#ifdef CGAL_RAY_2_H
#ifndef CGAL_RAY_2_PP
#define CGAL_RAY_2_PP

char *db_pretty_print(const CGAL_Ray_2< C<double> > *r,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *r << ends ;
  return os.str();
}
#endif // CGAL_RAY_2_PP
#endif // CGAL_RAY_2_H
 


 
#ifdef CGAL_SEGMENT_2_H
#ifndef CGAL_SEGMENT_2_PP
#define CGAL_SEGMENT_2_PP

char *db_pretty_print(const CGAL_Segment_2< C<double> > *s,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *s << ends ;
  return os.str();
}
#endif // CGAL_SEGMENT_2_PP
#endif // CGAL_SEGMENT_2_H
 


 
#ifdef CGAL_TRIANGLE_2_H
#ifndef CGAL_TRIANGLE_2_PP
#define CGAL_TRIANGLE_2_PP

char *db_pretty_print(const CGAL_Triangle_2< C<double> > *t,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *t << ends ;
  return os.str();
}
#endif // CGAL_TRIANGLE_2_PP
#endif // CGAL_TRIANGLE_2_H
 


 
#ifdef CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_ISO_RECTANGLE_2_PP
#define CGAL_ISO_RECTANGLE_2_PP

char *db_pretty_print(const CGAL_Iso_rectangle_2< C<double> > *t,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *t << ends ;
  return os.str();
}
#endif // CGAL_ISO_RECTANGLE_2_PP
#endif // CGAL_ISO_RECTANGLE_2_H
 


 

#ifdef CGAL_BBOX_2_H
#ifndef CGAL_BBOX_2_PP
#define CGAL_BBOX_2_PP

char *db_pretty_print(const CGAL_Bbox_2 *b,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *b << ends ;
  return os.str();
}
#endif // CGAL_BBOX_2_PP
#endif // CGAL_BBOX_2_H
 


 
#ifdef CGAL_PARABOLA_2_H
#ifndef CGAL_PARABOLA_2_PP
#define CGAL_PARABOLA_2_PP

char *db_pretty_print(const CGAL_parabola_2< C<double> > *p,
                      int flags,
                      char *formatstring)
{
  ostrstream os;
  os << *p << ends ;
  return os.str();
}
#endif // CGAL_PARABOLA_2_PP
#endif // CGAL_PARABOLA_2_H
 


 

 


#endif // CGAL_PRETTY_PRINT_2_H
