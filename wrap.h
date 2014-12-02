#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <tgf.h>
#include <car.h>
#include <track.h>
#include <raceman.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define TR_RGT      1           /**< Right curve */ 
#define TR_LFT      2           /**< Left curve */ 
#define TR_STR      3           /**< Straight */ 

class wrapper{
private:
public:
	vector< pair<float, float> > m_trackData;
	tCarElt* m_car;
	tSituation* m_situation;
	float m_distFromStart;
	float m_trackLength;

	wrapper();

    float getCurrentTime();
	void updateState(tCarElt* c, tSituation* s);
	void getTrack();
	float getDistanceFromStart(); 
	float getCurvature(float seg);
    float positionFromCenterline();

	void print();
	void printStuff(char* name, tdble stuff);
};

#endif
