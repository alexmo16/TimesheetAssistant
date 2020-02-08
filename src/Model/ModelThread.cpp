#include "ModelThread.h"

#include "Events/Event.h"
#include "Events/EventsSniffer.h"

#include <QDebug>
#include <QThread>

namespace Model
{
	constexpr auto SLEEP_TIME = 5000;

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

		EventsSniffer sniffer( channel, query, this );

		TEvents events;
		while ( m_isRunning )
		{
			// TODO a thread that polls the API every X seconds is not optimal.
			// Should have a subscriber instead.
			qInfo() << "ModelThead tick...";

			// Try to query the windows events API.
			try
			{
				const bool isInError = !sniffer.Sniff( events );
				if ( isInError )
				{
					break;
				}
				_LogEvents( events );
				events.clear();
			}
			catch ( ... )
			{
			}

			msleep( SLEEP_TIME );
		}

		qInfo() << "ModelThread stopped...";
	}

	void ModelThread::stop()
	{
		m_isRunning = false;
	}

} // namespace Model
