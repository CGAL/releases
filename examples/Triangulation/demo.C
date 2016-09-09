
#include <CGAL/basic.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

#include <CGAL/Cartesian.h>
//#include <CGAL/Homogeneous.h>
//#include <CGAL/Integer.h>
//#include <CGAL/Rational.h>
//#include <CGAL/Fixed.h>

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

#include <CGAL/IO/Window_stream.h>

#include "parse.h"



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

typedef CGAL_Window_stream  Window_stream;

#ifdef __GNU__
template < class R >
bool operator<(const CGAL_Point_2<R>& p, const CGAL_Point_2<R>& q)
{
    return CGAL_compare_lexicographically_xy (p, q) == CGAL_SMALLER;
}
#endif // __GNU__

Window_stream *W_global;
Triangulation_2 *T_global;

void
any_button(CGAL_Window_stream &W)
{
    double x, y;
    cerr << "Press any button to continue" << endl;
    W.read_mouse(x,y);
}


char*
db_pretty_print(const Face *t,
                int ,
                char *)
{
    Window_stream& W = *W_global;
    Triangulation_2& T = *T_global;
    ostrstream os;

    color c = W.set_color(blue);
    line_style l= W.set_line_style(dashed);
    drawing_mode dm = W.set_mode(xor_mode);

    Face* nct = (Face*)t;
    if(! T.is_infinite(nct)){
        os << T.triangle(nct);
    }
    W.set_color(c);
    W.set_mode(dm);
    W.set_line_style(l);

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
    Window_stream& W = *W_global;
    Point p = v->point();
    ostrstream os;

    drawing_mode dm = W.set_mode(xor_mode);
    double px = CGAL_to_double(p.x());
    double py = CGAL_to_double(p.y());
    W.draw_node(px, py, red);
    W.set_mode(dm);

    os << p << ends ;
    return os.str();
}


char*
db_pretty_print(const Point *pp,
                int ,
                char *)
{
    Window_stream& W = *W_global;
    Point p = *pp;
    ostrstream os;

    W.set_node_width(5);
    drawing_mode dm = W.set_mode(xor_mode);
    double px = CGAL_to_double(p.x());
    double py = CGAL_to_double(p.y());
    W.draw_node(px, py, red);
    W.set_mode(dm);

    os << p << ends ;
    return os.str();
}


Vertex*
closest_vertex(const Triangulation_2 &T,
               Face* f,
               const Point& p)
{
    Vertex* v = f->vertex(0);
    Rep::FT d  = CGAL_squared_distance(p, v->point());
    Rep::FT d2 = CGAL_squared_distance(p, f->vertex(1)->point());
    if(d2 < d){
        d = d2;
        v = f->vertex(1);
    }
    d2 = CGAL_squared_distance(p, f->vertex(2)->point());
    if(d2 < d){
        v = f->vertex(2);
    }
    return v;
}

