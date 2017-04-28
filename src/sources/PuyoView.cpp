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
**********************************************************************/

#include "PuyoView.h"
#include "PuyoAnimWin.h"
#include <iostream.h>
#include <Bitmap.h>
#include <TranslationUtils.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#if B_HOST_IS_LENDIAN
#define ARGB_FORMAT B_RGBA32_LITTLE
struct ARGBPixel { uint8 b,g,r,a; };
#else
#define ARGB_FORMAT B_RGBA32_BIG
struct ARGBPixel { uint8 a,r,g,b; };
#endif

PuyoView::PuyoView(BRect rect)
	: BView(rect, NULL, B_FOLLOW_NONE,B_WILL_DRAW) 
{
	playField = new PuyoField();
	puyoImage=BTranslationUtils::GetBitmap("Puyos.png");
	// On balance un Puyo dans le playField		
	puyo = NULL; //new PuyoCouple(2,2,2);
	
	next1= (int)((mrand48()+65535)%6)+1;
	next2= (int)((mrand48()+65535)%6)+1;
	newPuyo();
	bitmap=new BBitmap(rect, ARGB_FORMAT, true);
	bitmapView= new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);
	bitmap->AddChild(bitmapView);
	SetViewColor(B_TRANSPARENT_COLOR);
}


void PuyoView::newPuyo() { 
	//PuyoCouple *unpuyo;
	if(this->puyo!=NULL) delete this->puyo;
	puyo = new PuyoCouple(2,next1,next2); 
	next1= (int)((mrand48()+65535)%6)+1;
	next2= (int)((mrand48()+65535)%6)+1;
}


/*
	Effectue la mise à jour de l'affichage graphique à l'écran
*/
void PuyoView::Draw(BRect r)
{
	DrawBitmap(bitmap,BPoint(0,0));
}


void PuyoView::displayScore()
{
	bitmapView->LockLooper();
	char s_score[50];
	
	for(int i=0;i<50;i++) s_score[i]=0;
	sprintf(s_score,"Score : %d",playField->getScore());
	bitmapView->SetDrawingMode(B_OP_COPY);
	bitmapView->SetHighColor(255,255,255,255);
	bitmapView->SetLowColor(0,31,0,255);
	bitmapView->SetFontSize(24);
	bitmapView->DrawString(s_score , BPoint(Bounds().left+16 , Bounds().bottom-5));
	if  (((PuyoAnimWin *)Window())->pause)
	{
		bitmapView->SetDrawingMode(B_OP_ALPHA);
		bitmapView->SetHighColor(0,0,0,100);
		
		bitmapView->FillRect(Bounds());
		bitmapView->SetDrawingMode(B_OP_COPY);
		bitmapView->SetFontSize(60);
		bitmapView->SetHighColor(255,255,255,255);
		bitmapView->DrawString("Pause", BPoint( 40, Bounds().bottom/2) );	
	}
	bitmapView->Sync();
	bitmapView->UnlockLooper();
	//playField->getScore()
}

void PuyoView::display()
{
	/*
		 Parcours du PuyoField et affichage
		 On cherche à déterminer les coordonnées d'un élément dans la grosse
		 bitmap (qui regroupe tous les éléments graphiques) et ses coordonnées
		 dans la fenêtre.
	*/
	BRect source;
	BRect dest;
	int the_color;
	bitmapView->LockLooper();
	bitmapView->SetDrawingMode(B_OP_COPY);
	bitmapView->SetHighColor(0,31,0,255);
	bitmapView->SetLowColor(0,31,0,255);
	bitmapView->FillRect(Bounds());
	
	for (int i=0; i<_FIELD_HEIGHT_; i++)
	{
		for(int j=0; j<_FIELD_WIDTH_; j++)
		{
			the_color = playField->readField(j,i);
			if (the_color==_BORDER_PUYO_COLOR_)
				the_color=7;
		
		
			// Tous ces chiffres etranges sont les coordonnées des différents éléments graphiques dans
			// la grosse image bitmap					
			// si c'est bien un Puyo ...
			if (the_color > 0 && the_color < 9) 
			{
				source = BRect(129,28+(33*(the_color-1)),159,58+(33*(the_color-1)));
				// si c'est un élément de la bordure ...
			} 
			else if(the_color == _BORDER_PUYO_COLOR_ ) 
				source = BRect(0,0,30,30);
				// si il n'y a rien de remarquable ...
			else if (the_color !=0) 
				source = BRect(129,28+(33*6),159,58+(33*6));
			else 
				source = BRect(0,0,30,30);
		
			// c'est à ces coordonnées qu'on va afficher l'élément dans le fenêtre				
			dest = BRect( 30*j, 32+30*i, 30*(j+1)-1, 32+30*(i+1)-1 );
		
			source.right--; // Patch par GM
			source.bottom--; //            
			
			// hop on l'affiche !
			bitmapView->DrawBitmapAsync(puyoImage, source, dest );
		}
	}
	
	// Il serait peut etre opportun de placer le logo dans une autre vue pour accelerer l'affichage
	//bitmapView->DrawBitmapAsync(puyoImage,BRect(306,32,498,58),BRect (8,0,200,26));
	bitmapView->SetDrawingMode(B_OP_COPY);
	bitmapView->SetHighColor(255,255,255,255);
	bitmapView->SetLowColor(0,0,0,255);
	bitmapView->SetFontSize(28);
	bitmapView->DrawString("Be Puyo", BPoint(Bounds().left+32 , Bounds().top+26));
	
	// on affiche le prochain Puyo
	int i=_FIELD_HEIGHT_+1;int j=_FIELD_WIDTH_-2;
	the_color=next1;
	source = BRect(129,28+(33*(the_color-1)),159-1,58+(33*(the_color-1))-1);
	dest = BRect( 30*j, 30*i, 30*(j+1)-1, 30*(i+1)-1 );
	bitmapView->DrawBitmapAsync(puyoImage, source, dest );
	j++;
	the_color=next2;
	source = BRect(129,28+(33*(the_color-1)),159-1,58+(33*(the_color-1))-1);
	dest = BRect( 30*j, 30*i, 30*(j+1)-1, 30*(i+1)-1 );
	bitmapView->DrawBitmapAsync(puyoImage, source, dest );
	
	bitmapView->SetFontSize(24);
	bitmapView->DrawString("Next", BPoint( 30*j-90, 30*i +26 ));
	bitmapView->Sync();
	bitmapView->UnlockLooper();
	// on update ....
	displayScore();
	Draw(Bounds());	
}


/*
	Méthode qui interprete les touvches du clavier
*/
void PuyoView::KeyDown(const char *bytes, int32 numBytes)
{
	switch(bytes[0])
	{
		case B_LEFT_ARROW:
			puyo->movePuyo(-1, playField);
			display();
			
			break;
		case B_RIGHT_ARROW:
			puyo->movePuyo(1, playField);
			display();
			
			break;
		case B_DOWN_ARROW:
			puyo->fall(playField);
			display();
			
			break;
		case B_UP_ARROW:
			puyo->rotatePuyo(1,playField);
			display();
			
			break;
		case 'p':
		case 'P':
			((PuyoAnimWin *)Window())->setPause(!((PuyoAnimWin *)Window())->pause);
			break;			
	}
}

