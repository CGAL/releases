 

#ifndef CGAL_LINE_2_SEGMENT_2_PAIR_H
#define CGAL_LINE_2_SEGMENT_2_PAIR_H

#include <CGAL/Segment_2_Line_2_pair.h>

template <class R>
class CGAL_Line_2_Segment_2_pair: public CGAL_Segment_2_Line_2_pair<R> {
public:
    CGAL_Line_2_Segment_2_pair(
            CGAL_Line_2<R> const *line,
            CGAL_Segment_2<R> const *seg) :
                                CGAL_Segment_2_Line_2_pair<R>(seg, line) {}
};

#endif
