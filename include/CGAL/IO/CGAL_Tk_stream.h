 
// Source: CGAL_Tk_stream.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_CGAL_TK_STREAM_H
#define CGAL_CGAL_TK_STREAM_H


#include <fstream.h>
#include <strstream.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <CGAL/IO/Color.h>

 
class CGAL_Tk_stream {
public:
  CGAL_Tk_stream(int xpix, int ypix);
  ~CGAL_Tk_stream();
    
  void init(double xmin, double xmax, double ymin);

  int mapx(double x) const
  {
    return multx * x - constx;
  }

  int mapy(double y) const
  {
    return Y - multy * y + consty;
  }

  double imapx(int x) const
  {
    return (x + constx)/multx;
  }

  double imapy(int y) const
  {
    return (y - consty - Y)/ -multy;
  }

  fstream toTk;
  fstream fromTk;

private:
  double X, Y;
  double multx, constx;
  double multy, consty;

  static int count;
};

int CGAL_Tk_stream::count = 0;
 
inline CGAL_Tk_stream::CGAL_Tk_stream(int xpix, int ypix)
    : X(xpix), Y(ypix)
{
  ostrstream s;
  s << "CgalTk " << xpix << " " << ypix << " " << count << "&" << ends;
  system(s.str());

  struct stat buf;

  ostrstream Cgal, Tk;
  Cgal << "/tmp/TkToCgal_" << count << ends;
  Tk   << "/tmp/CgalToTk_" << count << ends;
  char* Cgal_str = Cgal.str();
  char* Tk_str = Tk.str();

  while ((stat(Cgal_str, &buf) == -1) ||
         (stat(Tk_str, &buf) == -1)) {
    sleep(5);
  }

  toTk.open(Tk_str, ios::in | ios::out);
  fromTk.open(Cgal_str, ios::in | ios::out);
  count++;
}

inline CGAL_Tk_stream::~CGAL_Tk_stream()
{
  toTk << "cgExit";
}
 
inline void CGAL_Tk_stream::init(double xmin, double xmax, double ymin)
{
  double ymax = Y * (xmax -xmin) / X + ymin;
  
  multx  = X / (xmax - xmin);
  constx = (X * xmin) / (xmax - xmin);
  multy  = Y / (ymax - ymin);
  consty = (Y * ymin) / (ymax - ymin);
}
 


 
inline CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Color &c)
{

  ostrstream s;
  char *rfill = (c.red()<=15) ? "0" : "";
  char *gfill = (c.green()<=15) ? "0" : "";
  char *bfill = (c.blue()<=15) ? "0" : "";
  s << "#" << hex << rfill << c.red()
                  << gfill << c.green()
                  << bfill << c.blue() << ends;
  char *cptr = s.str();
  os.toTk << "cgSetOutlineColor " << cptr  << endl;
  os.toTk << "cgSetFillColor " << cptr  << endl;
  return os;
}
 


 

#ifdef CGAL_POINT_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Point_2<R> &p)
{

  os.toTk << "cgDrawPoint_2 " << os.mapx(CGAL_to_double(p.x())) << " " 
                              << os.mapy(CGAL_to_double(p.y())) << endl;
  return os;
}

template < class R >
CGAL_Tk_stream &operator>>(CGAL_Tk_stream &os, CGAL_Point_2<R> &p)
{
  double x, y;
  os.toTk << "cgReadPoint_2" << endl;
  
  os.fromTk >> x >> y;

  os.toTk << "cgUnbindButton1" << endl;
  p = CGAL_Point_2<R>(R::FT(os.imapx(x)),
                      R::FT(os.imapy(y))) ;
  return os;
}

#endif // CGAL_POINT_2_H
 


 

#ifdef CGAL_LINE_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Line_2<R> &l)
{

  os << "Line_2(" << l.a() << ", "<< l.b() << ", " << l.c() << ")";
  return os;
}

#endif // CGAL_LINE_2_H
 


 

#ifdef CGAL_RAY_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Ray_2<R> &r)
{

  os << "Ray_2(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif // CGAL_RAY_2_H
 


 

#ifdef CGAL_SEGMENT_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Segment_2<R> &s)
{

  CGAL_Point_2<R> st = s.source(),
                  ta = s.target();
  os.toTk << "cgDrawSegment_2 " 
          << os.mapx(CGAL_to_double(st.x())) << " " 
          << os.mapy(CGAL_to_double(st.y())) << " "
          << os.mapx(CGAL_to_double(ta.x())) << " "
          << os.mapy(CGAL_to_double(ta.y())) 
          << endl;
  return os;
}

#endif // CGAL_SEGMENT_2_H
 


 

#ifdef CGAL_TRIANGLE_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Triangle_2<R> &t)
{
  os << "Triangle_2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif // CGAL_TRIANGLE_2_H
 


 

#ifdef CGAL_ISO_RECTANGLE_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Iso_rectangle_2<R> &r)
{
  os << "Iso_rectangle_2(" << r.vertex(0) <<  ", " << r.vertex(2) << ")";
  return os;
}

#endif // CGAL_ISO_RECTANGLE_2_H
 


 

#ifdef CGAL_BBOX_2_H

inline CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Bbox_2 &bbox)
{

  return os;
}

#endif // CGAL_BBOX_2_H
 


 
#ifdef CGAL_PARABOLA_2_H
template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Parabola_2<R> &p)
{
  os << "Parabola_2((" << p.base() << ", " << p.direction() 
     << ", " << p.curvature()  << "),";
  return os;
}
#endif // CGAL_PARABOLA_2_H
 


 

#ifdef CGAL_CIRCLE_2_H

template < class R >
CGAL_Tk_stream &operator<<(CGAL_Tk_stream &os, const CGAL_Circle_2<R> &t)
{
  os << "Circle_2(" << t.center() <<  ", " << t.radius()  <<")";
  return os;
}

#endif // CGAL_CIRCLE_2_H
 



#endif // CGAL_CGAL_TK_STREAM_H
