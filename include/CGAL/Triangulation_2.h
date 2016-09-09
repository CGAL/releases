// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Triangulation_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Triangulation_2.h,v $
// revision      : $Revision: 1.10.1.28 $
// revision_date : $Date: 1999/05/28 08:06:02 $
// author(s)     : Olivier Devillers, Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_2_H
#define CGAL_TRIANGULATION_2_H

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include <CGAL/Pointer.h>
#include <CGAL/circulator.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_default_data_structure_2.h>
#include <CGAL/Triangulation_face_2.h>
#include <CGAL/Triangulation_vertex_2.h>
#include <CGAL/Triangulation_handles_2.h>
#include <CGAL/Triangulation_iterators_2.h>
#include <CGAL/Triangulation_circulators_2.h>
#include <CGAL/Triangulation_line_face_circulator_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds>
class Triangulation_face_iterator_2;

template < class Gt, class Tds>
class Triangulation_vertex_iterator_2;

template < class Gt, class Tds>
class Triangulation_edge_iterator_2;


template < class Gt, class Tds >
class Triangulation_2
  : public Triangulation_cw_ccw_2
{
  friend std::istream& operator>> CGAL_NULL_TMPL_ARGS
                (std::istream& is, Triangulation_2<Gt,Tds> &tr);
  friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS
                (std::ostream& os, const Triangulation_2<Gt,Tds> &tr);
  friend Triangulation_face_iterator_2<Gt,Tds>;
  friend Triangulation_edge_iterator_2<Gt,Tds>;
  friend Triangulation_vertex_iterator_2<Gt,Tds>;

public:
  typedef Tds Triangulation_data_structure;
  typedef Triangulation_2<Gt,Tds> Triangulation;

  typedef Gt  Geom_traits;
  typedef typename Geom_traits::Point Point;
  typedef typename Geom_traits::Segment Segment;
  typedef typename Geom_traits::Triangle Triangle;

 
  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt,Tds> Vertex;

  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef std::pair<Face_handle, int>                Edge;

  typedef Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  typedef Triangulation_edge_circulator_2<Gt,Tds>      Edge_circulator;
  typedef Triangulation_vertex_circulator_2<Gt,Tds>    Vertex_circulator;

  typedef Triangulation_face_iterator_2<Gt,Tds>   Face_iterator;
  typedef Triangulation_edge_iterator_2<Gt,Tds>   Edge_iterator;
  typedef Triangulation_vertex_iterator_2<Gt,Tds> Vertex_iterator;

  typedef Triangulation_line_face_circulator_2<Gt,Tds>  Line_face_circulator;

  typedef Point value_type; // to have a back_inserter


   enum Locate_type {VERTEX=0, EDGE, FACE, OUTSIDE, COLLINEAR_OUTSIDE};

protected:
  Tds _tds;
  Gt  _gt;

public:

// CONSTRUCTORS
  Triangulation_2()
    :_tds()
  {}

  Triangulation_2(const Geom_traits& geom_traits) 
    : _tds(), _gt(geom_traits)
  {}

  Triangulation_2(const Vertex_handle&  v, 
		       const Geom_traits& geom_traits=Geom_traits())
    : _tds(&(*v)), _gt(geom_traits)
  { }



  // copy constructor duplicates vertices and faces
  Triangulation_2(const Triangulation_2<Gt,Tds> &tr)
    : _tds(tr._tds), _gt(tr._gt)
  {}
  

  Triangulation_2(Tds tds, const Geom_traits& geom_traits=Geom_traits())
    : _tds(),_gt(geom_traits)
  {
    _tds.swap(tds);
  }
  
 

  //Assignement
  Triangulation_2 &operator=(const Triangulation_2 &tr)
  {
    _tds = tr._tds;
    _gt = tr._gt;
     return *this;
  }

  // Helping functions
   
  void  copy_triangulation(const Triangulation_2 &tr)
  {
     _gt = tr._gt;
    _tds.copy_tds(tr._tds);
  }

  void swap(Triangulation_2 &tr)
  {
    Geom_traits t = geom_traits();
    _gt = tr.geom_traits();
    tr._gt = t; 
    _tds.swap(tr._tds);
  }

  void clear()
  {
    _tds.clear();
  }


  //ACCESS FUNCTIONs
  int  dimension() const { return _tds.dimension();}
  int number_of_vertices() const {return _tds.number_of_vertices();}
  int number_of_faces() const {return _tds.number_of_faces();}
  const Geom_traits& geom_traits() const { return _gt;}
  
  Vertex_handle finite_vertex() const
  {
    return (Vertex *) _tds.finite_vertex();
  }

  Vertex_handle  infinite_vertex() const
  {
    return (Vertex *) _tds.infinite_vertex();
  }
   
  Face_handle infinite_face() const
  {
    return infinite_vertex()->face();
  }

 
  //SETTING
protected:
  void set_finite_vertex(const Vertex_handle&  v)
  {
        _tds.set_finite_vertex (&(*v));
  }


  void set_infinite_vertex(const Vertex_handle&  v)
  {
        _tds.set_infinite_vertex(&(*v));
  }

  void set_number_of_vertices(int n) { _tds.set_number_of_vertices(n);}

public:   
  // CHECKING
  bool is_valid(bool verbose = false, int level = 0) const;
  

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

  bool is_infinite(const Edge& e) const {
    return is_infinite(e.first,e.second);
  }
   
  bool is_infinite(const Edge_circulator& ec) const {
    return is_infinite(*ec);
  }

  bool is_infinite(const Edge_iterator& ei) const {
    return is_infinite(*ei);
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

  Segment segment(const Edge& e) const
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



  //INSERTION - DELETION - Flip
public:
  void   flip(Face_handle& f, int i);
  
  void 
  insert_first(const Vertex_handle& v)
  {
    CGAL_triangulation_precondition(number_of_vertices() == 0 &&
				    v != infinite_vertex());
    _tds.insert_first( &(*v));
    return;
  }

  void 
  insert_second(const Vertex_handle& v)
  {
    CGAL_triangulation_precondition(number_of_vertices() == 1 &&
				    v != infinite_vertex() &&
				    v != finite_vertex());
    _tds.insert_second( &(*v));
    return;
  }

  void 
  insert_in_face(const Vertex_handle&  v, const Face_handle& f)
  {
    CGAL_triangulation_precondition(oriented_side(f, v->point()) == 
				    ON_POSITIVE_SIDE);
    _tds.insert_in_face( &(*v), &(*f));
    return;
  }

  void 
  insert_in_edge(const Vertex_handle& v, const Face_handle& f,int i)
  {
    CGAL_triangulation_precondition(
      geom_traits().orientation(f->vertex(cw(i))->point(),
				v->point(),
				f->vertex(ccw(i))->point() ) == COLLINEAR &&
      collinear_between(f->vertex(cw(i))->point(),
			v->point(),
			f->vertex(ccw(i))->point()) );
    _tds.insert_in_edge(&(*v), &(*f), i);
    return;
  }


void 
insert_outside(const Vertex_handle& vp, const Face_handle& f);

    
void
insert_collinear_outside(const Vertex_handle& v, const Face_handle& f, int i);
 
  
Vertex_handle 
insert(const Point& p,
       Locate_type& lt,
       Face_handle f = Face_handle() );
  
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
    int insert(std::list<Point>::const_iterator first,
               std::list<Point>::const_iterator last)
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
    int insert(std::vector<Point>::const_iterator first,
               std::vector<Point>::const_iterator last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
#endif // VECTOR_H
  //#ifdef ITERATOR_H
    int insert(std::istream_iterator<Point, ptrdiff_t> first,
               std::istream_iterator<Point, ptrdiff_t> last)
    {
        int n = number_of_vertices();
        while(first != last){
            insert(*first);
            ++first;
        }
        return number_of_vertices() - n;
    }
  //#endif // ITERATOR_H
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
#endif // TEMPLATE_MEMBER_FUNCTIONS

    
    
public:  

 void remove_degree_3(Vertex_handle  v, Face_handle f = Face_handle())
  {
    if (f == Face_handle()) f=v->face();
    _tds.remove_degree_3(&(*v), &(*f));
    return;
  }




void remove_first(Vertex_handle  v)
  {
    _tds.remove_first(&(*v));
    return;
  }

void remove_second(Vertex_handle v)
  {
    _tds.remove_second(&(*v));
    return;
  }

void remove(Vertex_handle  v);
    

protected:
  void remove_1D(Vertex_handle v);
  void remove_2D(Vertex_handle v);
  
public:    

  // POINT LOCATION

  Face_handle
    march_locate_1D(const Point& t, Locate_type& lt, int& li) const ;
     
  Face_handle
    march_locate_2D(const Face_handle& start,
                    const Point& t,
                    Locate_type& lt,
                    int& li) const;
    
    Face_handle
    locate(const Point& p,
           Locate_type& lt,
           int& li,
           Face_handle start = Face_handle()) const;
    
    
    inline Face_handle
    locate(const Point &p,
           Face_handle start = Face_handle()) const
    {
        Locate_type lt;
        int li;
        return locate(p, lt, li, start);
    }
    



  //TRAVERSING : ITERATORS AND CIRCULATORS
 Face_iterator faces_begin() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds> *)this;
        return Face_iterator(ncthis);
    }
    Face_iterator faces_end() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds> *)this;
        return Face_iterator(ncthis, 1);
    }
    Vertex_iterator vertices_begin() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds>*)this;
        return Vertex_iterator(ncthis);
    }
    Vertex_iterator vertices_end() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds>*)this;
        return Vertex_iterator(ncthis,1);
    }
    Edge_iterator edges_begin() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds>*)this;
        return Edge_iterator(ncthis);
    }
    Edge_iterator edges_end() const
    {
        Triangulation_2<Gt, Tds>* 
		ncthis = (Triangulation_2<Gt, Tds>*)this;
        return Edge_iterator(ncthis,1);
    }

  Face_circulator incident_faces( const Vertex_handle& v) const
  {
    return v->incident_faces();
  }

  
   Face_circulator incident_faces( 
	const Vertex_handle& v, const Face_handle& f) const
  {
    return v->incident_faces(f);
  }

   
  Vertex_circulator incident_vertices(const Vertex_handle& v) const
  {
    return v->incident_vertices();
  }

  
  Vertex_circulator incident_vertices(const Vertex_handle& v,
				      const Face_handle& f) const
  {
    return v->incident_vertices(f);
  }

 
  Edge_circulator incident_edgees(const Vertex_handle& v) const
  {
    return v->incident_edges();
  }

  
  Edge_circulator incident_edges(const Vertex_handle& v,
				 const Face_handle& f) const
  {
    return v->incident_edges(f);
  }


   Line_face_circulator
    line_walk(const Point& p,
              const Point& q,
              Face_handle f = Face_handle());
    
    
