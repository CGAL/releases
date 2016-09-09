 
#ifndef CGAL_GEOMVIEW_STREAM_H
#define CGAL_GEOMVIEW_STREAM_H

#include <LEDA/basic.h>
#include <LEDA/string.h>
#include <LEDA/array.h>
#include <LEDA/h_array.h>

#include <CGAL/IO/pipebuf.h>
#include <CGAL/IO/Color.h>

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <strstream.h>
#include <iomanip.h>

#include <sys/types.h>
#include <sys/uio.h>

 
class CGAL_Geomview_stream
{
  friend  CGAL_Geomview_stream &binary(CGAL_Geomview_stream &os);

  friend  CGAL_Geomview_stream &ascii(CGAL_Geomview_stream &os);

public:
  CGAL_Geomview_stream(const char *machine,
                       const char *login,
                       const CGAL_Bbox_3 &bbox = CGAL_Bbox_3(0,0,0, 1,1,1));

  ~CGAL_Geomview_stream();

  CGAL_Geomview_stream &operator<<(const CGAL_Color &c);

  CGAL_Geomview_stream &operator<<(const char *cptr);

  CGAL_Geomview_stream &operator<<(int i);
  CGAL_Geomview_stream &operator<<(double d);
  CGAL_Geomview_stream &operator<< (
                         CGAL_Geomview_stream& (*fct)(CGAL_Geomview_stream&));

  CGAL_Geomview_stream &operator>>(char *sexpr);


  // public but that will change to make it proper
  int bbox_2_count;
  int bbox_3_count;
  int triangle_count;
  int segment_count;
  int point_count;
  int tetrahedron_count;

  CGAL_Color col;
 
private:

  void pickplane(const CGAL_Bbox_3 &bbox);
  void frame(const CGAL_Bbox_3 &bbox);
  void setup_geomview(const char *machine, const char *login);

  inline int Binary(){ return bflag ;}

  CGAL_pipebuf buffer;

  int pid;      // the geomview process identification
  int bflag ;   // bool that makes operator<< write binary format


  char s[512];
};

 


 
#ifdef CGAL_SEGMENT_3_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Segment_3<R> &segment)
{
  ostrstream os;
  os << "seg" << gv.segment_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id << " { " ;
  gv << "VECT " ;
  gv << 1 <<  2 << 1  ;  // 1 polyline, two vertices, 1 color
  gv << 2  ;             // the first polyline contains 2 vertices
  gv << 1  ;             // and it has 1 color

  // here are start and end points
  gv << segment.start().x() << segment.start().y() << segment.start().z();
  gv << segment.end().x() << segment.end().y() << segment.end().z()  ;

  // and the color of the segment and its opaqueness
  gv  << gv.col.r()  << gv.col.g()  << gv.col.b()  << 1.0 ;

  // close the text bracket
  gv << "})" ;

  return gv;
}
#endif // CGAL_SEGMENT_3_H
 
#ifdef CGAL_SEGMENT_2_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Segment_2<R> &segment)
{
  ostrstream os;
  os << "seg" << gv.segment_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id << " { " ;
  gv << "VECT " ;
  gv << 1 <<  2 << 1  ;  // 1 polyline, two vertices, 1 color
  gv << 2  ;             // the first polyline contains 2 vertices
  gv << 1  ;             // and it has 1 color

  // here are start and end points
  gv << segment.start().x()  << segment.start().y()  << 0.0  ;
  gv << segment.end().x()  << segment.end().y()  << 0.0  ;

  // and the color of the segment and its opaqueness
  gv  << col.r()  << col.g()  << col.b()  << 1.0 ;

  // close the text bracket
  gv << "})" ;

  return gv;
}
#endif //CGAL_SEGMENT_2_H
 
#ifdef CGAL_TRIANGLE_3_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Triangle_3<R> &t)
{
  ostrstream os;
  os << "tr" << gv.triangle_count++ << ends;
  char *id = os.str();


  gv << ascii;
  gv << "(geometry " << id << " {appearance {+edge material { edgecolor ";
  gv  << col.r()  << col.g()  << col.b() <<  " } shading constant}{ ";
  gv << binary ;
  // it's a planar polygon
  gv << "OFF BINARY\n" ;

  // it has 3 vertices, 1 face and 3 edges
  gv << 3 << 1 << 3 ;

  for(int i=0; i<3; i++){
    gv << t[i].x() << t[i].y() << t[i].z() ;
  }

  // the face
  gv << 3 << 0 << 1 << 2 << 4 << col.r() << col.g() << col.b() << 1.0 ;
  gv << "}})" ;

  return gv;
}
#endif // CGAL_TRIANGLE_3_H
 
#ifdef CGAL_POINT_2_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Point_2<R> &point)
{
  ostrstream os;
  os << "p" << gv.point_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id  << "  {appearance {linewidth 3}{ " ;

  gv << "SKEL 1 1 " ;

  gv << point.x()  << point.y()  << 0.0  ;
  gv << "1 0\n" ;
  gv << "}})" ;

  return gv;
}
#endif // CGAL_POINT_2_H
 
