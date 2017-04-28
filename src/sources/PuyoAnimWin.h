/**********************************************************************
	PuyoAnimWin.cpp
	BePuyo-0.1
	
	La classe PuyoAnimWin représente une fenêtre contenant un ou 
	plusieurs PuyoField, et gère les interactions avec le système
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
#ifndef PUYOANIMWIN_H
#define PUYO_ANIMWIN_H

#include <Application.h>
#include <Button.h>
#include <DirectWindow.h>
#include "PuyoView.h"

class PuyoAnimWin : public BWindow {
public:
	PuyoAnimWin(BRect frame);
	void MessageReceived(BMessage *p_msg);
	bool QuitRequested();
	void WindowActivated(bool f);
	bool pause;
	void setPause(bool p);
private:
	// Affichage de la fenetre a l'ecran
	//void display();
	PuyoView * view;
	// bitmap qui stocke tous les elements graphiques
	BBitmap * puyoImage;
	// Compteur pour savoir quand faire tomber la piece
	int compteur;
};

#endif