// not documented
public:
 Oriented_side
    oriented_side(const Point &p0, const Point &p1,
                  const Point &p2, const Point &p) const;
    
    Bounded_side
    bounded_side(const Point &p0, const Point &p1,
                 const Point &p2, const Point &p) const;
    
    Oriented_side
    oriented_side(const Face_handle& f, const Point &p) const
    {
        return oriented_side(f->vertex(0)->point(),
                             f->vertex(1)->point(),
                             f->vertex(2)->point(),
                             p);
    }

 
  
    
  // NOT DOCUMENTED
    bool 
    collinear_between(const Point& p, const Point& q, const Point& r) const;
    
    
};

template <class Gt, class Tds >
bool
Triangulation_2<Gt,Tds>::
is_valid(bool verbose = false, int level = 0) const
{
    bool result = _tds.is_valid();

    Face_iterator it;
    for(it=faces_begin(); it!=faces_end(); it++){
      Orientation s = geom_traits().orientation(it->vertex(0)->point(),
						     it->vertex(1)->point(),
						     it->vertex(2)->point());
      CGAL_triangulation_assertion( s == LEFTTURN );
      result = result && ( s == LEFTTURN );
    }

    if (number_of_vertices() <= 2) return result;
    Vertex_circulator start = infinite_vertex()->incident_vertices(),
      pc(start),
      qc(start),
      rc(start);
    ++qc;
    ++rc;
    ++rc;
    do{
      Orientation s = geom_traits().orientation(pc->point(),
						     qc->point(),
						     rc->point());
      CGAL_triangulation_assertion( s != LEFTTURN );
      result = result && ( s != LEFTTURN );
      pc = qc;
      qc = rc;
      ++rc;
    }while(pc != start);
    return result;
  }

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
flip(Face_handle& f, int i)
{
    CGAL_triangulation_precondition ( ! f.is_null() );
    CGAL_triangulation_precondition (i == 0 || i == 1 || i == 2);

    //Face_handle n = f->neighbor(i);
    CGAL_triangulation_precondition( !is_infinite(f) && 
				     !is_infinite(f->neighbor(i)) );
    CGAL_triangulation_precondition( 
       geom_traits().orientation(f->vertex(i)->point(),
				 f->vertex(cw(i))->point(),
		(f->neighbor(i))->vertex((f->neighbor(i))->index(f))->point() ) 
       ==  RIGHTTURN  
       &&
      geom_traits().orientation(f->vertex(i)->point(),
				f->vertex(ccw(i))->point(),
		  (f->neighbor(i))->vertex((f->neighbor(i))->index(f))->point() ) 
       ==  LEFTTURN
       );
     
    _tds.flip( &(*f), i);
    return;
  }

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
insert_outside(const Vertex_handle& vp, const Face_handle& f)
  {
    CGAL_triangulation_precondition(is_infinite(f));

    std::list<Face_handle> ccwlist;
    std::list<Face_handle> cwlist;

    int li;
    Point p = vp->point();
    Point q,r;

    li = f->index(infinite_vertex());
    q = f->vertex(ccw(li))->point();
    r = f->vertex(cw(li))->point();
    CGAL_triangulation_precondition( geom_traits().orientation(p,q,r) 
					== LEFTTURN);
    
    Face_circulator fc = infinite_vertex()->incident_faces(f);
    bool done = false;
    while(! done) {
      fc--;
      li = fc->index(infinite_vertex());
      q = fc->vertex(ccw(li))->point();
      r = fc->vertex(cw(li))->point();
      if(geom_traits().orientation(p,q,r) == LEFTTURN ) {
      ccwlist.push_back(&(*fc));
      }
      else {done=true;}
    }

    fc= infinite_vertex()->incident_faces(f);
    done = false;
    while(! done){
      fc++;
      li = fc->index(infinite_vertex());
      q = fc->vertex(ccw(li))->point();
      r = fc->vertex(cw(li))->point();
      if(geom_traits().orientation(p,q,r) == LEFTTURN ) {
	cwlist.push_back(&(*fc));
      }
      else {done=true;}
    }

    _tds.insert_in_face( &(*vp), &(*f));

     Face_handle fh;
     while ( ! ccwlist.empty()) {
      fh = ccwlist.front();
      li = ccw(fh->index(infinite_vertex()));
      _tds.flip( &(*fh) , li);
      ccwlist.pop_front();
    }

    while ( ! cwlist.empty()) {
      fh = cwlist.front();
      li = cw(fh->index(infinite_vertex()));
      _tds.flip( &(*fh) , li);
      cwlist.pop_front();
    }

    //reset infinite_vertex()->face();
    fc = vp->incident_faces();
    while( ! is_infinite(&(*fc))) {
      fc++;}
    infinite_vertex()->set_face(&(*fc));
  } 

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
insert_collinear_outside(const Vertex_handle& v, const Face_handle& f, int i)
 {
    CGAL_triangulation_precondition(dimension()== 1 );
    //int j = f->index(infinite_vertex());
    //int k = 3-(i+j);
    CGAL_triangulation_precondition(
       geom_traits().orientation(
	       f->vertex(3-i-(f->index(infinite_vertex())))->point(),
	       f->vertex(i)->point(),
	       v->point()) == COLLINEAR &&
      collinear_between( 
                 f->vertex(3-i-(f->index(infinite_vertex())))->point(),
		 f->vertex(i)->point(),
		 v->point()) );
     _tds.insert_collinear_outside(&(*v),&(*f),i);
     return;
  }
	

