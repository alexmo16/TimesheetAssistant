#include "WorkDay.h"

#include <QString>
#include <QTime>

namespace Model
{
	WorkDay::WorkDay( const QDate& date_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: QObject( pParent_ ), m_date( date_ ), m_workedTime( QTime( 0, 0 ) )
	{
	}

	QTime WorkDay::getWorkTime()
	{
		QTime copy = m_workedTime;
		return copy;
	}

	void WorkDay::setWorkTime( const QTime& workTime_ )
	{
		m_workedTime = workTime_;
	}

	void WorkDay::setWorkTime( const QString& workTime_, const QString& format_ )
	{
		if ( !( workTime_.isEmpty() && workTime_.isEmpty() ) )
		{
			m_workedTime.fromString( workTime_, format_ );
		}
	}

	void WorkDay::addWorkTime( const QTime& workTime_ )
	{
		m_workedTime = m_workedTime.addMSecs( workTime_.msecsSinceStartOfDay() );
	}

} // namespace Model
