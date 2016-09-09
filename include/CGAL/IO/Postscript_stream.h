 
#ifndef CGAL_Postscript_STREAM
#define CGAL_Postscript_STREAM

#include <stdlib.h>
#include <iostream.h>
#include <iomanip.h>
#include <fcntl.h>
#include <fstream.h>
#include <strstream.h>
#include <stdio.h>
#include <string.h>

#include <LEDA/basic.h>
#include <CGAL/IO/Color.h>
#include <CGAL/cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Bbox_2.h>

 
#ifndef CGAL_PS_MANIP_H_
#define CGAL_PS_MANIP_H_

template <class T>
class CGAL_PS_Modifier {
  friend CGAL_PS_stream& operator<<(CGAL_PS_stream& pss,
                                    const CGAL_PS_Modifier<T> &);
public:
  CGAL_PS_Modifier(CGAL_PS_stream& (CGAL_PS_stream::*f)(T),T v):
    _PS_func(f), param(v) {}
private:
  CGAL_PS_stream& (CGAL_PS_stream::*_PS_func)(T);
  T param;
};

template <class T>
CGAL_PS_stream& operator<<(CGAL_PS_stream& pss, const CGAL_PS_Modifier<T> &m)
{
  (pss.*m._PS_func)(m.param);
  return pss;
};

template<class T>
class CGAL_PS_Modifier_creator {
public:
  CGAL_PS_Modifier_creator(CGAL_PS_stream& (CGAL_PS_stream::*f)(T)):
    _PS_func(f) {}
  CGAL_PS_Modifier<T> operator() (T param)
  {
    return CGAL_PS_Modifier<T>(_PS_func,param);
  }
private:
  CGAL_PS_stream& (CGAL_PS_stream::*_PS_func)(T);
};

#endif //CGAL_PS_MANIP_H_
 

 

class CGAL_PS_stream;
typedef CGAL_Bbox_2 PS_BBox;

class CGAL_PS_Axis {
public:
  CGAL_PS_Axis(double x, double y, unsigned int t=0.0)
    : _padx(x), _pady(y), _thick(t) {}
  CGAL_PS_Axis(double xy, unsigned int t=0.0)
    : _padx(xy),_pady(xy), _thick(t) {}
  CGAL_PS_Axis(): _padx(1.0), _pady(1.0), _thick(0.0) {}

  double padx() { return _padx;}
  double pady() { return _pady;}
  double thick() { return _thick;}
private:
  double _padx;
  double _pady;
  bool _thick;
};
 

class CGAL_PS_Grid {
public:
  CGAL_PS_Grid(double x, double y, char *str="[1 5] 0")
    : _padx(x), _pady(y) {_style=strdup(str);}
  CGAL_PS_Grid(double xy, char *str="[1 5] 0")
    : _padx(xy), _pady(xy) {_style=strdup(str);}
  CGAL_PS_Grid() : _padx(1.0), _pady(1.0), _style("[1 5] 0") {}

  double padx() { return _padx;}
  double pady() { return _pady;}
  const char *style() { return _style;}

private:
  double _padx;
  double _pady;
  char *_style;
};
 

class CGAL_PS_Context {

friend CGAL_PS_stream;

public:

static const char* SOLID;
static const char* DASH1;
static const char* DASH2;
static const char* DASH3;

enum DotStyle {NONE, XCROSS, ICROSS, EDOT, FDOT, EBOX, FBOX};

CGAL_PS_Context() : _border_color(CGAL_Color(0.0,0.0,0.0)),
  _fill_color(CGAL_Color(0.0,0.0,0.0)),_dot_style(XCROSS),_dot_size(5),
  _thickness(0),_line_style(SOLID),_fill(false),_font_size(12),
  _font("Helvetica"), _anchor_point(CGAL_Point_2<C <double> > (0,0))
  {}

CGAL_PS_Context(const CGAL_PS_Context& c)
  :  _border_color(c.border_color()),_fill_color(c.get_fill_color()),
     _dot_style(c.get_dot_style()), _dot_size(c.get_dot_size()),
     _thickness(c.thickness()), _line_style(strdup(c.line_style())),
     _fill(c.fill()), _font(strdup(c.font())), _font_size(c.font_size()),
     _anchor_point(c.get_pos())
  {};

// Accessor

CGAL_Color   border_color()  const {return _border_color;}
CGAL_Color   get_fill_color() const {return _fill_color;}
DotStyle     get_dot_style() const {return _dot_style;}
unsigned int get_dot_size()  const {return _dot_size;}
unsigned int thickness()     const {return _thickness;}
unsigned int font_size()     const {return _font_size;}
const char * line_style()    const {return _line_style;}
const char*  font()          const {return _font;}
bool         fill()          const {return _fill;}

CGAL_Point_2<C <double> > get_pos() const {return _anchor_point;}
 
private:

// Modifier
CGAL_Color&    border_color() {return _border_color;}
CGAL_Color&    fill_color()   {return _fill_color;}
DotStyle&      dot_style()    {return _dot_style;}
unsigned int&  dot_size()     {return _dot_size;}
unsigned int&  thickness()    {return _thickness;}
unsigned int&  font_size()    {return _font_size;}
bool&          set_fill()     {return _fill;}
bool&          show_dir()     {return _dir;}
void set_current_pos(const CGAL_Point_2<C <double> >& p) {_anchor_point=p;}
void set_line_style(const char *style) {_line_style=strdup(style);}
void set_font(const char *font) {_font=strdup(font);}

// Store the current border color
CGAL_Color _border_color;
// Store the current fill color
CGAL_Color _fill_color;
// Store the current dot style
enum DotStyle _dot_style;
// Store the current dot size
unsigned int _dot_size;
// Store the current line thickness
unsigned int _thickness;
// Store the current line style
const char* _line_style;
// Define if a polygone must be fill or not
bool _fill;
//Anchor point:
CGAL_Point_2<C <double> > _anchor_point;
// Define if direction must be shown.
bool _dir;
// Store the name of the font to use.
const char* _font;
// Store the size of the font.
unsigned int _font_size;


};

 

 

