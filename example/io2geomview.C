#include <CGAL/Cartesian.h>

#include <iostream.h>
#include <LEDA/random.h>

#include <CGAL/IO/geomview.h>

typedef double coord_type;

typedef CGAL_Point_3< CGAL_Cartesian<coord_type> > Point;
typedef CGAL_Segment_3< CGAL_Cartesian<coord_type> > Segment;

typedef CGAL_Triangle_3< CGAL_Cartesian<coord_type> > Triangle;
typedef CGAL_Tetrahedron_3< CGAL_Cartesian<coord_type> > Tetrahedron;

typedef CGAL_Bbox_3 Bbox;


void input_fct(CGAL_geomview_stream &visualizer)
{

  Point p;

  for(int i=0;i<4;i++){
    visualizer >> p;
    visualizer << p;
  }
}


void output_fct(CGAL_geomview_stream &visualizer)
{
  random_source S(1,999);
  int a,b, c,d, e,f;
  for (int i=0; i<=3; i++) {
    S >> a >> b >> c >> d >> e >> f;

    Point p1(a, b, 100*i),
          p2(c, d, 100*i),
          p3(e, f, 100*i);

    Triangle tr(p1, p2, p3);

    visualizer << tr ;
    visualizer << p1 ;
  }

  Tetrahedron tetrahedron(Point(10, 10, 10),
                          Point(300, 10, 10),
                          Point(150, 150, 10),
                          Point(100, 100, 400));
  visualizer << tetrahedron;
}


int main(int argc, char **argv)
{
  char  *machine = (argc>1)?argv[1]:NULL;
  char *login = (argc>2)?argv[2]:NULL;

  
    CGAL_geomview_stream geomview(machine, login, Bbox(0,0,0, 1000,1000,100));
  
  

  output_fct(geomview);

  input_fct(geomview);


  return 1;
}
