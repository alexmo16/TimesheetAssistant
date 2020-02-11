#include "TimesheetBuilder.h"

#include "Timesheet.h"
#include "WorkDay.h"

namespace Model
{
	TimesheetBuilder::TimesheetBuilder( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	void TimesheetBuilder::Build( const TEvents& events_, Timesheet& timesheet_ )
	{
		TWorkDays workDays;
		for ( const auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}
		}

		timesheet_.SetWorkDays( workDays );
	}
} // namespace Model
