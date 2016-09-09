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
// file          : include/CGAL/Triangulation_face.h
// package       : Triangulation (1.23)
// source        : web/Triangulation_face.fw
// revision      : $Revision: 1.15 $
// revision_date : $Date: 1998/04/27 09:52:02 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_FACE_H
#define CGAL_TRIANGULATION_FACE_H

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_vertex.h>

template < class Vertex >
class CGAL_Triangulation_face;

template < class Vertex >
class CGAL_Triangulation_face {
public:
        typedef CGAL_Triangulation_face<Vertex> Face;
        typedef typename Vertex::Vertex_handle Vertex_handle;
        typedef CGAL_Pointer<Face> Face_handle;
    
    inline Face_handle handle() const
    {
        return Face_handle(this);
    }
    
    inline void set_vertices()
    {
        V[0] = NULL;
        V[1] = NULL;
        V[2] = NULL;
    }
    
    
    inline void set_vertices(Vertex_handle v0,
                 Vertex_handle v1,
                 Vertex_handle v2)
    {
        V[0] = v0;
        V[1] = v1;
        V[2] = v2;
    }
    
    inline void set_neighbors()
    {
        N[0] = NULL;
        N[1] = NULL;
        N[2] = NULL;
    }
    
    inline
    void set_neighbors(Face_handle n0,
                       Face_handle n1,
                       Face_handle n2)
    {
        N[0] = n0;
        N[1] = n1;
        N[2] = n2;
    }
    
    inline
    CGAL_Triangulation_face()
    {
        set_vertices();
        set_neighbors();
    }
    
    inline
    CGAL_Triangulation_face(const Vertex_handle& v0,
                            const Vertex_handle& v1,
                            const Vertex_handle& v2)
    {
        set_vertices(v0, v1, v2);
        set_neighbors();
    }
    
    inline
    CGAL_Triangulation_face(const Vertex_handle& v0,
                            const Vertex_handle& v1,
                            const Vertex_handle& v2,
                            const Face_handle& n0,
                            const Face_handle& n1,
                            const Face_handle& n2)
    {
        set_vertices(v0, v1, v2);
        set_neighbors(n0, n1, n2);
    }
    
    
    ~CGAL_Triangulation_face()
    {}
    inline void set_vertex(int i, const Vertex_handle& v)
    {
        CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
        V[i] = v;
    }
    
    
    inline void set_neighbor(int i, const Face_handle& n)
    {
        CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
        N[i] = n;
    }
    
    inline const Vertex_handle& vertex(int i) const
    {
        CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
        return V[i];
    }
    
    
    inline bool has_vertex(const Vertex_handle& v) const
    {
        return (V[0] == v) || (V[1] == v) || (V[2]== v);
    }
    
    
    inline bool has_vertex(const Vertex_handle& v, int& i) const
    {
        if (v == V[0]) {
            i = 0;
            return true;
        }
        if (v == V[1]) {
            i = 1;
            return true;
        }
        if (v == V[2]) {
            i = 2;
            return true;
        }
        return false;
    }
    
    
    inline int index(const Vertex_handle& v) const
    {
        if (v == V[0]) {
            return 0;
        }
        if (v == V[1]) {
            return 1;
        }
        if (v == V[2]) {
            return 2;
        }
        CGAL_triangulation_assertion(false); // we should not get here
        return -1;
    }
    inline const Face_handle& neighbor(int i) const
    {
        CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);
    
