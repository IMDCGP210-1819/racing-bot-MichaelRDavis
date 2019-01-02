/***************************************************************************

    file                 : robot_base.cpp
    created              : Mon 13 Feb 11:40:23 GMT 2017
    copyright            : (C) 2002 Author

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include "../robot_base_davis/Robots/Robot.h"

static tTrack	*curTrack;

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void endrace(int index, tCarElt *car, tSituation *s);
static void shutdown(int index);
static int  InitFuncPt(int index, void *pt); 

#define BUFFER_SIZE 20
#define NUM_ROBOTS 2
static char* robotNames[NUM_ROBOTS] = {"robot_davis", "robot_base"};
static Robot* robotCars[NUM_ROBOTS];

/* 
 * Module entry point  
 */ 
extern "C" int 
robot_base_davis(tModInfo *modInfo) 
{
	char buffer[BUFFER_SIZE];
	int index;

    memset(modInfo, 0, 10*sizeof(tModInfo));

	for (int i = 0; i < NUM_ROBOTS; i++)
	{
		sprintf(buffer, "Robot: %d", i + 1);
		robotNames[i] = strdup(buffer);
		modInfo[i].name = robotNames[i];
		modInfo[i].desc = strdup("");
		modInfo[i].fctInit = InitFuncPt;
		modInfo[i].gfId = ROB_IDENT;
		modInfo[i].index = i;
	}

    //modInfo->name    = strdup("robot_base_davis");		/* name of the module (short) */
    //modInfo->desc    = strdup("");	/* description of the module (can be long) */
    //modInfo->fctInit = InitFuncPt;		/* init function */
    //modInfo->gfId    = ROB_IDENT;		/* supported framework version */
    //modInfo->index   = 1;

    return 0; 
} 

/* Module interface initialization. */
static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf  = (tRobotItf *)pt; 

	robotCars[index] = new Robot(index);

    itf->rbNewTrack = initTrack; /* Give the robot the track view called */ 
				 /* for every track change or new race */ 
    itf->rbNewRace  = newrace; 	 /* Start a new race */
    itf->rbDrive    = drive;	 /* Drive during race */
    itf->rbPitCmd   = NULL;
    itf->rbEndRace  = endrace;	 /* End of the current race */
    itf->rbShutdown = shutdown;	 /* Called before the module is unloaded */
    itf->index      = index; 	 /* Index used if multiple interfaces */
    return 0; 
} 

/* Called for every track change or new race. */
static void  
initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s) 
{ 
    //curTrack = track;
    //*carParmHandle = NULL;

	robotCars[index]->InitTrack(track, carHandle, carParmHandle, s);
} 

/* Start a new race. */
static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
	robotCars[index]->NewRace(car, s);
} 

/* Drive during race. */
static void  
drive(int index, tCarElt* car, tSituation *s)
{
	robotCars[index]->Drive(car, s);
}

/* End of the current race */
static void
endrace(int index, tCarElt *car, tSituation *s)
{
	robotCars[index]->EndRace(car, s);
}

/* Called before the module is unloaded */
static void
shutdown(int index)
{
	free(robotNames[index]);
	delete robotCars[index];
}

