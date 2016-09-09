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
// file          : include/CGAL/Alpha_shape_2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: Alpha_shape_2.h,v $
// revision      : $Revision: 1.15 $
// revision_date : $Date: 2000/07/11 15:52:09 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ALPHA_SHAPE_2_H
#define CGAL_ALPHA_SHAPE_2_H

#ifdef CGAL_STL_SGI_CC
#define STL_HASH_TABLES
#endif

#include <CGAL/basic.h>

// SGI MIPSpro C++ 7.x
#ifdef STL_HASH_TABLES
#include <hash_set>
#include <hash_map>
#include <map>
#else
#include <set>
#include <map>
#endif

#include <vector>

#include <algorithm>
#include <utility>
#include <iostream>

#ifdef CGAL_ALPHA_WINDOW_STREAM
#include <CGAL/IO/Window_stream.h>
#endif

#include <CGAL/less_partial.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template < class Dt >
class Alpha_shape_2 : public Dt 
{
  // DEFINITION The class Alpha_shape_2<Dt> represents the family
  // of alpha-shapes of points in a plane for all positive alpha. It
  // maintains the underlying Delaunay triangulation which represents
  // connectivity and order among its faces. Each k-dimensional face of the
  // Delaunay triangulation is associated with an interval that specifies
  // for which values of alpha the face belongs to the alpha-shape (sorted
  // linear arrays resp. multimaps or interval trees). There are links
  // between the intervals and the k-dimensional faces of the Delaunay
  // triangulation (multimaps resp. std::hashtables).
  //

  //------------------------- TYPES ------------------------------------

public:
  typedef typename Dt::Geom_traits Gt;
  typedef typename Dt::Triangulation_data_structure Tds;

  typedef typename Gt::Coord_type Coord_type;
  typedef typename Gt::Point Point;

  typedef typename Gt::Ray Ray;
  typedef typename Gt::Line Line;
  typedef typename Gt::Direction Direction;

  typedef typename Dt::Face_handle Face_handle;
  typedef typename Dt::Vertex_handle Vertex_handle;
  typedef typename Dt::Edge Edge;

  typedef typename Dt::Face_circulator Face_circulator;
  typedef typename Dt::Edge_circulator Edge_circulator;
  typedef typename Dt::Vertex_circulator Vertex_circulator;

  typedef typename Dt::Face_iterator Face_iterator;
  typedef typename Dt::Edge_iterator Edge_iterator;
  typedef typename Dt::Vertex_iterator Vertex_iterator;

  typedef typename Dt::Locate_type Locate_type;

private:

#ifndef STL_HASH_TABLES
  typedef long Key;
#else
  // hash_map seem only to work with build-in functions
  // thus cast to long TBC
  typedef long Key;
#endif
 
  typedef std::pair< Coord_type, Face_handle > Interval_face;
  typedef std::vector< Interval_face > Interval_face_map;

  // CC sun cannot handle Face_handle, only void* for map
  // gcc and CC irix ok
  // value_type is defined to be const
  // key must be const
  // this holds only for find and insert but not for the operator[]

  // it is faster to compute the radius directly
  // #ifndef STL_HASH_TABLES
  // typedef std::map< Key, Coord_type, std::less<Key> > 
  //                                           Face_interval_map;
  // #else
  // typedef std::hash_map< Key , Coord_type > Face_interval_map;
  // #endif

  // triple causes under certian conditions a CC sun complier problem
  typedef typename Tds::Face Face_tds;
  typedef typename Face_tds::Face Face_base;
  typedef typename Face_base::Interval_3 Interval3;

  typedef std::pair< Interval3, Edge > Interval_edge;
  typedef std::vector< Interval_edge > Interval_edge_map;

  typedef std::pair< Coord_type, Coord_type > Interval2;
  typedef std::pair< Interval2, Vertex_handle > Interval_vertex;
  typedef std::vector< Interval_vertex > Interval_vertex_map;

  typedef Face_handle const const_void;
  typedef std::pair<const_void, int> const_Edge;

  typedef std::vector< Coord_type > Alpha_spectrum;
  
  typedef typename Gt::Segment Segment;
  typedef std::vector<Segment> Vect_seg;

#ifndef STL_HASH_TABLES
  typedef std::set< Key, std::less<Key> > Marked_face_set;
#else
  typedef std::hash_set< Key > Marked_face_set;
#endif

public:

  typedef typename Alpha_spectrum::const_iterator Alpha_iterator;
  // An iterator that allow to traverse the sorted sequence of
  // different alpha-values. The iterator is bidirectional and
  // non-mutable. Its value-type is Coord_type

  enum Classification_type {EXTERIOR, SINGULAR, REGULAR, INTERIOR};
  // Distinguishes the different cases for classifying a
  // k-dimensional face of the underlying Delaunay triangulation of
  // the alpha-shape.
  // 
  // `EXTERIOR' if the face does not belong to the alpha-complex.
  // 
  // `SINGULAR' if the face belongs to the boundary of the
  // alpha-shape, but is not incident to any higher-dimensional
  // face of the alpha-complex
  // 
  // `REGULAR' if face belongs to the boundary of the alpha-shape
  // and is incident to a higher-dimensional face of the
  // alpha-complex
  // 
  // `INTERIOR' if the face belongs to the alpha-complex, but does
  // not belong to the boundary of the alpha-shape

  enum Mode {GENERAL, REGULARIZED};
  // In general, an alpha shape is a non-connected, mixed-dimension
  // polygon. Its regularized version is formed by the set of
  // regular edges and their vertices

  //------------------------ private VARIABLES -------------------------

private:

  // only finite edges and faces are inserted into the maps 
  Interval_face_map _interval_face_map;
  Interval_edge_map _interval_edge_map;
  Interval_vertex_map _interval_vertex_map;

  Alpha_spectrum _alpha_spectrum;
 
  Coord_type _alpha;
  Mode _mode;
  // should be constants
  Coord_type INFINITY;
  Coord_type UNDEFINED;

public:

  //------------------------- CONSTRUCTORS ------------------------------
 
  // Introduces an empty alpha-shape `A' for a positive
  // alpha-value `alpha'. Precondition: `alpha' >= 0.
  Alpha_shape_2(Coord_type alpha = Coord_type(0), 
		Mode m = GENERAL)
    : _alpha(alpha), _mode(m), INFINITY(-1), UNDEFINED(-2) 
    {}
 
// Introduces an alpha-shape `A' for a positive alpha-value
  // `alpha' that is initialized with the points in the range
  // from first to last

