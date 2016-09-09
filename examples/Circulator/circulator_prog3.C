/*  circulator_prog3.C              */
/*  ------------------------------- */
#include <CGAL/basic.h>
#include <cassert>
#include <list>
#include <CGAL/circulator.h>

template <class C> inline
int foo( C c, std::forward_iterator_tag) { 
    CGAL::Assert_circulator( c);
    CGAL::Assert_forward_category( c);
    return 1;
}
template <class C> inline
int foo( C c, std::random_access_iterator_tag) { 
    CGAL::Assert_circulator( c);
    CGAL::Assert_random_access_category( c);
    return 2;
}
template <class I> inline
int foo( I i, CGAL::Iterator_tag) { 
    CGAL::Assert_iterator( i);
    return 3;
}

template <class C> inline
int foo( C c, CGAL::Circulator_tag) { 
    CGAL::Assert_circulator( c);
    return foo( c, std::iterator_category(c));
}
template <class IC> inline
int foo( IC ic) { 
    return foo( ic, CGAL::query_circulator_or_iterator( ic));
}

int main() {
    typedef CGAL::Forward_circulator_base<int, std::ptrdiff_t, std::size_t> F;
    typedef CGAL::Random_access_circulator_base<int, std::ptrdiff_t,
	std::size_t> R;
    F f = F();
    R r = R();
    std::list<int> l;
    assert( foo( f)         == 1);
    assert( foo( r)         == 2);
    assert( foo( l.begin()) == 3);
    return 0;
}
