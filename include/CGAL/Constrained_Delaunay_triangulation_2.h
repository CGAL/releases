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
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Constrained_Delaunay_triangulation_2.h
// package       : Triangulation (4.30)
// source        : $RCSfile: Constrained_Delaunay_triangulation_2.h,v $
// revision      : $Revision: 1.7 $
// revision_date : $Date: 1999/11/12 09:47:03 $
// author(s)     : Mariette Yvinec, Jean Daniel Boissonnat
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H
#define CGAL_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H

#include <math.h>
#include <pair.h>
#include <list.h>
#include <vector.h>
#include <map.h> 
#include <set.h>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_2.h> 
#include <CGAL/Constrained_triangulation_2.h>


CGAL_BEGIN_NAMESPACE
template <class Gt, class Tds>


class Constrained_Delaunay_triangulation_2
  : public Constrained_triangulation_2<Gt,Tds>
{
public:
  typedef Triangulation_2<Gt,Tds> Triangulation;
  typedef Constrained_triangulation_2<Gt,Tds> Constrained_triangulation;
  typedef Constrained_Delaunay_triangulation_2<Gt,Tds>  CD_triangulation;
  typedef typename Constrained_triangulation::Constraint Constraint;
  typedef typename Constrained_triangulation::Vertex_handle Vertex_handle;

  typedef std::list<Edge> List_edges;  
  typedef std::list<Face_handle> List_faces;

  Constrained_Delaunay_triangulation_2(const Gt& gt=Gt() ) : 
    Constrained_triangulation(gt) { }

  Constrained_Delaunay_triangulation_2(const CD_triangulation& cdt)
    : Constrained_triangulation(cdt) {}

  Constrained_Delaunay_triangulation_2(std::list<Constraint>& lc, 
					    const Gt& gt=Gt())
      : Constrained_Delaunay_triangulation_2(gt)
  {
    std::list<Constraint>::iterator itc;
    itc=lc.begin();      
      do{
	insert((*itc).first, (*itc).second);
	++itc;
      } while (itc != list_contraintes.end());
      CGAL_triangulation_postcondition( is_valid() );
  }

  template<class InputIterator>
  Constrained_Delaunay_triangulation_2(InputIterator first,
			      InputIterator last,
			      const Gt& gt=Gt() )
     : Constrained_Delaunay_triangulation_2(gt)
  {
    while(first != last){
          insert((*first).first, (*first).second);
	  first++;
    }
    CGAL_triangulation_postcondition( is_valid() );
  }



  // FLIPS
  bool is_flipable(Face_handle f, int i) const;
  void flip(Face_handle& f, int i);
  void flip_around(Vertex_handle va);
  void propagating_flip(Face_handle& f,int i);
  void propagating_flip(List_edges & edges);

  bool test_conflict(Face_handle fh, const Point& p) const;
  void find_conflicts(Point p, std::list<Edge>& le, 
		      Face_handle hint= Face_handle()) const;
  
  // INSERTION-REMOVAL
  Vertex_handle insert(const Point & a);
  Vertex_handle special_insert_in_edge(const Point & a, Face_handle f, int i);
  void insert(const Point & a, const Point & b);
  void insert(Vertex_handle va, Vertex_handle & vb);
  void insert(Vertex_handle va, Vertex_handle vb, Face_handle & fr,
	      int & i);
  void remove(Vertex_handle v);

  // CHECK
  bool is_valid(bool verbose = false, int level = 0) const;

protected:
  void remove_2D(Vertex_handle v );

public:
  // MESHING 
  double twice_area_of_triangle(const Point &p, 
				const Point &q, 
				const Point &r);
  double norm(const Point &p, const Point &q);
  double aspect_ratio(const Point &p, const Point &q, const Point &r);
  double size(const Point &p, const Point &q, const Point &r);
  bool is_bad(Face_handle  f, double lmax, double lmin, double angmin);
  bool is_gabriel(Face_handle  f, int i);
  bool is_in_diametral_circle(Vertex_handle va, Vertex_handle vb,
			      const Point &p);

  Vertex_handle refine_edge(Face_handle & f, int & i,
			    List_edges & list_of_non_gabriel_constraints,
			    List_faces & set_of_bad_faces,
			    double lmax, double lmin, double angmin);
  void refine_face(Face_handle & f,
		   List_edges & list_of_non_gabriel_constraints,
		   List_faces & set_of_bad_faces,
		   double lmax, double lmin, double angmin);
  void refine(List_edges & list_of_constraints,
			  double lmax, double lmin, double angmin);

  void conform(List_edges & list_of_non_gabriel_constraints,
	       double lmax, double lmin, double angmin);
  void conform(List_edges & list_of_non_gabriel_constraints,
	       List_faces & set_of_bad_faces,
	       double lmax, double lmin, double angmin);
};

