// File: pcb.h
// Implementacija niti unutar jezgra

#ifndef _pcb_h_
#define _pcb_h_ 

#include "thread.h"
#include "queue.h"
#include "semaphor.h"


extern PCB* running; // tekuca nit
extern PCB* idlePCB; // staticka, ako nema ni jedna druga da radi

class KernelEv;
class KernelSem;

class PCB {
public:

	StackSize stackSize;
	Time timeSlice;
	unsigned ss, sp, finished;
	unsigned* stack;
	Thread* thread;	
	Queue waitToCompleteQueue;    	 // red niti koje cekaju
	int blocked;					 // indikator koji ukazuje da li je nit blokirana
	
	void clear(); // pomocna za brisanje
	void start();
	virtual ~PCB();	
	PCB (StackSize stackSize, Time timeSlice, Thread *t);
	void waitToComplete();
	void createProcess();
	static void runThread();
	void exitThread();
};

void interrupt _dispatch();

#endif