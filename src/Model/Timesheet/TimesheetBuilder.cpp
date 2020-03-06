#include "TimesheetBuilder.h"

#include "Timesheet.h"
#include "WorkDay.h"

#include <QDate>
#include <QDebug>
#include <QSharedPointer>

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
		QDate currentDate; // current date the algo is processing

		QDateTime firstTime;
		QDateTime lastTime;
		QSharedPointer<WorkDay> workDay;
		for ( const auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}

			const QDateTime& eventTime = pEvent->GetDateTime();
			const QDate& eventDate = eventTime.date();

			if ( pEvent == events_.back() )
			{
				if ( pEvent->IsLogoutEvent() && !firstTime.isNull() && !lastTime.isNull() )
				{
					lastTime = eventTime;
					const auto ms = lastTime.toMSecsSinceEpoch() - firstTime.toMSecsSinceEpoch();
					QTime workedTime = QTime::fromMSecsSinceStartOfDay( ms );
					workDay->AddWorkTime( workedTime );
				}
				if ( !workDay.isNull() )
				{
					workDays.push_back( workDay );
					workDay.clear();
				}
				break;
			}

			if ( currentDate == eventDate )
			{
				if ( pEvent->IsLogoutEvent() )
				{
					lastTime = eventTime;
					const auto ms = lastTime.toMSecsSinceEpoch() - firstTime.toMSecsSinceEpoch();
					QTime workedTime = QTime::fromMSecsSinceStartOfDay( ms );
					workDay->AddWorkTime( workedTime );
				}
				else if ( pEvent->IsLoginEvent() )
				{
					firstTime = eventTime;
					lastTime = QDateTime();
				}
			}
			else if ( pEvent->IsLoginEvent() )
			{
				if ( !workDay.isNull() )
				{
					workDays.push_back( workDay );
					workDay.clear();
				}

				currentDate = eventDate;
				firstTime = eventTime;
				lastTime = QDateTime();
				workDay = QSharedPointer<WorkDay>( new WorkDay( currentDate, &timesheet_ ) );
			}
		}

		timesheet_.SetWorkDays( workDays );
	}
} // namespace Model
