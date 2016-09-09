 

#ifndef CGAL_SEGMENT_2_RAY_2_PAIR_H
#define CGAL_SEGMENT_2_RAY_2_PAIR_H

#include <CGAL/Ray_2_Segment_2_pair.h>

template <class R>
class CGAL_Segment_2_Ray_2_pair: public CGAL_Ray_2_Segment_2_pair<R> {
public:
    CGAL_Segment_2_Ray_2_pair(
            CGAL_Segment_2<R> const *seg,
            CGAL_Ray_2<R> const *ray) :
                                CGAL_Ray_2_Segment_2_pair<R>(ray, seg) {}
};

#endif
