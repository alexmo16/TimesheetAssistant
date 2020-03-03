#include "TimesheetBuilder.h"

#include "Timesheet.h"
#include "WorkDay.h"

#include <QDate>
#include <QDebug>

namespace Model
{
	TimesheetBuilder::TimesheetBuilder( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	void TimesheetBuilder::Build( const TEvents& events_, Timesheet& timesheet_ )
	{
		if ( events_.size() < 2 )
		{
			Q_ASSERT( false );
			return;
		}

		TWorkDays workDays;
		QDate currentDate;

		QDateTime firstTime;
		QDateTime lastTime;
		QSharedPointer<WorkDay> workDay;
		for ( const auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}

			const QDateTime& dateTime = pEvent->GetDateTime();
			const QDate& date = dateTime.date();

			if ( pEvent == events_.back() )
			{
				if ( !firstTime.isNull() && !lastTime.isNull() )
				{
					workDay = QSharedPointer<WorkDay>( new WorkDay( date, &timesheet_ ) );
					const auto ms = lastTime.toMSecsSinceEpoch() - firstTime.toMSecsSinceEpoch();
					QTime workedTime = QTime::fromMSecsSinceStartOfDay( ms );
					workDay->SetWorkTime( workedTime );
					workDays.push_back( workDay );
				}
				else if ( !firstTime.isNull() && lastTime.isNull() )
				{
					Q_ASSERT( false );
					return;
				}
				break;
			}

			if ( currentDate == date )
			{
				if ( pEvent->GetEventType() == Event::EventType::E_LOCKED )
				{
					lastTime = dateTime;
				}
			}
			else if ( pEvent->GetEventType() == Event::EventType::E_UNLOCKED )
			{
				if ( !firstTime.isNull() && !lastTime.isNull() )
				{
					workDay = QSharedPointer<WorkDay>( new WorkDay( date, &timesheet_ ) );
					const auto ms = lastTime.toMSecsSinceEpoch() - firstTime.toMSecsSinceEpoch();
					QTime workedTime = QTime::fromMSecsSinceStartOfDay( ms );
					workDay->SetWorkTime( workedTime );
					workDays.push_back( workDay );
				}
				else if ( !firstTime.isNull() && lastTime.isNull() )
				{
					Q_ASSERT( false );
					return;
				}

				currentDate = date;
				firstTime = dateTime;
				lastTime = QDateTime();
			}
		}

		timesheet_.SetWorkDays( workDays );
	}
} // namespace Model
