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
// file          : include/CGAL/Optimisation_sphereHd.h
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

#ifndef CGAL_OPTIMISATION_SPHEREHD_H
#define CGAL_OPTIMISATION_SPHEREHD_H

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

template <class FT, class RT, class PT, class DA>
class CGAL_Optimisation_sphereHd
{
private:
    typedef             typename DA::InputIterator      It;
    
    // hack needed for egcs, see also test programs
    typedef             RT                              RT_;
    
    int                 d;                      // dimension
    int                 m;                      // |B|
    int                 s;                      // |B\cup S|
    
    RT**                q;                      // the q_j's
    RT***               inv;                    // the \tilde{A}^{-1}_{B^j}'s
    RT*                 denom;                  // corresponding denominators
    RT**                v_basis;                // the \tilde{v}_B^j
    
    RT*                 x;                      // solution vector
    mutable RT*         v;                      // auxiliary vector
    
    RT*                 c;                      // center, for internal use
    PT                  ctr;                    // center, for external use
    RT                  sqr_r;                  // numerator of squared_radius
    
    DA                  da;                     // data accessor object
    
    

public:
    CGAL_Optimisation_sphereHd ()
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
        sqr_r = -RT(1);
    
        q =             new RT*[d+1];
        inv =           new RT**[d+1];
        denom =         new RT[d+1];
        v_basis =       new RT*[d+1];
        x =             new RT[d+2];
        v =             new RT[d+2];
        c =             new RT[d+1];
    
        for (int j=0; j<d+1; ++j) {
            q[j] =      new RT[d];
            inv[j] =    new RT*[j+2];
            v_basis[j] =new RT[j+2];
            for (int row=0; row<j+2; ++row)
                inv[j][row] = new RT[row+1];
        }
    
