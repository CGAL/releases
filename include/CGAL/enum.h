


#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H




enum  CGAL_Ordertype
      { CGAL_CLOCKWISE   = -1,
        CGAL_COLLINEAR,
        CGAL_COUNTERCLOCKWISE
      };

// We should not have global constants?

const CGAL_Ordertype   CGAL_LEFTTURN  = CGAL_COUNTERCLOCKWISE;
const CGAL_Ordertype   CGAL_RIGHTTURN = CGAL_CLOCKWISE;
const CGAL_Ordertype   CGAL_POSITIVE  = CGAL_COUNTERCLOCKWISE;
const CGAL_Ordertype   CGAL_NEGATIVE  = CGAL_CLOCKWISE;
const CGAL_Ordertype   CGAL_COPLANAR  = CGAL_COLLINEAR;




enum  CGAL_Side
      { CGAL_INSIDE = -2,
        CGAL_LEFT,
        CGAL_ON,
        CGAL_RIGHT,
        CGAL_OUTSIDE
      };




enum  CGAL_Comparison_result
      { CGAL_SMALLER   = -1,
        CGAL_EQUAL,
        CGAL_LARGER
      };




enum CGAL_Intersection_result {CGAL_NO_INTERSECTION = 0,
                               CGAL_POINT_INTERSECTION,
                               CGAL_LINE_INTERSECTION,
                               CGAL_RAY_INTERSECTION,
                               CGAL_SEGMENT_INTERSECTION};

#endif
