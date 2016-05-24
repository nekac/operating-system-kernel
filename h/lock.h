// File: lock.h
// Za zakljucavanja nad procesima, sve je u .h

#ifndef _lock_h_
#define	_lock_h_

#define lock { asm pushf; asm cli; } // stavi na stek
#define unlock asm popf; // skida sa steka

#endif