template < class Gt, class Tds >
bool 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
is_flipable(Face_handle f, int i) const
  // determines if edge (f,i) can be flipped 
{
  Face_handle ni = f->neighbor(i); 
  if (is_infinite(f) || is_infinite(ni)) return false; 
  if (f->is_constrained(i)) return false;
  return (side_of_oriented_circle(ni, f->vertex(i)->point()) 
                                        == ON_POSITIVE_SIDE);
}

template < class Gt, class Tds >
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
flip(Face_handle& f, int i)
{
  CGAL_triangulation_precondition(is_flipable(f,i));
  Face_handle g = f->neighbor(i);
  _tds.flip( &(*f), i);
  int ig=g->index(f->vertex(i)); 
  // set constraints to new triangles
  Face_handle nfi=f->neighbor(i);
  Face_handle nfj=f->neighbor(cw(i));
  Face_handle ngi=g->neighbor(ig);
  Face_handle ngj=g->neighbor(ccw(ig));
  f->set_constraint(ccw(i),false);
  g->set_constraint(cw(ig),false);
  if (nfi->is_constrained(f->mirror_index(i))) 
           f->set_constraint(i,true);
  else     f->set_constraint(i,false);
 
  if (nfj->is_constrained(f->mirror_index(cw(i)))) 
           f->set_constraint(cw(i),true);
  else     f->set_constraint(cw(i),false);
 
  if (ngi->is_constrained(g->mirror_index(ig)))  
           g->set_constraint(ig,true);
  else     g->set_constraint(ig,false);

  if (ngj->is_constrained(g->mirror_index(ccw(ig)))) 
       g->set_constraint(ccw(ig),true);
  else g->set_constraint(ccw(ig),false);
}

template < class Gt, class Tds >
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
flip_around(Vertex_handle va)
  // makes the triangles incident to vertex va Delaunay using flips
{
  if (dimension() <= 1) return;
  Face_handle f=va->face();
  Face_handle next;    
  Face_handle start(f);
  int i;
  do {
    i = f->index(va); // FRAGILE : DIM 1
    next = f->neighbor(ccw(i));  // turns ccw around a
    propagating_flip(f,i);
    f=next;
  } while(next != start);
}

template < class Gt, class Tds >
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
propagating_flip(Face_handle& f,int i)
  // similar to the corresponding function in Delaunay_triangulation_2.h 
{ 
  if (!is_flipable(f,i)) return;
  Face_handle ni = f->neighbor(i); 
  flip(f, i); // flip for constrained triangulations
  propagating_flip(f,i); 
  i = ni->index(f->vertex(i)); 
  propagating_flip(ni,i); 
} 


