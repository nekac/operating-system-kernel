// File: timer.h																				  
// Realizacija metoda klase tajmera, brojaca	

#include <stdio.h>
#include <schedule.h>
#include "pcb.h"
#include "timer.h"


unsigned oldTimerOFF, oldTimerSEG;
unsigned tss, tsp;
extern void tick(); 				// Metoda implementirana u testu
volatile int counter = 0;
int calledFromDispatch = 0;

void init() {

	asm {
		cli
		push es
		push ax
		
		mov ax, 0
		mov es, ax
		
		mov ax, word ptr es:0020h			// 4*08h = 0020h -> ofset deo
		mov word ptr oldTimerOFF, ax
		mov ax, word ptr es:0022h			// 4*08h + 02h = 0022h -> segmentni deo
		mov word ptr oldTimerSEG, ax
		
		mov word ptr es:0020h, offset timer
		mov word ptr es:0022h, seg timer
		
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax			// 4*60h = 0180h
		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax			// 4*60h + 02h = 0182h
		
		pop ax
		pop es
		sti
	}
}

void restore() {

	asm {
		cli
		push es
		push ax
		
		mov ax, 0
		mov es, ax
		
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax
		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		
		pop ax
		pop es
		sti
	}
}

void interrupt timer() {
	if (!calledFromDispatch) {
		counter--;
		tick(); //samo je receno da se pozove, koristi se u testovima
		asm int 60h
	}
	if(counter == 0 || calledFromDispatch) {
		if (calledFromDispatch)
			calledFromDispatch = 0;
		asm {
			mov tss, ss
			mov tsp, sp
		}
		running->ss = tss;
		running->sp = tsp;
	
		if(!running->finished && !running->blocked && idlePCB != running){
			
				Scheduler::put(running);
		}
		running = Scheduler::get();
		
		if(running==0){
			running = idlePCB;
		}
		
		tss = running->ss;
		tsp = running->sp;
		counter = running->timeSlice;
		
		asm {
			mov ss, tss
			mov sp, tsp
		}
	}
}