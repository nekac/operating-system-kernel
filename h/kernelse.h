// File: kernelse.h
// Semafori jezgra sistema

#ifndef _kernelse_h_
#define _kernelse_h_

#include "queue.h"
#include "semaphor.h"

class KernelSem {
	
public:
	int value;
	Queue blockedQ;
	KernelSem(int init);
	void wait();
	void signal();
};

#endif