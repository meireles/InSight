/**
* @file			nodedata.cpp
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

#include "nodedata.h"



// test
#include <iostream>

NodeData::NodeData() :	leaf_spacing_y_coord(0.0),
						node_radius(0.5),
						node_height_x_coord(0.0),
						edge_thickness(0.1) {

	node_actor = vtkSmartPointer<NodeActor>::New();
	edge_actor = vtkSmartPointer<EdgeActor>::New();

	// ******  TEST ***** //
	std::cout << "Node Data's address " << this << "\n" << std::endl;
	std::cout << "Node's actor smart pointer address " << this-> node_actor << std::endl;
	std::cout << "Node's actor ptr address " << this-> node_actor.Get() << std::endl;
	std::cout << "Node's actor address " << this-> node_actor.GetPointer() << "\n" << std::endl;

	std::cout << "Edge's actor smart pointer address " << this-> edge_actor << std::endl;
	std::cout << "Edge's actor ptr address " << this-> edge_actor.Get() << std::endl;
	std::cout << "Edge's actor address " << this-> edge_actor.GetPointer() << "\n\n" << std::endl;

	// ****************** //

}




