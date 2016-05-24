// File: ivtentry.h
// Tabela prekidnih rutina

#ifndef _ivtentry_h_
#define _ivtentry_h_

class Event;
typedef void interrupt (*pInterrupt)(...);

class IVTEntry {

public:
	Event *firstEvent;
	pInterrupt oldRoutine;
	unsigned int IVTNo;
	static IVTEntry *ivtEntry[256];
	IVTEntry(unsigned int entryNo, pInterrupt newRoutine);
	~IVTEntry();
	
	static void pinEvent(unsigned char ivtNo, Event* ev); // Zakaci dogadjaj na ulaz ivt entry tabele ivtentry[ivtNo] = event;
	static void unpinEvent(unsigned char ivtNo, Event* ev);
	void signal();
};

#endif 