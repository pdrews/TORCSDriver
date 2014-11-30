#include "singleton.h"

singleton singleton::m_instance = singleton();

singleton::singleton(){
}

singleton::~singleton(){
}

singleton& singleton::getInstance(){
	return m_instance;
}

