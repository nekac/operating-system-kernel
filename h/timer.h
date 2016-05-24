// File: timer.h																				  
// Globalne funkcije za inicijalizaciju i restauraciju prekidne rutine od timer, kao i redefinisan prekid od timer-a 														  //

#ifndef _timer_h_
#define _timer_h_

#include "thread.h"

extern int calledFromDispatch; // pomocna promenljiva, za lociranje poziva

void init();				// Postavljanje nove prekidne rutine
void restore();				// Restauracija stare prekidne rutine
void interrupt timer();		// Prekidna rutina

#endif