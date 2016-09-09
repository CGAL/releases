// Copyright (c) 2008  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/GraphicsView/src/CGALQt4/debug.cpp $
// $Id: debug.cpp 45424 2008-09-09 11:57:39Z afabri $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#include <CGAL/Qt/debug.h>
#include <QDir>

#include <iostream>

namespace CGAL {
namespace Qt {


void traverse_resources(const QString& name, const QString& dirname, int indent)
{
  std::cerr << qPrintable(QString(indent, ' '))
            << qPrintable(name);
  QString fullname = 
    dirname.isEmpty() ?
    name :
    dirname + "/" + name;
  QDir dir(fullname);
  if(dir.exists()) {
    std::cerr << "/\n";
    Q_FOREACH(QString path, dir.entryList())
    {
      traverse_resources(path, fullname, indent + 2);
    }
  }
  else {
    std::cerr << "\n";
  }
}

} // namesapce Qt
} // namespace CGAL