void
window_input(Triangulation_2 &T,
             Window_stream &W,
             const Options& opt)
{
    cerr << "Enter points with the left button" << endl;
    cerr << "Remove points with the middle button" << endl;
    cerr << "Right button terminates input of points" << endl;

    Point p;
    Point q(coord_type(W.xmin()-1),
            coord_type(W.ymin()-1));

    Face* highlight = NULL;
    Vertex* hv      = NULL;

    while(1) {
        double x, y;
        int b = W.get_mouse(x,y);
        bool button_pressed = (b == MOUSE_BUTTON(1)) ||
                              (b == MOUSE_BUTTON(2)) ||
                              (b == MOUSE_BUTTON(3));
        p = Point(coord_type(x),
                  coord_type(y));
        bool mouse_moved = p != q;
        bool face_change = true,
             vertex_change = false;
        if( (highlight != NULL) && (button_pressed || mouse_moved) ){
            face_change = mouse_moved &&
                          ( T.oriented_side(highlight, p)
                                == CGAL_ON_NEGATIVE_SIDE );
            vertex_change = face_change ||
                            ( mouse_moved &&
                              ( hv != closest_vertex(T, highlight, p)));

            drawing_mode dm = W.set_mode(xor_mode);
            if(vertex_change){
                W << CGAL_RED ;
                W.draw_node(CGAL_to_double(hv->point().x()),
                            CGAL_to_double(hv->point().y()));
            }
            W.set_mode(src_mode);
            if(face_change){
                W << CGAL_GREEN << T.triangle(highlight);
                highlight = NULL;
            }
            W.set_mode(dm);
        }
        if(b == MOUSE_BUTTON(1)){
            Locate_type lt;
            Vertex* v = T.insert(p, lt);
            if(opt.check){
                T.is_valid();
            }

            if(lt != Triangulation_2::VERTEX){
                W.clear();
                W << T;
            }
        } else if(b == MOUSE_BUTTON(2)){
            if(hv != NULL){
                T.remove(hv);
                face_change = vertex_change = true;
                highlight = NULL;
                W.clear();
                W << T;
            }
        } else if(b == MOUSE_BUTTON(3)){
            // we are done. Nothing is highlighted
            break;
        }
        if( button_pressed || face_change){
            bool outside = highlight == NULL;
            highlight = T.locate(p, highlight);
            if((highlight != NULL) && (! T.is_infinite(highlight))){
                vertex_change = outside && true;
                drawing_mode dm = W.set_mode(src_mode);
                W << CGAL_RED << T.triangle(highlight) << CGAL_GREEN;
                W.set_mode(dm);
            } else {
                highlight = NULL;
            }
        }
        if(vertex_change){
            hv = NULL;
        }
        if(button_pressed || vertex_change){
            if((highlight != NULL) && (! T.is_infinite(highlight))){
                drawing_mode dm = W.set_mode(xor_mode);
                W << CGAL_RED;
                hv = closest_vertex(T, highlight, p);
                W.draw_node(CGAL_to_double(hv->point().x()),
                            CGAL_to_double(hv->point().y()));
                W << CGAL_GREEN;
                W.set_mode(dm);
            }
        }
        q = p;
    }
}


void
file_input(Triangulation_2 &T,
           Window_stream& W,
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

    if( (! opt.check) && (! opt.draw)){
        istream_iterator<Point, ptrdiff_t> begin(is);
        istream_iterator<Point, ptrdiff_t> end;
        T.insert(begin, end);
    }else{
        Point mp;
        for(; n > 0; n--){
            is >> mp;
            Vertex* v = T.insert(mp);
            if(opt.check){
                T.is_valid();
            }
            if(opt.draw){
#ifdef DELAUNAY
                W.clear();
                W << T;
#else
                Vertex_circulator vc = v->incident_vertices(),
                                  done(vc);
                if(*vc != NULL){
                    do{
                        if(! T.is_infinite(*vc)){
                            W << Segment(v->point(), (*vc)->point());
                        }
                    }while(++vc != done);
                }
#endif // DELAUNAY
            }

            if(++count == 100){
                cerr << ".";
                count = 0;
            }
        }
    }
}

void
container_input(Triangulation_2 &T,
                Window_stream &W)
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

    W.clear();
    W << T;
}

void
draw_incident_edges(Triangulation_2 &T,
                    Vertex* v,
                    Window_stream &W)
{
    drawing_mode dm = W.set_mode(xor_mode);

    W << CGAL_RED;
    Point p = v->point();

    Vertex_circulator vc = v->incident_vertices(),
                      done(vc);
    do {
        if(! T.is_infinite(*vc)) {
            W << Segment(p, (*vc)->point());
        }
    } while(++vc != done);

    W.set_mode(dm);
}
void draw_incident_edges(Triangulation_2 &T,
                         Window_stream &W)
{
    cerr << "Select a face" << endl;
    cerr << "The adjacent edges of the vertices of this face will be\n"
         << "highlighted in turn.\n";

    Point p;
    W >> p;
    Face* f = T.locate(p);

    for(int j = 0; j < 3; j++) {
        Vertex* v =  f->vertex(j);
        if(! T.is_infinite(v)) {
            cerr << "degree(v) = " << v->degree() << endl;
            draw_incident_edges(T, v, W);
            any_button(W);
            draw_incident_edges(T, v, W);
        }
    }
}


