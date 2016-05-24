// File: queue.cpp
// Realizcija metoda prioritetnog reda

#include <stdio.h>
#include "queue.h"
#include "pcb.h"

// konstruktor
Queue::Queue() {
	prvi = 0;
}

// destruktor
Queue::~Queue() {
	clearQ();
}

// pomocna metoda za brisanje celog reda
void Queue::clearQ() {	
	while(prvi) {
		Elem* stari = prvi;
		prvi = prvi->sled;
		delete stari;
	}
}

// dodavanje na kraj
void Queue::put(PCB* pcb) {
	pcb->blocked = 1;
	Elem* novi = new Elem(pcb);
	Elem *tren;
	if(prvi == 0) {
		prvi = novi;
		return;
	}
	for(tren = prvi; tren->sled; tren = tren->sled);
	tren->sled = novi;
}

// izbacivanje prvog elementa
PCB* Queue::pop() {
	Elem* temp = prvi;
	if(prvi == 0) return 0;
	prvi = prvi->sled;
	temp->pcb->blocked = 0;
	PCB* pcb = temp->pcb;
	delete temp;
	return pcb;
}