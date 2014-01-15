/**
* @file			actor.cpp
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


#include "actor.h"

#include <vtkObjectFactory.h>

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

#include <vtkSphereSource.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkProperty.h>


// **************************************************************** //
//							Node Actor
// **************************************************************** //

vtkStandardNewMacro(NodeActor)

// ---------------------------------------------------------------- //
//                  Overload members from vtkActor
// ---------------------------------------------------------------- //


void NodeActor::ReleaseGraphicsResources(vtkWindow* window) {
	this -> device_m -> ReleaseGraphicsResources(window);
	this -> Superclass::ReleaseGraphicsResources(window);
}


int NodeActor::RenderOpaqueGeometry(vtkViewport* viewport){
	if ( ! this -> Mapper ) {
		return 0;
	}
	if (!this -> Property) {
		this -> GetProperty();
	}
	if ( this -> GetIsOpaque() ) {
		vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
		this -> Render(ren);
		return 1;
	}
	return 0;
}


int NodeActor::RenderTranslucentPolygonalGeometry(vtkViewport* viewport) {
	if ( ! this -> Mapper ) {
		return 0;
	}
	if (! this -> Property) {
		this -> GetProperty();
	}
	if (! this -> GetIsOpaque()) {
		vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
		this -> Render(ren);
		return 1;
	}
	return 0;
}


void NodeActor::Render(vtkRenderer* ren) {
	this -> Property -> Render(this, ren);
	this -> device_m -> SetProperty (this->Property);
	this -> Property->Render(this, ren);
	if (this -> BackfaceProperty) {
		this -> BackfaceProperty -> BackfaceRender(this, ren);
		this -> device_m -> SetBackfaceProperty(this -> BackfaceProperty);
	}
	if (this -> Texture) {
		this -> Texture->Render(ren);
	}
	this -> ComputeMatrix();
	this -> device_m -> SetUserMatrix(this -> Matrix);
	this -> device_m -> Render(ren,this -> Mapper);
}


void NodeActor::ShallowCopy(vtkProp* prop) {
	NodeActor* f = NodeActor::SafeDownCast(prop);
	this -> vtkActor::ShallowCopy(prop);
}


NodeActor::NodeActor() {
	this -> device_m = vtkActor::New();

	source_m = vtkSmartPointer<vtkSphereSource>::New();
	mapper_m = vtkSmartPointer<vtkPolyDataMapper>::New();

	set_center(0,0,0);
	set_size(0.075);
	set_resolution(25,25);
	set_color(0.5,0.5,0.5);

	mapper_m->SetInputConnection(source_m->GetOutputPort());

	this -> SetMapper(mapper_m);
	this -> GetProperty() -> SetBackfaceCulling(1);
}


NodeActor::~NodeActor() {
	this -> device_m -> Delete();
}


void NodeActor::set_center(double x, double y, double z){
	source_m->SetCenter(x,y,z);
	source_m->Update();
}

void NodeActor::set_size(double size){
	source_m->SetRadius(size);
	source_m->Update();
}

void NodeActor::set_resolution(unsigned phi, unsigned theda){
	source_m->SetPhiResolution(phi);
	source_m->SetThetaResolution(theda);
	source_m->Update();
}

void NodeActor::set_color(double red, double green, double blue){
	this -> GetProperty()->SetColor(red, green, blue);
	source_m->Update();
}



// **************************************************************** //
//							Edge Actor
// **************************************************************** //

vtkStandardNewMacro(EdgeActor)

// ---------------------------------------------------------------- //
//                  Overload members from vtkActor
// ---------------------------------------------------------------- //


void EdgeActor::ReleaseGraphicsResources(vtkWindow* window) {
	this -> device_line_m		-> ReleaseGraphicsResources(window);
	this -> device_cylinder_m	-> ReleaseGraphicsResources(window);

	this -> Superclass::ReleaseGraphicsResources(window);
}


int EdgeActor::RenderOpaqueGeometry(vtkViewport* viewport){
	if ( ! this -> Mapper ) {
		return 0;
	}
	if (!this -> Property) {
		this -> GetProperty();
	}
	if ( this -> GetIsOpaque() ) {
		vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
		this -> Render(ren);
		return 1;
	}
	return 0;
}


int EdgeActor::RenderTranslucentPolygonalGeometry(vtkViewport* viewport) {
	if ( ! this -> Mapper ) {
		return 0;
	}
	if (! this -> Property) {
		this -> GetProperty();
	}
	if (! this -> GetIsOpaque()) {
		vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
		this -> Render(ren);
		return 1;
	}
	return 0;
}


void EdgeActor::Render(vtkRenderer* ren) {
	this -> Property -> Render(this, ren);

	this -> device_line_m		-> SetProperty (this->Property);
	this -> device_cylinder_m	-> SetProperty (this->Property);

	this -> Property->Render(this, ren);
	if (this -> BackfaceProperty) {
		this -> BackfaceProperty -> BackfaceRender(this, ren);

		this -> device_line_m		-> SetBackfaceProperty(this -> BackfaceProperty);
		this -> device_cylinder_m	-> SetBackfaceProperty(this -> BackfaceProperty);
	}
	if (this -> Texture) {
		this -> Texture -> Render(ren);
	}
	this -> ComputeMatrix();

	this -> device_line_m		-> SetUserMatrix(this -> Matrix);
	this -> device_cylinder_m	-> SetUserMatrix(this -> Matrix);

	this -> device_line_m		-> Render(ren, this -> Mapper);
	this -> device_cylinder_m	-> Render(ren, this -> Mapper);
}


void EdgeActor::ShallowCopy(vtkProp* prop) {
	EdgeActor* f = EdgeActor::SafeDownCast(prop);
	this -> vtkActor::ShallowCopy(prop);
}


EdgeActor::EdgeActor() {

	this -> device_line_m		= vtkActor::New();
	this -> device_cylinder_m	= vtkActor::New();

	source			= vtkSmartPointer<vtkLineSource>::New();
	cylinder_filter = vtkSmartPointer<vtkTubeFilter>::New();


	mapper			= vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinder_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();


	set_point1(0, 0, 0);
	set_point2(1, 1, 1);

	// Set the same thing for cylinder radius?
	set_width(0.05);
	set_color(0.7, 0.7, 0.7);

	// line //
	mapper	-> SetInputConnection(source -> GetOutputPort());
	this	-> SetMapper(mapper);

	// cylinder //
	cylinder_filter -> SetInputConnection(source -> GetOutputPort());
	cylinder_filter -> SetRadius(0.05);
	cylinder_filter -> SetCapping(1);
	cylinder_filter -> SetNumberOfSides(25);
	cylinder_filter -> Update();

	cylinder_mapper -> SetInputConnection(cylinder_filter->GetOutputPort());
	this  -> SetMapper(cylinder_mapper);

}


EdgeActor::~EdgeActor(){
	this -> device_line_m -> Delete();
	this -> device_cylinder_m -> Delete();

}


void EdgeActor::set_point1(double x, double y, double z){
	source -> SetPoint1(x,y,z);
	source -> Update();
}


void EdgeActor::set_point2(double x, double y, double z){
	source -> SetPoint2(x,y,z);
	source -> Update();
}


void EdgeActor::set_width(double width){
	this  -> GetProperty()		-> SetLineWidth(width);
	this  -> cylinder_filter	-> SetRadius(width);

	source			-> Update();
	cylinder_filter	-> Update();
}


void EdgeActor::set_color(double red, double green, double blue){
	this	-> GetProperty() -> SetColor(red, green, blue);
	source	-> Update();
}

