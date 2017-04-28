/**********************************************************************
	PuyoField.cpp
	BePuyo-0.1
	
	Cette classe représente une aire de jeu, et le score associé
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

#include "PuyoField.h"


/**********************************************************************
	Classe PuyoField
	
	Decrit l'aire de jeu et fournit les methodes de manipulation.
	Description complete de la classe dans la documentation
**********************************************************************/

/*
	Le constructeur
	Le PuyoField est represente par une matrice [lignes][colonnes]
	dont les dimensions sont donnees par les constantes	_FIELD_WIDTH_ et _FIELD_HEIGHT_
	La premiere et la derniere colonne ainsi que la derniere ligne sont reservees et remplies
	de 'puyo fantomes' dont la couleur est _BORDER_PUYO_COLOR_
*/
PuyoField::PuyoField() 
{
	for (int i=0; i<_FIELD_WIDTH_; i++)
		for (int j=0; j<_FIELD_HEIGHT_; j++)
			matrix[i][j] = new Puyo(0);
	initField();
	
}


void PuyoField::initField()
{
	for (int i=0; i<_FIELD_WIDTH_; i++)
		for (int j=0; j<_FIELD_HEIGHT_; j++)
			matrix[i][j]->setColor(0);
	// On ajoute de 'puyo fantomes' le long du field
	for (int i=0; i<_FIELD_WIDTH_; i++) 
		matrix[i][_FIELD_HEIGHT_ -1]->setColor(_BORDER_PUYO_COLOR_);
	for (int i=0; i<_FIELD_HEIGHT_; i++) 
	{
		matrix[_FIELD_WIDTH_ -1][i]->setColor(_BORDER_PUYO_COLOR_);
		matrix[0][i]->setColor(_BORDER_PUYO_COLOR_);
	}
	fieldScore=0;
	puyoInGroup=0;
}

/*
	Remplis une cellule du PuyoField avec un puyo d'une certaine couleur
	Parametres :	x		l'abcsisse du puyo dans le PuyoField
					y		l'ordonnee du puyo dans le PuyoField
					color	la couleur du puyo
					mark	le Puyo est-il marqué ?
					activ   le Puyo est il dans le groupe courant ?
	Retour :		1 si l'operation s'est bien deroulee
					0 si les coordonees sont erronees
*/
int PuyoField::setPuyo(int x, int y, int color, bool mark, bool activ) 
{
	// On verifie que les coordonnes sont bien dans le PuyoField
	if ( x < _FIELD_WIDTH_ && x > 0 && y < _FIELD_HEIGHT_ && y >= 0) 
	{
		matrix[x][y]->setColor(color);
		if (mark) matrix[x][y]->mark(); else matrix[x][y]->unmark();
		if (activ) matrix[x][y]->markActive(); else matrix[x][y]->unmarkActive();
		return 1;
	} else return 0;
}


/*
	Renvoie la couleur d'un puyo
	Parametres :	x et y les coordonnees
	Retour :		la couleur du puyo si il existe
	 				_BORDER_PUYO_COLOR_ si les coordonees sont erronees
*/
int PuyoField::readField(int x, int y)
{
	if ( x < _FIELD_WIDTH_ && x > 0 && y < _FIELD_HEIGHT_ && y >= 0) return matrix[x][y]->color();
	else return _BORDER_PUYO_COLOR_;
}	


/*
	Detecte les groupes et les puyo explosions.
	Fait egalement chutter les puyo qui en ont besoin
	Retour : 1 si explosion effective
	         0 si pas d'explosion
*/
int PuyoField::puyoExplosion()
{
	unmarkAll();
	for (int i=0; i < _FIELD_WIDTH_ ; i++)for (int j=0; j<_FIELD_HEIGHT_ ; j++)
	{
		// Si la case selectionnee n'est pas marquee on commence le parcours
		if (!matrix[i][j]->isMarked() 
			&& matrix[i][j]->color()!=_BORDER_PUYO_COLOR_ 
			&& matrix[i][j]->color()!= 0)
		{
			// On cherche un groupe de Puyo contigus de la même couleur
			if (findGroup(i,j) > 3) 
			{
				updateScore();
				explodeAll();
				puyoInGroup=0;
				fallAll();
				return 1;
			} 
			// Sinon, on enleve la marque active des puyo de ce groupe
			for(int x=0; x<_FIELD_WIDTH_ ; x++) for(int y=0; y<_FIELD_HEIGHT_; y++)
			{ matrix[x][y]->unmarkActive(); }
			puyoInGroup=0;			
		}
	}
	unmarkAll();	
	return 0;
}


/*
	Enlève le marquage de tous les Puyo du PuyoField
*/
void PuyoField::unmarkAll()
{
	for (int y=0; y < _FIELD_HEIGHT_ ; y++) for (int x=0; x<_FIELD_WIDTH_ ; x++)
		{
			matrix[x][y]->unmark();
			matrix[x][y]->unmarkActive();
		}
		puyoInGroup=0;
}



/*
	Fait exploser tous les puyo du groupe actifs (cad avec le bit 9 a 1)
	Peut eventuellement declancer une petite animation
*/
void PuyoField::explodeAll()
{
	for (int i=0; i<_FIELD_WIDTH_; i++) for (int j=0; j<_FIELD_HEIGHT_; j++)
	{
		// ajouter un petit compteur pour les points
		if (matrix[i][j]->isActiveMarked()) setPuyo(i,j,0);
	}
}


/*
	Detection recursive de groupes de puyo contigus d'une meme couleur
	Renvoie le nombre de puyo du groupe
*/
int PuyoField::findGroup(int x, int y)
{
	int retour=1;

	// Si le puyo a deja ete visite, on va voir ailleurs	
	if (matrix[x][y]->isMarked() || matrix[x][y]->color() == _BORDER_PUYO_COLOR_ ) return 0;
	
	// On marque le puyo
	matrix[x][y]->mark();		// puyo visite
	matrix[x][y]->markActive();	// puyo du groupe en inspection
	puyoInGroup++;
	
	// On regarde les puyo alentours non marques
	if (matrix[x][y]->color() == matrix[x+1][y]->color()) retour += findGroup(x+1,y);	// a droite
	if (matrix[x][y]->color() == matrix[x][y-1]->color()) retour += findGroup(x,y-1);	// en haut
	if (matrix[x][y]->color() == matrix[x-1][y]->color()) retour += findGroup(x-1,y);	// a gauche
	if (matrix[x][y]->color() == matrix[x][y+1]->color()) retour += findGroup(x,y+1);	// en bas
	return retour;
}



/*
	Des qu'on trouve un trou, on le bouche avec le premier puyo venu puis on monte
*/
void PuyoField::fallAll()
{
	for (int x=1; x < _FIELD_WIDTH_ -1; x++) for (int y= _FIELD_HEIGHT_ -1; y>0; y--)
	{
		// si on trouve un trou
		if (matrix[x][y]->color()==0)
		{
			int i;

			// on remonte a la recherche du premier puyo
			for (i=y; i>0 && matrix[x][i]->color()==0; i--);
			
			// Si on a atteint le sommet on passe directement a la colonne suivante
			if (i==0) break;
		
			// Une fois qu'on l'a trouve on fait l'echange
			setPuyo(x, y, matrix[x][i]->color());
			setPuyo(x, i, 0);
		 }
	} 
}

int PuyoField::getScore(){return fieldScore;}

void PuyoField::updateScore() { fieldScore += (puyoInGroup-3); }