  template <class InputIterator>
  Alpha_shape_2( InputIterator first,  
		 InputIterator last,  
		 const Coord_type& alpha = Coord_type(0),
		 Mode = GENERAL) 
    {
      if (Dt::insert(first, last) >= 4)
	{
	  // Compute the associated _interval_face_map
	  initialize_interval_face_map();

	  // Compute the associated _interval_edge_map
	  initialize_interval_edge_map();
   
	  // Compute the associated _interval_vertex_map
	  initialize_interval_vertex_map();

	  // merge the two maps
	  initialize_alpha_spectrum();
	}
    }
 
public:

//----------- OUTPUT POINTS CONNECTED BY PAIRS ----------------------

#if defined(LIST) || defined(__SGI_STL_LIST)
std::list<Point> Output();
#endif //LIST
 
std::ostream& op_ostream(std::ostream& os) const;

Vect_seg& op_vect_seg(Vect_seg& V) const;
  
#ifdef CGAL_ALPHA_WINDOW_STREAM
Window_stream& op_window(Window_stream& W) const;
#endif 
 
//----------------------- OPERATIONS ---------------------------------

// Introduces an alpha-shape `A' for a positive alpha-value
// `alpha' that is initialized with the points in the range
// from first to last

template < class InputIterator >  
int make_alpha_shape(InputIterator first,  
		     InputIterator last) 
{

  clear();

  int n =  Dt::insert(first, last);
 
#ifdef DEBUG
  std::cout << "Triangulation computed" << std::endl;
#endif
  if (n >= 4)
    {   
      // Compute the associated _interval_face_map
      initialize_interval_face_map();

      // Compute the associated _interval_edge_map
      initialize_interval_edge_map();

      // Compute the associated _interval_vertex_map
      initialize_interval_vertex_map();
  
      // merge the two maps
      initialize_alpha_spectrum();
    }
  return n;
}

private :

//--------------------- INITIALIZATION OF PRIVATE MEMBERS -----------

void initialize_interval_face_map(void);

void initialize_interval_edge_map(void);

void initialize_interval_vertex_map(void);

void initialize_alpha_spectrum(void);

//---------------------------------------------------------------------

public:

void clear() 
{
  // clears the structure
  Dt::clear();

  _interval_face_map.erase(_interval_face_map.begin(),
			   _interval_face_map.end());
  _interval_edge_map.erase(_interval_edge_map.begin(),
			   _interval_edge_map.end());
  _interval_vertex_map.erase(_interval_vertex_map.begin(),
			     _interval_vertex_map.end());
    
  _alpha_spectrum.erase(_alpha_spectrum.begin(),
			_alpha_spectrum.end());
    
  // _face_interval_map.erase(_face_interval_map.begin(),
  // _face_interval_map.end());
  // _edge_interval_map.erase(_edge_interval_map.begin(),
  // _edge	_interval_map.end());
  // _vertex_inter	val_map.erase(_vertex_interval_map.begin(),
  // 	                              _vertex_interval_map.end());

  set_alpha(Coord_type(0)); 
  set_mode(GENERAL);

}

//----------------------- PRIVATE MEMBERS --------------------------

private:
   
struct Less 
{
  bool operator()(const Interval_edge& ie, 
		  const Coord_type& alpha) 
    {
      return ie.first.first < alpha; 
    }

