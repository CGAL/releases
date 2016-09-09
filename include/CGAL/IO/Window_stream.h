 
// Source: Window_stream.h
// Author: Andreas.Fabri@sophia.inria.fr
#ifndef CGAL_WINDOW_STREAM_H
#define CGAL_WINDOW_STREAM_H


#include <CGAL/IO/Color.h>

#include <LEDA/window.h>

 
class CGAL_Window_stream : public window  {

public:
  CGAL_Window_stream(float xpix = 300.0,
                     float ypix = 300.0,
                     float xpos = 400.0,
                     float ypos = 400.0)
    : window(xpix, ypix)
  {
    window::display(int(xpos), int(ypos));
  }

  void color_init()
  {
    CGAL_black = CGAL_Color(0.0, 0.0, 0.0);
    CGAL_white = CGAL_Color(1.0, 1.0, 1.0);
    CGAL_red = CGAL_Color(1.0, 0.0, 0.0);
    CGAL_green = CGAL_Color(0.0, 1.0, 0.0);
    CGAL_blue = CGAL_Color(0.0, 0.0, 1.0);
    CGAL_violet = CGAL_Color(1.0, 0.0, 1.0);
    CGAL_orange = CGAL_Color(1.0, 0.75, 0.0);
    set_fg_color(black);
  }

  void init(const CGAL_Bbox_2 &b = CGAL_Bbox_2(0, 0, 100, 100))
  {
    window::init(b.xmin(), b.xmax(), b.ymin());
    color_init();
  }

  void init(double x0, double x1, double y0)
  {
    window::init(x0, x1, y0);
    color_init();
  }

  int read_mouse(double& x, double& y)
  {
    button = window::read_mouse(x,y);
    return button;
  }

  int last_button_pressed()
  {
    return button;
  }
  // we keep the foreground color in a field, as LEDA's window
  // can't store it in the shared library version
private:
  int button;

};
 


 
#ifdef CGAL_POINT_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w, const CGAL_Point_2<R> &p)
{
  w.draw_point(CGAL_to_double(p.x()), CGAL_to_double(p.y()));
  return w;
}


template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w, CGAL_Point_2<R> &p)
{
  double x, y;
  w.read_mouse(x,y);
  w.draw_point(x,y);
  p = CGAL_Point_2<R>(x,y);
  return w;
}
#endif //  CGAL_POINT_2_H
 

 
#ifdef CGAL_LINE_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,const CGAL_Segment_2<R> &s)
{
  w.draw_segment(CGAL_to_double(s.start().x()), CGAL_to_double(s.start().y()),
                 CGAL_to_double(s.end().x()), CGAL_to_double(s.end().y()));
  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w,
                               CGAL_Segment_2<R> &s)
{
  double x1, y1, x2, y2;
  w.read_mouse(x1,y1);
  w.read_mouse_seg(x1,y1, x2, y2);
  w.draw_segment(x1,y1, x2, y2);
  s = CGAL_Segment_2<R>(CGAL_Point_2<R>(x1,y1),
                        CGAL_Point_2<R>(x2,y2));
  return w;
}


template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w, const CGAL_Line_2<R> &l)
{
  CGAL_Point_2<R> p1 = l.point(),
                  p2 = p1 + l.direction().vector();

  w.draw_line(CGAL_to_double(p1.x()), CGAL_to_double(p1.y()),
              CGAL_to_double(p2.x()), CGAL_to_double(p2.y()));
  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w, CGAL_Line_2<R> &l)
{
  double x1, y1, x2, y2;
  w.read_mouse(x1,y1);
  w.read_mouse_seg(x1,y1, x2, y2);
  w.draw_line(x1,y1, x2, y2);

  l = CGAL_Line_2<R>(CGAL_Point_2<R>(x1,y1),
                     CGAL_Point_2<R>(x2,y2));
  return w;
}
#endif //CGAL_LINE_2_H



#ifdef CGAL_RAY_2_H

#include <CGAL/intersection_2_1.h>

template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w, const CGAL_Ray_2<R> &r)
{


  CGAL_Point_2< C<double> > p;
  CGAL_Segment_2< C<double> > s, segment;

  CGAL_Bbox_2 bbox(w.xmin(), w.ymin(), w.xmax(), w.ymax());

  CGAL_Bbox_2_Ray_2_pair<R> pair(&bbox, &r);

  switch (pair.intersection_type()){
  case CGAL_Bbox_2_Ray_2_pair<R>::NO :
    return w;
  case CGAL_Bbox_2_Ray_2_pair<R>::POINT :
    pair.intersection(p);
    w.draw_segment(CGAL_to_double(r.start().x()), CGAL_to_double(r.start().y()),
                   p.x(), p.y());
    return w;
  case CGAL_Bbox_2_Ray_2_pair<R>::SEGMENT :
    pair.intersection(s);
    w.draw_segment(s.start().x(), s.start().y(),
                   s.end().x(), s.end().y());
    return w;
  }
  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w, CGAL_Ray_2<R> &r)
{
  double x1, y1, x2, y2;
  w.read_mouse(x1,y1);
  w.read_mouse_seg(x1,y1, x2, y2);
  r = CGAL_Ray_2<R>(CGAL_Point_2<R>(x1,y1),
                    CGAL_Point_2<R>(x2,y2));
  w << r;
  return w;
}
#endif //CGAL_RAY_2_H

 

 
#ifdef CGAL_ISO_RECTANGLE_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Iso_rectangle_2<R> &r)
{
  double xmin = CGAL_to_double(r.min().x()),
         ymin = CGAL_to_double(r.min().y()),
         xmax = CGAL_to_double(r.max().x()),
         ymax = CGAL_to_double(r.max().y());


  w.draw_segment(xmin, ymin, xmax, ymin);
  w.draw_segment(xmax, ymin, xmax, ymax);
  w.draw_segment(xmax, ymax, xmin, ymax);
  w.draw_segment(xmin, ymax, xmin, ymin);

  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w,
                               CGAL_Iso_rectangle_2<R> &r)
{
  double x1, y1, x2, y2;
  w.read_mouse(x1,y1);
  w.read_mouse_rect(x1,y1, x2, y2);
  r = CGAL_Iso_rectangle_2<R>(CGAL_Point_2<R>(x1,y1),
                              CGAL_Point_2<R>(x2,y2));
  w << r;
  return w;
}

