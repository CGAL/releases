// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Triangulation_2.h
// package       : Triangulation (1.23)
// source        : web/Triangulation_2.fw
// revision      : $Revision: 1.45 $
// revision_date : $Date: 1998/07/15 14:07:01 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//                 Monique Teillaud
//                 Mariette Yvinec
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_2_H
#define CGAL_TRIANGULATION_2_H

#include <list.h>
#include <vector.h>
#include <map.h>
#include <algo.h>
#include <pair.h>
#include <CGAL/Object.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>

#include <CGAL/Triangulation_face_iterator.h>
#include <CGAL/Triangulation_edge_iterator.h>
#include <CGAL/Triangulation_vertex_iterator.h>

template < class I >
class CGAL_Triangulation_2;

template < class I >
class CGAL_Triangulation_2
{
friend istream& operator>> CGAL_NULL_TMPL_ARGS
                (istream& is, CGAL_Triangulation_2<I> &T);
public:
    typedef I                                     Traits;

    typedef typename I::Point                     Point;
    typedef typename I::Point                     value_type;
    typedef typename I::Segment                   Segment;
    typedef typename I::Triangle                  Triangle;


    typedef typename I::Vertex                    Vertex;
    typedef typename I::Face                      Face;

    typedef typename Vertex::Vertex_handle        Vertex_handle;
    typedef typename Face::Face_handle            Face_handle;
    typedef pair<Face_handle, int>                Edge;

    typedef typename Vertex::Face_circulator      Face_circulator;
    typedef typename Vertex::Edge_circulator      Edge_circulator;
    typedef typename Vertex::Vertex_circulator    Vertex_circulator;

    typedef CGAL_Triangulation_face_iterator<I>   Face_iterator;
    typedef CGAL_Triangulation_edge_iterator<I>   Edge_iterator;
    typedef CGAL_Triangulation_vertex_iterator<I> Vertex_iterator;

private:
    I             _traits;
    Vertex_handle _finite_vertex; // to handle number_of_vertices == 1
    Vertex_handle _infinite_vertex;
    int           _number_of_vertices;

protected:
    void set_number_of_vertices(int n) {_number_of_vertices = n;}

public:
    // LOCAL TYPES
    enum Locate_type {VERTEX=0, EDGE, FACE, OUTSIDE, COLLINEAR_OUTSIDE};

    // CONSTRUCTORS
    CGAL_Triangulation_2();
    CGAL_Triangulation_2(I& i);
    CGAL_Triangulation_2(const CGAL_Triangulation_2<I> &T);
    CGAL_Triangulation_2<I> &operator=(const CGAL_Triangulation_2<I> &T);
    ~CGAL_Triangulation_2();

protected:
     void init(Vertex_handle  v)
    {
        if( v == NULL ){
            _infinite_vertex = new Vertex();
        } else if( v->face() == NULL ){
            set_finite_vertex(v);
            set_number_of_vertices(1);
        } else if( (v->face()->neighbor(0) == v->face()->neighbor(1))
                 &&(v->face()->neighbor(0) == v->face()->neighbor(2)) ){
            set_infinite_vertex(v);
            Face_handle f = v->face();
            int i = f->index(v);
            set_finite_vertex(f->vertex(cw(i)));
            set_number_of_vertices(2);
        } else {
            set_infinite_vertex(v);
            Face_handle f = v->face();
            int i = f->index(v);
            set_finite_vertex(f->vertex(cw(i)));
            // the following makes that the constructor of the
            // vertex iterator class works correctly
            set_number_of_vertices(3);

            Vertex_iterator it = vertices_begin();

            while(it != vertices_end()){
                ++_number_of_vertices;
                ++it;
            }
            _number_of_vertices -= 3;
        }
    }

public:
    CGAL_Triangulation_2(const Vertex_handle&  v)
      : _infinite_vertex(NULL),
        _number_of_vertices(0)
    {
        init(v);
        CGAL_triangulation_postcondition( is_valid() );
    }


    CGAL_Triangulation_2(const Vertex_handle&  v,
                         I& i)
        : _infinite_vertex(NULL),
          _traits(i),
          _number_of_vertices(0)
    {
        init(v);
        CGAL_triangulation_postcondition( is_valid() );
    }

  // STATIC
    static int ccw(int i) {return (i+1) % 3;}
    static int cw(int i) {return (i+2) % 3;}

  // FORWARD DECLARATIONS
    void clear();
    void swap(CGAL_Triangulation_2<I> &T);
    void copy_triangulation(const CGAL_Triangulation_2<I> &T);

  // DIMENSION can be 0, 1 or 2
    int  dimension() const {
        if(number_of_vertices() == 0 || number_of_vertices() == 1){
            return 0;
        }
        Face_handle f = infinite_vertex()->face();
        int i = f->index(infinite_vertex());
        return (f->neighbor(i)->has_vertex(infinite_vertex())) ? 1 : 2;
    }

  // NUMBER OF FEATURES
    int number_of_vertices() const {return _number_of_vertices;}
    int number_of_faces() const {
        return (number_of_vertices() <= 1) ? 0 : 2 * number_of_vertices() - 2;
    }

    const Traits& traits() const {return _traits;}

  // TEST IF INFINITE FEATURES
    bool is_infinite(const Face_handle& f) const {
        return f->has_vertex(infinite_vertex());
    }
    bool is_infinite(const Vertex_handle& v) const {
        return v == infinite_vertex();
    }
    bool is_infinite(const Face_handle& f, int i) const {
      return is_infinite(f->vertex(ccw(i))) ||
             is_infinite(f->vertex(cw(i)));
    }
    bool is_infinite(Edge e) const {
      return is_infinite(e.first,e.second);
    }
    bool is_infinite(Edge_circulator& ec) const {
      return is_infinite(*ec);
    }

    bool is_infinite(Edge_iterator& ei) const {
      return is_infinite(*ei);
    }

  // NOT DOCUMENTED
    CGAL_Oriented_side
    oriented_side(const Point &p0, const Point &p1,
                  const Point &p2, const Point &p) const
    {
        // depends on the orientation of the vertices
        CGAL_Orientation o1 = traits().orientation(p0, p1, p),
                         o2 = traits().orientation(p1, p2, p),
                         o3 = traits().orientation(p2, p0, p),
                         ot = traits().orientation(p0, p1, p2);

        if (o1 == CGAL_COLLINEAR ||
            o2 == CGAL_COLLINEAR ||
            o3 == CGAL_COLLINEAR)  {
            if ((o1 == CGAL_COLLINEAR &&
                 collinear_between(p0, p, p1)) ||
                (o2 == CGAL_COLLINEAR &&
                 collinear_between(p1, p, p2)) ||
                (o3 == CGAL_COLLINEAR &&
                 collinear_between(p2, p, p0)))
                {
                return  CGAL_ON_ORIENTED_BOUNDARY;
            }
                // for ot == CGAL_ON_ORIENTED_BOUNDARY the following also
                // does the right thing:
                return (ot == CGAL_LEFTTURN) ? CGAL_ON_POSITIVE_SIDE
                                             : CGAL_ON_NEGATIVE_SIDE;
            }
        if (ot == CGAL_RIGHTTURN)
            {
                if (o1 == CGAL_RIGHTTURN &&
                    o2 == CGAL_RIGHTTURN &&
                    o3 == CGAL_RIGHTTURN)
                    {
                        return CGAL_ON_NEGATIVE_SIDE;
                    }
                return CGAL_ON_POSITIVE_SIDE;
            }
        if (o1 == CGAL_LEFTTURN &&
            o2 == CGAL_LEFTTURN &&
            o3 == CGAL_LEFTTURN)
            {
                return CGAL_ON_POSITIVE_SIDE;
            }
        return CGAL_ON_NEGATIVE_SIDE;
    }