void draw_faces_along_line(Triangulation_2 &T,
                           Window_stream &W)
{
    Point p, q;
    cerr << "Enter two points" << endl;
    W << CGAL_RED;
    drawing_mode dm = W.set_mode(xor_mode);
    W >> p >> q;
    W << p << q << Line(p,q) << CGAL_RED;
    W.set_mode(dm);

    Face* f = T.locate(p);
    Line_face_circulator lfc = T.line_walk(p, q, f),
                         done(lfc);
    if(lfc == NULL){
        cerr << "Line does not intersect convex hull" << endl;
    } else {
        do{
            if(! T.is_infinite(*lfc)){
                W << T.triangle(*lfc);
            }
        }while(++lfc != done);

        any_button(W);
        // Remove the line and unhighlight again
        dm = W.set_mode(xor_mode);
        W << Line(p,q) << CGAL_GREEN;
        W.set_mode(dm);
        do{
            if(! T.is_infinite(*lfc)){
                W << T.triangle(*lfc);
            }
        }while(--lfc != done);
    }
}

void
draw_convex_hull(Triangulation_2 &T,
                 Window_stream &W)
{
    Point p, q;
    cerr << "Highlighting of the convex hull\n";

    Convex_hull_vertex_circulator chc = T.convex_hull(),
                           done(chc);
    if(*chc == NULL) {
        cerr << "convex hull is empty" << endl;
    } else {
        drawing_mode dm = W.set_mode(src_mode);
        W << CGAL_RED;
        p = (*chc)->point();
        do {
            --chc;
            q = (*chc)->point();
            W << Segment(p, q);
            p = q;
        } while(chc != done);
        any_button(W);
        W << CGAL_GREEN;
        p = (*chc)->point();
        do{
            ++chc;
            q = (*chc)->point();
            W << Segment(p, q);
            p = q;
        } while(chc != done);
        W.set_mode(dm);
    }
}

#ifdef DELAUNAY
void
show_nearest_vertex(Triangulation_2 &T,
                    Window_stream &W)
{
    cerr << "The vertex that is nearest to the cursor is highlighted" << endl;
    cerr << "Click any button to continue" << endl;

    Vertex* nv = NULL;
    Vertex* v = NULL;

    Point p;
    Point q(coord_type(W.xmin()-1),
            coord_type(W.ymin()-1));

    drawing_mode dm = W.set_mode(xor_mode);
    W.set_node_width(3);
    while(1) {
        double x, y;
        int b = W.get_mouse(x,y);

        p = Point(coord_type(x),
                  coord_type(y));
        if(p != q){
            v = T.nearest_vertex(p);
        }

        if( (nv != NULL) && ( (b != NO_BUTTON) || ((p != q) && (v != nv) ) )){
            // unhighlight
            x = CGAL_to_double(nv->point().x());
            y = CGAL_to_double(nv->point().y());
            W.draw_node(x, y, red);
        }
        if(b != NO_BUTTON){
            W.set_mode(dm);
            return;
        }
        if( (p != q) && (v != nv) ){
            nv = v;
            x = CGAL_to_double(nv->point().x());
            y = CGAL_to_double(nv->point().y());
            W.draw_node(x, y, red);
            q = p;
        }
    }
}
#endif // DELAUNAY

void fileIO(Triangulation_2 &T,
            Window_stream &W,
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

    Window_stream W2(opt.winx, opt.winy);
    W2.init(opt.min, opt.max, opt.min);
    W2.set_show_coordinates(true);
    W2 << CGAL_GREEN;

    W2 << T2;

    any_button(W);
}

int
main(int argc, char* argv[])
{
    Options opt;
    parse(argc, argv, opt);

    Triangulation_2 T;
    T_global = &T;

    Window_stream W(opt.winx, opt.winy); // physical window size
    W_global = &W;

    W.init(opt.min, opt.max, opt.min);   // logical window size

    W.set_show_coordinates(true);
    W << CGAL_GREEN;

    file_input(T, W, opt);

    W.clear();
    W << T;

    window_input(T, W, opt);

    container_input(T, W);

    draw_faces_along_line(T, W);

    draw_incident_edges(T, W);

    draw_convex_hull(T, W);


#ifdef DELAUNAY
    show_nearest_vertex(T, W);
#endif // DELAUNAY
    fileIO(T, W, opt);

    return 1;
}

