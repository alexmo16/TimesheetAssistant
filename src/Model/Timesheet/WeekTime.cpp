#include "WeekTime.h"

#include <QObject>
#include <QString>

namespace Model
{
	WeekTime::WeekTime( QObject* pParent_ ) : QObject( pParent_ ) {}

	bool WeekTime::addTime( int timeMs_ )
	{
		if ( timeMs_ > INT_MAX || ( m_totalTimeMs + timeMs_ ) > INT_MAX )
		{
			return false;
		}

		m_totalTimeMs += timeMs_;
		return true;
	}

	int WeekTime::getTime() const
	{
		return m_totalTimeMs;
	}

	void WeekTime::reset()
	{
		m_totalTimeMs = 0;
	}

	QString weekTimeToString( const WeekTime& weekTime_ )
	{
		const int msInHour = 1000 * 60 * 60;
		const int msInMinutes = 1000 * 60;

		const int& timeMs = weekTime_.getTime();
		const int hours = timeMs / msInHour;
		int rest = timeMs - ( hours * msInHour );

		const int minutes = rest / msInMinutes;

		QString timeString = QString::number( hours ) + "h" + QString::number( minutes );

		const QStringList& timeStrings = timeString.split( "h" );
		if ( timeStrings.size() > 1 && timeStrings[ 1 ] == "0" )
		{
			timeString.append( "0" );
		}

		return timeString;
	}

} // namespace Model
