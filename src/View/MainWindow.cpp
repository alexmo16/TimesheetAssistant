#include "MainWindow.h"

#include "Model/Events/Event.h"
#include "Model/ModelThread.h"
#include "Model/Timesheet/Timesheet.h"
#include "Model/Timesheet/WorkDay.h"

#include <QAction>
#include <QDate>
#include <QDebug>
#include <QTimer>

namespace View
{
	MainWindow::MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ )
		: QMainWindow( pParent_ ), m_pModelThread( pModelThread_ ), m_helpDialog( this ), m_aboutDialog( this ),
		  m_currentDayTotalTime( QTime( 0, 0 ) ), m_totalWorkTime( QTime( 0, 0 ) )
	{
		m_ui.setupUi( this );

		setCurrentWeekLabel();
		m_workDays = { m_ui.mondayTime, m_ui.tuesdayTime, m_ui.wednesdayTime, m_ui.thursdayTime, m_ui.fridayTime };
		m_workDaysStrings = { m_ui.mondayTime->text(), m_ui.tuesdayTime->text(), m_ui.wednesdayTime->text(),
			m_ui.thursdayTime->text(), m_ui.fridayTime->text() };

		connect( m_ui.actionHelp, &QAction::triggered, [ this ]( const bool /*checked_*/ ) { onHelpAction(); } );
		connect( m_ui.actionAbout, &QAction::triggered, [ this ]( const bool /*checked_*/ ) { onAboutAction(); } );
		connect( m_pModelThread.get(), &Model::ModelThread::timesheetUpdated,
			[ this ]( const QSharedPointer<Model::Timesheet>& timesheet_ ) { onTimesheetUpdated( *timesheet_ ); } );
		connect( m_ui.actionRefresh, &QAction::triggered, [ this ]( const bool /*checked_*/ ) { onRefreshClicked(); } );

		if ( m_pModelThread != nullptr )
		{
			m_pModelThread->start();
		}
	}

	void MainWindow::paintEvent( QPaintEvent* /*pEvent_*/ )
	{
		int index = -1;
		for ( auto* pWorkDayLineEdit : m_workDays )
		{
			++index;
			if ( pWorkDayLineEdit == nullptr )
			{
				continue;
			}

			pWorkDayLineEdit->setText( m_workDaysStrings.at( index ) );
		}
		m_ui.totalTime->setText( m_totalWorkTime.toString( "H'h'mm" ) );
	}

	void MainWindow::onRefreshClicked()
	{
		if ( m_workDays.empty() )
		{
			return;
		}

		const size_t index = static_cast<size_t>( QDate::currentDate().dayOfWeek() ) - 1;
		if ( index < 0 || index >= m_workDays.size() )
		{
			return;
		}

		m_currentDayTotalTime = m_currentDayTotalTime.addMSecs( m_currentDayTimer.elapsed() );
		m_currentDayTimer.restart();
		m_workDaysStrings[ index ] = m_currentDayTotalTime.toString( "H'h'mm" );

		calculateTotalTime();

		update();
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
	void MainWindow::onHelpAction()
	{
		m_helpDialog.open();
	}

	void MainWindow::onAboutAction()
	{
		m_aboutDialog.open();
	}

	void MainWindow::setCurrentWeekLabel()
	{
		const QDate& currentDate = QDate::currentDate();
		const int currentWeekDay = currentDate.dayOfWeek();
		m_mondayDate = currentDate.addDays( static_cast<qint64>( -currentWeekDay ) + 1 ); // remove days to get monday
		m_fridayDate = m_mondayDate.addDays( 4 );										  // 1 + 4 = 5 = friday

		if ( m_ui.weekLabel != nullptr )
		{
			const QString dateFormat = "MMMM d yyyy"; // example: February 24 2020
			const QString newWeekLabel =
				m_mondayDate.toString( dateFormat ) + " - " + m_fridayDate.toString( dateFormat ) + ":";
			m_ui.weekLabel->setText( newWeekLabel );
		}
	}

	void MainWindow::onTimesheetUpdated( const Model::Timesheet& timesheet_ )
	{
		if ( m_workDays.empty() )
		{
			return;
		}

		const Model::TWorkDays& workDays = timesheet_.getWorkDays();
		for ( const auto& pWorkDay : workDays )
		{
			if ( pWorkDay == nullptr )
			{
				continue;
			}
			const QDate& date = pWorkDay->getDate();
			if ( date < m_mondayDate )
			{
				continue;
			}
			const QString& timeStr = pWorkDay->getWorkTime().toString( "H'h'mm" );
			m_workDaysStrings[ date.dayOfWeek() - 1 ] = timeStr;

			if ( date == QDate::currentDate() )
			{
				m_currentDayTotalTime = QTime::fromString( timeStr, "H'h'mm" );
				m_currentDayTimer.start();
			}
		}
		calculateTotalTime();
		update();
	}

	void MainWindow::calculateTotalTime()
	{
		QTime totalTime( 0, 0 );
		for ( auto& workdayString : m_workDaysStrings )
		{
			totalTime.addMSecs( QTime::fromString( workdayString, "H'h'mm" ).msecsSinceStartOfDay() );
		}
		m_totalWorkTime = totalTime;
	}
} // namespace View
