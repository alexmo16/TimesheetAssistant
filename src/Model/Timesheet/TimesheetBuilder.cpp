#include "TimesheetBuilder.h"

#include "Timesheet.h"
#include "WorkDay.h"

#include <QDate>
#include <QDebug>
#include <QSharedPointer>

namespace Model
{
	enum class TypeOfEvents
	{
		E_LOGIN,
		E_LOGOUT
	};

	void _calculateWorkTime(
		const QDateTime& firstTime_, const QDateTime& lastTime_, QSharedPointer<WorkDay>& workDay_ );

	TimesheetBuilder::TimesheetBuilder( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	void TimesheetBuilder::build( const TEvents& events_, Timesheet& timesheet_ )
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

		TypeOfEvents eventWaitingFor = TypeOfEvents::E_LOGIN;

		for ( const auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}

			const QDateTime& eventTime = pEvent->getDateTime();
			const QDate& eventDate = eventTime.date();

			// Useless to initialize those variables if it's the last event.
			if ( currentDate.isNull() && pEvent != events_.back() )
			{
				currentDate = eventDate;
				firstTime = eventTime;
				lastTime = QDateTime();
				workDay = QSharedPointer<WorkDay>( new WorkDay( currentDate, &timesheet_ ) );
				eventWaitingFor = TypeOfEvents::E_LOGOUT;
				continue;
			}

			if ( pEvent == events_.back() )
			{
				if ( pEvent->isLogoutEvent() )
				{
					lastTime = eventTime;
					_calculateWorkTime( firstTime, lastTime, workDay );
				}
				if ( !workDay.isNull() )
				{
					workDays.push_back( workDay );
					workDay.clear();
				}
				continue;
			}

			if ( currentDate == eventDate )
			{
				// Processing events logged in the same day.
				if ( pEvent->isLogoutEvent() && eventWaitingFor == TypeOfEvents::E_LOGOUT )
				{
					lastTime = eventTime;
					_calculateWorkTime( firstTime, lastTime, workDay );
					eventWaitingFor = TypeOfEvents::E_LOGIN;
				}
				else if ( pEvent->isLoginEvent() && eventWaitingFor == TypeOfEvents::E_LOGIN )
				{
					firstTime = eventTime;
					lastTime = QDateTime();
					eventWaitingFor = TypeOfEvents::E_LOGOUT;
				}
			}
			else if ( pEvent->isLoginEvent() )
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
				eventWaitingFor = TypeOfEvents::E_LOGOUT;
			}
		}
		timesheet_.setWorkDays( workDays );
	}

	void _calculateWorkTime(
		const QDateTime& firstTime_, const QDateTime& lastTime_, QSharedPointer<WorkDay>& workDay_ )
	{
		const auto ms = lastTime_.toMSecsSinceEpoch() - firstTime_.toMSecsSinceEpoch();
		QTime workedTime = QTime::fromMSecsSinceStartOfDay( ms );
		if ( workDay_ != nullptr && workedTime.isValid() )
		{
			workDay_->addWorkTime( workedTime );
		}
	}
} // namespace Model
