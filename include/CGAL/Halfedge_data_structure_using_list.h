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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Halfedge_data_structure_using_list.h
// package       : Halfedge_DS (1.9)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/10/14 14:02:03 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Using a List Implementation.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H 1
// Includes also <CGAL/basic.h>, <stddef.h>.
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

#ifndef CGAL_IN_PLACE_LIST_H
#include <CGAL/In_place_list.h>
#endif

#ifndef CGAL_N_STEP_ADAPTOR_H
#include <CGAL/N_step_adaptor.h>
#endif

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_DECORATOR_H
#include <CGAL/Halfedge_data_structure_decorator.h>
#endif

#ifndef CGAL_PROTECT_MAP_H
#include <map.h>
#define CGAL_PROTECT_MAP_H
#endif // CGAL_PROTECT_MAP_H

// Define shorter names to please linker (g++/egcs)
#define CGAL__HDS_list_vertex                    CGAL__Hlv
#define CGAL__HDS_list_halfedge                  CGAL__Hlh
#define CGAL__HDS_list_facet                     CGAL__Hlf


template <class V, class H, class F> class CGAL__HDS_list_vertex;
template <class V, class H, class F> class CGAL__HDS_list_halfedge;
template <class V, class H, class F> class CGAL__HDS_list_facet;

template <class V, class H, class F>
class CGAL__HDS_list_vertex
    : public  V,
      public  CGAL_In_place_list_base< CGAL__HDS_list_vertex<V,H,F> >
{
public:
    typedef V                                       Base;
    typedef CGAL__HDS_list_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_list_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_list_facet<V,H,F>              Facet;

    // Needed for point constructor, which is needed for efficiency.
    typedef typename V::Point                       Point;

    CGAL__HDS_list_vertex() {}
    CGAL__HDS_list_vertex( const Point& p) : V(p) {}

    Halfedge*       halfedge()       {return (Halfedge*)(V::halfedge());}
    const Halfedge* halfedge() const {return (const Halfedge*)(V::halfedge());}
    void            set_halfedge( Halfedge* h) { V::set_halfedge(h);}
};

template <class V, class H, class F>
class CGAL__HDS_list_halfedge
    : public  H,
      public  CGAL_In_place_list_base< CGAL__HDS_list_halfedge<V,H,F> >
{
public:
    typedef H                                       Base;
    typedef CGAL__HDS_list_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_list_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_list_facet<V,H,F>              Facet;

    typedef typename H::Supports_halfedge_prev    Supports_halfedge_prev;
    typedef typename H::Supports_halfedge_vertex  Supports_halfedge_vertex;
    typedef typename H::Supports_halfedge_facet   Supports_halfedge_facet;

    Halfedge*       opposite()       {return (Halfedge*)(H::opposite());}
    Halfedge*       next()           {return (Halfedge*)(H::next());}
    Halfedge*       prev()           {return (Halfedge*)(H::prev());}
    Vertex*         vertex()         {return (Vertex*)(H::vertex());}
    Facet*          facet()          {return (Facet*)(H::facet());}

    const Halfedge* opposite() const {return (const Halfedge*)(H::opposite());}
    const Halfedge* next()     const {return (const Halfedge*)(H::next());}
    const Halfedge* prev()     const {return (const Halfedge*)(H::prev());}
    const Vertex*   vertex()   const {return (const Vertex*)(H::vertex());}
    const Facet*    facet()    const {return (const Facet*)(H::facet());}

    void  set_next( Halfedge* h)     { H::set_next(h);}
    void  set_prev( Halfedge* h)     { H::set_prev(h);}
    void  set_vertex( Vertex* ve)    { H::set_vertex(ve);}
    void  set_facet( Facet* facet)   { H::set_facet(facet);}

private:
    void  set_opposite( void* h)     { H::set_opposite(h);}
};


template <class V, class H, class F>
class CGAL__HDS_list_facet
    : public  F,
      public  CGAL_In_place_list_base< CGAL__HDS_list_facet<V,H,F> >
{
public:
    typedef F                                       Base;
    typedef CGAL__HDS_list_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_list_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_list_facet<V,H,F>              Facet;

    Halfedge*       halfedge()       {return (Halfedge*)(F::halfedge());}
    const Halfedge* halfedge() const {return (const Halfedge*)(F::halfedge());}
    void            set_halfedge( Halfedge* h) { F::set_halfedge(h);}
};


