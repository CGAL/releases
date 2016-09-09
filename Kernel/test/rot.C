
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>


typedef CGAL_Cartesian < float > Rep;

void fct(double x, double y)
{
  cout << ".............................\n";
  cout << "direction = " << x << "  " << y << endl;

  double sin_num = 0.0;
  double cos_num = 0.0;
  double denom = 0.0;


  CGAL_rational_rotation_approximation(x, y,
				       sin_num, cos_num, denom,
				       1.0, 100.0);

  double sinus   = sin_num/denom;
  double cosinus = cos_num/denom;

  cout << "( " << sin_num << ", " << cos_num << ", " << denom << ")\n";
  
  cout << "sinus     = " << sinus << endl;
  cout << "cosinus   = " << cosinus << endl;
}  


int main()
{
  double x, y;

  while( ! cin.eof() ) {
    cin >> x >> y;
    fct(x, y);
    fct(x + 0.001, y);
    fct(x - 0.001, y);
  }
  return 1;
}



/*
.............................
direction = 1  0        0 deg
( 0, 1, 1)
sinus     = 0		ok
cosinus   = 1		ok
.............................
direction = 1  1        45 deg
( 120, -119, 169)
sinus     = 0.710059  	ok
cosinus   = -0.704142	falsch
.............................
direction = -1  1	135 deg
( -119, -120, 169)
sinus     = -0.704142	falsch
cosinus   = -0.710059   ok
.............................
direction = -1  -1      225 deg
( -120, 119, 169)
sinus     = -0.710059   ok
cosinus   = 0.704142    falsch
.............................
direction = 1  -1       315 deg
( 120, 119, 169)
sinus     = 0.710059    falsch
cosinus   = 0.704142    ok
 */

