// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Triangulation_line_face_circulator_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_line_face_circulator_2.h,v $
// revision      : $Revision: 1.12 $
// revision_date : $Date: 2000/06/20 16:51:49 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_LINE_FACE_CIRCULATOR_2_H
#define CGAL_TRIANGULATION_LINE_FACE_CIRCULATOR_2_H

// #include <CGAL/circulator.h>
// #include <CGAL/Triangulation_utils_2.h>
// #include <CGAL/triangulation_assertions.h>
// #include <CGAL/Triangulation_face_2.h>
// #include <CGAL/Triangulation_vertex_2.h>
// #include <CGAL/Triangulation_handles_2.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds >
class Triangulation_2;

template < class Gt, class Tds >
class Triangulation_line_face_circulator_2
  :   public Bidirectional_circulator_base<Triangulation_face_2<Gt,Tds>,
	                                      std::ptrdiff_t,std::size_t>,
      public Triangulation_cw_ccw_2,
      public  Triangulation_face_handle_2<Gt,Tds>
{
public:
  typedef Triangulation_line_face_circulator_2<Gt,Tds> Line_face_circulator;
  typedef Triangulation_2<Gt,Tds> Triangulation;
  typedef Triangulation_face_2<Gt,Tds> Face;
  typedef Triangulation_vertex_2<Gt,Tds> Vertex;
  typedef Triangulation_face_circulator_2<Gt,Tds>      Face_circulator;
  
  typedef Triangulation_face_handle_2<Gt,Tds> Face_handle;
  typedef Triangulation_vertex_handle_2<Gt,Tds> Vertex_handle;
  typedef std::pair<Face_handle, int>                Edge;
 
  typedef typename Gt::Point_2 Point;
  typedef typename Triangulation::Locate_type Locate_type;

   enum State {undefined = -1,
	       vertex_vertex,
	       vertex_edge,
	       edge_vertex,
	       edge_edge};
            
private:
  const Triangulation_2<Gt, Tds>* _tr;
  State s;
  int i;
  Point p, q;
            
public:
  Triangulation_line_face_circulator_2()
    : Face_handle(), _tr(NULL), s(undefined), i(-1)
    {}
            
  Triangulation_line_face_circulator_2(const Line_face_circulator& lfc)
    : Face_handle(& (*lfc)), _tr(lfc._tr), s(lfc.s), 
					i(lfc.i),  p(lfc.p), q(lfc.q)
    {}
            
  Triangulation_line_face_circulator_2(const Face_handle& face,
				       int index,
				       State state,
				       const Triangulation_2<Gt,Tds> * t,
				       const Point& pp,
				       const Point& qq)
    : Face_handle(face), _tr(t), s(state), i(index),  
      p(pp), q(qq)            {
    CGAL_triangulation_precondition(! t->xy_equal(p, q));
  }
   
  Triangulation_line_face_circulator_2(Vertex_handle v,
				       const Triangulation_2<Gt,Tds>* tr,
				       const Point& dir);

  Triangulation_line_face_circulator_2(const Point& pp,
				       const Point& qq,
				       const Triangulation_2<Gt,Tds> * t);
           
  Triangulation_line_face_circulator_2(const Point& pp,
				       const Point& qq,
				       const Face_handle& ff,
				       const Triangulation_2<Gt,Tds>* t); 

  Triangulation_line_face_circulator_2&
  operator=(const Line_face_circulator& lfc) ;
  

  Line_face_circulator&   operator++() ;
  Line_face_circulator&   operator--() ;
  Line_face_circulator    operator++(int);
  Line_face_circulator    operator--(int);
  bool  operator==(const Line_face_circulator& lfc) const;
  bool  operator!=(const Line_face_circulator& lfc) const;
  bool  is_empty() const;
  bool  operator==(CGAL_NULL_TYPE n) const;
  bool  operator!=(CGAL_NULL_TYPE n) const;
  bool  collinear_outside() const;
  bool locate(const Point& t, Locate_type &lt,  int &li);

private:
  void increment();
  void decrement();
};


