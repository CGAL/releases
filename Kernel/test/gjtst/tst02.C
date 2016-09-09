/*
 * Test number types check.
 */
#include <CGAL/basic.h>
#include <CGAL/test_types.h>
#include <iostream.h>

CGAL_TestrepH to_rt(double d)
{
    unsigned char dummy1;
    signed char dummy2;
    return CGAL_TestrepH(dummy1, dummy2, d);
}

CGAL_TestfieldH to_ft(double d)
{
    unsigned char dummy1;
    signed char dummy2;
    return CGAL_TestfieldH(dummy1, dummy2, d);
}

CGAL_TestfieldC to_nt(double d)
{
    unsigned char dummy1;
    signed char dummy2;
    return CGAL_TestfieldC(dummy1, dummy2, d);
}

void main()
{
    double d = 7.8;
    CGAL_TestrepH trh;
    CGAL_TestfieldH tfh;
    CGAL_TestfieldC tfc;
    trh = to_rt(d);
    tfh = to_ft(d);
    tfc = to_nt(d);
    cout<<CGAL_to_double(trh)<<'\n';
    cout<<CGAL_to_double(tfh)<<'\n';
    cout<<CGAL_to_double(tfc)<<'\n';
}
