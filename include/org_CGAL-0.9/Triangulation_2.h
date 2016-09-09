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


#ifndef CGAL_TRIANGULATION_2_H
#define CGAL_TRIANGULATION_2_H
#ifdef __KCC
#include <functional.h>
#endif // __KCC
#include <list.h>
#include <vector.h>
#include <map.h>
#ifdef __KCC
#include <algorithm.h>
#else
#include <algo.h>
#endif // __KCC
#include <pair.h>
#include <CGAL/Circulator.h>

#include <CGAL/Triangulation_2_face_iterator.h>
#include <CGAL/Triangulation_2_edge_iterator.h>
#include <CGAL/Triangulation_2_vertex_iterator.h>
#include <CGAL/Triangulation_2_convex_hull_vertex_circulator.h>
#include <CGAL/Delete.h>


template < class I >
class CGAL_Triangulation_2;

template < class I >
class CGAL_Triangulation_2
{
    friend istream& operator>>(istream& is, CGAL_Triangulation_2<I> &T);
public:
    typedef I Traits;
    typedef I::Point Point;
    typedef I::Segment Segment;
    typedef I::Triangle Triangle;

    typedef CGAL_Triangulation_vertex<Point> Vertex;
    typedef CGAL_Triangulation_face<Vertex> Face;

    typedef I::Vertex::Face_circulator Face_circulator;
    typedef I::Vertex::Vertex_circulator Vertex_circulator;

    typedef CGAL_Triangulation_2_face_iterator<I>   Face_iterator;
    typedef CGAL_Triangulation_2_edge_iterator<I>   Edge_iterator;
    typedef CGAL_Triangulation_2_vertex_iterator<I> Vertex_iterator;

    typedef CGAL_Triangulation_2_convex_hull_vertex_circulator<Vertex,Face>
                                                Convex_hull_vertex_circulator;

private:
    I _traits;
    Vertex* _finite_vertex; // to handle number_of_vertices == 1
    Vertex* _infinite_vertex;
    int _number_of_vertices;


protected:
    void
    set_number_of_vertices(int n)
    {
        _number_of_vertices = n;
    }



public:
    enum Locate_type {VERTEX=0, EDGE, FACE, OUTSIDE, COLLINEAR_OUTSIDE};

    CGAL_Triangulation_2();

    CGAL_Triangulation_2(I& i);

    ~CGAL_Triangulation_2();

    void
    init(Vertex* v)
    {
        if( v == NULL ){
            _infinite_vertex = new Vertex();
        } else if( v->face() == NULL ){
            set_finite_vertex(v);
            set_number_of_vertices(1);
        } else {
            set_infinite_vertex(v);
            Face* f = v->face();
            int i = f->index(v);
            set_finite_vertex(f->vertex(cw(i)));

            Vertex_iterator it = vertices_begin();

            while(it != vertices_end()){
                ++_number_of_vertices;
                ++it;
            }
        }
    }

    CGAL_Triangulation_2(Vertex* v)
        : _infinite_vertex(NULL),
          _number_of_vertices(0)
    {
        init(v);
        CGAL_kernel_postcondition( is_valid() );
    }


    CGAL_Triangulation_2(Vertex* v,
                         I& i)
        : _infinite_vertex(NULL),
          _traits(i),
          _number_of_vertices(0)
    {
        init(v);
        CGAL_kernel_postcondition( is_valid() );
    }


    static
    int
    ccw(int i)
    {
        return (i+1) % 3;
    }


    static
    int
    cw(int i)
    {
        return (i+2) % 3;
    }

    void
    clear();

    int
    dimension() const
    {
        if(number_of_vertices() == 0 || number_of_vertices() == 1){
            return 0;
        }
        Face* f = infinite_vertex()->face();
        int i = f->index(infinite_vertex());
        return (f->neighbor(i)->has_vertex(infinite_vertex()))
               ? 1 : 2;
    }


    int
    number_of_vertices() const
    {
        return _number_of_vertices;
    }


    int
    number_of_faces() const
    {
        return (number_of_vertices() <= 1) ? 0 : 2 * number_of_vertices() - 2;
    }


    const Traits&
    traits() const
    {
        return _traits;
    }


    bool
    is_infinite(Face *f) const
    {
        return f->has_vertex(infinite_vertex());
    }


    bool
    is_infinite(Vertex *v) const
    {
        return v == infinite_vertex();
    }


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


    CGAL_Bounded_side
    bounded_side(const Point &p0, const Point &p1,
                 const Point &p2, const Point &p) const
{
  CGAL_Orientation o1 = traits().orientation(p0, p1, p),
                   o2 = traits().orientation(p1, p2, p),
                   o3 = traits().orientation(p2, p0, p),
                   ot = traits().orientation(p0, p1, p2);

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      if ((o1 == CGAL_COLLINEAR && collinear_between(
                                                  p0, p, p1)) ||
          (o2 == CGAL_COLLINEAR && collinear_between(
                                                  p1, p, p2)) ||
          (o3 == CGAL_COLLINEAR && collinear_between(
                                                  p2, p, p0)))
        {
          return  CGAL_ON_BOUNDARY;
        }

      return CGAL_ON_UNBOUNDED_SIDE;
    }