  bool operator()( const Coord_type& alpha, 
		   const Interval_edge& ie) 
    {
      return alpha < ie.first.first; 
    }
};

  
//----------------------- ACCESS TO PRIVATE MEMBERS -----------------

private:
   
  
Coord_type find_interval(Face_handle f) const 
{
  return f->get_alpha();
  // return the value Alpha f the face f
}
 
Interval3 find_interval(const_Edge e)  const 
{ // corriger le parametrage
  return (e.first)->get_ranges(e.second);
  // return the Interval3 for the edge n
}


//---------------------------------------------------------------------

public:

Coord_type set_alpha(const Coord_type& alpha) 
{
  // Sets the alpha-value to `alpha'. Precondition: `alpha' >= 0.
  // Returns the previous alpha
  Coord_type previous_alpha = _alpha;
  _alpha = alpha;
  return previous_alpha;
}

const Coord_type&  get_alpha() const 
{
  // Returns the current alpha-value.
  return _alpha;
}
  
const Coord_type&  get_nth_alpha(int n) const 
{
  // Returns the n-th alpha-value.
  // n < size()
  if (! _alpha_spectrum.empty())
    return _alpha_spectrum[n];
  else
    return UNDEFINED;
}
  
int number_of_alphas() const 
{
  // Returns the number of not necessary different alpha-values
  return _alpha_spectrum.size();
}

//---------------------------------------------------------------------

private:

// the dynamic version is not yet implemented
// desactivate the triangulation member functions
Vertex_handle insert(const Point& p) 
{}
// Inserts point `p' in the alpha shape and returns the
// corresponding vertex of the underlying Delaunay triangulation.
// If point `p' coincides with an already existing vertex, this
// vertex is returned and the alpha shape remains unchanged.
// Otherwise, the vertex is inserted in the underlying Delaunay
// triangulation and the associated intervals are updated.

void remove(Vertex_handle v) 
{}
// Removes the vertex from the underlying Delaunay triangulation.
// The created hole is retriangulated and the associated intervals
// are updated.

//---------------------------------------------------------------------

public:

Mode set_mode(Mode mode = GENERAL ) 
{
  // Sets `A' to its general or regularized version. Returns the
  // previous mode.

  Mode previous_mode = _mode;
  _mode = mode;
  return previous_mode;
}

Mode get_mode(void) const 
{
  // Returns whether `A' is general or regularized.
  return _mode;
}

//---------------------------------------------------------------------

public:

std::back_insert_iterator< std::list< Vertex_handle > >
get_alpha_shape_vertices(std::back_insert_iterator< 
			 std::list< Vertex_handle > > result) const;

//---------------------------------------------------------------------

std::back_insert_iterator< std::list<Edge > >
get_alpha_shape_edges(std::back_insert_iterator< 
		      std::list< Edge > > result) const;

//---------------------------------------------------------------------

public: 
  
// Traversal of the alpha-Values
// 
// The alpha shape class defines an iterator that allows to
// visit the sorted sequence of alpha-values. This iterator is
// non-mutable and bidirectional. Its value type is Coord_type.

Alpha_iterator alpha_begin() const 
{
  // Returns an iterator that allows to traverse the sorted sequence
  // of alpha-values of `A'.
  return _alpha_spectrum.begin(); 
}

Alpha_iterator alpha_end() const 
{
  // Returns the corresponding past-the-end iterator.
  return _alpha_spectrum.end(); 
}
  
Alpha_iterator alpha_find(const Coord_type& alpha) const 
{
  // Returns an iterator pointing to an element with alpha-value
  // `alpha', or the corresponding past-the-end iterator if such an
  // element is not found.
  return std::find(_alpha_spectrum.begin(),
		   _alpha_spectrum.end(),
		   alpha);
}

Alpha_iterator alpha_lower_bound(const Coord_type& alpha) const 
{
  // Returns an iterator pointing to the first element with
  // alpha-value not less than `alpha'.
  return std::lower_bound(_alpha_spectrum.begin(),
			  _alpha_spectrum.end(),
			  alpha);
}

Alpha_iterator alpha_upper_bound(const Coord_type& alpha) const 
{
  // Returns an iterator pointing to the first element with
  // alpha-value greater than `alpha'.
  return std::upper_bound(_alpha_spectrum.begin(),
			  _alpha_spectrum.end(),
			  alpha);
}

//--------------------- PREDICATES -----------------------------------

// the classification predicates take 
//      amortized const time if STL_STD::HASH_TABLES
//      O(log #alpha_shape ) otherwise

Classification_type  classify( const Point& p ) const 
{
  return classify( p, get_alpha());
}

  
Classification_type  classify(
			      const Point& p,   
			      const Coord_type& alpha) const 
{
  // Classifies a point `p' with respect to `A'.
  Locate_type type;
  int i;
  Face_handle pFace = locate(p, type, i);
  switch (type) 
    {
    case VERTEX            : return classify(pFace->vertex(i), alpha);
    case EDGE              : return classify(pFace, i, alpha);
    case FACE              : return classify(pFace, alpha);
    case OUTSIDE           : 
    case COLLINEAR_OUTSIDE : return EXTERIOR;
    default                : return EXTERIOR;
    }
}

//---------------------------------------------------------------------

Classification_type  classify( Face_handle f ) const 
{
  // Classifies the face `f' of the underlying Delaunay
  // triangulation with respect to `A'.
  return classify(f, get_alpha());
}
  
Classification_type  classify( Face_handle f, 
			       const Coord_type& alpha ) const 
{
  // Classifies the face `f' of the underlying Delaunay
  // triangulation with respect to `A'.
  // we consider open circles :
  // f->radius == alpha => f exterior
  // problem the operator [] is non-const

  if (is_infinite(f)) return EXTERIOR;
    
  // the version that computes the squared radius seems to be 
  // much faster
    
  return (find_interval(f) < alpha) ? 
    INTERIOR :
    EXTERIOR;

}

//---------------------------------------------------------------------
  
Classification_type  classify( std::pair< Face_handle, int > edge) const
{  
  return classify(edge.first, edge.second, get_alpha());
}

Classification_type  classify( Face_handle f, 
			       int i ) const 
{  
  return classify(f, i, get_alpha());
}

Classification_type  classify( std::pair< Face_handle, int > edge,
			       const Coord_type& alpha ) const 
{  
  return classify(edge.first, edge.second, alpha);
}

Classification_type  classify( Face_handle f, 
			       int i,
			       const Coord_type& alpha ) const;

  
//---------------------------------------------------------------------

Classification_type  classify(Vertex_handle v ) const 
{
  return classify( v, get_alpha());
}

Classification_type  classify( Vertex_handle v,
			       const Coord_type& alpha ) const;

//--------------------- NB COMPONENTS ---------------------------------


int
number_solid_components() const 
{
  return number_solid_components(get_alpha());
}

int
number_solid_components(const Coord_type& alpha) const ;

private:

void
traverse( Face_handle pFace,
	  Marked_face_set& marked_face_set, 
	  const Coord_type alpha) const;

class Line_face_circulator;

//----------------------------------------------------------------------

public:

Alpha_iterator find_optimal_alpha(int nb_components);  	

private:

Coord_type find_alpha_solid() const;

//---------------------- PREDICATES ------------------------------------

private:
  
bool is_attached(const Face_handle& f, int i) const 
{
  Bounded_side b = 
    Gt().side_of_circle((*(((*f).vertex(cw(i))))).point(),
			(*(((*f).vertex(ccw(i))))).point(),
			(*(((*f).vertex(i)))).point());
 
  return (b == ON_BOUNDED_SIDE) ? true : false;
}
  
//-------------------- GEOMETRIC PRIMITIVES ----------------------------

Coord_type squared_radius(const Face_handle& f) const 
{
  return 
    Gt().squared_radius(f->vertex(0)->point(),
			f->vertex(1)->point(),
			f->vertex(2)->point());
}

Coord_type squared_radius(const Face_handle& f, const int& i) const 
{
  // should be
  // return (traits().squared_radius_smallest_circumcircle(...)
  // TBC
  return 
    Gt().squared_radius(f->vertex(ccw(i))->point(),
			f->vertex(cw(i))->point());
}

//---------------------------------------------------------------------

private:
// prevent default copy constructor and default assigment
  
Alpha_shape_2( const Alpha_shape_2& A) 
{}

Alpha_shape_2& operator=(const Alpha_shape_2& A) 
{} 

};

//----------------------- MEMBER FUNCTIONS -----------------------------

template < class Dt >
void 
Alpha_shape_2<Dt>::initialize_interval_face_map(void) 
{

  _interval_face_map.reserve(number_of_faces());
  // #ifdef STL_HASH_TABLES
  // _face_interval_map.resize(number_of_faces());
  // #endif
  // size equals number of finite faces
  // actually number of finite + infinite faces TBC !!!

  Coord_type alpha_f;

  Face_iterator face_it;
  // only finite faces
  for( face_it = faces_begin(); 
       face_it != faces_end(); 
       ++face_it) 
    {
      alpha_f = squared_radius(face_it);
      _interval_face_map.push_back(Interval_face(alpha_f, face_it));

      // cross references
      face_it->set_alpha(alpha_f);
    }

  std::sort(_interval_face_map.begin(),
	    _interval_face_map.end(),less_partial<Interval_face>());
 
}

//-------------------------------------------------------------------------

