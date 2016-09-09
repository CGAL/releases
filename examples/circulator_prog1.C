/*  circulator_prog1.C              */
/*  ------------------------------- */
#include <CGAL/basic.h>
#include <assert.h>
#include <vector.h>
#include <algo.h>
#include <CGAL/circulator.h>

typedef CGAL_Random_access_circulator_from_iterator< 
    vector<int>::iterator,
    vector<int>::value_type,
    vector<int>::size_type,
    vector<int>::difference_type
> Circulator;
typedef CGAL_Random_access_container_from_circulator<Circulator> Container;
typedef Container::iterator Iterator;

main() {
    vector<int> v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(9);
    Circulator c( v.begin(), v.end());
    Container  container( c);
    sort( container.begin(), container.end());
    Iterator i = container.begin();
    assert( *i == 2);
    i++;    assert( *i == 5);
    i++;    assert( *i == 9);
    i++;    assert(  i == container.end());
    return 0;
}
