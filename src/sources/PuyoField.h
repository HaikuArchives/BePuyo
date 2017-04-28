/**********************************************************************
	PuyoField
	Version 0.1
	
	Classe représentant l'espace de jeu et le score
	
	Une description complete de cette classe est disponible dans la
	documezntation du projet BePuyo
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

#ifndef _PUYO_FIELD_H_
#define _PUYO_FIELD_H_

#include <iostream>
//#include <be/interface/Bitmap.h>
#include "Puyo.h"

/*
	Constantes globales influant sur les dimensions de l'affichage
	Il faudra un jour regroupper toutes les constantes et les mettre dans
	un joli fichier unique pour pouvoir tout modifier dans un seul fichier
	centralisé plutot que 36
*/
const int _FIELD_HEIGHT_ = 13;
const int _FIELD_WIDTH_ = 8;
const int _PUYO_WIDTH_ = 30;
const int _PUYO_HEIGHT_ = 30;
const int _BORDER_PUYO_COLOR_ = -1;


class PuyoField {
public :
	PuyoField();
	void initField();
	// Operations de lecture/ecriture de bas niveau sur l'aire de jeu
	int setPuyo(int x, int y, int color, bool mark=0, bool activ=0);
	int readField(int,int);

	// A partir d'ici, je crois que les fonctions devraient toutes etres privees
	// pour l'instant ca marche, mais il faut rendre le code le plus propre possible

	// Operations de traitement des evenement du jeu
	int puyoExplosion();	// détecte les explosions
	int findGroup(int,int);
	void explodeAll();
	void fallAll();
	int getScore();
	void updateScore();
private:	
	Puyo *matrix[_FIELD_WIDTH_][_FIELD_HEIGHT_];
	void unmarkAll();		
	
	int fieldScore;		// score du PuyoField
	int puyoInGroup;	// sert a calculer le score d'une explosion
};

#endif
