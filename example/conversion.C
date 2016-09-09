
#include <iostream.h>
#include <CGAL/cartesian.h>
#include <CGAL/Rational.h>
#include <CGAL/Segment_2.h>
#include <CGAL/IO/ostream_2.h>

typedef CGAL_Rational coordtype;

typedef C<double> REPT1;
typedef C<coordtype> REPT2;

typedef CGAL_Point_2< REPT2 > Point;
typedef CGAL_Segment_2< REPT2 > Segment;



void conversion(double &res, const CGAL_Rational &arg)
{
  res = to_double(arg);
}


void conversion(int &res, const CGAL_Rational &arg)
{
  res = int(to_double(arg));
}
double Rational_to_double(const CGAL_Rational &n)
{
    return to_double(n);
}


template <class R1,  class R2, class RES, class ARG>
void conversion(CGAL_Point_2<R1> &result,
                const CGAL_Point_2<R2> &origin,
                void (*conversion)(RES &, const ARG &))
{
  R1::RT hx, hy, hw;
  conversion(hx, origin.hx());
  conversion(hy, origin.hy());
  conversion(hw, origin.hw());
  result = CGAL_Point_2<R1>(hx, hy, hw);
}
template <class R1,  class R2, class RES, class ARG>
void conversion(CGAL_Point_2<R1> &result,
                const CGAL_Point_2<R2> &origin,
                RES (*conversion)(const ARG &))
{
    result = CGAL_Point_2<R1>(conversion(origin.hx()),
                              conversion(origin.hy()),
                              conversion(origin.hw()));
}
template <class R1,  class R2, class RES, class ARG>
void conversion(CGAL_Segment_2<R1> &result,
                const CGAL_Segment_2<R2> &origin,
                void (*conversion)(RES &, const ARG &))
{
  CGAL_Point_2<R1> sp, ep;
  ::conversion(sp, origin.start(), conversion);
  ::conversion(ep, origin.end(), conversion);
  result = CGAL_Segment_2<R1>(sp, ep);
}
template <class R1,  class R2, class RES, class ARG>
void conversion(CGAL_Segment_2<R1> &result,
                const CGAL_Segment_2<R2> &origin,
                RES (*conversion)(const ARG &))
{
  CGAL_Point_2<R1> sp, ep;
  ::conversion(sp, origin.start(), conversion);
  ::conversion(ep, origin.end(), conversion);
  result = CGAL_Segment_2<R1>(sp, ep);
}


template < class R1, class R2 >
void two_template_parameters(const R1 &, const CGAL_Segment_2<R2> &segment2)
{
CGAL_Segment_2<R1> segment1;

  conversion(segment1, segment2,
             (void (*)(R1::RT&, const R2::RT &)) conversion);

  // now do something with segment1;
  cout << segment2 << endl << segment1 << endl;
}
template < class R2 >
void one_template_parameter(const CGAL_Segment_2<R2> &segment2)
{
  CGAL_Segment_2< C<double> > segment1;
  conversion(segment1, segment2,
             (double (*)(const R2::RT &)) to_double);

  cout << segment2 << endl << segment1 << endl;
}
void non_template_code()
{
  CGAL_Point_2<REPT2> point2(coordtype(10.5),
                             coordtype(32.5));
  CGAL_Point_2<REPT1> point1;
  conversion(point1, point2, Rational_to_double);

  cout << point2 << endl << point1 << endl;
}


int main()
{
  Segment segment2(Point(coordtype(1.5), coordtype(2.5)),
                   Point(coordtype(3.5), coordtype(4.5)));

  REPT1 rept1;
  two_template_parameters(rept1, segment2);

  one_template_parameter(segment2);

  non_template_code();

  return 1;
}
