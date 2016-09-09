#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/IO/Window_stream.h>

typedef CGAL_Cartesian< double >             RepCls;
typedef CGAL_Point_2<RepCls>                 Point;
typedef CGAL_Segment_2<RepCls>               Segment;
typedef CGAL_Line_2<RepCls>                  Line;
typedef CGAL_Ray_2<RepCls>                   Ray;
typedef CGAL_Iso_rectangle_2<RepCls>         Iso;
typedef CGAL_Triangle_2<RepCls>              Triangle;
typedef CGAL_Circle_2<RepCls>                Circle;

int
main()
{
  leda_window W;
  CGAL_cgalize( W);
  W.set_fg_color( leda_red);
  W.set_bg_color( leda_yellow);
  W.display();

  CGAL_set_pretty_mode( cout);

  W.acknowledge("Input Points");
  W.clear();
  Point p;
  while ( W >> p) { cout << p << endl; }

  W.acknowledge("Input Segments");
  W.clear();
  Segment s;
  while ( W >> s) { cout << s << endl; }

  W.acknowledge("Input Lines");
  W.clear();
  Line l;
  while ( W >> l) { cout << l << endl; }

  W.acknowledge("Input Rays");
  W.clear();
  Ray ray;
  while ( W >> ray) { cout << ray << endl; }

  W.acknowledge("Input Triangles");
  W.clear();
  Triangle t;
  while ( W >> t) { cout << t << endl; }

  W.acknowledge("Input Iso_rectangles");
  W.clear();
  Iso x;
  while ( W >> x) { cout << x << endl; }

  W.acknowledge("Input Circles");
  W.clear();
  Circle c;
  while ( W >> c) { cout << c << endl; }

  W.acknowledge("Read Functions");
  W.clear();
  W.message("Point");
  CGAL_read( W, p);
  W.message("Segment");
  CGAL_read( W, s);
  W.message("Line");
  CGAL_read( W, l);
  W.message("Ray");
  CGAL_read( W, ray);
  W.message("Triangle");
  CGAL_read( W, t);
  W.message("Iso_rectangle");
  CGAL_read( W, x);
  W.message("Circle");
  CGAL_read( W, c);


  W.acknowledge("THE END");
  return 0;
}