  // not documented
    CGAL_Bounded_side
    bounded_side(const Point &p0, const Point &p1,
                 const Point &p2, const Point &p) const
    {
      CGAL_Orientation o1 = traits().orientation(p0, p1, p),
        o2 = traits().orientation(p1, p2, p),
        o3 = traits().orientation(p2, p0, p),
        ot = traits().orientation(p0, p1, p2);

      if(o1 == CGAL_COLLINEAR ||
         o2 == CGAL_COLLINEAR ||
         o3 == CGAL_COLLINEAR)
        {
          if ((o1 == CGAL_COLLINEAR &&
               collinear_between(p0, p, p1)) ||
              (o2 == CGAL_COLLINEAR &&
               collinear_between(p1, p, p2)) ||
              (o3 == CGAL_COLLINEAR &&
               collinear_between(p2, p, p0)))
            {
              return  CGAL_ON_BOUNDARY;
            }
          return CGAL_ON_UNBOUNDED_SIDE;
        }
      if (ot == CGAL_RIGHTTURN)
        {
          if(o1==CGAL_RIGHTTURN &&
             o2==CGAL_RIGHTTURN &&
             o3==CGAL_RIGHTTURN)
            {
              return CGAL_ON_BOUNDED_SIDE;
            }
          return CGAL_ON_UNBOUNDED_SIDE;
        }
      if (o1 == CGAL_LEFTTURN &&
          o2 == CGAL_LEFTTURN &&
          o3 == CGAL_LEFTTURN)
        {
          return CGAL_ON_BOUNDED_SIDE;
        }
      return CGAL_ON_UNBOUNDED_SIDE;
    }
    CGAL_Oriented_side
    oriented_side(const Face_handle& f, const Point &p) const
    {
        return oriented_side(f->vertex(0)->point(),
                             f->vertex(1)->point(),
                             f->vertex(2)->point(),
                             p);
    }

  // GEOMETRIC FEATURES
    Triangle triangle(const Face_handle& f) const
    {
        CGAL_triangulation_precondition( ! is_infinite(f) );
        return Triangle(f->vertex(0)->point(),
                        f->vertex(1)->point(),
                        f->vertex(2)->point());
    }
    Segment segment(const Face_handle& f, int i) const
    {
        CGAL_triangulation_precondition
          ((! is_infinite(f->vertex(ccw(i)))) &&
           (! is_infinite(f->vertex(cw(i)))) );
        return Segment(f->vertex(ccw(i))->point(),
                       f->vertex(cw(i))->point());
    }
    Segment segment(Edge e) const
    {
        CGAL_triangulation_precondition(! is_infinite(e));
        return Segment(e.first->vertex(ccw(e.second))->point(),
                       e.first->vertex( cw(e.second))->point());
    }

    Segment segment(const Edge_circulator& ec) const
    {
        return segment(*ec);
    }
    Segment segment(const Edge_iterator& ei) const
    {
        return segment(*ei);
    }

  // COMBINATORIAL FEATURES
    const Vertex_handle& finite_vertex() const
    {
        return _finite_vertex;
    }
    void set_finite_vertex(const Vertex_handle&  v)
    {
        _finite_vertex = v;
    }

    void set_finite_vertex(CGAL_NULL_TYPE v)
    {
        CGAL_triangulation_assertion( v == NULL);
        _finite_vertex.clear();
    }

    const Vertex_handle& infinite_vertex() const
    {
        return _infinite_vertex;
    }
    void set_infinite_vertex(const Vertex_handle&  v)
    {
        _infinite_vertex = v;
    }
    Face_handle infinite_face() const
    {
        CGAL_triangulation_precondition(_infinite_vertex->face()->
                                       has_vertex(_infinite_vertex));
        return _infinite_vertex->face();
    }

  // NOT DOCUMENTED
    bool collinear_between(const Point& p, const Point& q, const Point& r) const
    {
        CGAL_Comparison_result c_pr = traits().compare_x(p, r);
        CGAL_Comparison_result c_pq;
        CGAL_Comparison_result c_qr;
        if(c_pr == CGAL_EQUAL) {
            c_pr = traits().compare_y(p, r);
            c_pq = traits().compare_y(p, q);
            c_qr = traits().compare_y(q, r);
        } else {
            c_pq = traits().compare_x(p, q);
            c_qr = traits().compare_x(q, r);
        }
        return ( (c_pq == CGAL_SMALLER) && (c_qr == CGAL_SMALLER) ) ||
            ( (c_qr == CGAL_LARGER) && (c_pq == CGAL_LARGER) );
    
    }
    
    void flip(Face_handle& f, int i)
    {
        // bl == bottom left, tr == top right
        Face_handle tl = f->neighbor(ccw(i));
        Face_handle n  = f->neighbor(i);
    
        Vertex_handle  v_cw = f->vertex(cw(i));
        Vertex_handle  v_ccw = f->vertex(ccw(i));
    
        // The following seems natural, but it fails if the faces
        // f and n are neighbors on two edges (1-dim triangulation,
        // with infinite faces
        // int ni = n->index(f);
    
        int ni = cw(n->index(v_cw));
    
        CGAL_triangulation_assertion( f == n->neighbor(ni) );
    
        Face_handle br = n->neighbor(ccw(ni));
        int bri, tli;
    
        bri = br->index(n);
        tli = tl->index(f);
    
        f->set_vertex(cw(i), n->vertex(ni));
        n->set_vertex(cw(ni), f->vertex(i));
    
        // update the neighborhood relations
        f->set_neighbor(i, br);
        br->set_neighbor(bri, f);
    
        f->set_neighbor(ccw(i), n);
        n->set_neighbor(ccw(ni), f);
    
        n->set_neighbor(ni, tl);
        tl->set_neighbor(tli, n);
    
        if(v_cw->face() == f) {
            v_cw->set_face(n);
        }
    
        if(v_ccw->face() == n) {
            v_ccw->set_face(f);
        }
    }
    

protected:
    void insert_outside(Face_handle& f, const Vertex_handle& vp)
    {
        int li = f->index(infinite_vertex());
    
        Face_handle fcw;
        Face_handle fccw;
        Face_handle ff = f;
    
        Point p = vp->point();
        f->set_vertex(li, vp);
        int i = ccw(li);
        Vertex_handle  vq = f->vertex(i);
        Point q = vq->point();
        Face_handle n = f->neighbor(ccw(i));
        int ni = cw(n->index(vq)); // that works even in the 1D case
    
        bool done = false;
    
        while(! done) {
            Vertex_handle  vr = n->vertex(ni);
            Point r = vr->point();
            if( traits().orientation(p, q, r) == CGAL_RIGHTTURN ) {
                n->set_vertex(cw(ni), vp);
                f = n;
                i = ni;
                vq = vr;
                q = r;
                n = f->neighbor(ccw(i));
                ni = cw(n->index(vq));
            } else {
                fcw = new Face(infinite_vertex(), vq, vp,
                               f, NULL, n);
                infinite_vertex()->set_face(fcw);
                n->set_neighbor(ni, fcw);
                f->set_neighbor(ccw(i), fcw);
                vp->set_face(f);
                done = true;
            }
        }
    
        f = ff;
        i = cw(li);
    
        vq = f->vertex(i);
        q = vq->point();
        n = f->neighbor(cw(i));
        ni = ccw(n->index(vq));
    
        done = false;
    
        while(! done) {
            Vertex_handle  vr = n->vertex(ni);
            Point r = vr->point();
            if( traits().orientation(p, q, r) == CGAL_LEFTTURN) {
                n->set_vertex(ccw(ni), vp);
                f = n;
                i = ni;
                vq = vr;
                q = r;
                n = f->neighbor(cw(i));
                ni = ccw(n->index(vq));
            } else {
                fccw = new Face(infinite_vertex(), vp, vq,
                                f, n, fcw);
                fcw->set_neighbor(1, fccw);
                n->set_neighbor(ni, fccw);
                f->set_neighbor(cw(i), fccw);
                done = true;
            }
        }
    }
    

public:
  // INSERTION / DELETION
    Vertex_handle insert(const Point& p,
                         Locate_type& lt,
                         Face_handle f = Face_handle() )
    {
        Vertex_handle v;
        if(number_of_vertices() == 0) {
          v = new Vertex(p);
          lt = OUTSIDE;
          set_finite_vertex(v);
          set_number_of_vertices(1);
          return v;
        }
        if(number_of_vertices() == 1) {
                if (traits().compare(p,finite_vertex()->point())) {
                    lt = VERTEX;
                    return finite_vertex();
                  }
                v = new Vertex(p);
                lt = OUTSIDE;
                Face_handle f1 = new Face(infinite_vertex(), finite_vertex(), v,
                                    NULL, NULL, NULL);
    
                Face_handle f2 = new Face(infinite_vertex(), v, finite_vertex(),
                                    f1, f1, f1);
    
                f1->set_neighbor(0, f2);
                f1->set_neighbor(1, f2);
                f1->set_neighbor(2, f2);
    
                infinite_vertex()->set_face(f1);
                v->set_face(f1);
                finite_vertex()->set_face(f1);
                set_number_of_vertices(2);
                return v;
        }
    
        int li;
        Face_handle loc = locate(p, lt, li, f);
    
        switch(lt){
        case FACE:
            {
                v = new Vertex(p);
                loc->insert(v);
                _number_of_vertices++;
                break;
            }
        case OUTSIDE:
            {
                v = new Vertex(p);
                insert_outside(loc, v);
                _number_of_vertices++;
                break;
            }
        case EDGE:
            {
                v = new Vertex(p);
                Face_handle n = loc->neighbor(li);
                Vertex_handle  w = loc->vertex(ccw(li));
                int ni = ccw(n->index(w));
                loc->insert(v);
                _number_of_vertices++;
                flip(n, ni);
                break;
            }
        case COLLINEAR_OUTSIDE:
            {
                v = new Vertex(p);
                Vertex_handle  w = loc->vertex(li); // the extremal vertex
                Face_handle n = loc->neighbor(ccw(li));
                int ni = n->index(w);
                Face_handle f1 = new Face(infinite_vertex(), w, v,
                                    NULL, NULL, n);
                n->set_neighbor(cw(ni), f1);
                Face_handle f2 = new Face(infinite_vertex(), v, w,
                                    f1, loc, f1);
                f1->set_neighbor(0, f2);
                f1->set_neighbor(1, f2);
                loc->set_neighbor(ccw(li), f2);
                v->set_face(f1);
                infinite_vertex()->set_face(f1);
                _number_of_vertices++;
            }
        case VERTEX:
            return loc->vertex(li);
        default:
            CGAL_triangulation_assertion(false);  // locate step failed
        }
        return v;
    }
    