class CGAL_PS_stream {
public:


  static const float CM;
  static const float INCH;
  static const float POINT;

  enum OutputMode {READABLE, QUIET, READABLE_EPS, QUIET_EPS, GS_VIEW};
  
 
    CGAL_PS_stream(const PS_BBox &bb);
  
 
    CGAL_PS_stream(const PS_BBox &bb, ostream &os,
                 OutputMode = READABLE);
  
 
        CGAL_PS_stream(const PS_BBox &bb, const char *fname,
                     OutputMode = READABLE);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float H);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float H, ostream &os,
                 OutputMode = READABLE);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float H, const char *fname,
                 OutputMode = READABLE);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float L, float H);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float L, float H, ostream &os,
                 OutputMode = READABLE);
  
 
    CGAL_PS_stream(const PS_BBox &bb,float L, float H, const char *fname,
                 OutputMode = READABLE);
  
 
    ~CGAL_PS_stream();
  
 
    CGAL_PS_stream& _SetBorderColor(CGAL_Color &);
  CGAL_PS_stream& _SetFillColor(CGAL_Color &);
  CGAL_PS_stream& _SetPointSize(unsigned int);
  CGAL_PS_stream& _SetLineWidth(unsigned int);
  CGAL_PS_stream& _SetPointStyle(enum DotStyle);
  CGAL_PS_stream& _SetLineStyle(char *);
  CGAL_PS_stream& _SetFill(bool);
  CGAL_PS_stream& _SetDefaultContext(void);
  CGAL_PS_stream& _SetCurrentContext(const CGAL_PS_Context &);
  CGAL_PS_stream& _ShowDirection(bool);
  CGAL_PS_stream& _MoveTo(CGAL_Point_2< C <double> >);
  CGAL_PS_stream& _ShowAxis(CGAL_PS_Axis &);
  CGAL_PS_stream& _ShowGrid(CGAL_PS_Grid &);
  CGAL_PS_stream& _PutPsLabel(const char *);
  CGAL_PS_stream& _PutLatexLabel(const char *);
  CGAL_PS_stream& _PutBorder(unsigned int);
  CGAL_PS_stream& _SetFont(const char *);
  CGAL_PS_stream& _SetFontSize(unsigned int);
  ostream&        os()   {return _os;}
  CGAL_PS_Context context() {return ctxt;}

  bool         gs_output()     const {return (bool)(mode()==GS_VIEW);}
  double       scale_factor()  const {return _scale_factor;}
  PS_BBox      bbox()          const {return _bbox;}
  int          width()         const {return _width;}
  int          height()        const {return _height;}
  OutputMode   mode()          const {return _mode;}

  double xratio() { return _width/(_bbox.xmax()-_bbox.xmin()); }
  double yratio() { return _height/(_bbox.ymax()-_bbox.ymin()); }
  double x2ps(double x) {
    return (x-_bbox.xmin())*xratio();
  }
  double y2ps(double y) {
    return (y-_bbox.ymin())*yratio();

  }

  bool is_eps();
  bool is_readable();




  
 
  private:

void init_const();

// Manipulation du contexte.
void setdefault();
void setcontext();

// Pour inserer l'entete

void insert_catalogue();

