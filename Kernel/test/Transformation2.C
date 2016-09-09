
#include <CGAL/basic.h>
#include <iostream.h>
#include <math.h>


#include <CGAL/Double_eps.h>
#include <CGAL/Rational.h>
#include <CGAL/Integer.h>

typedef CGAL_Double_eps fieldtype;
typedef CGAL_Double_eps ringtype;


#ifdef CARTESIAN
#include <CGAL/Cartesian.h>
#else
#include <CGAL/Homogeneous.h>
#endif // CARTESIAN



#include <CGAL/Point_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/IO/ostream_2.h>

#ifdef CARTESIAN
typedef CGAL_Cartesian<fieldtype> reptype;
#else
typedef CGAL_Homogeneous<ringtype> reptype;
#endif // CARTESIAN

typedef CGAL_Point_2<reptype>     Point;
typedef CGAL_Vector_2<reptype>    Vector;
typedef CGAL_Direction_2<reptype> Direction;
typedef CGAL_Aff_transformation_2<reptype> Aff_transformation;


void Transformations()
{
  cout << "Testing CGAL_Aff_transformation_2<R> ... " << endl;
  
  
  Vector v(2.0, 1.0);

  Aff_transformation  general(-1.0, 3.0, 7.0,
			      -2.0, 5.0, 9.0), 
                      g2(1.0, 2.0, 3.0,
			 4.0, 5.0, 6.0), 
                      g3;

  Aff_transformation  translate(CGAL_TRANSLATION, v), 
                      trans(    CGAL_TRANSLATION, Vector(8,3)),
                      itranslate = translate.inverse();

  CGAL__Translation_repC2<fieldtype> rep;

  Aff_transformation  rotate(CGAL_ROTATION,Direction(-1.0, 0.0), 1.0), 
                      irotate = rotate.inverse();

  Aff_transformation  scale(CGAL_SCALING, 2.0), iscale = scale.inverse();

  Aff_transformation  g = translate;

  Aff_transformation pi_half(CGAL_ROTATION, Direction(0.0, 1.0), 1.0);
  Aff_transformation pi_quarter(CGAL_ROTATION, Direction(1.0, 1.0), 1.0);
  

  Point p(CGAL_ORIGIN), 
        q(2,3);


  q = general(q);
  assert( q == Point(14, 20) );

  q = trans(q);
  assert( q == Point(22, 23) ); 

  q = scale(q);
  assert( q == Point(44, 46) ); 

  q = pi_half(q);
  assert( q == Point(-46, 44) ); 


 
  Vector vect(3,2);

  assert( Vector(3,4) == general(vect) );
  assert( vect == translate(vect) );
  assert( vect * 2.0 == scale(vect) );
  assert( -vect == pi_half(pi_half(vect)) );
 

  Direction d(vect);

  assert( Direction(Vector(3,4)) == general(d) );
  assert( d == translate(d) );
  assert( d == scale(d) );
  assert( -d == pi_half(pi_half(d)) );


  cout << "---------\n";
  cout << "translation * translation" << endl;
  cout << trans << endl;
  cout << translate << endl;

  cout << translate*trans << endl<< endl;

  cout << "---------\n";
  cout << "rotation * translation" << endl;
  cout << pi_half << endl;
  cout << translate << endl;
  cout << pi_half * translate << endl;
  cout << translate * pi_half  << endl;

  cout << "---------\n";
  cout << "scaling * translation" << endl;
  cout << scale << endl;
  cout << translate << endl;
  cout << scale * translate << endl;
  cout << translate * scale << endl;

  cout << "---------\n";
  cout << "general * translation" << endl;
  cout <<  general << endl;
  cout << translate << endl;
  cout << general * translate << endl;
  cout << translate * general << endl;
  

  cout << "---------\n";
  cout << "rotation * rotation" << endl;
  cout << pi_half << endl;
  cout << pi_quarter << endl;
  cout << pi_half * pi_quarter << endl;

  
  cout << "---------\n";
  cout << "rotation * scaling" << endl;
  cout << pi_half << endl;
  cout << scale << endl;
  cout << pi_half * scale << endl;
  cout << scale * pi_half << endl;

  
  cout << "---------\n";
  cout << "rotation * general" << endl;
  cout << pi_half << endl;
  cout <<  general << endl;
  cout << pi_half * general << endl;
  cout << general * pi_half << endl;


  cout << "---------\n";
  cout << "scaling * scaling" << endl;
  cout << scale << endl;
  cout << iscale << endl;
  cout << scale * iscale << endl;


  cout << "---------\n";
  cout << "scaling * general" << endl;
  cout << scale << endl;
  cout <<  general << endl;
  cout << scale * general << endl;
  cout << general * scale << endl;

  cout << "---------\n";
  cout << "general * general" << endl;
  cout <<  g2 << endl;
  cout <<  general << endl;
  cout << g2 * general << endl;
  cout << general * g2 << endl;




  cout << " done" << endl;

}



#ifdef MAIN

int main()
{
  Transformations();

  return 1;
}
#endif
