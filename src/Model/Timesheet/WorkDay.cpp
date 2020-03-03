#include "WorkDay.h"

#include <QString>
#include <QTime>

namespace Model
{
	WorkDay::WorkDay( const QDate& date_, QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ), m_date( date_ ) {}

	QTime WorkDay::GetWorkTime()
	{
		QTime copy = m_workedTime;
		return copy;
	}

	void WorkDay::SetWorkTime( const QTime& workTime_ )
	{
		m_workedTime = workTime_;
	}

	void WorkDay::SetWorkTime( const QString& workTime_, const QString& format_ )
	{
		if ( !( workTime_.isEmpty() && workTime_.isEmpty() ) )
		{
			m_workedTime.fromString( workTime_, format_ );
		}
	}

} // namespace Model