template < class Dt >
void 
Alpha_shape_2<Dt>::initialize_interval_edge_map(void) 
{

  _interval_edge_map.reserve(3*number_of_faces()-6);
  // derive from number of faces and vertices using Euler's formula
  // e <= 3*f -6

  Edge_iterator edge_it;
  Edge edge;

  // only finite faces
  for( edge_it = edges_begin(); 
       edge_it != edges_end(); 
       ++edge_it) 
    { 
      Interval3 interval;
      edge = (*edge_it);

      Face_handle pFace = edge.first;
      int i = edge.second;
      Face_handle pNeighbor = pFace->neighbor(i);
     
      
      // not on the convex hull
      
      if(!is_infinite(pFace) && !is_infinite(pNeighbor)) 
	{ 
	  Coord_type squared_radius_Face = 
	    find_interval(pFace);
	  Coord_type squared_radius_Neighbor = 
	    find_interval(pNeighbor);

	  interval = (is_attached(pFace, i) || 
		      is_attached(pNeighbor, pNeighbor->index(&(*pFace)))) ?
	    make_triple(UNDEFINED,
			std::min(squared_radius_Face, 
				 squared_radius_Neighbor),
			std::max(squared_radius_Face, 
				 squared_radius_Neighbor)):
	    make_triple(squared_radius(pFace, i),
			std::min(squared_radius_Face, 
				 squared_radius_Neighbor),
			std::max(squared_radius_Face, 
				 squared_radius_Neighbor));
	}
      else 
	{ // on the convex hull

	  if(is_infinite(pFace)) 
	    {
	      if (!is_infinite(pNeighbor)) 
		{
		  interval =  (is_attached(pNeighbor,
					   pNeighbor->index(&(*pFace)))) ?
		    make_triple(UNDEFINED,
				find_interval(pNeighbor), 
				INFINITY):
		    make_triple(squared_radius(pNeighbor, 
					       pNeighbor->index(&(*pFace))), 
				find_interval(pNeighbor), 
				INFINITY);
		}
	      else 
		{
		  // both faces are infinite by definition unattached
		  // the edge is finite by construction
		  CGAL_triangulation_precondition((is_infinite(pNeighbor) 
						   && is_infinite(pFace)));
		  interval = make_triple(squared_radius(pFace, i), 
					 INFINITY,
					 INFINITY);
		}
	    }
	  else 
	    { // is_infinite(pNeighbor)
	   
	      CGAL_triangulation_precondition((is_infinite(pNeighbor) 
					       && !is_infinite(pFace)));
	      if (is_attached(pFace, i))
		interval = make_triple(UNDEFINED,
				       find_interval(pFace),
				       INFINITY);
	      else
		interval = make_triple(squared_radius(pFace, i),
				       find_interval(pFace),
				       INFINITY);

	    }
	}
      
      _interval_edge_map.push_back(Interval_edge(interval, edge));
      
      // cross-links
      
      pFace->set_ranges(i,interval);

    }

  std::sort(_interval_edge_map.begin(), 
	    _interval_edge_map.end(),less_partial<Interval_edge>());

  // Remark:
  // The interval_edge_map will be sorted as follows
  // first the attached edges on the convex hull
  // second                   not on the convex hull
  // third the un-attached edges on the convex hull
  // finally                     not on the convex hull
  // 
  // if we are in regularized mode we should sort differently
  // by the second third first Key
}

//-------------------------------------------------------------------------

template < class Dt >
void 
Alpha_shape_2<Dt>::initialize_interval_vertex_map(void) 
{

  _interval_vertex_map.reserve(number_of_vertices());

  // size equals number of finite vertices

  Coord_type alpha_mid_v;
  Coord_type alpha_max_v;
  Coord_type alpha_f;

  Vertex_iterator vertex_it;
  // only finite vertexs
  for( vertex_it = vertices_begin(); 
       vertex_it != vertices_end(); 
       ++vertex_it) 
    {
      Vertex_handle v = vertex_it;
      Face_handle f;

      alpha_max_v = Coord_type(0);    
      alpha_mid_v = (!_interval_face_map.empty() ?
		     _interval_face_map.back().first :
		     Coord_type(0));

      //----------------- examine incident edges --------------------------
      /*
	// if we used Edelsbrunner and Muecke's definition
	// singular means not incident to any higher-dimensional face
	// regular means incident to a higher-dimensional face
	Edge_circulator edge_circ = v->incident_edges(),
	edge_done(edge_circ);

	do 
      
	{ 
	f = (*edge_circ).first;
	int i = (*edge_circ).second;

	if (is_infinite(f, i))
      
	{
	alpha_max_v = INFINITY;
	}
	else
      
	{
	Interval3 interval3 = find_interval(const_Edge(f, i));
				
	
	alpha_mid_v = (interval3.first != UNDEFINED) ?
	std::min(alpha_mid_v, interval3.first): 
	std::min(alpha_mid_v, interval3.second); 
			
	if (alpha_max_v != INFINITY)
      
	{
	alpha_max_v = (interval3.third != INFINITY) ?
	std::max(alpha_max_v, interval3.third):
	INFINITY;
	}
	}
	}
	while(++edge_circ != edge_done);
      */

      //-------------- examine incident faces --------------------------
      
      // we use a different definition than Edelsbrunner and Muecke
      // singular means not incident to any 2-dimensional face
      // regular means incident to a 2-dimensional face
     
      Face_circulator face_circ = v->incident_faces(),
	done = face_circ;
   
      if (!face_circ.is_empty()) 
	{
	  do 
	    {
	      f = face_circ;
	      if (is_infinite(f)) 
		{
		  alpha_max_v = INFINITY;
		  // continue;
		}
	      else 
		{
		  alpha_f = find_interval(f);
		  // if we define singular as not incident to a 2-dimensional
		  // face
		  alpha_mid_v = std::min(alpha_mid_v, alpha_f);
		    
		  if (alpha_max_v != INFINITY)
		    alpha_max_v = std::max(alpha_max_v, alpha_f);
			    
		}
	    }
	  while(++face_circ != done);
	}
	
 
      Interval2 interval = std::make_pair(alpha_mid_v, alpha_max_v);
      _interval_vertex_map.push_back(Interval_vertex(interval, vertex_it));

      // cross references
      vertex_it->set_range(interval);
    }

  std::sort(_interval_vertex_map.begin(), 
	    _interval_vertex_map.end(),less_partial<Interval_vertex>());
 
}

//-------------------------------------------------------------------------

