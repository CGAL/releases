// ============================================================================
// The CGAL Project
// Example Program: 2D Smallest Enclosing Circle (2)
// ----------------------------------------------------------------------------
// file  : example/example2_Min_circle_2.C
// author: Sven Schönherr 
// ----------------------------------------------------------------------------
// $Revision: 3.1 $
// $Date: 1997/06/23 13:23:20 $
// ============================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In this release correct results are only guaranteed if exact
// arithmetic is used, so this example (using inexact floating-point
// arithmetic) is only intended to illustrate the techniques. However,
// the program will terminate, but the computed circle may neither
// contain all points nor be the smallest one.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <CGAL/Min_circle_2_adapterC2.h>
#include <CGAL/Min_circle_2.h>
#include <iostream.h>

// your own point class
class Pt {
    double _x, _y;
  public:
    Pt( ) { }
    Pt( double x, double y) : _x( x), _y( y) { }
    double  x( ) const { return( _x); }
    double  y( ) const { return( _y); }
};

bool
operator == ( Pt const& p, Pt const& q)
{
    return( ( p.x() == q.x()) && ( p.y() == q.y()));
}

ostream&
operator << ( ostream& os, Pt const& p)
{
    return( os << "Pt( " << p.x() << ", " << p.y() << ')');
}

istream&
operator >> ( istream& is, Pt& p)
{
    double x, y;
    is >> x >> y;
    p = Pt( x, y);
    return( is);
}

// the data accessor for Pt
class Pt_DA {
  public:
    typedef  double  FT;

    double  get_x( Pt const& p) const { return( p.x()); }
    double  get_y( Pt const& p) const { return( p.y()); }

    void
    get( Pt const& p, double& x, double& y) const
    {
	x = p.x();
	y = p.y();
    }

    void
    set( Pt& p, double x, double y) const
    {
	p = Pt( x, y);
    }
};

// some typedefs
typedef  CGAL_Min_circle_2_adapterC2< Pt, Pt_DA >  Adapter;
typedef  CGAL_Min_circle_2< Adapter >              Min_circle;

// main
int
main( int, char**)
{
    // generate 10 random points and insert them in `mc'
    Min_circle  mc;
    for ( int i = 0; i < 10; ++i)
	mc.insert( Pt( CGAL_random.get_double(), CGAL_random.get_double()));

    // output `mc'
    CGAL_set_pretty_mode( cout);
    cout << mc;
}

// ===== EOF ==================================================================
