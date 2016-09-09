// Copyright (c) 2001  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Snap_rounding_2/demo/Snap_rounding_2/snap_rounding_2_toolbar.cpp $
// $Id: snap_rounding_2_toolbar.cpp 45456 2008-09-09 21:53:57Z lrineau $
//
//
// Author(s)     : Eli Packer <elip@post.tau.ac.il>

#include <CGAL/basic.h>


#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/pixmaps/movepoint.xpm>
#include <CGAL/IO/pixmaps/point.xpm>
#include <CGAL/IO/pixmaps/line.xpm>
#include <CGAL/IO/pixmaps/arrow.xpm>

#include <qiconset.h>

#include "snap_rounding_2_toolbar.h"

Tools_toolbar::Tools_toolbar(CGAL::Qt_widget * w,
			     QMainWindow *mw, std::list<Segment_2> * l1) :
  QToolBar(mw, "NT")
{
  segment_layer.pass_the_structure(l1);
  w->attach(&segment_layer);

  segment_layer.deactivate();

  //set the widget
  widget = w;

  QIconSet set0(QPixmap( (const char**)arrow_small_xpm ),
                QPixmap( (const char**)arrow_xpm ));
  QIconSet set2(QPixmap( (const char**)line_small_xpm ),
                QPixmap( (const char**)line_xpm ));

  but[0] = new QToolButton(this, "deactivate layer");
  but[0]->setIconSet(set0);
  but[0]->setTextLabel("Deactivate Layer");
  but[1] = new QToolButton(this, "segment layer");
  but[1]->setIconSet(set2);
  but[1]->setTextLabel("Segment layer");

  nr_of_buttons = 2;
  button_group = new QButtonGroup(0, "My_group");
  for (int i = 0; i<nr_of_buttons; i++) {
    button_group->insert(but[i]);
    but[i]->setToggleButton(true);
  }
  button_group->setExclusive(true);

  connect(but[1], SIGNAL(stateChanged(int)),
          &segment_layer, SLOT(stateChanged(int)));
  but[1]->toggle();
};

#include "snap_rounding_2_toolbar.moc"