    Vertex_handle insert(const Point &p,
                         Face_handle f = Face_handle() )
    {
        Locate_type lt;
        return insert(p, lt, f);
    }

    Vertex_handle push_back(const Point &p)
    {
        Locate_type lt;
        return insert(p, lt, NULL);
    }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
    template < class InputIterator >
    int insert(InputIterator first, InputIterator last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#else
#if defined(LIST_H) || defined(__SGI_STL_LIST_H)
    int insert(list<Point>::const_iterator first,
               list<Point>::const_iterator last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#endif // LIST_H
#if defined(VECTOR_H) || defined(__SGI_STL_VECTOR_H)
    int insert(vector<Point>::const_iterator first,
               vector<Point>::const_iterator last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#endif // VECTOR_H
#ifdef ITERATOR_H
    int insert(istream_iterator<Point, ptrdiff_t> first,
               istream_iterator<Point, ptrdiff_t> last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#endif // ITERATOR_H
    int insert(Point* first,
               Point* last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#endif // CGAL_TEMPLATE_MEMBER_FUNCTIONS

    void remove(Vertex_handle&  v)
    {
      CGAL_triangulation_precondition(v != NULL);
      CGAL_triangulation_precondition( !is_infinite(v));
    
      if  (number_of_vertices() == 1) {
        // clear();
        v.Delete();
        set_finite_vertex(NULL);
        set_number_of_vertices(0);
        return;
      }
    
    
      // take care of finite_vertex data member
      if (finite_vertex() == v){
        Face_handle f = v->face();
        int i=f->index(v);
        Vertex_handle vv=is_infinite(f->vertex(cw(i))) ?
                           f->vertex(ccw(i)) : f->vertex(cw(i));
        set_finite_vertex( vv);
      }
    
      if (number_of_vertices() == 2) {
        Face_handle f = v->face();
        Face_handle ff =f->neighbor(0);
        ff.Delete();
        f.Delete();
      }
      else{
        if ( dimension() == 1) remove_1D(v);
        else  remove_2D(v);
      }
    
      v.Delete();
      set_number_of_vertices(number_of_vertices()-1);
      return;
    }
    

protected:
    void remove_1D(Vertex_handle& v)
    {
     //deal with one dimensional case
      Face_handle f1, f2, f1n, f2n;
      int i1,i2,i1n,i2n;
    
        switch( v->degree())  {
        case 2 :
          f1= v->face(); i1= f1->index(v);
          f2= f1->neighbor(cw(i1));  i2= f2->index(v);
          f1n = f1->neighbor(i1); i1n = f1n->index(f1);
          f2n = f2->neighbor(i2); i2n = f2n->index(f2);
          f1n->set_neighbor(i1n,f2n); f2n->set_neighbor(i2n,f1n);
          f1.Delete(); f2.Delete();
          return;
    
        case 4 :
          int j1,j2,j1n,j2n;
           f1= v->face(); i1= f1->index(v);
           j1 = (is_infinite(f1->vertex(cw(i1)))) ? ccw(i1) : cw(i1);
           // j1 is the other finite vertex of f1
           // 3-i1-j1 is the index of the infinite_vertex in face f1
           f2 = f1->neighbor(3-i1-j1); i2 = f2->index(v);
           j2 = f2->index(f1->vertex(j1));
           f1n = f1->neighbor(j1); i1n = f1n->index(v); j1n = f1n->index(f1);
           f2n = f2->neighbor(j2); i2n = f2n->index(v); j2n = f2n->index(f2);
    
           // update f1n and f2n
           f1n->set_vertex(i1n,f1->vertex(j1));
           f2n->set_vertex(i2n,f2->vertex(j2));
           if(f1->neighbor(i1) != f2) {
             Face_handle ff1 = f1->neighbor(i1);
             Face_handle ff2 = f2->neighbor(i2);
             f1n->set_neighbor(j1n,ff1); ff1->set_neighbor(ff1->index(f1),f1n);
             f2n->set_neighbor(j2n,ff2); ff2->set_neighbor(ff2->index(f2),f2n);
           }
           else {
             f1n->set_neighbor(j1n,f2n);
             f2n->set_neighbor(j2n,f1n);
           }
           f1.Delete(); f2.Delete();
           return;
        }
     }
    

    void remove_2D(Vertex_handle& v)
    {
      // General case
    
      // remove incident faces
      // set up list of faces neighboring the hole
      // in ccw order around the hole
    
      typedef pair<Face_handle  , int>  Hole_Neighbor;
      typedef list<Hole_Neighbor> Hole;
    
      Hole hole;
      typename Hole::iterator hit;
    
      Face_handle  f, ff, fn;
      int i =0,ii =0, in =0;
      Vertex_handle  vv;
      Point p = v->point();
    
      Face_circulator fc = v->incident_faces();
      Face_circulator done(fc);
       do {
          i = fc->index(v);
          fn = fc->neighbor(i);
          vv = fc->vertex(fc->cw(i));
          if( vv->face()== fc) vv->set_face(fn);
          vv = fc->vertex(fc->ccw(i));
          if( vv->face()== fc) vv->set_face(fn);
          in = fn->index(fc);
          fn->set_neighbor(in, NULL);
          hole.push_back(Hole_Neighbor(fn,in));
          fc++.Delete();
        }
      while(fc != done);
    
    
      while( hole.size() != 3)
        {
           //  find the first edge  v0v1 on the hole boundary
          //  such that
          //  v0, v1 and the next vertex v2 are all finite
         //   v0v1v2 is a left turn
          //  triangle v0v1v2 does not contain the removed point
    
    
          Vertex_handle v0, v1, v2;
          Point   p0, p1, p2;
          Triangle t;
          CGAL_Bounded_side side;
    
         bool ok = false;
         int nhole= hole.size();
         while (!ok && nhole>0) {
            hole.push_back(hole.front());
            hole.pop_front();
            nhole--;
            hit = hole.begin();
            ff  = (*hit).first;
            ii  = (*hit).second;
            v0 = ff->vertex(cw(ii));
            v1 = ff->vertex(ccw(ii));
            if(is_infinite(v0) || is_infinite(v1))  continue;
    
            hit++;
            fn =   (*hit).first; in = (*hit).second;
            v2 = fn->vertex(ccw(in));
            if(is_infinite(v2)) continue;
    
            p0 = v0->point();
            p1 = v1->point();
            p2 = v2->point();
            CGAL_Orientation or = traits().orientation(p0,p1,p2);
            if ( or  == CGAL_RIGHTTURN) continue;
            side = bounded_side(p0,p1,p2, p);
            if( side == CGAL_ON_BOUNDED_SIDE) continue;
            if(side == CGAL_ON_BOUNDARY &&
               ! (or == CGAL_COLLINEAR && collinear_between(p0, p, p2) ))
               continue;
    
            ok = true;
         }
    
    
          if(ok != true) break;
          // new triangle has not been found
          // meaning that all the hole vertices
          // are reflex or infinite
    
           // new triangle has been found
           // update triangulation and hole
          Face_handle  newf = new Face(v0,v1,v2);
          newf->set_neighbor(2,ff);
          newf->set_neighbor(0,fn);
          ff->set_neighbor(ii, newf);
          fn->set_neighbor(in,newf);
          hole.pop_front();
          hole.pop_front();
          hole.push_front(Hole_Neighbor(newf,1));
        }
    
    
    
    // either the hole has only three edges
      // or all its finite vertices are reflex
      if(hole.size() != 3){
          ff = (hole.front()).first;
          ii = (hole.front()).second;
          while ( ! is_infinite(ff->vertex(cw(ii)))){
            hole.push_back(hole.front());
            hole.pop_front();
            ff = (hole.front()).first;
            ii = (hole.front()).second;
          }
          while(hole.size() != 3){
            ff = (hole.front()).first;
            ii = (hole.front()).second;
            hole.pop_front();
            fn = (hole.front()).first;
            in = (hole.front()).second;
            hole.pop_front();
            Face_handle  newf = new Face(infinite_vertex(),fn->vertex(cw(in)),
                                                     fn->vertex(ccw(in)));
            ff->set_neighbor(ii,newf);
            fn->set_neighbor(in,newf);
            newf->set_neighbor(0,fn);
            newf->set_neighbor(2,ff);
            hole.push_front(Hole_Neighbor(newf,1));
            }
      }
    
    
          // now hole has three edges
          Face_handle  newf = new Face();
          hit = hole.begin();
          for(int j = 0;j<3;j++) {
            ff = (*hit).first;
            ii = (*hit).second;
            hit++;
            ff->set_neighbor(ii,newf);
            newf->set_neighbor(j,ff);
            newf->set_vertex(newf->ccw(j),ff->vertex(ff->cw(ii)));
          }
    }
    

public:
    //
    // $RCSfile: Line_face_circulator.fw,v $
    // $Revision: 1.17 $
    // $Date: 1998/06/23 15:11:57 $
    //
    
    class Line_face_circulator
        : public CGAL_Bidirectional_circulator_base<Face,ptrdiff_t,size_t>,
          public Face::Face_handle
    {
        public:
            //typedef Vertex::Face_circulator
            //                       Face_circulator ;
            
            typedef Face           value_type;
            typedef Face   &       reference;
            typedef const Face   & const_reference;
            typedef unsigned int   size_type;
            typedef int            distance_type;
            
            enum State {undefined = -1,
                        vertex_vertex,
                        vertex_edge,
                        edge_vertex,
                        edge_edge};
            
            Line_face_circulator()
                : Face::Face_handle(), T(NULL), s(undefined), i(-1)
            {}
            
            Line_face_circulator(const Line_face_circulator& lfc)
                : Face::Face_handle(lfc), T(lfc.T), s(lfc.s), i(lfc.i),  p(lfc.p), q(lfc.q)
            {}
            
            ~Line_face_circulator()
            {}
            
            
            Line_face_circulator(const Face_handle& face,
                                 int index,
                                 State state,
                                 CGAL_Triangulation_2<I>* t,
                                 const Point& pp,
                                 const Point& qq)
                : Face::Face_handle(face), T(t), s(state), i(index),  p(pp), q(qq)
            {
                CGAL_triangulation_precondition(! T->traits().compare(p,q));
            }
            
            
            Line_face_circulator&
            operator=(const Line_face_circulator& lfc)
            {
                ptr() = lfc.ptr();
                i = lfc.i;
                s = lfc.s;
                T = lfc.T;
                p = lfc.p;
                q = lfc.q;
                return *this;
            }
            Line_face_circulator(Vertex_handle v,
                                 CGAL_Triangulation_2<I>* Tr,
                                 const Point& dir)
                : T(Tr)
            {
                CGAL_triangulation_precondition((! T->is_infinite(v)) &&
                                                (T->dimension() == 2) &&
                                                !T->traits().compare(v->point(),dir));
            
                ptr() = &(*v->face());
            
                while(T->is_infinite(ptr()->handle())){
                    i = ptr()->index(v);
                    ptr() = &(*ptr()->neighbor(cw(i)));
                }
                i = ptr()->index(v);
                p = v->point();
                q = dir;
            
                Point t = ptr()->vertex(ccw(i))->point();
                Point r = ptr()->vertex(cw(i))->point();
            
                CGAL_Orientation ptq = T->traits().orientation(p, t, q);
                CGAL_Orientation prq = T->traits().orientation(p, r, q);
            
                if( ptq == CGAL_LEFTTURN  && prq == CGAL_RIGHTTURN ) {
                    s = vertex_edge;
                } else if( (ptq == CGAL_COLLINEAR) && (prq == CGAL_RIGHTTURN) ) {
                    i= ccw(i);
                    s = vertex_vertex;
                } else if( (prq == CGAL_COLLINEAR) && (ptq == CGAL_LEFTTURN) ) {
                    Face_handle n = ptr()->neighbor(ccw(i));
                    i = n->index(ptr()->vertex(cw(i)));
                    ptr() = &(*n);
                    s = vertex_vertex;
                } else if( ptq == CGAL_LEFTTURN ) {
                    do{
                        Face_handle n = ptr()->neighbor(ccw(i));
                        i = n->index(ptr()->handle());
                        ptr() = &(*n);
                        if(T->is_infinite(n)){
                            s = vertex_vertex;
                            return;
                        }
                        r = n->vertex(i)->point();
                        i = ccw(i);
                    }while((prq = T->traits().orientation(p, r, q)) == CGAL_LEFTTURN);
            
                    if(prq == CGAL_COLLINEAR){
                        Face_handle n = ptr()->neighbor(ccw(i));
                        i = cw(n->index(ptr()->handle()));
                        ptr() = &(*n);
                        s = vertex_vertex;
                    } else {
                        s = vertex_edge;
                    }
                } else {
                    do{
                        Face_handle n = ptr()->neighbor(cw(i));
                        i = n->index(ptr()->handle());
                        ptr() = &(*n);
                        if(T->is_infinite(n)){
                            s = vertex_vertex;
                            return;
                        }
                        t = n->vertex(i)->point();
                        i = cw(i);
                    }while((ptq = T->traits().orientation(p, t, q)) == CGAL_RIGHTTURN);
            
                    if(ptq == CGAL_COLLINEAR){
                        s = vertex_vertex;
                        i = ccw(i);
                    } else {
                        s = vertex_edge;
                    }
                }
            }
            Line_face_circulator(const Point& pp,
                                 const Point& qq,
                                 CGAL_Triangulation_2<I>* t)
                : T(t), s(undefined), p(pp), q(qq)
            {
                Vertex_handle inf = T->infinite_vertex();
                Face_circulator fc = inf->incident_faces(),
                    done(fc);
                i = fc->index(inf);
            
                Point l = fc->vertex(cw(i))->point(),
                    r = fc->vertex(ccw(i))->point();
            
                CGAL_Orientation pql = T->traits().orientation(p, q, l),
                    pqr = T->traits().orientation(p, q, r);
            
            
                do{
                    if( (pql == CGAL_LEFTTURN) && (pqr == CGAL_RIGHTTURN) ){
                        *this = ++Line_face_circulator( fc ,
                                                       i,
                                                       vertex_edge,
                                                       t,
                                                       p,
                                                       q);
                        return;
                    } else if ( (pql == CGAL_LEFTTURN) && (pqr == CGAL_COLLINEAR) ){
                        *this = ++Line_face_circulator( fc ,
                                                       ccw(i),
                                                       vertex_vertex,
                                                       t,
                                                       p,
                                                       q);
                        return;
                    } else if( (pql == CGAL_COLLINEAR) && (pqr == CGAL_COLLINEAR) ){
                        Face_handle n = fc->neighbor(i);
                        int ni  = n->index( fc );
                        Vertex_handle vn = n->vertex(ni);
                        if(T->traits().orientation(p, q, vn->point()) == CGAL_LEFTTURN){
                            // the entire triangulation is to the left of line (p,q).
                            // There might be further collinear edges, so we might have
                            // to walk back on the hull.
                            while(1){
                                ++fc;
                                i = fc->index(inf);
                                l = fc->vertex(cw(i))->point();
                                if(T->traits().orientation(p, q, l) == CGAL_COLLINEAR){
                                    continue;
                                } else {
                                    // we went one step to far back
                                    --fc;
                                    i = fc->index(inf);
                                    ptr() = &(*fc->neighbor(i));
                                    i = cw(ptr()->index( fc ));
                                    s = vertex_vertex;
                                    return;
                                }
                            }
                        } else {
                            // the entire triangulation is to the right of line (p,q).
                            // There are no faces to traverse, so we give the circulator
                            // a singular value
                            return;
                        }
                    } else {
                        --fc;
                        l = r;
                        pql = pqr;
                        i = fc->index(inf);
                        r = fc->vertex(ccw(i))->point();
                        pqr = T->traits().orientation(p, q, r);
                    }
                }while(fc != done);
                // if line (p,q) does not intersect the convex hull in an edge
                // the circulator has a singular value
            }
            Line_face_circulator(const Point& pp,
                                 const Point& qq,
                                 const Face_handle& ff,
                                 CGAL_Triangulation_2<I>* t)
                : Face::Face_handle(ff), T(t), s(undefined), p(pp), q(qq)
            {
                //CGAL_triangulation_precondition(T->is_infinite(f) ||
                //                         T->oriented_side(f,p) != CGAL_ON_NEGATIVE_SIDE);
            
                int j;
                if(T->is_infinite(ptr()->handle())){
                    *this  = Line_face_circulator(p, q, t);
                    return;
                }
            
                // Test whether p lies on a vertex
                for(j = 0; j < 3; j++){
                    if(T->traits().compare(ptr()->vertex(j)->point(),p)){
                        *this = Line_face_circulator( ptr()->vertex(j), t, q);
                        return;
                    }
                }
            
                // Test whether p lies on an edge
                for(j = 0; j < 3; j++){
                    if(T->traits().orientation(ptr()->vertex(j)->point(),
                                             ptr()->vertex(ccw(j))->point(),
                                             p) == CGAL_COLLINEAR){
                        CGAL_Orientation jpq =
                            T->traits().orientation(ptr()->vertex(j)->point(),
                                                  p,
                                                  q);
                        CGAL_Orientation p_cwj_q =
                            T->traits().orientation(p,
                                                  ptr()->vertex(cw(j))->point(),
                                                  q);
                        switch(jpq){
                        case CGAL_COLLINEAR:
                            if(p_cwj_q == CGAL_RIGHTTURN){
                                s = vertex_vertex;
                                i = ccw(j);
                                return;
                            } else if(! T->is_infinite(ptr()->neighbor(cw(j)))){
                                Face_handle n = ptr()->neighbor(cw(j));
                                i = cw(n->index(ptr()->handle()));
                                ptr() = &(*n);
                                s = vertex_vertex;
                                return;
                            } else {
                                // singular value
                                return;
                            }
                        case CGAL_RIGHTTURN:
                            i = cw(j);
                            s = (p_cwj_q == CGAL_COLLINEAR) ? vertex_edge :  edge_edge;
                            break;
                        default: //  CGAL_LEFTTURN
                            switch(p_cwj_q){
                            case CGAL_COLLINEAR:
                                s = edge_vertex;
                                i = cw(j);
                                return;
                            case CGAL_RIGHTTURN:
                                s = edge_edge;
                                i = j;
                                return;
                            default:
                                s = edge_edge;
                                i = ccw(j);
                                return;
                            }
                        }
                    }
                }
            
                // p lies in the interior of the face
                CGAL_Orientation or[3];
                for(j=0; j<3; j++){
                    or[j] = T->traits().orientation(p,q,ptr()->vertex(j)->point());
                }
                for(j=0; j<3; j++){
                    if(or[j] == CGAL_COLLINEAR){
                        i = j;
                        s = (or[ccw(j)] == CGAL_LEFTTURN) ? edge_vertex : vertex_edge;
                        return;
                    }
                }
                s = edge_edge;
                for(j=0; j<3; j++){
                    if(or[j] == CGAL_RIGHTTURN){
                        i = (or[ccw(j)] == CGAL_RIGHTTURN) ? j : cw(j);
                        return;
                    }
                }
            }
            void increment()
            {
                CGAL_triangulation_precondition(s != undefined);
                if(s == vertex_vertex || s == edge_vertex){
                    CGAL_Orientation o;
                    Point r;
                    do{
                        Face_handle n = ptr()->neighbor(cw(i));
                        i = n->index(ptr()->handle());
                        ptr() = &(*n);
                        if (n->vertex(i) == T->infinite_vertex()){
                            o = CGAL_COLLINEAR;
                            i = cw(i);
                            break;
                        }
                        r = n->vertex(i)->point();
                        i = cw(i);
                    }while((o = T->traits().orientation(p, q, r)) == CGAL_LEFTTURN);
            
                    if(o == CGAL_COLLINEAR){
                        s = vertex_vertex;
                        i = ccw(i);
                    } else {
                        s = vertex_edge;
                    }
                } else {
                    Face_handle n = ptr()->neighbor(i);
                    int ni = n->index(ptr()->handle());
                    ptr() = &(*n);
                    CGAL_Orientation o = T->is_infinite(ptr()->vertex(ni)) ?
                        CGAL_COLLINEAR :
                        T->traits().orientation(p, q, ptr()->vertex(ni)->point());
            
                    switch(o){
                    case CGAL_LEFTTURN:
                        s = edge_edge;
                        i = ccw(ni);
                        break;
                    case CGAL_RIGHTTURN:
                        s = edge_edge;
                        i = cw(ni);
                        break;
                    default:
                        s = edge_vertex;
                        i = ni;
                    }
                }
            }
            
            
            void decrement()
            {
                CGAL_triangulation_precondition(s != undefined);
                if(s == vertex_vertex || s == vertex_edge){
                    if(s == vertex_vertex){
                        i = cw(i);
                    }
                    CGAL_Orientation o;
                    Point r;
                    do{
                        Face_handle n = ptr()->neighbor(ccw(i));
                        i = n->index(ptr()->handle());
                        ptr() = &(*n);
                        if (n->vertex(i) == T->infinite_vertex()){
                            o = CGAL_COLLINEAR;
                            i = ccw(i);
                            break;
                        }
                        r = n->vertex(i)->point();
                        i = ccw(i);
                    }while((o = T->traits().orientation(p, q, r)) == CGAL_LEFTTURN);
            
                    s = (o == CGAL_COLLINEAR) ? vertex_vertex : edge_vertex;
            
                } else { // s == edge_edge  ||  s == edge_vertex
                    // the following is not nice. A better solution is to say
                    // that index i is at the vertex that is alone on one side of l(p,q)
                    if(s == edge_edge){
                        i = (T->traits().orientation
                                            (p, q,
                                            ptr()->vertex(i)->point()) == CGAL_LEFTTURN)
                            ? cw(i) : ccw(i);
                    }
                    Face_handle n = ptr()->neighbor(i);
                    i = n->index(ptr()->handle());
                    ptr() = &(*n);
                    CGAL_Orientation o = T->is_infinite(ptr()->vertex(i)) ?
                        CGAL_COLLINEAR :
                        T->traits().orientation(p, q, ptr()->vertex(i)->point());
            
                    s = (o == CGAL_COLLINEAR) ? vertex_edge : edge_edge;
                }
            }
            bool
            locate(const Point& t,
                   Locate_type &lt,
                   int &li)
            {
                switch(s){
            
                case edge_edge:
                case vertex_edge:
                    {
                        CGAL_Orientation o =
                            T->traits().orientation(ptr()->vertex(ccw(i))->point(),
                                                  ptr()->vertex(cw(i))->point(),
                                                  t);
                        if(o == CGAL_RIGHTTURN){
                            return false;
                        }
                        if(o == CGAL_COLLINEAR){
                            lt = EDGE;
                            li = i;
                            return true;
                        }
                        lt = FACE;
                        return true;
                    }
                case vertex_vertex:
                    {
                        if(T->is_infinite(ptr()->vertex(i))){
                            CGAL_triangulation_assertion(T->traits().orientation(
                                                         ptr()->vertex(cw(i))->point(),
                                                         ptr()->vertex(ccw(i))->point(),
                                                         t) != CGAL_LEFTTURN);
                            lt = OUTSIDE;
                            li = i;
                            return true;
                        }
            
                        Point u = ptr()->vertex(cw(i))->point();
                        Point v = ptr()->vertex(i)->point();
                        // u == t  was detected earlier
                        if(T->traits().compare(v,t)){
                            lt = VERTEX;
                            li = i;
                            return true;
                        }
                        if(T->collinear_between(u, t, v)){
                            lt = EDGE;
                            li = ccw(i);
                            return true;
                        }
                        return false;
                    }
                default: // edge_vertex
                    {
                        if(T->is_infinite(ptr()->vertex(i))){
                            lt = OUTSIDE;
                            li = i;
                            return true;
                        }
                        if(T->traits().compare(t,ptr()->vertex(i)->point())){
                            li = i;
                            lt = VERTEX;
                            return true;
                        }
                        if(T->collinear_between(p, t, ptr()->vertex(i)->point())){
                            lt = FACE;
                            return true;
                        }
                        return false;
                    }
                }
            }
            Line_face_circulator&
            operator++()
            {
                if (ptr()==NULL) {
                   return *this; // circulator has singular value
                }
                //xfc while (T->is_infinite(ptr()->handle()))
                //    increment();
                //we are looking for a finite face but stop if back to the origin
                Face_handle origin = ptr()->handle();
                do
                 increment();
                while ((T->is_infinite(ptr()->handle())) && (ptr()->handle() != origin));
            
                return *this;
            }
            
            
            Line_face_circulator&
            operator--()
            {
                if (ptr()==NULL) {
                   return *this; // circulator has singular value
                }
                while (T->is_infinite(ptr()->handle()))
                       decrement();
                return *this;
            }
            
            
            Line_face_circulator
            operator++(int)
            {
                Line_face_circulator tmp(*this);
                ++(*this);
                return tmp;
            }
            
            
            Line_face_circulator
            operator--(int)
            {
                Line_face_circulator tmp(*this);
                --(*this);
                return tmp;
            }
            bool
            operator==(const Line_face_circulator& lfc) const
            {
                CGAL_triangulation_precondition
                          ( ptr() != NULL  &&  lfc.ptr() != NULL );
                return ptr() == lfc.ptr();
            }
            
            bool
            operator!=(const Line_face_circulator& lfc) const
            {
                CGAL_triangulation_precondition
                            ( ptr() != NULL  &&  lfc.ptr() != NULL );
                return ptr() != lfc.ptr();
            }
            
            
            inline bool
            operator==(CGAL_NULL_TYPE n) const
            {
                CGAL_triangulation_assertion( n == NULL);
                return s == undefined;
            }
            
            inline bool
            operator!=(CGAL_NULL_TYPE n) const
            {
                return !(*this == n);
            }
            
            bool
            collinear_outside() const
            {
            
                return (T->is_infinite(ptr()->handle()))
                        && (s == vertex_vertex)
                        && (! T->is_infinite(ptr()->vertex(i)));
            }
            
        private:
            CGAL_Triangulation_2<I>* T;
            State s;
            int i;
            Point p, q;
            
        };
    

  // POINT LOCATION
    Face_handle
    march_locate_1D(const Point& t,
                    Locate_type& lt,
                    int& li) const
    
    {
        Face_handle i_f = infinite_face();
        int i = i_f->index(infinite_vertex());
        Point p = i_f->vertex(ccw(i))->point();
        Point q = i_f->vertex(cw(i))->point();
        CGAL_Orientation pqt = traits().orientation(p, q, t);
        if(pqt == CGAL_RIGHTTURN){
            lt = OUTSIDE;
            return i_f->neighbor(i);
        }
        if(pqt == CGAL_LEFTTURN){
            lt = OUTSIDE;
            return i_f;
        }
        Vertex_handle  vi = infinite_vertex();
        Face_circulator fc = vi->incident_faces();
        i = fc->index(vi);
        Vertex_handle  u = fc->vertex(ccw(i));
        Vertex_handle  v = fc->vertex(cw(i));
        Vertex_handle  w;
    
        while(1){
            if(traits().compare(t,v->point())){
                lt = VERTEX;
                li = cw(i);
                return fc ;
            }
            if(collinear_between(u->point(), t, v->point())){
                lt = EDGE;
                li = i;
                return fc ;
            }
            ++fc;
            i = fc->index(vi);
            w = fc->vertex(cw(i));
            if( (u == w) && collinear_between(u->point(), v->point(), t)){
                lt = COLLINEAR_OUTSIDE;
                li = ccw(i);
                return fc ;
            }
            u = v;
            v = w;
        }
    }
    


    Face_handle
    march_locate_2D(const Face_handle& start,
                    const Point& t,
                    Locate_type& lt,
                    int& li) const
    {
        CGAL_triangulation_precondition( ! is_infinite(start) );
        CGAL_Triangulation_2<I> *ncthis = (CGAL_Triangulation_2<I>*)this;
    
        Point p(start->vertex(0)->point());
        if(traits().compare(p,t)){
            lt = VERTEX;
            li = 0;
            return start;
        }
        Line_face_circulator lfc(start->vertex(0),
                                 ncthis,
                                 t);
        if(lfc.collinear_outside()){
            // point t lies outside or on the convex hull
            // we walk clockwise on the hull
            int i = lfc->index(infinite_vertex());
            p = lfc->vertex(ccw(i))->point();
            if(traits().compare(t,p)){
                lt = VERTEX;
                li = ccw(i);
                return lfc;
            }
         Point q(lfc->vertex(cw(i))->point());
         Face_handle f(lfc);
         while(1){
           if(traits().compare(t,q)){
             lt = VERTEX;
             li = cw(i);
             return f;
           }
           if(collinear_between(p, t, q)){
             // t != p and t != q
             lt = EDGE;
             li = i;
             return f;
           }
           // go to the next face
           f = f->neighbor(ccw(i));
           i = f->index(infinite_vertex());
           p = q;
           q = f->vertex(cw(i))->point();
           if(traits().orientation(p,q,t) == CGAL_LEFTTURN){
             lt = OUTSIDE;
             return f ;
           }
         }
        }
        while(! lfc.locate(t, lt, li) ){
          lfc.increment();
        }
        return lfc;
    }
    

    inline Face_handle
    locate(const Point& p,
           Locate_type& lt,
           int& li,
           Face_handle start = Face_handle()) const
    {
        if(number_of_vertices() < 2) {
            if(number_of_vertices() == 0) {
                lt = OUTSIDE;
            } else { // number_of_vertices() == 1
                lt = traits().compare(p,finite_vertex()->point())
                   ? VERTEX : OUTSIDE;
            }
            return NULL;
        }
        if(dimension() == 1){
            return march_locate_1D(p, lt, li);
        }
    
        if(start == NULL){
            start = infinite_face()->
                        neighbor(infinite_face()->index(infinite_vertex()));
        }else if(is_infinite(start)){
            start = start->neighbor(start->index(infinite_vertex()));
        }
    
        return march_locate_2D(start, p, lt, li);
    }
    

    inline Face_handle
    locate(const Point &p,
           Face_handle start = Face_handle()) const
    {
        Locate_type lt;
        int li;
        return locate(p, lt, li, start);
    }
    

  // ITERATOR METHODS
    Face_iterator faces_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I> *)this;
        return Face_iterator(ncthis);
    }
    Face_iterator faces_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I> *)this;
        return Face_iterator(ncthis, 1);
    }
    Vertex_iterator vertices_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Vertex_iterator(ncthis);
    }
    Vertex_iterator vertices_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Vertex_iterator(ncthis,1);
    }
    Edge_iterator edges_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Edge_iterator(ncthis);
    }
    Edge_iterator edges_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Edge_iterator(ncthis,1);
    }


    Line_face_circulator
    line_walk(const Point& p,
              const Point& q,
              Face_handle f = Face_handle())
    {
        CGAL_triangulation_precondition( (dimension() == 2)
                                      && !traits().compare(p,q) );
    
        Line_face_circulator lfc = (f == NULL)
                                   ? Line_face_circulator(p, q, this)
                                   : Line_face_circulator(p, q, f, this);
    
        if((! (lfc == NULL)) && is_infinite( lfc )){
            return Line_face_circulator();
        }
        return lfc;
    }
    


    bool is_valid(bool verbose = false, int level = 0) const
    {
        if(number_of_vertices() <= 1){
            return true;
        }
    
        bool result = true;
    
        int vertex_count = 0;
        {
            Vertex_iterator it = vertices_begin();
    
            while(it != vertices_end()){
                ++vertex_count;
                ++it;
            }
        }
    
        result = result && (number_of_vertices() == vertex_count);
    
        CGAL_triangulation_assertion( number_of_vertices() == vertex_count );
    
        int edge_count = 0;
        {
            Edge_iterator it = edges_begin();
    
            while(it != edges_end()){
                ++edge_count;
                ++it;
            }
        }
    
        int face_count = 0;
        {
            Face_iterator it = faces_begin();
    
            while(it != faces_end()){
                ++face_count;
                result = result && it->is_valid(verbose, level);
                CGAL_triangulation_assertion( it->is_valid(verbose, level) );
                result = result && (! is_infinite(it));
                CGAL_triangulation_assertion( ! is_infinite(it) );
                CGAL_Orientation s = traits().orientation(it->vertex(0)->point(),
                                                          it->vertex(1)->point(),
                                                          it->vertex(2)->point());
                result = result && ( s == CGAL_LEFTTURN );
                CGAL_triangulation_assertion( s == CGAL_LEFTTURN );
                ++it;
            }
        }
    
    
        Face_circulator fc = infinite_vertex()->incident_faces(),
            fcdone(fc);
        do{
            if(dimension() == 2){
                result = result && fc->is_valid(verbose, level);
                CGAL_triangulation_assertion( fc->is_valid(verbose, level) );
            }
            ++face_count;
            ++edge_count;
        }while(++fc != fcdone);
    
    
        Vertex_circulator start = infinite_vertex()->incident_vertices(),
            pc(start),
            qc(start),
            rc(start);
        ++qc;
        ++rc;
        ++rc;
        do{
            bool extremal = ( traits().extremal(pc->point(),
                                                qc->point(),
                                                rc->point()) != CGAL_POSITIVE);
            result = result && extremal;
            CGAL_triangulation_assertion( extremal );
            pc = qc;
            qc = rc;
            ++rc;
        }while(pc != start);
        result = result && ( edge_count == 3* (vertex_count -1) );
        CGAL_triangulation_assertion( edge_count == 3* (vertex_count -1) );
        result = result && ( face_count == 2* (vertex_count -1) );
        CGAL_triangulation_assertion( face_count == 2* (vertex_count -1) );
    
        return result;
    }
    

};


