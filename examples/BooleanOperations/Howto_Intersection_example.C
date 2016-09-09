//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL basic library.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//
 
// Source: BooleanOperations_example.C
// Author: Wolfgang Freiseisen
 

/*
  This is an example program for the usage of the boolean operation
  Intersection with cartesian coordiantes.

  The number type it uses is a non-exact one:    CGAL_Quotient<int>
                               ---------
*/

#ifdef __GNUC__
#include <typeinfo>
#endif
#include <iostream.h>

#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>
#include <CGAL/basic.h>

#include <list.h>
#include <CGAL/boolean_operations_2.h>


typedef CGAL_Quotient<int> TestNum;
typedef CGAL_Cartesian<TestNum>              R_type;
//typedef CGAL_Homogeneous<TestNum>            R_type;
typedef CGAL_Point_2<R_type>                 Point_2;
typedef CGAL_Segment_2<R_type>               Segment_2;
typedef list< Point_2 >                      Container;
typedef CGAL_Polygon_2< R_type, Container >  Polygon_2;


typedef vector<Point_2>                      Input_container;

int example_intersection(
  const Input_container& container_A,
  const Input_container& container_B
) {
  /* possible results */
  Point_2   point;
  Segment_2 segment;
  Polygon_2 polygon;

  /* instantiate Polygon A and B with containers */
  Polygon_2 A(container_A.begin(), container_A.end());
  Polygon_2 B(container_B.begin(), container_B.end());

  /* declaration of the result container */
  list<CGAL_Object> result;

  /* performing intersection of A and B */
  CGAL_intersection(A, B, back_inserter(result));
  
  /* print out the result */
  cout << "size=" << result.size() << endl;

  /* declaration of an iterator on the result container */
  list<CGAL_Object>::const_iterator it;
  for( it= result.begin(); it != result.end(); it++) {
    if( CGAL_assign( polygon, *it) ) {
      cout << polygon << endl;               /* polygon detected */
    }
    else if( CGAL_assign( segment, *it) ) {
      cout << segment << endl;               /* segment detected */
    }
    else if( CGAL_assign( point, *it) )  {  
      cout << point << endl;                 /* point detected */
    }
    else {
      cout << "undefined object " << endl;   /* nothing detected */
    }
  }
  
  /* return size of result */
  return result.size();
}



int main(void)
{
  Input_container container_A(6), container_B(4);

  container_A[0]= Point_2(2,4);
  container_A[1]= Point_2(0,3);
  container_A[2]= Point_2(1,1);
  container_A[3]= Point_2(2,3);
  container_A[4]= Point_2(3,1);
  container_A[5]= Point_2(4,3);
  container_B[0]= Point_2(0,2);
  container_B[1]= Point_2(0,0);
  container_B[2]= Point_2(5,0);
  container_B[3]= Point_2(5,2);

  example_intersection( container_A, container_B);
  return 0;
}
