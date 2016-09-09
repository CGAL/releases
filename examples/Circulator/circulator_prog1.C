// circulator_prog1.C
// -------------------------------
#include <CGAL/basic.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <CGAL/circulator.h>

typedef  std::vector<int> V;
typedef  CGAL::Random_access_circulator_from_iterator<
             V::iterator, V::value_type, V::size_type, V::difference_type>
           Circulator;
typedef  CGAL::Random_access_container_from_circulator<Circulator> Container;
typedef  Container::iterator Iterator;

int main() {
    V v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(9);
    Circulator c( v.begin(), v.end());
    Container  container( c);
    std::sort( container.begin(), container.end());
    Iterator i = container.begin();
    assert( *i == 2);
    i++;    assert( *i == 5);
    i++;    assert( *i == 9);
    i++;    assert(  i == container.end());
    return 0;
}
