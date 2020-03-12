#include "MainWindow.h"

#include "Model/Events/Event.h"
#include "Model/ModelThread.h"
#include "Model/Timesheet/Timesheet.h"
#include "Model/Timesheet/WorkDay.h"

#include <QAction>
#include <QDate>
#include <QDebug>
#include <QTimer>

constexpr auto ONE_MINUTE_MS = 60 * 1000;

namespace View
{
	MainWindow::MainWindow( std::shared_ptr<Model::ModelThread> pModelThread_, QWidget* pParent_ )
		: QMainWindow( pParent_ ), m_pModelThread( pModelThread_ ), m_helpDialog( this ),
		  m_currentDayTotalTime( QTime( 0, 0 ) )
	{
		m_ui.setupUi( this );

		SetCurrentWeekLabel();
		m_workDays = { m_ui.mondayTime, m_ui.tuesdayTime, m_ui.wednesdayTime, m_ui.thursdayTime, m_ui.fridayTime };
		m_workDaysStrings = { m_ui.mondayTime->text(), m_ui.tuesdayTime->text(), m_ui.wednesdayTime->text(),
			m_ui.thursdayTime->text(), m_ui.fridayTime->text() };

		connect( m_ui.actionHelp, &QAction::triggered, [ this ]( const bool checked_ ) { OnHelpAction( checked_ ); } );
		connect( m_pModelThread.get(), &Model::ModelThread::TimesheetUpdated,
			[ this ]( const QSharedPointer<Model::Timesheet>& timesheet_ ) { OnTimesheetUpdated( *timesheet_ ); } );
		connect( m_ui.actionRefresh, &QAction::triggered, [ this ]( const bool /*checked_*/ ) { OnRefreshClicked(); } );

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
	}

	void MainWindow::OnRefreshClicked()
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
		QLineEdit* pWorkDayLineEdit = m_workDays.at( index );
		if ( pWorkDayLineEdit == nullptr )
		{
			return;
		}

		m_currentDayTotalTime = m_currentDayTotalTime.addMSecs( m_currentDayTimer.elapsed() );
		m_currentDayTimer.restart();
		m_workDaysStrings[ index ] = m_currentDayTotalTime.toString( "H'h'mm" );
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

	void MainWindow::SetCurrentWeekLabel()
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

	void MainWindow::OnTimesheetUpdated( const Model::Timesheet& timesheet_ )
	{
		if ( m_workDays.empty() )
		{
			return;
		}

		const Model::TWorkDays& workDays = timesheet_.GetWorkDays();
		for ( const auto& pWorkDay : workDays )
		{
			if ( pWorkDay == nullptr )
			{
				continue;
			}
			const QDate& date = pWorkDay->GetDate();
			if ( date < m_mondayDate )
			{
				continue;
			}
			const QString& timeStr = pWorkDay->GetWorkTime().toString( "H'h'mm" );
			m_workDaysStrings[ date.dayOfWeek() - 1 ] = timeStr;

			if ( date == QDate::currentDate() )
			{
				m_currentDayTotalTime = QTime::fromString( timeStr, "H'h'mm" );
				m_currentDayTimer.start();
			}
		}
		update();
	}
} // namespace View
