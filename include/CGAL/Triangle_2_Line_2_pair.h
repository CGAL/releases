
#ifndef CGAL_TRIANGLE_2_LINE_2_PAIR_H
#define CGAL_TRIANGLE_2_LINE_2_PAIR_H

#include <CGAL/Line_2_Triangle_2_pair.h>

template <class R>
class CGAL_Triangle_2_Line_2_pair
: public CGAL_Line_2_Triangle_2_pair<R> {
public:
    CGAL_Triangle_2_Line_2_pair(
            CGAL_Triangle_2<R> const *trian,
            CGAL_Line_2<R> const *line) :
                        CGAL_Line_2_Triangle_2_pair<R>(line, trian) {}
};

#endif
