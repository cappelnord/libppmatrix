/*
 *  ppmatrix.c
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
#include <string.h>

#include "ppmatrix.h"

char* errorMessage = "no error";

char* ppmErrorMessage()
{
	return errorMessage;
}

PPM* readSinglePPMFromFile(char* fileName)
{
	FILE* in = fopen(fileName, "r");
		
	if(in == NULL)
	{
		errorMessage = "Can't open input file!";
		return NULL;
	}
	
	PPM* ret = readPPMFromStream(in);
	fclose(in);
	return ret;
}

PPMLIST* readPPMListFromFile(char* fileName)
{
	FILE* in = fopen(fileName, "r");
	
	if(in == NULL)
	{
		errorMessage = "Can't open file!";
		return NULL;
	}
	
	PPMLIST* ret = initPPMList();
	PPM* ppm;
	
	while(ppm = readPPMFromStream(in))
	{
		addPPMToList(ret, ppm);
	}
	
	fclose(in);
	return ret;
	
}

PPM* readPPMFromStream(FILE* stream)
{
	int ok = 1;
	char buffer;
	PPM* ret = malloc(sizeof(PPM));
	
	ok = ok | fscanf(stream, "%ld", &ret->timestamp);
	
	for(int y = 0; y < PPMATRIX_DIMENSION; y++)
	{
		// newline char
		ok = ok | fscanf(stream, "%c", &buffer);
		for(int x = 0; x < PPMATRIX_DIMENSION; x++)
		{
			ok = ok | fscanf(stream, "%c", &buffer);
			if(buffer == '0')
			{
				ret->matrix[y][x] = 0;
			}
			else
			{
				ret->matrix[y][x] = 1;
			}
		}
	}
	
	// newline char, in case there is another ppm in the stream
	fscanf(stream, "%c", &buffer);
	
	if(ok < 0)
	{
		errorMessage = "Can't read the file!";
		free(ret);
		return NULL;
	}
	
	return ret;
}

PPMLIST* initPPMList()
{
	PPMLIST* ret = malloc(sizeof(PPMLIST));
	
	ret->size = 0;
	ret->buffer_size = 64;
	ret->buffer = malloc(sizeof(PPM*) * 64);
	
	return ret;
}

void freePPMList(PPMLIST* list)
{
	for (int i = 0; i < list->size; i++)
	{
		free(list->buffer[i]);
	}
	free(list->buffer);
	free(list);
}

void addPPMToList(PPMLIST* list, PPM* ppm)
{
	list->size++;
	if(list->size > list->buffer_size)
	{
		list->buffer = realloc(list->buffer, sizeof(PPM*) * list->buffer_size * 2);
		list->buffer_size *= 2;
	}
	
	list->buffer[list->size-1] = ppm;
}

PPM* clonePPM(PPM* ppm)
{
	PPM* ret = malloc(sizeof(PPM));
	memcpy(ret, ppm, sizeof(PPM));
	return ret;
}

void invertPPM(PPM* ppm)
{
	for(int y = 0; y < PPMATRIX_DIMENSION; y++)
	{
		for(int x = 0; x < PPMATRIX_DIMENSION; x++)
		{
			if(ppm->matrix[y][x] != 0)
			{
				ppm->matrix[y][x] = 0;
			}
			else
			{
				ppm->matrix[y][x] = 1;
			}
		}
		
	}
}

void printPPM(PPM* matrix)
{
	printf("Timestamp: %i", matrix->timestamp);
	for(int y = 0; y < PPMATRIX_DIMENSION; y++)
	{
		printf("\n");
		for(int x = 0; x < PPMATRIX_DIMENSION; x++)
		{
			printf("%i", matrix->matrix[y][x]);
		}
	}
}
