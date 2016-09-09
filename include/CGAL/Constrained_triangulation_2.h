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
// file          : include/CGAL/Constrained_triangulation_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Constrained_triangulation_2.h,v $
// revision      : $Revision: 1.39 $
// revision_date : $Date: 2000/07/06 13:27:26 $
// author(s)     : Mariette Yvinec, Jean Daniel Boissonnat
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_TRIANGULATION_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_2_H

// #include <utility>
// #include <list>
// #include <map> 
#include <set>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_2.h> 
#include <CGAL/Constrained_triangulation_face_base_2.h>
#include <CGAL/Constrained_triangulation_sweep_2.h>

CGAL_BEGIN_NAMESPACE
template < class Gt, class Tds>
class Constrained_triangulation_2  : public Triangulation_2<Gt,Tds>
{
  friend Constrained_triangulation_sweep_2<Gt,Tds>;
  //friend Constrained_triangulation_sweep_2<Gt,Tds>::Neighbor_list;
public:
  typedef Triangulation_2<Gt,Tds> Triangulation;
  typedef Constrained_triangulation_2<Gt,Tds>  Constrained_triangulation;
  typedef Constrained_triangulation_sweep_2<Gt,Tds>  Sweep;
  
  typedef typename Triangulation::Edge Edge;
  typedef typename Triangulation::Vertex Vertex;
  typedef typename Triangulation::Vertex_handle Vertex_handle;
  typedef typename Triangulation::Face_handle Face_handle;
  typedef typename Triangulation::Locate_type Locate_type;
  typedef typename Triangulation::Face_circulator Face_circulator;
  typedef typename Triangulation::Edge_circulator Edge_circulator;
  typedef typename Triangulation::Vertex_circulator Vertex_circulator;
  typedef typename Triangulation::Line_face_circulator Line_face_circulator;
  

  typedef Gt Geom_traits;
  typedef typename Geom_traits::Point_2      Point;
  typedef typename Geom_traits::Segment_2    Segment;
  typedef std::pair<Point,Point>             Constraint;
  typedef std::list<Edge>                    List_edges;
  typedef std::list<Face_handle>             List_faces;
  typedef std::list<Vertex_handle>           List_vertices;

  //nouveau 
  class Less_edge;
  typedef std::set<Edge,Less_edge> Edge_set;
  //nouveau

  Constrained_triangulation_2(const Gt& gt=Gt()) : Triangulation() { }

  Constrained_triangulation_2(const Constrained_triangulation_2& ct)
    : Triangulation(ct) {}

  Constrained_triangulation_2(std::list<Constraint>& lc, const Gt& gt=Gt())
      : Triangulation_2<Gt,Tds>(gt)
  {
    //Sweep sweep(this,lc);
    //sweep is momentaneously broken
    typename std::list<Constraint>::iterator lcit=lc.begin();
    for( ;lcit != lc.end(); lcit++) {
      insert( (*lcit).first, (*lcit).second);
    }
     CGAL_triangulation_postcondition( is_valid() );
  }

  template<class InputIterator>
  Constrained_triangulation_2(InputIterator first,
			      InputIterator last,
			      const Gt& gt=Gt() )
     : Triangulation_2<Gt,Tds>(gt)
  {
     //  std::list<Constraint> lc;
//       while(first != last){
//           lc.push_back(*first++);
//       }
//       Sweep sweep(this,lc);
    while( first != last){
      insert((*first).first, (*first).second);
      ++first;
    }
      CGAL_triangulation_postcondition( is_valid() );
  }

  // INSERTION
  Vertex_handle insert(Point a);
  Vertex_handle special_insert_in_edge(const Point & a, Face_handle f, int i);
  void insert(Point a, Point b);
  void insert(const Vertex_handle & va, const Vertex_handle & vb);
  void insert(const Vertex_handle & va, const Vertex_handle & vb,
		     Face_handle & fr, int & i);
  void insert(const Vertex_handle & va, const Vertex_handle & vb,
	      Face_handle & fr, int & i, 
	      List_edges & new_edges);
  
