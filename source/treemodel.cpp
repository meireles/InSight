/**
* @file			treemodel.cpp
*
* @package		%DOXYGEN_PACKAGE%
* @brief		%DOXYGEN_BRIEF%
*
* @author		Meireles
* @date			1/5/2014
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

#include "treemodel.h"


void TreeModel::fill_leaf_spacing(){
	double last_leaf_y = 0.0;
	double increase_by = 1.0;

	for( auto& i : iter_postorder(root()) ) {
		if(i -> is_leaf() ) {
			i -> data -> leaf_spacing_y_coord = last_leaf_y;
			last_leaf_y += increase_by;
		}
		else {
			// Take the average of the children coords
			double sum_kids = 0.0;
			for(auto& j : i -> children() ){
				sum_kids += j -> data -> leaf_spacing_y_coord;
			}
			double avg_kids = sum_kids / ( i -> children().size() );
			i -> data -> leaf_spacing_y_coord = avg_kids;
		}
	}
}



void TreeModel::fill_node_hights(bool set_unit_brlens) {

	double start_root_at = 0.0;

	for(auto& i : iter_preorder(root()) ){

		if(set_unit_brlens) {
			if( i == root() ) {
				i -> data -> node_height_x_coord = start_root_at;
			} else {
				i -> data -> node_height_x_coord = i -> parent() -> data -> node_height_x_coord + 1.0;
			}
		} else {
			if( i == root() ) {
				i -> data -> node_height_x_coord = start_root_at + i -> edge.length();
			} else {
				i -> data -> node_height_x_coord = (i -> parent() -> data -> node_height_x_coord ) + (i -> edge.length() );
			}

		}
	}
}