// A Halfedge Data Structure Using Lists
// -----------------------------------------
//
// DEFINITION
//
// The class CGAL_Halfedge_data_structure_using_list<Vertex,Halfedge,Facet>
// is a halfedge data structure parameterized with vertex, halfedge,
// and facet types. The base classes defined in the previous subsection
// could be used therefore. It is sufficient for the parameter classes to
// implement the pointers as `void*'. They do not have to know the types
// of their relatives.
//
// CGAL_Halfedge_data_structure_using_list<Vertex,Halfedge,Facet> uses a list
// implementation and supports therefore removal, but the iterators are
// only bidirectional iterators. The capacity is not restricted and calls
// to reserve do not invalidate any iterator or circulator.

template < class V, class H, class F>
class CGAL_Halfedge_data_structure_using_list {
public:
    typedef CGAL_Halfedge_data_structure_using_list<V,H,F>   Self;
    typedef CGAL__HDS_list_vertex<V,H,F>         Vertex;
    typedef CGAL__HDS_list_halfedge<V,H,F>       Halfedge;
    typedef CGAL__HDS_list_facet<V,H,F>          Facet;

    // Point needed for Vertex constructor for efficiency reasons.
    typedef typename Vertex::Point              Point;
    typedef typename Facet::Normal              Normal;
    typedef typename Facet::Plane               Plane;

protected:
    // Three in-place lists for the elements. They are unmanaged.
    typedef CGAL_In_place_list<Vertex,false>     Vertex_list;
    typedef CGAL_In_place_list<Halfedge,false>   Halfedge_list;
    typedef CGAL_In_place_list<Facet,false>      Facet_list;

public:
    typedef typename Halfedge_list::size_type   Size;
    // typedef typename Halfedge_list::size_type   size_type;
    typedef typename Halfedge_list::difference_type
                                                Difference;
protected:
    Vertex_list    vertices;
    Halfedge_list  halfedges;
    Facet_list     facets;
    Size           nb_border_halfedges;
    Size           nb_border_edges;
    Halfedge*      border_halfedges;
public:
    typedef typename Vertex::Supports_vertex_halfedge Supports_vertex_halfedge;
    typedef typename Halfedge::Supports_halfedge_prev Supports_halfedge_prev;
    typedef typename Halfedge::Supports_halfedge_vertex
                                                      Supports_halfedge_vertex;
    typedef typename Halfedge::Supports_halfedge_facet
                                                      Supports_halfedge_facet;
    typedef typename Facet::Supports_facet_halfedge   Supports_facet_halfedge;

    typedef typename Vertex::Supports_vertex_point    Supports_vertex_point;
    typedef typename Facet::Supports_facet_plane      Supports_facet_plane;
    typedef typename Facet::Supports_facet_normal     Supports_facet_normal;

    typedef CGAL_Tag_true                         Supports_removal;
    typedef bidirectional_iterator_tag          iterator_category;

    typedef typename Vertex_list::iterator      Vertex_iterator;
    typedef typename Halfedge_list::iterator    Halfedge_iterator;
    typedef typename Facet_list::iterator       Facet_iterator;
    typedef CGAL_N_step_adaptor< Halfedge_iterator,
                                2,
                                Halfedge&,
                                Halfedge*,
                                Halfedge,
                                ptrdiff_t,
                                iterator_category>
                                                Edge_iterator;

    typedef typename Vertex_list::const_iterator    Vertex_const_iterator;
    typedef typename Halfedge_list::const_iterator  Halfedge_const_iterator;
    typedef typename Facet_list::const_iterator     Facet_const_iterator;
    typedef CGAL_N_step_adaptor< Halfedge_const_iterator,
                                2,
                                const Halfedge&,
                                const Halfedge*,
                                Halfedge,
                                ptrdiff_t,
                                iterator_category>
                                                Edge_const_iterator;


    // Halfegdes are allocated in pairs. Here is the type for that.
    struct Halfedge_pair {
        Halfedge first;
        Halfedge second;
        Halfedge_pair() {}
        Halfedge_pair( const Halfedge& h, const Halfedge& g)
            : first(h), second(g) {}
    };

// CREATION

private:
    void pointer_update( const Self& hds);
        // Update own pointers assuming that they lived previously
        // in a halfedge data structure `hds' with lists.

public:
    CGAL_Halfedge_data_structure_using_list()
        : nb_border_halfedges(0), nb_border_edges(0), border_halfedges(NULL) {}
        // the empty polyhedron `P'.

    CGAL_Halfedge_data_structure_using_list( Size, Size, Size)
        : nb_border_halfedges(0), nb_border_edges(0), border_halfedges(NULL) {}
        // Parameter order is v,h,f.
        // a polyhedron `P' with storage reserved for v vertices, h
        // halfedges, and f facets. The reservation sizes are a hint for
        // optimizing storage allocation. They are not used here.


