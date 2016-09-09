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

#ifndef CGAL_TRIANGULATION_FACE_H
#define CGAL_TRIANGULATION_FACE_H

template < class V >
class CGAL_Triangulation_face {
public:
    typedef V Vertex;
    typedef CGAL_Triangulation_face<V> Face;

    
    CGAL_Triangulation_face()
      : _v0(NULL), _v1(NULL), _v2(NULL),
        _n0(NULL), _n1(NULL), _n2(NULL)
    {}
    
    
    CGAL_Triangulation_face(Vertex *v0,
         Vertex *v1,
         Vertex *v2)
      : _v0(v0), _v1(v1), _v2(v2),
        _n0(NULL), _n1(NULL), _n2(NULL)
    {}
    
    
    CGAL_Triangulation_face(Vertex *v0,
         Vertex *v1,
         Vertex *v2,
         Face *n0,
         Face *n1,
         Face *n2)
      : _v0(v0), _v1(v1), _v2(v2),
        _n0(n0), _n1(n1), _n2(n2)
    {}
    
    
    ~CGAL_Triangulation_face()
    {}
    void
    set_vertex(int i, Vertex *v)
    {
        CGAL_kernel_precondition( i == 0 || i == 1 || i == 2);
        switch (i) {
        case 0 :
            _v0 = v;
            break;
        case 1 :
            _v1 = v;
            break;
        default:
            _v2 = v;
        }
    }
    
    
    void
    set_neighbor(int i, Face *n)
    {
        CGAL_kernel_precondition( i == 0 || i == 1 || i == 2);
        switch (i) {
        case 0 :
            _n0 = n;
            break;
        case 1 :
            _n1 = n;
            break;
        default:
            _n2 = n;
        }
    }
    
    Vertex*
    vertex(int i) const
    {
        CGAL_kernel_precondition( i == 0 || i == 1 || i == 2);
        switch (i) {
        case 0 :
            return _v0;
        case 1 :
            return _v1;
        default:
            break;
        }
        return _v2;
    }
    
    
    bool
    has_vertex(Vertex *v) const
    {
        return (_v0 == v) || (_v1 == v) || (_v2 == v);
    }
    
    
    bool
    has_vertex(Vertex *v, int& i) const
    {
        if (v == _v0) {
            i = 0;
            return true;
        }
        if (v == _v1) {
            i = 1;
            return true;
        }
        if (v == _v2) {
            i = 2;
            return true;
        }
        return false;
    }
    
    
    int
    index(Vertex *v) const
    {
        if (v == _v0) {
            return 0;
        }
        if (v == _v1) {
            return 1;
        }
        if (v == _v2) {
            return 2;
        }
        CGAL_kernel_assertion(false); // we should not get here
        return -1;
    }
    Face*
    neighbor(int i) const
    {
        CGAL_kernel_precondition( i == 0 || i == 1 || i == 2);
        switch (i) {
        case 0 :
            return _n0;
        case 1 :
            return _n1;
        default:
            break;
        }
        return _n2;
    }
    
    
    bool
    has_neighbor(Face *n) const
    {
        return (_n0 == n) || (_n1 == n) || (_n2 == n);
    }
    
    
    bool
    has_neighbor(Face *n, int& i) const
    {
        if(n == _n0){
            i = 0;
            return true;
        }
        if(n == _n1){
            i = 1;
            return true;
        }
        if(n == _n2){
            i = 2;
            return true;
        }
        return false;
    }
    
    
    int
    index(Face *n) const
    {
        if (n == _n0) {
            return 0;
        }
        if (n == _n1) {
            return 1;
        }
        if (n == _n2) {
            return 2;
        }
        CGAL_kernel_precondition(false); // we should not get here
        return -1;
    }
    
