
#include <CGAL/Cartesian.h>

#include <iostream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef FIELDTYPE fieldtype;


#include <CGAL/Plane_3.h>
#include <CGAL/IO/ostream_3.h>
typedef CGAL_Plane_3< CGAL_Cartesian<fieldtype> >     Plane;

typedef CGAL_Segment_3< CGAL_Cartesian<fieldtype> >   Segment;
typedef CGAL_Line_3< CGAL_Cartesian<fieldtype> >      Line;
typedef CGAL_Ray_3< CGAL_Cartesian<fieldtype> >       Ray;

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >     Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> >    Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> > Direction;



void Planes()
{
  cout << "Testing CGAL_Plane_3<R> ... " << flush;
  fieldtype x1 = -1.0,
            y1 = -1.0,
            z1 = -1.0,
            x2 = 4.0,
            y2 = 4.0,
            z2 = 4.0;

  Point p1(x1,y1,z1), p2(x2,y2,z2),
        px(1,0,0), py(0,1,0), pz(0,0,1);

  Line l, lp(p1,p2), lxy(px,py);
  Segment s12(p1,p2);

  Ray r12(p1,p2);

  Plane xyplane(CGAL_ORIGIN,px,py), pl(xyplane), 
        plane(p1,p2,pz), splane(s12,pz), rplane(r12,pz), pcopy;

  pcopy = xyplane;

  //  cout << pcopy << endl;
  // cout << xyplane << endl;

  //cout << pcopy.orthogonal_direction() << endl;
  //cout << xyplane.orthogonal_direction() << endl;

  assert( pcopy.has_on_boundary(xyplane.point()) );
  assert( pcopy.orthogonal_direction() == xyplane.orthogonal_direction());
  assert( pcopy == xyplane );
  assert( identical(pcopy, xyplane) );
  assert( pcopy == pl );
  assert( identical(pcopy, pl) );
  assert( xyplane != plane );
  assert( plane == splane  &&  plane == rplane );

  assert( Plane(plane.a(), plane.b(), plane.c(), plane.d()) == plane );

  Plane opp = plane.opposite();
  
  assert( plane != opp );
  assert( plane == opp.opposite() );
  assert( xyplane.has_on_boundary(Point(345,23,0)) );
  assert( plane.has_on_boundary(plane.point()) );

  Vector v = plane.orthogonal_vector();
  assert( (v*plane.base1()) == 0.0
	  && (v*plane.base2()) == 0.0 );
  assert( (plane.base2()*plane.base1()) == 0.0 );

  assert( plane.has_on_boundary(plane.point() + plane.base1()) );
  assert( plane.has_on_boundary(plane.point() + plane.base2()) );

  cout << opp << endl;

  cout << "...  done" << endl;
}

#ifdef MAIN

int main()
{
  Planes();

  return 1;
}
#endif // MAIN
