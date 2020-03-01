#include "ModelThread.h"

#include "Events/Event.h"
#include "Events/QueryParser.h"
#include "Timesheet/Timesheet.h"
#include "Timesheet/TimesheetBuilder.h"

#include <QDebug>
#include <QThread>
#include <windows.h>
#include <winevt.h>

namespace Model
{
	constexpr auto SLEEP_TIME = 100;
	void _LogEvents( const TEvents& events_ );
	void _logTimesheet( const Timesheet& timesheet_ );

	ModelThread::ModelThread( QObject* pParent_ ) : QThread( pParent_ )
	{
		this->moveToThread( this );
	}

	void ModelThread::run()
	{
		m_isRunning = true;
		qInfo() << "ModelThread started...";

		// Event 4800 of Security is "Locked" and 4801 is "Unlocked" [System[(EventID=4800 or EventID=4801)]]
		// Only last 7 days are query to not ask for all events logged since the Big Bang.
		const std::wstring query = L"Event/System[(EventID=4800 or EventID=4801)] and "
								   L"Event/System/TimeCreated[timediff(@SystemTime) <= 604800000]";
		const std::wstring channel = L"Security";

		// Init new data subscriber
		HANDLE newEventHandle = CreateEvent( NULL, false, true, NULL );
		if ( newEventHandle == NULL )
		{
			Q_ASSERT( "CreateEvent failed with " + GetLastError() );
			qInfo() << "ModelThread stopped...";
			return;
		}

		EVT_HANDLE hSubscription = EvtSubscribe(
			NULL, newEventHandle, channel.c_str(), query.c_str(), NULL, NULL, NULL, EvtSubscribeStartAtOldestRecord );
		if ( hSubscription == NULL )
		{
			DWORD status = GetLastError();
			if ( status != ERROR_SUCCESS )
			{
				Q_ASSERT( "CreateEvent failed with " + status );
				qInfo() << "ModelThread stopped...";
				return;
			}
		}

		// Init Parser
		QueryParser parser( this );

		// Init Data
		TEvents events;
		TimesheetBuilder timesheetBuilder( this );
		Timesheet timesheet;

		// Thread loop
		DWORD dwWait = 0;
		while ( m_isRunning )
		{
			try
			{
				// Wait for a signal, if there is one, we gonna query the API to get the events.
				dwWait = WaitForSingleObject( newEventHandle, SLEEP_TIME );
				if ( dwWait != 0 )
				{
					continue;
				}
				const DWORD isInError = parser.ParseToEvents( hSubscription, events );
				if ( isInError != ERROR_SUCCESS )
				{
					break;
				}
				parser.ApplyEventsFilter( QueryParser::EventsFilter::E_CURRENT_WEEK_EVENTS, events );

				if ( !events.empty() )
				{
					_LogEvents( events );
					timesheetBuilder.Build( events, timesheet );
					qInfo() << "-------------------------------------------------";
					_logTimesheet( timesheet );
					emit TimesheetUpdated( timesheet );
				}
			}

			catch ( const std::exception& exception )
			{
				qCritical() << "An exception occurred: " << exception.what();
				Q_ASSERT_X( false, "ModelThread", exception.what() );
				break;
			}

			catch ( ... )
			{
				qCritical() << "An unknown exception occurred";
				Q_ASSERT_X( false, "ModelThread", "An unknown exception occurred" );
				break;
			}
		}

		qInfo() << "ModelThread stopped...";
	}

	void ModelThread::stop()
	{
		m_isRunning = false;
	}

	// Log queried events informations.
	void _LogEvents( const TEvents& events_ )
	{
		for ( const auto& pEvent : events_ )
		{
			if ( pEvent != nullptr )
			{
				qInfo() << "Time: " << pEvent->GetDateTime();
				qInfo() << "Event ID: " << pEvent->GetEventType();
			}
		}
		qInfo() << events_.size();
	}

	// Log a timesheet workdays
	void _logTimesheet( const Timesheet& timesheet_ )
	{
		const TWorkDays& workDays = timesheet_.GetWorkDays();
		for ( const auto& pWorkDay : workDays )
		{
			if ( pWorkDay == nullptr )
			{
				continue;
			}
			qInfo() << "WorkedTime: " << pWorkDay->GetWorkTime();
		}
	}

} // namespace Model
