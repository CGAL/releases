 

#ifndef CGAL_LINE_2_BBOX_2_PAIR_H
#define CGAL_LINE_2_BBOX_2_PAIR_H

#include <CGAL/Bbox_2_Line_2_pair.h>

template <class R>
class CGAL_Line_2_Bbox_2_pair: public CGAL_Bbox_2_Line_2_pair<R> {
public:
    CGAL_Line_2_Bbox_2_pair(
            CGAL_Line_2<R> const *line,
            CGAL_Bbox_2 const *bbox) :
                                CGAL_Bbox_2_Line_2_pair<R>(bbox, line) {}
};

#endif