// The scale factor define the product factor of the size of the output
double     _scale_factor;
// Define the boounding box
PS_BBox _bbox;
// Size of output.
int _width,_height;
// OutputMode
OutputMode _mode;
// Graphical Context
CGAL_PS_Context ctxt;
// The Output stream
ostream_withassign &_os;
// the file pointer in case of a pipe to gs
FILE       *fp;
};
extern const CGAL_PS_Context CGAL_CTXT_DEFAULT;

extern CGAL_PS_Modifier_creator<CGAL_Color &> set_fill_color;

extern CGAL_PS_Modifier_creator<CGAL_Color &> set_border_color;

extern CGAL_PS_Modifier_creator<unsigned int> set_point_size;

extern CGAL_PS_Modifier_creator<enum DotStyle> set_point_style;

extern CGAL_PS_Modifier_creator<const char *> set_line_style;

extern CGAL_PS_Modifier_creator<unsigned int> set_line_width;

extern CGAL_PS_Modifier_creator<bool> set_fill;

//extern CGAL_PS_Modifier_creator<void> set_default_context;

extern CGAL_PS_Modifier_creator<const CGAL_PS_Context &> set_current_context;

extern CGAL_PS_Modifier_creator<bool> show_direction;

extern CGAL_PS_Modifier_creator<CGAL_Point_2< C <double> > > move_to;

extern CGAL_PS_Modifier_creator<CGAL_PS_Axis &> show_axis;

extern CGAL_PS_Modifier_creator<CGAL_PS_Grid &> show_grid;

extern CGAL_PS_Modifier_creator<const char *> put_ps_label;

extern CGAL_PS_Modifier_creator<const char *> put_latex_label;

extern CGAL_PS_Modifier_creator<unsigned int> put_border;

extern CGAL_PS_Modifier_creator<const char *> set_font;

extern CGAL_PS_Modifier_creator<unsigned int> set_font_size;
 

 

#ifdef CGAL_POINT_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps, const CGAL_Point_2<R> &p)
{

  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Point" << endl;
      ps.os() << "%CGAL% "<<p.x()<<" "<<p.y()<<endl;
    }
  if (ps.context().get_dot_style()!=CGAL_PS_Context::NONE)
    ps.os() << ps.x2ps(p.x()) << " "
            << ps.y2ps(p.y()) << " "
            << ps.context().get_dot_size() << " ";
  switch (ps.context().get_dot_style())
    {
    case CGAL_PS_Context::EBOX:
      ps.os() << "eb" << endl;
      break;
    case CGAL_PS_Context::FBOX:
      ps.os() << "fb" << endl;
      break;
    case CGAL_PS_Context::EDOT:
      ps.os() << "ec" << endl;
      break;
    case CGAL_PS_Context::FDOT:
      ps.os() << "fc" << endl;
      break;
    case CGAL_PS_Context::ICROSS:
      ps.os() << "ic" << endl;
      break;
    case CGAL_PS_Context::XCROSS:
      ps.os() << "xc" << endl;
      break;
    }
  return ps;
}

#endif // CGAL_POINT_2_H
 
#ifdef CGAL_SEGMENT_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps, const CGAL_Segment_2<R> &s)
{
  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Segment" << endl;
      ps.os() << "%CGAL% "<<s.start().x()<<" "<<s.start().y()<<" "
              <<s.end().x()<<" "<<s.end().y()<<endl;
    }
  ps.os() << ps.x2ps(s.start().x()) << " "
          << ps.y2ps(s.start().y()) << " mt ";
  ps.os() << ps.x2ps(s.end().x()) << " "
          << ps.y2ps(s.end().y())
          << " lt st" << endl;

  return ps;
}

#endif // CGAL_SEGMENT_2_H
 
#ifdef CGAL_LINE_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps, const CGAL_Line_2<R> &l)
{
  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Line" << endl;
      ps.os() << "%CGAL% "<<l.a()<<" "<<l.b()<<" "<<l.c()<<endl;
    }
  if (!l.is_degenerate())
    if (l.is_vertical())
      {
        double t=ps.x2ps(l.x_at_y(0));
        ps.os()<< t;
        ps.os()<< " 0 mt" << endl;
        ps.os()<< t << " " << ps.height() << " lt st" <<endl;
      }
    else
      {
        ps.os() << "0 "
                << ps.y2ps(l.y_at_x(ps.bbox().xmin()))
                << " mt" << endl;
        ps.os() << ps.width() << " "
                << ps.y2ps(l.y_at_x(ps.bbox().xmax()))
                << " lt st"<< endl;
      }
  return ps;
}
#endif // CGAL_LINE_2_H
 
