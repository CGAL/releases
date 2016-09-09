
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/IO/Window_stream.h>



typedef double coord_type;
typedef CGAL_Point_2< CGAL_Cartesian<coord_type> > Point;
typedef CGAL_Vector_2< CGAL_Cartesian<coord_type> > Vector;
typedef CGAL_Direction_2< CGAL_Cartesian<coord_type> > Direction;

typedef CGAL_Segment_2< CGAL_Cartesian<coord_type> > Segment;
typedef CGAL_Line_2< CGAL_Cartesian<coord_type> > Line;
typedef CGAL_Ray_2< CGAL_Cartesian<coord_type> > Ray;

typedef CGAL_Iso_rectangle_2< CGAL_Cartesian<coord_type> > Iso_rectangle;

typedef CGAL_Bbox_2 Bbox;


int main()
{
  
    CGAL_Window_stream W(400, 200);
  
    W.init(-20.0, 20.0, -10.0);
  
  

    {
      int i;
      W << CGAL_RED;
      W << Line(Point(0.0, 0.0), Direction(1.0, 0.0));
      W << Line(Point(0.0, 0.0), Direction(0.0, 1.0));
      for(i = -35; i<=35; i+=5){
        W << Segment(Point(double(i), 0.2),
                     Point(double(i), -0.3));
      }
      for(i = -5; i<=5; i+=5){
        W << Segment(Point(-0.2, double(i)),
                     Point(0.2, double(i)));
      }
    }
  

    {
      W << CGAL_BLACK;
      Line line;
      W >> line;
  
      Iso_rectangle iso_r1, iso_r2;
  
      W >> iso_r1;
      W >> iso_r2;
      W << iso_r1.bbox() + iso_r2.bbox();
    }
  

  
    Segment segment;
    for(int count = 0; count < 10; count++){
      W << CGAL_BLUE ;
  
      W >> segment ;
  
      W << CGAL_GREEN  << segment.start() ;
      W << CGAL_ORANGE << segment.end() ;
      Line line = segment.supporting_line().perpendicular(segment.start()) ;
      W << CGAL_VIOLET << line ;
      W << segment.bbox() ;
  
    }
  

  char c;
  cout << " Type any character to continue: " << endl;
  cin >> c;
  cout << " done" << endl;

  return 1;
}
