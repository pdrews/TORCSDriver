#ifndef SINGLETON_H
#define SINGLETON_H

#include "wrap.h"


class singleton{
private:
	singleton();
	~singleton();
	singleton& operator= (const singleton&){};
	singleton (const singleton&){};

	static singleton m_instance;
public:
	static singleton& getInstance();
	wrapper wrap;
};

#endif
