// File: main.cpp
// Klasa koja realizuje Main-a, glavni program poziva

#include <stdio.h>
#include "timer.h"
#include "thread.h"
#include "lock.h"
#include "pcb.h"

int userMain (int argc, char* argv[]);
int End = 0;


class Idle : public Thread {

public:
	Idle() : Thread(2048, 2) {		
		idlePCB = myPCB;
	}
	void run();
};


void Idle::run() {
	while(!End){
		_dispatch();
	}
}


class UserThread: public Thread {

public:
	int argc; char** argv; int povratna;
	UserThread(int argc1,char** argv1):Thread(4096,1){
		argc=argc1; argv=argv1;
	}
	~UserThread(){}
	void run();
};


void UserThread::run(){
	povratna=userMain(argc,argv);
}


int main(int argc, char *argv[]){ // glavni program
	init(); //postavljamo nasu rutinu i cuvamo staru na ulazu 60h
	lock
		Idle* idle = new Idle();
		PCB* mainPCB = new PCB(2048, 0, NULL);
		running = mainPCB;
	unlock
	idle->start();
	UserThread* uthr = new UserThread(argc,argv); // korisnicka nit
	uthr->start(); // pokretanje
	End = 1; //gasi idle nit
	uthr->waitToComplete();
	restore(); //vracamo staru rutinu na ulaz 08h
	int rez=uthr->povratna;
	
	delete uthr; // brisanje korisnicka niti
	delete idle;
	delete mainPCB;
	return rez; // int koji vrati userMain se vraca od strane main-a
}