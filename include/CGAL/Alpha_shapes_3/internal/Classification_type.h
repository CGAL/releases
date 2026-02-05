// Copyright (c) 2009  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/v6.1/Alpha_shapes_3/include/CGAL/Alpha_shapes_3/internal/Classification_type.h $
// $Id: include/CGAL/Alpha_shapes_3/internal/Classification_type.h b26b07a1242 $
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Sebastien Loriot
//


#ifndef CGAL_INTERNAL_CLASSIFICATION_TYPE_H
#define CGAL_INTERNAL_CLASSIFICATION_TYPE_H

#include <CGAL/license/Alpha_shapes_3.h>


namespace CGAL{
  namespace internal{
    enum Classification_type {EXTERIOR,SINGULAR,REGULAR,INTERIOR};
  }
}
#endif //CGAL_INTERNAL_CLASSIFICATION_TYPE_H