#ifdef CGAL_RAY_2_H
template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps, const CGAL_Ray_2<R> &r)
{
  typedef CGAL_Direction_2<C <double> > dir;
  CGAL_Line_2<R> l=r.supporting_line();
  dir haut(0,1);
  dir bas(0,-1);
  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Ray" << endl;
      ps.os() << "%CGAL% "<<r.start().x()<<" "<<r.start().y()<<" ";
      ps.os() << r.second_point().x() << " " << r.second_point().y() <<endl;
    }
  if (!r.is_degenerate())
    {
      ps.os()<< ps.x2ps(r.start().x()) << " "
             << ps.y2ps(r.start().y()) << " mt" << endl;
      if (r.is_vertical())
        {
          ps.os()<< ps.x2ps(r.start().x()) << " ";
          if (r.direction()==haut)
            ps.os() << ps.height();
          else
            ps.os() << "0 ";
          ps.os() << " lt st" << endl;
        }
      else
        if (r.direction()>bas || r.direction()<haut)
          ps.os() << ps.width()
                  << " "
                  <<ps.y2ps(l.y_at_x(ps.bbox().xmax()))
                  << " lt st" << endl;
        else
          ps.os() << "0 "
                  << ps.y2ps(l.y_at_x(ps.bbox().xmin()))
                  << " lt st" << endl;
    }
  return ps;
}

#endif // CGAL_RAY_2_H
 
#ifdef CGAL_PARABOLA_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps,const CGAL_Parabola<R> &p)
{

  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Parabola" << endl;
      ps.os() << "%CGAL% Base "<<p.base().x()<<" "<<p.base().y()<<endl;
      ps.os() << "%CGAL% Vector "<<p.vertor().x()<<" "p.vector().y()<<endl;
      ps.os() << "%CGAL% Curvature "<<p.curvature()<<endl;
    }
  return ps;
}


#endif // CGAL_PARABOLA_2_H
 
#ifdef CGAL_TRIANGLE_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps,const CGAL_Triangle_2<R> &t)
{
  if (ps.is_readable())
    {
      ps.os() << "%CGAL% Triangle" << endl;
      for (int i=0;i<3;i++)
        ps.os() << "%CGAL " << t[i].x() << " " << t[i].y() << endl;
    }
  for (int i=0;i<4;i++)
    ps.os() << ps.x2ps(t[i].x())<< " " << ps.y2ps(t[i].y()) << " ";

  ps.os() << "tr ";
  if (ps.context().fill())
    {
      ps.os() << "gsave " << endl;
      ps.os() << ps.context().get_fill_color().r() << " "
              << ps.context().get_fill_color().g() << " "
              << ps.context().get_fill_color().b()
              << " setcolor fill grestore " <<endl;
    }
  ps.os() << "st" <<endl;
  return ps;
}


#endif // CGAL_TRIANGLE_2_H
 
#ifdef CGAL_ISO_RECTANGLE_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps,const CGAL_Iso_rectangle_2<R> &r)
{
    if (ps.is_readable())
      {
        ps.os() << "%CGAL% Rectangle" << endl;
        for (int i=0;i<4;i++)
          ps.os() << "%CGAL " << r[i].x() << " " << r[i].y() << endl;
      }
    for (int i=0;i<5;i++)
      ps.os() << ps.x2ps(r[i].x()) << " " << ps.y2ps(r[i].y()) << " ";

    ps.os() << "re ";
    if (ps.context().fill())
      {
        ps.os() << "gsave " << endl;
        ps.os() << ps.context().get_fill_color().r() << " "
                << ps.context().get_fill_color().g() << " "
                << ps.context().get_fill_color().b()
                << " setcolor fill grestore " <<endl;
      }
    ps.os() << "st" <<endl;
    return ps;
  }
#endif // CGAL_ISO_RECTANGLE_2_H
 
#ifdef CGAL_CIRCLE_2_H

template < class R >
CGAL_PS_stream &operator<<(CGAL_PS_stream &ps,
                                   const CGAL_Circle_2<R> &c)
{
    if (ps.is_readable())
      {
        ps.os() << "%CGAL% Circle" << endl;
        ps.os() << "%CGAL " << c.center().x() << " " << c.center().y() << endl;
        ps.os() << "%CGAL " << c.radius() << endl;
      }
    double ratio=ps.yratio()/ps.xratio();
    ps.os()<< "gsave 1 " << ratio << " scale" << endl;
    ps.os()<< ps.x2ps(c.center().x()) << " " << ps.y2ps(c.center().y())/ratio
           << " " << c.radius()*ps.xratio()  << " 0 360 arc " << endl;
    if (ps.context().fill())
      {
        ps.os() << "gsave " << endl;
        ps.os() << ps.context().get_fill_color().r() << " "
                << ps.context().get_fill_color().g() << " "
                << ps.context().get_fill_color().b()
                << " setcolor fill grestore " <<endl;
      }
    ps.os() << "st grestore" <<endl;
    return ps;
  }
#endif // CGAL_ISO_RECTANGLE_2_H
 


#endif  // CGAL_Postscript_STREAM
