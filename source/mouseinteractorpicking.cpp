/**
* @file			mouseinteractorpicking.cpp
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

#include "mouseinteractorpicking.h"


#include <vtkSmartPointer.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindowInteractor.h>


vtkStandardNewMacro(MouseInteractorPicking)


void MouseInteractorPicking::OnLeftButtonDown() {

	// Get Position of the left button click
	int* click_position = this->GetInteractor()->GetEventPosition();

	vtkSmartPointer<vtkPropPicker>  picker = vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick( click_position[0], click_position[1], 0, this->GetDefaultRenderer() );


	std::cout << "Click position (renderer coordinates)? is: "
			  << click_position[0] << " " << click_position[1] << std::endl;

	double* position = picker->GetPickPosition();
	std::cout << "Actor pick position (world coordinates) is: "
			  << position[0] << " " << position[1] << " " << position[2] << std::endl;

	std::cout << "Picked actor: " << picker->GetActor() << std::endl;

	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}


void MouseInteractorPicking::OnRightButtonDown() {

	// Get Position of the left button click
	int* click_position = this->GetInteractor()->GetEventPosition();

	vtkSmartPointer<vtkPropPicker>  picker = vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick( click_position[0], click_position[1], 0, this->GetDefaultRenderer() );


	std::cout << "RIGHT Click position (renderer coordinates)? is: "
			  << click_position[0] << " " << click_position[1] << std::endl;

	double* position = picker->GetPickPosition();
	std::cout << "RIGHT Actor pick position (world coordinates) is: "
			  << position[0] << " " << position[1] << " " << position[2] << std::endl;

	std::cout << " RIGHT Picked actor: " << picker->GetActor() << std::endl;


	// ************************ //



	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}
