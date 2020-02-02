#include "MainWindow.h"

#include "Model/ModelThread.h"

#include <QDebug>

namespace View
{
	MainWindow::MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ )
		: QMainWindow( pParent_ ), m_pModelThread( pModelThread_ )
	{
		ui.setupUi( this );

		if ( m_pModelThread != nullptr )
		{
			m_pModelThread->start();
		}
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
} // namespace View
