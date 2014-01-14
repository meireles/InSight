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

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

#include <vtkSphereSource.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkProperty.h>


// **************************************************************** //
//							Node Actor
// **************************************************************** //


NodeActor::NodeActor() {
	source = vtkSmartPointer<vtkSphereSource>::New();
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	actor  = vtkSmartPointer<vtkActor>::New();

	set_center(0,0,0);
	set_size(0.1);
	set_resolution(25,25);
	set_color(0.5,0.5,0.5);

	mapper->SetInputConnection(source->GetOutputPort());
	actor->SetMapper(mapper);
	actor->GetProperty()->SetBackfaceCulling(1);
}

void NodeActor::set_center(double x, double y, double z){
	source->SetCenter(x,y,z);
	source->Update();
	//mapper->Update();
}

void NodeActor::set_size(double size){
	source->SetRadius(size);
	source->Update();
	//mapper->Update();
}

void NodeActor::set_resolution(unsigned phi, unsigned theda){
	source->SetPhiResolution(phi);
	source->SetThetaResolution(theda);
	source->Update();
	//mapper->Update();
}

void NodeActor::set_color(double red, double green, double blue){
	actor -> GetProperty()->SetColor(red, green, blue);
	source->Update();
	//mapper->Update();
}


vtkActor* NodeActor::get(){
	return actor;
}


// **************************************************************** //
//							Edge Actor
// **************************************************************** //


EdgeActor::EdgeActor() {

	source			= vtkSmartPointer<vtkLineSource>::New();
	mapper			= vtkSmartPointer<vtkPolyDataMapper>::New();
	actor			= vtkSmartPointer<vtkActor>::New();

	cylinder_filter = vtkSmartPointer<vtkTubeFilter>::New();
	cylinder_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinder_actor  = vtkSmartPointer<vtkActor>::New();

	set_point1(0,0,0);
	set_point2(3,3,3);
	set_width(3);
	set_color(0.5,0.5,0.5);

	mapper -> SetInputConnection(source->GetOutputPort());
	actor  -> SetMapper(mapper);

	// cylinder //
	cylinder_filter -> SetInputConnection(source->GetOutputPort());
	cylinder_filter -> SetRadius(0.05);
	cylinder_filter -> SetCapping(1);
	cylinder_filter -> SetNumberOfSides(25);
	cylinder_filter -> Update();

	cylinder_mapper -> SetInputConnection(cylinder_filter->GetOutputPort());
	cylinder_actor  -> SetMapper(cylinder_mapper);

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
	actor  -> GetProperty() -> SetLineWidth(width);
	source -> Update();
}

void EdgeActor::set_color(double red, double green, double blue){
	actor -> GetProperty() -> SetColor(red, green, blue);
	source -> Update();
}


vtkActor* EdgeActor::get(){
	return actor;
}

vtkActor* EdgeActor::get_cylinder(){
	return cylinder_actor;
}
