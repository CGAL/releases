// Copyright (c) 2006-2008 Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/Number_types/include/CGAL/Sqrt_extension/Modular_traits.h $
// $Id: Modular_traits.h 63778 2011-05-31 13:03:27Z sloriot $
//
//
// Author(s)     : Michael Hemmer   <hemmer@mpi-inf.mpg.de>


#ifndef CGAL_SQRT_EXTENSION_MODULAR_TRAITS_H
#define CGAL_SQRT_EXTENSION_MODULAR_TRAITS_H

#include <CGAL/basic.h>
#include <CGAL/Residue.h>
#include <CGAL/Modular_traits.h>

namespace CGAL {

/////////// MODULAR_TRAITS BEGIN

template< class COEFF, class ROOT, class ACDE_TAG, class FP_TAG>
class Modular_traits< Sqrt_extension<COEFF,ROOT,ACDE_TAG,FP_TAG> > {
    
private:
  typedef Sqrt_extension<COEFF,ROOT,ACDE_TAG,FP_TAG> EXT; 
    typedef Modular_traits<COEFF> MT_COEFF;
    typedef Modular_traits<ROOT>  MT_ROOT;
    typedef typename MT_COEFF::Residue_type Residue_type_coeff;
    typedef typename MT_ROOT::Residue_type  Residue_type_root;
public:
    typedef EXT NT;
    typedef typename MT_COEFF::Is_modularizable Is_modularizable;
    typedef Sqrt_extension<Residue_type_coeff, Residue_type_root, ACDE_TAG,FP_TAG> Residue_type;
    
    struct Modular_image{
        Residue_type operator()(const EXT& a){
            typename MT_ROOT::Modular_image mod_image_root;
            typename MT_COEFF::Modular_image mod_image_coeff;
            Residue_type_root  root_mod = mod_image_root(a.root());
            if(root_mod != Residue_type_root(0)){
                return Residue_type(mod_image_coeff(a.a0()),
                                  mod_image_coeff(a.a1()),
                                  root_mod);
            }else{
                return Residue_type(mod_image_coeff(a.a0()));
            }
        }
    };

    struct Modular_image_representative{
        NT operator()(const Residue_type& a){
            typename MT_ROOT::Modular_image_representative mod_image_inv_root;
            typename MT_COEFF::Modular_image_representative mod_image_inv_coeff;
            
            if(a.is_extended()){
                return NT(
                        mod_image_inv_coeff(a.a0()),
                        mod_image_inv_coeff(a.a1()),
                        mod_image_inv_root(a.root()));
            }else{
                return NT(mod_image_inv_coeff(a.a0()));
            }
        }
    };
};

/////////// MODULAR_TRAITS END

} //namespace CGAL

#endif