template <class Gt, class Tds >
Triangulation_2<Gt,Tds>::Vertex_handle
Triangulation_2<Gt,Tds>::
insert(const Point& p, Locate_type& lt, Face_handle f)
{
    Vertex_handle v;
    if(number_of_vertices() == 0) {
      v = new Vertex(p);
      lt = OUTSIDE;
      //_tds.insert_first(&(*v));
      insert_first(v);
      return v;
    }
    if(number_of_vertices() == 1) {
      if (geom_traits().compare(p,finite_vertex()->point()) ) {
	lt = VERTEX;
	return finite_vertex();
      }
      v = new Vertex(p);
      lt = OUTSIDE;
      //_tds.insert_second(&(*v));
      insert_second(v);
      return v;
    }

    int li;
    Face_handle loc = locate(p, lt, li, f);
    
    switch(lt){
    case FACE:
      {
	v = new Vertex(p);
        //_tds.insert_in_face( &(*v), &(*loc));
	insert_in_face(v,loc);
	break;
      }
    case OUTSIDE:
      {
	v = new Vertex(p);
	insert_outside(v,loc);
	break;
      }
    case EDGE:
      {
	v = new Vertex(p);
	//_tds.insert_in_edge( &(*v), &(*loc), li);
	insert_in_edge(v,loc,li);
	break;
      }
    case COLLINEAR_OUTSIDE:
      {
	v = new Vertex(p);
	//_tds.insert_collinear_outside( &(*v), &(*loc),li);
	insert_collinear_outside(v,loc,li);
	break; 
      }
    case VERTEX:
      return loc->vertex(li);
    default:
      CGAL_triangulation_assertion(false);  // locate step failed
    }
    return v;
  }

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
remove(Vertex_handle  v)
{
      CGAL_triangulation_precondition( ! v.is_null() );
      CGAL_triangulation_precondition( !is_infinite(v));
    
      if  (number_of_vertices() == 1) {
        remove_first(& (*v));
	v.clear();
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

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
remove_1D(Vertex_handle v)
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
	  f1->vertex(cw(i1))->set_face(f1n);
	  f1->vertex(ccw(i1))->set_face(f1n);
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

	   // update the face() pointer of the remaining vertices of f1 and f2
	   f1->vertex(j1)->set_face(f1n);
	   f2->vertex(j2)->set_face(f2n);
	   infinite_vertex()->set_face(f1n);

           f1.Delete(); f2.Delete();
           return;
        }
     }

