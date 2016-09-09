// Source: Color.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_COLOR_H
#define CGAL_COLOR_H


class CGAL_Color {
public:
  CGAL_Color() {}
  CGAL_Color(float r, float g, float b) {red = r; green =g; blue =b;}
  float r() const {return red;}
  float g() const {return green;}
  float b() const {return blue;}

  bool operator==(const CGAL_Color &c)
  {
    return ( (red == c.r()) &&
             (green == c.g()) &&
             (blue == c.b()) );
  }

  bool operator!=(CGAL_Color &c)
  {
    return !( (*this) == c);
  }

private:
  float red;
  float green;
  float blue;
};

extern CGAL_Color CGAL_black;
extern CGAL_Color CGAL_white;
extern CGAL_Color CGAL_red;
extern CGAL_Color CGAL_green;
extern CGAL_Color CGAL_blue;
extern CGAL_Color CGAL_violet;
extern CGAL_Color CGAL_orange;
#endif  // CGAL_COLOR_H