template < class Gt, class Tds >
Triangulation_line_face_circulator_2<Gt,Tds>&
Triangulation_line_face_circulator_2<Gt,Tds>::
operator=(const Line_face_circulator& lfc)
{
  Face_handle::operator=(lfc);
  i = lfc.i;
  s = lfc.s;
  _tr = lfc._tr;
  p = lfc.p;
  q = lfc.q;
  return *this;
}

template < class Gt, class Tds >
Triangulation_line_face_circulator_2<Gt,Tds>::
Triangulation_line_face_circulator_2(Vertex_handle v,
				     const Triangulation_2<Gt,Tds>* tr,
				     const Point& dir)
  :Face_handle(NULL), _tr(tr), s(undefined)
  //begin at the face incident to v, traversed by the ray from v to dir 
{
  CGAL_triangulation_precondition(
				  (! _tr->is_infinite(v)) &&
				  (_tr->dimension() == 2) &&
				  (! _tr->xy_equal(v->point(),dir)));

  p=v->point();
  q=dir;
  Face_circulator fc = v->incident_faces();
  Face_circulator done = fc;
  int ic = fc->index(v);
  Vertex_handle  vt= fc->vertex(ccw(ic));
  Orientation ptq = RIGHTTURN; 
  //this	initialisation means nothing;
  // just there to avoid a warning
  if (! _tr->is_infinite(vt)) 
    ptq = _tr->orientation(p, vt->point(), q);

		
  while( _tr->is_infinite(vt) || ptq == RIGHTTURN) {
    ++fc;
    if (fc == done) {
      // no edge on the left of pq , pq is a supporting line
      // set Face_handle to the right infinite face
      while ( ! _tr->is_infinite(fc)) 
	{  ++fc;}
      ic = fc->index(_tr->infinite_vertex());
      if( _tr->orientation(fc->vertex( cw(ic))->point(),
			   fc->vertex( ccw(ic))->point(),
			   q) != RIGHTTURN) {  ++fc;}
      Face_handle::operator=(&(*fc));
      i = fc->index(_tr->infinite_vertex());
      s = vertex_vertex;
      return;
    }

    ic = fc->index(v);
    vt= fc->vertex(ccw(ic));
    if (! _tr->is_infinite(vt)) 
      ptq = _tr->orientation(p,  vt->point(), q);
  }
		
	
  // now vt is a finite vertex and ptq is COLLINEAR or LEFTTURN
  Vertex_handle vr = fc-> vertex(cw(ic));
  Orientation prq= RIGHTTURN; 
  //this	initialisation means nothing;
  // just there to avoid a warning
  if (! _tr->is_infinite(vr))
    prq = _tr->orientation(p, vr->point(), q);

  while ( (!_tr->is_infinite(vr)) && (!(prq == RIGHTTURN ))){
    ++fc;
    ic = fc->index(v);
    vr = fc-> vertex(cw(ic));
    if (! _tr->is_infinite(vr))
      prq = _tr->orientation(p, vr->point(), q);
  }
	
  Face_handle::operator=(&(*fc));
  // reset vt, vt is finite and ptq is still COLLINEAR or LEFTTURN
  ic = fc->index(v);
  vt= fc->vertex(ccw(ic));
  ptq = _tr->orientation(p,  vt->point(), q);

  if (_tr->is_infinite(vr)) {		  
    s = vertex_vertex;
    if (ptq == LEFTTURN) {
      i = fc->index(vr); 
    }
    else {// ptq == COLLINEAR
      i= fc->index(vt);
    }
  }
  else{ // vr is a finite vertex}
    if (ptq == LEFTTURN) {
      s = vertex_edge;
      i = ic;
    }
    else { // ptq == COLLINEAR
      s = vertex_vertex;
      i = fc->index(vt);
    }
  }
	
}


