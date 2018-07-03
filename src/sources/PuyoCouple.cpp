/**********************************************************************
	Puyo.h
	BePuyo-0.1

	Decrit les puyo (la descritpion complete de la classe est 
	disponible dans la documentation
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
#include "PuyoCouple.h"


/*
	Cree un nouveau Puyo
	Parametres :	x l'ordonnee du master-puyo
					ca cb : les couleurs des 2 puyo
*/
PuyoCouple::PuyoCouple(int xx, int ca, int cb) 
{
   hasMoved=false;
	// on initialise la matrice puyo
	for (int i=0; i<3; i++)for(int j=0; j<3; j++) pMatrix[i][j] = new Puyo(0);
	pMatrix[1][1]->setColor(ca);
	pMatrix[2][1]->setColor(cb);
	x=xx;
	y=0;
	puyoCount = 0;
	if (ca != 0) ++puyoCount;
	if (cb != 0) ++puyoCount;
}


/*
	Dis si le puyo est tombe ou tombe encore
	Retour :	>=1 il tombe
				0 	il est tombe
*/
int PuyoCouple::countPuyo() const { return puyoCount; }


/*
	Destructeur
*/
PuyoCouple::~PuyoCouple()
{
	for (int i=0; i<3; i++)
		for(int j=0; j<3; j++) 
			delete pMatrix[i][j] ;
}

/*
	Efface le puyo du PuyoField
	Parametres : pf le PuyoField
*/
void PuyoCouple::hidePuyo(PuyoField *pf) const
{
	for (int i=0; i<3; i++) for(int j=0; j<3; j++)
	{
		if(pMatrix[i][j]->color()!=0) pf->setPuyo(x+i,y+j,0,false,false);
	}
}


/*
	Rend visible un puyo dans le PuyoField (necessaire apres la creation)
	Parametres : pf le PuyoField
*/
void PuyoCouple::showPuyo(PuyoField *pf) const
{
	for (int i=0; i<3; i++) for(int j=0; j<3; j++) 
	{
		if(pMatrix[i][j]->color()!=0) pf->setPuyo(x+i,y+j,pMatrix[i][j]->color(),false,false);
	}
}


/*
	Deplacement horizontal du Puyo
	Parametres :	dep le deplacement horizontal (-1 a gauche, +1 a droite)
					pf le PuyoField
	Retour :		1 si le deplacement est possible
					0 sinon
*/
int PuyoCouple::movePuyo(int dep, PuyoField *pf)
{
	hidePuyo(pf); // On commence par l'effacer du Playfield

	// On verifie que la puyo matrice ne rentre pas en collision avec le PuyoField
	for (int i=0; i<3; i++) for (int j=0; j<3; j++) 
	{
		if ((pMatrix[i][j]->color()*pf->readField(x+i+dep, y+j))!=0)
		{
			// pas de deplacemet
			showPuyo(pf);
			return 0;
		}
	}
	// Si ca passe, on le deplace
	x += dep%2; // deplacement d'une seule vase a la fois
	showPuyo(pf);
	return 1;
}


/*
	Rotation du couple de Puyo
*/
int PuyoCouple::rotatePuyo(int alpha, PuyoField *pf)
{
	Puyo *pm[3][3];

	hidePuyo(pf); 
	for (int i=0; i<3; i++) for (int j=0; j<3; j++) pm[i][j]=NULL;

	if (alpha>0) // sens direct
	{
		pm[1][0] = pMatrix[2][1];
		pm[0][1] = pMatrix[1][0];
		pm[1][2] = pMatrix[0][1];
		pm[2][1] = pMatrix[1][2];
		pm[1][1] = pMatrix[1][1];
	}	
	if (alpha<0) // sens inverse
	{
		pm[2][1] = pMatrix[1][0];
		pm[1][0] = pMatrix[2][1];
		pm[0][1] = pMatrix[1][2];
		pm[1][2] = pMatrix[2][1];
		pm[1][1] = pMatrix[1][1];
	}	

	// On verifie que la puyo matrice ne rentre pas en collision avec le PuyoField
	for(int i=0; i<3; i++) for(int j=0; j<3; j++)
	{
		if(pm[i][j]!=NULL) if ((pm[i][j]->color()*pf->readField(x+i,y+j))!=0)
		{
			showPuyo(pf);
			return 0;
		}
	}

	// Si il n'y a pas eu de collision, on effectue reelement la rotation
	for (int i=0; i<3; i++) for(int j=0; j<3; j++) 
	{
		if (pm[i][j]!=NULL) pMatrix[i][j]=pm[i][j];
	}
	showPuyo(pf);
	return 1;
}


/*
	Effectue un affichage sommaire du Puyo sur la sortie standard
*/
// Je ne l'utilise plus car la classe est suffisament bien foutue pour ne
// pas polluer l'affichage du Terminal avec ca
void PuyoCouple::printPuyo() const
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if (pMatrix[j][i]->color()!=0) cout << pMatrix[j][i]->color();
			else cout << '.';
		}
		cout << endl;
	}
	cout << endl;
}


/*
	Fait tomber un Puyo d'une case. 
	Retour :	1 <=> ok
				0 <=> a touche le sol
*/
int PuyoCouple::fall(PuyoField *pf)
{
	hidePuyo(pf);	
	for (int i=0; i<3; i++) for(int j=0; j<3; j++)
	{
		// on elimine le puyo tombe
		if ( (pMatrix[i][j]->color()!=0) && (pf->readField(x+i, y+j+1)!=0) )
		{
			// On transfert le puyo sur le PuyoField
			pf->setPuyo(x+i, y+j, pMatrix[i][j]->color());
			pMatrix[i][j]->setColor(0);// penser a recentrer le puyo restant			
			puyoCount --;
			// On fait tomber le deuxieme
			while(fall(pf)); return 0;
		}
	}	
	y++;
	hasMoved=true;
	showPuyo(pf);
	return puyoCount;
}

int PuyoCouple::puyoY() const { return y; }