#endif // CGAL_ISO_RECTANGLE_2_H
 

 
#ifdef CGAL_PARABOLA_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Parabola_2<R> &par)
{
  double width = w.xmax()-w.xmin();
  double height = w.ymax()-w.ymin();
  double diag_sq = width*width + height*height;

  double lambda=1.0;
  
  CGAL_Point_2<R> p1 = par.base(),
                  p2;

  while((par(lambda)-p1).operator*(par(lambda)-p1) < diag_sq){
    lambda *= 2.0;
  }

  while((par(lambda)-p1).operator*(par(lambda)-p1) > diag_sq){
    lambda /= 2.0;
  }

  lambda *= 2.0;
  double delta = lambda/50.0;

  int i;
  for(lambda = 0.0, i=0; i<=50 ; lambda += delta,i++){
    p2 = par(lambda);
    w << CGAL_Segment_2<R>(p1,p2);
    p1 = p2;
  }
  p1 = par.base();
  for(lambda = 0.0, i=0; i<=50 ; lambda -= delta,i++){
    p2 = par(lambda);
    w << CGAL_Segment_2<R>(p1,p2);
    p1 = p2;
  }
  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w,
                               CGAL_Parabola_2<R> &par)
{
  CGAL_Line_2<R> l;
  CGAL_Point_2<R> p;
  w >> l;
  w >> p;
  par = CGAL_Parabola_2<R>(l,p);
  w << par;
  return w;
}

#endif // CGAL_PARABOLA_2_H
 

 
#ifdef CGAL_PARABOLA_ARC_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Parabola_arc_2<R> &arc)
{
  double lambda, lmin, lmax;

  if (arc.lambda_end() > arc.lambda_start()){
    lmin = arc.lambda_start();
    lmax = arc.lambda_end();
  } else {
    lmin = arc.lambda_end();
    lmax = arc.lambda_start();
  }

  double delta = CGAL_abs(lmax - lmin)/100.0;

  CGAL_Point_2<R> p1 = arc.start();
  for(lambda = lmin;  lambda <= lmax; lambda += delta)
    {
      CGAL_Point_2<R> p2 = arc.supporting_parabola()(lambda);
      w << CGAL_Segment_2<R>(p1,p2);
      p1 = p2;
    }
  return w;
}
#endif // CGAL_PARABOLA_ARC_2_H
 


 
CGAL_Window_stream& operator<<(CGAL_Window_stream &w, const CGAL_Color& c)
{
  if ((c.r() == 0.0) && (c.g() == 0.0) && (c.b() == 0.0)) {
    w.set_fg_color(black);
  }
  else if ((c.r() == 1.0) && (c.g() == 1.0) && (c.b() == 1.0)) {
    w.set_fg_color(white);
  }
  else if ((c.r() == 0.0) && (c.g() == 0.0) && (c.b() == 1.0)) {
    w.set_fg_color(blue);
  }
  else if ((c.r() == 0.0) && (c.g() == 1.0) && (c.b() == 0.0)) {
    w.set_fg_color(green);
  }
  else if ((c.r() == 1.0) && (c.g() == 0.0) && (c.b() == 0.0)) {
    w.set_fg_color(red);
  }
  else if ((c.r() == 1.0) && (c.g() == 0.75) && (c.b() == 0.0)) {
    w.set_fg_color(orange);
  }
  else if ((c.r() == 1.0) && (c.g() == 0.0) && (c.b() == 1.0)) {
    w.set_fg_color(violet);
  }
  else {
    cerr << "Warning: color(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
    cerr << "not available." << endl;
    w.set_fg_color(black);
  }
  return w;
}
 

 
#ifdef CGAL_BBOX_2_H
inline CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                                      const CGAL_Bbox_2 &b)
{
  line_style style = w.set_line_style(dotted);
  double xmin = b.xmin(),
         ymin = b.ymin(),
         xmax = b.xmax(),
         ymax = b.ymax();


  w.draw_segment(xmin, ymin, xmax, ymin);
  w.draw_segment(xmax, ymin, xmax, ymax);
  w.draw_segment(xmax, ymax, xmin, ymax);
  w.draw_segment(xmin, ymax, xmin, ymin);

  w.set_line_style(style);
  return w;
}
#endif // CGAL_BBOX_2_H
 


#endif // CGAL_WINDOW_STREAM_H

