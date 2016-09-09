
#include <stream.h>
#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

// the following types come from outside
typedef FIELDTYPE fieldtype;
typedef RINGTYPE  ringtype;


#ifdef CARTESIAN
#include <CGAL/cartesian.h>
#else
#include <CGAL/homogeneous.h>
#endif // CARTESIAN

#ifdef CGAL_REPCLASS
#include <CGAL/Direction_2.h>
#include <CGAL/IO/ostream_2.h>
#ifdef CARTESIAN
typedef C<fieldtype> reptype;
#else
typedef H<fieldtype, ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Vector_2<reptype>     Vector;
typedef CGAL_Direction_2<reptype>  Direction;

#else

#include <CGAL/DirectionC2.h>
#include <CGAL/IO/ostreamC2.h>
typedef CGAL_VectorC2<fieldtype>     Vector;
typedef CGAL_DirectionC2<fieldtype>  Direction;

#endif


void Directions()
{
  cout << "Testing CGAL_Direction_2<R> ... " << flush;

  // constructors
  Direction dir(1,1), d(1.0,2.0), e(1.0, 2.0), dd(d);



  assert( Direction(0,1) == Direction(0,234) );
  assert( Direction(1,0) == Direction(234,0) );
  assert( Direction(0,1) != Direction(0,-234) );
  assert( Direction(1,0) != Direction(-234,0) );

  const int n = 12;
  Direction dirs[n];

  dirs[0] = Direction(3,0);
  dirs[1] = Direction(2,2); 
  dirs[2] = Direction(1,5); 
  dirs[3] = Direction(0,4); 
  dirs[4] = Direction(-1,5); 
  dirs[5] = Direction(-2,2);
  dirs[6] = Direction(-4,0); 
  dirs[7] = Direction(-4,-4); 
  dirs[8] = Direction(-1,-5); 
  dirs[9] = Direction(0,-10);
  dirs[10]= Direction(1,-8);
  dirs[11]= Direction(2,-2);

  for(int i=0; i<n; i++) {
     for(int j=0; j<n; j++) {
       if (i == j) {
	 assert( dirs[i] == dirs[j] );
	 assert( dirs[i] <= dirs[j] );
	 assert( dirs[i] >= dirs[j] );
       } else if (i<j) {
	 assert( dirs[i] < dirs[j] );
	 assert( dirs[i] <= dirs[j] );
       } else {
	 assert( dirs[i] > dirs[j] );
	 assert( dirs[i] >= dirs[j] );
       }
     }
  }

  assert( d != dir );
  assert( d == dd  &&  dd == d );
  assert( d == e  &&  e == d );
  assert( d == d );
  assert( d == Direction(2.0 * d.vector()) );
  assert( d.identical(d) );
  assert( ! e.identical(dd)  &&  ! dd.identical(e));
  assert( dd.identical(d)    &&  d.identical(dd) );

  assert( d == - (-d) );

  cout << " done" << endl;  
 
}

#ifdef MAIN

int main()
{
  Directions();

  return 1;
}
#endif