template < class Dt >
void 
Alpha_shape_2<Dt>::initialize_alpha_spectrum(void) 
{

  // skip the attached edges 
  // <=> _interval_edge_map.first.first == UNDEFINED
  typename Interval_edge_map::iterator edge_it;
  edge_it = std::upper_bound(_interval_edge_map.begin(),
			     _interval_edge_map.end(),
			     UNDEFINED,
			     Less());

  // merge the maps which is sorted and contains the alpha-values
  // of the unattached edges and the triangles.
  // eliminate duplicate values due to for example attached edges
  // merge and copy from STL since assignment should be function object
	
  typename Interval_face_map::iterator
    face_it = _interval_face_map.begin();

  _alpha_spectrum.reserve(_interval_face_map.size() +
			  _interval_edge_map.size()/ 2 );
  // should be only the number of unattached edges
  // size_type nb_unattached_edges;
  // distance(edge_it, _interval_edge_map.end(), nb_unattached_edges);
  // however the distance function is expensive

  while (edge_it != _interval_edge_map.end() &&
	 face_it != _interval_face_map.end()) 
    {

      if ((*face_it).first < (*edge_it).first.first) 
	{
	  if (((_alpha_spectrum.empty() || 
		_alpha_spectrum.back() < (*face_it).first)) && 
	      ((*face_it).first > Coord_type(0)))
	    _alpha_spectrum.push_back((*face_it).first);
	  face_it++;
	}
      else
	{
	  if (((_alpha_spectrum.empty() || 
		_alpha_spectrum.back() < (*edge_it).first.first)) &&
	      (((*edge_it).first.first) > Coord_type(0)))
	    _alpha_spectrum.push_back((*edge_it).first.first);
	  edge_it++;
	}
    }
    
  while (edge_it != _interval_edge_map.end()) 
    {
      if (((_alpha_spectrum.empty() || 
	    _alpha_spectrum.back() < (*edge_it).first.first))&&
	  (((*edge_it).first.first) > Coord_type(0)))
	_alpha_spectrum.push_back((*edge_it).first.first);
      edge_it++;
    }

  while (face_it != _interval_face_map.end()) 
    { 
      if (((_alpha_spectrum.empty() || 
	    _alpha_spectrum.back() < (*face_it).first))&&
	  ((*face_it).first > Coord_type(0)))
	_alpha_spectrum.push_back((*face_it).first);
      face_it++;
    }

}

//-------------------------------------------------------------------------

template < class Dt >
std::back_insert_iterator
                  < std::list< typename Alpha_shape_2<Dt>::Vertex_handle > >
Alpha_shape_2<Dt>::get_alpha_shape_vertices
(std::back_insert_iterator< std::list< Vertex_handle > > result) const 
{
  //typedef typename Alpha_shape_2<Dt>::Interval_vertex_map 
  //                                              Interval_vertex_map;
  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  //const typename Alpha_shape_2<Dt>::Interval2* pInterval2;
  const Interval2* pInterval2;
  Vertex_handle v;
     
  // write the regular vertices

  for (vertex_alpha_it = _interval_vertex_map.begin(); 
       vertex_alpha_it != _interval_vertex_map.end() &&
	 (*vertex_alpha_it).first.first < get_alpha();
       ++vertex_alpha_it) 
    {
      pInterval2 = &(*vertex_alpha_it).first;

      if((pInterval2->second >= get_alpha()
	  || pInterval2->second == INFINITY)) 
	{
	  // alpha must be larger than the min boundary
	  // and alpha is smaller than the upper boundary
	  // which might be infinity 
	  // write the vertex
	  v = (*vertex_alpha_it).second;
	  CGAL_triangulation_assertion((classify(v) == REGULAR));
	  *result++ = v;
	}
    }
 
  if (get_mode() == Alpha_shape_2<Dt>::GENERAL) 
    {
      // write the singular vertices
      for (; 
	   vertex_alpha_it != _interval_vertex_map.end();
	   ++vertex_alpha_it) 
	{
	  v = (*vertex_alpha_it).second;
	  CGAL_triangulation_assertion((classify(v) == SINGULAR));

	  *result++ = v;
	}
    }
  return result;
}

//-------------------------------------------------------------------------

template < class Dt >
std::back_insert_iterator< std::list< typename Alpha_shape_2<Dt>::Edge > >
Alpha_shape_2<Dt>::get_alpha_shape_edges
(std::back_insert_iterator< std::list< Edge > > result) const 
{
  // Writes the edges of the alpha shape `A' for the current $\alpha$-value
  // to the container where 'out' refers to. Returns an output iterator 
  // which is the end of the constructed range.
  //typedef  typename Alpha_shape_2<Dt>::Interval_edge_map Interval_edge_map;
  typename Interval_edge_map::const_iterator edge_alpha_it;

  //const typename Alpha_shape_2<Dt>::Interval3* pInterval;
  const Interval3* pInterval;
  
  if (get_mode() == REGULARIZED) 
    {
      // it is much faster looking at the sorted intervals 
      // than looking at all sorted faces
      // alpha must be larger than the mid boundary
      // and alpha is smaller than the upper boundary
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
	  pInterval = &(*edge_alpha_it).first;
      
	  CGAL_triangulation_assertion(pInterval->second != INFINITY);
	  // since this happens only for convex hull of dimension 2
	  // thus singular

	  if(pInterval->second < get_alpha() &&
	     (pInterval->third >= get_alpha()
	      || pInterval->third == INFINITY)) 
	    {
	      // alpha must be larger than the mid boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second)
			       == REGULAR));
	      *result++ = Edge((*edge_alpha_it).second.first,
			       (*edge_alpha_it).second.second);
	    }
	}
    }
  else 
    {  // get_mode() == GENERAL -------------------------------------------
      // draw the edges
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
	  pInterval = &(*edge_alpha_it).first;
      
	  if (pInterval->first == UNDEFINED) 
	    {
	      CGAL_triangulation_assertion(pInterval->second != INFINITY);
	      // since this happens only for convex hull of dimension 2
	      // thus singular
	
	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second) 
			       == REGULAR));
		  *result++ = Edge((*edge_alpha_it).second.first,
				   (*edge_alpha_it).second.second);
		}
	    }
	  else 
	    {
	
	      if(pInterval->third >= get_alpha()
		 || pInterval->third == INFINITY) 
		{
		  // if alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
 CGAL_triangulation_assertion(((classify((*edge_alpha_it).second.first,
					 (*edge_alpha_it).second.second) 
				== REGULAR)
			       || (classify((*edge_alpha_it).second.first,
					    (*edge_alpha_it).second.second) 
				   == SINGULAR)));
		  *result++ = Edge((*edge_alpha_it).second.first,
				   (*edge_alpha_it).second.second);
		}
	    }
      
	}
    
    }
  return result;
}

