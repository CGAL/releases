
#include <CGAL/cartesian.h>

#ifdef CGAL_REPCLASS

#include <CGAL/Polygon_2.h>

typedef CGAL_Segment_2< C<double> > Segment;
typedef CGAL_Polygon_2< C<double> > Polygon;
typedef CGAL_Point_2< C<double> > Point;
#else

#include <CGAL/PolygonC2.h>
typedef CGAL_SegmentC2<double> Segment;
typedef CGAL_PolygonC2<double> Polygon;

typedef CGAL_PointC2<double> Point;
#endif

#include <stream.h>



void Polygons()
{
  cout << "Testing CGAL_Polygons_2<R> ... " << flush;


  Point p(0, 0), q(1, 0), r(0, 1);

  list<Point> l, l2, convex, nonconvex;

  l.append(p);
  l.append(q);
  l.append(r);

  l2.append(r);
  l2.append(q);
  l2.append(p);

  for(int i=0; i<10; i++){
    convex.append(Point(i,i*i));
    nonconvex.append(Point(i,i*i));
  }

  nonconvex.append(Point(1,2));
  nonconvex.append(Point(0,2));

  // constructors
  Polygon poly, pconvex(convex), pnonconvex(nonconvex);

  Polygon pqr(l);

  Polygon rqp(l2);

  poly = pqr;
  assert( poly == pqr );
  assert( pqr == pqr );
  assert( pqr != rqp );

  assert( pqr.is_convex() );
  assert( pqr.orientation() == CGAL_COUNTERCLOCKWISE );
  assert( rqp.orientation() == CGAL_CLOCKWISE );

  assert( pconvex.is_convex() );
  assert( pconvex.orientation() == CGAL_COUNTERCLOCKWISE );

  assert( ! pnonconvex.is_convex() );
  assert( pnonconvex.orientation() == CGAL_COUNTERCLOCKWISE );

  
  cout << pqr << endl;

  cout << pqr.area() << endl;
  cout << rqp.area() << endl;

  assert( pqr.size() == 3 );

  list<Point> lpqr = pqr.vertices();
  assert( r == lpqr.pop() );
  assert( q == lpqr.pop() );
  assert( p == lpqr.pop() );
  assert( lpqr.empty() );


  list<Segment> ls;

  cout <<  pqr.edges().pop();
  assert( p == pqr[0] && q == pqr[1] && r == pqr[2] );
  assert( pqr.vertex(0) == pqr[0] && 
	  pqr.vertex(1) == pqr[1] && 
	  pqr.vertex(2) == pqr[2] );

  assert( pqr.vertex(3) == pqr[3] && pqr.vertex(3) == pqr[0]);
  cout << " done" << endl;
}


#ifdef MAIN

int main()
{
  Polygons();

  return 1;
}
#endif
