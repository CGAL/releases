 
// Source: Color.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_COLOR_H
#define CGAL_COLOR_H


class CGAL_Color {
public:
  CGAL_Color() {}
  CGAL_Color(int red, int green, int blue)
    : _red(red), _green(green), _blue(blue)
  {}

  int r() const {return _red;}
  int g() const {return _green;}
  int b() const {return _blue;}

  int red() const {return _red;}
  int green() const {return _green;}
  int blue() const {return _blue;}

  bool operator==(const CGAL_Color &c)
  {
    return ( (_red == c.red()) &&
             (_green == c.green()) &&
             (_blue == c.blue()) );
  }

  bool operator!=(CGAL_Color &c)
  {
    return !( (*this) == c);
  }

private:
  int _red;
  int _green;
  int _blue;
};

const CGAL_Color CGAL_BLACK  = CGAL_Color(0, 0, 0);
const CGAL_Color CGAL_WHITE  = CGAL_Color(255, 255, 255);
const CGAL_Color CGAL_RED    = CGAL_Color(255, 0, 0);
const CGAL_Color CGAL_GREEN  = CGAL_Color(0, 255, 0);
const CGAL_Color CGAL_BLUE   = CGAL_Color(0, 0, 255);
const CGAL_Color CGAL_VIOLET = CGAL_Color(255, 0, 255);
const CGAL_Color CGAL_ORANGE = CGAL_Color(255, 170, 0);
#endif  // CGAL_COLOR_H

