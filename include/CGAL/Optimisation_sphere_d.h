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
// file          : include/CGAL/Optimisation_sphere_d.h
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

#ifndef CGAL_OPTIMISATION_SPHERE_D_H
#define CGAL_OPTIMISATION_SPHERE_D_H

// Class declarations
// ==================
template <class FT, class RT, class PT, class DA>
class CGAL_Optimisation_sphereHd;


template <class FT, class PT, class DA>
class CGAL_Optimisation_sphereCd;



// Class interface and implementation
// ==================================
// includes

#ifndef CGAL_REP_CLASS_DEFINED
#error  no representation class defined
#endif // CGAL_REP_CLASS_DEFINED

#ifndef CGAL_OPTIMISATION_SPHEREHD_H
#include<CGAL/Optimisation_sphereHd.h>
#endif

#ifndef CGAL_OPTIMISATION_SPHERECD_H
#include<CGAL/Optimisation_sphereCd.h>
#endif

#ifndef CGAL_REP_DISTINGUISHER
#ifndef CGAL_REP_DISTINGUISHER_H
#include<CGAL/Rep_distinguisher.h>
#endif // CGAL_REP_DISTINGUISHER_H
#endif

template <class R, class PT, class DA>
class CGAL_Optimisation_sphere_d
{
    private:
        typedef typename R::FT                              FT;
        typedef typename R::RT                              RT;
        typedef typename R::Rep_tag                         Rep_tag;

        typedef CGAL_Optimisation_sphereCd<FT,PT,DA>        SC;
        typedef CGAL_Optimisation_sphereHd<FT,RT,PT,DA>     SH;

        typename R::Rep_tag                                 tag;

        CGAL_Rep_distinguisher<SC,SH,Rep_tag>               rd;

    public:

        // construction; passes the data accessor to the representation
        // dependent spheres
        // ---------------------------------------------------------------
        CGAL_Optimisation_sphere_d (const DA& dao = DA())
        {
            set_da (dao);
        }

        // set_da: sets the data accessor
        void set_da (const DA& dao)
        {
            rd.ptr(tag)->set_da (dao);
        }

        // set_size; removes the sphere and reinitializes it with the
        // empty sphere of given dimension
        // ---------------------------------------------------------------
        void set_size (int ambient_dim)
        {
            rd.ptr(tag)->set_size(ambient_dim);
        }

        // push method; pushes p onto B and sets ms to msb(B)
        // ---------------------------------------------------------------
        void push (const PT& p)
        {
            rd.ptr(tag)->push(p);
        }

        // pop method; pops the top element from B and leaves ms unchanged
        // ---------------------------------------------------------------
        void pop ()
        {
            rd.ptr(tag)->pop();
        }

        // excess method; returns a positive multiple of
        // (c-p)^2-r^2. The multiplicative factor is the
        // same for all points p and remains unchanged until
        // the next push operation. If the sphere is empty, the excess
        // is guaranteed to be positive. Precondition is that the
        // ambient dimension of the sphere is not -1.
        // ---------------------------------------------------------------
        RT excess (const PT& p) const
        {
            return rd.ptr(tag)->excess (p);
        }

        // center method; returns the center of ms. If ms is empty, the
        // zero vector is returned. Precondition is that the
        // ambient dimension of the sphere is not -1.
        // ---------------------------------------------------------------
        PT center () const
        {
            return rd.ptr(tag)->center();
        }

        // squared_radius method; returns the squared radius of ms
        // if ms is empty, -1 is returned. Precondition is that the
        // ambient dimension of the sphere is not -1.
        // ---------------------------------------------------------------
        FT squared_radius () const
        {
            return rd.ptr(tag)->squared_radius ();
        }

        // number_of_support_points method; returns the size of
        // S union B
        // ---------------------------------------------------------------
        int number_of_support_points () const
        {
            return rd.ptr(tag)->number_of_support_points ();
        }

        // size_of_basis method; returns |B|
        // ---------------------------------------------------------------
        int size_of_basis () const
        {
            return rd.ptr(tag)->size_of_basis ();
        }

        // is_valid method; checks whether sphere really equls msb(S),
        // S the current support set. The parameter level is not used
        // ---------------------------------------------------------------
        bool is_valid (bool verbose = false, int level = 0) const
        {
            return rd.ptr(tag)->is_valid (verbose, level);
        }
};



#endif // CGAL_OPTIMISATION_SPHERE_D_H

// ===== EOF ==================================================================

