// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Optimisation_sphere_d.h
// package       : Min_sphere_d (2.30)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/02/05 10:18:34 $
// author(s)     : Sven Sch�nherr
//                 Bernd G�rtner
//
// coordinator   : ETH Zurich (Bernd G�rtner)
//
// implementation: dD Smallest Enclosing Sphere
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_SPHERE_D_H
#define CGAL_OPTIMISATION_SPHERE_D_H

CGAL_BEGIN_NAMESPACE

// Class declarations
// ==================
// general template
template <class Rep_tag, class FT, class RT, class PT, class Traits>
class Optimisation_sphere_d;

#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphere_d<Homogeneous_tag, FT, RT, PT, Traits>;
    
    
    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphere_d<Cartesian_tag, FT, RT, PT, Traits>;
    
    

#else

   template <class FT, class RT, class PT, class Traits>
   class Optimisation_sphereCd;

   template < class FT, class RT, class PT, class Traits>
   class Optimisation_sphereHd;

#endif

    CGAL_END_NAMESPACE

    // Class interfaces and implementation
    // ==================================
    // includes


    #include <CGAL/Optimisation/basic.h>

    #include <CGAL/Optimisation/assertions.h>


    CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

    // Cartesian version
    // -----------------
    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphere_d<Cartesian_tag, FT, RT, PT, Traits>
    {
    private:
        typedef
          typename Traits::Access_coordinates_begin_d::Coordinate_iterator  It;
        
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
        
        Traits              tco;
        
        
        
        

    public:

        Optimisation_sphere_d& get_sphere (Cartesian_tag)
        {return *this;}

        const Optimisation_sphere_d&
          get_sphere (Cartesian_tag) const
        {return *this;}

        Optimisation_sphere_d (const Traits& t = Traits())
            : d(-1), m(0), s(0), tco (t)
        {}
        
        void set_tco (const Traits& tcobj)
        {
            tco = tcobj;
        }
        
        
        void init (int ambient_dimension)
        {
            d = ambient_dimension;
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
        
        
        ~Optimisation_sphere_d ()
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
        
        
        void set_size (int ambient_dimension)
        {
            if (d != -1)
                destroy();
            if (ambient_dimension != -1)
                init(ambient_dimension);
            else {
                d = -1;
                m = 0;
                s = 0;
            }
        }
        
        
        void push (const PT& p)
        {
            // store q_m = p by copying its cartesian coordinates into q[m]
            It i(tco.access_coordinates_begin_d_object()(p)); FT *o;
            for (o=q[m]; o<q[m]+d; *(o++)=*(i++));
        
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
                CGAL_optimisation_assertion (!CGAL_NTS is_zero (z));
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
            It i(tco.access_coordinates_begin_d_object()(p));
            FT *j;
            for (j=c; j<c+d; ++i, ++j)
                sqr_dist += CGAL_NTS square(*i-*j);
            return sqr_dist - sqr_r;
         }
        
        
        
        PT center () const
        {
             return tco.construct_point_d_object()(d, c, c+d);
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
            Verbose_ostream verr (verbose);
            for (int j=1; j<m+1; ++j)
                if (!CGAL_NTS is_positive (x[j]))
                    return (_optimisation_is_valid_fail
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


    // Homogeneous version
    // -----------------
    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphere_d<Homogeneous_tag, FT, RT, PT, Traits>
    {
    private:
        typedef
          typename Traits::Access_coordinates_begin_d::Coordinate_iterator  It;
        
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
        
        Traits              tco;
        
        

    public:

        Optimisation_sphere_d& get_sphere (Homogeneous_tag t)
        {return *this;}

        const Optimisation_sphere_d&
          get_sphere (Homogeneous_tag t) const
        {return *this;}

        Optimisation_sphere_d (const Traits& t = Traits())
            : d(-1), m(0), s(0), tco(t)
        {}
        
        void set_tco (const Traits& tcobj)
        {
            tco = tcobj;
        }
        
        
        void init (int ambient_dimension)
        {
            d = ambient_dimension;
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
        
        
        ~Optimisation_sphere_d ()
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
        
        
        void set_size (int ambient_dimension)
        {
            if (d != -1)
                destroy();
            if (ambient_dimension != -1)
                init(ambient_dimension);
            else {
                d = -1;
                m = 0;
                s = 0;
            }
        }
        
        
        void push (const PT& p)
        {
            // store q_m = p by copying its cartesian part into q[m]
            It i(tco.access_coordinates_begin_d_object()(p)); RT *o;
            for (o=q[m]; o<q[m]+d; *(o++)=*(i++));
        
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
                denom[0] = -CGAL_NTS square(hom);  // det(\tilde{A}_{B^0})
        
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
                CGAL_optimisation_assertion (!CGAL_NTS is_zero (z));
        
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
            It i(tco.access_coordinates_begin_d_object()(p)); RT *o;
        
        #ifndef CGAL_CFG_NO_MUTABLE
        
                for ( o=v; o<v+d; *(o++)=hD*(*(i++)));
        #else
                for (o=(RT*)v; o<(RT*)v+d; *(o++)=hD*(*(i++)));
        
        #endif // CGAL_CFG_NO_MUTABLE
        
                // get h_p
                RT h_p = *(i++);
                CGAL_optimisation_precondition (!CGAL_NTS is_zero (h_p));
        
                // compute (h_p h D)^2 (c-p)^2
                RT sqr_dist(RT(0));
                for (int k=0; k<d; ++k)
                    sqr_dist += CGAL_NTS square(h_p*c[k]-v[k]);
        
                // compute excess
                return sqr_dist - CGAL_NTS square(h_p)*sqr_r;
             }
        
        
        
        PT center () const
        {
             return tco.construct_point_d_object()(d,c,c+d+1);
        }
        
        FT squared_radius () const
        {
             return FT(sqr_r)/FT(CGAL_NTS square(c[d]));
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
            Verbose_ostream verr (verbose);
            int sign_hD = CGAL::sign(c[d]), s_old = 1,
                s_new = CGAL::sign(v_basis[0][0]), signum;
            for (int j=1; j<m+1; ++j) {
                signum = sign_hD * s_old * s_new * CGAL::sign(x[j]);
                if (!CGAL_NTS is_positive (signum))
                    return (_optimisation_is_valid_fail
                        (verr, "center not in convex hull of support points"));
                s_old = s_new; s_new = CGAL::sign(v_basis[j][0]);
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

#else

    // general template
    template <class Rep_tag, class FT, class RT, class PT,class Traits>
    class Optimisation_sphere_d
    {
        Optimisation_sphereCd<FT,RT,PT,Traits> ms_cart;
        Optimisation_sphereHd<FT,RT,PT,Traits> ms_hom;

    public:

        Optimisation_sphere_d (Cartesian_tag t, const Traits& tr = Traits())
        : ms_cart (tr) {}

        Optimisation_sphere_d (Homogeneous_tag t, const Traits& tr = Traits())
        : ms_hom (tr) {}

        Optimisation_sphereCd<FT,RT,PT,Traits>& get_sphere (Cartesian_tag t)
        {return ms_cart;}

        Optimisation_sphereHd<FT,RT,PT,Traits>& get_sphere (Homogeneous_tag t)
        {return ms_hom;}

        const Optimisation_sphereCd<FT,RT,PT,Traits>& get_sphere
        (Cartesian_tag t) const
        {return ms_cart;}

        const Optimisation_sphereHd<FT,RT,PT,Traits>& get_sphere
        (Homogeneous_tag t) const
        {return ms_hom;}

    };

    // Cartesian version
    // -----------------
    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphereCd

    #define Optimisation_sphere_d Optimisation_sphereCd
    {
    private:
        typedef
          typename Traits::Access_coordinates_begin_d::Coordinate_iterator  It;
        
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
        
        Traits              tco;
        
        
        
        

    public:
        Optimisation_sphere_d (const Traits& t = Traits())
            : d(-1), m(0), s(0), tco (t)
        {}
        
        void set_tco (const Traits& tcobj)
        {
            tco = tcobj;
        }
        
        
        void init (int ambient_dimension)
        {
            d = ambient_dimension;
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
        
        
        ~Optimisation_sphere_d ()
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
        
        
        void set_size (int ambient_dimension)
        {
            if (d != -1)
                destroy();
            if (ambient_dimension != -1)
                init(ambient_dimension);
            else {
                d = -1;
                m = 0;
                s = 0;
            }
        }
        
        
        void push (const PT& p)
        {
            // store q_m = p by copying its cartesian coordinates into q[m]
            It i(tco.access_coordinates_begin_d_object()(p)); FT *o;
            for (o=q[m]; o<q[m]+d; *(o++)=*(i++));
        
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
                CGAL_optimisation_assertion (!CGAL_NTS is_zero (z));
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
            It i(tco.access_coordinates_begin_d_object()(p));
            FT *j;
            for (j=c; j<c+d; ++i, ++j)
                sqr_dist += CGAL_NTS square(*i-*j);
            return sqr_dist - sqr_r;
         }
        
        
        
        PT center () const
        {
             return tco.construct_point_d_object()(d, c, c+d);
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
            Verbose_ostream verr (verbose);
            for (int j=1; j<m+1; ++j)
                if (!CGAL_NTS is_positive (x[j]))
                    return (_optimisation_is_valid_fail
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

    #undef Optimisation_sphere_d


    // Homogeneous version
    // -----------------
    template <class FT, class RT, class PT, class Traits>
    class Optimisation_sphereHd

    #define Optimisation_sphere_d Optimisation_sphereHd
    {
    private:
        typedef
          typename Traits::Access_coordinates_begin_d::Coordinate_iterator  It;
        
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
        
        Traits              tco;
        
        

    public:
        Optimisation_sphere_d (const Traits& t = Traits())
            : d(-1), m(0), s(0), tco(t)
        {}
        
        void set_tco (const Traits& tcobj)
        {
            tco = tcobj;
        }
        
        
        void init (int ambient_dimension)
        {
            d = ambient_dimension;
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
        
        
        ~Optimisation_sphere_d ()
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
        
        
        void set_size (int ambient_dimension)
        {
            if (d != -1)
                destroy();
            if (ambient_dimension != -1)
                init(ambient_dimension);
            else {
                d = -1;
                m = 0;
                s = 0;
            }
        }
        
        
        void push (const PT& p)
        {
            // store q_m = p by copying its cartesian part into q[m]
            It i(tco.access_coordinates_begin_d_object()(p)); RT *o;
            for (o=q[m]; o<q[m]+d; *(o++)=*(i++));
        
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
                denom[0] = -CGAL_NTS square(hom);  // det(\tilde{A}_{B^0})
        
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
                CGAL_optimisation_assertion (!CGAL_NTS is_zero (z));
        
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
            It i(tco.access_coordinates_begin_d_object()(p)); RT *o;
        
        #ifndef CGAL_CFG_NO_MUTABLE
        
                for ( o=v; o<v+d; *(o++)=hD*(*(i++)));
        #else
                for (o=(RT*)v; o<(RT*)v+d; *(o++)=hD*(*(i++)));
        
        #endif // CGAL_CFG_NO_MUTABLE
        
                // get h_p
                RT h_p = *(i++);
                CGAL_optimisation_precondition (!CGAL_NTS is_zero (h_p));
        
                // compute (h_p h D)^2 (c-p)^2
                RT sqr_dist(RT(0));
                for (int k=0; k<d; ++k)
                    sqr_dist += CGAL_NTS square(h_p*c[k]-v[k]);
        
                // compute excess
                return sqr_dist - CGAL_NTS square(h_p)*sqr_r;
             }
        
        
        
        PT center () const
        {
             return tco.construct_point_d_object()(d,c,c+d+1);
        }
        
        FT squared_radius () const
        {
             return FT(sqr_r)/FT(CGAL_NTS square(c[d]));
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
            Verbose_ostream verr (verbose);
            int sign_hD = CGAL::sign(c[d]), s_old = 1,
                s_new = CGAL::sign(v_basis[0][0]), signum;
            for (int j=1; j<m+1; ++j) {
                signum = sign_hD * s_old * s_new * CGAL::sign(x[j]);
                if (!CGAL_NTS is_positive (signum))
                    return (_optimisation_is_valid_fail
                        (verr, "center not in convex hull of support points"));
                s_old = s_new; s_new = CGAL::sign(v_basis[j][0]);
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

    #undef Optimisation_sphere_d

#endif

     CGAL_END_NAMESPACE

    #endif // CGAL_OPTIMISATION_SPHERE_D_H



    // ===== EOF ==================================================================