    void reserve( Size, Size, Size) {}
        // Parameter order is v,h,f.
        // reserve storage for v vertices, h halfedges, and f facets. The
        // reservation sizes are a hint for optimizing storage allocation.
        // If the `capacity' is already greater than the requested size
        // nothing happens. If the `capacity' changes all iterators and
        // circulators invalidates. Function is void here.

    ~CGAL_Halfedge_data_structure_using_list() { delete_all(); }

    CGAL_Halfedge_data_structure_using_list( const Self& hds)
    :  vertices( hds.vertices),
       halfedges( hds.halfedges),
       facets( hds.facets),
       nb_border_halfedges( hds.nb_border_halfedges),
       nb_border_edges( hds.nb_border_edges),
       border_halfedges( hds.border_halfedges)
    {
        pointer_update( hds);
    }

    Self& operator=( const Self& hds)  {
        if ( this != &hds) {
            delete_all();
            vertices            = hds.vertices;
            halfedges           = hds.halfedges;
            facets              = hds.facets;
            nb_border_halfedges = hds.nb_border_halfedges;
            nb_border_edges     = hds.nb_border_edges;
            border_halfedges    = hds.border_halfedges;
            pointer_update( hds);
        }
        return *this;
    }

// Access Member Functions

    Size size_of_vertices() const  { return vertices.size();}
    Size size_of_halfedges() const { return halfedges.size();}
        // number of all halfedges (including border halfedges).
    Size size_of_facets() const    { return facets.size();}

    Size capacity_of_vertices() const    { return vertices.max_size();}
    Size capacity_of_halfedges() const   { return halfedges.max_size();}
    Size capacity_of_facets() const      { return facets.max_size();}

    size_t bytes() const {
        return sizeof(Self)
               + vertices.size()  * sizeof( Vertex)
               + halfedges.size() * sizeof( Halfedge)
               + facets.size()    * sizeof( Facet);
    }
    size_t bytes_reserved() const { return bytes();}

    Vertex_iterator   vertices_begin()   { return vertices.begin();}
    Vertex_iterator   vertices_end()     { return vertices.end();}
    Halfedge_iterator halfedges_begin()  { return halfedges.begin();}
    Halfedge_iterator halfedges_end()    { return halfedges.end();}
    Facet_iterator    facets_begin()     { return facets.begin();}
    Facet_iterator    facets_end()       { return facets.end();}

    Edge_iterator edges_begin() { return Edge_iterator(halfedges_begin());}
        // iterator over all edges. The iterator refers to halfedges, but
        // enumerates only one of the two corresponding opposite
        // halfedges.

    Edge_iterator edges_end() { return Edge_iterator(halfedges_end());}
        // end of the range over all edges.

    // The constant iterators and circulators.

    Vertex_const_iterator   vertices_begin()  const{ return vertices.begin();}
    Vertex_const_iterator   vertices_end()    const{ return vertices.end();}
    Halfedge_const_iterator halfedges_begin() const{ return halfedges.begin();}
    Halfedge_const_iterator halfedges_end()   const{ return halfedges.end();}
    Facet_const_iterator    facets_begin()    const{ return facets.begin();}
    Facet_const_iterator    facets_end()      const{ return facets.end();}

    Edge_const_iterator edges_begin() const {
        return Edge_const_iterator(halfedges_begin());
    }
    Edge_const_iterator edges_end() const {
        return Edge_const_iterator(halfedges_end());
    }

// Insertion
//
// The following operations simply allocate a new element of that type.
// Halfedges are always allocated in pairs of opposite halfedges. The
// opposite pointers are automatically set.

    Vertex* new_vertex() {
                Vertex* v = new Vertex;
                vertices.push_back( *v);
                return v;
    }

    Vertex* new_vertex( const Vertex* w) {
                Vertex* v = new Vertex(*w);
                vertices.push_back( *v);
                return v;
    }

    Vertex* new_vertex( const Point& p) {
                Vertex* v = new Vertex(p);
                vertices.push_back( *v);
                return v;
    }

    Halfedge* new_edge() {
                // creates a new pair of opposite border halfedges.
                Halfedge_pair* hpair = new Halfedge_pair;
                Halfedge* h = &(hpair->first);
                Halfedge* g = &(hpair->second);
                CGAL_assertion( h == (Halfedge*)hpair);
                CGAL_assertion( g == h + 1);
                h->H::set_opposite(g);
                g->H::set_opposite(h);
                halfedges.push_back( *h);
                halfedges.push_back( *g);
                return h;
    }

