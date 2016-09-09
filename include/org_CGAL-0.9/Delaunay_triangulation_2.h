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


#ifndef CGAL_DELAUNAY_2_H
#define CGAL_DELAUNAY_2_H

#include <CGAL/Triangulation_2.h>

template < class I>
class CGAL_Delaunay_triangulation_2 : public CGAL_Triangulation_2<I>
{
public:
  typedef I::Distance Distance;

  CGAL_Delaunay_triangulation_2()
  : CGAL_Triangulation_2<I>()
  {}
  
  CGAL_Delaunay_triangulation_2(I& i)
  : CGAL_Triangulation_2<I>(i)
  {}
  
  
  CGAL_Delaunay_triangulation_2(Vertex* v)
      : CGAL_Triangulation_2<I>(v)
  {
      CGAL_kernel_postcondition( is_valid() );
  }
  
  
  
  CGAL_Delaunay_triangulation_2(Vertex* v,
                                 I& i)
      : CGAL_Triangulation_2<I>(v, i)
  {
      CGAL_kernel_postcondition( is_valid() );
  }
  
  #ifdef CGAL_TEMPLATE_MEMBER_FUNCTIONS
  template < class InputIterator >
  int
  insert(InputIterator first, InputIterator last)
  {
    int n = number_of_vertices();
    while(first != last){
        T.insert(*first);
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
  CGAL_Oriented_side
  side_of_oriented_circle(Face* f, const Point & p) const
  {
      CGAL_Orientation o;
      if ( ! is_infinite(f) ) {
          return traits().side_of_oriented_circle(f->vertex(0)->point(),
                                                  f->vertex(1)->point(),
                                                  f->vertex(2)->point(),p);
      } else if ( f->vertex(0) == infinite_vertex() ) {
          o = traits().extremal(f->vertex(1)->point(),
                                f->vertex(2)->point(),p);
      } else if ( f->vertex(1) == infinite_vertex() ) {
          o = traits().extremal(f->vertex(2)->point(),
                                f->vertex(0)->point(),p);
      } else if ( f->vertex(2) == infinite_vertex() ) {
          o = traits().extremal(f->vertex(0)->point(),
                                f->vertex(1)->point(),p);
      }
      return (o == CGAL_NEGATIVE) ? CGAL_ON_NEGATIVE_SIDE :
          (o == CGAL_POSITIVE) ? CGAL_ON_POSITIVE_SIDE :
          CGAL_ON_ORIENTED_BOUNDARY;
  }
  Vertex *
  nearest_vertex(const Point& p, Face* f) const
  {
      Vertex *nn;
      Distance closer(p,&traits());
      int min;
      int i;
  
      i = ( ! is_infinite(f->vertex(0)) ) ? 0 : 1;
  
      closer.set_point(1,f->vertex(i)->point());
      min = 1;
      nn = f->vertex(i);
      if ( ! is_infinite(f->vertex(ccw(i)))){
          closer.set_point( 3-min, f->vertex(ccw(i))->point() );
          if (  ( (min==1)? CGAL_LARGER : CGAL_SMALLER )
                == closer.compare() ) {
              min = 3-min;
              nn=f->vertex(ccw(i));
          }
      }
      if ( ! is_infinite(f->vertex(cw(i)))){
          closer.set_point( 3-min, f->vertex(cw(i))->point() );
          if (  ( (min==1)? CGAL_LARGER : CGAL_SMALLER )
                == closer.compare() ) {
              min = 3-min;
              nn=f->vertex(cw(i));
          }
      }
      look_nearest_neighbor(p,f,0,min,nn,closer);
      look_nearest_neighbor(p,f,1,min,nn,closer);
      look_nearest_neighbor(p,f,2,min,nn,closer);
      return nn;
  }
  
  Vertex *
  nearest_vertex(const Point  &p) const
  {
      Face *f = locate(p);
      return nearest_vertex(p, f);
  }
  Vertex *
  insert(const Point  &p,
         Face* f = NULL)
  {
      Locate_type lt;
      return insert(p,lt,f);
  }
  
  Vertex *
  insert(const Point  &p,
         CGAL_Triangulation_2<I>::Locate_type& lt,
         Face* f = NULL)
  {
      Vertex * v;
      if(dimension() <= 1) {
          return CGAL_Triangulation_2<I>::insert(p,lt,f);
      }
      int li;
      Face *loc = locate(p, lt, li, f);
  
      switch(lt){
      case OUTSIDE:
          {
              Face_circulator circ=infinite_vertex()->incident_faces(loc),
                  done(circ);
              do{
                  if ( side_of_oriented_circle(*circ,p)==CGAL_ON_POSITIVE_SIDE ){
                      break;
                  }
              }while(++circ != done);
              loc=*circ;
          }
      case FACE:
          {
              v = new Vertex(p);
              loc->insert(v);
              set_number_of_vertices(number_of_vertices()+1);
              break;
          }
      case EDGE:
          {
              v = new Vertex(p);
              Face *n = loc->neighbor(li);
              Vertex* w = loc->vertex(ccw(li));
              int ni = ccw(n->index(w));
              loc->insert(v);
              set_number_of_vertices(number_of_vertices()+1);
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
              set_number_of_vertices(number_of_vertices()+1);
              return v;
          }
      case VERTEX:
          return loc->vertex(li);
      default:
          CGAL_kernel_assertion(false);  // locate step failed
      }
  
      f=v->face();
      Face *next;
      int i;
      Face *start(f);
      do {
          i = f->index(v);
          next = f->neighbor(ccw(i));  // turn ccw around v
          flip(f,i);
          f=next;
      } while(next != start);
      return v;
  }
   void  remove(Vertex*& v )
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
  
  
  
  
     //  take care of finite_vertex data member
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
   void remove_1D(Vertex*& v )
   {
    // deal with one dimensional case
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
          //  j1 is the other finite vertex of f1
          //  3-i1-j1 is the index of the infinite_vertex in face f1
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
   void remove_2D(Vertex*& v )
  {
    // General case
  
    // remove incident faces
    // set up list of faces neighboring the hole
    // in ccw order around the hole
  
    typedef pair<Face * , int>  Hole_Neighbor;
    typedef list<Hole_Neighbor> Hole;
    typedef list<Hole> Hole_list;
  
    Hole hole;
    Hole_list hole_list;
  
    Face * f, *ff, * fn;
    int i =0,ii =0, in =0;
    Vertex * vv;
  
  
  
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
  
    hole_list.push_front(hole);
  
    while( ! hole_list.empty())
      {
        hole = hole_list.front();
        hole_list.pop_front();
        Hole::iterator hit = hole.begin();
  
        // if the hole has only three edges, create the triangle
          if (hole.size() == 3) {
          Face * newf = new Face();
          hit = hole.begin();
          for(int j = 0;j<3;j++){
            ff = (*hit).first;
            ii = (*hit).second;
            hit++;
            ff->set_neighbor(ii,newf);
            newf->set_neighbor(j,ff);
            newf->set_vertex(newf->ccw(j),ff->vertex(ff->cw(ii)));
  
          }
          continue;
        }
  
        // else find an edge with two finite vertices
        // on the hole boundary
        // and the new triangle adjacent to that edge
       //  cut the hole and push it back
  
          // first, ensure that a neighboring face
          // whose vertices on the hole boundary are finite
          // is the first of the hole
       bool finite= false;
       while (!finite){
          ff = (hole.front()).first;
          ii = (hole.front()).second;
          if ( is_infinite(ff->vertex(cw(ii))) ||
               is_infinite(ff->vertex(ccw(ii)))) {
          hole.push_back(hole.front());
          hole.pop_front();
          }
          else finite=true;
        }
  
        // take the first neighboring face and pop it;
        ff = (hole.front()).first;
        ii =(hole.front()).second;
        hole.pop_front();
  
  
        Vertex * v0 = ff->vertex(ff->cw(ii)); Point p0 =v0->point();
        Vertex * v1 = ff->vertex(ff->ccw(ii)); Point p1 =v1->point();
        Vertex * v2 = infinite_vertex(); Point p2;
        Vertex * vv; Point p;
  
        Hole::iterator hdone = hole.end();
        hit =  hole.begin();
        Hole::iterator cut_after(hit);
  
        // if tested vertex is c with respect to the vertex opposite
        // to NULL neighbor,
        // stop at the before last face;
        hdone--;
        while( hit != hdone) {
          fn = (*hit).first;
          in = (*hit).second;
          vv = fn->vertex(ccw(in));
          if (is_infinite(vv)) {
            if(is_infinite(v2)) cut_after = hit;
          }
          else {     // vv is a finite vertex
            p = vv->point();
            if (  traits().orientation(p0,p1,p) == CGAL_COUNTERCLOCKWISE) {
              if(is_infinite(v2)) { v2=vv; p2=p; cut_after=hit;}
              else{
                if( traits().side_of_oriented_circle (p0,p1,p2,p) ==
                    CGAL_ON_POSITIVE_SIDE){
               v2=vv; p2=p; cut_after=hit;}
              }
            }
          }
          ++hit;
        }
  
  
        // create new triangle and update adjacency relations
        Face * newf = new Face(v0,v1,v2);
        newf->set_neighbor(2,ff);
        ff->set_neighbor(ii, newf);
  
  
        //update the hole and push back in the Hole_List stack
        // if v2 belongs to the neighbor following or preceding *f
        // the hole remain a single hole
        // otherwise it is split in two holes
  
        fn = (hole.front()).first;
        in = (hole.front()).second;
        if (fn->has_vertex(v2, i) && i == fn->ccw(in)) {
          newf->set_neighbor(0,fn);
          fn->set_neighbor(in,newf);
          hole.pop_front();
          hole.push_front(Hole_Neighbor(newf,1));
          hole_list.push_front(hole);
        }
        else{
          fn = (hole.back()).first;
          in = (hole.back()).second;
          if (fn->has_vertex(v2, i) && i== fn->cw(in)) {
            newf->set_neighbor(1,fn);
            fn->set_neighbor(in,newf);
            hole.pop_back();
            hole.push_back(Hole_Neighbor(newf,0));
            hole_list.push_front(hole);
          }
          else{
            // split the hole in two holes
            Hole new_hole;
            ++cut_after;
            while( hole.begin() != cut_after )
            {
              new_hole.push_back(hole.front());
              hole.pop_front();
            }
  
            hole.push_front(Hole_Neighbor(newf,1));
            new_hole.push_front(Hole_Neighbor(newf,0));
            hole_list.push_front(hole);
            hole_list.push_front(new_hole);
          }
        }
      }
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
          Vertex_iterator it = vertices_begin(),
                          done = vertices_end();
  
          while(it != done){
              ++vertex_count;
              ++it;
          }
      }
      result = result && (number_of_vertices() == vertex_count);
      CGAL_kernel_assertion( result );
  
      int edge_count = 0;
      {
          Edge_iterator it = edges_begin(),
                        done = edges_end();
  
          while(it != done){
              ++edge_count;
              ++it;
          }
      }
  
      int face_count = 0;
      {
          Face_iterator it = faces_begin(),
                        done = faces_end();
  
          while(it != done){
              ++face_count;
              result = result && (*it)->is_valid(verbose, level);
              CGAL_kernel_assertion( result );
              result = result && (! is_infinite(*it));
              CGAL_kernel_assertion( result );
              if ( ! is_infinite((*it)->neighbor(0)) ){
                  result = result &&
                      (CGAL_ON_POSITIVE_SIDE !=
                        side_of_oriented_circle(*it,(*it)->neighbor(0)->
                              vertex((*it)->neighbor(0)->index(*it))->point()));
              }
              if ( ! is_infinite((*it)->neighbor(1)) ){
                  result = result && (CGAL_ON_POSITIVE_SIDE !=
                        side_of_oriented_circle(*it,(*it)->neighbor(1)->
                              vertex((*it)->neighbor(1)->index(*it))->point()));
              }
              if ( ! is_infinite((*it)->neighbor(2)) ){
                  result = result && (CGAL_ON_POSITIVE_SIDE !=
                        side_of_oriented_circle(*it,(*it)->neighbor(2)->
                              vertex((*it)->neighbor(2)->index(*it))->point()));
              }
              CGAL_kernel_assertion( result );
              ++it;
          }
      }
  
      Face_circulator fc = infinite_vertex()->incident_faces(),
                      fcdone(fc);
      do{
          if(dimension() == 2){
              result = result && (*fc)->is_valid(verbose, level);
              CGAL_kernel_assertion( result );
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
          CGAL_kernel_assertion( result );
          pc = qc;
          qc = rc;
          ++rc;
      }while(pc != start);
      result = result && ( edge_count == 3* (vertex_count -1) );
      CGAL_kernel_assertion( result );
      result = result && ( face_count == 2* (vertex_count -1) );
      CGAL_kernel_assertion( result );
  
      return result;
  }
  
private:
  void
  look_nearest_neighbor(const Point& p,
                        Face* f,
                        int i,
                        int& min,
                        Vertex*& nn,
                        Distance& closer)const
  {
      Face * ni=f->neighbor(i);
      if ( CGAL_ON_POSITIVE_SIDE != side_of_oriented_circle(ni,p) ) {
          return;
      }
      i = ni->index(f);
      if ( ! is_infinite(ni->vertex(i))){
          closer.set_point( 3-min, ni->vertex(i)->point() );
          if (  ( (min==1)? CGAL_LARGER : CGAL_SMALLER )
                == closer.compare() ) {
              min = 3-min;
              nn=ni->vertex(i);
          }
      }
      // recursive exploration of triangles whose circumcircle contains p
      look_nearest_neighbor(p, ni, ccw(i), min, nn, closer);
      look_nearest_neighbor(p, ni, cw(i),  min, nn, closer);
  }
  void
  flip(Face* f,int i)
  {
      Face *ni = f->neighbor(i);
      if ( CGAL_ON_POSITIVE_SIDE != side_of_oriented_circle(ni,
                                                      f->vertex(i)->point()) ) {
          return;
      }
      f->flip(i);
      flip(f,i);
      i = ni->index(f->vertex(i));
      flip(ni,i);
  }
  
};


template < class I >
ostream&
operator<<(ostream& os, const CGAL_Delaunay_triangulation_2<I> &DT)
{
  return os << (const CGAL_Triangulation_2<I>&)DT;
}



#endif // CGAL_DELAUNAY_2_H
