#define CGAL_WORKAROUND_DC 1
#include <CGAL/basic.h>
#include <iostream.h>
#include <CGAL/Object.h>

CGAL_Object foo()
{
    typedef int tp;
    tp p = 7;
    return CGAL_make_object(p);
}

main()
{
    CGAL_Object obj;
    float f;
    int i;
    obj = foo();
    if (CGAL_assign(f, obj)) {
	cout<<"Oops, recognised as float: "<<f<<"\n";
    } else if (CGAL_assign(i, obj)) {
	cout<<"Ok, recognised as int: "<<i<<"\n";
    } else {
	cout<<"Not recognised.\n";
    }
}
