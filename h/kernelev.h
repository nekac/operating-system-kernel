// File: kernelev.h
// Dogadjaji jezgra sistema

#ifndef _kernelev_h_
#define _kernelev_h_

#include "event.h"
#include "queue.h"

class KernelEv {
public:
	unsigned char ivtNo;
	PCB* blockedT;
	int value;
	Event* sled;
	
	KernelEv(unsigned char no);
	void wait();
	void signal();
};

#endif