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
// file          : include/CGAL/Delaunay_triangulation_2.h
// package       : Triangulation (1.23)
// source        : web/Delaunay_triangulation_2.fw
// revision      : $Revision: 1.17 $
// revision_date : $Date: 1998/04/24 14:23:37 $
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


#ifndef CGAL_DELAUNAY_TRIANGULATION_2_H
#define CGAL_DELAUNAY_TRIANGULATION_2_H

#include <CGAL/Triangulation_2.h>

template < class I>
class CGAL_Delaunay_triangulation_2 : public CGAL_Triangulation_2<I>
{
friend istream& operator>> CGAL_NULL_TMPL_ARGS
                (istream& is, CGAL_Delaunay_triangulation_2<I> &T);
public:
  typedef typename I::Line                      Line;
  typedef typename I::Direction                 Direction;
  typedef typename I::Ray                       Ray;
  typedef typename I::Distance Distance;

  CGAL_Delaunay_triangulation_2()
  : CGAL_Triangulation_2<I>() {}
  
  CGAL_Delaunay_triangulation_2(I& i)
  : CGAL_Triangulation_2<I>(i) {}
  
  
  CGAL_Delaunay_triangulation_2(const Vertex_handle& v)
    : CGAL_Triangulation_2<I>(v)
  {   CGAL_triangulation_postcondition( is_valid() );  }
  
  
  
  CGAL_Delaunay_triangulation_2(const Vertex_handle& v,
                                 I& i)
      : CGAL_Triangulation_2<I>(v, i)
  {   CGAL_triangulation_postcondition( is_valid() );  }
  
