
#ifndef CGAL_TRIANGLE_2_SEGMENT_2_PAIR_H
#define CGAL_TRIANGLE_2_SEGMENT_2_PAIR_H

#include <CGAL/Segment_2_Triangle_2_pair.h>

template <class R>
class CGAL_Triangle_2_Segment_2_pair
: public CGAL_Segment_2_Triangle_2_pair<R> {
public:
    CGAL_Triangle_2_Segment_2_pair(
            CGAL_Triangle_2<R> const *trian,
            CGAL_Segment_2<R> const *seg) :
                        CGAL_Segment_2_Triangle_2_pair<R>(seg, trian) {}
};

#endif
