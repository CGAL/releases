// ============================================================================
// The CGAL Project
// Example Program: 2D Smallest Enclosing Circle (3)
// ----------------------------------------------------------------------------
// file  : example/example3_Min_circle_2.C
// author: Sven Schönherr 
// ----------------------------------------------------------------------------
// $Revision: 3.1 $
// $Date: 1997/06/23 13:23:20 $
// ============================================================================

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In this release correct results are only guaranteed if exact
// arithmetic is used, so this example (using integer arithmetic with
// possible overflows) is only intended to illustrate the techniques.
// However, the program will terminate, but the computed circle may
// neither contain all points nor be the smallest one. In some rare cases
// where an overflow results in a zero, the program might crash.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <CGAL/Min_circle_2_adapterH2.h>
#include <CGAL/Min_circle_2.h>
#include <iostream.h>

// your own point class
class Pt {
    int _hx, _hy, _hw;
  public:
    Pt( ) { }
    Pt( int hx, int hy, int hw = 1) : _hx( hx), _hy( hy), _hw( hw) { }
    int  hx( ) const { return( _hx); }
    int  hy( ) const { return( _hy); }
    int  hw( ) const { return( _hw); }
};

bool
operator == ( Pt const& p, Pt const& q)
{
    return( ( p.hx()*q.hw() == q.hx()*p.hw()) &&
	    ( p.hy()*q.hw() == q.hy()*p.hw()) );
}

ostream&
operator << ( ostream& os, Pt const& p)
{
    return( os << "Pt( " << p.hx() << ", " << p.hy() << ", " << p.hw() << ')');
}

istream&
operator >> ( istream& is, Pt& p)
{
    int hx, hy, hw;
    is >> hx >> hy >> hw;
    p = Pt( hx, hy, hw);
    return( is);
}

// the data accessor for Pt
class Pt_DA {
  public:
    typedef  int  RT;

    int  get_hx( Pt const& p) const { return( p.hx()); }
    int  get_hy( Pt const& p) const { return( p.hy()); }
    int  get_hw( Pt const& p) const { return( p.hw()); }

    void
    get( Pt const& p, int& hx, int& hy, int& hw) const
    {
	hx = p.hx();
	hy = p.hy();
	hw = p.hw();
    }

    void
    set( Pt& p, int hx, int hy, int hw) const
    {
	p = Pt( hx, hy, hw);
    }
};

// some typedefs
typedef  CGAL_Min_circle_2_adapterH2< Pt, Pt_DA >  Adapter;
typedef  CGAL_Min_circle_2< Adapter >              Min_circle;

// main
int
main( int, char**)
{
    // generate 10 random points and insert them in `mc'
    Min_circle  mc;
    for ( int i = 0; i < 10; ++i)
	mc.insert( Pt( CGAL_random( 10), CGAL_random( 10)));

    // output `mc'
    CGAL_set_pretty_mode( cout);
    cout << mc;
}

// ===== EOF ==================================================================
