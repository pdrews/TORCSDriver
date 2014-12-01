#include "singleton.h"

singleton singleton::m_instance = singleton();

singleton::singleton() : myArbiter(300,3){
}

singleton::~singleton(){
}

singleton& singleton::getInstance(){
	return m_instance;
}

