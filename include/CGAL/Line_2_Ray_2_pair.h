 

#ifndef CGAL_LINE_2_RAY_2_PAIR_H
#define CGAL_LINE_2_RAY_2_PAIR_H

#include <CGAL/Ray_2_Line_2_pair.h>

template <class R>
class CGAL_Line_2_Ray_2_pair: public CGAL_Ray_2_Line_2_pair<R> {
public:
    CGAL_Line_2_Ray_2_pair(
            CGAL_Line_2<R> const *line,
            CGAL_Ray_2<R> const *ray) :
                                CGAL_Ray_2_Line_2_pair<R>(ray, line) {}
};

#endif