  if (ot == CGAL_RIGHTTURN)
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return CGAL_ON_BOUNDED_SIDE;
        }
      return CGAL_ON_UNBOUNDED_SIDE;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return CGAL_ON_BOUNDED_SIDE;
    }
  return CGAL_ON_UNBOUNDED_SIDE;
}


    CGAL_Oriented_side
    oriented_side(Face *f, const Point &p) const
    {
        return oriented_side(f->vertex(0)->point(),
                             f->vertex(1)->point(),
                             f->vertex(2)->point(),
                             p);
    }


    Triangle
    triangle(Face *f) const
    {
        CGAL_kernel_precondition( ! is_infinite(f) );

        return Triangle(f->vertex(0)->point(),
                        f->vertex(1)->point(),
                        f->vertex(2)->point());
    }


    Segment
    segment(Face *f, int i) const
    {
        CGAL_kernel_precondition( (! is_infinite(f->vertex(ccw(i))))
                                  && (! is_infinite(f->vertex(cw(i)))) );

        return Segment(f->vertex(ccw(i))->point(),
                       f->vertex(cw(i))->point());
    }


    Vertex*
    finite_vertex() const
    {
        return _finite_vertex;
    }


    void
    set_finite_vertex(Vertex* v)
    {
        _finite_vertex = v;
    }


    Vertex*
    infinite_vertex() const
    {
        return _infinite_vertex;
    }


    void
    set_infinite_vertex(Vertex* v)
    {
        _infinite_vertex = v;
    }


    Face*
    infinite_face() const
    {
        Face* f = _infinite_vertex->face();
        CGAL_kernel_precondition(f->has_vertex(_infinite_vertex));
        return f;
    }


    bool
    collinear_between(const Point& p, const Point& q, const Point& r) const
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
    


    void
    insert_outside(Face *f, Vertex *vp)
    {
        int li = f->index(infinite_vertex());
    
        Face* fcw;
        Face* fccw;
        Face* ff = f;
    
        Point p = vp->point();
        f->set_vertex(li, vp);
        int i = ccw(li);
        Vertex* vq = f->vertex(i);
        Point q = vq->point();
        Face* n = f->neighbor(ccw(i));
        int ni = cw(n->index(vq)); // that works even in the 1D case
    
        bool done = false;
    
        while(! done) {
            Vertex* vr = n->vertex(ni);
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
            Vertex* vr = n->vertex(ni);
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
    


    Vertex*
    insert(const Point& p,
           Locate_type& lt,
           Face* f = NULL)
    {
        Vertex *v;
        if(number_of_vertices() <= 1) {
            v = new Vertex(p);
            lt = OUTSIDE;
            if(number_of_vertices() == 0) {
                set_finite_vertex(v);
                set_number_of_vertices(1);
            } else {
                Face* f1 = new Face(infinite_vertex(), finite_vertex(), v,
                                    NULL, NULL, NULL);
    
                Face* f2 = new Face(infinite_vertex(), v, finite_vertex(),
                                    f1, f1, f1);
    
                f1->set_neighbor(0, f2);
                f1->set_neighbor(1, f2);
                f1->set_neighbor(2, f2);
    
                infinite_vertex()->set_face(f1);
                v->set_face(f1);
                finite_vertex()->set_face(f1);
                set_number_of_vertices(2);
            }
            return v;
        }
    
        int li;
        Face *loc = locate(p, lt, li, f);
    
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
                Face *n = loc->neighbor(li);
                Vertex* w = loc->vertex(ccw(li));
                int ni = ccw(n->index(w));
                loc->insert(v);
                _number_of_vertices++;
                n->flip(ni);
                break;
            }
        case COLLINEAR_OUTSIDE:
            {
                v = new Vertex(p);
                Vertex* w = loc->vertex(li); // the extremal vertex
                Face* n = loc->neighbor(ccw(li));
                int ni = n->index(w);
                Face* f1 = new Face(infinite_vertex(), w, v,
                                    NULL, NULL, n);
                n->set_neighbor(cw(ni), f1);
                Face* f2 = new Face(infinite_vertex(), v, w,
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
            CGAL_kernel_assertion(false);  // locate step failed
        }
        return v;
    }
    


    Vertex*
    insert(const Point &p,
           Face* f = NULL)
    {
        Locate_type lt;
        return insert(p, lt, f);
    }

#ifdef CGAL_TEMPLATE_MEMBER_FUNCTIONS
    template < class InputIterator >
    int
    insert(InputIterator first, InputIterator last)
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
    int
    insert(list<Point>::const_iterator first,
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
    int
    insert(vector<Point>::const_iterator first,
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
    int
    insert(istream_iterator<Point, ptrdiff_t> first,
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


    int
    insert(Point* first,
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

   void
   remove(Vertex* v)
   {
     CGAL_kernel_precondition(v != NULL);
     CGAL_kernel_precondition( !is_infinite(v));
   
     if  (number_of_vertices() == 1) {
       // clear();
       delete v;
       set_finite_vertex(NULL);
       set_number_of_vertices(0);
       return;
     }
   
   
     // take care of finite_vertex data member
     if (finite_vertex() == v){
       Face *f = v->face();
       int i=f->index(v);
           set_finite_vertex( is_infinite(f->vertex(cw(i))) ?
                          f->vertex(ccw(i)) : f->vertex(cw(i)) );
     }
   
     if (number_of_vertices() == 2) {
       Face *f = v->face();
       delete f; delete f->neighbor(0);
     }
     else{
       if ( dimension() == 1) remove_1D(v);
       else  remove_2D(v);
     }
   
     delete v;
     set_number_of_vertices(number_of_vertices()-1);
     return;
   }
   

   void
   remove_1D(Vertex* v)
   {
    //deal with one dimensional case
     Face  *f1, *f2, *f1n, *f2n;
     int i1,i2,i1n,i2n;
   
       switch( v->degree())  {
       case 2 :
         f1= v->face(); i1= f1->index(v);
         f2= f1->neighbor(cw(i1));  i2= f2->index(v);
         f1n = f1->neighbor(i1); i1n = f1n->index(f1);
         f2n = f2->neighbor(i2); i2n = f2n->index(f2);
         f1n->set_neighbor(i1n,f2n); f2n->set_neighbor(i2n,f1n);
         delete f1; delete f2;
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
            Face *ff1 = f1->neighbor(i1);
            Face *ff2 = f2->neighbor(i2);
            f1n->set_neighbor(j1n,ff1); ff1->set_neighbor(ff1->index(f1),f1n);
            f2n->set_neighbor(j2n,ff2); ff2->set_neighbor(ff2->index(f2),f2n);
          }
          else {
            f1n->set_neighbor(j1n,f2n);
            f2n->set_neighbor(j2n,f1n);
          }
          delete f1; delete f2;
          return;
       }
    }
   

   void
   remove_2D(Vertex* v)
   {
     // General case
   
     // remove incident faces
     // set up list of faces neighboring the hole
     // in ccw order around the hole
   
     typedef pair<Face * , int>  Hole_Neighbor;
     typedef list<Hole_Neighbor> Hole;
   
     Hole hole;
     Hole::iterator hit;
   
     Face * f, *ff, * fn;
     int i =0,ii =0, in =0;
     Vertex * vv;
     Point p = v->point();
   
     Face_circulator fc = v->incident_faces();
     Face_circulator done(fc);
      do {
         f= *fc;
         i = f->index(v);
         fn = f->neighbor(i);
         vv = f->vertex(f->cw(i));
         if( vv->face()== f) vv->set_face(fn);
         vv = f->vertex(f->ccw(i));
         if( vv->face()== f) vv->set_face(fn);
         in = fn->index(f);
         fn->set_neighbor(in, NULL);
         delete f;
         hole.push_back(Hole_Neighbor(fn,in));
       }
     while(++fc != done);
   
   
     while( hole.size() != 3)
       {
          //  find the first edge  v0v1 on the hole boundary
         //  such that
         //  v0, v1 and the next vertex v2 are all finite
        //   v0v1v2 is a left turn
         //  triangle v0v1v2 does not contain the removed point
   
   
         Vertex *v0, *v1, *v2;
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
         Face * newf = new Face(v0,v1,v2);
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
           Face * newf = new Face(infinite_vertex(),fn->vertex(cw(in)),
                                                    fn->vertex(ccw(in)));
           ff->set_neighbor(ii,newf);
           fn->set_neighbor(in,newf);
           newf->set_neighbor(0,fn);
           newf->set_neighbor(2,ff);
           hole.push_front(Hole_Neighbor(newf,1));
           }
     }
   
   
         // now hole has three edges
         Face * newf = new Face();
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
   



    class Line_face_circulator {
    public:
        //typedef Vertex::Face_circulator
        //                       Face_circulator ;
        
        typedef Face *         value_type;
        typedef Face * &       reference;
        typedef const Face * & const_reference;
        typedef unsigned int   size_type;
        typedef int            difference_type;  // changed by Wieger
        
        enum State {undefined = -1,
                    vertex_vertex,
                    vertex_edge,
                    edge_vertex,
                    edge_edge};
        
        Line_face_circulator()
            : T(NULL), s(undefined), f(NULL), i(-1)
        {}
        
        Line_face_circulator(const Line_face_circulator& lfc)
            : T(lfc.T), s(lfc.s), f(lfc.f), i(lfc.i),  p(lfc.p), q(lfc.q)
        {}
        
        ~Line_face_circulator()
        {}
        
        
        Line_face_circulator(Face* face,
                             int index,
                             State state,
                             CGAL_Triangulation_2<I>* t,
                             const Point& pp,
                             const Point& qq)
            : T(t), s(state), f(face), i(index),  p(pp), q(qq)
        {
            CGAL_kernel_precondition(p != q);
        }
        
        
        Line_face_circulator&
        operator=(const Line_face_circulator& lfc)
        {
            f = lfc.f;
            i = lfc.i;
            s = lfc.s;
            T = lfc.T;
            p = lfc.p;
            q = lfc.q;
            return *this;
        }
        Line_face_circulator(Vertex* v,
                             CGAL_Triangulation_2<I>* Tr,
                             const Point& dir)
            : T(Tr)
        {
            CGAL_kernel_precondition((! T->is_infinite(v)) &&
                                     (T->dimension() == 2) &&
                                     (v->point() != dir));
        
            f = v->face();
        
            while(T->is_infinite(f)){
                i = f->index(v);
                f = f->neighbor(cw(i));
            }
            i = f->index(v);
            p = v->point();
            q = dir;
        
            Point t = f->vertex(ccw(i))->point();
            Point r = f->vertex(cw(i))->point();
        
            CGAL_Orientation ptq = T->traits().orientation(p, t, q);
            CGAL_Orientation prq = T->traits().orientation(p, r, q);
        
            if( ptq == CGAL_LEFTTURN  && prq == CGAL_RIGHTTURN ) {
                s = vertex_edge;
            } else if( (ptq == CGAL_COLLINEAR) && (prq == CGAL_RIGHTTURN) ) {
                i= ccw(i);
                s = vertex_vertex;
            } else if( (prq == CGAL_COLLINEAR) && (ptq == CGAL_LEFTTURN) ) {
                Face* n = f->neighbor(ccw(i));
                i = n->index(f->vertex(cw(i)));
                f = n;
                s = vertex_vertex;
            } else if( ptq == CGAL_LEFTTURN ) {
                do{
                    Face* n = f->neighbor(ccw(i));
                    i = n->index(f);
                    f = n;
                    if(T->is_infinite(n)){
                        s = vertex_vertex;
                        return;
                    }
                    r = n->vertex(i)->point();
                    i = ccw(i);
                }while((prq = T->traits().orientation(p, r, q)) == CGAL_LEFTTURN);
        
                if(prq == CGAL_COLLINEAR){
                    Face* n = f->neighbor(ccw(i));
                    i = cw(n->index(f));
                    f = n;
                    s = vertex_vertex;
                } else {
                    s = vertex_edge;
                }
            } else {
                do{
                    Face* n = f->neighbor(cw(i));
                    i = n->index(f);
                    f = n;
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
            Vertex* inf = T->infinite_vertex();
            Face_circulator fc = inf->incident_faces(),
                done(fc);
            i = (*fc)->index(inf);
        
            Point l = (*fc)->vertex(cw(i))->point(),
                r = (*fc)->vertex(ccw(i))->point();
        
            CGAL_Orientation pql = T->traits().orientation(p, q, l),
                pqr = T->traits().orientation(p, q, r);
        
        
            do{
                if( (pql == CGAL_LEFTTURN) && (pqr == CGAL_RIGHTTURN) ){
                    *this = ++Line_face_circulator(*fc,
                                                   i,
                                                   vertex_edge,
                                                   t,
                                                   p,
                                                   q);
                    return;
                } else if ( (pql == CGAL_LEFTTURN) && (pqr == CGAL_COLLINEAR) ){
                    *this = ++Line_face_circulator(*fc,
                                                   ccw(i),
                                                   vertex_vertex,
                                                   t,
                                                   p,
                                                   q);
                    return;
                } else if( (pql == CGAL_COLLINEAR) && (pqr == CGAL_COLLINEAR) ){
                    Face* n = (*fc)->neighbor(i);
                    int ni  = n->index(*fc);
                    Vertex* vn = n->vertex(ni);
                    if(T->traits().orientation(p, q, vn->point()) == CGAL_LEFTTURN){
                        // the entire triangulation is to the left of line (p,q).
                        // There might be further collinear edges, so we might have
                        // to walk back on the hull.
                        while(1){
                            ++fc;
                            i = (*fc)->index(inf);
                            l = (*fc)->vertex(cw(i))->point();
                            if(T->traits().orientation(p, q, l) == CGAL_COLLINEAR){
                                continue;
                            } else {
                                // we went one step to far back
                                --fc;
                                i = (*fc)->index(inf);
                                f = (*fc)->neighbor(i);
                                i = cw(f->index(*fc));
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
                    i = (*fc)->index(inf);
                    r = (*fc)->vertex(ccw(i))->point();
                    pqr = T->traits().orientation(p, q, r);
                }
            }while(fc != done);
            // if line (p,q) does not intersect the convex hull in an edge
            // the circulator has a singular value
        }
        Line_face_circulator(const Point& pp,
                             const Point& qq,
                             Face* ff,
                             CGAL_Triangulation_2<I>* t)
            : T(t), s(undefined), f(ff), p(pp), q(qq)
        {
            //CGAL_kernel_precondition(T->is_infinite(f) ||
            //                         T->oriented_side(f,p) != CGAL_ON_NEGATIVE_SIDE);
        
            int j;
            if(T->is_infinite(f)){
                *this  = Line_face_circulator(p, q, t);
                return;
            }
        
            // Test whether p lies on a vertex
            for(j = 0; j < 3; j++){
                if(f->vertex(j)->point() == p){
                    *this = Line_face_circulator(f->vertex(j), t, q);
                    return;
                }
            }
        
            // Test whether p lies on an edge
            for(j = 0; j < 3; j++){
                if(T->traits().orientation(f->vertex(j)->point(),
                                         f->vertex(ccw(j))->point(),
                                         p) == CGAL_COLLINEAR){
                    CGAL_Orientation jpq =
                        T->traits().orientation(f->vertex(j)->point(),
                                              p,
                                              q);
                    CGAL_Orientation p_cwj_q =
                        T->traits().orientation(p,
                                              f->vertex(cw(j))->point(),
                                              q);
                    switch(jpq){
                    case CGAL_COLLINEAR:
                        if(p_cwj_q == CGAL_RIGHTTURN){
                            s = vertex_vertex;
                            i = ccw(j);
                            return;
                        } else if(! T->is_infinite(f->neighbor(cw(j)))){
                            Face* n = f->neighbor(cw(j));
                            i = cw(n->index(f));
                            f = n;
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
                or[j] = T->traits().orientation(p,q,f->vertex(j)->point());
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
        Line_face_circulator&
        operator++()
        {
            CGAL_kernel_precondition(s != undefined);
            if(s == vertex_vertex || s == edge_vertex){
                CGAL_Orientation o;
                Point r;
                do{
                    Face* n = f->neighbor(cw(i));
                    i = n->index(f);
                    f = n;
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
                Face* n = f->neighbor(i);
                int ni = n->index(f);
                f = n;
                CGAL_Orientation o = T->is_infinite(f->vertex(ni)) ?
                    CGAL_COLLINEAR :
                    T->traits().orientation(p, q, f->vertex(ni)->point());
        
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
            return *this;
        }
        
        
        Line_face_circulator&
        operator--()
        {
            CGAL_kernel_precondition(s != undefined);
            if(s == vertex_vertex || s == vertex_edge){
                if(s == vertex_vertex){
                    i = cw(i);
                }
                CGAL_Orientation o;
                Point r;
                do{
                    Face* n = f->neighbor(ccw(i));
                    i = n->index(f);
                    f = n;
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
                // that index i is at the vertex that is alone on one sie of l(p,q)
                if(s == edge_edge){
                    i = (T->traits().orientation(p,
                                               q,
                                               f->vertex(i)->point()) == CGAL_LEFTTURN)
                        ? cw(i) : ccw(i);
                }
                Face* n = f->neighbor(i);
                i = n->index(f);
                f = n;
                CGAL_Orientation o = T->is_infinite(f->vertex(i)) ?
                    CGAL_COLLINEAR :
                    T->traits().orientation(p, q, f->vertex(i)->point());
        
                s = (o == CGAL_COLLINEAR) ? vertex_edge : edge_edge;
            }
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
        locate(const Point& t,
               Locate_type &lt,
               int &li)
        {
            switch(s){
            case vertex_vertex:
                {
                    if(T->is_infinite(f->vertex(i))){
                        CGAL_kernel_assertion(T->traits().orientation(
                                                            f->vertex(cw(i))->point(),
                                                            f->vertex(ccw(i))->point(),
                                                            t) != CGAL_LEFTTURN);
                        lt = OUTSIDE;
                        li = i;
                        return true;
                    }
        
                    Point u = f->vertex(cw(i))->point();
                    Point v = f->vertex(i)->point();
                    // u == t  was detected earlier
                    if(v == t){
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
            case edge_edge:
            case vertex_edge:
                {
                    CGAL_Orientation o =
                        T->traits().orientation(f->vertex(ccw(i))->point(),
                                              f->vertex(cw(i))->point(),
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
            default: // edge_vertex
                {
                    if(T->is_infinite(f->vertex(i))){
                        lt = OUTSIDE;
                        li = i;
                        return true;
                    }
                    if(t == f->vertex(i)->point()){
                        li = i;
                        lt = VERTEX;
                        return true;
                    }
                    if(T->collinear_between(p, t, f->vertex(i)->point())){
                        lt = FACE;
                        return true;
                    }
                    return false;
                }
            }
        }
        Face*
        operator*() const
        {
            return f;
        }
        
        
        bool
        operator==(const Line_face_circulator& lfc) const
        {
            CGAL_kernel_precondition( f != NULL  &&  lfc.f != NULL );
            return f == lfc.f;
        }
        
        bool
        operator!=(const Line_face_circulator& lfc) const
        {
            CGAL_kernel_precondition( f != NULL  &&  lfc.f != NULL );
            return f != lfc.f;
        }
        
        
        bool
        operator==(CGAL_NULL_TYPE n) const
        {
            CGAL_kernel_assertion( n == NULL);
            return s == undefined;
        }
        
        bool
        operator!=(CGAL_NULL_TYPE n) const
        {
            CGAL_kernel_assertion( n == NULL);
            return s != undefined;
        }

    private:
        CGAL_Triangulation_2<I>* T;
        State s;
        Face *f;
        int i;
        Point p, q;
        
    };

    Face*
    march_locate_1D(const Point& t,
                    Locate_type& lt,
                    int& li) const
    
    {
        Face* f = infinite_face();
        int i = f->index(infinite_vertex());
        Point p = f->vertex(ccw(i))->point();
        Point q = f->vertex(cw(i))->point();
        CGAL_Orientation pqt = traits().orientation(p, q, t);
        if(pqt == CGAL_RIGHTTURN){
            lt = OUTSIDE;
            return f->neighbor(i);
        }
        if(pqt == CGAL_LEFTTURN){
            lt = OUTSIDE;
            return f;
        }
        Vertex* vi = infinite_vertex();
        Face_circulator fc = vi->incident_faces();
        f = *fc;
        i = f->index(vi);
        Vertex* u = f->vertex(ccw(i));
        Vertex* v = f->vertex(cw(i));
        Vertex* w;
    
        while(1){
            if(t == v->point()){
                lt = VERTEX;
                li = cw(i);
                return f;
            }
            if(collinear_between(u->point(), t, v->point())){
                lt = EDGE;
                li = i;
                return f;
            }
            ++fc;
            f = *fc;
            i = f->index(vi);
            w = f->vertex(cw(i));
            if( (u == w) && collinear_between(u->point(), v->point(), t)){
                lt = COLLINEAR_OUTSIDE;
                li = ccw(i);
                return f;
            }
            u = v;
            v = w;
        }
    }
    


    Face*
    march_locate_2D(Face *start,
                    const Point& t,
                    Locate_type& lt,
                    int& li) const
    {
        CGAL_kernel_precondition( ! is_infinite(start) );
        CGAL_Triangulation_2<I> *ncthis = (CGAL_Triangulation_2<I>*)this;
    
        Point p = start->vertex(0)->point();
    
        if(p == t){
            lt = VERTEX;
            li = 0;
            return start;
        }
        Line_face_circulator lfc(start->vertex(0),
                                 ncthis,
                                 t);
    
        while(! lfc.locate(t, lt, li) ){
            ++lfc;
        }
        return *lfc;
    }
    


    Face*
    locate(const Point& p,
           Locate_type& lt,
           int& li,
           Face* start = NULL) const
    {
        if(number_of_vertices() == 0) {
            lt = OUTSIDE;
            return NULL;
        }
        if(number_of_vertices() == 1) {
            lt = (p == finite_vertex()->point()) ? VERTEX : OUTSIDE;
            return NULL;
        }
    
        if(dimension() == 1){
            return march_locate_1D(p, lt, li);
        }
    
        if(start == NULL){
            start = infinite_face();
        }
    
        if(is_infinite(start)){
            int i = start->index(infinite_vertex());
            start = start->neighbor(i);
        }
    
        return march_locate_2D(start, p, lt, li);
    }
    


    Face*
    locate(const Point &p,
           Face* start = NULL) const
    {
        Locate_type lt;
        int li;
        return locate(p, lt, li, start);
    }
    



    Face_iterator
    faces_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I> *)this;
        return Face_iterator(ncthis);
    }


    Face_iterator
    faces_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I> *)this;
        return Face_iterator(ncthis, 1);
    }



    Vertex_iterator
    vertices_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Vertex_iterator(ncthis);
    }


    Vertex_iterator
    vertices_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Vertex_iterator(ncthis,1);
    }



    Edge_iterator
    edges_begin() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Edge_iterator(ncthis);
    }


    Edge_iterator
    edges_end() const
    {
        CGAL_Triangulation_2<I>* ncthis = (CGAL_Triangulation_2<I>*)this;
        return Edge_iterator(ncthis,1);
    }


    Segment
    segment(const Edge_iterator& ei) const
    {
        pair<Face*, int> edge = *ei;
        return Segment(edge.first->vertex(cw(edge.second))->point(),
                       edge.first->vertex(ccw(edge.second))->point());
    }



    Convex_hull_vertex_circulator
    convex_hull() const
    {
        if(number_of_vertices() == 1){
            return Convex_hull_vertex_circulator(NULL, finite_vertex());
        }
    
        Face* f = infinite_face();
        int i = f->index(infinite_vertex());
        Vertex* v = f->vertex(ccw(i));
        return Convex_hull_vertex_circulator(f, v);
    }
    

    Line_face_circulator
    line_walk(const Point& p,
              const Point& q,
              Face* f = NULL)
    {
        CGAL_kernel_precondition( (dimension() == 2) && (p != q) );
    
        Line_face_circulator lfc = (f == NULL)
                                   ? Line_face_circulator(p, q, this)
                                   : Line_face_circulator(p, q, f, this);
    
        if((! (lfc == NULL)) && is_infinite(*lfc)){
            return Line_face_circulator();
        }
        return lfc;
    }
    


    bool
    is_valid(bool verbose = false, int level = 0) const
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
    
        CGAL_kernel_assertion( number_of_vertices() == vertex_count );
    
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
                result = result && (*it)->is_valid(verbose, level);
                CGAL_kernel_assertion( (*it)->is_valid(verbose, level) );
                result = result && (! is_infinite(*it));
                CGAL_kernel_assertion( ! is_infinite(*it) );
                CGAL_Orientation s = traits().orientation((*it)->vertex(0)->point(),
                                                        (*it)->vertex(1)->point(),
                                                        (*it)->vertex(2)->point());
                result = result && ( s == CGAL_LEFTTURN );
                CGAL_kernel_assertion( s == CGAL_LEFTTURN );
                ++it;
            }
        }
    
    
        Face_circulator fc = infinite_vertex()->incident_faces(),
            fcdone(fc);
        do{
            if(dimension() == 2){
                result = result && (*fc)->is_valid(verbose, level);
                CGAL_kernel_assertion( (*fc)->is_valid(verbose, level) );
            }
            ++face_count;
            ++edge_count;
        }while(++fc != fcdone);
    
    
        Convex_hull_vertex_circulator start = convex_hull(),
            pc(start),
            qc(start),
            rc(start);
        ++qc;
        ++rc;
        ++rc;
        do{
            bool extremal = ( traits().extremal((*pc)->point(),
                                              (*qc)->point(),
                                              (*rc)->point()) != CGAL_POSITIVE);
            result = result && extremal;
            CGAL_kernel_assertion( extremal );
            pc = qc;
            qc = rc;
            ++rc;
        }while(pc != start);
        result = result && ( edge_count == 3* (vertex_count -1) );
        CGAL_kernel_assertion( edge_count == 3* (vertex_count -1) );
        result = result && ( face_count == 2* (vertex_count -1) );
        CGAL_kernel_assertion( face_count == 2* (vertex_count -1) );
    
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
CGAL_Triangulation_2<I>::~CGAL_Triangulation_2()
{
    clear();
    delete infinite_vertex();
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


    copy(vertices_begin(), vertices_end(), back_inserter(Vertices));

    copy(faces_begin(), faces_end(), back_inserter(Faces));

    {
        Face_circulator fc = infinite_vertex()->incident_faces(),
            done(fc);
        do{
            Faces.push_front(*fc);
        }while(++fc != done);
    }
//    assert( number_of_faces() == Faces.size()); line removed by Wieger
    for_each(Faces.begin(),Faces.end(), CGAL_Delete<Face>());

    for_each(Vertices.begin(), Vertices.end(), CGAL_Delete<Vertex>());


    infinite_vertex()->set_face(NULL);
    set_finite_vertex(NULL);
    set_number_of_vertices(0);
}
/*
template < class I >
CGAL_Triangulation_2<I>::Convex_hull_vertex_circulator
CGAL_Triangulation_2<I>::convex_hull() const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Line_face_circulator
CGAL_Triangulation_2<I>::line_walk(const CGAL_Triangulation_2<I>::Point& p,
                                   const CGAL_Triangulation_2<I>::Point& q,
                                   Face* f = NULL) const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Vertex *
CGAL_Triangulation_2<I>::insert(const CGAL_Triangulation_2<I>::Point &p,
                                CGAL_Triangulation_2<I>::Face* f)
{
  Locate_type lt;
  int li;
  return insert(p, lt, f);
}

*/
/*
template < class I >
CGAL_Triangulation_2<I>::Vertex*
CGAL_Triangulation_2<I>::insert(const CGAL_Triangulation_2<I>::Point &p,
                                CGAL_Triangulation_2<I>::Locate_type& lt,
                                CGAL_Triangulation_2<I>::Face* f)
*/
/*
template < class I >
void
CGAL_Triangulation_2<I>::insert_outside
                               (CGAL_Triangulation_2<I>::Face *f,
                                CGAL_Triangulation_2<I>::Vertex *vp)
*/
/*
template < class I >
void
CGAL_Triangulation_2<I>::remove(CGAL_Triangulation_2<I>::Vertex* v)
*/
/*
template < class I >
void
CGAL_Triangulation_2<I>::remove_1D(CGAL_Triangulation_2<I>::Vertex* v)
*/
/*
template < class I >
void
CGAL_Triangulation_2<I>::remove_2D(CGAL_Triangulation_2<I>::Vertex* v)
*/
/*
template < class I >
bool
CGAL_Triangulation_2<I>::is_valid(bool verbose, int level) const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Face*
CGAL_Triangulation_2<I>::locate(const CGAL_Triangulation_2<I>::Point &p,
                                CGAL_Triangulation_2<I>::Face* f) const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Face*
CGAL_Triangulation_2<I>::locate(const CGAL_Triangulation_2<I>::Point &p,
                                CGAL_Triangulation_2<I>::Locate_type &lt,
                                int &li,
                                Face* start) const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Face*
CGAL_Triangulation_2<I>::march_locate_2D(
                       CGAL_Triangulation_2<I>::Face *start,
                       const CGAL_Triangulation_2<I>::Point & t,
                       CGAL_Triangulation_2<I>::Locate_type& lt,
                       int &li) const
*/
/*
template < class I >
CGAL_Triangulation_2<I>::Face*
CGAL_Triangulation_2<I>::march_locate_1D(
                       const CGAL_Triangulation_2<I>::Point& t,
                       CGAL_Triangulation_2<I>::Locate_type& lt,
                       int &li) const
*/
/*
template < class I >
bool
CGAL_Triangulation_2<I>::collinear_between(
                                 const CGAL_Triangulation_2<I>::Point& p,
                                 const CGAL_Triangulation_2<I>::Point& q,
                                 const CGAL_Triangulation_2<I>::Point& r) const
*/


template < class I >
ostream&
operator<<(ostream& os, const CGAL_Triangulation_2<I> &T)
{
    map< void*, int, less<void*> > V;
    map< void*, int, less<void*> > F;
    CGAL_Triangulation_2<I>::Vertex* v;
    CGAL_Triangulation_2<I>::Face* f;

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
    V[v] = i;
    os << v->point();
    if(CGAL_is_ascii(os)){
        os << ' ';
    }
    if(n == 1){
        return os;
    }

    // write the finite vertices
    {
        CGAL_Triangulation_2<I>::Vertex_iterator it = T.vertices_begin();

        while(it != T.vertices_end()){
            V[*it] = ++i;
            os << (*it)->point();
            if(CGAL_is_ascii(os)){
                os << ' ';
            }
            ++it;
        }
    }
    CGAL_kernel_assertion( (i+1) == n );

    if(n == 2){
        return os;
    }

    i = 0;
    // vertices of the finite faces
    {
        CGAL_Triangulation_2<I>::Face_iterator it = T.faces_begin();

        while(it != T.faces_end()){
            f = *it;
            F[f] = i++;
            for(int j = 0; j < 3; j++){
                os << V[f->vertex(j)];
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
        CGAL_Triangulation_2<I>::Face_circulator
            fc = T.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            f = *fc;
            F[f] = i++;
            for(int j = 0; j < 3; j++){
                os << V[f->vertex(j)];
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
    CGAL_kernel_assertion( i == m );

    // neighbor pointers of the finite faces
    {
        CGAL_Triangulation_2<I>::Face_iterator
            it = T.faces_begin();
        while(it != T.faces_end()){
            for(int j = 0; j < 3; j++){
                os << F[(*it)->neighbor(j)];
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
        CGAL_Triangulation_2<I>::Face_circulator
            fc = T.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            for(int j = 0; j < 3; j++){
                os << F[(*fc)->neighbor(j)];
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
    CGAL_Triangulation_2<I>::Vertex* v;
    CGAL_Triangulation_2<I>::Face* f;

    if(T.number_of_vertices() != 0){
        T.clear();
    }

    int i = 0;
    int n, m, d;
    is >> n >> m >> d;

    T.set_number_of_vertices(n-1);

    vector<CGAL_Triangulation_2<I>::Vertex*> V(n);
    vector<CGAL_Triangulation_2<I>::Face*> F(m);

    // the first point is at infinity

    I::Point p;
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
        I::Point p;
        is >> p;
        V[i] = new Vertex(p);
    }

    T.set_finite_vertex(V[i-1]);

    if(n == 2){
        return is;
    }
    // Creation of the faces
    for(i = 0; i < m; i++) {
        int i0, i1, i2;
        is >> i0 >> i1 >> i2;
        f = new Face(V[i0], V[i1], V[i2]);
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