template < class I >
CGAL_Triangulation_2<I>::CGAL_Triangulation_2()
    : _infinite_vertex(NULL),
      _number_of_vertices(0)
{
    _infinite_vertex = new Vertex();
}


template < class I >
CGAL_Triangulation_2<I>::CGAL_Triangulation_2(I& i)
    : _infinite_vertex(NULL),
      _traits(i),
      _number_of_vertices(0)
{
    _infinite_vertex = new Vertex();
}


template < class I >
CGAL_Triangulation_2<I>::CGAL_Triangulation_2
                  (const CGAL_Triangulation_2<I> &T)
{
  copy_triangulation(T);
}

template < class I >
CGAL_Triangulation_2<I> & CGAL_Triangulation_2<I>::operator=
                  (const CGAL_Triangulation_2<I> &T)
{
  copy_triangulation(T);
  return *this;
}

template < class I >
void CGAL_Triangulation_2<I>::swap(CGAL_Triangulation_2<I> &T)
{
  //I       t  = traits();
    Vertex_handle  fv = finite_vertex();
    Vertex_handle  iv = infinite_vertex();
    int     nv = number_of_vertices();
    //  _traits = T.traits();
    set_finite_vertex(T.finite_vertex());
    set_infinite_vertex(T.infinite_vertex());
    set_number_of_vertices(T.number_of_vertices());
    //T._traits = t;
    T.set_finite_vertex(fv);
    T.set_infinite_vertex(iv);
    T.set_number_of_vertices(nv);
}

