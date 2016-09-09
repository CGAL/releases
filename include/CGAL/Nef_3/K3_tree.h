#line 15 "k3_tree.nw"
// Copyright (c) 1997-2000  Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Nef_3/include/CGAL/Nef_3/K3_tree.h,v $
// $Revision: 1.15.2.2 $ $Date: 2004/12/08 19:30:28 $
// $Name:  $
//
// Author(s)     : Miguel Granados <granados@mpi-sb.mpg.de>

#ifndef K3_TREE_H
#define K3_TREE_H

#include <CGAL/basic.h>
#include <CGAL/Unique_hash_map.h>
#include <CGAL/Nef_3/quotient_coordinates_to_homogeneous_point.h>

#include <deque>
#include <sstream>
#include <string>

#undef CGAL_NEF_DEBUG
#define CGAL_NEF_DEBUG 503
#include <CGAL/Nef_2/debug.h>

CGAL_BEGIN_NAMESPACE

template <typename Triangle_3>
void sort_triangle_by_lexicographically_smaller_vertex
(const Triangle_3& t, int& a, int& b, int& c) {
  typedef typename Triangle_3::R Kernel;
  a = 0;
  for( int i = 1; i < 3; ++i) {
    if( compare_xyz<Kernel>( t[a], t[i]) == SMALLER)
      a = i;
  }
  b = (a + 1) % 3;
  c = (b + 1) % 3;
  if( compare_xyz<Kernel>( t[b], t[c]) == LARGER)
    std::swap( b, c);
  return;
}

template <typename Triangle_3>
struct Compare_triangle_3 {
  typedef typename Triangle_3::R Kernel;
  bool operator()( const Triangle_3& t1, const Triangle_3& t2) const {
    int v1[3], v2[3];
    sort_triangle_by_lexicographically_smaller_vertex
      ( t1, v1[0], v1[1], v1[2]);
    sort_triangle_by_lexicographically_smaller_vertex
      ( t2, v2[0], v2[1], v2[2]);
    for( int i = 0; i < 3; ++i) {
      Comparison_result c = compare_xyz<Kernel>( t1[v1[i]], t2[v2[i]]);
      if( c == SMALLER)
	return true;
      else if( c == LARGER)
	return false;
    }
    return false; // the two triangles are equivalent
  }
};

template <class Traits>
class K3_tree
{
public:
  friend class Objects_along_ray;
  friend class Objects_around_segment;

public:
  
#line 302 "k3_tree.nw"
typedef typename Traits::SNC_decorator SNC_decorator;
typedef typename Traits::Infimaximal_box Infimaximal_box;
typedef typename Traits::Vertex_handle Vertex_handle;
typedef typename Traits::Halfedge_handle Halfedge_handle;
typedef typename Traits::Halffacet_handle Halffacet_handle;
typedef typename Traits::Halffacet_triangle_handle Halffacet_triangle_handle;

typedef typename Traits::Object_handle Object_handle;
typedef std::vector<Object_handle> Object_list;
typedef typename Object_list::const_iterator Object_const_iterator;
typedef typename Object_list::iterator Object_iterator;
typedef typename Object_list::size_type size_type;

typedef typename Traits::Point_3 Point_3;
typedef typename Traits::Segment_3 Segment_3;
typedef typename Traits::Ray_3 Ray_3;
typedef typename Traits::Vector_3 Vector_3;
typedef typename Traits::Plane_3 Plane_3;
typedef typename Traits::Triangle_3 Triangle_3;
typedef typename Traits::Aff_transformation_3 Aff_transformation_3;

typedef typename Traits::Bounding_box_3 Bounding_box_3;
typedef typename Traits::Side_of_plane Side_of_plane;
typedef typename Traits::Objects_bbox Objects_bbox;

typedef typename Traits::Kernel Kernel;
typedef typename Kernel::RT RT;

#line 486 "k3_tree.nw"
class Node {
  friend class K3_tree<Traits>;
public:
  Node( Node* p, Node* l, Node* r, Plane_3 pl, const Object_list& O) : 
    parent_node(p), left_node(l), right_node(r), splitting_plane(pl), 
    object_list(O) {}
  bool is_leaf() const {
    CGAL_assertion( (left_node != 0 && right_node != 0) ||
                    (left_node == 0 && right_node == 0));
    return (left_node == 0 && right_node == 0);
  }
  const Node* parent() const { return parent_node; }
  const Node* left() const { return left_node; }
  const Node* right() const { return right_node; }
  const Plane_3& plane() const { return splitting_plane; }
  const Object_list& objects() const { return object_list; }