template < class Gt, class Tds >
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
propagating_flip(List_edges & edges)
  // makes the triangulation Delaunay by flipping 
  // List edges contains an initial list of edges to be flipped
  // Precondition : the output triangulation is Delaunay if the list 
  // edges contains all edges of the input triangulation that need to be
  // flipped (plus possibly others)
{
  int i, ii, indf, indn;
  Face_handle ni, f,ff;
  Edge ei,eni; 
  Constrained_triangulation::Edge_set edge_set;
  Constrained_triangulation::Less_edge less_edge;
  Edge e[4];
  List_edges:: iterator itedge=edges.begin();

  // initialization of the set of edges to be flip

  while (itedge != edges.end()) {
    f=(*itedge).first;
    i=(*itedge).second;
    if (is_flipable(f,i)) {
      eni=Edge(f->neighbor(i),f->mirror_index(i));
      if (less_edge(*itedge,eni)) edge_set.insert(*itedge);
      else edge_set.insert(eni);
    }
    ++itedge;
  }

  // flip edges and updates the set of edges to be flipped

  while (!(edge_set.empty())) {
    f=(*(edge_set.begin())).first;
    indf=(*(edge_set.begin())).second;

    // erase from edge_set the 4 edges of the wing of the edge to be
    // flipped (edge_set.begin) , i.e. the edges of the faces f and
    // f->neighbor(indf) that are distinct from the edge to be flipped

    ni = f->neighbor(indf); 
    indn=f->mirror_index(indf);
    ei= Edge(f,indf);
    edge_set.erase(ei);
    e[0]= Edge(f,cw(indf));
    e[1]= Edge(f,ccw(indf));
    e[2]= Edge(ni,cw(indn));
    e[3]= Edge(ni,ccw(indn));

    for(i=0;i<4;i++) { 
      ff=e[i].first;
      ii=e[i].second;
      if (is_flipable(ff,ii)) {
	eni=Edge(ff->neighbor(ii),ff->mirror_index(ii));
	if (less_edge(e[i],eni)) { 
	  edge_set.erase(e[i]);}
	else {
	  edge_set.erase(eni);} 
      }
    } 

    // here is the flip 
    flip(f, indf); 

    //insert in edge_set the 4 edges of the wing of the edge that
    //have been flipped 
    e[0]= Edge(f,indf);
    e[1]= Edge(f,cw(indf));
    e[2]= Edge(ni,indn);
    e[3]= Edge(ni,cw(indn));

    for(i=0;i<4;i++) { 
      ff=e[i].first;
      ii=e[i].second;
      if (is_flipable(ff,ii)) {
	eni=Edge(ff->neighbor(ii),ff->mirror_index(ii));
	if (less_edge(e[i],eni)) { 
	  edge_set.insert(e[i]);}
	else {
	  edge_set.insert(eni);} 
      }
    } 
  }  
}

template < class Gt, class Tds >
inline bool
Constrained_Delaunay_triangulation_2<Gt, Tds>::
test_conflict(Face_handle fh, const Point& p) const
  // true if point P lies inside the circle circumscribing face fh
{
  return ( side_of_oriented_circle(fh,p) == ON_POSITIVE_SIDE );
}


template < class Gt, class Tds >    
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
find_conflicts(Point p, std::list<Edge>& le, Face_handle hint) const
{
  // sets in le the counterclocwise list of the edges of the boundary of the 
  // union of the faces in conflict with p
  // an edge is represented by the incident face that is not in conflict with p
  Face_handle fh= locate(p, hint);
  le.push_back(Edge(fh->neighbor(0),fh->neighbor(0)->index(fh)));
  le.push_back(Edge(fh->neighbor(1),fh->neighbor(1)->index(fh)));
  le.push_back(Edge(fh->neighbor(2),fh->neighbor(2)->index(fh)));

  std::list<Edge>::iterator lit=le.begin();
  std::list<Edge>::iterator litt;
  int ih;
  while(lit != le.end()){
    if ( !((*lit).first->is_constrained((*lit).second)) && 
	 ( test_conflict((*lit).first, p)) ){
      fh = (*lit).first;
      ih = (*lit).second;
      litt = lit; // this one has to be deleted
      lit = le.insert(lit, Edge(fh->neighbor(cw(ih)),
				fh->neighbor(cw(ih))->index(fh)) );
      lit = le.insert(lit, Edge(fh->neighbor(ccw(ih)),
				fh->neighbor(ccw(ih))->index(fh)) );
      le.erase(litt);
    }
    else { ++lit;}
  }
}
  
template < class Gt, class Tds >  
inline 
Constrained_Delaunay_triangulation_2<Gt, Tds>::Vertex_handle 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
insert(const Point & a)
  // inserts a in the triangulation
{
  Vertex_handle va= Constrained_triangulation::insert(a);
  flip_around(va); 
  return va;
}


