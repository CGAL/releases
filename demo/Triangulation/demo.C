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
//#include <CGAL/Real.h>
#include <CGAL/squared_distance_2.h>   // to avoid a g++ problem
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/Triangulation_euclidean_traits_2.h>

#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/IO/Window_stream.h>

#include "parse.h"

//typedef leda_rational coord_type;
//typedef leda_integer  coord_type;
typedef double coord_type;
//typedef leda_real coord_type;
//typedef CGAL_Fixed coord_type;

typedef CGAL_Cartesian<coord_type>  Rep;
//typedef CGAL_Homogeneous<coord_type>  Rep;

typedef CGAL_Point_2<Rep>  Point_;
typedef CGAL_Segment_2<Rep>  Segment_;
typedef CGAL_Ray_2<Rep>  Ray_;
typedef CGAL_Line_2<Rep>  Line_;
typedef CGAL_Triangle_2<Rep>  Triangle_;

typedef CGAL_Triangulation_euclidean_traits_2<Rep> Traits_;

typedef CGAL_Triangulation_2<Traits_>  Triangulation_;
typedef CGAL_Delaunay_triangulation_2<Traits_>  Delaunay_;

typedef Triangulation_::Face  Face_;
typedef Triangulation_::Vertex Vertex_;
typedef Vertex_::Vertex_handle Vertex_handle_;
typedef Face_::Face_handle Face_handle_;

typedef Triangulation_::Face_circulator  Face_circulator_;
typedef Triangulation_::Vertex_circulator  Vertex_circulator_;

typedef Triangulation_::Locate_type Locate_type_;

typedef Triangulation_::Face_iterator  Face_iterator_;
typedef Triangulation_::Vertex_iterator  Vertex_iterator_;
typedef Triangulation_::Edge_iterator  Edge_iterator_;
typedef Triangulation_::Line_face_circulator  Line_face_circulator_;
typedef Triangulation_::Edge_circulator  Edge_circulator_;

typedef CGAL_Window_stream  Window_stream;

#ifdef __GNU__
template < class R >
bool operator<(const CGAL_Point_2<R>& p, const CGAL_Point_2<R>& q)
{
    return CGAL_compare_lexicographically_xy (p, q) == CGAL_SMALLER;
}
#endif // __GNU__

Window_stream *W_global;
Triangulation_ *T_global;

void
any_button(CGAL_Window_stream &W)
{
    double x, y;
    cerr << "Press any button to continue" << endl;
    W.read_mouse(x,y);
}


