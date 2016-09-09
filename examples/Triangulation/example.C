
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

#ifndef DELAUNAY
#include <CGAL/Triangulation_2.h>
#else
#include <CGAL/Delaunay_triangulation_2.h>
#endif // DELAUNAY



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

#ifndef DELAUNAY
typedef CGAL_Triangulation_2<Traits>  Triangulation_2;
#else
typedef CGAL_Delaunay_triangulation_2<Traits>  Triangulation_2;
#endif // DELAUNAY

typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex Vertex;

typedef Triangulation_2::Face_circulator  Face_circulator;
typedef Triangulation_2::Vertex_circulator  Vertex_circulator;

typedef Triangulation_2::Locate_type Locate_type;

typedef Triangulation_2::Convex_hull_vertex_circulator
                                     Convex_hull_vertex_circulator;

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


char*
db_pretty_print(const Face *t,
                int ,
                char *)
{
    Triangulation_2& T = *T_global;
    ostrstream os;

    os << "(" << t->vertex(0)->point() << ", "
       << t->vertex(1)->point() << ", "
       << t->vertex(2)->point() << ")" << ends ;
    return os.str();
}


char*
db_pretty_print(const Vertex *v,
                int ,
                char *)
{
    Point p = v->point();
    ostrstream os;

    double px = CGAL_to_double(p.x());
    double py = CGAL_to_double(p.y());

    os << p << ends ;
    return os.str();
}


char*
db_pretty_print(const Point *pp,
                int ,
                char *)
{
    Point p = *pp;
    ostrstream os;

    double px = CGAL_to_double(p.x());
    double py = CGAL_to_double(p.y());

    os << p << ends ;
    return os.str();
}



void
input_from_file(Triangulation_2 &T,
                const Options& opt)
{
    if(! opt.file_input){
        return;
    }

    ifstream is(opt.fname);
    CGAL_set_ascii_mode(is);

    int n, count = 0;
    is >> n;
    cerr << "Reading " << n << " points" << endl;

    istream_iterator<Point, ptrdiff_t> begin(is);
    istream_iterator<Point, ptrdiff_t> end;
    T.insert(begin, end);
    
}

void
input_from_range(Triangulation_2 &T)
{
    list<Point> L;
    L.push_front(Point(0,0));
    L.push_front(Point(1,0));
    L.push_front(Point(1,1));

    int n = T.insert(L.begin(), L.end());
    cerr << n << " points inserted from a list." << endl;

    vector<Point> V(3);
    V[0] = Point(0, 0);
    V[1] = Point(0.4, 0.4);
    V[2] = Point(0.3, 0.3);

    list<Vertex*> Vertices;
    n = T.insert(V.begin(), V.end());
    cerr << n << " points inserted from a vector." << endl;

}


void faces_along_line(Triangulation_2 &T)
{
    Point p, q;
    cerr << "Enter the coordinates of two points" << endl;

    cin >> p >> q;
    Face* f = T.locate(p);
    Line_face_circulator lfc = T.line_walk(p, q, f),
                         done(lfc);
    if(lfc == NULL){
        cerr << "Line does not intersect convex hull" << endl;
    } else {
        int count = 0;
        do{
            if(! T.is_infinite(*lfc)){
                count++;
            }
        }while(++lfc != done);
        cerr << "The line intersects " << count << " finite faces" << endl;
    }
}

void
convex_hull(Triangulation_2 &T)
{
    Point p, q;

    Convex_hull_vertex_circulator chc = T.convex_hull(),
                                  done(chc);
    if(*chc == NULL) {
        cerr << "convex hull is empty" << endl;
    } else {
        p = (*chc)->point();
        do {
            --chc;
            q = (*chc)->point();
            p = q;
        } while(chc != done);
        
    }
}

void fileIO(Triangulation_2 &T,
            const Options& opt)
{
    cerr << "The triangulation will be written to a file and read again\n";
    {
        ofstream out("tr");
        CGAL_set_ascii_mode(out);
        out << T << endl;
    }
    Triangulation_2 T2;

    ifstream in("tr");
    CGAL_set_ascii_mode(in);
    in >> T2;
    T2.is_valid();
}

int
main(int argc, char* argv[])
{
    Options opt;
    parse(argc, argv, opt);

    Triangulation_2 T;
    T_global = &T;

    input_from_range(T);
    input_from_file(T, opt);

    faces_along_line(T);

    convex_hull(T);

    fileIO(T, opt);

    return 1;
}

