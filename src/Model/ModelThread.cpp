#include "ModelThread.h"

#include "Events/EventsSniffer.h"

#include <QDebug>
#include <QThread>

namespace Model
{
	ModelThread::ModelThread( QObject* pParent_ ) : QThread( pParent_ ) {}

	void ModelThread::run()
	{
		m_isRunning = true;
		qInfo() << "ModelThread started...";

		while ( m_isRunning )
		{
			qInfo() << "ModelThead tick...";
			msleep( 1000 );
		}

		qInfo() << "ModelThread stopped...";
	}

	void ModelThread::stop()
	{
		m_isRunning = false;
	}

} // namespace Model
