#include "Timesheet.h"

#include "WorkDay.h"

namespace Model
{
	Timesheet::Timesheet( TWorkDays workDays_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: QObject( pParent_ ), m_workDays( workDays_ )
	{
	}

} // namespace Model