template < class Gt, class Tds >  
inline 
Constrained_Delaunay_triangulation_2<Gt, Tds>::Vertex_handle 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
special_insert_in_edge(const Point & a, Face_handle f, int i)
  // insert  point p in edge(f,i)
  // update constrained status
  // and restore Delaunay constrained property
  // this function is intended to be use by refine
{
  Vertex_handle va;
  Vertex_handle c1,c2;
  c1 = f->vertex(cw(i));  //endpoint of edge
  c2 = f->vertex(ccw(i)); //endpoint of edge

  // CGAL_triangulation_precondition(
  //   geom_traits().orientation(c1->point(), a, c2->point()) == COLLINEAR &&
  //   collinear_between(c1->point(), p, c2->point()));

  // inserting a bypassing the precondition of
  // va = Triangulation::insert_in_edge(a,f,i);
  // because midpoint is not exact
  // TO BE DISCUSSED
  va = static_cast<Vertex*> (_tds.insert_in_edge(&(*f), i));
  va->set_point(a);

  if (f->is_constrained(i)) update_constraints_incident(va, c1,c2);
  else clear_constraints_incident(va);
  if (dimension() == 2) update_constraints_opposite(va);
  flip_around(va); 
  return va;
}


template < class Gt, class Tds >  
inline void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
insert(const Point & a, const Point & b)
 // inserts segment ab as a constraint and updates the 
 // constrained Delaunay triangulation
{
  Vertex_handle va= insert(a);
  Vertex_handle vb= insert(b);
  insert(va, vb);
}

template < class Gt, class Tds >  
inline void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
insert(Vertex_handle va, Vertex_handle & vb)
// inserts line segment ab as an edge in the triangulation 
{
  List_edges new_edges;
  Face_handle fr;
  int i;
  Constrained_triangulation::insert(va,vb,fr,i,new_edges);
  propagating_flip(new_edges);
}

template < class Gt, class Tds >  
inline void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
insert(Vertex_handle va, Vertex_handle vb,
       Face_handle & fr, int & i)
 // inserts line segment ab as an edge in the triangulation 
 // returns the triangle fr right to edge ab
 // edge ab=(fr,i)
{
  List_edges new_edges;
  Constrained_triangulation::insert(va,vb,fr,i,new_edges);
  propagating_flip(new_edges);
}

template < class Gt, class Tds >  
inline void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
remove(Vertex_handle v)
{
  CGAL_triangulation_precondition( ! v.is_null() );
  CGAL_triangulation_precondition( !is_infinite(v));
    
  if  (dimension() <= 1)    Constrained_triangulation::remove(v);
  else  remove_2D(v);
  return;
}

template < class Gt, class Tds >  
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
remove_2D(Vertex_handle v)
{
 if (test_dim_down(v)) {  _tds.remove_dim_down(&(*v));  }
  else {
    std::list<Edge> hole;
    make_hole(v, hole);
    std::list<Edge> shell=hole; //because hole will be emptied by fill_hole
    fill_hole_delaunay(hole);
    update_constraints(shell);
    delete &(*v);
    set_number_of_vertices(number_of_vertices()-1);
  }
  return;
}

template < class Gt, class Tds >  
bool 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
is_valid(bool verbose, int level) const
{
  bool result = Constrained_triangulation::is_valid(verbose, level);
  CGAL_triangulation_assertion( result );

    Finite_faces_iterator fit= finite_faces_begin();
    for (; fit != finite_faces_end(); fit++) {
      for(int i=0;i<3;i++) {
	result = result && !is_flipable(fit,i);
	CGAL_triangulation_assertion( result );
      }
    }
    return result;
}

template < class Gt, class Tds >  
double
Constrained_Delaunay_triangulation_2<Gt, Tds>::
twice_area_of_triangle(const Point & p, const Point & q, const Point & r)
     // 2*area of  triangle pqr
     // !! le produit vectoriel de 2 vecteurs devrait exister
  //should be in traits class
{
  double pv; 
  pv = (p.x() - r.x())*(q.y() - r.y())  
    - (p.y() - r.y())*(q.x() - r.x()); 
  //  return abs((p.x() - r.x())*(q.y() - r.y()) 
  //       - (p.y() - r.y())*(q.x() - r.x())  ); 
  if (pv >= 0) {return pv;} 
  else {return -pv;} 
}

