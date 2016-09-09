
#include <assert.h>
#include <iostream.h>
#include <fstream.h>
#include <CGAL/basic.h>
#include <CGAL/predicates_on_pointsC2.h> // for the orientation

#include "points.h"

#include <CGAL/Triangulation_2.h>

typedef CGAL_Triangulation_2< Euclidean_2 > Triangulation_2;



int main(int argc, char* argv[])
{

  Triangulation_2 T;

  PVector V;

  ifstream data(argv[1]);
  
  if(data.bad()){
    cout << "Problem with file " << argv[1] << endl;
  }
  data >> V;

  cout << V.size() << endl;

  int count = 0;
  cout << "Start insertion" << endl;
  for(int i = 0; i<V.size();i++){
    
    T.insert(V[i]);

    if(++count == 100){
      cerr << ".";
      count = 0;
    }
  }
  cout << endl << "done" << endl;
  T.is_valid();

  return 0;
}