        for (int i=0; i<d; ++i)
            c[i] = RT(0);
        c[d] = RT(1);
    }
    
    
    ~CGAL_Optimisation_sphereHd ()
    {
        if (d != -1)
            destroy();
    }
    
    
    void destroy ()
    {
        for (int j=0; j<d+1; ++j) {
            for (int row=0; row<j+2; ++row)
                delete[] inv[j][row];
            delete[] v_basis[j];
            delete[] inv[j];
            delete[] q[j];
        }
        delete[] c;
        delete[] v;
        delete[] x;
        delete[] v_basis;
        delete[] denom;
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
        // store q_m = p by copying its cartesian part into q[m]
        It i; RT *o;
        for (i=da.get_begin(p), o=q[m]; o<q[m]+d; *(o++)=*(i++));
    
        // get homogenizing coordinate
        RT hom = *(i++);
    
        if (m==0)
        {
            // set up v_{B^0} directly
            v_basis[0][0] = hom;
            v_basis[0][1] = prod(q[0],q[0],d);
    
            // set up \tilde{A}^{-1}_{B^0} directly
            RT** M = inv[0];
            M[0][0] = RT_(2)*v_basis[0][1];
            M[1][0] = -hom;
            M[1][1] = RT_(0);
            denom[0] = -square(hom);  // det(\tilde{A}_{B^0})
    
        } else {
            // set up v_{B^m}
            int j;
            RT sqr_q_m = prod(q[m],q[m],d);
            v_basis[m][m+1] = v_basis[m-1][0]*sqr_q_m;
            for (j=0; j<m+1; ++j)
                v_basis[m][j] = hom*v_basis[m-1][j];
    
    
            // set up vector v by computing 2q_j^T q_m, j=0,...,m-1
            v[0] = hom;
            for (j=0; j<m; ++j)
                v[j+1] = RT_(2)*prod(q[j],q[m],d);
    
            // compute \tilde{a}_0,...,\tilde{a}_m
            multiply (m-1, v, x);               // x[j]=\tilde{a}_j, j=0,...,m
    
            // compute \tilde{z}
            RT old_denom = denom[m-1];
            RT z = old_denom*RT_(2)*sqr_q_m - prod(v,x,m+1);
            CGAL_optimisation_assertion (!CGAL_is_zero (z));
    
            // set up \tilde{A}^{-1}_{B^m}
            RT** M = inv[m-1];          // \tilde{A}^{-1}_B, old matrix
            RT** M_new = inv[m];        // \tilde{A}^{-1}_{B'}, new matrix
    
            // first m rows
            int row, col;
            for (row=0; row<m+1; ++row)
                for (col=0; col<row+1; ++col)
                    M_new [row][col]
                        = (z*M[row][col] + x[row]*x[col])/old_denom;
    
            // last row
            for (col=0; col<m+1; ++col)
                M_new [m+1][col] = -x[col];
            M_new [m+1][m+1] = old_denom;
    
            // new denominator
            denom[m] = z;
        }
        s = ++m;
        compute_c_and_sqr_r();
    }
    
    
    void pop ()
    {
        --m;
    }
    
    
    RT excess (const PT& p) const
    {
        // store hD times the cartesian part of p in v
        RT hD = c[d];
        It i; RT *o;
    
    #ifndef CGAL_CFG_NO_MUTABLE
    
            for (i=da.get_begin(p), o=v; o<v+d; *(o++)=hD*(*(i++)));
    #else
            for (i=da.get_begin(p), o=(RT*)v; o<(RT*)v+d; *(o++)=hD*(*(i++)));
    
    #endif // CGAL_CFG_NO_MUTABLE
    
            // get h_p
            RT h_p = *(i++);
            CGAL_optimisation_precondition (!CGAL_is_zero (h_p));
    
            // compute (h_p h D)^2 (c-p)^2
            RT sqr_dist(RT(0));
            for (int k=0; k<d; ++k)
                sqr_dist += square (h_p*c[k]-v[k]);
    
            // compute excess
            return sqr_dist - square(h_p)*sqr_r;
         }
    
    
    
    PT center () const
    {
         PT p;
         da.set (p, c, c+d+1);
         return p;
    }
    
    FT squared_radius () const
    {
         return FT(sqr_r)/FT(square(c[d]));
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
        if (d==-1) return true;
        CGAL_Verbose_ostream verr (verbose);
        int sign_hD = CGAL_sign(c[d]), s_old = 1,
            s_new = CGAL_sign(v_basis[0][0]), sign;
        for (int j=1; j<m+1; ++j) {
            sign = sign_hD * s_old * s_new * CGAL_sign(x[j]);
            if (!CGAL_is_positive (sign))
                return (CGAL__optimisation_is_valid_fail
                    (verr, "center not in convex hull of support points"));
            s_old = s_new; s_new = CGAL_sign(v_basis[j][0]);
        }
        return true;
    }
    
    
private:
    void multiply (int j, const RT* vec, RT* res)
    {
        RT** M = inv[j];
        for (int row=0; row<j+2; ++row) {
            res[row] = prod(M[row],vec,row+1);
            for (int col = row+1; col<j+2; ++col)
                res[row] += M[col][row]*vec[col];
        }
    }
    
    
    void compute_c_and_sqr_r ()
    {
        // solve
        multiply (m-1, v_basis[m-1], x);
    
        // set cartesian part
        for (int i=0; i<d; ++i) c[i] = RT(0);
            for (int j=0; j<m; ++j) {
                RT l = x[j+1], *q_j = q[j];
                for (int i=0; i<d; ++i)
                    c[i] += l*q_j[i];
        }
        c[d] = v_basis[m-1][0]*denom[m-1];                // hD
        sqr_r = x[0]*c[d] + prod(c,c,d); // \tilde{\alpha}hD+c^Tc
    }
    
    
    RT prod (const RT* v1, const RT* v2, int k) const
    {
        RT res = RT(0);
        for (const RT *i=v1, *j=v2; i<v1+k; res += (*(i++))*(*(j++)));
        return res;
    }
    
    
};

#endif // CGAL_OPTIMISATION_SPHEREHD_H

// ===== EOF ==================================================================

