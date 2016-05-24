// File: event.cpp
// Realizacija metoda klase dogadjaja

#include "event.h"
#include "kernelev.h"
#include "ivtentry.h"

Event::Event(IVTNo ivtNo) {
	myImpl = new KernelEv(ivtNo);
	IVTEntry::pinEvent(ivtNo, this);
}

Event::~Event() {
	IVTEntry::unpinEvent(myImpl->ivtNo, this);
	delete myImpl;
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}