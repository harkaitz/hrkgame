#ifndef _HRKAUX_H_
#define _HRKAUX_H_
#ifdef _WIN32
#  define CHARACTER_IS_SEPARATOR(c) (c == '/' || c == '\\')
#else
#  define CHARACTER_IS_SEPARATOR(c) (c == '/')
#endif
/*
 * lic:#
 * lic:#    Copyright (C) 2017  Harkaitz Agirre Ezama
 * lic:#
 * lic:#    This file is part of hrkgame.
 * lic:#
 * lic:#    hrkgame is free software: you can redistribute it and/or modify
 * lic:#    it under the terms of the GNU Lesser General Public License as published by
 * lic:#    the Free Software Foundation, either version 3 of the License, or
 * lic:#    (at your option) any later version.
 * lic:#
 * lic:#    hrkgame is distributed in the hope that it will be useful,
 * lic:#    but WITHOUT ANY WARRANTY; without even the implied warranty of
 * lic:#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * lic:#    GNU Lesser General Public License for more details.
 * lic:#
 * lic:#    You should have received a copy of the GNU Lesser General Public License
 * lic:#    along with hrkgame.  If not, see <http://www.gnu.org/licenses/>.
 * lic:#
 */
#ifdef __cplusplus
extern "C" {
#endif
     const char *hrkaux_basename(const char *filename);
     int         hrkaux_rootname_equal(const char *filename,const char *rootname);
#ifdef __cplusplus
}
#endif

#endif
