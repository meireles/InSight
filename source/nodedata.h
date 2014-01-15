/**
* @file			nodedata.h
*
* @package		%DOXYGEN_PACKAGE%
* @brief		%DOXYGEN_BRIEF%
*
* @author		Meireles
* @date			1/6/2014
*
* @copyright	Copyright (C) 2014  Meireles
*
* 	This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef NODEDATA_H
#define NODEDATA_H

#include "actor.h"


/*
 *	This is how the screen is modelled:
 *
 *  Y ~ spacing				(∞/∞)
 *
 *               ______ sp1
 *       _______|
 *      |       |______ sp2
 *      |
 *      |______________ sp3
 *
 * (0/0)         X ~ brlens
 */

class NodeData {
	public:
		NodeData();

		vtkSmartPointer<NodeActor>	node_actor;
		vtkSmartPointer<EdgeActor>	edge_actor;

		double		leaf_spacing_y_coord;
		double		node_radius;

		double		node_height_x_coord;	// sum edges from root -> node
		double		edge_thickness;

	private:

};


#endif // NODEDATA_H
