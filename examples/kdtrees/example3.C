/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * example3.C -
 *    Simple example the CGAL KD-tree module.
 *    Example with user defined point_d.    
 *
 * Written by Sariel Har-Peled 
 *            Iddo Hanniel
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

//might be needed when compiling with g++-2.7.2 
//#ifdef  __GNUG__ 
//#include  <typeinfo>
//#endif  /* __GNUG__ */ 

#include  <iostream.h>
#include  <time.h>
#include  <assert.h>

#include  <CGAL/Cartesian.h>
#include  <CGAL/Point_3.h>

#include  <list.h>

#include  <CGAL/kdtree_d.h>



template <int  DIM>
class Point_float_d 
{
private:
  double   vec[ DIM ];
  
public:
  Point_float_d()
  {
    for  ( int ind = 0; ind < DIM; ind++ )
      vec[ ind ] = 0;
  }

  int dimension() const
  {
    return  DIM;
  }
  
//not essential by specification but needed for initializing a general d-point
  void set_coord(int k, double x)
  {
    assert( 0 <= k  &&  k < DIM );
    vec[ k ] = x;
  }
  
  double  & operator[](int k)  
  {
    assert( 0 <= k  &&  k < DIM );
    return  vec[ k ];
  }

  double  operator[](int k) const
  {
    assert( 0 <= k  &&  k < DIM );
    return  vec[ k ];
  }

  
  // not essential by specification but nice to have
  friend ostream &operator<<(ostream &os, const Point_float_d<DIM> &p)
  {
    cout << "(";
    for(int i = 0; i < DIM; i++)
      {
        cout << p[i] ;
        if (i < p.dimension() - 1) cout << ", ";
      }
    cout << ")";
    return os;
  }
  
};


typedef Point_float_d<4>  point;
typedef CGAL_Kdtree_interface<point>  kd_interface;
typedef CGAL_Kdtree_d<kd_interface>  kd_tree;
typedef kd_tree::Box  box;
typedef list<point>  points_list; 


//RANDOM FUNCTIONS
// dblRand - a random number between 0..1 
#ifndef  RAND_MAX
#define  RAND_MAX    0x7fffffff
#endif  // RAND_MAX

static inline  double    dblRand( void )
{
    return  (double)rand() / (double)RAND_MAX;
}


void random_points( int  num, points_list &l, int DIM)
{
  double  x;
  
  for  (int j = 0;  j < num; j++)
    {
      point p;
      for (int i=0; i<DIM; i++)
        {
          x = dblRand()*10 ;
          p.set_coord(i,x);
        }
      l.push_front(p);
    }
}


int   main()
{

  CGAL_Kdtree_d<kd_interface>  tree(3);
  
  srand( (unsigned)time(NULL) );
  
  cout << "Choosing randomly 30 points in the cube (0,0,0)-(10,10,10)\n" ;
  
  points_list  l , res;
  random_points( 30, l , 4);

  
  cout << "Listing of random points:\n" ;
  copy (l.begin(),l.end(),ostream_iterator<point>(cout,"\n") );
  cout << endl;
  
  // building the tree for the random points
  tree.build( l );
  
  //checking validity
  if  ( ! tree.is_valid() )
    tree.dump();
  assert( tree.is_valid() );
  
  
  //searching the box r
  point p,q;
  for (int k=0;k<4;k++)
    {
      p.set_coord(k,2);
      q.set_coord(k,8);
    }
  
  box r(p, q, 4);
  tree.search( back_inserter( res ), r );
  
  cout << "Listing of the points in the box (2,2,2,2)-(8,8,8,8) : \n" ;
  copy (res.begin(),res.end(),ostream_iterator<point>(cout,"\n") );
  cout << endl;
  
  tree.delete_all();
  
  
  
  return  0;
}