//-------------------------------------------------------------------------

template < class Dt >
Alpha_shape_2<Dt>::Classification_type  
Alpha_shape_2<Dt>::classify(Face_handle f, int i, 
			    const Coord_type& alpha) const
{
  // Classifies the edge `e' of the underlying Delaunay
  // triangulation with respect to `A'.

  // the version that uses a simplified version without crosslinks
  // is much slower
  if (is_infinite(f, i))
    return EXTERIOR;

  // we store only finite edges in _edge_interval_map
  Interval3 interval = find_interval(const_Edge(f, i));
  //  (*(_edge_interval_map.find(const_Edge(f, i)))).second;
 
  if (alpha <= interval.second) 
    {
      if (get_mode() == REGULARIZED ||
	  interval.first == UNDEFINED ||
	  alpha <= interval.first)
	return EXTERIOR;
      else // alpha > interval.first
	return SINGULAR;
    }
  else 
    {   // alpha > interval.second
      if (interval.third == INFINITY ||
	  alpha <= interval.third)
	return REGULAR;
      else // alpha > interval.third
	return INTERIOR;
    }
   
}

//-------------------------------------------------------------------------

template < class Dt >
Alpha_shape_2<Dt>::Classification_type  
Alpha_shape_2<Dt>::classify(Vertex_handle v,
			    const Coord_type& alpha) const 
{
  // Classifies the vertex `v' of the underlying Delaunay
  // triangulation with respect to `A'.
  Interval2 interval = v->get_range();
 
  if (alpha <= interval.first) 
    {
      if (get_mode() == REGULARIZED) 
	return EXTERIOR;
      else // general => vertices are never exterior
	return SINGULAR;
    }
  else 
    {   // alpha > interval.first
      if (interval.second == INFINITY ||
	  alpha <= interval.second)
	return REGULAR;
      else // alpha > interval.second
	return INTERIOR;
    }
}

//-------------------------------------------------------------------------

template < class Dt >
int
Alpha_shape_2<Dt>::number_solid_components(const Coord_type& alpha) const
{
  // Determine the number of connected solid components 
  // takes time O(#alpha_shape) amortized if STL_STD::HASH_TABLES
  //            O(#alpha_shape log n) otherwise
  Marked_face_set marked_face_set;
  Face_iterator face_it;
  int nb_solid_components = 0;

  //prevent error (Rajout Frank)
  if (number_of_vertices()==0)
    return 0;

  // only finite faces
  for( face_it = faces_begin(); 
       face_it != faces_end(); 
       ++face_it) 
    {
      Face_handle pFace = face_it;
      CGAL_triangulation_postcondition((!pFace.is_null()));

      if (classify(pFace, alpha) == INTERIOR &&
	  ((marked_face_set.insert(Key(&(*face_it))))).second) 
	{
	  // we traverse only interior faces
	  traverse(pFace, marked_face_set, alpha);
	  nb_solid_components++;  
	}
    }
  return nb_solid_components;
}
//-------------------------------------------------------------------------

template < class Dt >
void
Alpha_shape_2<Dt>::traverse(Face_handle pFace,
			    Marked_face_set& marked_face_set, 
			    const Coord_type alpha) const 
{
  for (int i=0; i<=2; i++) 
    { 
      Face_handle pNeighbor = pFace->neighbor(i);
	 
      CGAL_triangulation_precondition((!pNeighbor.is_null())); 
      if (classify(pNeighbor, alpha) == INTERIOR &&
	  ((marked_face_set.insert(Key(&(*pNeighbor))))).second)
	traverse(pNeighbor, marked_face_set, alpha);
    }
}

//-------------------------------------------------------------------------

template < class Dt >
Alpha_shape_2<Dt>::Alpha_iterator
Alpha_shape_2<Dt>::find_optimal_alpha(int nb_components) 
{
  // find the minimum alpha that satisfies the properties
  // (1) nb_components solid components
  // (2) all data points on the boundary or in its interior
  Coord_type alpha = find_alpha_solid();
  // from this alpha on the alpha_solid satisfies property (2)
  
  Alpha_iterator first = alpha_lower_bound(alpha);

  if (number_solid_components(alpha) == nb_components) 
    {
      if ((first+1) < alpha_end())
	return (first+1);
      else
	return first;
    }
	  
    

  // do binary search on the alpha values
  // number_solid_components() is a monotone function 
  // if we start with find_alpha_solid

  
  Alpha_iterator last = alpha_end();
  Alpha_iterator middle;
  
  ptrdiff_t len = last - first - 1;
  ptrdiff_t half;

  while (len > 0) 
    {
      half = len / 2;
      middle = first + half;

#ifdef DEBUG
      std::cout << "first : " << *first << " last : " << *(first+len)
		<< " mid : " << *middle 
		<< " nb comps : " << number_solid_components(*middle) 
		<< std::endl;
#endif // DEBUG

      if (number_solid_components(*middle) > nb_components) 
	{
	  first = middle + 1;
	  len = len - half - 1; 
	} 
      else 
	{ // number_solid_components(*middle) <= nb_components
	  len = half;
	}
    }
  if ((first+1) < alpha_end())
    return (first+1);
  else
    return first;
}

//-------------------------------------------------------------------------

template < class Dt >
Alpha_shape_2<Dt>::Coord_type 
Alpha_shape_2<Dt>::find_alpha_solid() const 
{
  // compute the minumum alpha such that all data points 
  // are either on the boundary or in the interior
  // not necessarily connected
  // starting point for searching 
  // takes O(#alpha_shape) time
  Coord_type alpha_solid = 0;

  Vertex_iterator vertex_it;
  // only finite vertices
  for( vertex_it = vertices_begin(); 
       vertex_it != vertices_end();
       ++vertex_it) 
    {
      Coord_type alpha_min_v = _interval_face_map.back().first;

      Face_circulator face_circ = vertex_it->incident_faces();
      Face_circulator  done = face_circ;
      do 
	{
	  Face_handle f = face_circ;
	  if (! is_infinite(f))
	    alpha_min_v = std::min(find_interval(f),
				   alpha_min_v);
	}
      while (++face_circ != done);
      alpha_solid = std::max(alpha_min_v, alpha_solid);

    }
  return alpha_solid;
}

//-------------------------------------------------------------------------