template < class TRIANGULATION > 
Vertex_handle_ closest_vertex(const TRIANGULATION &T,
               Face_handle_ f,
               const Point_& p)
{
    Vertex_handle_ v = f->vertex(0);
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

template <class TRIANGULATION>
void window_input(TRIANGULATION &T,
             Window_stream &W,
             const Options& opt)
{
    cerr << "Enter points with the left button" << endl;
    cerr << "Remove points with the middle button" << endl;
    cerr << "Right button terminates input of points" << endl;

    Point_ p;
    Point_ q(coord_type(W.xmin()-1),
            coord_type(W.ymin()-1));

    Face_handle_ highlight = NULL;
    Vertex_handle_ hv;

    while(1) {
        double x, y;
        int b = W.get_mouse(x,y);
        bool button_pressed = (b == MOUSE_BUTTON(1)) ||
                              (b == MOUSE_BUTTON(2)) ||
                              (b == MOUSE_BUTTON(3));
        p = Point_(coord_type(x),
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

            drawing_mode dm = W.set_mode(leda_xor_mode);
            if(vertex_change){
                W << CGAL_RED ;
                W.draw_node(CGAL_to_double(hv->point().x()),
                            CGAL_to_double(hv->point().y()));
            }
            W.set_mode(leda_src_mode);
            if(face_change){
                W << CGAL_BLUE << T.triangle(highlight);
                highlight = NULL;
            }
            W.set_mode(dm);
        }
        if(b == MOUSE_BUTTON(1)){
            typename TRIANGULATION::Locate_type lt;
            Vertex_handle_ v = T.insert(p, lt);
            if(opt.check){
                T.is_valid();
            }

            if(lt != TRIANGULATION::VERTEX){
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
                drawing_mode dm = W.set_mode(leda_src_mode);
                W << CGAL_RED << T.triangle(highlight) << CGAL_BLUE;
                W.set_mode(dm);
            } else {
                highlight = NULL;
            }
        }
        if(vertex_change){
            hv.clear();
        }
        if(button_pressed || vertex_change){
            if((highlight != NULL) && (! T.is_infinite(highlight))){
                drawing_mode dm = W.set_mode(leda_xor_mode);
                W << CGAL_RED;
                hv = closest_vertex(T, highlight, p);
                W.draw_node(CGAL_to_double(hv->point().x()),
                            CGAL_to_double(hv->point().y()));
                W << CGAL_BLUE;
                W.set_mode(dm);
            }
        }
        q = p;
    }
}

void file_input(Triangulation_ &T,
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
	cerr << "Reading from iterator" << endl;
        istream_iterator<Point_, ptrdiff_t> begin(is);
        istream_iterator<Point_, ptrdiff_t> end;
        T.insert(begin, end);
    }else{
	cerr << "Reading from point to point" << endl;
        Point_ mp;

        for(; n > 0; n--){
            is >> mp;
            Vertex_handle_ v = T.insert(mp);
            if(opt.check){
		cerr << "Checking validity" << endl;
                T.is_valid();
            }
            if(opt.draw){
#ifdef DELAUNAY
                W.clear();
                W << CGAL_BLUE << T << CGAL_RED;
#else
                Vertex_circulator_ vc = v->incident_vertices(),
                                  done(vc);
                if(vc != NULL){
                    do{
                        if(! T.is_infinite(vc)){
                            W << Segment_(v->point(), vc->point());
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
    cerr << "Done with file input" << endl;
}

void container_input(Triangulation_ &T,
                Window_stream &W)
{
    list<Point_> L;
    L.push_front(Point_(0,0));
    L.push_front(Point_(1,0));
    L.push_front(Point_(1,1));

    int n = T.insert(L.begin(), L.end());
    cerr << n << " points inserted from a list." << endl;

    vector<Point_> V(3);
    V[0] = Point_(0, 0);
    V[1] = Point_(0.4, 0.4);
    V[2] = Point_(0.3, 0.3);

    n = T.insert(V.begin(), V.end());
    cerr << n << " points inserted from a vector." << endl;

    W.clear();
    W << T;
}

void draw_incident_edges(Triangulation_ &T,
                    Vertex_handle_ v,
                    Window_stream &W)
{
    drawing_mode dm = W.set_mode(leda_xor_mode);

    W << CGAL_RED;
    Point_ p = v->point();

    Vertex_circulator_ vc = v->incident_vertices(),
                      done(vc);
    do {
        if(! T.is_infinite(vc)) {
            W << Segment_(p, vc->point());
        }
    } while(++vc != done);

    W.set_mode(dm);
}

void redraw_incident_edges(Triangulation_ &T,
                    Vertex_handle_ v,
                    Window_stream &W)
{
    drawing_mode dm = W.set_mode(leda_xor_mode);

    W << CGAL_RED;

    Edge_circulator_ ec = v->incident_edges(),
                      done(ec);
    do {
        if(! T.is_infinite(*ec)) {
            W << T.segment(*ec);
        }
    } while(++ec != done);

    W.set_mode(dm);
}

void draw_incident_edges(Triangulation_ &T,
                         Window_stream &W)
{
    if (T.dimension()<1) return;
    cerr << "Select a face" << endl;
    cerr << "The adjacent edges of the vertices of this face will be\n"
         << "highlighted in turn.\n";

    Point_ p;
    W >> p;
    Face_handle_ f = T.locate(p);

    for(int j = 0; j < 3; j++) {
        Vertex_handle_ v =  f->vertex(j);
        if(! T.is_infinite(v)) {
            cerr << "degree(v) = " << v->degree() << endl;
            draw_incident_edges(T, v, W);
            any_button(W);
            redraw_incident_edges(T, v, W);
        }
    }
}

void draw_faces_along_line(Triangulation_ &T,
                           Window_stream &W)
{
    if (T.dimension()<2) return;
    Point_ p, q;
    cerr << "Enter two points" << endl;
    W << CGAL_RED;
    drawing_mode dm = W.set_mode(leda_xor_mode);
    W >> p >> q;
    while (p==q) W<<q;
    W << p << q << Line_(p,q) << CGAL_RED;
    W.set_mode(dm);

    Face_handle_ f = T.locate(p);
    Line_face_circulator_ lfc = T.line_walk(p, q, f),
                         done(lfc);
    if(lfc == NULL){
        cerr << "Line does not intersect convex hull" << endl;
    } else {
        do{
            if(! T.is_infinite( lfc  )){
                W << T.triangle( lfc );
            }
        }while(++lfc != done);

        any_button(W);
        // Remove the line and unhighlight again
        dm = W.set_mode(leda_xor_mode);
        W << Line_(p,q) << CGAL_BLUE;
        W.set_mode(dm);
        do{
            if(! T.is_infinite( lfc )){
                W << T.triangle( lfc );
            }
        }while(--lfc != done);
    }
}

void draw_convex_hull(Triangulation_ &T,
                 Window_stream &W)
{
    if (T.dimension()<1) return;
    Point_ p, q;
    cerr << "Highlighting of the convex hull\n";

    Vertex_circulator_ chc = T.infinite_vertex()->incident_vertices(),
                           done(chc);
    if(chc == NULL) {
        cerr << "convex hull is empty" << endl;
    } else {
        drawing_mode dm = W.set_mode(leda_src_mode);
        W << CGAL_RED;
        p = chc->point();
        do {
            --chc;
            q = chc->point();
            W << Segment_(p, q);
            p = q;
        } while(chc != done);
        any_button(W);
        W << CGAL_BLUE;
        p = chc->point();
        do{
            ++chc;
            q = chc->point();
            W << Segment_(p, q);
            p = q;
        } while(chc != done);
        W.set_mode(dm);
    }
}

void show_nearest_vertex(Delaunay_ &T,
                    Window_stream &W)
{
    if (T.dimension()<1) return;
    cerr << "The vertex that is nearest to the cursor is highlighted" << endl;
    cerr << "Click any button to continue" << endl;

    Vertex_handle_ nv = NULL;
    Vertex_handle_ v = NULL;

    Point_ p;
    Point_ q(coord_type(W.xmin()-1),
            coord_type(W.ymin()-1));

    drawing_mode dm = W.set_mode(leda_xor_mode);
    while(1) {
        double x, y;
        int b = W.get_mouse(x,y);

        p = Point_(coord_type(x),
                  coord_type(y));
        if(p != q){
	  v = T.nearest_vertex(p);dm=W.set_mode(leda_xor_mode);
	  W << p<<v->point();
	  v = T.nearest_vertex(p); W << p<<v->point();W.set_mode(dm);
        }

        if( (nv != NULL) && ( (b != NO_BUTTON) || ((p != q) && (v != nv) ) )){
            // unhighlight
            x = CGAL_to_double(nv->point().x());
            y = CGAL_to_double(nv->point().y());
            W.draw_node(x, y, leda_red);
        }
        if(b != NO_BUTTON){
            W.set_mode(dm);
            return;
        }
        if( (p != q) && (v != nv) ){
            nv = v;
            x = CGAL_to_double(nv->point().x());
            y = CGAL_to_double(nv->point().y());
            W.draw_node(x, y, leda_red);
            q = p;
        }
    }
}

void fileIO(Delaunay_ &T,
            Window_stream &W,
            const Options& opt)
{
    cerr << "The triangulation will be written to a file and read again\n";
    {
        ofstream out("tr");
        CGAL_set_ascii_mode(out);
        out << T << endl;
    }
    Triangulation_ T2;

    ifstream in("tr");
    CGAL_set_ascii_mode(in);
    in >> T2;
    T2.is_valid();

    Window_stream W2(opt.winx, opt.winy);
    W2.init(opt.min, opt.max, opt.min);
    W2.set_show_coordinates(true);
    W2 << CGAL_BLUE;
    W2.display();

    W2 << T2;

    any_button(W);
}


void draw_dual( Delaunay_ &T, Window_stream &W )
{
   cerr << "The dual of the triangulation is displayed" << endl;
   W << CGAL_RED;
    Delaunay_::Face_iterator fit, fbegin=T.faces_begin(), fend=T.faces_end();
    for (fit=fbegin; fit != fend; ++fit)
        W << T.dual(fit);

    Delaunay_::Edge_iterator eit, ebegin=T.edges_begin(), eend=T.edges_end();
    for (eit=ebegin; eit != eend; ++eit)
    {
        CGAL_Object o = T.dual(eit);
        Traits_::Ray r;
        Traits_::Segment s;
        if (CGAL_assign(s,o)) W << s;
        if (CGAL_assign(r,o)) W << r;
    }
    any_button(W);
}
 
void action(int n)
{
  cerr << "action is called "<<n<<endl;
}


int main(int argc, char* argv[])
{
    Options opt;
    parse(argc, argv, opt);
    Triangulation_ T, Copy;
    Delaunay_ D, DCopy;
    T_global = &T;

    Window_stream W(opt.winx, opt.winy); // physical window size
    W_global = &W;

    W.init(opt.min, opt.max, opt.min);   // logical window size
    //  W.set_show_coordinates(true);
    W << CGAL_BLUE;
    W.set_mode(leda_src_mode);
    W.set_node_width(3);
    // W.button("toto",1,action);
    W.display();
    
    file_input(T, W, opt);
    (void) T.is_valid();
    W << T;
    window_input(T, W, opt);
    W.set_mode(leda_src_mode);
    W << CGAL_RED;
    W.clear();
    if(opt.check) T.is_valid();
    W << T;
    any_button(W);
    // Copy constructor
    cout << "copy"<<endl;
    Copy = Triangulation_(T);
    W << CGAL_BLUE;
    W << Copy;
    container_input(T, W);
    draw_faces_along_line(T, W);
    draw_incident_edges(T, W);
    draw_convex_hull(T, W);
 
    cout <<endl<<endl<< "DELAUNAY TRIANGULATION"<<endl;
    T_global = (Triangulation_ *)&D;
    W.clear();
    window_input(D, W, opt);
    W.set_mode(leda_src_mode);
    W << CGAL_RED;
    W.clear();
    if(opt.check) D.is_valid();
    W << D;
    any_button(W);
    // Copy constructor
    cout << "copy"<<endl;
    DCopy = Delaunay_(D);
    W << CGAL_BLUE;
    W << DCopy;
    show_nearest_vertex(D, W);
    fileIO(D, W, opt);
    draw_dual(D, W);

    return 0;
}

