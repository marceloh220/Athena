/*
  Copyright (c) 2018 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

 */


#include "timer.h"

uint32_t countTime;

ISR(TIMER0_OVF_vect) {
	TCNT0 = 5;
	countTime++;
}

void Temporizador::configura(numerico tempo) {
	PRR &= ~bv(PRTIM0);
	_tempo = tempo;
	estado = 0;
	trava = 0;
	TCCR0A = 0;
	TCCR0B = bv(CS01)|bv(CS00);
#ifndef	ATHENA85
	TIMSK0 = bv(TOIE);
#else
	TIMSK = bv(TOIE0);
#endif
	sei();
	
}

void Temporizador::verifica(logico v) {
	if(v) {
		if(!trava) {
			referencia = countTime;
			trava = 1;
		}
		if( (countTime - referencia) >= _tempo )
			estado = 1;
	}
	else {
		estado = 0;
		trava = 0;
	}
}

logico Temporizador::leitura() {
	return estado;
}

Temporizador::Temporizador() {
}

Temporizador::Temporizador(numerico tempo) {
	configura(tempo);
}

void Temporizador::operator= (logico v) { 
	verifica(v);
}

logico Temporizador::operator& (logico v) {
	return leitura() & v;
}

logico Temporizador::operator| (logico v) {
	return leitura() | v;
}

logico Temporizador::operator! () {
	return !leitura();
}
