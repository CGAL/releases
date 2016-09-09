//! \file examples/Envelope_2/ex_convex_hull.cpp
// Compute the convex hull of set of points using the lower envelope and upper
// envelopes of their dual line.

#include <CGAL/Gmpq.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_linear_traits_2.h>
#include <CGAL/Arr_curve_data_traits_2.h>
#include <CGAL/Env_default_diagram_1.h>
#include <CGAL/envelope_2.h>
#include <vector>

typedef CGAL::Gmpq                                       Number_type;
typedef CGAL::Cartesian<Number_type>                     Kernel;
typedef CGAL::Arr_linear_traits_2<Kernel>                Linear_traits_2;
typedef Linear_traits_2::Point_2                         Point_2;
typedef Linear_traits_2::Line_2                          Line_2;
typedef CGAL::Arr_curve_data_traits_2<Linear_traits_2,
                                      unsigned int>      Traits_2;
typedef Traits_2::X_monotone_curve_2                     Dual_line_2;
typedef CGAL::Env_default_diagram_1<Traits_2>            Diagram_1;

int main (int argc, char **argv)
{
  // Get the name of the input file from the command line, or use the default
  // points.dat file if no command-line parameters are given.
  const char   *filename = "ch_points.dat";

  if (argc > 1)
    filename = argv[1];

  // Open the input file.
  std::ifstream     in_file (filename);

  if (! in_file.is_open())
  {
    std::cerr << "Failed to open " << filename << " ..." << std::endl;
    return (1);
  }

  // Read the points from the file, and construct their dual lines.
  unsigned int            n;
  int                     px, py;
  std::vector<Point_2>    points;
  Line_2                  line;
  std::list<Dual_line_2>  dual_lines;
  unsigned int            k;

  in_file >> n;
  points.resize (n);
  for (k = 0; k < n; ++k)
  {
    in_file >> px >> py;
    points[k] = Point_2 (px, py);

    // The line dual to the point (p_x, p_y) is y = p_x*x - p_y,
    // or: p_x*x - y - p_y = 0:
    line = Line_2 (Number_type(px), Number_type(-1), Number_type(-py));

    // Generate the x-monotone curve based on the line and the point index.
    dual_lines.push_back (Dual_line_2 (line, k));
  }
  in_file.close();

  // Compute the lower envelope of dual lines, which corresponds to the upper
  // part of the convex hull, and their upper envelope, which corresponds to
  // the lower part of the convex hull.
  Diagram_1              min_diag;
  Diagram_1              max_diag;

  lower_envelope_x_monotone_2 (dual_lines.begin(), dual_lines.end(),
                               min_diag);

  upper_envelope_x_monotone_2 (dual_lines.begin(), dual_lines.end(),
                               max_diag);

  // Output the points along the boundary convex hull in counterclockwise
  // order. We start by traversing the minimization diagram from left to
  // right, then the maximization diagram from right to left.
  Diagram_1::Edge_const_handle  e = min_diag.leftmost();

  std::cout << "The convex hull of " << points.size() << " input points:";
  while (e != min_diag.rightmost())
  {
    k = e->curve().data();    // The index of the dual point.
    std::cout << " (" << points[k] << ')';
    e = e->right()->right();
  }

  e = max_diag.rightmost();
  while (e != max_diag.leftmost())
  {
    k = e->curve().data();    // The index of the dual point.
    std::cout << " (" << points[k] << ')';
    e = e->left()->left();
  }
  std::cout << std::endl;

  return (0);
}
