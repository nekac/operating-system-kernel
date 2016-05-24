// File: event.h
// Klasa dogadjaja

#ifndef _event_h_
#define _event_h_

#include "ivtentry.h"

typedef unsigned char IVTNo;
class KernelEv;

class Event {

public:
   Event(IVTNo ivtNo);
  ~Event();
   void wait();

protected:
   friend class KernelEv;
   friend class IVTEntry;
   void signal();

private:
   KernelEv* myImpl;
};

// makro za kreiranje ulaza u IVT
#define PREPAREENTRY(entryNo, old)\
	void interrupt routine##entryNo(...);\
	IVTEntry entry##entryNo(entryNo, &routine##entryNo);\
	void interrupt routine##entryNo(...) {\
		entry##entryNo.signal();\
		if(old)\
			entry##entryNo.oldRoutine();\
	}

#endif