template < class I >
void CGAL_Triangulation_2<I>::copy_triangulation(const CGAL_Triangulation_2<I> &T)
{
    map< void*, void*, less<void*> > V;
    map< void*, void*, less<void*> > F;
    typedef typename I::Vertex Vertex;
    typedef typename I::Face Face;
    Vertex*  v2;
    Face* f2;

    int n = T.number_of_vertices();
    int m = T.number_of_faces();
    set_number_of_vertices(n);
    // _traits =  T.traits();        //  operator= needed for traits

    // create the vertex at infinity
    int i = 0;
    set_infinite_vertex(
            ((Vertex*)(V[&(*T.infinite_vertex())]=new Vertex()))
                          ->handle());

    if(n == 0){
        return ;
    }

    if(n == 1){
        set_finite_vertex(
                (new Vertex(T.finite_vertex()->point()))->handle());
        return ;
    }

    // create the finite vertices
    {
        typename CGAL_Triangulation_2<I>::Vertex_iterator
          it = T.vertices_begin();

        while(it != T.vertices_end()) {
            V[&(*it)] = new Vertex( it->point() );
            ++it;
        }
    }

     // create the finite faces
    {
        typename CGAL_Triangulation_2<I>::Face_iterator
          it = T.faces_begin();

        while(it != T.faces_end()){
            F[&(*it)]=
              new Face(  ((Vertex*) V[&(*it->vertex(0))])->handle(),
                         ((Vertex*) V[&(*it->vertex(1))])->handle(),
                         ((Vertex*) V[&(*it->vertex(2))])->handle() );
            ++it;
        }
    }

    // create the infinite faces
    {
        typename CGAL_Triangulation_2<I>::Face_circulator
          fc = T.infinite_vertex()->incident_faces(),
          done(fc);

        do{
            F[&(*fc)]=
              new Face(  ((Vertex*) V[&(*fc->vertex(0))])->handle(),
                            ((Vertex*) V[&(*fc->vertex(1))])->handle(),
                            ((Vertex*) V[&(*fc->vertex(2))])->handle());
        }while(++fc != done);
    }

    // link the infinite vertex to a triangle
    infinite_vertex()->set_face(((Face*)F[&(*T.infinite_face())])->handle());

    // link the finite vertices to a triangle
    {
        CGAL_Triangulation_2<I>::Vertex_iterator it = T.vertices_begin();

        while(it != T.vertices_end()) {
            v2 = (Vertex*) V[&(*it)];
            v2->set_face( ((Face*) F[ &(*it->face()) ])->handle() );
            ++it;
        }
    }

    // hook neighbor pointers of the finite faces
    {
        typename CGAL_Triangulation_2<I>::Face_iterator
            it = T.faces_begin();
        while(it != T.faces_end()){
          for(int j = 0; j < 3; j++){
            f2 = ((Face*) F[&(*it)]);
            f2->set_neighbor(j, ((Face*) F[ &(*it->neighbor(j))])->handle());
          }
          ++it;
        }
    }

    // hook neighbor pointers of the infinite faces
    {
        typename CGAL_Triangulation_2<I>::Face_circulator
            fc = T.infinite_vertex()->incident_faces(),
            done(fc);

        do{
          f2 = ((Face*) F[&(*fc)]);
          for(int j = 0; j < 3; j++){
            f2->set_neighbor(j, ((Face*) F[ &(*fc->neighbor(j))])->handle());
          }
        }while(++fc != done);
    }
    CGAL_triangulation_postcondition( is_valid() );

}