template < class Gt, class Tds >
Triangulation_line_face_circulator_2<Gt,Tds>::
Triangulation_line_face_circulator_2(const Point& pp,
				     const Point& qq,
				     const Triangulation_2<Gt,Tds> * t)
     : Face_handle(NULL), _tr(t), s(undefined), p(pp), q(qq)
  //begins at the  first finite face traversed be the oriented line pq
{
  Vertex_handle inf = _tr->infinite_vertex();
  Face_circulator fc = inf->incident_faces(),
    done(fc);
  i = fc->index(inf);
            
  Point l = fc->vertex(cw(i))->point(),
    r = fc->vertex(ccw(i))->point();
            
  Orientation pql = _tr->orientation(p, q, l),
    pqr = _tr->orientation(p, q, r);
            
   do{
    if( (pql == LEFTTURN) && (pqr == RIGHTTURN) ){
      *this = ++Line_face_circulator( fc, i, vertex_edge, t, p, q);
      return;
    } 
    else if ( (pql == LEFTTURN) && (pqr == COLLINEAR) ){
      *this = ++Line_face_circulator( fc, ccw(i), vertex_vertex, t, p, q);
      return;
    } 
    else if( (pql == COLLINEAR) && (pqr == COLLINEAR) ){
      Face_handle n = fc->neighbor(i);
      int ni  = n->index( fc->handle() );
      Vertex_handle vn = n->vertex(ni);
      if(_tr->orientation(p, q, vn->point()) == LEFTTURN){
	// the entire triangulation is to the left of line (p,q).
	// There might be further collinear edges, so we might have
	// to walk back on the hull.
	while(1){
	  ++fc;
	  i = fc->index(inf);
	  l = fc->vertex(cw(i))->point();
	  if(_tr->orientation(p, q, l) == COLLINEAR) continue;
	  else {
	    // we went one step to far back
	    --fc;
	    i = fc->index(inf);
	    Face_handle::operator=(&(*fc->neighbor(i)));
	    i = cw((*this)->index(fc));
	    s = vertex_vertex;
	    return;
	  }
	}
      }
      else {
	// the entire triangulation is to the right of line (p,q).
	// here are no faces to traverse, so we give the circulator
	// a singular value
	return;
      }
    } 
    else {
      --fc;
      l = r;
      pql = pqr;
      i = fc->index(inf);
      r = fc->vertex(ccw(i))->point();
      pqr = _tr->orientation(p, q, r);
    }
  }while(fc != done);
  // if line (p,q) does not intersect the convex hull in an edge
  // the circulator has a singular value
}


