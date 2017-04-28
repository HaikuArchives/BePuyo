/**********************************************************************
	PuyoView.cpp
	BePuyo-0.1
	
	Cette classe contient la représentation graphique d'un PuyoField.
	Elle se charge des interactions avec l'utilisateur pour un Field.
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
**********************************************************************/#include <View.h>
#include "PuyoCouple.h"
#include "PuyoField.h"

#ifndef _PUYO_VIEW_H_
#define _PUYO_VIEW_H_

class PuyoView : public BView{
public:
	// Constructeur
	PuyoView(BRect rect);
	
	void display();
	void displayScore();
	void Draw(BRect r);
	void KeyDown(const char *bytes, int32 numBytes);
	// Ajoute un nouveau puyo quand le precedent est tombe
	void newPuyo();
	PuyoField * playField;
	// le puyo-couple qui est en train de tomber
	PuyoCouple *puyo;

private:
	int next1,next2;
	BBitmap *puyoImage;
	BView *bitmapView;
	BBitmap *bitmap;
};
#endif
