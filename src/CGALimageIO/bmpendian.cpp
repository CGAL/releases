// Copyright (c) 2005-2008 ASCLEPIOS Project, INRIA Sophia-Antipolis (France)
// All rights reserved.
//
// This file is part of the ImageIO Library, and as been adapted for
// CGAL (www.cgal.org).
// You can redistribute it and/or  modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation;
// version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// These files are provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/CGALimageIO/src/CGALimageIO/bmpendian.cpp $
// $Id: bmpendian.cpp 45591 2008-09-16 12:45:40Z lrineau $
//
//
// Author(s)     :  ASCLEPIOS Project (INRIA Sophia-Antipolis), Laurent Rineau


/*
 * These functions read and write our basic integer types from a little-endian
 * file.  The endian and word-size of the host machine will not affect this
 * code.  The only assumption made is that the C data type (char) is one byte
 * long.  This should be a safe assumption.
 */

#include <stdio.h>
#include "bmptypes.h"
#include "bmpendian.h"

/*****************************************************************************
*
* Read functions.  All read functions take an open file pointer as the first
* parameter and a pointer to data as the second parameter.  The return value
* will be 0 on success, and EOF on failure.  If successful, the second
* parameter will point to the data read.
*/

/*
 * The CGAL_INT8 and CGAL_UINT8 types are stored as a single byte on disk.  The INT8
 * type is a signed integer with range (-128..127).  The CGAL_UINT8 type is an
 * unsigned integer with range (0..255).
 */
int readINT8little(FILE *f, CGAL_INT8 *i)
{
    int rc;
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    *i = (rc & 0xff);
    return 0;
}

int readUINT8little(FILE *f, CGAL_UINT8 *i)
{
    int  rc;
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    *i = (rc & 0xff);
    return 0;
}


/*
 * The CGAL_INT16 and CGAL_UINT16 types are stored as two bytes on disk.  The INT16 type
 * is a signed integer with range (-32768..32767).  The CGAL_UINT16 type is an
 * unisgned integer with range (0..65535).
 */
int readINT16little(FILE *f, CGAL_INT16 *i)
{
    int rc;
    CGAL_INT16 temp = 0;
    
    temp = (fgetc(f) & 0xff);
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    temp |= ((rc & 0xff) << 8);
    *i = temp;
    return 0;
}

int readUINT16little(FILE *f, CGAL_UINT16 *i)
{
    int rc;
    CGAL_UINT16 temp = 0;
    
    temp = (fgetc(f) & 0xff);
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    temp |= ((rc & 0xff) << 8);
    *i = temp;
    return 0;
}

/*
 * The CGAL_INT32 and CGAL_UINT32 types are stored as four bytes on disk.  The INT32
 * type is a signed integer with range (-2147483648..2147483647).  The CGAL_UINT32
 * type is an unisgned integer with range (0..4294967295).
 */
int readINT32little(FILE *f, CGAL_INT32 *i)
{
    int rc;
    CGAL_INT32 temp = 0;
    
    temp = ((long)fgetc(f) & 0xff);
    temp |= (((long)fgetc(f) & 0xff) << 8);
    temp |= (((long)fgetc(f) & 0xff) << 16);
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    temp |= (((long)rc & 0xff) << 24);
    *i = temp;
    return 0;
}

int readUINT32little(FILE *f, CGAL_UINT32 *i)
{
    int rc;
    CGAL_UINT32 temp = 0;
    
    temp = ((long)fgetc(f) & 0xff);
    temp |= (((long)fgetc(f) & 0xff) << 8);
    temp |= (((long)fgetc(f) & 0xff) << 16);
    
    rc = fgetc(f);
    if (rc == EOF)
	return rc;
    
    temp |= (((long)rc & 0xff) << 24);
    *i = temp;
    return 0;
}

/*****************************************************************************
*
* Write functions.  All write functions take an open file pointer as the first
* parameter and a data as the second parameter.  The return value will be 0 on
* success, and EOF on failure.  If successful, the second parameter will have
* been written to the open file.
*/

int writeINT8little(FILE *f, CGAL_INT8 i)
{
    return fputc(i, f);
}

int writeUINT8little(FILE *f, CGAL_UINT8 i)
{
    return fputc(i, f);
}

int writeINT16little(FILE *f, CGAL_INT16 i)
{
    int rc;
    
    rc = fputc((i & 0xff), f);
    if (rc == EOF)
	return rc;
    
    return fputc(((i >> 8) & 0xff), f);
}

int writeUINT16little(FILE *f, CGAL_UINT16 i)
{
    int rc;
    
    rc = fputc((i & 0xff), f);
    if (rc == EOF)
	return rc;
    
    return fputc(((i >> 8) & 0xff), f);
}

int writeINT32little(FILE *f, CGAL_INT32 i)
{
    int rc;
    
    rc = fputc((i & 0xff), f);
    if (rc == EOF)
	return rc;
    
    rc = fputc(((i >> 8) & 0xff), f);
    if (rc == EOF)
	return rc;
    
    rc = fputc(((i >> 16) & 0xff), f);
    if (rc == EOF)
	return rc;
    
    return fputc(((i >> 24) & 0xff), f);
}


int writeUINT32little(FILE *f, CGAL_UINT32 i)
{
    int rc;
    
    rc = fputc((i & 0xff), f);
    if (rc == EOF)
	return rc;
    
    rc = fputc(((i >> 8) & 0xff), f);
    if (rc == EOF)
	return rc;
    
    rc = fputc(((i >> 16) & 0xff), f);
    if (rc == EOF)
	return rc;
    
    return fputc(((i >> 24) & 0xff), f);
}

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:4
 * c-brace-offset:-4
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-4
 * End:
 */