#ifdef CGAL_POINT_3_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Point_3<R> &point)
{
  ostrstream os;
  os << "p" << gv.point_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id  << "  {appearance {linewidth 3}{ " ;

  gv << "SKEL 1 1 " ;

  gv << point.x()  << point.y()  << point.z()  ;
  gv << "1 0\n" ;
  gv << "}})" ;

  return gv;
}
#endif // CGAL_POINT_3_H
 
#ifdef CGAL_TETRAHEDRON_3_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 const CGAL_Tetrahedron_3<R> &t)
{
  ostrstream os;
  os << "tetra" << gv.tetrahedron_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id  << "  {appearance {}{ " ;
 gv << binary ;
  // it's a planar polygon
  gv << "OFF BINARY\n" ;

  // it has 4 vertices, 4 face and 6 edges
  gv << 4 << 4 << 6 ;

  // the vertices
  for(int i=0; i<4; i++){
    gv << t[i].x() << t[i].y() << t[i].z() ;
  }

  // the faces
  gv << 3 << 0 << 1 << 2 << 4 << gv.col.r() << gv.col.g() << gv.col.b() << 1.0 ;
  gv << 3 << 3 << 0 << 1 << 4 << gv.col.r() << gv.col.g() << gv.col.b() << 1.0 ;
  gv << 3 << 3 << 1 << 2 << 4 << gv.col.r() << gv.col.g() << gv.col.b() << 1.0 ;
  gv << 3 << 3 << 0 << 2 << 4 << gv.col.r() << gv.col.g() << gv.col.b() << 1.0 ;

  gv << "}})" ;

  return gv;
}
#endif  // CGAL_TETRAHEDRON_3_H
 

#ifdef CGAL_POLYHEDRON_3_H
template < class R >
CGAL_Geomview_stream &operator<<(CGAL_Geomview_stream &gv,
                                 list< list< CGAL_Point_3<R> > > &L)
{
  ostrstream os;
  os << "poly" << gv.tetrahedron_count++ << ends ;
  char *id = os.str();

  gv << ascii;
  gv << "(geometry " << id  << "  {appearance {}{ " ;
  //gv << binary ;
  // it's a planar polygon
  gv << "OFF \n" ;

  int vertices = 0,
      faces = L.length(),
    edges = 0;  // not relevant for OFF format

  list_item it = L.first();
  while(it){
    list< CGAL_Point_3<R> > &l = L[it];
    vertices += l.length();
    it = l.succ(it);
  }

  gv << vertices << faces << vertices ;

  // the vertices
  it = L.first();
  while(it){
    list< CGAL_Point_3<R> > &l = L[it];
    CGAL_Point_3<R> p;
    forall(p,l){
      gv << p.x() << p.y() << p.z() ;
    }
    it = L.succ(it);
  }


  // the faces
  it = L.first();
  int n = 0,
      i = 0;

  while(it){
    list< CGAL_Point_3<R> > &l = L[it];
    gv << l.length();
    n += l.length();

    while(i < n){
      gv << i++ ;
    }
    gv << gv.col.r() << gv.col.g() << gv.col.b() << 1.0 ;
    it = L.succ(it);
  }

  gv  << "}})" ;

  return gv;
}
#endif  // CGAL_POLYHEDRON_3_H
 


 
template < class R >
void parse_point(const string &pickpoint,
                 CGAL_Point_3<R> &point)
{
  strstream ss;
  ss << pickpoint << ends ;

  double x,y,z,w;
  char parenthesis;
  ss >> parenthesis >> x >> y >> z >> w;
  point  = CGAL_Point_3<R>(x, y, z, w);
}
 


 
#ifdef CGAL_POINT_3_H
template < class R >
CGAL_Geomview_stream &operator>>(CGAL_Geomview_stream &gv,
                                 CGAL_Point_3<R> &point)
{
  char sexpr[100];

  char gclpick[100];

  strcpy(gclpick, "(pick world pickplane * nil nil nil nil nil nil nil)");

  cout << "input a point " << endl ;

  gv << ascii ;

  gv << "(pickable pickplane yes) (ui-target pickplane yes)";
  gv << "(interest " << gclpick <<")" ;

  gv >> sexpr;  // this reads a gcl expression
  string  str(sexpr);
  string pickpoint = nth(str,4);
  // this gives something as: (0.0607123 0.0607125 4.76837e-07 0.529628)

  parse_point(pickpoint,point);

  // we are done and tell geomview to stop sending pick events
  gv << "(uninterest " << gclpick  << ") (pickable pickplane no)" ;

  return gv ;
}
#endif // CGAL_POINT_3_H
 


#endif // CGAL_GEOMVIEW_STREAM_H
