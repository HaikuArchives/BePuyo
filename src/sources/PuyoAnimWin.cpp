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


#include "PuyoAnimWin.h"
#include <Alert.h>
#include "string.h"
#include "stdio.h"
PuyoAnimWin::PuyoAnimWin(BRect frame) 
	: BWindow(frame,"BePuyo 0.1",B_TITLED_WINDOW,B_NOT_RESIZABLE)
{
	
	BRect b=Bounds();
	view=new PuyoView(b);
	AddChild(view);
	view->MakeFocus();	// important pour que le clavier marche
	compteur=0;
	pause=false;
	Show();
}



void PuyoAnimWin::MessageReceived( BMessage * p_msg )
{
	switch(p_msg->what)
	{
		// Effectue une itération
		case MON_BOUTON_MSG:
		{
			if(!pause)
			{
				if (view->puyo->fall(view->playField)==0 && view->puyo->countPuyo()==0)
				{
					if ((view->playField->readField(3,1)+view->playField->readField(4,1))!=0)
					{
						char *strGameOver=new char[35];
						sprintf(strGameOver,"Game Over! Score %i", view->playField->getScore());
						pause=true; // pour eviter d'ouvrir 100000 d'Alert
						BAlert *alert = new BAlert(	NULL, strGameOver,"OK");
						alert->Go(new BInvoker(new BMessage(RESTART),this));
					}
					// on explose les puyos adjacents!
					while(view->playField->puyoExplosion()!=0)view->display();
					view->displayScore();
					// On ajoute un nouveau couple de Puyo
					view->newPuyo();
				}
				view->display();
			}
			break;
		}
		case RESTART:
		{
			view->playField->initField();
			pause=false;
			break;
		}
		case B_QUIT_REQUESTED:
			QuitRequested();
			break;
		default:
			BWindow::MessageReceived( p_msg );
	}
}

void PuyoAnimWin::setPause(bool p)
{
	pause=p;
	view->display();
}
void PuyoAnimWin::WindowActivated(bool f)
{
	
	setPause(!f);
	
}
bool PuyoAnimWin::QuitRequested() {
	be_app->PostMessage(B_QUIT_REQUESTED); 
	return(true);
}
