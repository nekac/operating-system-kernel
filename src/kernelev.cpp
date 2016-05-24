// File: kernelev.cpp
// Realizacija metoda dogadjaja jezgra sistema

#include "kernelev.h"
#include "lock.h"
#include "pcb.h"
#include "schedule.h"
#include "ivtentry.h"

KernelEv::KernelEv(unsigned char no) {
	value = 0;
	blockedT = running;
	ivtNo = no;
	sled = 0;
}

void KernelEv::wait() {
	lock
	if (running == blockedT)  {
		if(--value < 0) {
			running->blocked = 1;
			_dispatch();
		}
	}
	unlock
}

void KernelEv::signal() {
	lock
	if(value == -1){
		blockedT->blocked = 0;
		Scheduler::put(blockedT);
		value = 0;
	}
	else {
		value = 1;
	}
	_dispatch();
	unlock
}