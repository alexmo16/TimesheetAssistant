#include "MainWindow.h"

#include "Model/ModelThread.h"

#include <QAction>
#include <QDebug>

namespace View
{
	MainWindow::MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ )
		: QMainWindow( pParent_ ), m_pModelThread( pModelThread_ ), m_helpDialog( this )
	{
		m_ui.setupUi( this );

		if ( m_pModelThread != nullptr )
		{
			m_pModelThread->start();
		}

		connect( m_ui.actionHelp, &QAction::triggered, [ this ]( const bool checked_ ) { OnHelpAction( checked_ ); } );
	}

	/**
	 * @brief Callback when the close button is clicked. Ensure all threads are stopped.
	 */
	void MainWindow::closeEvent( QCloseEvent* /*pEvent_*/ )
	{
		qInfo() << "closing application...";
		m_pModelThread->stop();
		m_pModelThread->wait();
	}

	/*
	 * @brief Callback when the menu action button is clicked to open help dialog.
	 */
	void MainWindow::OnHelpAction( const bool /*checked_*/ )
	{
		m_helpDialog.open();
	}
} // namespace View