    int
    ccw(int i) const
    {
        ++i;
        if(i==3){
            i = 0;
        }
        return i;
    }
    
    
    int
    cw(int i) const
    {
        --i;
        if(i==-1){
            i = 2;
        }
        return i;
    }
    
    
    void
    insert(Vertex *v)
    {
        CGAL_kernel_precondition(v != NULL);
        Vertex* v0 = vertex(0);
        Vertex* v2 = vertex(2);
    
        Face* ccwptr = neighbor(ccw(0));
        Face* cwptr  = neighbor(cw(0));
    
        int ccwi, cwi;
        if(ccwptr != NULL) {
            ccwi = cw(ccwptr->index(v0));
        }
        if(cwptr != NULL) {
            cwi  = ccw(cwptr->index(v0));
        }
    
        Face *n1ptr = new Face(v0, v, v2,
                               this, ccwptr, NULL);
    
        Face *n2ptr = new Face(v0, vertex(1), v,
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
    
    bool
    insert(Vertex *v, int i)
    {
        CGAL_kernel_precondition(v != NULL);
        if(neighbor(i) != NULL) {
            cerr << "Insertion impossible as neighbor face already exists" << endl;
            return false;
        }
        Face *f = new Face(v, vertex(cw(i)), vertex(ccw(i)),
                           this, NULL, NULL);
        set_neighbor(i, f);
        v->set_face(f);
        Vertex *w = vertex(ccw(i));
        if(w != NULL){
            w->set_face(f);
        }
    
        return true;
    }
    
    bool
    remove(Vertex *&v)
    {
        CGAL_kernel_precondition(v != NULL);
        int i = index(v);
    
        Face *left, *right, *ll, *rr;
    
        left = neighbor(cw(i));
        right = neighbor(ccw(i));
    
        if(left == NULL || right == NULL) {
            if(left == NULL && right == NULL) {
                Face *n = neighbor(i);
                if(n != NULL) {
                    int ni = n->index(this);
                    n->set_neighbor(ni, NULL);
                    Vertex *q = vertex(cw(i));
                    if(q != NULL){
                        q->set_face(n);
                    }
                } else {
                    cerr << "removal of boundary vertex failed as face has"
                         << "no neighbors" << endl;
                }
                delete this;
                delete v;
                v = NULL;
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
        Vertex *q = left->vertex(li);
    
        ll = left->neighbor(cw(li));
        if(ll != NULL) {
            int lli = ll->index(left);
            ll->set_neighbor(lli, this);
        } else {
            q->set_face(this);
        }
        set_neighbor(cw(i), ll);
    
        delete left;
    
        int ri = ccw(right->index(this));
        q = right->vertex(ccw(ri));
        rr = right->neighbor(ri);
        if(rr != NULL) {
            int rri = rr->index(right);
            rr->set_neighbor(rri, this);
        } else {
            q->set_face(this);
        }
        set_neighbor(ccw(i), rr);
    
        delete right;
    
        set_vertex(i, q);
    
        delete v;
        v = NULL;
        return true;
    }
    
    void
    flip(int i)
    {
        // bl == bottom left, tr == top right
        Face* tl = neighbor(ccw(i));
        Face* n  = neighbor(i);
    
        Vertex* v_cw = vertex(cw(i));
        Vertex* v_ccw = vertex(ccw(i));
    
        // The following seems natural, but it fails if the faces
        // this and n are neighbors on two edges (1-dim triangulation,
        // with infinite faces
        // int ni = n->index(this);
    
        int ni = cw(n->index(v_cw));
    
        CGAL_kernel_assertion( this == n->neighbor(ni) );
    
        Face *br = n->neighbor(ccw(ni));
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
        Face* ncthis = (Face*)this;
        for(int i = 0; i < 3; i++) {
            Face *n = neighbor(i);
            if(n != NULL){
                int ni = n->index(ncthis);
                result = result && (vertex(cw(i)) == n->vertex(ccw(ni)));
                result = result && (vertex(ccw(i)) == n->vertex(cw(ni)));
            } else {
                result = result && (vertex(cw(i))->face() == this);
            }
        }
        return result;
    }
    
private:
    
      Vertex *_v0, *_v1, *_v2;
      Face *_n0, *_n1, *_n2;
    
};

#endif // CGAL_TRIANGULATION_FACE_H
