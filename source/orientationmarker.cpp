/**
* @file			orientationmarker.cpp
*
* @package		%DOXYGEN_PACKAGE%
* @brief		%DOXYGEN_BRIEF%
*
* @author		Meireles
* @date			1/14/2014
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

#include "orientationmarker.h"


#include <vtkRenderWindowInteractor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>

#include <vtkProperty.h>
#include <vtkRenderWindow.h>


OrientationMarker::OrientationMarker() {
	orientation_marker_m = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	axes_actor_m = vtkSmartPointer<vtkAxesActor>::New();
	axes_actor_m -> SetShaftTypeToCylinder();
}


void OrientationMarker::set_interactor(vtkRenderWindowInteractor* interactor){
	this -> orientation_marker_m -> SetInteractor(interactor);

	orientation_marker_m -> SetOrientationMarker(axes_actor_m);
	orientation_marker_m -> SetViewport(0.0,0.0,0.25,0.25);

	// Must enable marker before disabeling interaction (weird, no?)
	// Last line disables the marker though;
	orientation_marker_m -> EnabledOn();
	orientation_marker_m -> KeyPressActivationOff();
	orientation_marker_m -> InteractiveOff();
	orientation_marker_m -> EnabledOff();
}

void OrientationMarker::set_enabeled(bool arg){
	this->orientation_marker_m->SetEnabled(arg);
}

