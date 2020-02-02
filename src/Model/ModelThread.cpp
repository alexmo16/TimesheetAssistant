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

		EventsSniffer sniffer( this );

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
