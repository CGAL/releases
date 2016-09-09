
#ifndef CGAL_ENUM_H
#define CGAL_ENUM_H


enum  CGAL_Ordertype
      { CGAL_CLOCKWISE   = -1,
        CGAL_COLLINEAR,
        CGAL_COUNTERCLOCKWISE
      };

extern const CGAL_Ordertype   CGAL_LEFTTURN ;
extern const CGAL_Ordertype   CGAL_RIGHTTURN;
extern const CGAL_Ordertype   CGAL_POSITIVE ;
extern const CGAL_Ordertype   CGAL_NEGATIVE ;
extern const CGAL_Ordertype   CGAL_COPLANAR ;


enum  CGAL_Side
      { CGAL_INSIDE = -1,
        CGAL_ON,
        CGAL_OUTSIDE
      };


extern const CGAL_Side  CGAL_LEFT;
extern const CGAL_Side  CGAL_RIGHT;
extern const CGAL_Side CGAL_ON_BOUNDARY;


enum  CGAL_Comparison_result
      { CGAL_SMALLER   = -1,
        CGAL_EQUAL,
        CGAL_LARGER
      };


#endif
