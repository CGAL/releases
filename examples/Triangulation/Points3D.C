
extern "C" long clock();

#include <assert.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <CGAL/Cartesian.h>

#include <CGAL/Point_3.h>
#include <CGAL/predicates_on_points_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/IO/istream_3.h>
#include <CGAL/IO/ostream_3.h>

#include <CGAL/Triangulation_vertex.h>
#include <CGAL/Triangulation_face.h>
#include <CGAL/Triangulation_face_circulator.h>
#include <CGAL/Triangulation_vertex_circulator.h>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/IO/Inventor_ostream.h>

typedef CGAL_Cartesian<double> Rep;
typedef CGAL_Point_3<Rep> Point;

template < class R >
class Terrain {
public:
    typedef R Rep;
    typedef CGAL_Point_3<R>    Point;
    typedef CGAL_Segment_3<R>  Segment;
    typedef CGAL_Triangle_3<R> Triangle;

    typedef CGAL_Triangulation_vertex<Point> Vertex;
    typedef CGAL_Triangulation_face<Vertex> Face;


    CGAL_Comparison_result compare_x(const Point &p, const Point &q) const
    {
        return CGAL_compare_x(p, q);
    }


    CGAL_Comparison_result compare_y(const Point &p, const Point &q) const
    {
        return CGAL_compare_y(p, q);
    }


    CGAL_Orientation orientation(const Point &p,
                                 const Point &q,
                                 const Point &r) const
    {
        return CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
    }


    CGAL_Orientation extremal(const Point &p,
                              const Point &q,
                              const Point &r) const
    {
        if (p==q) return CGAL_COLLINEAR;
        if (p==r) return CGAL_COLLINEAR;
        if (r==q) return CGAL_COLLINEAR;

        return CGAL_orientation(p.x(), p.y(), q.x(), q.y(), r.x(), r.y());
    }


    CGAL_Oriented_side side_of_oriented_circle(const Point &p,
                                               const Point &q,
                                               const Point &r,
                                               const Point &s) const
    {
        if (p==s) return CGAL_ON_ORIENTED_BOUNDARY;
        if (q==s) return CGAL_ON_ORIENTED_BOUNDARY;
        if (r==s) return CGAL_ON_ORIENTED_BOUNDARY;

        return CGAL_side_of_oriented_circle(p.x(), p.y(),
                                            q.x(), q.y(),
                                            r.x(), r.y(),
                                            s.x(), s.y());
    }
    class Distance{};
};



typedef CGAL_Delaunay_triangulation_2< Terrain<Rep> > Delaunay;
//typedef CGAL_Triangulation_2< Terrain<Rep> > Delaunay;




int main(int argc, char* argv[])
{
  ifstream Points(argv[1]);

  istream_iterator<Point,ptrdiff_t> begin(Points);
  istream_iterator<Point,ptrdiff_t> end;

  Delaunay DT;

  long t1=clock();

  DT.insert(begin, end);

  long t2=clock();

  cout << "Triangulation takes time " << (t2-t1)/1000000.0 << endl;


  ofstream out(argv[2]);
  CGAL_Inventor_ostream Inventor(out);

  Inventor << DT;

  return 1;
}
