/**
* @file			actor.h
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

#ifndef ACTOR_H
#define ACTOR_H

#include "vtkRenderingCoreModule.h" // For export macro

#include <vtkSmartPointer.h>


class vtkActor;
class vtkPolyDataMapper;
class vtkSphereSource;
class vtkLineSource;
class vtkTubeFilter;


class NodeActor {
	public:
		NodeActor();

		void set_center(double x, double y, double z);
		void set_size(double size);
		void set_resolution(unsigned phi, unsigned theda);
		void set_color(double red, double green, double blue);

		/// gets the underlying vtkActor
		vtkActor* get();

	private:
		vtkSmartPointer<vtkSphereSource>	source;
		vtkSmartPointer<vtkPolyDataMapper>	mapper;
		vtkSmartPointer<vtkActor>			actor;
};



class EdgeActor {
	public:
		EdgeActor();

		void set_point1(double x, double y, double z);
		void set_point2(double x, double y, double z);
		void set_width(double width);
		void set_color(double red, double green, double blue);

		/// gets the underlying vtkActor
		vtkActor* get();
		vtkActor* get_cylinder();

	private:
		vtkSmartPointer<vtkLineSource>		source;
		vtkSmartPointer<vtkPolyDataMapper>	mapper;
		vtkSmartPointer<vtkActor>			actor;

		vtkSmartPointer<vtkTubeFilter>		cylinder_filter;
		vtkSmartPointer<vtkPolyDataMapper>	cylinder_mapper;
		vtkSmartPointer<vtkActor>			cylinder_actor;

};


#endif // ACTOR_H
