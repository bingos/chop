/*
 * chop 
 * ( and it's nemesis unchop )
 * Copyright (C) 1999 BingosNET Produktions Ltd
 * Written by Kidney Bingos aka Chris Williams
 * <chris@kidney-bingos.demon.co.uk> 
 * With some components borrowed from the Free Software Foundation
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include "choputil.h"
#include "version.h"
#include "tailor.h"

void err(int e) 
{
if(e == IN) {
printf("Error on input\n");
}
else { 
printf("Error on output\n");
}
exit(1);
}

/* ========================================================================
 * Return the base name of a file (remove any directory prefix and
 * any version suffix). For systems with file names that are not
 * case sensitive, force the base name to lower case.
 */
char *basename(fname)
    char *fname;
{
    char *p;

    if ((p = strrchr(fname, PATH_SEP))  != NULL) fname = p+1;
#ifdef PATH_SEP2
    if ((p = strrchr(fname, PATH_SEP2)) != NULL) fname = p+1;
#endif
#ifdef PATH_SEP3
    if ((p = strrchr(fname, PATH_SEP3)) != NULL) fname = p+1;
#endif
#ifdef SUFFIX_SEP
    if ((p = strrchr(fname, SUFFIX_SEP)) != NULL) *p = '\0';
#endif
    if (casemap('A') == 'a') strlwr(fname);
    return fname;
}

/* ========================================================================
 * Put string s in lower case, return s.
 */
char *strlwr(s)
    char *s;
{
    char *t;
    for (t = s; *t; t++) *t = tolow(*t);
    return s;
}

void PrintUsage(const char *prog_name)
{
	printf("Usage: %s [OPTIONS] filename\n",prog_name);

	if(!strcmp(prog_name,"chop")) {
		printf("Chops a file into chunks, by default 1.44Mb floppy disk sized, named chunk1..n\n");
	}
	else {
		printf("Unchops a previously \'chopped\' file.\n");
		printf("Filename is the name of the original \'chopped\' file.\n");
	}

	printf("\n");
	printf("-V, --version  output version information and exit\n");
	printf("-v, --verbose  give verbose output\n");
	printf("-h, --help     display this help message and exit\n");

	if(!strcmp(prog_name,"chop")) {

		printf("-s, --size     specify the \'chunk\' size\n");
		printf("               144m - 1.44Mb Floppy Disk [Default]\n");
		printf("               12m    - 1.2Mb Floppy Disk\n");
		printf("               720k  - 720Kb Floppy Disk\n");
		printf("               zip   - 100Mb Iomega Zip Disk\n");
		printf("               lszip - 120Mb LS-Zip Disk\n");
	}
	
	printf("\nBug reports to chop-bugs@kidney-bingos.demon.co.uk\n"); 
}

void PrintVersion(const char *prog_name)
{
	if(!strcmp(prog_name,"chop")) printf("%s and its nemesis unchop\n\n", prog_name);
	if(!strcmp(prog_name,"unchop")) printf("%s and its nemesis chop\n\n", prog_name);
	printf("version:                    %s\n",VERSION);
	printf("compile date:               %s %s\n",__DATE__,__TIME__);
#if defined __GNUC__
	printf("compiler:                   %s %s\n",COMPILER,__VERSION__);
#else
	printf("compiler:                   %s\n",COMPILER);
#endif
	printf("environment:                %s\n",BUILD_ENV);
	printf("author:                     Kidney Bingos (chris@kidney-bingos.demon.co.uk)\n");
}