template <class Gt, class Tds >
void
Triangulation_2<Gt,Tds>::
remove_2D(Vertex_handle v)
  {
      // General case
    
      // remove incident faces
      // set up list of faces neighboring the hole
      // in ccw order around the hole
    
      // problem with gcc link
      typedef std::pair<void *, int> Hole_neighbor;
      //typedef pair<Face_handle  , int>  Hole_neighbor;
      //typedef pair<Face*, int> Hole_neighbor;
      typedef std::list<Hole_neighbor> Hole;
      
    
      Hole hole;
      typename Hole::iterator hit;
      std::list<Face*> to_delete;

      Face_handle  f, ff, fn;
      int i =0,ii =0, in =0;
      Vertex_handle  vv;
      Point p = v->point();
    
      Face_circulator fc = v->incident_faces();
      Face_circulator done(fc);
       do {
	 f = (*fc).handle(); fc++;
	 i = f->index(v);
	 fn = f->neighbor(i);
	 vv = f->vertex(f->cw(i));
	 if( vv->face()==  f) vv->set_face(fn);
	 vv = f->vertex(f->ccw(i));
	 if( vv->face()== f) vv->set_face(fn);
	 in = fn->index(f);
	 fn->set_neighbor(in, NULL);
	 hole.push_back(Hole_neighbor(&(*fn),in));
	 //hole.push_back(Hole_neighbor(fn,in));
	 // to_delete.push_back(f);
	 to_delete.push_back(&(*f));
       }
      while(fc != done);

       while (! to_delete.empty()){
	 delete to_delete.front();
	 to_delete.pop_front();
       }
    
       Vertex_handle v0, v1, v2;
       Point   p0, p1, p2;
       Bounded_side side;
       	Orientation or;
       int nhole;

       if( hole.size() != 3) {
	 //  find the first edge  v0v1 on the hole boundary
	 //  such that
	 //  v0, v1 and the next vertex v2 are all finite
         //   v0v1v2 is a left turn and
	 //  triangle v0v1v2 does not contain the removed point
    
	 // if found create face v0v1v2
	 // stop when no more faces can be created that way
                  
         nhole= hole.size(); 
	 // nhole decount the number of hole edges passed
	 // from the last created edges
         while (hole.size()>3 && nhole>0) {           
            ff  = (Face *) ( (hole.front()).first);
	    //ff =  hole.front().first
	    ii  = (hole.front()).second;
	    hole.pop_front();

            v0 = ff->vertex(cw(ii));
            v1 = ff->vertex(ccw(ii));
            if( !is_infinite(v0) && !is_infinite(v1)) {
	      fn  = (Face *) ( (hole.front()).first);
	      //fn =  hole.front().first
	      in  = (hole.front()).second;
            
	      v2 = fn->vertex(ccw(in));
	      if( !is_infinite(v2)) {
		p0 = v0->point();
		p1 = v1->point();
		p2 = v2->point();
		or = geom_traits().orientation(p0,p1,p2);
		if ( or  == LEFTTURN) {
		  side = bounded_side(p0,p1,p2, p);
		  if( side == ON_UNBOUNDED_SIDE || 
		      (side == ON_BOUNDARY && collinear_between(p0, p, p2)) ) {
		    //create face
		    Face_handle  newf = new Face(v0,v1,v2);
		    newf->set_neighbor(2,ff);
		    newf->set_neighbor(0,fn);
		    ff->set_neighbor(ii, newf);
		    fn->set_neighbor(in,newf);
		    hole.pop_front();
		    hole.push_front(Hole_neighbor(&(*newf),1));
		    nhole = hole.size();
		    continue;
		  }
		}
	      }
	    }

	    // not possible to create face v0,v1,v2;
	    hole.push_back(Hole_neighbor(&(*ff),ii));
	    nhole--;
	 }
       }
    
      // either the hole has only three edges
      // or all its finite vertices are reflex or flat
      // except may be one vertex whose corresponding ear 
      // includes the vertex being removed

      // deal with the last leftturn if any
      if(hole.size() != 3) {
	nhole = hole.size();
	while ( nhole>0) {
	  ff = (Face *) ((hole.front()).first);
	  // ff = ((hole.front()).first)
	  ii = (hole.front()).second;
	  hole.push_back(hole.front());
	  hole.pop_front();
	  nhole--;
	  
	  v0 = ff->vertex(cw(ii));
	  v1 = ff->vertex(ccw(ii));
	  if(is_infinite(v0) || is_infinite(v1))  continue;

	  fn = (Face *) ((hole.front()).first);
	  // fn = ((hole.front()).first)
	  in = (hole.front()).second;
	  v2 = fn->vertex(ccw(in));
          if( is_infinite(v2) ) continue;
	  p0 = v0->point();
	  p1 = v1->point();
	  p2 = v2->point();
	  Orientation or = geom_traits().orientation(p0,p1,p2);
          if ( or  == LEFTTURN) {
	    Face_handle  newf = new Face(v0,v1,v2);
	    newf->set_neighbor(2,ff);
	    newf->set_neighbor(0,fn);
	    ff->set_neighbor(ii, newf);
	    fn->set_neighbor(in,newf);
	    hole.pop_back();
	    hole.pop_front();
	    hole.push_front(Hole_neighbor(&(*newf),1));
	    break;
	  }
	}
      }


      if(hole.size() != 3) {
	// look for infinite vertex
	ff = (Face *) ((hole.front()).first);
	//ff = (hole.front()).first;
	//ff = ((hole.front()).first)->handle();
	ii = (hole.front()).second;
	while ( ! is_infinite(ff->vertex(cw(ii)))){
	  hole.push_back(hole.front());
	  hole.pop_front();
	  ff = (Face *)((hole.front()).first);
	  //ff = (hole.front()).first;
	  //ff = ((hole.front()).first)->handle();
	  ii = (hole.front()).second;
          }
	//create faces
          while(hole.size() != 3){
            ff = (Face *)((hole.front()).first);
	    //ff = (hole.front()).first;
	    //ff = ((hole.front()).first)->handle();
            ii = (hole.front()).second;
            hole.pop_front();
            fn = (Face *)((hole.front()).first);
	    //fn = (hole.front()).first;
	    //fn = ((hole.front()).first)->handle();
            in = (hole.front()).second;
            hole.pop_front();
            Face_handle  newf = new Face(infinite_vertex(),fn->vertex(cw(in)),
                                                     fn->vertex(ccw(in)));
            ff->set_neighbor(ii,newf);
            fn->set_neighbor(in,newf);
            newf->set_neighbor(0,fn);
            newf->set_neighbor(2,ff);
            hole.push_front(Hole_neighbor(&(*newf),1));
	    //hole.push_front(Hole_neighbor(newf,1));
            }
      }
    
 // now hole has three edges
          Face_handle  newf = new Face();
          hit = hole.begin();
          for(int j = 0;j<3;j++) {
            ff = (Face *)((*hit).first);
	    //ff = (*hit).first;
	    //ff = ((*hit).first)->handle();
            ii = (*hit).second;
            hit++;
            ff->set_neighbor(ii,newf);
            newf->set_neighbor(j,ff);
            newf->set_vertex(newf->ccw(j),ff->vertex(ff->cw(ii)));
          }
    }


