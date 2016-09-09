// Copyright (c) 1997  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/iostream/src/CGAL/io.cpp $
// $Id: io.cpp 40831 2007-11-07 23:11:19Z spion $
// 
//
// Author(s)     : Andreas Fabri

#include <CGAL/basic.h>
#include <CGAL/IO/io.h>
#include <CGAL/assertions.h>

#include <sstream>
#include <string>

CGAL_BEGIN_NAMESPACE

int IO::mode = std::ios::xalloc();


IO::Mode
get_mode(std::ios& i)
{
    return static_cast<IO::Mode>(i.iword(IO::mode));
}

IO::Mode
set_ascii_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::ASCII;
    return m;
}


IO::Mode
set_binary_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::BINARY;
    return m;
}


IO::Mode
set_pretty_mode(std::ios& i)
{
    IO::Mode m = get_mode(i);
    i.iword(IO::mode) = IO::PRETTY;
    return m;
}

IO::Mode
set_mode(std::ios& i, IO::Mode m)
{
    IO::Mode old = get_mode(i);
    i.iword(IO::mode) = m;
    return old;
}

bool
is_pretty(std::ios& i)
{
    return i.iword(IO::mode) == IO::PRETTY;
}

bool
is_ascii(std::ios& i)
{
    return i.iword(IO::mode) == IO::ASCII;
}


bool
is_binary(std::ios& i)
{
    return i.iword(IO::mode) == IO::BINARY;
}

const char* 
mode_name( IO::Mode m) {
    static const char* const names[] = {"ASCII", "PRETTY", "BINARY" };
    CGAL_assertion( IO::ASCII <= m && m <= IO::BINARY );
    return names[m];
}

void 
swallow(std::istream &is, char d) {
    char c;
    do is.get(c); while (isspace(c));
    if (c != d) {
      std::stringstream msg;
      msg << "input error: expected '" << d << "' but got '" << c << "'";
      CGAL_error_msg( msg.str().c_str() );
    }
}

void 
swallow(std::istream &is, const std::string& s ) {
    std::string t;
    is >> t;
    if (s != t) {
      std::stringstream msg;
      msg << "input error: expected '" << s << "' but got '" << t << "'";
      CGAL_error_msg( msg.str().c_str() );
    }
}

CGAL_END_NAMESPACE
