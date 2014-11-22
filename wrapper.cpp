#include "wrapper.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>

Wrapper Wrapper::m_instance = Wrapper();

Wrapper::Wrapper(){
	m_car = NULL;
	m_situation = NULL;
	m_distFromStart = 0.0;
}

Wrapper::~Wrapper(){
}

Wrapper& Wrapper::getInstance(){
	return m_instance;
}

void Wrapper::updateState(tCarElt* c, tSituation* s){
	m_car = c;
	m_situation = s;
	m_distFromStart += 1.0; 
}

void Wrapper::getTrack(){
	tTrackSeg* seg= m_car->pub.trkPos.seg;
	while(seg->id != 0){
		seg = seg->next;
	}
	int nbSeg = seg->prev->id + 1;
	std::vector < std::pair<int, float> > test (nbSeg, std::make_pair(0, 0.0));
	float pred = 0.0;
	for(int i=0; i<nbSeg; i++){
		if(i == 0){
			pred = 0.0;
		}else{
			pred = test[i-1].second;
		}
		test[i] = std::make_pair(i, pred + seg->length);
		seg = seg->next;
		std::cout << "Seg " << i << " : cum_length = " << test[i].second << std::endl;
	}
}

void Wrapper::print(){
	tPublicCar data = m_car->pub;

	std::string txt;
	switch(data.trkPos.type){
		case 0:
			txt = std::string("TL_LPOS_MAIN");
			break;
		case 1:
			txt = std::string("TL_LPOS_SEGMENT");
			break;
		case 2:
			txt = std::string("TL_LPOS_TRACK");
			break;
	}
	std::cout << txt << std::endl;

	tTrackSeg *seg = data.trkPos.seg;

	std::cout << seg->id << std::endl;
	std::cout << seg->length << std::endl;
	std::cout << seg->raceInfo << std::endl;
			
	// printStuff("Middle", data.trkPos.toMiddle);
	printStuff("To Start", data.trkPos.toStart);
	printStuff("From Start", m_distFromStart);
	
	std::cout << std::endl;
	// printStuff("Type", data.trkPos.toMiddle);

}

void Wrapper::printStuff(char* name, tdble stuff){
	std::cout << name << " : ";
	std::cout << stuff << std::endl;
}

void Wrapper::test(){
	std::cout << "testing" << std::endl;
}