  #ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
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
  CGAL_Oriented_side
  side_of_oriented_circle(const Face_handle& f, const Point & p) const
  {
      CGAL_Orientation o;
      if ( ! is_infinite(f) ) {
          return traits().side_of_oriented_circle(f->vertex(0)->point(),
                                                  f->vertex(1)->point(),
                                                  f->vertex(2)->point(),p);
      } else if ( f->vertex(0) == infinite_vertex() ) {
          o = traits().orientation(f->vertex(1)->point(),
                                f->vertex(2)->point(),p);
      } else if ( f->vertex(1) == infinite_vertex() ) {
          o = traits().orientation(f->vertex(2)->point(),
                                f->vertex(0)->point(),p);
      } else if ( f->vertex(2) == infinite_vertex() ) {
          o = traits().orientation(f->vertex(0)->point(),
                                f->vertex(1)->point(),p);
      }
      return (o == CGAL_NEGATIVE) ? CGAL_ON_NEGATIVE_SIDE :
          (o == CGAL_POSITIVE) ? CGAL_ON_POSITIVE_SIDE :
          CGAL_ON_ORIENTED_BOUNDARY;
  }
  Vertex_handle
  nearest_vertex(const Point& p, const Face_handle& f) const
  {
      Vertex_handle nn;
      Distance closer(p,&traits());
      int min;
      int i;
  
      if (number_of_vertices() == 0) return NULL;
      if (number_of_vertices() == 1) return finite_vertex();
  
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
  
  inline Vertex_handle
  nearest_vertex(const Point  &p) const
  {
      Face_handle f = locate(p);
      return nearest_vertex(p, f);
  }
  Vertex_handle
  insert(const Point  &p,
         Face_handle f = Face_handle() )
  {
      Locate_type lt;
      return insert(p,lt,f);
  }
  
  Vertex_handle
  push_back(const Point &p)
  {
      Locate_type lt;
      return insert(p, lt, NULL);
  }
  
  Vertex_handle
  insert(const Point  &p,
         CGAL_Triangulation_2<I>::Locate_type& lt,
         Face_handle f = Face_handle() )
  {
      Vertex_handle v;
      if(dimension() <= 1) {
          return CGAL_Triangulation_2<I>::insert(p,lt,f);
      }
      int li;
      Face_handle loc = locate(p, lt, li, f);
  
      switch(lt){
      case OUTSIDE:
          {
              Face_circulator circ=infinite_vertex()->incident_faces(loc),
                  done(circ);
              do{
                if(side_of_oriented_circle( circ ,p)
                                         ==CGAL_ON_POSITIVE_SIDE){
                      break;
                }
              }while(++circ != done);
              loc= circ ;
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
              Face_handle n = loc->neighbor(li);
              Vertex_handle w = loc->vertex(ccw(li));
              int ni = ccw(n->index(w));
              loc->insert(v);
              set_number_of_vertices(number_of_vertices()+1);
              flip(n, ni);
              break;
          }
      case COLLINEAR_OUTSIDE:
          {
              v = new Vertex(p);
              Vertex_handle w = loc->vertex(li); // the extremal vertex
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
              set_number_of_vertices(number_of_vertices()+1);
              return v;
          }
      case VERTEX:
          return loc->vertex(li);
      default:
          CGAL_triangulation_assertion(false);  // locate step failed
      }
  
      f=v->face();
      Face_handle next;
      int i;
      Face_handle start(f);
      do {
          i = f->index(v);
          next = f->neighbor(ccw(i));  // turn ccw around v
          propagating_flip(f,i);
          f=next;
      } while(next != start);
      return v;
  }
  void  remove(Vertex_handle& v )
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
  
  
  
  
     //  take care of finite_vertex data member
     if (finite_vertex() == v){
       Face_handle f = v->face();
       int i=f->index(v);
       Vertex_handle vv= is_infinite(f->vertex(cw(i))) ?
                          f->vertex(ccw(i)) : f->vertex(cw(i));
       set_finite_vertex( vv);
     }
  
     if (number_of_vertices() == 2) {
      Face_handle f = v->face();
      Face_handle ff = f->neighbor(0);
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
  bool is_valid(bool verbose = false, int level = 0) const
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
      CGAL_triangulation_assertion( result );
  
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
              result = result && it->is_valid(verbose, level);
              CGAL_triangulation_assertion( result );
              result = result && (! is_infinite( it ));
              CGAL_triangulation_assertion( result );
              if ( ! is_infinite( it->neighbor(0)) ){
                  result = result &&
                      (CGAL_ON_POSITIVE_SIDE !=
                       side_of_oriented_circle( it, it->neighbor(0)->
                        vertex(it->neighbor(0)->index( it ))->point()));
              }
              if ( ! is_infinite(it->neighbor(1)) ){
                  result = result && (CGAL_ON_POSITIVE_SIDE !=
                    side_of_oriented_circle( it, it->neighbor(1)->
                        vertex(it->neighbor(1)->index( it ))->point()));
              }
              if ( ! is_infinite(it->neighbor(2)) ){
                  result = result && (CGAL_ON_POSITIVE_SIDE !=
                      side_of_oriented_circle( it, it->neighbor(2)->
                         vertex(it->neighbor(2)->index( it))->point()));
              }
              CGAL_triangulation_assertion( result );
              ++it;
          }
      }
  
      Face_circulator fc = infinite_vertex()->incident_faces(),
                      fcdone(fc);
      do{
          if(dimension() == 2){
              result = result && fc->is_valid(verbose, level);
              CGAL_triangulation_assertion( result );
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
          bool extremal = ( traits().orientation(pc->point(),
                                              qc->point(),
                                              rc->point()) != CGAL_POSITIVE);
          result = result && extremal;
          CGAL_triangulation_assertion( result );
          pc = qc;
          qc = rc;
          ++rc;
      }while(pc != start);
      result = result && ( edge_count == 3* (vertex_count -1) );
      CGAL_triangulation_assertion( result );
      result = result && ( face_count == 2* (vertex_count -1) );
      CGAL_triangulation_assertion( result );
  
      return result;
  }
  Point dual(const Face_handle &f) const
  {
    return traits().circumcenter(f->vertex(0)->point(),
                   f->vertex(1)->point(),
                   f->vertex(2)->point());
  }
  
