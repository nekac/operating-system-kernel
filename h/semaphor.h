// File: semaphor.h
// Implementacija semafora u okviru sistema

#ifndef _semaphor_h_
#define _semaphor_h_

class KernelSem;

class Semaphore {

public:
  Semaphore (int init=1);
  virtual ~Semaphore ();

  virtual void wait  (); // standardna operacija
  virtual void signal(); // standardna operacija
 
   int val () const;  // Returns the current value of the semaphore

private:
  KernelSem* myImpl;
};

#endif