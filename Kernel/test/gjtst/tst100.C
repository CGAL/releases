
#include <CGAL/Cartesian.h>
#include <iostream.h>

template < class R >
class X {
public:
  X()
  {
    R::FT ft_zero = 0;
    R::RT rt_zero = R::FT_denominator(ft_zero);
  }
};

int main()
{
  X<CGAL_Cartesian<int> > x;
  return 1;
}
