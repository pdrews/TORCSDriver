/***************************************************************************

    file                 : racerx.cpp
    created              : Tue Oct 28 10:41:07 EDT 2014
    copyright            : (C) 2002 pauldrews

 ***************************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include "singleton.h"
#include "wrap.h"

static tTrack	*curTrack;

static void initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void endrace(int index, tCarElt *car, tSituation *s);
static void shutdown(int index);
static int  InitFuncPt(int index, void *pt); 
static const char* botname = "racerx";
static const char* botdesc = "6601 project car";

static int counter = 0;

/* 
 * Module entry point  
 */ 
extern "C" int 
racerx(tModInfo *modInfo) 
{
    memset(modInfo, 0, 10*sizeof(tModInfo));

    modInfo->name    = strdup(botname);		/* name of the module (short) */
    modInfo->desc    = strdup(botdesc);	/* description of the module (can be long) */
    modInfo->fctInit = InitFuncPt;		/* init function */
    modInfo->gfId    = 0;		/* supported framework version */
    modInfo->index   = 1;

    return 0; 
} 

/* Module interface initialization. */
static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf  = (tRobotItf *)pt; 

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
    curTrack = track;
    *carParmHandle = NULL; 
} 

/* Start a new race. */
static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
	singleton& sing = singleton::getInstance();
	wrapper& wrap = sing.wrap;
	wrap.updateState(car, s);
	wrap.getTrack();
}
 
/* Drive during race. */
static void
drive(int index, tCarElt* car, tSituation *s)
{
	singleton& sing = singleton::getInstance();
	wrapper& wrap = sing.wrap;
	wrap.updateState(car, s);
	counter = (counter + 1)%10;
	if (counter == 0){
	//	wrap.print();
	}

	memset(&car->ctrl, 0, sizeof(tCarCtrl));

	float angle;
	const float SC = 1.0;

	angle = RtTrackSideTgAngleL(&(car->_trkPos)) - car->_yaw;
	NORM_PI_PI(angle); // put the angle back in the range from -PI to PI
	angle -= SC*car->_trkPos.toMiddle/car->_trkPos.seg->width;

	// set up the values to return
	car->ctrl.steer = angle / car->_steerLock;
	car->ctrl.gear = 1; // first gear
	car->ctrl.accelCmd = 0.3; // 30% accelerator pedal
	car->ctrl.brakeCmd = 0.0; // no brakes
}

/* End of the current race */
static void
endrace(int index, tCarElt *car, tSituation *s)
{
}

/* Called before the module is unloaded */
static void
shutdown(int index)
{
}

