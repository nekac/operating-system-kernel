// File: pcb.cpp
// Implementacija niti unutar jezgra

#include <dos.h>
#include <schedule.h>
#include "pcb.h"
#include "queue.h"
#include "lock.h"
#include "timer.h"
#include "kernelev.h"
#include "kernelse.h"


PCB* running; // ona nit koja trenutno radi
PCB* idlePCB; // idle nit

void PCB::clear(){					 // pomocna funkcija za brisanje
	delete [] stack;
}

// pokretanje niti
void PCB::start(){
	createProcess();
	if(idlePCB != this){ // ako nije idle nit
		Scheduler::put(this);
	}
}

// destruktor
PCB::~PCB(){
	clear();
}
			 
// konstruktor
PCB::PCB (StackSize stackSize, Time timeSlice, Thread* t) : 
		stackSize(stackSize/2), timeSlice(timeSlice), blocked(0){	
			thread = t;
}

// blokira pozivajucu nit sve dok nit nad objektom nad kojim je pozvana ne zavrsi
void PCB::waitToComplete() {
	lock
		if(this->finished == 0 && idlePCB != this) {
			waitToCompleteQueue.put(running);
			dispatch();
	}
	unlock
}

// kreiranje procesa niti
void PCB::createProcess() {
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;	// Setovan I flag u registru PSW; I flag je 9. bit registra PSW
	stack[stackSize - 2] = FP_SEG(PCB::runThread);
	stack[stackSize - 3] = FP_OFF(PCB::runThread);
	
	ss = FP_SEG(stack + stackSize - 12);
	sp = FP_OFF(stack + stackSize - 12);

	finished = 0;
}

// pokretanje niti, enkapsulirana run() metoda
void PCB::runThread() {
	running->thread->run();
	running->exitThread(); // kada zavrsi poziva metodu exitThread da bi izasla
}

// zavrsavanje niti i izlazak
void PCB::exitThread() {
	lock
		running->finished = 1;
		PCB* temp = waitToCompleteQueue.pop();
		while(temp) {
			Scheduler::put(temp);
			temp = waitToCompleteQueue.pop();
	}
	unlock
	dispatch();
}

// definisanje sistemske metode za promenu konteksta
void interrupt _dispatch() {
	calledFromDispatch = 1;
	timer();
}