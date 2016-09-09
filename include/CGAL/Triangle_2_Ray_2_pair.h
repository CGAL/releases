
#ifndef CGAL_TRIANGLE_2_RAY_2_PAIR_H
#define CGAL_TRIANGLE_2_RAY_2_PAIR_H

#include <CGAL/Ray_2_Triangle_2_pair.h>

template <class R>
class CGAL_Triangle_2_Ray_2_pair
: public CGAL_Ray_2_Triangle_2_pair<R> {
public:
    CGAL_Triangle_2_Ray_2_pair(
            CGAL_Triangle_2<R> const *trian,
            CGAL_Ray_2<R> const *ray) :
                        CGAL_Ray_2_Triangle_2_pair<R>(ray, trian) {}
};

#endif