    Halfedge* new_edge( const Halfedge* he) {
                Halfedge_pair* hpair =new Halfedge_pair(*he,*(he->opposite()));
                Halfedge* h = &(hpair->first);
                Halfedge* g = &(hpair->second);
                CGAL_assertion( h == (Halfedge*)hpair);
                CGAL_assertion( g == h + 1);
                h->H::set_opposite(g);
                g->H::set_opposite(h);
                halfedges.push_back( *h);
                halfedges.push_back( *g);
                return h;
    }

    Facet* new_facet(){
                Facet* f = new Facet;
                facets.push_back( *f);
                return f;
    }

    Facet* new_facet( const Facet* g) {
                Facet* f = new Facet(*g);
                facets.push_back( *f);
                return f;
    }

// Removal
//
// The following operations erase an element referenced by a pointer.
// Halfedges are always deallocated in pairs of opposite halfedges. Erase
// of single elements is optional. The deletion of all is mandatory.

    void delete_vertex( Vertex* v) {
                vertices.erase(v);
                delete v;
    }

    void delete_edge( Halfedge* h) {
                // deletes the pair of opposite halfedges h.
                Halfedge* g = h->opposite();
                halfedges.erase(h);
                halfedges.erase(g);
                if ( h > g)
                    h = g;
                Halfedge_pair* hpair = (Halfedge_pair*)h;
                CGAL_assertion( &(hpair->first) == h);
                delete hpair;
    }

    void delete_facet( Facet* f) {
                facets.erase(f);
                delete f;
    }

    void delete_all() {
                vertices.destroy();
                while ( halfedges.begin() != halfedges.end()) {
                    Halfedge_iterator i = halfedges.begin();
                    halfedges.pop_front();
                    halfedges.pop_front();
                    Halfedge_pair* hpair = (Halfedge_pair*)(&*i);
                    CGAL_assertion( &(hpair->first) == &*i);
                    if ( &*i > &*(i->opposite()))
                        hpair = (Halfedge_pair*)(&*(i->opposite()));
                    delete hpair;
                }
                facets.destroy();
                nb_border_halfedges = 0;
                nb_border_edges = 0;
                border_halfedges = NULL;
    }

    void vertex_pop_back() {
                Vertex* v = & (vertices.back());
                vertices.pop_back();
                delete v;
    }

    void edge_pop_back() {
                Halfedge_iterator i = halfedges.end();
                --i;
                --i;
                halfedges.pop_back();
                halfedges.pop_back();
                Halfedge_pair* hpair = (Halfedge_pair*)(&*i);
                CGAL_assertion( &(hpair->first) == &*i);
                if ( &*i > &*(i->opposite()))
                    hpair = (Halfedge_pair*)(&*(i->opposite()));
                delete hpair;
    }

    void facet_pop_back() {
                Facet* f = & (facets.back());
                facets.pop_back();
                delete f;
    }

// Operations with Border Halfedges

    Size size_of_border_halfedges() const { return nb_border_halfedges;}
        // number of border halfedges. An edge with no incident facet
        // counts as two border halfedges. Precondition: `normalize_border()'
        // has been called and no halfedge insertion or removal and no
        // change in border status of the halfedges have occured since
        // then.

    Size size_of_border_edges() const { return nb_border_edges;}
        // number of border edges. If `size_of_border_edges() ==
        // size_of_border_halfedges()' all border edges are incident to a
        // facet on one side and to a hole on the other side.
        // Precondition: `normalize_border()' has been called and no
        // halfedge insertion or removal and no change in border status of
        // the halfedges have occured since then.

    Halfedge_iterator border_halfedges_begin() {
        // halfedge iterator starting with the border edges. The range [
        // `halfedges_begin(), border_halfedges_begin()') denotes all
        // non-border edges. The range [`border_halfedges_begin(),
        // halfedges_end()') denotes all border edges. Precondition:
        // `normalize_border()' has been called and no halfedge insertion
        // or removal and no change in border status of the halfedges have
        // occured since then.
        CGAL_assertion( border_halfedges);
        return Halfedge_iterator( border_halfedges);
    }

    Edge_iterator border_edges_begin()  {
        // ... trial to make Edge_iterator obsolete.
        return Edge_iterator(border_halfedges_begin());
    }

    Halfedge_const_iterator border_halfedges_begin() const {
        return Halfedge_const_iterator( border_halfedges);
    }

    Edge_const_iterator border_edges_begin()  const {
        return Edge_const_iterator(border_halfedges_begin());
    }