template < class Dt >
std::ostream& 
Alpha_shape_2<Dt>::op_ostream(std::ostream& os) const
{
  
  typedef typename Alpha_shape_2<Dt>::Interval_vertex_map 
    Interval_vertex_map ;
  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  const typename Alpha_shape_2<Dt>::Interval2* pInterval2;

    
#ifndef STL_HASH_TABLES
  typedef long Key;
  std::map< Key, int, std::less< Key > > V;
#else
  typedef long Key;
  std::hash_map< Key, int > V;
  V.resize(number_of_vertices());
#endif
  int number_of_vertices = 0;
      
  typedef typename Alpha_shape_2<Dt>::Interval_edge_map 
    Interval_edge_map;
  typename Interval_edge_map::const_iterator edge_alpha_it;

  const typename Alpha_shape_2<Dt>::Interval3* pInterval;

  if (get_mode() == Alpha_shape_2<Dt>::REGULARIZED) 
    {

      typename Alpha_shape_2<Dt>::Vertex_handle v;
      for (vertex_alpha_it = _interval_vertex_map.begin(); 
	   vertex_alpha_it != _interval_vertex_map.end() &&
	     (*vertex_alpha_it).first.first < get_alpha();
	   ++vertex_alpha_it) 
	{

	  pInterval2 = &(*vertex_alpha_it).first;

#ifdef DEBUG
	  typename Alpha_shape_2<Dt>::Coord_type alpha =
	    get_alpha();
	  typename Alpha_shape_2<Dt>::Coord_type alpha_mid = 
	    pInterval2->first;
	  typename Alpha_shape_2<Dt>::Coord_type alpha_max = 
	    pInterval2->second;
#endif // DEBUG

	  if((pInterval2->second >= get_alpha()
	      || pInterval2->second == INFINITY)) 
	    {
	      // alpha must be larger than the min boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // write the vertex

	      v = (*vertex_alpha_it).second;
 CGAL_triangulation_assertion((classify(v) == 
			       Alpha_shape_2<Dt>::REGULAR));
	      // if we used Edelsbrunner and Muecke's definition
	      // regular means incident to a higher-dimensional face
	      // we would write too many vertices

	      V[Key(&v)] = number_of_vertices++;
	      os << v->point() << endl;
	    }
	}
      // the vertices are oriented counterclockwise

      typename Alpha_shape_2<Dt>::Face_handle f;
      int i;

      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;

	  CGAL_triangulation_assertion(pInterval->second != INFINITY);
	  // since this happens only for convex hull of dimension 1
	  // thus singular

	  if(pInterval->second < get_alpha() &&
	     (pInterval->third >= get_alpha()
	      || pInterval->third == INFINITY)) 
	    {
	      // alpha must be larger than the mid boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary


	      f = (*edge_alpha_it).second.first;
	      i = (*edge_alpha_it).second.second;

	      // assure that all vertices are in ccw order
	      if (classify(f) == Alpha_shape_2<Dt>::EXTERIOR) 
		{
            
		  // take the reverse face
		  typename Alpha_shape_2<Dt>::Face_handle 
		    pNeighbor = f->neighbor(i);
		  i = pNeighbor->index(&(*f));
		  f = pNeighbor;
		}
	  
 CGAL_triangulation_assertion((classify(f) == 
			       Alpha_shape_2<Dt>::INTERIOR));

 CGAL_triangulation_assertion((classify(f, i) == 
			       Alpha_shape_2<Dt>::REGULAR));

	      os << V[Key(&(f->vertex(f->ccw(i))))] << ' ' 
		 << V[Key(&(f->vertex(f->cw(i))))] << endl;
	    }
	}
    }
  else 
    { // get_mode() == GENERAL -----------------------------------------

      typename Alpha_shape_2<Dt>::Vertex_handle v;
     
      // write the regular vertices

      for (vertex_alpha_it = _interval_vertex_map.begin(); 
	   vertex_alpha_it != _interval_vertex_map.end() &&
	     (*vertex_alpha_it).first.first < get_alpha();
	   ++vertex_alpha_it) 
	{

	  pInterval2 = &(*vertex_alpha_it).first;

	  if((pInterval2->second >= get_alpha()
	      || pInterval2->second == INFINITY)) 
	    {
	      // alpha must be larger than the min boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // write the vertex

	      v = (*vertex_alpha_it).second;
 CGAL_triangulation_assertion((classify(v) == 
			       Alpha_shape_2<Dt>::REGULAR));
	      V[Key(&v)] = number_of_vertices++;
	      os << v->point() << endl;
	    }
	}
 
      // write the singular vertices
      for (; 
	   vertex_alpha_it != _interval_vertex_map.end();
	   ++vertex_alpha_it) 
	{

	  v = (*vertex_alpha_it).second;
 CGAL_triangulation_assertion((classify(v) ==
			       Alpha_shape_2<Dt>::SINGULAR));

	  V[Key(&v)] = number_of_vertices++;
	  os << v->point() << endl;
	}
 
      // the vertices are oriented counterclockwise

      typename Alpha_shape_2<Dt>::Face_handle f;
      int i;

      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;

#ifdef DEBUG
	  typename Alpha_shape_2<Dt>::Coord_type alpha =
	    get_alpha();
	  typename Alpha_shape_2<Dt>::Coord_type alpha_min = 
	    pInterval->first;
	  typename Alpha_shape_2<Dt>::Coord_type alpha_mid = 
	    pInterval->second;
	  typename Alpha_shape_2<Dt>::Coord_type alpha_max = 
	    pInterval->third;
#endif // DEBUG
	  
	  if(pInterval->third >= get_alpha()
	     || pInterval->third == INFINITY) 
	    {
	      // if alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary

	      f = (*edge_alpha_it).second.first;
	      i = (*edge_alpha_it).second.second;


	      // write the regular edges
	      if (pInterval->second != INFINITY &&
		  pInterval->second < get_alpha()) 
		{

 CGAL_triangulation_assertion((classify(f, i) == 
			       Alpha_shape_2<Dt>::REGULAR));
		  // assure that all vertices are in ccw order
		  if (classify(f) == Alpha_shape_2<Dt>::EXTERIOR) 
		    {
 
		      // take the reverse face
		      typename Alpha_shape_2<Dt>::Face_handle 
			pNeighbor = f->neighbor(i);
		      
		      i = pNeighbor->index(&(*f));
		      f = pNeighbor;
		    }
	  
 CGAL_triangulation_assertion((classify(f) == 
			       Alpha_shape_2<Dt>::INTERIOR));

		  os << V[Key(&(f->vertex(f->ccw(i))))] << ' ' 
		     << V[Key(&(f->vertex(f->cw(i))))] << endl;
		  
		}
	      else 
		{ // pInterval->second == INFINITY || 
		  //                           pInterval->second >= get_alpha())  
		  // pInterval->second == INFINITY happens only for convex hull
		  // of dimension 1 thus singular

		  // write the singular edges
		  if (pInterval->first != UNDEFINED) 
		    {
 CGAL_triangulation_assertion((classify(f, i) == 
			       Alpha_shape_2<Dt>::SINGULAR));
		      os << V[Key(&(f->vertex(f->ccw(i))))] << ' ' 
			 << V[Key(&(f->vertex(f->cw(i))))] << endl;
	
		    }	
		}
	    }
	}
    }
  
  return os;
}

