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
#include "hrkaux.h"
#include <string.h>
#include <strings.h>
const char *hrkaux_basename(const char *filename) {
     const char *basename = filename;
     for(const char *p = basename;*p;p++)
	  if(CHARACTER_IS_SEPARATOR(*p))
	       basename = p+1;
     return basename;
}
int hrkaux_rootname_equal(const char *filename,const char *rootname) {
     const char *base = hrkaux_basename(filename);
     int len   = strlen(rootname);
     int match =!strncasecmp(base,rootname,len);
     return (match)?(base[len] == '\0' || base[len] == '.'):0;
}
