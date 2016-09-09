 
// Source: Integer.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_CGAL_INTEGER_H
#define CGAL_CGAL_INTEGER_H

 



class CGAL_Integer : public integer
{

public:
          CGAL_Integer(){}
          CGAL_Integer(int n) : integer(n) {}
          CGAL_Integer(unsigned int ui) : integer(ui) {}
          CGAL_Integer(long l) : integer(l) {}
          CGAL_Integer(unsigned long ul) : integer(ul) {}
          CGAL_Integer(double d) : integer(d) {}
          CGAL_Integer(float f) : integer( double(f) ) {}
          CGAL_Integer(integer i) : integer(i) {}

          operator double() const { return todouble(); }
};
 


inline
bool
CGAL_is_finite(const CGAL_Integer &)
{
  return true;
}

inline
bool
CGAL_is_valid(const CGAL_Integer &)
{
  return true;
}

#endif // CGAL_CGAL_INTEGER_H
