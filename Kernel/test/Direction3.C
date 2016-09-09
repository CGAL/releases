
#include <CGAL/Cartesian.h>

#include <iostream.h>

#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>

// the fieldtype should come from outside
typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps ringtype;

#include <CGAL/Direction_3.h>
#include <CGAL/IO/ostream_3.h>

typedef CGAL_Point_3< CGAL_Cartesian<fieldtype> >     Point;
typedef CGAL_Vector_3< CGAL_Cartesian<fieldtype> >    Vector;
typedef CGAL_Direction_3< CGAL_Cartesian<fieldtype> > Direction;

void Directions3()
{
  CGAL_set_eps(0.00001);
  cout << "Testing CGAL_Direction_3<FT> ... " << flush;

  fieldtype x1 = -1.0,
            y1 = -1.0,
            z1 = -1.0,
            x2 = 4.0,
            y2 = 4.0,
            z2 = 4.0;
  fieldtype scalar(3.0);


  // constructors
  Direction dir(1,1,1), d(1.0, 2.0, -3.0), e(1.0, 2.0, -3.0), dd(d);

  assert( d != dir );
  assert( d == dd  &&  dd == d );
  assert( d == e  &&  e == d );
  assert( d == d );

  assert( Direction(0,0,1) == Direction(0,0,10) );
  assert( Direction(0,1,0) == Direction(0,10,0) );
  assert( Direction(1,0,0) == Direction(10,0,0) );

  assert( Direction(0,0,1) != Direction(0,0,-10) );
  assert( Direction(0,1,0) != Direction(0,-10,0) );
  assert( Direction(1,0,0) != Direction(-10,0,0) );

  assert( d == Direction(d.vector() * ringtype(2)) );
  assert( identical(d, d) );
  assert( ! identical(e, dd)  &&  ! identical(dd, e));
  assert( identical(dd, d)    &&  identical(d, dd) );


  assert( d == - (-d) );
  
  cout << " done" << endl; 
}


#ifdef MAIN

int main()
{
  Directions3();

  return 1;
}
#endif