  void transform(const Aff_transformation_3& t) {
    if(left_node != 0) {
	CGAL_assertion(right_node != 0);
	left_node->transform(t);
 	right_node->transform(t);
  	splitting_plane = splitting_plane.transform(t);
    }
  }
  
#line 812 "k3_tree.nw"
friend std::ostream& operator<<
  (std::ostream& os, const Node* node) {
  CGAL_assertion( node != 0);
  if( node->is_leaf())
    os <<  node->objects().size();
  else {
    os << " ( ";
    if( !node->left()) os << '-';
    else os << node->left();
    os << " , ";
    if( !node->right()) os << '-';
    else os << node->right();
    os << " ) ";
  }
  return os;
}

#line 512 "k3_tree.nw"
  
#line 587 "k3_tree.nw"
~Node() {
  CGAL_NEF_TRACEN("~Node: deleting node...");
  if( !is_leaf()) {
    delete left_node;
    delete right_node;
  }
}

#line 513 "k3_tree.nw"
private:
  Node* parent_node;
  Node* left_node;
  Node* right_node;
  Plane_3 splitting_plane;
  Object_list object_list;
};



#line 97 "k3_tree.nw"
public:
  class Objects_around_segment 
  {
   public:
    class Iterator;
  protected:
    Traits traits;
    Node *root_node;
    Segment_3 segment;
    bool initialized;
  public:
    Objects_around_segment() : initialized(false) {}
    Objects_around_segment( const K3_tree& k, const Segment_3& s) : 
      root_node(k.root), segment(s), initialized(true) {
      CGAL_NEF_TRACEN("Objects_around_segment: input segment: "<<segment);
    }
    void initialize( const K3_tree& k, const Segment_3& s) {
      root_node = k.root;
      segment = s;
      initialized = true;
      CGAL_NEF_TRACEN("Objects_around_segment: input segment: "<<s<<" (initialize)");
    }
  public:
    Iterator begin() const {
      CGAL_assertion( initialized == true);
      return Iterator( root_node, segment);
    }
    Iterator end() const {
      return Iterator();
    }
    class Iterator
    {
      friend class K3_tree;
      typedef Iterator Self;
      typedef std::pair< const Node*, Segment_3> Candidate;
    protected:
      std::deque<Candidate> S;
      const Node* node;
      Traits traits;
      CGAL_assertion_code( Segment_3 prev_segment);
      CGAL_assertion_code( bool first_segment);
    public:
      Iterator() : node(0) {}
      Iterator( const Node* root, const Segment_3& s) {
        CGAL_assertion_code( first_segment = true);
        S.push_front( Candidate( root, s));
        ++(*this); // place the interator in the first intersected cell
      }
      Iterator( const Self& i) : S(i.S), node(i.node) {}
      const Object_list& operator*() const { 
        CGAL_assertion( node != 0);
        return node->objects();
      }
      Self& operator++() {
        
#line 882 "k3_tree.nw"
if( S.empty())
  node = 0; // end of the iterator
else {
  while( !S.empty()) {
    const Node* n = S.front().first;
    Segment_3 s = S.front().second;
    S.pop_front();
    if( n->is_leaf()) {
#ifndef NDEBUG
      CGAL_assertion_code(
      if( first_segment) {
        first_segment = false;
        CGAL_NEF_TRACEN("operator++: prev_segment=(none), segment="<<s);
      }
      else {
        CGAL_assertion( prev_segment.target() == s.source());
        CGAL_assertion( prev_segment.direction() == s.direction());
        CGAL_NEF_TRACEN("operator++: prev_segment="<<prev_segment<<", segment="<<s);
      }
      prev_segment = s);
#endif
      node = n;
      break;
    }
    else {
      CGAL_NEF_TRACEN("find next intersected cell: segment: "<<s);
      CGAL_NEF_TRACEN("find next intersected cell: node plane: "<<n->plane() <<
             ", point: "<<n->plane().point());
      Oriented_side src_side = n->plane().oriented_side(s.source());
      Oriented_side tgt_side = n->plane().oriented_side(s.target());
      if( src_side == ON_ORIENTED_BOUNDARY && tgt_side == ON_ORIENTED_BOUNDARY)
        src_side = tgt_side = ON_NEGATIVE_SIDE;
      else if( src_side == ON_ORIENTED_BOUNDARY)
        src_side = tgt_side;
      else if( tgt_side == ON_ORIENTED_BOUNDARY)
        tgt_side = src_side;
      if( src_side == tgt_side)
        S.push_front( Candidate( get_child_by_side( n, src_side), s));
      else {
        Segment_3 s1, s2;
        divide_segment_by_plane( s, n->plane(), s1, s2);
        S.push_front( Candidate( get_child_by_side( n, tgt_side), s2)); // cell on target pushed first
        S.push_front( Candidate( get_child_by_side( n, src_side), s1));
      }
    }
  }
}

#line 152 "k3_tree.nw"
        return *this;
      }
      bool operator==(const Self& i) const { 
        return (node == i.node); 
      }
      bool operator!=(const Self& i) const { 
        return !(*this == i); 
      }
    private:
      const Node* get_node() const { 
        CGAL_assertion( node != 0);
        return node;
      }
      
#line 743 "k3_tree.nw"
inline 
const Node* get_child_by_side( const Node* node, Oriented_side side) {
  CGAL_assertion( node != NULL);
  CGAL_assertion( side != ON_ORIENTED_BOUNDARY);
  if( side == ON_NEGATIVE_SIDE) {
    return node->left();
  }
  CGAL_assertion( side == ON_POSITIVE_SIDE);
  return node->right();
}

void divide_segment_by_plane( Segment_3 s, Plane_3 pl, 
                              Segment_3& s1, Segment_3& s2) {
  Object o = traits.intersect_object()( pl, s);
  Point_3 ip;
  CGAL_assertion( CGAL::assign( ip, o));
  CGAL::assign( ip, o);
  ip = normalized(ip);
  s1 = Segment_3( s.source(), ip);
  s2 = Segment_3( ip, s.target());
  CGAL_assertion( s1.target() == s2.source());
  CGAL_assertion( s1.direction() == s.direction());
  CGAL_assertion( s2.direction() == s.direction());
}

#line 166 "k3_tree.nw"
    };
  };

