// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Envelope_3/include/CGAL/Envelope_3/Envelope_base.h $
// $Id: Envelope_base.h 41547 2008-01-12 16:02:36Z efif $
//
// Author(s)     : Michal Meyerovitch     <gorgymic@post.tau.ac.il>
//                 Baruch Zukerman        <baruchzu@post.tau.ac.il>
//                 Efi Fogel              <efif@post.tau.ac.il>

#ifndef CGAL_ENVELOPE_BASE_H
#define CGAL_ENVELOPE_BASE_H

CGAL_BEGIN_NAMESPACE

// Envelope types:
enum Envelope_type {
  ENVELOPE_LOWER = 1,
  ENVELOPE_UPPER = 2,
};

// Types of intersection curve between 2 xy-monotone surfaces:
enum Intersection_type {
  INTERSECTION_UNKNOWN = 0,
  INTERSECTION_TRANSVERSAL = 1,
  INTERSECTION_TANGENT = 2
};

// Decision mark for DCEL features:
enum Dac_decision
{
  DAC_DECISION_FIRST = -1,
  DAC_DECISION_BOTH,
  DAC_DECISION_SECOND,
  DAC_DECISION_NOT_SET
};

CGAL_END_NAMESPACE

#endif // CGAL_ENVELOPE_BASE_3_H
