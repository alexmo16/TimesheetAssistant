#include "Model/Config/Config.h"
#include "Model/ModelThread.h"
#include "View/MainWindow.h"

#include <QFileInfo>
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
	std::unique_ptr<QSettings> pSettings = std::make_unique<QSettings>( settingsFile, QSettings::IniFormat );
	if ( pSettings == nullptr )
	{
		return -1;
	}
	QSharedPointer<Model::Config> pConfig =
		QSharedPointer<Model::Config>( new Model::Config( std::move( pSettings ) ) );
	if ( pConfig == nullptr )
	{
		return -1;
	}
	if ( !QFileInfo::exists( settingsFile ) )
	{
		Model::loadDefault( *pConfig );
	}

	std::unique_ptr<Model::ModelThread> modelThread = std::make_unique<Model::ModelThread>( pConfig );

	View::MainWindow* pWindow = new View::MainWindow( std::move( modelThread ), pConfig );
	pConfig->setParent( pWindow );

	pWindow->show();
	return a.exec();
}
