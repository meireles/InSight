/**
* @file			orientationmarker.h
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

#ifndef ORIENTATIONMARKER_H
#define ORIENTATIONMARKER_H


#include <vtkSmartPointer.h>

class vtkOrientationMarkerWidget;
class vtkRenderWindowInteractor;
class vtkAxesActor;


class OrientationMarker {
	public:
		OrientationMarker();

		void set_interactor(vtkRenderWindowInteractor* interactor);
		void set_enabeled(bool arg);

	private:
		vtkSmartPointer<vtkOrientationMarkerWidget>	orientation_marker_m;
		vtkSmartPointer<vtkAxesActor>				axes_actor_m;
};


#endif // ORIENTATIONMARKER_H
