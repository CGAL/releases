 

#ifndef CGAL_BBOX_2_RAY_2_PAIR_H
#define CGAL_BBOX_2_RAY_2_PAIR_H

#include <CGAL/Ray_2_Bbox_2_pair.h>

template <class R>
class CGAL_Bbox_2_Ray_2_pair: public CGAL_Ray_2_Bbox_2_pair<R> {
public:
    CGAL_Bbox_2_Ray_2_pair() {}
    CGAL_Bbox_2_Ray_2_pair(CGAL_Bbox_2 const *box, CGAL_Ray_2<R> const *ray)
                :CGAL_Ray_2_Bbox_2_pair<R> (ray, box){}
};

#endif