  void remove(Vertex_handle  v);
  void remove_constraint(Face_handle f, int i);

  Vertex_handle find_intersected_faces(Vertex_handle va, 
				 Vertex_handle vb,
				 Vertex_handle vaa,
				 List_faces & intersected_faces,
				 List_edges & list_ab, 
				 List_edges & list_ba);
  void triangulate(List_edges & list_edges); 
  void triangulate(List_edges & list_edges, 
		   List_edges & new_edges);

  class Less_edge 
    :  public std::binary_function<Edge, Edge, bool>
  {
  public:
    Less_edge() {}
    bool operator() (const Edge& e1, const Edge& e2) const
      {
	int ind1=e1.second, ind2=e2.second;
 	return( (&(*e1.first) < &(*e2.first))
 		|| ( (&(*e1.first) == &(*e2.first)) && (ind1 < ind2)));
      } 
  };


  void file_output(std::ostream& os) const;

protected:
  void update_constraints_incident(Vertex_handle va, 
				   Vertex_handle c1,
				   Vertex_handle c2);
  void clear_constraints_incident(Vertex_handle va);
  void update_constraints_opposite(Vertex_handle va);
  void update_constraints(const std::list<Edge> &hole);

  void remove_1D(Vertex_handle v);
  void remove_2D(Vertex_handle v);
};
    



template < class Gt, class Tds >
Constrained_triangulation_2<Gt,Tds>::Vertex_handle
Constrained_triangulation_2<Gt,Tds>::
insert(Point a)
// inserts point a 
// in addition to what is done for non constrained triangulations
// constrained edges are updated
{
  Vertex_handle va;
  Vertex_handle c1,c2;
  Face_handle loc;
  int li;
  Locate_type lt;
  bool insert_in_constrained_edge = false;

  loc = locate(a, lt, li);
  if ( lt == EDGE && loc->is_constrained(li) ){
    insert_in_constrained_edge = true;
    c1=loc->vertex(ccw(li)); //endpoint of the constraint
    c2=loc->vertex(cw(li)); // endpoint of the constraint
  }
  
  va = Triangulation::insert(a,lt,loc,li);
  if (insert_in_constrained_edge) update_constraints_incident(va, c1,c2);
  else if(lt != VERTEX) clear_constraints_incident(va);
  if (dimension() == 2) update_constraints_opposite(va);
  return va;
}

template < class Gt, class Tds >  
Constrained_triangulation_2<Gt, Tds>::Vertex_handle 
Constrained_triangulation_2<Gt, Tds>::
special_insert_in_edge(const Point & a, Face_handle f, int i)
  // insert  point p in edge(f,i)
  // bypass the precondition for point a to be in edge(f,i)
  // update constrained status
{
  Vertex_handle va;
  Vertex_handle c1,c2;
  c1 = f->vertex(cw(i));  //endpoint of edge
  c2 = f->vertex(ccw(i)); //endpoint of edge
  bool insert_in_constrained_edge = f->is_constrained(i);
 
  va = static_cast<Vertex*> (_tds.insert_in_edge(&(*f), i));
  va->set_point(a);

  if (insert_in_constrained_edge) update_constraints_incident(va, c1,c2);
  else clear_constraints_incident(va);
  if (dimension() == 2) update_constraints_opposite(va);
  return va;
}


