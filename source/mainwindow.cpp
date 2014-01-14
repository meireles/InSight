#include "mainwindow.h"
#include "treemodel.h"
#include "newick.h"
#include "mouseinteractorpicking.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

#include <QAction>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>

#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>

#include <iostream>


#include "nodeeditor.h"

// **************************************************************** //
//							Constructor
// **************************************************************** //

MainWindow::MainWindow() {

	// Setup the MOC generated header from the designer .ui file
	setupUi(this);

	// Not working in Qt5.2
	setUnifiedTitleAndToolBarOnMac(true);

	// If I want to change the toolbar backgound color, I also have to change the border, otherwise Qt doesn't repaint it
	// toolBar -> setStyleSheet("QToolBar {background: #AEAEAE; border: 2px #AEAEAE}");





	connections	= vtkSmartPointer<vtkEventQtSlotConnect>::New();
	renderer	= vtkSmartPointer<vtkRenderer>::New();
	qvtkWidget -> GetRenderWindow()->AddRenderer(renderer);

	orientation_marker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

	// Instantiate my custom interactor
	vtkSmartPointer<MouseInteractorPicking> iter_style = vtkSmartPointer<MouseInteractorPicking>::New();


	iter_style -> SetDefaultRenderer(renderer);
	qvtkWidget->GetRenderWindow()->GetInteractor()->SetInteractorStyle(iter_style);


	// Setup the orientation marker widget with axes
	vtkSmartPointer<vtkAxesActor> axes_actor = vtkSmartPointer<vtkAxesActor>::New();
	axes_actor -> SetShaftTypeToCylinder();

	orientation_marker -> SetOrientationMarker(axes_actor);
	orientation_marker -> SetViewport(0.0,0.0,0.2,0.2);
	orientation_marker -> SetInteractor(qvtkWidget->GetRenderWindow()->GetInteractor());

	// Must enable marker before disabeling interaction (weird, no?)
	// Last line disables the marker though;
	orientation_marker -> EnabledOn();
	orientation_marker -> KeyPressActivationOff();
	orientation_marker -> InteractiveOff();
	orientation_marker -> EnabledOff();


	// Vtk / Qt communication
	connections->Connect(this->qvtkWidget->GetRenderWindow()->GetInteractor(),
							   vtkCommand::LeftButtonPressEvent,
							   this,
							   SLOT(slot_clicked(vtkObject*, unsigned long, void*, void*)) );
}




// **************************************************************** //
//							Slots
// **************************************************************** //


void MainWindow::slot_clicked(vtkObject*, unsigned long, void*, void*) {
	std::cout << "Left Button Clicked." << std::endl;
}


void MainWindow::on_actionImport_Tree_triggered() {
	open_tree_file();
}



// **************************************************************** //
//						Private Functions
// **************************************************************** //

void MainWindow::reset_camera(){
	renderer->ResetCamera();
	update_rendering_window();
}

void MainWindow::set_renderer_color(double r, double g, double b){
	renderer->SetBackground(r,g,b);
}

void MainWindow::update_rendering_window(){
	qvtkWidget->update();
}


void MainWindow::load_tree(std::string statement) {
	Newick n(statement);

	// If Newick statement is empty
	// it means that the tree format was off
	if(n.get() == "") {
		QMessageBox::critical(this, tr("Error"), tr("Bad newick format"));
		return;
	}

	else {
		mytree.read_newcik( n.get() );

		/*	A lot of stuff to do here:
		 *
		 *	- read in data from hot comments?
		 *	- compute default node coords			** needs transversal **
		 *	- add default coord to node actors		** needs transversal **
		 *  - add actors to scene					** needs transversal **
		 */

		mytree.fill_leaf_spacing();
		mytree.fill_node_hights(true);	// NOT USING BRLENS

		add_node_actors_to_renderer();

		renderer  ->ResetCamera();
		qvtkWidget->update();


		// TEST //
		for(auto& i : mytree.iter_postorder(mytree.root())){
			std::cout << i -> taxon << " has brlens " << i -> edge.length()
					  << " and X and Y coords = "
					  << i -> data -> node_height_x_coord << " "
					  << i -> data -> leaf_spacing_y_coord
					  << std::endl;
		}
	}
}



void MainWindow::open_tree_file(){
	QString file_path = QFileDialog::getOpenFileName(
							this,
							tr("Open File"),
							QString(),
							tr("Newick Files (*.tre);;Any File (*)") );

	if ( !file_path.isEmpty() ) {
		QFile file(file_path);

		if ( !file.open(QIODevice::ReadOnly) ) {
			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
			return;
		}

		QTextStream in(&file);
		std::string fp( in.readAll().toStdString() );

		load_tree(fp);

		file.close();
	}
}



void MainWindow::add_node_actors_to_renderer(){
	for(auto& i : mytree.iter_postorder(mytree.root())){
		i -> data -> node_actor.set_center( i-> data -> node_height_x_coord,
											i-> data -> leaf_spacing_y_coord,
											0.0);
		renderer -> AddActor(i -> data -> node_actor.get());
	}

	for(auto& i : mytree.iter_postorder(mytree.root()) ){
		if(i == mytree.root()) {
			// Do nothing since the root has no Edge associated with it
			// And trying to access it will make the app crash
		}
		else {
			i -> data -> edge_actor.set_point1(i-> data -> node_height_x_coord,
											   i-> data -> leaf_spacing_y_coord,
											   0.0
											   );

			i -> data -> edge_actor.set_point2(i-> parent() -> data -> node_height_x_coord,
											   i-> parent() -> data -> leaf_spacing_y_coord,
											   0.0
											   );

			//renderer -> AddActor(i -> data -> edge_actor.get());
			renderer -> AddActor(i -> data -> edge_actor.get_cylinder());
		}
	}
}


void MainWindow::on_actionSet_Background_Color_triggered() {
	QColor color = QColorDialog::getColor(Qt::black, this, "Select a background color");
	if(color.isValid()){
		set_renderer_color(color.redF(), color.greenF(), color.blueF());
		update_rendering_window();
	}
}


void MainWindow::on_actionView_All_Actors_triggered(){
	reset_camera();
}

void MainWindow::on_actionShow_Orientation_Axes_toggled(bool enable) {
	orientation_marker ->SetEnabled(enable);
	update_rendering_window();
}

void MainWindow::on_actionSet_X_triggered() {
	node_editor.show();
}

void MainWindow::on_actionSet_Y_triggered()
{

}

void MainWindow::on_actionSet_Z_triggered()
{

}