template < class Gt, class Tds >  
double
Constrained_Delaunay_triangulation_2<Gt, Tds>::
norm(const Point & p, const Point & q)
     // !!! in the kernel ???
{
  return  sqrt ( (p - q) * (p - q) );
}

template < class Gt, class Tds >  
double
Constrained_Delaunay_triangulation_2<Gt, Tds>::
aspect_ratio(const Point & p, const Point & q, const Point & r)
  // returns the sine of the smallest angle of triangle pqr 
  // to be defined in a traits class
  // to be replaced by kernel functions
{
  double area, sinp, sinq, sinr;

  area = twice_area_of_triangle(p,q,r); 
  sinr = area/(norm(r,p)*norm(r,q)); 
  sinp = area/(norm(p,r)*norm(p,q));
  sinq = area/(norm(q,p)*norm(q,r)); 
  return  min(min(sinp,sinq),min(sinp,sinr));
}

template < class Gt, class Tds >  
double
Constrained_Delaunay_triangulation_2<Gt, Tds>::
size(const Point & p, const Point & q, const Point & r)
     // returns the length of the longest edge of triangle pqr
     // to be defined in a traits class
{
  return  max(max(norm(r,p),norm(r,q)), max(norm(r,p),norm(p,q)));
}

template < class Gt, class Tds >  
bool
Constrained_Delaunay_triangulation_2<Gt, Tds>::
is_bad(Face_handle  f,  double lmax, double lmin, double angmin)
     // returns true if f is bounded and its aspect ratio < 1
     // to be defined in a traits class
{
  //double as;
  Point p,q,r;

  if (is_infinite(f)) {
    return false;
  }

  p=(f->vertex(0))->point();
  q=(f->vertex(1))->point();
  r=(f->vertex(2))->point();
  if ((norm(r,p) < lmin) && (norm(r,q) < lmin ) && (norm(p,q) < lmin)) {
    return false;
  }

  Point c=circumcenter(f);
  /*   double nn=c.x()*c.x()+c.y()*c.y(); */
  /*   nn = nn-lmax; */
  /*   if (nn <0) { nn=-nn;} */
  /*   return ( (aspect_ratio(p,q,r) < angmin) || (nn < size(p,q,r))); */

  return ( (aspect_ratio(p,q,r) < angmin) || (size(p,q,r) > lmax));
}

template < class Gt, class Tds >  
bool
Constrained_Delaunay_triangulation_2<Gt, Tds>::
is_gabriel(Face_handle  f, int i)
  // returns true if the interior of the circle that has e=(f,i)
  // as a diameter contains a vertex
  // returns false if (f,i) is an infinite edge
  // of the triangulation
  // Precondition : if (f,i) is an edge of the triangulation
  // f and f->neighbor(i) must be Delaunay faces
{
  Point a, cc;
  Vertex_handle vb, vc;
  bool ok1, ok2; // true when ci and ai are on the same side of (f,i)=[bc]
  Face_handle f2;
  Orientation orient, orient2;

  vb = f->vertex(cw(i)); // an endpoint of e
  vc = f->vertex(ccw(i)); // the other endpoint

  if (is_infinite(f)) {
    ok1 = true;
  }
  else {
    cc = circumcenter(f);
    a = (f->vertex(i))->point(); // the vertex of f1 not on e
    orient = geom_traits().orientation(vb->point(),vc->point(),a);
    orient2 = geom_traits().orientation(vb->point(),vc->point(),cc);
    if (orient == orient2) {ok1 = true;}
    else {ok1 = false;}
  }  

  f2 = f->neighbor(i);
  if (is_infinite(f2)) {
    ok2 = true;
  }
  else {
    cc = circumcenter(f2);
    a = (f2->vertex(f->mirror_index(i)))->point(); // the vertex of f2 not on e
    orient = geom_traits().orientation(vb->point(),vc->point(),a);
    orient2 = geom_traits().orientation(vb->point(),vc->point(),cc);
    if (orient == orient2) {ok2 = true;}
    else {ok2 = false;}
  }

  return(ok1 && ok2);
}