template <class Gt, class Tds >
Triangulation_2<Gt, Tds>:: Face_handle
Triangulation_2<Gt, Tds>::
march_locate_1D(const Point& t, Locate_type& lt, int& li) const
{
        Face_handle i_f = infinite_face();
        int i = i_f->index(infinite_vertex());
        Point p = i_f->vertex(ccw(i))->point();
        Point q = i_f->vertex(cw(i))->point();
        Orientation pqt = geom_traits().orientation(p, q, t);
        if(pqt == RIGHTTURN){
            lt = OUTSIDE;
            return i_f->neighbor(i);
        }
        if(pqt == LEFTTURN){
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
            if(geom_traits().compare_x(t,v->point()) == EQUAL && 
	       geom_traits().compare_y(t,v->point()) == EQUAL){
                lt = VERTEX;
                li = cw(i);
                return fc->handle() ;
            }
            if(collinear_between(u->point(), t, v->point())){
                lt = EDGE;
                li = i;
                return fc->handle() ;
            }
            ++fc;
            i = fc->index(vi);
            w = fc->vertex(cw(i));
            if( (u == w) && collinear_between(u->point(), v->point(), t)){
                lt = COLLINEAR_OUTSIDE;
                li = ccw(i);
                return fc->handle() ;
            }
            u = v;
            v = w;
        }
    }

