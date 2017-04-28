/**********************************************************************
	Puyo.h
	BePuyo Version 0.1
	
	Classe decrivant les puyo qui sont utilises dans les PuyoCouples
	qui tombent de l'ecran et pour composer le PuyoField.
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

#ifndef _PUYO_H_
#define _PUYO_H_

#define MON_BOUTON_MSG 'puyo'
#define RESTART 'pure'

class Puyo {
public:
	// Cree un puyo de la couleur voulue
	Puyo(int coul=0) {
		col = coul;
		visited = activeGroup = false;
	}
	// Clone un puyo
	Puyo(Puyo &nouv) {
		col = nouv.col;
		visited = nouv.visited;
		activeGroup = nouv.activeGroup;
	}
	~Puyo()	{}
	// Change ou lit sa couleur
	void setColor(int coul) { col = coul; }
	int color() const { return col; }
	// Méthodes de marquage des Puyo
	void mark() { visited = true; }
	void unmark() { visited = false; }
	bool isMarked() { return visited; }
	void markActive() { activeGroup = true; }
	void unmarkActive() { activeGroup = false; }
	bool isActiveMarked() { return activeGroup; }

private:
	// sa couleur
	int col;	
	// attributs de marquages pour la detection des explosions
	bool visited;
	bool activeGroup;
};

#endif
