// File: kernelse.cpp
// Realizacija metoda klase semafora jezgra sistema

#include <stdio.h>
#include "pcb.h"
#include "queue.h"
#include "kernelse.h"
#include "lock.h"
#include "schedule.h"

KernelSem::KernelSem(int init) {
	value = init;
}

void KernelSem::wait() {
	lock
		// Preuzimanje samo ukoliko se pozivalac blokira
		if(--value < 0) {
			blockedQ.put(running);
			_dispatch();
	}
	unlock
}

void KernelSem::signal() {
	lock
		if(value++ < 0){
			PCB* pcb = blockedQ.pop();
			Scheduler::put(pcb);
	}
	unlock
}