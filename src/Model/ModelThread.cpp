#include "ModelThread.h"

#include "Events/EventsSniffer.h"

#include <QDebug>
#include <QThread>

namespace Model
{
	ModelThread::ModelThread( QObject* pParent_ ) : QThread( pParent_ )
	{
		this->moveToThread( this );
	}

	void ModelThread::run()
	{
		m_isRunning = true;
		qInfo() << "ModelThread started...";

		// Event 4800 of Security is "Locked" and 4801 is "Unlocked" [System[(EventID=4800 or EventID=4801)]]
		const std::wstring query = L"Event/System[(EventID=4800 or EventID=4801)]";
		const std::wstring channel = L"Security";

		EventsSniffer sniffer( channel, query, this );

		while ( m_isRunning )
		{
			qInfo() << "ModelThead tick...";

			// Trying to query the windows events API.
			try
			{
				const bool isInError = !sniffer.Sniff();
				if ( isInError )
				{
					break;
				}
			}
			catch ( ... )
			{
			}

			msleep( 1000 );
		}

		qInfo() << "ModelThread stopped...";
	}

	void ModelThread::stop()
	{
		m_isRunning = false;
	}

} // namespace Model
