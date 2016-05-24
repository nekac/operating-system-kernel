// File: ivtentry.cpp
// Realizacija metoda klase tabela prekidnih rutina

#include <dos.h> // zbog getvect i setvect
#include "ivtentry.h"
#include "event.h"
#include "kernelev.h"

IVTEntry* IVTEntry::ivtEntry[256] = { 0 };

//konstruktor
IVTEntry::IVTEntry(unsigned int entryNo, pInterrupt newRoutine) {
	IVTNo = entryNo;
	ivtEntry[entryNo] = this;
	firstEvent = 0;
	oldRoutine = getvect(entryNo);
	setvect(entryNo, newRoutine);
}

//destruktor
IVTEntry::~IVTEntry() {
	setvect(IVTNo, oldRoutine);
}

// dodavanje dogadjaja
void IVTEntry::pinEvent(unsigned char ivtNo, Event* ev) {
	ev->myImpl->sled = ivtEntry[ivtNo]->firstEvent;
	ivtEntry[ivtNo]->firstEvent = ev;
}

// izbacivanje dogadjaja
void IVTEntry::unpinEvent(unsigned char ivtNo, Event* ev) {
	Event* pret = 0;
	Event* tek = ivtEntry[ivtNo]->firstEvent;
	while (tek) {
		if (tek == ev) {
			if (pret)
				pret->myImpl->sled = tek->myImpl->sled;
			else
				ivtEntry[ivtNo]->firstEvent = tek->myImpl->sled;
			tek->myImpl->sled = 0;
			return;
		}
		pret = tek;
		tek = tek->myImpl->sled;
	}
}

// signaliziranje svim, otkacinjanje
void IVTEntry::signal() {
	for (Event* tek = ivtEntry[IVTNo]->firstEvent; tek; tek = tek->myImpl->sled)
		tek->signal(); // realizovano u kernelev
}