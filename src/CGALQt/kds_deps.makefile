# Copyright (c) 2005,2006  Utrecht University (The Netherlands),
# ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
# INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
# (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
# and Tel-Aviv University (Israel).  All rights reserved.
#
# This file is part of CGAL (www.cgal.org); you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; version 2.1 of the License.
# See the file LICENSE.LGPL distributed with CGAL.
#
# Licensees holding a valid commercial license may use this file in
# accordance with the commercial license agreement provided with the software.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Kinetic_data_structures/src/CGALQt/kds_deps.makefile $
# $Id: kds_deps.makefile 29886 2006-03-31 09:46:24Z drussel $
#
# Author(s)     : Daniel Russel


Kinetic_Qt_widget_2_core$(OBJ_EXT): Kinetic_Qt_widget_2_core.moc

Kinetic_Qt_core$(OBJ_EXT): Kinetic_Qt_core.moc

Kinetic_Qt_timer$(OBJ_EXT): Kinetic_Qt_timer.moc

Kinetic_Qt_window_2$(OBJ_EXT): Kinetic_Qt_window_2.moc

Kinetic_pixmaps$(OBJ_EXT): Kinetic_*.xpm

#CGAL_KDS_INCL_DIR := $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal


Kinetic_Qt_core.moc: $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_core.h
	$(QT_MOC) $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_core.h -o Kinetic_Qt_core.moc


Kinetic_Qt_timer.moc: $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_timer.h
	$(QT_MOC) $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_timer.h -o Kinetic_Qt_timer.moc


Kinetic_Qt_widget_2_core.moc: $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_widget_2_core.h
	$(QT_MOC) $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_widget_2_core.h -o Kinetic_Qt_widget_2_core.moc


Kinetic_Qt_window_2.moc: $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_window_2.h
	$(QT_MOC)  $(CGAL_INCL_DIR)/CGAL/Kinetic/IO/internal/Qt_window_2.h -o Kinetic_Qt_window_2.moc
