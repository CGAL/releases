// Copyright (c) 2007  GeometryFactory (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL: https://github.com/CGAL/cgal/blob/v5.2.3/Triangulation_2/include/CGAL/boost/graph/graph_traits_Regular_triangulation_2.h $
// $Id: graph_traits_Regular_triangulation_2.h 52164b1 2019-10-19T15:34:59+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Andreas Fabri, Fernando Cacciola

#ifndef CGAL_GRAPH_TRAITS_REGULAR_TRIANGULATION_2_H
#define CGAL_GRAPH_TRAITS_REGULAR_TRIANGULATION_2_H

#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/boost/graph/properties_Regular_triangulation_2.h>

// The functions and classes in this file allows the user to
// treat a CGAL Regular_triangulation_2 object as a boost graph "as is". No
// wrapper is needed for the Regular_triangulation_2 object.

#define CGAL_2D_TRIANGULATION_TEMPLATE_PARAMETERS typename GT, typename TDS
#define CGAL_2D_TRIANGULATION CGAL::Regular_triangulation_2<GT, TDS>
#define CGAL_2D_TRIANGULATION_TEMPLATES GT, TDS

#include <CGAL/boost/graph/internal/graph_traits_2D_triangulation.h>

#endif // CGAL_GRAPH_TRAITS_REGULAR_TRIANGULATION_2_H
