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
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Optimisation_sphereCd.h
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/07/01 10:00:10 $
// author(s)     : Sven Schönherr
//                 Bernd Gärtner
//
// coordinator   : ETH Zurich (Bernd Gärtner)
//
// implementation: dD Smallest Enclosing Sphere
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_SPHERECD_H
#define CGAL_OPTIMISATION_SPHERECD_H

// Class declarations
// ==================

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_OPTIMISATION_BASIC_H
#include <CGAL/optimisation_basic.h>
#endif

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif

template <class FT, class PT, class DA>
class CGAL_Optimisation_sphereCd
{
private:
    typedef             typename DA::InputIterator      It;
    
    // hack needed for egcs, see also test programs
    typedef             FT                              FT_;
    
    int                 d;                      // dimension
    int                 m;                      // |B|
    int                 s;                      // |B\cup S|
    
    FT**                q;                      // the q_j's
    FT***               inv;                    // the A^{-1}_{B^j}'s
    FT*                 v_basis;                // the vector v_B
    
    FT*                 x;                      // solution vector
    FT*                 v;                      // auxiliary vector
    
    FT*                 c;                      // center, for internal use
    PT                  ctr;                    // center, for external use
    FT                  sqr_r;                  // squared_radius
    
    DA                  da;                     // data accessor object
    
    
    
    

public:
    CGAL_Optimisation_sphereCd ()
        : d(-1), m(0), s(0)
    {}
    
    void set_da (const DA& dao)
    {
        da = dao;
    }
    
    
    void init (int ambient_dim)
    {
        d = ambient_dim;
        m = 0;
        s = 0;
        sqr_r = -FT(1);
    
        q =             new FT*[d+1];
        inv =           new FT**[d+1];
        v_basis =       new FT[d+2];
        x =             new FT[d+2];
        v =             new FT[d+2];
        c =             new FT[d];
    
        for (int j=0; j<d+1; ++j) {
            q[j] =      new FT[d];
            inv[j] =    new FT*[j+2];
            for (int row=0; row<j+2; ++row)
                inv[j][row] = new FT[row+1];
        }
    
        for (int i=0; i<d; ++i)
            c[i] = FT(0);
        v_basis[0] = FT(1);
    }
    
    
    ~CGAL_Optimisation_sphereCd ()
    {
        if (d != -1)
           destroy();
    }
    
    
    void destroy ()
    {
        for (int j=0; j<d+1; ++j) {
            for (int row=0; row<j+2; ++row)
                delete[] inv[j][row];
            delete[] inv[j];
            delete[] q[j];
        }
        delete[] c;
        delete[] v;
        delete[] x;
        delete[] v_basis;
        delete[] inv;
        delete[] q;
    }
    
    
    void set_size (int ambient_dim)
    {
        if (d != -1)
            destroy();
        if (ambient_dim != -1)
            init(ambient_dim);
        else {
            d = -1;
            m = 0;
            s = 0;
        }
    }
    
    
    void push (const PT& p)
    {
        // store q_m = p by copying its cartesian coordinates into q[m]
        It i; FT *o;
        for (i=da.get_begin(p), o=q[m]; o<q[m]+d; *(o++)=*(i++));
    
        // update v_basis by appending q_m^Tq_m
        v_basis[m+1] = prod(q[m],q[m],d);
    
        if (m==0)
        {
            // set up A^{-1}_{B^0} directly
            FT** M = inv[0];
            M[0][0] = -FT_(2)*v_basis[1];
            M[1][0] = FT_(1);
            M[1][1] = FT_(0);
        } else {
            // set up vector v by computing 2q_j^T q_m, j=0,...,m-1
            v[0] = FT_(1);
            for (int j=0; j<m; ++j)
                v[j+1] = FT_(2)*prod(q[j],q[m],d);
    
            // compute a_0,...,a_m
            multiply (m-1, v, x);               // x[j]=a_j, j=0,...,m
    
            // compute z
            FT z = FT_(2)*v_basis[m+1] - prod(v,x,m+1);
            CGAL_optimisation_assertion (!CGAL_is_zero (z));
            FT inv_z = FT_(1)/z;
    
            // set up A^{-1}_{B^m}
            FT** M = inv[m-1];          // A^{-1}_B, old matrix
            FT** M_new = inv[m];        // A^{-1}_{B'}, new matrix
    
            // first m rows
            int row, col;
            for (row=0; row<m+1; ++row)
                for (col=0; col<row+1; ++col)
                    M_new [row][col] = M[row][col] + x[row]*x[col]*inv_z;
    
            // last row
            for (col=0; col<m+1; ++col)
                M_new [m+1][col] = -x[col]*inv_z;
            M_new [m+1][m+1] = inv_z;
        }
        s = ++m;
        compute_c_and_sqr_r();  // side effect: sets x
    }
    
    
    void pop ()
    {
        --m;
    }
    
    
    FT excess (const PT& p) const
    {
        // compute (c-p)^2
        FT sqr_dist (FT(0));
        It i; FT *j;
        for (i=da.get_begin(p), j=c; j<c+d; ++i, ++j)
            sqr_dist += square (*i-*j);
        return sqr_dist - sqr_r;
     }
    
    
    
    PT center () const
    {
         PT p;
         da.set (p, c, c+d);
         return p;
    }
    
    FT squared_radius () const
    {
         return sqr_r;
    }
    
    int number_of_support_points () const
    {
         return s;
    }
    
    int size_of_basis () const
    {
         return m;
    }
    
    
    bool is_valid (bool verbose = false, int level = true) const
    {
        CGAL_Verbose_ostream verr (verbose);
        for (int j=1; j<m+1; ++j)
            if (!CGAL_is_positive (x[j]))
                return (CGAL__optimisation_is_valid_fail
                    (verr, "center not in convex hull of support points"));
        return (true);
    }
    
    
private:
    void multiply (int j, const FT* vec, FT* res)
    {
        FT** M = inv[j];
        for (int row=0; row<j+2; ++row) {
            res[row] = prod(M[row],vec,row+1);
            for (int col = row+1; col<j+2; ++col)
                res[row] += M[col][row]*vec[col];
        }
    }
    
    
    void compute_c_and_sqr_r ()
    {
        multiply (m-1, v_basis, x);
    
        for (int i=0; i<d; ++i) c[i] = FT(0);
        for (int j=0; j<m; ++j) {
            FT l = x[j+1], *q_j = q[j];
            for (int i=0; i<d; ++i)
                c[i] += l*q_j[i];
        }
        sqr_r = x[0] + prod(c,c,d);
    }
    
    
    FT prod (const FT* v1, const FT* v2, int k) const
    {
        FT res(FT(0));
        for (const FT *i=v1, *j=v2; i<v1+k; res += (*(i++))*(*(j++)));
        return res;
    }
    
    
};

#endif // CGAL_OPTIMISATION_SPHERECD_H

// ===== EOF ==================================================================