template < class I >
CGAL_Triangulation_2<I>::~CGAL_Triangulation_2()
{
    clear();
    _infinite_vertex.Delete();
}
template < class I >
void
CGAL_Triangulation_2<I>::clear()
{
    if(number_of_vertices() <= 1){
        return;
    }

    list<Face*> Faces;
    list<Vertex*> Vertices;

    {
        Vertex_iterator it = vertices_begin(), done = vertices_end();
        do{
            Vertices.push_front(&(*it));
        }while(++it!=done);
    }
    {
        Face_iterator it = faces_begin(), done = faces_end();
        while(it!=done){
            Faces.push_front(&(*it));
            ++it;
        }
        Face_circulator fc = infinite_vertex()->incident_faces(),
            fcdone(fc);
        do{
            Faces.push_front(&(*fc));
        }while(++fc != fcdone);
    }
    CGAL_triangulation_assertion( number_of_faces() == (int) Faces.size());

    {
        typename list<Face*>::iterator
          it=Faces.begin(),done=Faces.end();
        do{
            delete *it;
        }while(++it!=done);
    }
    {
        typename list<Vertex*>::iterator
          it=Vertices.begin(),done=Vertices.end();
        do{
            delete *it;
        }while(++it!=done);
    }

    infinite_vertex()->set_face(NULL);
    set_finite_vertex(NULL);
    set_number_of_vertices(0);
}