    void normalize_border();
        // sorts halfedges such that the non-border edges precedes the
        // border edges. For each border edge that is incident to a facet
        // the halfedge iterator will reference the halfedge incident to
        // the facet right before the halfedge incident to the hole.
};


template < class V, class H, class F>
void
CGAL_Halfedge_data_structure_using_list<V,H,F>::
pointer_update( const CGAL_Halfedge_data_structure_using_list<V,H,F>& hds) {
    // Update own pointers assuming that they lived previously
    // in a halfedge data structure `hds' with lists.
    typedef map< const Vertex*,   Vertex*,   less<const Vertex*> >   V_map;
    typedef map< const Halfedge*, Halfedge*, less<const Halfedge*> > H_map;
    typedef map< const Facet*,    Facet*,    less<const Facet*> >    F_map;
    V_map v_map;
    H_map h_map;
    F_map f_map;
    // initialize maps.
    Halfedge_iterator ii = halfedges.begin();
    Halfedge_const_iterator i = hds.halfedges.begin();
    for ( ; i != hds.halfedges.end(); ++i) {
        h_map[&*i] = &*ii;
        ++ii;
    }
    h_map[&*i] = &*ii;
    if ( CGAL_check_tag( Supports_halfedge_vertex())) {
        Vertex_iterator vv = vertices.begin();
        for ( Vertex_const_iterator v = hds.vertices.begin();
              v != hds.vertices.end(); ++v) {
            v_map[&*v] = &*vv;
            ++vv;
        }
    }
    if ( CGAL_check_tag( Supports_halfedge_facet())) {
        Facet_iterator ff = facets.begin();
        for ( Facet_const_iterator f = hds.facets.begin();
              f != hds.facets.end(); ++f) {
            f_map[&*f] = &*ff;
            ++ff;
        }
    }

    CGAL_Halfedge_data_structure_decorator<Self> D;
    for ( Halfedge_iterator h = halfedges.begin(); h != halfedges.end(); ++h) {
        h->set_next( h_map[ h->next()]);
        h->H::set_opposite( h_map[ h->opposite()]);
        if ( CGAL_check_tag( Supports_halfedge_prev()))
            D.set_prev( &*h, h_map[ D.get_prev(&*h)]);
        if ( CGAL_check_tag( Supports_halfedge_vertex())) {
            D.set_vertex( &*h, v_map[ D.get_vertex(&*h)]);
            D.set_vertex_halfedge( &*h);
        }
        if ( h->is_border())
            D.set_facet( &*h, 0);
        else if ( CGAL_check_tag( Supports_halfedge_facet())) {
            D.set_facet( &*h, f_map[ D.get_facet(&*h)]);
            D.set_facet_halfedge( &*h);
        }
    }
    border_halfedges = h_map[ border_halfedges];
}

template < class V, class H, class F>
void
CGAL_Halfedge_data_structure_using_list<V,H,F>::normalize_border() {
    CGAL_assertion_code( size_t count = halfedges.size();)
    nb_border_halfedges = 0;
    nb_border_edges = 0;
    Halfedge_list  border;
    Halfedge_iterator i = halfedges_begin();
    while ( i != halfedges_end()) {
        Halfedge_iterator j = i;
        ++i;
        ++i;
        Halfedge_iterator k = j;
        ++k;
        if ( j->is_border()) {
            nb_border_halfedges++;
            nb_border_edges++;
            if (k->is_border())
                nb_border_halfedges++;
            border.splice( border.end(), halfedges, k);
            border.splice( border.end(), halfedges, j);
        } else if ( k->is_border()) {
            nb_border_halfedges++;
            nb_border_edges++;
            border.splice( border.end(), halfedges, j);
            border.splice( border.end(), halfedges, k);
        } else {
            CGAL_assertion_code( count -= 2;)
        }
    }
    CGAL_assertion( count == 2 * nb_border_edges );
    CGAL_assertion( count == border.size());
    if ( i == halfedges_begin()) {
        halfedges.splice( halfedges.end(), border);
        i = halfedges_begin();
    } else {
        --i;
        --i;
        CGAL_assertion( ! (*i).is_border() &&
                   ! (*i).opposite()->is_border());
        halfedges.splice( halfedges.end(), border);
        ++i;
        ++i;
    }
    CGAL_assertion( i == halfedges_end() ||
               (*i).opposite()->is_border());
    border_halfedges = &*i;
}

// Undef shorter names (g++/egcs)
#undef CGAL__HDS_list_vertex
#undef CGAL__HDS_list_halfedge
#undef CGAL__HDS_list_facet
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_USING_LIST_H //
// EOF //
