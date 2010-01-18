/*
 *  test.c
 *  libppmatrix
 *  http://matrix.cappel-nord.de
 *
 *  Created by Patrick Borgeat on 16.01.10.
 *  Copyright 2010 Patrick Borgeat. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 * 
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General
 *  Public License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA  02111-1307  USA
 */


#include <stdio.h>
#include <stdlib.h>

#include "ppmatrix.h"

int main (int argc, char *argv[])
{
	PPM* single = readSinglePPMFromFile("current.txt");
	if(single == NULL)
	{
		printf("Error: %s", ppmErrorMessage());
		exit(1);
	}
	
	PPM* clone = clonePPM(single);
	invertPPM(clone);
	
	PPMLIST* list = initPPMList();
	addPPMToList(list, single);
	addPPMToList(list, clone);
	
	printf("List Size: %d", list->size);
	printf("\n");
	
	printPPM(single);
	printf("\n\n");
	printPPM(list->buffer[1]);
	
	freePPMList(list);
	
	list = readPPMListFromFile("history.txt");
	if(single == NULL)
	{
		printf("Error: %s", ppmErrorMessage());
		exit(1);
	}
	printf("\nList has %d Entries. Buffer size: %d\n", list->size, list->buffer_size);
	
	printf("First PPM:\n");
	printPPM(list->buffer[0]);
	
	printf("\nLast PPM:\n");
	printPPM(list->buffer[list->size-1]);
}