//-------------------------------------------------------------------------

template < class Dt >
typename Alpha_shape_2<Dt>::Vect_seg& 
Alpha_shape_2<Dt>::op_vect_seg(Vect_seg& V) const
{

  typedef typename Alpha_shape_2<Dt>::Interval_vertex_map 
    Interval_vertex_map;
  //  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  typedef  typename Alpha_shape_2<Dt>::Interval_edge_map 
    Interval_edge_map;
  typename Interval_edge_map::const_iterator edge_alpha_it;

  const typename Alpha_shape_2<Dt>::Interval3* pInterval;

  if (get_mode() == Alpha_shape_2<Dt>::REGULARIZED) 
    {
      // it is much faster looking at the sorted intervals 
      // than looking at all sorted faces
      // alpha must be larger than the mid boundary
      // and alpha is smaller than the upper boundary
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;

	  CGAL_triangulation_assertion(pInterval->second != INFINITY);
	  // since this happens only for convex hull of dimension 1
	  // thus singular

	  if(pInterval->second < get_alpha() &&
	     (pInterval->third >= get_alpha()
	      || pInterval->third == INFINITY)) 
	    {
	      // alpha must be larger than the mid boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary
	    
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second)
			       == Alpha_shape_2<Dt>::REGULAR));
	      // if we used Edelsbrunner and Muecke's definition
	      // regular means incident to a higher-dimensional face
	      // thus we would write to many vertices
	      V.push_back(segment((*edge_alpha_it).second.first,
				  (*edge_alpha_it).second.second));
	    }
	}
    }
  else 
    { // get_mode() == GENERAL
    
      // draw the edges
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
	
	  pInterval = &(*edge_alpha_it).first;

	  if (pInterval->first == UNDEFINED) 
	    {
	    
 CGAL_triangulation_assertion(pInterval->second != INFINITY);
	      // since this happens only for convex hull of dimension 1
	      // thus singular

	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
		
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second) ==
			       Alpha_shape_2<Dt>::REGULAR));
		  V.push_back(segment((*edge_alpha_it).second.first,
				      (*edge_alpha_it).second.second));
		}
	    }
	  else 
	    {
	    

	      if(pInterval->third >= get_alpha()
		 || pInterval->third == INFINITY) 
		{
		  // if alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
	
 CGAL_triangulation_assertion(
			      ((classify((*edge_alpha_it).second.first,
					 (*edge_alpha_it).second.second) ==
				Alpha_shape_2<Dt>::REGULAR) || 
			       (classify((*edge_alpha_it).second.first,
					 (*edge_alpha_it).second.second) ==
				Alpha_shape_2<Dt>::SINGULAR)));

		  V.push_back(segment((*edge_alpha_it).second.first,
				      (*edge_alpha_it).second.second));
		}
	    }

	}
    }
  return V;
}

//-------------------------------------------------------------------

template < class Dt >
std::ostream& 
operator<<(std::ostream& os, const Alpha_shape_2<Dt>& A)
{
  return A.op_ostream(os);
}

//-------------------------------------------------------------------

template < class Dt >
typename Alpha_shape_2<Dt>::Vect_seg& 
operator<<(typename Alpha_shape_2<Dt>::Vect_seg& V,const Alpha_shape_2<Dt>& A)
{
  return A.op_vect_seg(V);
}

//-------------------------------------------------------------------

#if defined(LIST) || defined(__SGI_STL_LIST)
template < class Dt >
std::list<typename Alpha_shape_2<Dt>::Point> 
Alpha_shape_2<Dt>::Output () 
{

  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  typename Interval_edge_map::const_iterator edge_alpha_it;

  const Interval3* pInterval;
  std::list<Point> L;


  if (get_mode() == REGULARIZED) 
    {

      // it is much faster looking at the sorted intervals 
      // than looking at all sorted faces
      // alpha must be larger than the mid boundary
      // and alpha is smaller than the upper boundary
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
      
	  pInterval = &(*edge_alpha_it).first;

	  if (pInterval->second != INFINITY)
	    {
	      // since this happens only for convex hull of dimension 1
	      // thus singular
	
	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
	  
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second) ==
			       REGULAR));
	  
		  // if we used Edelsbrunner and Muecke's definition
		  // regular means incident to a higher-dimensional face
		  // thus we would write to many vertices
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .source());
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .target());
		}
	    }
	}
    }
  else 
    {  // get_mode() == GENERAL
      // draw the edges
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;
	
	  if (pInterval->first == UNDEFINED) 
	    {

 CGAL_triangulation_assertion(pInterval->second != INFINITY);
	      // since this happens only for convex hull of dimension 1
	      // thus singular

	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
		
 CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
					(*edge_alpha_it).second.second) ==
			       REGULAR));
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .source());
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .target());
		}
	    }
	  else 
	    {

	      if(pInterval->third >= get_alpha()
		 || pInterval->third == INFINITY) 
		{
		  // if alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
		
 CGAL_triangulation_assertion(((classify((*edge_alpha_it).second.first,
					 (*edge_alpha_it).second.second) ==
				REGULAR) || 
			       (classify((*edge_alpha_it).second.first,
					 (*edge_alpha_it).second.second) ==
				SINGULAR)));
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .source());
		  L.push_back((segment((*edge_alpha_it).second.first,
				       (*edge_alpha_it).second.second))
			      .target());
		}
	    }

	}
    }
  return L;
}
#endif //LIST

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#ifdef CGAL_ALPHA_WINDOW_STREAM
#include <CGAL/IO/alpha_shapes_2_window_stream.h>
#endif

#endif //CGAL_ALPHA_SHAPE_2_H