template <class Gt, class Tds >    
Triangulation_2<Gt, Tds>::Face_handle
Triangulation_2<Gt, Tds>::
march_locate_2D(const Face_handle& start,
		const Point& t,
		Locate_type& lt,
		int& li) const
{
     //    CGAL_triangulation_precondition( ! is_infinite(start) );
        Triangulation_2 *ncthis = (Triangulation_2 *)this;
    
        Point p(start->vertex(0)->point());
        if(geom_traits().compare_x(t,p) == EQUAL &&  
	   geom_traits().compare_y(t,p) == EQUAL){
            lt = VERTEX;
            li = 0;
            return start;
        }

        Line_face_circulator lfc(start->vertex(0),
                                 ncthis,
                                 t);
	
        if(lfc.collinear_outside()) {
            // point t lies outside or on the convex hull
            // we walk clockwise on the hull to decide
            int i = lfc->index(infinite_vertex());
            p = lfc->vertex(ccw(i))->point();
            if(geom_traits().compare_x(t,p) == EQUAL &&  
	       geom_traits().compare_y(t,p) == EQUAL){
                lt = VERTEX;
                li = ccw(i);
                return lfc;
            }
         Point q(lfc->vertex(cw(i))->point());
	 Orientation pqt;
         Face_handle f(lfc);
         while(1){
           if(geom_traits().compare_x(t,q) == EQUAL &&  
	      geom_traits().compare_y(t,q) == EQUAL){
             lt = VERTEX;
             li = cw(i);
             return f;
           }
	   pqt = geom_traits().orientation(p,q,t);
	   if (pqt == COLLINEAR && collinear_between(p, t, q)){
	     lt = EDGE;
	     li = i;
	     return f;
	   }
	   if (pqt == LEFTTURN){
	     lt = OUTSIDE;
	     return f ;
	   }
	   	       
           // go to the next face
           f = f->neighbor(ccw(i));
           i = f->index(infinite_vertex());
           p = q;
           q = f->vertex(cw(i))->point();
     	 }
        }

        while(! lfc.locate(t, lt, li) ){
	  lfc.increment();
        }
        return lfc;
  //return start;
    }
 
