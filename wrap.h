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

class wrapper{
private:
public:
	vector< pair<float, float> > m_trackData;
	tCarElt* m_car;
	tSituation* m_situation;
	float m_distFromStart;
	float m_trackLength;

	wrapper();

	void updateState(tCarElt* c, tSituation* s);
	void getTrack();
	float getDistanceFromStart(); 

	void print();
	void printStuff(char* name, tdble stuff);
};

#endif