  CGAL_Object dual(const Edge &e) const
  {
    if (! is_infinite(e.first) && ! is_infinite(e.first->neighbor(e.second))) {
      Segment s(dual(e.first),dual(e.first->neighbor(e.second)));
      return CGAL_Object(new CGAL_Wrapper< Segment >(s));
    } else {
      Face_handle f; int i;
      if (is_infinite(e.first)) {
        f=e.first->neighbor(e.second); f->has_neighbor(e.first,i);
      } else {
        f=e.first; i=e.second;
      }
      if (! is_infinite(f)) {
        Ray r(dual(f), segment(f,i).direction().perpendicular(CGAL_NEGATIVE));
        return CGAL_Object(new CGAL_Wrapper< Ray >(r));
      } else {
        Segment s(segment(f,i));
        Point p = s.source() + (s.target() - s.source()) / 2.0;
        Line l(segment(f,i));
        return CGAL_Object(new CGAL_Wrapper< Line >(l.perpendicular(p)));
      }
    }
  }
  
  CGAL_Object dual(const Edge_circulator& ec) const
  {
      return dual(*ec);
  }
  
  CGAL_Object dual(const Edge_iterator& ei) const
  {
      return dual(*ei);
  }
  
private:
  void
  look_nearest_neighbor(const Point& p,
                        const Face_handle& f,
                        int i,
                        int& min,
                        Vertex_handle& nn,
                        Distance& closer)const
  {
      Face_handle  ni=f->neighbor(i);
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
  propagating_flip(Face_handle& f,int i)
  {
      Face_handle ni = f->neighbor(i);
      if ( CGAL_ON_POSITIVE_SIDE != side_of_oriented_circle(ni,
                                                      f->vertex(i)->point()) ) {
          return;
      }
      flip(f, i);
      propagating_flip(f,i);
      i = ni->index(f->vertex(i));
      propagating_flip(ni,i);
  }
  void remove_2D(Vertex_handle& v )
  {
    // General case
  
    // remove incident faces
    // set up list of faces neighboring the hole
    // in ccw order around the hole
  
    typedef pair<Face_handle  , int>  Hole_Neighbor;
    typedef list<Hole_Neighbor> Hole;
    typedef list<Hole> Hole_list;
  
    Hole hole;
    Hole_list hole_list;
  
    Face_handle  f, ff, fn;
    int i =0,ii =0, in =0;
    Vertex_handle vv;
  
    Face_circulator fc = v->incident_faces();
    Face_circulator done(fc);
     do {
        i  = fc->index(v);
        fn = fc->neighbor(i);
        vv = fc->vertex(fc->cw(i));
        if( vv->face()==  fc ) vv->set_face(fn);
        vv = fc->vertex(fc->ccw(i));
        if( vv->face()==  fc ) vv->set_face(fn);
        in = fn->index( fc );
        fn->set_neighbor(in, NULL);
        hole.push_back(Hole_Neighbor(fn,in));
        fc++.Delete() ;
      }
    while(fc != done);
  
    hole_list.push_front(hole);
  
    while( ! hole_list.empty())
      {
        hole = hole_list.front();
        hole_list.pop_front();
        Hole::iterator hit = hole.begin();
  
        // if the hole has only three edges, create the triangle
          if (hole.size() == 3) {
          Face_handle  newf = new Face();
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
  
  
        Vertex_handle v0 = ff->vertex(ff->cw(ii)); Point p0 =v0->point();
        Vertex_handle v1 = ff->vertex(ff->ccw(ii)); Point p1 =v1->point();
        Vertex_handle v2 = infinite_vertex(); Point p2;
        Vertex_handle vv; Point p;
  
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
        Face_handle  newf = new Face(v0,v1,v2);
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
  
};


template < class I >
ostream&
operator<<(ostream& os, const CGAL_Delaunay_triangulation_2<I> &DT)
{
  return os << (const CGAL_Triangulation_2<I>&)DT;
}



#endif // CGAL_DELAUNAY_TRIANGULATION_2_H