  class Objects_along_ray : public Objects_around_segment
  {
    typedef Objects_around_segment Base;
  protected:
    Traits traits;	
  public:
    Objects_along_ray( const K3_tree& k, const Ray_3& r) {
      CGAL_NEF_TRACEN("Objects_along_ray: input ray: "<<r);
      Vector_3 vec(r.to_vector());
      CGAL_assertion(vec == Vector_3( -1, 0, 0));
      // First of all, we need to find out wheather we are working over an extended kernel or on a standard kernel. As precondition we have that ray is oriented in the minus x axis direction.  When having an extended kernel, the ray can be subtituted by a segment with the endpoint on the 'intersection' between the ray and the bounding infimaximal box.  In the presence of a standard kernel, the intersection is computed with the bounding box with the vertices of the Nef polyhedron.
      Point_3 p(r.source()), q;
      Bounding_box_3 b = k.bounding_box;
//      Point_3 pt_on_minus_x_plane = quotient_coordinates_to_homogeneous_point<Kernel>
//	( b.xmin(), b.ymin(), b.zmin());
	Point_3 pt_on_minus_x_plane(b.get_min());
      // We compute the intersection between a plane with normal vector in the minus x direction and located at the minimum point of the bounding box, and the input ray.  When the ray does not intersect the bounding volume, there won't be any object hit, so it is safe to construct a segment that simply lay in the unbounded side of the bounding box.  This approach is taken instead of somehow (efficiently) report that there was no hit object, in order to mantain a clear interface with the Iterator class.
      Plane_3 pl_on_minus_x( pt_on_minus_x_plane, Vector_3( -1, 0, 0));
      Object o = traits.intersect_object()( pl_on_minus_x, r);
      if( !CGAL::assign( q, o) || pl_on_minus_x.has_on(p))
	q = r.source() + Vector_3( -1, 0, 0);
      else
	q = normalized(q);
      Base::initialize( k, Segment_3( p, q));
    }
  };

private:
  Traits traits;
  Node* root;
  int max_depth;
  Bounding_box_3 bounding_box;
public:
  K3_tree(Object_list& objects, Object_iterator& v_end) {
    
#line 285 "k3_tree.nw"
typename Object_list::difference_type n_vertices = std::distance(objects.begin(),v_end);
CGAL_NEF_TRACEN("K3_tree(): n_vertices = " << std::distance(objects.begin(),v_end));
frexp( (double) n_vertices, &max_depth);

#line 204 "k3_tree.nw"
    
#line 293 "k3_tree.nw"
// TODO: in the presence of a infimaximal bounding box, the bounding box does not have to be computed
Objects_bbox objects_bbox = traits.objects_bbox_object();
bounding_box = objects_bbox(objects);
//CGAL_NEF_TRACEN("bounding box:"<<objects_bbox);

#line 205 "k3_tree.nw"
    root = build_kdtree( objects, v_end, 0);
  }
  const Object_list& objects_around_point( const Point_3& p) const {
    return locate( p, root);
  }
  Objects_along_ray objects_along_ray( const Ray_3& r) const {
    return Objects_along_ray( *this, r);
  }
  Object_list objects_around_segment( const Segment_3& s) const {
    Object_list O;
    
#line 836 "k3_tree.nw"
Objects_around_segment objects( *this, s);
Unique_hash_map< Vertex_handle, bool> v_mark(false);
Unique_hash_map< Halfedge_handle, bool> e_mark(false);
Unique_hash_map< Halffacet_handle, bool> f_mark(false);
std::map< Triangle_3, bool, Compare_triangle_3<Triangle_3> > t_mark;
for( typename Objects_around_segment::Iterator oar = objects.begin(); 
     oar != objects.end(); ++oar) {
  for( typename Object_list::const_iterator o = (*oar).begin();
       o != (*oar).end(); ++o) { // TODO: implement operator->(...)
    Vertex_handle v;
    Halfedge_handle e;
    Halffacet_handle f;
    if( CGAL::assign( v, *o)) {
      if( !v_mark[v]) {
        O.push_back(*o);
        v_mark[v] = true;
      }
    }
    else if( CGAL::assign( e, *o)) {
      if( !e_mark [e]) {
        O.push_back(*o);
        e_mark[e] = true;
      }
    }
    else if( CGAL::assign( f, *o)) {
      if( !f_mark[f]) {
        O.push_back(*o);
        f_mark[f] = true;
      }
    }
    else {
      Halffacet_triangle_handle t;
      if( CGAL::assign( t, *o)) {
        Triangle_3 tr = t.get_triangle();
        if( !t_mark[tr]) {
	  O.push_back(*o);
	  t_mark[tr] = true;
        }
      }
      else
        CGAL_assertion_msg( 0, "wrong handle");
    }
  }
}

#line 216 "k3_tree.nw"
    return O;
  }
  bool is_point_on_cell( const Point_3& p, const typename Objects_around_segment::Iterator& target) const {
    return is_point_on_cell( p, target.get_node(), root);
  }

