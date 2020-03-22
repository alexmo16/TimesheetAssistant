#include "Model/ModelThread.h"
#include "View/MainWindow.h"

#include <QResource>
#include <QSettings>
#include <QSharedPointer>
#include <QString>
#include <QtWidgets/QApplication>
#pragma comment( lib, "wevtapi.lib" )

int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );
	a.setOrganizationName( "TimesheetAssistant" );
	a.setOrganizationDomain( "Timesheets Software" );
	a.setApplicationName( "TimesheetAssistant" );

	const QString settingsFile = QApplication::applicationDirPath() + "/settings.conf";
	QSharedPointer<QSettings> pSettings =
		QSharedPointer<QSettings>( new QSettings( settingsFile, QSettings::IniFormat ) );
	if ( pSettings == nullptr )
	{
		return -1;
	}

	std::shared_ptr<Model::ModelThread> modelThread = std::make_shared<Model::ModelThread>();

	View::MainWindow w( modelThread, pSettings );
	w.show();
	return a.exec();
}