        return N[i];
    }
    
    
    inline bool has_neighbor(const Face_handle& n) const
    {
        return (N[0] == n) || (N[1] == n) || (N[2] == n);
    }
    
    
    inline bool has_neighbor(const Face_handle& n, int& i) const
    {
        if(n == N[0]){
            i = 0;
            return true;
        }
        if(n == N[1]){
            i = 1;
            return true;
        }
        if(n == N[2]){
            i = 2;
            return true;
        }
        return false;
    }
    
    
    inline int index(const Face_handle& n) const
    {
        if (n == N[0]) {
            return 0;
        }
        if (n == N[1]) {
            return 1;
        }
        if (n == N[2]) {
            return 2;
        }
        CGAL_triangulation_precondition(false); // we should not get here
        return -1;
    }
    
    inline int ccw(int i) const
    {
    
        return (i+1) % 3;
    }
    
    
    inline int cw(int i) const
    {
        return (i+2) % 3;
    }
    
    
    void insert(const Vertex_handle& v)
    {
        CGAL_triangulation_precondition(v != NULL);
        Vertex_handle v0 = vertex(0);
        Vertex_handle v2 = vertex(2);
    
        Face_handle ccwptr = neighbor(ccw(0));
        Face_handle cwptr  = neighbor(cw(0));
    
        int ccwi, cwi;
        if(ccwptr != NULL) {
            ccwi = cw(ccwptr->index(v0));
        }
        if(cwptr != NULL) {
            cwi  = ccw(cwptr->index(v0));
        }
    
        Face_handle n1ptr = new Face(v0, v, v2,
                               this, ccwptr, NULL);
    
        Face_handle n2ptr = new Face(v0, vertex(1), v,
                               this, n1ptr, cwptr);
    
        if( (v0 != NULL) && (v0->face() == this) ) {
            v0->set_face(n2ptr);
        }
    
        if( (v2 != NULL) && (v2->face() == this) ) {
            v2->set_face(n1ptr);
        }
    
        set_vertex(0, v);
        v->set_face(this);
    
        // here come the missing links
        set_neighbor(1, n1ptr);
        set_neighbor(2, n2ptr);
        n1ptr->set_neighbor(2, n2ptr);
    
        if(ccwptr != NULL) {
            ccwptr->set_neighbor(ccwi, n1ptr);
        }
        if(cwptr != NULL) {
            cwptr->set_neighbor(cwi, n2ptr);
        }
    }
    
    bool insert(const Vertex_handle& v, int i)
    {
        CGAL_triangulation_precondition(v != NULL);
        if(neighbor(i) != NULL) {
            cerr << "Insertion impossible as neighbor face already exists" << endl;
            return false;
        }
        Face_handle f = new Face(v, vertex(cw(i)), vertex(ccw(i)),
                           this, NULL, NULL);
        set_neighbor(i, f);
        v->set_face(f);
        Vertex_handle w = vertex(ccw(i));
        if(w != NULL){
            w->set_face(f);
        }
    
        return true;
    }
    
    bool remove(Vertex_handle &v)
    {
        CGAL_triangulation_precondition(v != NULL);
        int i = index(v);
    
        Face_handle left, right, ll, rr;
    
        left = neighbor(cw(i));
        right = neighbor(ccw(i));
    
        if(left == NULL || right == NULL) {
            if(left == NULL && right == NULL) {
                Face_handle n = neighbor(i);
                if(n != NULL) {
                    int ni = n->index(this);
                    n->set_neighbor(ni, NULL);
                    Vertex_handle q = vertex(cw(i));
                    if(q != NULL){
                        q->set_face(n);
                    }
                } else {
                    cerr << "removal of boundary vertex failed as face has"
                         << "no neighbors" << endl;
                }
                handle().Delete();
                v.Delete();
                return true;
            } else {
                cerr << "removal of boundary vertex with degree != 2 failed";
                cerr << endl;
                return false;
            }
        }
    
        if(v->degree() != 3){
            cerr << "removal of internal vertex with degree != 3 failed";
            cerr << endl;
            return false;
        }
    
        int li = left->index(this);
        int ri = right->index(this);
        Vertex_handle q = left->vertex(li);
        CGAL_triangulation_assertion( left->vertex(li) == right->vertex(ri));
    
        ll = left->neighbor(cw(li));
        if(ll != NULL) {
            int lli = ll->index(left);
            ll->set_neighbor(lli, this);
        }
        set_neighbor(cw(i), ll);
        if (vertex(ccw(i))->face() == left) vertex(ccw(i))->set_face(this);
    
        rr = right->neighbor(ccw(ri));
        if(rr != NULL) {
            int rri = rr->index(right);
            rr->set_neighbor(rri, this);
        }
        set_neighbor(ccw(i), rr);
        if (vertex(cw(i))->face() == right) vertex(cw(i))->set_face(this);
    
        set_vertex(i, q);
        if (q->face() == right || q->face() == left) {
           q->set_face( ll != NULL ? ll : this->handle());
        }
        right.Delete();
        left.Delete();
    
        v.Delete();
        return true;
    }
    
    void flip(int i)
    {
        cerr << "The flip member function should no longer be called" << endl;
        // bl == bottom left, tr == top right
        Face_handle tl = neighbor(ccw(i));
        Face_handle n  = neighbor(i);
    
        Vertex_handle v_cw = vertex(cw(i));
        Vertex_handle v_ccw = vertex(ccw(i));
    
        // The following seems natural, but it fails if the faces
        // this and n are neighbors on two edges (1-dim triangulation,
        // with infinite faces
        // int ni = n->index(this);
    
        int ni = cw(n->index(v_cw));
    
        CGAL_triangulation_assertion( this == n->neighbor(ni) );
    
        Face_handle br = n->neighbor(ccw(ni));
        int bri, tli;
    
        if(br != NULL){
            bri = br->index(n);
        }
        if(tl != NULL){
            tli = tl->index(this);
        }
        set_vertex(cw(i), n->vertex(ni));
        n->set_vertex(cw(ni), vertex(i));
    
        // update the neighborhood relations
        set_neighbor(i, br);
        if(br != NULL){
            br->set_neighbor(bri, this);
        }
    
        set_neighbor(ccw(i), n);
        n->set_neighbor(ccw(ni), this);
    
        n->set_neighbor(ni, tl);
        if(tl != NULL){
            tl->set_neighbor(tli, n);
        }
    
    
        if(v_cw->face() == this) {
            v_cw->set_face(n);
        }
    
        if(v_ccw->face() == n) {
            v_ccw->set_face(this);
        }
    }
    
    bool is_valid(bool verbose = false, int level = 0) const
    {
        bool result = true;
        for(int i = 0; i < 3; i++) {
            Face_handle n = neighbor(i);
            if(n != NULL){
                int ni = n->index(handle());
                result = result && (vertex(cw(i)) == n->vertex(ccw(ni)));
                result = result && (vertex(ccw(i)) == n->vertex(cw(ni)));
            } else {
                result = result && (vertex(cw(i))->face() == handle());
            }
        }
        return result;
    }
    
private:
    
      Vertex_handle V[3];
      Face_handle N[3];
    
};

#endif // CGAL_TRIANGULATION_FACE_H
