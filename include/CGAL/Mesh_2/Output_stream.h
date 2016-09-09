// Copyright (c) 2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Mesh_2/include/CGAL/Mesh_2/Output_stream.h $
// $Id: Output_stream.h 32347 2006-07-10 09:25:35Z lrineau $
//
//
// Author(s)     : Laurent Rineau

#ifndef CGAL_MESHES_OUTPUT_STREAM_H

#ifndef CGAL_MESHES_OUTPUT_ON_CERR
#define CGAL_MESHES_OUTPUT_STREAM std::cout
#else
#define CGAL_MESHES_OUTPUT_STREAM std::cerr
#endif

#endif
