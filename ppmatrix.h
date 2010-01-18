/*
 *  ppmatrix.h
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


#define PPMATRIX_DIMENSION 17

#include <stdio.h>

struct ppmatrix
{
	long timestamp;
	char matrix[PPMATRIX_DIMENSION][PPMATRIX_DIMENSION];
};

typedef struct ppmatrix PPM;

struct ppmatrix_list
{
	unsigned int size;
	unsigned int buffer_size;
	PPM** buffer;
};

typedef struct ppmatrix_list PPMLIST;

char* ppmErrorMessage();
PPM* readPPMFromStream(FILE* stream);
PPM* readSinglePPMFromFile(char* fileName);
PPMLIST* readPPMListFromFile(char* filenName);

PPM* clonePPM(PPM* ppm);
void invertPPM(PPM* ppm);

PPMLIST* initPPMList();
void freePPMList(PPMLIST* list);
void addPPMToList(PPMLIST* list, PPM* ppm);

int activeFieldsInPPM(PPM* ppm);


void printPPM(PPM* matrix);