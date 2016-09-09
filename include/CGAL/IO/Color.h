/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

 
// Source: Color.h
// Author: Andreas Fabri

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

