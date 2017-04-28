/**********************************************************************
	PuyoCouple.h
	BePuyo-0.1 

	Decrit les couple de puyo
***********************************************************************

	BePuyo! a free puyopuyo-like game for the BeOS !
	Copyright (C) 2000-2001 Aurélien Girard
	(see index.html for complete documentation and informations)

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**********************************************************************/
#ifndef _PUYO_COUPLE_H_
#define _PUYO_COUPLE_H_

#include "Puyo.h"
#include "PuyoField.h"

/*
	Cette classe decrit les couples de Puyo qui tombent de l'ecran
*/
class PuyoCouple
{
public:
	// Cree un PuyoCouple a l'abscisse x de couleurs ca et cb
	PuyoCouple(int x, int ca, int cb);
	~PuyoCouple();
	/*
		 Deplace le puyo lateralement
		 Vers la gauche si l'entier est négatif strictement
		 Vers la droite si l'entier est positif strictement
		 
		 Renvoie 1 si l'action a reussi, 0 si elle est bloquee
	*/
	int movePuyo(int, PuyoField *);
	/*
		Fait tourner les puyo comme explique dans la doc
		Tourne de pi/2 radians si l'entier est positif
		Tourne de -pi/2 radians si l'entier est négatif
		
		Renvoie 1 si l'action a reussi, 0 si elle est bloquee		
	*/
	int rotatePuyo(int, PuyoField *);
	/*
	 Le PuyoCouple tombe d'une case si c'est possible
	 Renvoie 1 si l'action a reussi, 0 si elle est bloquee	 
	*/
	int fall(PuyoField *);
	// Renvoie le nombre de Puyo du PuyoCouple
	int countPuyo() const;
	void printPuyo () const;
	bool hasMoved;
	int puyoY() const;
	
private:
	void showPuyo(PuyoField *) const;
	void hidePuyo(PuyoField *) const;
	
	Puyo* pMatrix[3][3];
	int x,y;	// coordonnes du coin superieur gauche de la pMatrix;
	int puyoCount;	// nombre de puyo presents dans l'agregat de puyo
};

#endif