template < class Gt, class Tds >
Triangulation_line_face_circulator_2<Gt,Tds>::
Triangulation_line_face_circulator_2(const Point& pp,
				     const Point& qq,
				     const Face_handle& ff,
				     const Triangulation_2<Gt,Tds>* t)
  : Face_handle(ff), _tr(t), s(undefined), p(pp), q(qq)
  //begin the walk at face ff which has to contain pp
{
  CGAL_triangulation_precondition(_tr->is_infinite(ff) ||
			      _tr->oriented_side(ff,p) != ON_NEGATIVE_SIDE);
  int j;
  if(_tr->is_infinite(*this)){
    *this  = Line_face_circulator(p, q, t);
    return;
  }

  // Test whether p lies on a vertex
  for(j = 0; j < 3; j++){
    if((*this)->vertex(j)->point() == p){
      *this = Line_face_circulator( (*this)->vertex(j), t, q);
      return;
    }
  }
            
  // Test whether p lies on an edge
  for(j = 0; j < 3; j++){
    if(_tr->orientation((*this)->vertex(j)->point(),
				      (*this)->vertex(ccw(j))->point(),
				      p) == COLLINEAR){
      Orientation jpq =
	_tr->orientation((*this)->vertex(j)->point(),
				       p,
				       q);
      Orientation p_cwj_q =
	_tr->orientation(p,
				       (*this)->vertex(cw(j))->point(),
				       q);
      switch(jpq){
      case COLLINEAR:
	if(p_cwj_q == RIGHTTURN){
	  s = vertex_vertex;
	  i = ccw(j);
	  return;
	} 
	else if(! _tr->is_infinite((*this)->neighbor(cw(j)))){
	  Face_handle n = (*this)->neighbor(cw(j));
	  i = cw(n->index(*this));
	  Face_handle::operator=(n);
	  s = vertex_vertex;
	  return;
	} else {
           // singular value
	  return;
	}
      case RIGHTTURN:
	i = cw(j);
	s = (p_cwj_q == COLLINEAR) ? vertex_edge :  
	  edge_edge;
	break;
      default: //  LEFTTURN
	switch(p_cwj_q){
	case COLLINEAR:
	  s = edge_vertex;
	  i = cw(j);
	  return;
	case RIGHTTURN:
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
  Orientation or[3];
  for(j=0; j<3; j++) {
    or[j] =
      _tr->orientation(p,q,(*this)->vertex(j)->point());
  }
  for(j=0; j<3; j++) {
    if(or[j] == COLLINEAR){
      i = j;
      s = (or[ccw(j)] == LEFTTURN) ? edge_vertex : 
	vertex_edge;
      return;
    }
  }
  s = edge_edge;
  for(j=0; j<3; j++){
    if(or[j] == RIGHTTURN){
      i = (or[ccw(j)] == RIGHTTURN) ? j : cw(j);
      return;
    }
  }
}


template < class Gt, class Tds >
void
Triangulation_line_face_circulator_2<Gt,Tds>::
increment()
{
  CGAL_triangulation_precondition(*this != CGAL_CIRC_NULL);
  if(s == vertex_vertex || s == edge_vertex) {
    Orientation o;
    Point r;
    do{
      Face_handle n = (*this)->neighbor(cw(i));
      i = n->index(*this);
      Face_handle::operator=(n);
      if (n->vertex(i) == _tr->infinite_vertex()){
	o = COLLINEAR;
	i = cw(i);
	break;
      }
      r = n->vertex(i)->point();
      i = cw(i);
    }while((o = _tr->orientation(p, q, r)) ==  LEFTTURN);
            
    if(o == COLLINEAR) {
      s = vertex_vertex;
      i = ccw(i);
    } 
    else {
      s = vertex_edge;
    }
  } 
  else {
    Face_handle n = (*this)->neighbor(i);
    int ni = n->index(*this);
    Face_handle::operator=(n);
    Orientation o = _tr->is_infinite((*this)->vertex(ni)) ?
      COLLINEAR :
      _tr->orientation(p,q,(*this)->vertex(ni)->point());
            
    switch(o){
    case LEFTTURN:
      s = edge_edge;
      i = ccw(ni);
      break;
    case RIGHTTURN:
      s = edge_edge;
      i = cw(ni);
      break;
    default:
      s = edge_vertex;
      i = ni;
    }
  }
} 
            
template < class Gt, class Tds >
void
Triangulation_line_face_circulator_2<Gt,Tds>::             
decrement()
{
  CGAL_triangulation_precondition(*this != CGAL_CIRC_NULL);
  if(s == vertex_vertex || s == vertex_edge) {
    if(s == vertex_vertex){
      i = cw(i);
    }
    Orientation o;
    Point r;
    do{
      Face_handle n = (*this)->neighbor(ccw(i));
      i = n->index(*this);
      Face_handle::operator=(n);
      if (n->vertex(i) == _tr->infinite_vertex()){
	o = COLLINEAR;
	i = ccw(i);
	break;
      }
      r = n->vertex(i)->point();
      i = ccw(i);
    }while((o = _tr->orientation(p, q, r)) == 
	   LEFTTURN);
            
    s = (o == COLLINEAR) ? vertex_vertex : edge_vertex;
            
  } 
  else { // s == edge_edge  ||  s == edge_vertex
    // the following is not nice. A better solution is to say
    // that index i is at the vertex that is alone on one side of l(p,q)
    if(s == edge_edge){
      i = (_tr->orientation
	   (p, q,
	    (*this)->vertex(i)->point()) == 
	   LEFTTURN)
	? cw(i) : ccw(i);
    }
    Face_handle n = (*this)->neighbor(i);
    i = n->index(*this);
    Face_handle::operator=(n);
    Orientation o = _tr->is_infinite((*this)->vertex(i)) ?
      COLLINEAR :
      _tr->orientation(p, q, (*this)->vertex(i)->point());
            
    s = (o == COLLINEAR) ? vertex_edge : edge_edge;
  }
}

template < class Gt, class Tds >
bool
Triangulation_line_face_circulator_2<Gt,Tds>::
locate(const Point& t, Locate_type &lt,  int &li)
{
  switch(s){            
  case edge_edge:
  case vertex_edge:
    {
      Orientation o =
	_tr->orientation((*this)->vertex(ccw(i))->point(),
			 (*this)->vertex(cw(i))->point(),
			 t);
      if(o == RIGHTTURN)      return false;
      if(o == COLLINEAR){
	lt = Triangulation::EDGE;
	li = i;
	return true;
      }
      lt = Triangulation::FACE;
      li = 4;//li unused in this case
      return true;
    }
  case vertex_vertex:
    {
      if(_tr->is_infinite((*this)->vertex(i))){
	CGAL_triangulation_assertion(
	       _tr->orientation( (*this)->vertex(cw(i))->point(),
				 (*this)->vertex(ccw(i))->point(),
				 t) != LEFTTURN);
	lt = Triangulation::OUTSIDE_CONVEX_HULL;
	li = i;
	return true;
      }
      Point u = (*this)->vertex(cw(i))->point();
      Point v = (*this)->vertex(i)->point();
      // u == t  was detected earlier
      if(_tr->compare_x(v,t)==EQUAL && 
	 _tr->compare_y(v,t)==EQUAL){
	lt = Triangulation::VERTEX;
	li = i;
	return true;
      }
      if(_tr->collinear_between(u, t, v)) {
	lt = Triangulation::EDGE;
	li = ccw(i);
	return true;
      }
      return false;
    }
  default: // edge_vertex
    {
      if(_tr->is_infinite((*this)->vertex(i))){
	lt = Triangulation::OUTSIDE_CONVEX_HULL;
	li = i;
	return true;
      }
      if(_tr->xy_equal(t,(*this)->vertex(i) ->point()) ){
	li = i;
	lt = Triangulation::VERTEX;
	return true;
      }
      if(_tr->collinear_between(p, t, (*this)->vertex(i)->point())) {
	lt = Triangulation::FACE;
	return true;
      }
      return false;
    }
  }
}
           
template < class Gt, class Tds >
inline
Triangulation_line_face_circulator_2<Gt,Tds>&
Triangulation_line_face_circulator_2<Gt,Tds>::
operator++()
{
  CGAL_triangulation_precondition( *this != CGAL_CIRC_NULL) ;
  increment();
  return *this;
}
            
template < class Gt, class Tds >
inline
Triangulation_line_face_circulator_2<Gt,Tds>&
Triangulation_line_face_circulator_2<Gt,Tds>::            
operator--()
{
  CGAL_triangulation_precondition(*this != CGAL_CIRC_NULL) ;
  decrement();
  return *this;
}
            
template < class Gt, class Tds >
inline
Triangulation_line_face_circulator_2<Gt,Tds>
Triangulation_line_face_circulator_2<Gt,Tds>::             
operator++(int)
{
  Line_face_circulator tmp(*this);
  ++(*this);
  return tmp;
}
            
template < class Gt, class Tds >
inline
Triangulation_line_face_circulator_2<Gt,Tds>
Triangulation_line_face_circulator_2<Gt,Tds>::             
operator--(int)
{
  Line_face_circulator tmp(*this);
  --(*this);
  return tmp;
}

template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>::    
operator==(const Line_face_circulator& lfc) const
{
  CGAL_triangulation_precondition( *this != CGAL_CIRC_NULL &&
				   lfc != CGAL_CIRC_NULL);
  return ( Face_handle::operator==(lfc) &&  _tr == lfc._tr &&
            s== lfc.s && p==lfc.p && q==lfc.q);
}

template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>:: 
operator!=(const Line_face_circulator& lfc) const
{
  return !(*this == lfc);
}
            
template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>::   
is_empty() const
{
  return Face_handle::operator==(CGAL_CIRC_NULL);
}

template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>::            
operator==(CGAL_NULL_TYPE n) const
{
  CGAL_triangulation_assertion( n == NULL);
  return Face_handle::operator==(CGAL_CIRC_NULL);
}
            
template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>:: 
operator!=(CGAL_NULL_TYPE n) const
{
  return !(*this == n);
}
            
template < class Gt, class Tds >
inline bool
Triangulation_line_face_circulator_2<Gt,Tds>:: 
collinear_outside() const
{
  return (_tr->is_infinite(*this))
    && (s == vertex_vertex)
    && (! _tr->is_infinite((*this)->vertex(i)));
}

CGAL_END_NAMESPACE
#endif //CGAL_TRIANGULATION_LINE_FACE_CIRCULATOR_2_H

