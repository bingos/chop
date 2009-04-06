/*
 * chop 
 * ( and it's nemesis unchop )
 * Copyright (C) 1999 BingosNET Produktions Ltd
 * Written by Kidney Bingos aka Chris Williams
 * <chris@kidney-bingos.demon.co.uk> 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getopt.h"
#include "choputil.h"


#define FDHD 1447034
#define FDSD 1258291
#define FDVS 737280
#define IZIP 100663296
#define LZIP 122880000

int main(int argc, char *argv[])
{

	static struct option options[] = 
	{
		{"version", no_argument,NULL,'V'},
		{"verbose", no_argument,NULL,'v'},
		{"help",    no_argument,NULL,'h'},
		{"size",    required_argument,NULL,'s'}
	};
	
	FILE *in, *out;
	int fn;
	char ch;
	char opt;
	char *progname;
	char *filename;
	char *optstring = "Vvhs:";
	char outfiletmp[256];
	char outfilecur[256];
	char number[10];
	int i, file_count, fileind;
	int verboseness = 0;
	int chunk_size = FDHD;

	progname = basename(argv[0]);	
	strlwr(progname);

	while ((opt=getopt_long(argc,argv,optstring,options,NULL)) != EOF ) {
		switch (opt) {
			
			case 'V':
				PrintVersion(progname);
				return 0;

			case 'h':
				PrintUsage(progname);
				return 0;

			case 'v':
				verboseness = 1;
				break;

			case 's':
				if (!strcmp(progname,"chop")) {
					strlwr(optarg);
					if (!strcmp(optarg,"144m")) { 
						chunk_size = FDHD;
						break;
				 	}
					else if (!strcmp(optarg,"1m")) { 
						chunk_size = FDSD; 
						break;
					}
					else if (!strcmp(optarg,"720k")) { 
						chunk_size = FDVS; 
						break;
					}
					else if (!strcmp(optarg,"zip")) { 
						chunk_size = IZIP; 
						break;
					}
					else if (!strcmp(optarg,"lszip")) { 
						chunk_size = LZIP; 
						break;
					}
					else {
						printf("Invalid size specified\n");
					}
				} else if (!strcmp(progname,"unchop")) {
					printf("Invalid option for %s\n",progname);
				}
			default:
				fprintf(stderr,"Try '%s --help' for more information.\n",progname);
				return 1;
		}
	}
	
	file_count = argc - optind;

	fileind = optind++;

	if(file_count == 0) {

		PrintUsage(progname);
		exit(1);

	} else if(!strcmp(progname,"chop")) {

		if((in=fopen(argv[fileind], "rb")) == NULL) {
			printf("Bad magic. Can\'t open specified file %s\n", argv[fileind]);
			exit(1);
		} else if(verboseness) {
			printf("%s opened for input\n",argv[fileind]);
		}

		fn = 1;
		filename = basename(argv[fileind]);
		strcpy(outfiletmp,filename);
		strcat(outfiletmp,".chunk");

		while(!feof(in)) {

			sprintf(number,"%i",fn);
			strcpy(outfilecur,outfiletmp);
			strcat(outfilecur,number);

			if((out=fopen(outfilecur, "wb")) == NULL) {
				printf("Bad Magic. Can\'t open specified output file %s\n", outfilecur);
				exit(1);
			} else if(verboseness) {
				printf("Writing to %s\n",outfilecur);
			}

			for(i=1; i < chunk_size; i++) {

				ch=getc(in);
				if(ferror(in)) err(IN);
				if(feof(in)) { 
					if(fn==1) {
						printf("Input file is less than specified chunk size.\nAbandoning chop of %s\n",argv[fileind]);
						if(fclose(out)) printf("Bad magic. Can\'t close output file %s\n",outfilecur);
						if(remove(outfilecur)) printf("Bad magic. Can't remove output file %s\n",outfilecur);
						exit(1);
					}	
					break;
				}
				putc(ch, out);
				if(ferror(out)) err(OUT);
			}
			fn++;
		}

	} else if(!strcmp(progname,"unchop")) {

		if((out=fopen(argv[fileind], "wb")) == NULL) {
			printf("Bad magic. Can\'t open specified output file %s\n", argv[fileind]);
			exit(1);
		} else if(verboseness) {
			printf("%s opened for output\n",argv[fileind]);
		}

		fn = 1;
		strcpy(outfiletmp,argv[fileind]);
		strcat(outfiletmp,".chunk");

		while(1) {

			sprintf(number,"%i",fn);
			strcpy(outfilecur,outfiletmp);
			strcat(outfilecur,number);

			if((in=fopen(outfilecur, "rb")) == NULL) {
				break;
			} else if(verboseness) {
				printf("Reading from %s\n",outfilecur);
			}

			while(!feof(in)) {

				ch=getc(in);
				if(ferror(in)) err(IN);
				if(!feof(in)) putc(ch, out); 
				if(ferror(out)) err(OUT);
			}
			fn++;
		}


	}

	exit(0);
}
