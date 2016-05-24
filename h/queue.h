// File: queue.h																				  //
// Prioritetni red za ubacivanje niti, klasicna realizacija

#ifndef _queue_h_
#define _queue_h_

#include "thread.h"

class PCB;

class Queue {
	struct Elem {
		PCB* pcb;
		Elem* sled;
		Elem(PCB* p, Elem* s = 0) {
			pcb = p; sled = s;
		}
	};
	Elem *prvi;

public:
	Queue();
	~Queue();
	void clearQ(); // pomocna metoda za unistavanje reda
		
	// korisceno za semafore
	void put(PCB* pcb);			// dodavanje na kraj
	PCB* pop();					// izbacivanje prvog elementa
	
};

#endif