template < class Gt, class Tds >  
bool
Constrained_Delaunay_triangulation_2<Gt, Tds>::
is_in_diametral_circle(Vertex_handle va, Vertex_handle vb, const Point & p)
     // true if p lies inside the circle whose diameter is ab
{
  Point a=va->point();
  Point m=a+(vb->point()-a)/2; 
  if (squared_distance(p,m) <
      squared_distance(va->point(),m)) { 
    return true;
  }
  else {
    return false;
  }
}
      
template < class Gt, class Tds >  
Constrained_Delaunay_triangulation_2<Gt, Tds>::Vertex_handle
Constrained_Delaunay_triangulation_2<Gt, Tds>::
refine_edge(Face_handle & f, int & i,
	    List_edges & list_of_non_gabriel_constraints,
	    List_faces & set_of_bad_faces,
	    double lmax, double lmin, double angmin)
     // inserts the midpoint of edge ab and updates the sets of non Gabriel 
     // constraints and of bad triangles
     // returns the vertex v whose point is the midpoint of ab
     // the returned f is a face incident to v and i=f->index(v) 
  //???? a verifier que insert on edge fait bien ca
{
  Vertex_handle va, vb, v;
  Face_handle fv;
  int iv;
  Point midpoint_of_e;

  va = f->vertex(cw(i)); // endpoint of the constraint
  vb = f->vertex(ccw(i)); // the other endpoint
  midpoint_of_e = va->point() + (vb->point() - va->point())/2.0;
  v = special_insert_in_edge(midpoint_of_e, f,i);
  
  // updates list_of_non_gabriel_constraints 
  //  fv = v->incident_faces(); // distinct from f ???
  // iv = fv->index(v);  // distinct from i ???

  Face_circulator face_circ=v->incident_faces(), done(face_circ);  

  do {
    fv = face_circ->handle();
    iv = fv->index(v);  
    if ((fv->vertex(cw(iv)) == va) || (fv->vertex(cw(iv)) == vb)) {
      if (!is_gabriel(fv,ccw(iv))) {
	list_of_non_gabriel_constraints.push_back(Edge(fv,ccw(iv)));
      }
    }
    if (!is_gabriel(fv, iv) && fv->is_constrained(iv)) { // ??? utile ?
      list_of_non_gabriel_constraints.push_back(Edge(fv, iv));
    }
    ++face_circ;
  } while (face_circ != done);

  // inserts in set_of_bad_faces the faces that become bad
  // (they are all incident to v)

  do {
    if (is_bad(face_circ, lmax, lmin, angmin)) {
      set_of_bad_faces.push_back(face_circ->handle());
    }
    ++face_circ;
  } while (face_circ != done);

  return v;
}

template < class Gt, class Tds >  
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
refine_face(Face_handle & f,
	    List_edges & list_of_non_gabriel_constraints,
	    List_faces & set_of_bad_faces,
	    double lmax, double lmin, double angmin)
     // inserts the circumcenter c of face f if this does not introduce new
     // non Gabriel edges
     // otherwise the midpoints of these edges are inserted
     // the set of non Gabriel constraints and of bad triangles
     // are updated
{
  Point c;
  Vertex_handle vc, vm;
  Face_handle ff(f);
  int ic;
  Edge current_constraint;
  List_edges hole_edges;

  c=circumcenter(f);
  find_conflicts(c, hole_edges, f);

  List_edges::iterator edgeit(hole_edges.begin());
  while (edgeit != hole_edges.end()) {
    ff = (*edgeit).first;
    ic = (*edgeit).second;
    //    if ( (ff->is_constrained(ic)) && (!(is_gabriel(ff,ic))) ) {
    if ( (ff->is_constrained(ic)) && 
	 (is_in_diametral_circle
	  (ff->vertex(cw(ic)), ff->vertex(ccw(ic)),c ))) {
      list_of_non_gabriel_constraints.push_back(Edge(ff,ic));
    }
    ++edgeit;
  } 

  if (!(list_of_non_gabriel_constraints.empty())) {
    do {
      current_constraint=list_of_non_gabriel_constraints.front();
      ff = current_constraint.first; // necessary before remove
      ic = current_constraint.second; // necessary before remove
      list_of_non_gabriel_constraints.pop_front();
      //    if (!(is_gabriel(ff,ic))) {
      if( ff->is_constrained(ic) &&  
	  is_in_diametral_circle(ff->vertex(cw(ic)), ff->vertex(ccw(ic)),c )) {
	vm=refine_edge(ff, ic,
		       list_of_non_gabriel_constraints,
		       set_of_bad_faces,
		       lmax, lmin, angmin);
      }
    } while (!(list_of_non_gabriel_constraints.empty()));
  }
  else {
    // inserts in set_of_bad_faces the faces that become bad
    // (they are all incident to c)
    vc = insert(c);
    Face_circulator face_circ(vc->incident_faces()), done(face_circ);
    do {
      if (is_bad(face_circ, lmax, lmin, angmin)) {
	set_of_bad_faces.push_back(face_circ->handle());
      }
      ++face_circ;
    } while (face_circ != done);
  }
}

