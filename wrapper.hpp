#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <tgf.h>
#include <car.h>
#include <track.h>
#include <raceman.h>
#include "controller.h"

class Wrapper{
	private:
		Wrapper();
		~Wrapper();
		Wrapper& operator= (const Wrapper&){};
		Wrapper (const Wrapper&){};

		static Wrapper m_instance;

		tCarElt* m_car;
		tSituation* m_situation;
		double m_distFromStart;

	public:
		static Wrapper& getInstance();
		void updateState(tCarElt* c, tSituation* s);
		void getTrack();
		void print();
		void printStuff(char* name, tdble stuff);
		void test();
				
};

#endif
