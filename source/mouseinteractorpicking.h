/**
* @file			mouseinteractorpicking.h
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

#ifndef MOUSEINTERACTORPICKING_H
#define MOUSEINTERACTORPICKING_H


#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>


class MouseInteractorPicking : public vtkInteractorStyleTrackballCamera {
	public:
		static MouseInteractorPicking* New();
		vtkTypeMacro(MouseInteractorPicking, vtkInteractorStyleTrackballCamera);

		virtual void OnLeftButtonDown();
		virtual void OnRightButtonDown();
};


#endif // MOUSEINTERACTORPICKING_H