template <class Gt, class Tds >
Triangulation_2<Gt, Tds>::Face_handle
Triangulation_2<Gt, Tds>::
locate(const Point& p,
           Locate_type& lt,
           int& li,
           Face_handle start) const
 {
        if(number_of_vertices() < 2) {
            if(number_of_vertices() == 0) {
                lt = OUTSIDE;
            } else { // number_of_vertices() == 1
                lt = geom_traits().compare(p,finite_vertex()->point()) ? 
							VERTEX : OUTSIDE;
            }
            return NULL;
        }
        if(dimension() == 1){
            return march_locate_1D(p, lt, li);
        }
    
        if(start.is_null()){
            start = infinite_face()->
                        neighbor(infinite_face()->index(infinite_vertex()));
        }else if(is_infinite(start)){
            start = start->neighbor(start->index(infinite_vertex()));
        }
    
        return march_locate_2D(start, p, lt, li);
 }
    
template <class Gt, class Tds >
Triangulation_2<Gt, Tds>:: Line_face_circulator  
Triangulation_2<Gt, Tds>::    
line_walk(const Point& p,
              const Point& q,
              Face_handle f) 
{
        CGAL_triangulation_precondition( (dimension() == 2) && 
					 (! geom_traits().compare(p,q)) );
    
        Line_face_circulator lfc = (f.is_null())
                                   ? Line_face_circulator(p, q, this)
                                   : Line_face_circulator(p, q, f, this);
    
        if( (!lfc.is_empty()) && is_infinite( lfc )){
            return Line_face_circulator();
        }
        return lfc;
}
   
template <class Gt, class Tds >
 Oriented_side
Triangulation_2<Gt, Tds>::
oriented_side(const Point &p0, const Point &p1,
                  const Point &p2, const Point &p) const
{
        // depends on the orientation of the vertices
        Orientation o1 = geom_traits().orientation(p0, p1, p),
                         o2 = geom_traits().orientation(p1, p2, p),
                          o3 = geom_traits().orientation(p2, p0, p),
                         ot = geom_traits().orientation(p0, p1, p2);

        if (o1 == COLLINEAR ||
            o2 == COLLINEAR ||
            o3 == COLLINEAR)  {
            if ((o1 == COLLINEAR &&
                 collinear_between(p0, p, p1)) ||
                (o2 == COLLINEAR &&
                 collinear_between(p1, p, p2)) ||
                (o3 == COLLINEAR &&
                 collinear_between(p2, p, p0)))
                {
                return  ON_ORIENTED_BOUNDARY;
            }
                // for ot == ON_ORIENTED_BOUNDARY the following also
                // does the right thing:
                return (ot == LEFTTURN) ? ON_POSITIVE_SIDE
                                             : ON_NEGATIVE_SIDE;
            }
        if (ot == RIGHTTURN)
            {
                if (o1 == RIGHTTURN &&
                    o2 == RIGHTTURN &&
                    o3 == RIGHTTURN)
                    {
                        return ON_NEGATIVE_SIDE;
                    }
                return ON_POSITIVE_SIDE;
            }
        if (o1 == LEFTTURN &&
            o2 == LEFTTURN &&
            o3 == LEFTTURN)
            {
                return ON_POSITIVE_SIDE;
            }
        return ON_NEGATIVE_SIDE;
    }

