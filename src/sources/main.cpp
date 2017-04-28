/**********************************************************************
	main.cpp
	BePuyo Version 0.1
	
	Contient la classe PuyoApp qui cree l'application et lance tout
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
#include <Application.h>
#include <Bitmap.h>
#include <TranslationUtils.h>
#include <time.h>
#include <stdlib.h>
#include "Puyo.h"
#include "PuyoAnimWin.h"
#include "PuyoField.h"
class PuyoApp : public BApplication {
public:
	PuyoApp() : BApplication( "application/x-vnd.BePuyo" ) 
	{
		win=new PuyoAnimWin(BRect(20,20,20+_PUYO_WIDTH_*_FIELD_WIDTH_,20+_PUYO_HEIGHT_*_FIELD_HEIGHT_+90));
		//SetPulseRate(2000000);
		SetPulseRate(500000); 
	}

	/* Permet la chutte automatique des Puyo.
	 * La fréquence d'appel est donnée dans le constructeur de la classe
	 * par la méthode SetPulseRate(int)
	 * Cette solution devra à terme être remplacée par quelquechose de plus
	 * fiable (Pulse utilise des messages, et si la file des messages est 
	 * encombree l'utilisateur riqsue de perdre le controle du jeu)
 	 */
	void Pulse() 
	{
		
		win->PostMessage(new BMessage(MON_BOUTON_MSG));
		
	}
private:
	PuyoAnimWin *win;
};

/* Fonction main().
 */
int main() {
	time_t t; 
	PuyoApp app;
	srand48(time(&t));	
	app.Run();
	return(0);
}
