/*  circulator_prog3.C              */
/*  ------------------------------- */
#include <CGAL/basic.h>
#include <assert.h>
#include <list.h>
#include <CGAL/circulator.h>

template <class C> inline
int foo( C c, forward_iterator_tag) { 
    CGAL_Assert_circulator( c);
    CGAL_Assert_forward_category( c);
    return 1;
}
template <class C> inline
int foo( C c, random_access_iterator_tag) { 
    CGAL_Assert_circulator( c);
    CGAL_Assert_random_access_category( c);
    return 2;
}
template <class I> inline
int foo( I i, CGAL_Iterator_tag) { 
    CGAL_Assert_iterator( i);
    return 3;
}

template <class C> inline
int foo( C c, CGAL_Circulator_tag) { 
    CGAL_Assert_circulator( c);
    return foo( c, iterator_category(c));
}
template <class IC> inline
int foo( IC ic) { 
    return foo( ic, CGAL_query_circulator_or_iterator( ic));
}

int main() {
    typedef CGAL_Forward_circulator_base<int, ptrdiff_t, size_t> F;
    typedef CGAL_Random_access_circulator_base<int, ptrdiff_t, size_t> R;
    F f = F();
    R r = R();
    list<int> l;
    assert( foo( f)         == 1);
    assert( foo( r)         == 2);
#ifndef __GNUG__
    assert( foo( l.begin()) == 3);
#endif
    return 0;
}
