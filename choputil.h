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
#include <config.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

#define tolow(c)  (isupper(c) ? (c)-'A'+'a' : (c))    /* force to lower case */

extern void err(int e);
extern char *basename(char *fname);
extern char *strlwr(char *s);
extern void PrintUsage(const char *prog_name);
extern void PrintVersion(const char *prog_name);
