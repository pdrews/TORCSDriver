#include "wrap.h"

wrapper::wrapper(){
	m_car = NULL;
	m_situation = NULL;
	m_distFromStart = 0.0;
	m_trackLength = 0.0;
}

void wrapper::updateState(tCarElt* c, tSituation* s){
	m_car = c;
	m_situation = s;
	float tmp = m_distFromStart;
	while(tmp > m_trackLength){
		tmp -= m_trackLength;
	}
	m_distFromStart += getDistanceFromStart() - tmp;
	//cout << "distFromStart = " << m_distFromStart << endl;
}

void wrapper::getTrack(){
	tTrackSeg* seg= m_car->pub.trkPos.seg;
	while(seg->id != 0){
		seg = seg->next;
	}
	int nbSeg = seg->prev->id + 1;
	m_trackData = vector < pair<float,float> > (nbSeg, pair<float, float>(0.0, 0.0));
	float pred = 0.0;
	for(int i=0; i<nbSeg; i++){
		if(seg->type2 == 1){
			if(i == 0){
				pred = 0.0;
			}else{
				pred = m_trackData[i-1].first;
			}
			pair<float, float>tmp (pred + seg->length, seg->radius);
			m_trackData.push_back(tmp);
			seg = seg->next;
			//std::cout << "Seg " << i ;
			//cout << " : cum_length = " << m_trackData[i].first;
			//cout << " , curvature = " << m_trackData[i].second << std::endl;
		}
	}
	m_trackLength = m_trackData.back().first; 
}

float wrapper::getDistanceFromStart(){
	if(m_trackLength!=0){
		tTrackSeg* seg= m_car->pub.trkPos.seg;
		float dist = 0.0;
		if(seg->id != 0){
			dist += m_trackData[seg->id - 1].first;
		}
		dist += m_car->pub.trkPos.toStart;
		return dist;
	}else{
		return 0.0;
	}
}


void wrapper::print(){
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

void wrapper::printStuff(char* name, tdble stuff){
	std::cout << name << " : ";
	std::cout << stuff << std::endl;
}



