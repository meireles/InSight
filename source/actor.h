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

#include <vtkActor.h>
#include <vtkSmartPointer.h>


class vtkPolyDataMapper;
class vtkRenderer;
class vtkSphereSource;
class vtkLineSource;
class vtkTubeFilter;


class VTKRENDERINGCORE_EXPORT  NodeActor :  public vtkActor {
	public:
		// *************************************** //
		//		Overload members from vtkActor
		// *************************************** //
		vtkTypeMacro(NodeActor, vtkActor);

		static NodeActor* New();
		virtual void ReleaseGraphicsResources(vtkWindow* window);
		virtual int RenderOpaqueGeometry(vtkViewport* viewport);
		virtual int RenderTranslucentPolygonalGeometry(vtkViewport* viewport);
		virtual void Render(vtkRenderer* ren);
		void ShallowCopy(vtkProp* prop);

		// *************************************** //
		//				Wrappers
		// *************************************** //
		void set_center(double x, double y, double z);
		void set_size(double size);
		void set_resolution(unsigned phi, unsigned theda);
		void set_color(double red, double green, double blue);


	protected:
		NodeActor();
		~NodeActor();

	private:
		vtkActor*							device_m;

		vtkSmartPointer<vtkSphereSource>	source_m;
		vtkSmartPointer<vtkPolyDataMapper>	mapper_m;
};




class VTKRENDERINGCORE_EXPORT EdgeActor : public vtkActor {
	public:
		// *************************************** //
		//		Overload members from vtkActor
		// *************************************** //
		vtkTypeMacro(EdgeActor, vtkActor);

		static EdgeActor* New();
		virtual void ReleaseGraphicsResources(vtkWindow* window);
		virtual int RenderOpaqueGeometry(vtkViewport* viewport);
		virtual int RenderTranslucentPolygonalGeometry(vtkViewport* viewport);
		virtual void Render(vtkRenderer* ren);
		void ShallowCopy(vtkProp* prop);

		// *************************************** //
		//				Wrappers
		// *************************************** //
		void set_point1(double x, double y, double z);
		void set_point2(double x, double y, double z);

		/// sets line width or cylinder diameter!
		void set_width(double width);
		void set_color(double red, double green, double blue);


	protected:
		EdgeActor();
		~EdgeActor();

	private:
		vtkActor*							device_line_m;
		vtkActor*							device_cylinder_m;

		vtkSmartPointer<vtkLineSource>		source;
		vtkSmartPointer<vtkPolyDataMapper>	mapper;

		vtkSmartPointer<vtkTubeFilter>		cylinder_filter;
		vtkSmartPointer<vtkPolyDataMapper>	cylinder_mapper;
};


#endif // ACTOR_H
