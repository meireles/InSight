#ifndef mainwindow_H
#define mainwindow_H

#include "treemodel.h"
#include "ui_mainwindow.h"

#include <QMainWindow>

#include <vtkSmartPointer.h>


#include "nodeeditor.h"


// Forward Declaration
class vtkEventQtSlotConnect;
class vtkOrientationMarkerWidget;


class MainWindow : public QMainWindow, private Ui::MainWindow {
	Q_OBJECT
	public:
		MainWindow();
	public slots:
		void slot_clicked(vtkObject*, unsigned long, void*, void*);
	private slots:
		void on_actionImport_Tree_triggered();		
		void on_actionSet_Background_Color_triggered();
		void on_actionView_All_Actors_triggered();

		void on_actionShow_Orientation_Axes_toggled(bool arg1);

		void on_actionSet_X_triggered();

		void on_actionSet_Y_triggered();

		void on_actionSet_Z_triggered();

	private:
		TreeModel									mytree;


		NodeEditor									node_editor;


		vtkSmartPointer<vtkRenderer>				renderer;
		vtkSmartPointer<vtkEventQtSlotConnect>		connections;
		vtkSmartPointer<vtkOrientationMarkerWidget>	orientation_marker;

		void update_rendering_window();
		void reset_camera();
		void set_renderer_color(double r, double g, double b);

		void open_tree_file();
		void load_tree(std::string statement);
		void add_node_actors_to_renderer();
};

#endif