template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
update_constraints_incident(Vertex_handle va, 
			    Vertex_handle c1,
			    Vertex_handle c2)
  // update status of edges incident to a 
  // after insertion in the  constrained edge c1c2
{
  if (dimension() == 0) return;
  if (dimension()== 1) {
    Edge_circulator ec=va->incident_edges(), done(ec);
    do {
      ((*ec).first)->set_constraint(2,true);
    }while (++ec != done);
  }
  else{
    //dimension() ==2
    int cwi, ccwi, indf;
    Face_circulator fc=va->incident_faces(), done(fc);  
    CGAL_triangulation_assertion(fc != 0);
    do {
      indf = fc->index(va);
      cwi=cw(indf);
      ccwi=ccw(indf); 
      if ((fc->vertex(cwi) == c1)||(fc->vertex(cwi) == c2)) {
	  fc->set_constraint(ccwi,true);
	  fc->set_constraint(cwi,false);
	}	
	else {
	  fc->set_constraint(ccwi,false);
	  fc->set_constraint(cwi,true);
	}
	++fc;
      } while (fc != done);
  }
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
clear_constraints_incident(Vertex_handle va)
// make the edges incident to a newly created vertex unconstrained
{
 Edge_circulator ec=va->incident_edges(), done(ec);
 Face_handle f;
 int indf;
  if ( ec != 0){
    do {
      f = (*ec).first ;
      indf = (*ec).second;
      f->set_constraint(indf,false);
      if (dimension() == 2) {
	f->neighbor(indf)->set_constraint(f->mirror_index(indf),false);
      }
    } while (++ec != done);
  }
  return;
}


template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::  
update_constraints_opposite(Vertex_handle va)
  // update status of edges opposite to a
  // after insertion of a
{
  CGAL_triangulation_assertion(dimension()==2); 
  Face_handle f=va->face(), start=f;
  int indf;
  do {
    indf = f->index(va);
    if (f->neighbor(indf)->is_constrained(f->mirror_index(indf)) ) {
      f->set_constraint(indf,true);
    }
    else {
      f->set_constraint(indf,false);
    }
    f= f->neighbor(ccw(indf)); // turns ccw around va 
  } while (f != start);
  return;
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>:: 
update_constraints( const std::list<Edge> &hole)
{
  typename std::list<Edge>::const_iterator it = hole.begin();
  Face_handle f;
  int i;
  for ( ; it != hole.end(); it ++) {
    f =(*it).first;
    i = (*it).second;
    if ( f->is_constrained(i) ) 
      (f->neighbor(i))->set_constraint(f->mirror_index(i),true);
    else (f->neighbor(i))->set_constraint(f->mirror_index(i),false);
  }
}


template < class Gt, class Tds >
inline void
Constrained_triangulation_2<Gt,Tds>::
insert(Point a, Point b)
// the algorithm first inserts a and b, then walks in t along ab, removes
// the triangles crossed by ab and creates new ones
// if a vertex c of t lies on segment ab, constraint ab is replaced by the
// two constraints ac and cb 
// apart from the insertion of a and b, the algorithm runs in time 
// proportionnal to the number of removed triangles
{
  Vertex_handle va= insert(a);
  Vertex_handle vb= insert(b);
  insert(va, vb);
}

template < class Gt, class Tds >
inline void
Constrained_triangulation_2<Gt,Tds>::
insert(const Vertex_handle & va, const Vertex_handle & vb)
// Precondition va != vb
{
  List_edges new_edges;
  Face_handle fr;
  int i;
  insert(va, vb, fr, i, new_edges);
}

template < class Gt, class Tds >
inline void
Constrained_triangulation_2<Gt,Tds>::
insert(const Vertex_handle & va, 
       const Vertex_handle & vb,
       Face_handle & fr, int & i)
{
  List_edges new_edges;
  insert(va, vb, fr, i, new_edges);
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
insert(const Vertex_handle & va, 
       const Vertex_handle & vb,
       Face_handle & fr, int & i, 
       List_edges & new_edges)
  // Inserts line segment ab as a constraint (i.e. an edge) in
  // triangulation t
  // Precondition : the algorithm assumes that a and b are vertices of t
  // walks in t along ab, removes the triangles intersected by ab and
  // creates new ones
  // fr is the face incident to edge ab and to the right  of ab
  // edge ab=(fr,i).
  // new_edges will contain in the end 
  // all the new edges 
  // to be used e.g. by propagating flip 
  // for Delaunay constrained triangulation
  // The algorithm runs in time proportionnal to the number 
  // of removed triangles
{
  Vertex_handle vaa=va, vbb=va;
  Face_handle fl;
  List_faces faces_to_be_removed;
      
  while (vbb != vb) {
    vaa = vbb;

    // case where ab contains an edge of t incident to a
    if(includes_edge(vaa,vb,vbb,fr,i)) {
      if (dimension()==1) fr->set_constraint(2, true);
      else{
	fr->set_constraint(i,true);
	fr->neighbor(i)->set_constraint(fr->mirror_index(i),true);
      }
    }
    else {
      // ab does not contain an edge of t incident to a
      // finds all triangles intersected by ab (in conflict)
      List_faces intersected_faces;
      List_edges conflict_boundary_ab, conflict_boundary_ba;
      vbb = find_intersected_faces(va, vb, vaa,
				   intersected_faces,
				   conflict_boundary_ab,
				   conflict_boundary_ba);

      // skip if the lists are empty : the first crossed edge is a constraint
      if ( !conflict_boundary_ab.empty() ) {
	triangulate(conflict_boundary_ab, new_edges);
	triangulate(conflict_boundary_ba, new_edges);
	
	// the two faces that share edge ab are neighbors
	// their common edge ab is a constraint
	fl=(*conflict_boundary_ab.begin()).first;
	fr=(*conflict_boundary_ba.begin()).first;
	fl->set_neighbor(2, fr);
	fr->set_neighbor(2, fl);
	fl->set_constraint(2, true);
	fr->set_constraint(2, true);
	i=2;

	// delete faces to be removed
	while( ! intersected_faces.empty()) {
	  fl = intersected_faces.front();
	  intersected_faces.pop_front();
	  delete_face(fl);
	}
      }
    }
  }
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
remove(Vertex_handle  v)
{
  CGAL_triangulation_precondition( ! v.is_null() );
  CGAL_triangulation_precondition( !is_infinite(v));
    
  if  (number_of_vertices() == 1)     remove_first(v);
  else if (number_of_vertices() == 2) remove_second(v);
  else   if ( dimension() == 1) remove_1D(v);
  else  remove_2D(v);
  return;
}


template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
remove_1D(Vertex_handle  v)
{
  Edge_circulator ec = incident_edges(v), done(ec);
  do {
    (*ec).first->set_constraint(2,false);
  } while (++ec != done);
  Triangulation::remove_1D(v);
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
remove_2D(Vertex_handle v)
  // remove a vertex and updates the constrained edges of the new faces
  // all constraints incident to the removed vertex are removed
{
  if (test_dim_down(v)) {_tds.remove_dim_down(&(*v));}
  else {
    std::list<Edge> hole;
    make_hole(v, hole);
    std::list<Edge> shell=hole; //because hole will be emptied by fill_hole
    fill_hole(v, hole);
    update_constraints(shell);
    delete &(*v);
    set_number_of_vertices(number_of_vertices()-1);
  }
  return;       
}


template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
remove_constraint(Face_handle f, int i)
{
  f->set_constraint(i, false);
  if (dimension() == 2)
    (f->neighbor(i))->set_constraint(f->mirror_index(i), false);
  return;
}
    
template < class Gt, class Tds >
Constrained_triangulation_2<Gt,Tds>::Vertex_handle 
Constrained_triangulation_2<Gt,Tds>::
find_intersected_faces(Vertex_handle va, 
		       Vertex_handle  vb,
		       Vertex_handle vaa,
		       List_faces & intersected_faces,
		       List_edges & list_ab, 
		       List_edges & list_ba)
  // finds all triangles intersected the current part of constraint ab
  // vaa is the vertex at the begin of the current part
  // the procedure returns the vertex vbb at the end of the current part
  // If segment ab contains a vertex c, 
  // c becomes the new vertex vbb and 
  // only triangles intersected by ac are reported.
  // 
  // Returns also the boundary B of the union 
  // of intersected triangles oriented cw
  // B is represented by two lists of edges list_ab and list_ba 
  // list_ab consists of the edges from a to b (i.e. on the left of a->b)
  // list_ba    "         "        from b to a (i.e. on the right of a->b)
  // an element of the lists (an edge e) is represented as the edge of
  // the triangle incident to e that is not intersected by ab
{
  Point a=va->point(), b=vb->point();
  Line_face_circulator current_face=line_walk(vaa->point(),b, vaa->face());
  int ind=current_face->index(vaa);
  assert( !current_face->is_constrained(ind));
  Vertex_handle vbb=vb;
  Face_handle lf= current_face->neighbor(ccw(ind)); 
  Face_handle rf= current_face->neighbor(cw(ind));
  Orientation orient;
  Face_handle previous_face;
  Vertex_handle current_vertex;	

  list_ab.push_back(Edge(lf, lf->index(current_face)));
  list_ba.push_front(Edge(rf, rf->index(current_face)));
  intersected_faces.push_front(current_face);
  
  // init
  previous_face=current_face; 
  ++current_face;
  ind=current_face->index(previous_face);  
  current_vertex=current_face->vertex(ind);  

  // loop over triangles intersected by ab
  while (current_vertex != vbb)  { 
    orient = orientation(a,b,current_vertex->point());
    int i1, i2;
    switch (orient) {
    case COLLINEAR :  
      vbb=current_vertex; // new endpoint of the constraint
      break;
    case LEFTTURN :
    case RIGHTTURN :
      if (orient == LEFTTURN) {
	i1 = ccw(ind) ; //index of second intersected edge of current_face
	i2 = cw(ind); //index of non intersected edge of current_face
      }
      else {
	i1 = cw(ind) ; //index of second intersected edge of current_face
	i2 = ccw(ind); //index of non intersected edge of current_face
      }

      assert( !current_face->is_constrained(i1));
      lf= current_face->neighbor(i2);
      intersected_faces.push_front(current_face);
      if (orient == LEFTTURN) 
	list_ab.push_back(Edge(lf, lf->index(current_face)));
      else // orient == RIGHTTURN
	list_ba.push_front(Edge(lf, lf->index(current_face)));
      previous_face=current_face;
      ++current_face;
      ind=current_face->index(previous_face); 
      current_vertex=current_face->vertex(ind);
      break;
    }
  }
    
  // last triangle (having vbb as a vertex)
  intersected_faces.push_front(current_face);
  lf= current_face->neighbor(cw(ind));
  list_ab.push_back(Edge(lf, lf->index(current_face))); 
  rf= current_face->neighbor(ccw(ind));
  list_ba.push_front(Edge(rf, rf->index(current_face)));
  return vbb;
}


template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
triangulate(List_edges & list_edges)
  // triangulates the  polygon whose boundary consists of list_edges
  // plus the edge ab joining the two endpoints of list_edges
  // the orientation of the polygon (as provided by list_edges) must
  // be cw
  // the edges of list_edges are assumed to be edges of a
  // triangulation that will be updated by the procedure
  // the faces intersecting ab are put in the list faces_to_be_removed
  // takes linear time
{
  List_edges new_edges;
  triangulate(list_edges, new_edges);
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt,Tds>::
triangulate(List_edges & list_edges,  List_edges & new_edges)
  // triangulates the  polygon whose boundary consists of list_edges
  // plus the edge ab joining the two endpoints of list_edges
  // the orientation of the polygon (as provided by list_edges) must
  // be cw
  // the edges of list_edges are assumed to be edges of a
  // triangulation that will be updated by the procedure
  // the edges that are created are put in list new_edges
  // takes linear time
{
  Vertex_handle va,vb; // first and last vertices of list_edges 
  Face_handle newlf;
  Face_handle n1,n2,n;
  int ind1, ind2,ind;
  Orientation orient;
    
  typename List_edges::iterator current, next, tempo;
  current=list_edges.begin();
  tempo=list_edges.end(); 
  --tempo; 

  va=((*current).first)->vertex(ccw((*current).second));
  vb=((*tempo).first)->vertex(cw((*tempo).second));
  next=current; 
  ++next;

  do
    {
      n1=(*current).first;
      ind1=(*current).second;
      // in case n1 is no longer a triangle of the new triangulation
      if (!((n1->neighbor(ind1)).is_null())) {
	n=n1->neighbor(ind1);
	//ind=n1->mirror_index(ind1); 
	// mirror_index does not work in this case
	ind = cw(n->index(n1->vertex(cw(ind1))));
	n1=n->neighbor(ind); 
	ind1= n->mirror_index(ind);
      }
      n2=(*next).first;
      ind2=(*next).second;
      // in case n2 is no longer a triangle of the new triangulation
      if (!((n2->neighbor(ind2)).is_null())) {
	n=n2->neighbor(ind2); 
	// ind=n2->mirror_index(ind2);
	// mirror_index does not work in this case
	ind = cw(n->index(n2->vertex(cw(ind2))));
	n2=n->neighbor(ind); 
	ind2= n->mirror_index(ind);
      }

      Vertex_handle v0=n1->vertex(ccw(ind1));
      Vertex_handle v1=n1->vertex(cw(ind1));
      Vertex_handle v2=n2->vertex(cw(ind2));
      orient= orientation(v0->point(),v1->point(),v2->point());
      switch (orient) {
      case RIGHTTURN : 	  		
	// creates the new triangle v0v1v2
	// updates the neighbors, the constraints 
	//and the list of new edges
	newlf = create_face(v0,v2,v1);
	new_edges.push_back(Edge(newlf,2));
	newlf->set_neighbor(1, n1);
	newlf->set_neighbor(0, n2);
	n1->set_neighbor(ind1, newlf);
	n2->set_neighbor(ind2, newlf);
	if (n1->is_constrained(ind1)) {
	  newlf->set_constraint(1,true);
	}
	if (n2->is_constrained(ind2)) {
	  newlf->set_constraint(0,true);
	}
	// v0, v1 or v2.face() may have been removed
	v0->set_face(newlf); 
	v1->set_face(newlf);
	v2->set_face(newlf);
	// update list_edges
	tempo=current;
	current=list_edges.insert(current, Edge(newlf,2));
	list_edges.erase(tempo);
	list_edges.erase(next);
	next=current;
	if (v0 != va) {--current;} 
	else {++next;} 
	break;
      case LEFTTURN : 	  
	++current; ++next;
	break;
      case COLLINEAR : 
	++current; ++next;
	break;
      }
    } while (list_edges.size()>1);
}

template < class Gt, class Tds >
void
Constrained_triangulation_2<Gt, Tds>::
file_output(std::ostream& os) const
{
  Triangulation_2<Gt, Tds>::file_output(os);

  // write constrained status
  typename Tds::Iterator_base ib = _tds.iterator_base_begin();
  for( ; ib != _tds.iterator_base_end(); ++ib) {
    for(int j = 0; j < 3; ++j){
      if (ib->is_constrained(j)) { os << "C";}
      else { os << "N";}
      if(is_ascii(os)){
	if(j==2) {
	  os << "\n";
	} else {
	  os <<  ' ';
	}
      }
    }
  }
}

template < class Gt, class Tds >
std::ostream &
operator<<(std::ostream& os, const Constrained_triangulation_2<Gt,Tds> &ct)
{
  ct.file_output(os);
  return os ;
}


CGAL_END_NAMESPACE

#endif //CGAL_CONSTRAINED_TRIANGULATION_2_H



