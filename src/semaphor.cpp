// File: semaphor.cpp
// Realizcija metoda klase semafora

#include "semaphor.h"
#include "kernelse.h"

// konstruktor
Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init);
}

// destruktor
Semaphore::~Semaphore() {
	delete myImpl;
}

// cekanje da se udje u kriticnu sekciju
void Semaphore::wait() {
	myImpl->wait();
}

// signaliziranje pri izlasku iz kriticne sekcije
void Semaphore::signal() { 
	myImpl->signal();
}

// vrednost semafora
int Semaphore::val() const {
	return myImpl->value;
}