  template<typename SNCd>
  class BBox_updater {
    SNCd D;
    Bounding_box_3 b;

  public:	
    BBox_updater(const SNCd& sncd) : D(sncd), b(Point_3(0,0,0),Point_3(0,0,0)) {}

    void pre_visit(const Node* n) {}
    void post_visit(const Node* n) {
      typename Object_list::const_iterator o;
      for( o = n->objects().begin(); o != n->objects().end(); ++o) {
        Vertex_handle v;
        if( CGAL::assign( v, *o)) {
	  Point_3 p(D.point(v));
          b = b + Bounding_box_3(p,p);
        }
      }
    }

    Bounding_box_3 box() const{
      return b;
    }
    
  };

  template <typename Visitor>
  void visit_k3tree(const Node* current, Visitor& V) const {
    V.pre_visit(current);
    if(current->left() != 0) {
      visit_k3tree(current->left(), V);
      visit_k3tree(current->right(), V);
    }
    V.post_visit(current);
  }

  void transform(const Aff_transformation_3& t) {
    // TODO: Bounding box must be updated/transformed, too
    if(root != 0)
      root->transform(t);

    SNC_decorator D;
    BBox_updater<SNC_decorator> bbup(D);
    visit_k3tree(root, bbup);
    bounding_box = bbup.box();
  }

  
#line 769 "k3_tree.nw"
#ifdef CODE_DOES_NOT_WORK_WITH_BOTH_KERNELS_AT_THE_SAME_TIME
template <typename T>
friend std::ostream& operator<<
(std::ostream& os, const K3_tree<T>& k3_tree) {
  os << (const Node*)k3_tree.root; // no default conversion to const Node*?
  return os;
}
#endif
std::string dump_object_list( const Object_list& O, int level = 0) {
  std::stringstream os; 
  typename Object_list::size_type v_count = 0, e_count = 0, f_count = 0, t_count = 0;
  typename Object_list::const_iterator o;
  for( o = O.begin(); o != O.end(); ++o) {
    SNC_decorator D;
    Vertex_handle v;
    Halfedge_handle e;
    Halffacet_handle f;
    if( CGAL::assign( v, *o)) {
      if( level) os << D.point(v) << std::endl;
      v_count++;
    }
    else if( CGAL::assign( e, *o)) {
      if( level) os << D.segment(e) << std::endl;
      e_count++;
    }
    else if( CGAL::assign( f, *o)) {
      if( level) os << "facet" << std::endl;
      f_count++;
    }
    else {
      Halffacet_triangle_handle t;
      if( CGAL::assign( t, *o)) {
        if( level) os << "triangle" << std::endl;
        t_count++;
      }	
      else CGAL_assertion_msg( 0, "wrong handle");
    }
  }
  os << v_count << "v " << e_count << "e " << f_count << "f " << t_count << "t ";
  return os.str();
}

#line 270 "k3_tree.nw"
  
#line 525 "k3_tree.nw"
bool update( Unique_hash_map<Vertex_handle, bool>& V, 
             Unique_hash_map<Halfedge_handle, bool>& E, 
             Unique_hash_map<Halffacet_handle, bool>& F) {
  return update( root, V, E, F);
}

bool update( Node* node,
             Unique_hash_map<Vertex_handle, bool>& V, 
             Unique_hash_map<Halfedge_handle, bool>& E, 
             Unique_hash_map<Halffacet_handle, bool>& F) {
  CGAL_assertion( node != 0);
  if( node->is_leaf()) {
    bool updated = false;
    Object_list* O = &node->object_list;
    typename Object_list::iterator onext, o = O->begin();
    while( o != O->end()) {
      onext = o;
      onext++;
      Vertex_handle v;
      Halfedge_handle e;
      Halffacet_handle f;
      if( CGAL::assign( v, *o)) {
        if( !V[v]) {
          O->erase(o);
          updated = true;
        }
      }
      else if( CGAL::assign( e, *o)) {
        if( !E[e]) {
          O->erase(o);
          updated = true;
        }         
      }
      else if( CGAL::assign( f, *o)) {
        if( !F[f]) {
          O->erase(o);
          updated = true;
        }
      }
      else CGAL_assertion_msg( 0, "wrong handle");
      o = onext;
    }
    return updated;
  }
  // TODO: protect the code below from optimizations!
  bool left_updated = update( node->left_node, V, E, F);
  CGAL_NEF_TRACEN("k3_tree::update(): left node updated? "<<left_updated);
  bool right_updated = update( node->right_node, V, E, F);
  CGAL_NEF_TRACEN("k3_tree::update(): right node updated? "<<right_updated);
  return (left_updated || right_updated);
}

#line 271 "k3_tree.nw"
  
#line 581 "k3_tree.nw"
~K3_tree() {
  CGAL_NEF_TRACEN("~K3_tree: deleting root...");
  delete root;
}

#line 272 "k3_tree.nw"
private:
  
#line 338 "k3_tree.nw"
template <typename Depth>
Node* build_kdtree(Object_list& O, Object_iterator v_end, 
	           Depth depth, Node* parent=0, int non_efective_splits=0) {
  CGAL_precondition( depth >= 0);
  CGAL_NEF_TRACEN( "build_kdtree: "<<O.size()<<" objects, "<<"depth "<<depth);
  CGAL_NEF_TRACEN( "build_kdtree: "<<dump_object_list(O));
  if( !can_set_be_divided(O.begin(), v_end, depth)) {
    CGAL_NEF_TRACEN("build_kdtree: set cannot be divided");
    return new Node( parent, 0, 0, Plane_3(), O);
  }
  Object_iterator median; 
  Plane_3 partition_plane = construct_splitting_plane(O.begin(), v_end, median, depth);
  CGAL_NEF_TRACEN("build_kdtree: plane: "<<partition_plane<< " " << partition_plane.point());
  Object_list O1, O2;
  Vertex_handle vm,vx;
  CGAL::assign(vm,*median);
  for(Object_iterator oi=O.begin();oi!=median;++oi) {
    O1.push_back(*oi);
    CGAL::assign(vx,*oi);
    if(vm->point()[depth%3] == vx->point()[depth%3])
      O2.push_back(*oi);
  }
  O1.push_back(*median);
  O2.push_back(*median);
  for(Object_iterator oi=median+1;oi!=v_end;++oi) {
    O2.push_back(*oi);
    CGAL::assign(vx,*oi);
    if(vm->point()[depth%3] == vx->point()[depth%3])
      O1.push_back(*oi);
  }
  typename Object_list::size_type v_end1 = O1.size();
  typename Object_list::size_type v_end2 = O2.size();
  bool splitted = classify_objects( v_end, O.end(), partition_plane, depth,
                                    std::back_inserter(O1), 
                                    std::back_inserter(O2));
  if( !splitted) {
    CGAL_NEF_TRACEN("build_kdtree: splitting plane not found");
    return new Node( parent, 0, 0, Plane_3(), O);
  }

  CGAL_assertion( O1.size() <= O.size() && O2.size() <= O.size());
  CGAL_assertion( O1.size() + O2.size() >= O.size());
  bool non_efective_split = ((O1.size() == O.size()) || (O2.size() == O.size()));
  if( non_efective_split)
    non_efective_splits++;
  else
    non_efective_splits = 0;
  if( non_efective_splits > 2) {
    CGAL_NEF_TRACEN("build_kdtree: non efective splits reached maximum");
    return new Node( parent, 0, 0, Plane_3(), O);
  }
  Node *node = new Node( parent, 0, 0, partition_plane, Object_list());
  node->left_node = build_kdtree( O1, O1.begin()+v_end1, depth + 1, node, non_efective_splits);
  node->right_node = build_kdtree( O2, O2.begin()+v_end2, depth + 1, node, non_efective_splits);
  return node;
}

#line 399 "k3_tree.nw"
template <typename Depth>
bool can_set_be_divided(Object_iterator start, Object_iterator end, Depth depth) {
  if( depth >= max_depth)
    return false;
  if(std::distance(start,end)<2)
    return false;
  return true;
}

#line 414 "k3_tree.nw"
template <typename OutputIterator>
bool classify_objects(Object_iterator start, Object_iterator end, 
                      Plane_3 partition_plane, int depth,
                      OutputIterator o1, OutputIterator o2) {
  typename Object_list::difference_type on_oriented_boundary = 0;
  typename Object_list::const_iterator o;
  
  Side_of_plane sop;
  for( o = start; o != end; ++o) {
    Oriented_side side = sop( partition_plane, *o);
    if( side == ON_NEGATIVE_SIDE || side == ON_ORIENTED_BOUNDARY) {
      *o1 = *o;
      ++o1;
    }
    if( side == ON_POSITIVE_SIDE || side == ON_ORIENTED_BOUNDARY) {
      *o2 = *o;
      ++o2;
    }
    if( side == ON_ORIENTED_BOUNDARY)
      on_oriented_boundary++;
  }
  return (on_oriented_boundary != std::distance(start,end));
}

#line 442 "k3_tree.nw"
template <typename Object, typename Vertex, typename Explorer, typename Coordinate>
class Vertex_smaller_than
{
public:
  Vertex_smaller_than(Coordinate c) : coord(c) {
    CGAL_assertion( c >= 0 && c <=2);
  }
  bool operator()( const Object& o1, const Object& o2) {
    Vertex v1,v2;
    CGAL::assign(v1,o1);
    CGAL::assign(v2,o2);
    return(v1->point()[coord] < v2->point()[coord]); 
  }
private:
  Coordinate coord;
  SNC_decorator D;
};

template <typename Depth>
Plane_3 construct_splitting_plane(Object_iterator start, Object_iterator end,
                                  Object_iterator& median, Depth depth) {
  CGAL_precondition( depth >= 0);
  typename Object_list::difference_type n=std::distance(start,end);
  CGAL_assertion(n>1);

  std::nth_element(start, start+n/2, end,
  	           Vertex_smaller_than<Object_handle,Vertex_handle, SNC_decorator, int>(depth%3));

  median = start+n/2;
  Vertex_handle v;
  CGAL::assign(v,*median);
  switch( depth % 3) {
  case 0: return Plane_3( v->point(), Vector_3( 1, 0, 0)); break;
  case 1: return Plane_3( v->point(), Vector_3( 0, 1, 0)); break;
  case 2: return Plane_3( v->point(), Vector_3( 0, 0, 1)); break;
  }
  CGAL_assertion_msg( 0, "never reached");
  return Plane_3();
}

#line 274 "k3_tree.nw"
  
#line 601 "k3_tree.nw"
const Node *locate_cell_containing( const Point_3& p, const Node* node) const {
  CGAL_precondition( node != 0);
  if( node->is_leaf())
    return node;
  else {
    Oriented_side side = node->plane().oriented_side(p);
    if( side == ON_NEGATIVE_SIDE || side == ON_ORIENTED_BOUNDARY)
      return locate_cell_containing( p, node->left());
    else { // side == ON_POSITIVE_SIDE 
      CGAL_assertion( side == ON_POSITIVE_SIDE);
      return locate_cell_containing( p, node->right());
    }
  }
}

const Object_list& locate( const Point_3& p, const Node* node) const {
  CGAL_precondition( node != 0);
  return locate_cell_containing( p, node)->objects();
}

bool is_point_on_cell( const Point_3& p, const Node* target, const Node* current) const {
  CGAL_precondition( target != 0 && current != 0);
  if( current->is_leaf())
    return (current == target); 
  Oriented_side side = current->plane().oriented_side(p);
  if( side == ON_NEGATIVE_SIDE)
    return is_point_on_cell( p, target, current->left());
  else if( side == ON_POSITIVE_SIDE)
    return is_point_on_cell( p, target, current->right());
  CGAL_assertion( side == ON_ORIENTED_BOUNDARY);
  return (is_point_on_cell( p, target, current->left()) ||
          is_point_on_cell( p, target, current->right()));
}

#line 275 "k3_tree.nw"
};

CGAL_END_NAMESPACE

#endif // K3_TREE_H