template < class I >
ostream&
operator<<(ostream& os, const CGAL_Triangulation_2<I> &T)
{
    map< void*, int, less<void*> > V;
    map< void*, int, less<void*> > F;
    typename CGAL_Triangulation_2<I>::Vertex_handle  v;

    int n = T.number_of_vertices() + 1;
    int m = T.number_of_faces();
    if(CGAL_is_ascii(os)){
        os << n << ' ' << m << ' ' << T.dimension() << endl;
    } else {
        os << n << m << T.dimension();
    }

    // write the vertex at infinity
    int i = 0;
    v = T.infinite_vertex();
    V[&(*v)] = i;
    os << v->point();
    if(CGAL_is_ascii(os)){
        os << ' ';
    }
    if(n == 1){
        return os;
    }

    // write the finite vertices
    {
        typename CGAL_Triangulation_2<I>::Vertex_iterator
          it = T.vertices_begin();

        while(it != T.vertices_end()){
            V[&(*it)] = ++i;
            os << it->point();
            if(CGAL_is_ascii(os)){
                os << ' ';
            }
            ++it;
        }
    }
    CGAL_triangulation_assertion( (i+1) == n );

    if(n == 2){
        return os;
    }

    i = 0;
    // vertices of the finite faces
    {
        typename CGAL_Triangulation_2<I>::Face_iterator
          it = T.faces_begin();

        while(it != T.faces_end()){
            F[&(*it)] = i++;
            for(int j = 0; j < 3; j++){
                os << V[&(*it->vertex(j))];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
            ++it;
        }
    }

    // vertices of the infinite faces
    {
        typename CGAL_Triangulation_2<I>::Face_circulator
            fc = T.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            F[&(*fc)] = i++;
            for(int j = 0; j < 3; j++){
                os << V[&(*fc->vertex(j))];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
        }while(++fc != done);
    }
    CGAL_triangulation_assertion( i == m );

    // neighbor pointers of the finite faces
    {
        typename CGAL_Triangulation_2<I>::Face_iterator
            it = T.faces_begin();
        while(it != T.faces_end()){
            for(int j = 0; j < 3; j++){
                os << F[&(*it->neighbor(j))];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
            ++it;
        }
    }

    // neighbor pointers of the infinite faces
    {
        typename CGAL_Triangulation_2<I>::Face_circulator
            fc = T.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            for(int j = 0; j < 3; j++){
                os << F[&(*fc->neighbor(j))];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
        }while(++fc != done);
    }

    return os;
}

template < class I >
istream&
operator>>(istream& is, CGAL_Triangulation_2<I> &T)
{
    typedef typename CGAL_Triangulation_2<I>::Vertex_handle  Vertex_handle;
    typedef typename CGAL_Triangulation_2<I>::Face_handle Face_handle;
    Vertex_handle v;
    Face_handle f;

    if(T.number_of_vertices() != 0){
        T.clear();
    }

    int i = 0;
    int n, m, d;
    is >> n >> m >> d;

    T.set_number_of_vertices(n-1);

    vector<Vertex_handle > V(n);
    vector<Face_handle> F(m);

    // the first point is at infinity

    typename I::Point p;
    is >> p;
    v = T.infinite_vertex();
    v->set_point(p);
    V[i] = v;
    ++i;

    if(n == 1){
        return is;
    }
    // for the other points we create new vertices
    for(; i < n; i++) {
        typename I::Point p;
        is >> p;
        V[i] = new typename I::Vertex(p);
    }

    T.set_finite_vertex(V[i-1]);

    if(n == 2){
        return is;
    }
    // Creation of the faces
    for(i = 0; i < m; i++) {
        int i0, i1, i2;
        is >> i0 >> i1 >> i2;
        f = new typename I::Face(V[i0], V[i1], V[i2]);
        F[i] = f;
        // The face pointer of vertices is set too often,
        // but otherwise we had to use a further map
        V[i0]->set_face(f);
        V[i1]->set_face(f);
        V[i2]->set_face(f);
    }

    // Setting the neighbor pointers is the same for the
    // faces on the other side of the plane  and the other faces
    for(i = 0; i < m; i++) {
        int i0, i1, i2;
        is >> i0 >> i1 >> i2;
        f = F[i];
        f->set_neighbor(0, F[i0]);
        f->set_neighbor(1, F[i1]);
        f->set_neighbor(2, F[i2]);
    }
    T.infinite_vertex()->set_face(f);
    return is;
}


#endif // CGAL_TRIANGULATION_2_H
