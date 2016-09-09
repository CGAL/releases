#include <CGAL/basic.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

#include <CGAL/Cartesian.h>

#include <CGAL/squared_distance_2.h>   // to avoid a g++ problem
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>

#include <CGAL/Delaunay_triangulation_2.h>

class Options {
public:
    Options()
        :  file_input(false)

    {}

    char program[100];
    char fname[100];
    bool file_input;
};



void usage(char* program)
{
  cerr << "\nNAME\n     "
       << program << " - Triangulation of a point set\n\n";
  cerr << "SYNOPSIS\n     "
       << program << " [-file fname]\n";

  cerr << "\nDESCRIPTION\n"
       << "     Triangulates a point set that comes from a file or stdin.\n";
  cerr << "\nOPTIONS\n"
       << "     All options can be abbreviated by their first character\n\n";
}


bool
parse(int argc, char* argv[], Options &opt)
{
    strcpy(opt.program, argv[0]);
    --argc;
    argv++;

    while ((argc > 0) && (argv[0][0] == '-')){
        if ((!strcmp(argv[0], "-f")) || (!strcmp(argv[0], "-file"))) {
          strcpy(opt.fname, argv[1]);
          opt.file_input = true;
          argv += 2;
          argc -= 2;
      }
      else if ((!strcmp(argv[0], "-?")) ||
               (!strcmp(argv[0], "-h")) ||
               (!strcmp(argv[0], "-help"))) {
          usage(opt.program);
          return false;
      }
      else {
          cerr << "Unrecognized option " << argv[0] << endl;
          usage(opt.program);
          return false;
      }
    }
  if(argc > 0){
      cerr << "Unrecognized option " << argv[0] << endl;
      usage(opt.program);
      return false;
  }
  return true;
}





//typedef leda_integer  coord_type;
typedef double coord_type;
//typedef CGAL_Fixed coord_type;

typedef CGAL_Cartesian<coord_type>  Rep;
//typedef CGAL_Homogeneous<coord_type>  Rep;

typedef CGAL_Point_2<Rep>  Point;
typedef CGAL_Segment_2<Rep>  Segment;
typedef CGAL_Ray_2<Rep>  Ray;
typedef CGAL_Line_2<Rep>  Line;
typedef CGAL_Triangle_2<Rep>  Triangle;

typedef CGAL_Triangulation_euclidean_traits_2<Rep> Traits;

typedef CGAL_Delaunay_triangulation_2<Traits>  Triangulation_2;

typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex Vertex;
typedef Triangulation_2::Face_handle  Face_handle;
typedef Triangulation_2::Vertex_handle Vertex_handle;

typedef Triangulation_2::Face_circulator  Face_circulator;
typedef Triangulation_2::Vertex_circulator  Vertex_circulator;

typedef Triangulation_2::Locate_type Locate_type;

typedef Triangulation_2::Face_iterator  Face_iterator;
typedef Triangulation_2::Vertex_iterator  Vertex_iterator;
typedef Triangulation_2::Edge_iterator  Edge_iterator;
typedef Triangulation_2::Line_face_circulator  Line_face_circulator;


#ifdef __GNU__
template < class R >
bool operator<(const CGAL_Point_2<R>& p, const CGAL_Point_2<R>& q)
{
    return CGAL_compare_lexicographically_xy (p, q) == CGAL_SMALLER;
}
#endif // __GNU__

Triangulation_2 *T_global;

void input_from_file(Triangulation_2 &T,
                     const Options& opt)
{
    if(! opt.file_input){
        return;
    }

    ifstream is(opt.fname);
    CGAL_set_ascii_mode(is);

    int n;
    is >> n;
    cout << "Reading " << n << " points" << endl;

    istream_iterator<Point, ptrdiff_t> begin(is);
    istream_iterator<Point, ptrdiff_t> end;
    T.insert(begin, end);
}

int
main(int argc, char* argv[])
{
    Options opt;
    parse(argc, argv, opt);

    Triangulation_2 T;

    input_from_file(T, opt);
    
    cout << "Vertices :" << endl << "=============" << endl;
    Face_iterator fit, fbegin=T.faces_begin(), fend=T.faces_end(); 
    for (fit=fbegin; fit != fend; ++fit)
	cout << T.dual(fit) << endl;

    cout << "Segment :" << endl << "=============" << endl;
      {
	Edge_iterator eit, ebegin=T.edges_begin(), eend=T.edges_end(); 
	for (eit=ebegin; eit != eend; ++eit)
	  {
	    CGAL_Object o = T.dual(eit);
	    Triangulation_2::Segment s;
	    if (CGAL_assign(s,o)) cout << s << endl;
	  }
      }

    cout << "Rays :" << endl << "=============" << endl;
      {
	Edge_iterator eit, ebegin=T.edges_begin(), eend=T.edges_end(); 
	for (eit=ebegin; eit != eend; ++eit)
	  {
	    CGAL_Object o = T.dual(eit);
	    Triangulation_2::Ray r;
	    if (CGAL_assign(r,o)) cout << r << endl;
	  }
      }

    return 0;
}