template <class Gt, class Tds >
bool
Triangulation_2<Gt, Tds>::
collinear_between(const Point& p, const Point& q, const Point& r) const
{
        Comparison_result c_pr = geom_traits().compare_x(p, r);
        Comparison_result c_pq;
        Comparison_result c_qr;
        if(c_pr == EQUAL) {
            c_pr = geom_traits().compare_y(p, r);
            c_pq = geom_traits().compare_y(p, q);
            c_qr = geom_traits().compare_y(q, r);
        } else {
            c_pq = geom_traits().compare_x(p, q);
            c_qr = geom_traits().compare_x(q, r);
        }
        return ( (c_pq == SMALLER) && (c_qr == SMALLER) ) ||
            ( (c_qr == LARGER) && (c_pq == LARGER) );
    
}

template <class Gt, class Tds >
Bounded_side
Triangulation_2<Gt, Tds>::
bounded_side(const Point &p0, const Point &p1,
                 const Point &p2, const Point &p) const
{
      Orientation o1 = geom_traits().orientation(p0, p1, p),
        o2 = geom_traits().orientation(p1, p2, p),
        o3 = geom_traits().orientation(p2, p0, p),
        ot = geom_traits().orientation(p0, p1, p2);

      if(o1 == COLLINEAR ||
         o2 == COLLINEAR ||
         o3 == COLLINEAR)
        {
          if ((o1 == COLLINEAR &&
               collinear_between(p0, p, p1)) ||
              (o2 == COLLINEAR &&
               collinear_between(p1, p, p2)) ||
              (o3 == COLLINEAR &&
               collinear_between(p2, p, p0)))
            {
              return  ON_BOUNDARY;
            }
          return ON_UNBOUNDED_SIDE;
        }
      if (ot == RIGHTTURN)
        {
          if(o1==RIGHTTURN &&
             o2==RIGHTTURN &&
             o3==RIGHTTURN)
            {
              return ON_BOUNDED_SIDE;
            }
          return ON_UNBOUNDED_SIDE;
        }
      if (o1 == LEFTTURN &&
          o2 == LEFTTURN &&
          o3 == LEFTTURN)
        {
          return ON_BOUNDED_SIDE;
        }
      return ON_UNBOUNDED_SIDE;
    }



 


template <class Gt, class Tds >
std::ostream&
operator<<(std::ostream& os, const Triangulation_2<Gt, Tds> &tr)
{
  // to debug
  //operator<<(os, tr._tds);
  //os << tr._tds;

  std::map< void*, int, std::less<void*> > V;
  std::map< void*, int, std::less<void*> > F;
  typename Triangulation_2<Gt, Tds>::Vertex_handle  v;

    int n = tr.number_of_vertices() + 1;
    int m = tr.number_of_faces();
    if(is_ascii(os)){
        os << n << ' ' << m << ' ' << tr.dimension() << endl;
    } else {
        os << n << m << tr.dimension();
    }

    // write the vertex at infinity
    int i = 0;
    v = tr.infinite_vertex();
    V[&(*v)] = i;
    os << v->point();
    if(is_ascii(os)){
        os << ' ';
    }
    if(n == 1){
        return os;
    }

    // write the finite vertices
    {
        typename Triangulation_2<Gt, Tds>::Vertex_iterator
          it = tr.vertices_begin();

        while(it != tr.vertices_end()){
            V[&(*it)] = ++i;
            os << it->point();
            if(is_ascii(os)){
                os << ' ';
            }
            ++it;
        }
    }
    CGAL_triangulation_assertion( (i+1) == n );
    if(is_ascii(os)){ os << "\n";}

    if(n == 2){
        return os;
    }

    i = 0;
    // vertices of the finite faces
    {
        typename Triangulation_2<Gt, Tds>::Face_iterator
          it = tr.faces_begin();

        while(it != tr.faces_end()){
	  F[&(*it)] = i++;
	  for(int j = 0; j < 3; j++){
	    os << V[&(*it->vertex(j))];
	    if(is_ascii(os)){
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
        typename Triangulation_2<Gt, Tds>::Face_circulator
            fc = tr.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            F[&(*fc)] = i++;
            for(int j = 0; j < 3; j++){
                os << V[&(*fc->vertex(j))];
                if(is_ascii(os)){
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
        typename Triangulation_2<Gt, Tds>::Face_iterator
            it = tr.faces_begin();
        while(it != tr.faces_end()){
            for(int j = 0; j < 3; j++){
                os << F[&(*it->neighbor(j))];
                if(is_ascii(os)){
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
        typename Triangulation_2<Gt, Tds>::Face_circulator
            fc = tr.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            for(int j = 0; j < 3; j++){
                os << F[&(*fc->neighbor(j))];
                if(is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
        }while(++fc != done);
    }

    
    return os ;
}



template < class Gt, class Tds >
std::istream&
operator>>(std::istream& is, Triangulation_2<Gt, Tds> &tr)
{

  
  return operator>>(is, tr._tds);
}
 
CGAL_END_NAMESPACE
    

#endif //CGAL_TRIANGULATION_2_H

