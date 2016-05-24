// File: thread.cpp
// Koncept niti 

#include "thread.h"
#include "pcb.h"
#include "lock.h"
#include "stdio.h"
#include "kernelev.h"
#include "kernelse.h"
#include "schedule.h"
#include "timer.h"

// pokretanje niti
void Thread::start(){
	myPCB->start();	
}

// cekanje da nit nad kojom je metoda pozvana ne zavrsi svoje izvrsavanje
void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

// destruktor
Thread::~Thread(){
	waitToComplete();
	delete myPCB;
}

// konstruktor
Thread::Thread(StackSize stackSize, Time timeSlice) {
	myPCB = new PCB(stackSize, timeSlice, this);
}

// eksplicitno preuzimanje kontrole
void dispatch() {
	lock
	_dispatch();
	unlock
}