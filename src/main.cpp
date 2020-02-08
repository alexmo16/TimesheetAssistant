#include "Model/ModelThread.h"
#include "View/MainWindow.h"

#include <QtWidgets/QApplication>
#pragma comment( lib, "wevtapi.lib" )

int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );

	std::shared_ptr<Model::ModelThread> modelThread = std::make_shared<Model::ModelThread>();

	View::MainWindow w( modelThread );
	w.show();
	return a.exec();
}
