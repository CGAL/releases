#line 543 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
// Source: Window_stream.h
// Author: Andreas.Fabri@sophia.inria.fr
#ifndef CGAL_WINDOW_STREAM_H
#define CGAL_WINDOW_STREAM_H


#include <CGAL/IO/Color.h>

#include <LEDA/window.h>
#include <LEDA/REDEFINE_NAMES.h>
typedef window LEDA_Window;
#include <LEDA/UNDEFINE_NAMES.h>

#line 20 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
class CGAL_Window_stream : public LEDA_Window  {

public:
  CGAL_Window_stream(int xpix = 300,
                     int ypix = 300,
                     int xpos = 400,
                     int ypos = 400)
    : LEDA_Window(xpix, ypix)
  {
    set_frame_label("CGAL_Window_stream");
    LEDA_Window::display(xpos, ypos);
  }



  void init(const CGAL_Bbox_2 &b = CGAL_Bbox_2(0, 0, 100, 100))
  {
    LEDA_Window::init(b.xmin(), b.xmax(), b.ymin());
    set_fg_color(black);
  }

  void init(double xmin, double xmax, double ymin)
  {
    LEDA_Window::init(xmin, xmax, ymin);
    set_fg_color(black);
  }

  int read_mouse(double& x, double& y)
  {
    button = LEDA_Window::read_mouse(x,y);
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
#line 556 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#line 68 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
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
#line 558 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 91 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_LINE_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,const CGAL_Segment_2<R> &s)
{
  w.draw_segment(CGAL_to_double(s.source().x()),
                 CGAL_to_double(s.source().y()),
                 CGAL_to_double(s.target().x()),
                 CGAL_to_double(s.target().y()));
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

#include <CGAL/Object.h>
#include <CGAL/intersection_2_1.h>

template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w, const CGAL_Ray_2<R> &r)
{
  CGAL_Point_2<R> p;
  CGAL_Segment_2<R> s;
  CGAL_Point_2<R> point[4];
  CGAL_Point_2<R> ipoint[2];

  point[0] = CGAL_Point_2<R>(w.xmin(), w.ymin());
  point[1] = CGAL_Point_2<R>(w.xmin(), w.ymax());
  point[2] = CGAL_Point_2<R>(w.xmax(), w.ymax());
  point[3] = CGAL_Point_2<R>(w.xmax(), w.ymin());

  int no_of_intersections = 0;
  for(int i=0; i < 4; i++) {
    CGAL_Segment_2<R> seg(point[i],point[(i+1)%4]);
    CGAL_Object o = CGAL_intersection(seg, r);
    if ( CGAL_assign(p, o) ) {
      ipoint[no_of_intersections] = p;
      no_of_intersections++;
    }else if( CGAL_assign(s, o) ) {
      w.draw_segment(CGAL_to_double(s.source().x()),
                     CGAL_to_double(s.source().y()),
                     CGAL_to_double(s.target().x()),
                     CGAL_to_double(s.target().y()));
      return w;
    }
  }

  if( no_of_intersections == 1 ) {
    // the start point of the ray is inside the window

    w.draw_segment(CGAL_to_double(r.source().x()),
                   CGAL_to_double(r.source().y()),
                   CGAL_to_double(ipoint[0].x()),
                   CGAL_to_double(ipoint[0].y()));
  } else if( no_of_intersections == 2 ) {
    w.draw_segment(CGAL_to_double(ipoint[0].x()),
                   CGAL_to_double(ipoint[0].y()),
                   CGAL_to_double(ipoint[1].x()),
                   CGAL_to_double(ipoint[1].y()));
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

#line 559 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#line 387 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_TRIANGLE_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Triangle_2<R> &t)
{
  double x0 = CGAL_to_double(t.vertex(0).x()),
         y0 = CGAL_to_double(t.vertex(0).y()),
         x1 = CGAL_to_double(t.vertex(1).x()),
         y1 = CGAL_to_double(t.vertex(1).y()),
         x2 = CGAL_to_double(t.vertex(2).x()),
         y2 = CGAL_to_double(t.vertex(2).y());


  w.draw_segment(x0, y0, x1, y1);
  w.draw_segment(x1, y1, x2, y2);
  w.draw_segment(x2, y2, x0, y0);

  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w,
                               CGAL_Triangle_2<R> &t)
{
  double x0, y0, x1, y1, x2, y2;
  w.read_mouse(x0,y0);
  w.read_mouse_seg(x0,y0, x1, y1);
  w.draw_seg(x0,y0, x1, y1);
  w.read_mouse_seg(x1,y1, x2, y2);
  w.draw_seg(x1,y1, x2, y2);
  w.draw_seg(x2,y2, x0, y0);
  r = CGAL_Triangle_2<R>(CGAL_Point_2<R>(x0,y0),
                         CGAL_Point_2<R>(x1,y1),
                         CGAL_Point_2<R>(x2,y2));
  return w;
}

#endif // CGAL_TRIANGLE_2_H
#line 561 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 435 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_TRIANGULATION_ELEMENT_2_H
template < class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &os,
                               const CGAL_Triangulation_element_2<R> *t)
{

  switch(t->finite_vertices()){
  case 3 :
    {
      os <<  t->triangle();
      break;
    }
  case 2 :
    {
      int fi = 0;
      if (! t->is_finite(1)){
        fi = 1;
      }else if(! t->is_finite(2)){
        fi = 2;
      }
      os << CGAL_Segment_2<R>((*t)[fi-1], (*t)[fi+1]);
      os << CGAL_Ray_2<R>((*t)[fi+2],
                          (*t)[fi+2] + ((*t)[fi] - CGAL_ORIGIN));
      os << CGAL_Ray_2<R>((*t)[fi+1],
                          (*t)[fi+1] + ((*t)[fi] - CGAL_ORIGIN));
   break;
    }
  case 1:
    {
      int fi = 0;
      if (t->is_finite(1)){
        fi = 1;
      }else if(t->is_finite(2)){
        fi = 2;
      }

      os << CGAL_Ray_2<R>((*t)[fi],
                          (*t)[fi]+ ((*t)[fi+1] - CGAL_ORIGIN));
      os << CGAL_Ray_2<R>((*t)[fi],
                          (*t)[fi]+ ((*t)[fi+2] - CGAL_ORIGIN));
      break;
    }
  }
  return os;
}
#endif // CGAL_TRIANGULATION_ELEMENT_2_H
#line 562 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 487 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_TRIANGULATION_2_H

template < class R >
CGAL_Window_stream &operator<<(CGAL_Window_stream &os,
                               CGAL_Triangulation_2<R> &T)
{
  CGAL_Triangulation_element_2<R> *t;

  forall_triangulation_elements(t, T){
    os << t;
  }
  return os;
}
#endif //  CGAL_TRIANGULATION_2_H
#line 563 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#line 310 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
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
#line 565 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 219 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
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
#line 566 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 278 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_PARABOLA_ARC_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Parabola_arc_2<R> &arc)
{
  double lambda, lmin, lmax;

  if (arc.lambda_target() > arc.lambda_source()){
    lmin = arc.lambda_source();
    lmax = arc.lambda_target();
  } else {
    lmin = arc.lambda_target();
    lmax = arc.lambda_source();
  }

  double delta = CGAL_abs(lmax - lmin)/100.0;

  CGAL_Point_2<R> p1 = arc.source();
  for(lambda = lmin;  lambda <= lmax; lambda += delta)
    {
      CGAL_Point_2<R> p2 = arc.supporting_parabola()(lambda);
      w << CGAL_Segment_2<R>(p1,p2);
      p1 = p2;
    }
  return w;
}
#endif // CGAL_PARABOLA_ARC_2_H
#line 567 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#line 349 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
#ifdef CGAL_CIRCLE_2_H
template< class R >
CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                               const CGAL_Circle_2<R> &c)
{
  double cx = CGAL_to_double(c.center().x()),
         cy = CGAL_to_double(c.center().y()),
         r = CGAL_to_double(c.squared_radius());

  w.draw_circle(cx, cy , sqrt(r));
  return w;
}

template< class R >
CGAL_Window_stream& operator>>(CGAL_Window_stream &w,
                               CGAL_Circle_2<R> &c)
{
  double cx, cy, x1, y1;
  w.read_mouse(cx,cy);
  w.read_mouse_circle(cx,cy, x1, y1);
  CGAL_Point_2<R> center(cx, cy),
                  p(x1, y1);

  CGAL_Vector_2<R> v = center - p;
  R::FT sr = v*v;

  w.draw_circle(cx, cy , sqrt(sr));
  c = CGAL_Circle_2<R>(center, sr);
  return w;
}

#endif // CGAL_CIRCLE_2_H
#line 569 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#line 531 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
inline CGAL_Window_stream& operator<<(CGAL_Window_stream &w,
                                      const CGAL_Color& c)
{
  w.set_fg_color(color(c.red(), c.green(), c.blue()));

  return w;
}
#line 571 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"

#line 506 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"
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
#line 572 "/u/sargas/2/prisme/fabri/Cgal/IO/web/Window_stream.fw"


#endif // CGAL_WINDOW_STREAM_H