template < class Gt, class Tds >  
inline void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
conform(List_edges & list_of_non_gabriel_constraints,
	double lmax, double lmin, double angmin)
{
  List_faces set_of_bad_faces;
  conform(list_of_non_gabriel_constraints, set_of_bad_faces,
			  lmax, lmin, angmin);
}

template < class Gt, class Tds >  
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
conform(List_edges & list_of_non_gabriel_constraints,
	List_faces & set_of_bad_faces,
	double lmax, double lmin, double angmin)
  // recursively splits the edges in list_of_non_gabriel_constraints
  // into two halfsegments until the circumscribing circle of each
  // subsegment is empty (i.e. are gabriel edges) all the subsegments
  // become constrained edges 
  // the set of bad triangles is updated
{
  Face_handle f;
  Vertex_handle v;
  int i;
  Edge current_constraint;

  while (!(list_of_non_gabriel_constraints.empty())) {  
    current_constraint = list_of_non_gabriel_constraints.front();
    list_of_non_gabriel_constraints.pop_front(); 
    f = current_constraint.first;
    i = current_constraint.second; 
    if (is_edge(f->vertex(cw(i)), f->vertex(ccw(i))) 
	&& f->is_constrained(i)
	// because of insertions (f,i) may not be 
	// an edge nor a constrained edge
	&& (!is_gabriel(f,i))) { 
      v=refine_edge(f,i,list_of_non_gabriel_constraints,
		    set_of_bad_faces, lmax, lmin, angmin); 
    }
  }
}

template < class Gt, class Tds >  
void 
Constrained_Delaunay_triangulation_2<Gt, Tds>::
refine(List_edges & list_of_constraints,
       double lmax, double lmin, double angmin)
     // makes all edges in list_of_constraints Gabriel edges and refine 
     // all bad faces
{
  List_faces set_of_bad_faces; // a remplacer par un set avec
  // comparaison basee sur l'aspect ratio
  List_edges list_of_non_gabriel_constraints;
  Face_iterator face_it=faces_begin(); 
  Face_handle f;
  List_edges :: iterator constraint_it=list_of_constraints.begin();

  // init. list_of_non_gabriel_constraints

  while(constraint_it != list_of_constraints.end()) {
    if (!is_gabriel((*constraint_it).first, (*constraint_it).second)) {
      list_of_non_gabriel_constraints.push_back(*constraint_it);
    }
    ++constraint_it;
  }
  conform(list_of_non_gabriel_constraints, set_of_bad_faces, lmax,
	  lmin, angmin);

  // init. list of bad faces

  while (face_it != faces_end()) { 

    if (is_bad(face_it, lmax, lmin, angmin)) {
      set_of_bad_faces.push_back(face_it);
    }
    ++face_it;
  }

  // refine all bad triangles

   while (!(set_of_bad_faces.empty())) {
     //std::cerr << set_of_bad_faces.size() << std::endl;
     f=set_of_bad_faces.front();
     set_of_bad_faces.pop_front();
     if (is_bad(f, lmax, lmin, angmin)) {
       refine_face(f, list_of_non_gabriel_constraints, set_of_bad_faces, 
		   lmax, lmin, angmin);
     }
   }
}


CGAL_END_NAMESPACE
#endif // CGAL_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H
