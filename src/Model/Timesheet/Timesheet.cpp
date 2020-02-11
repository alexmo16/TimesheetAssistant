#include "Timesheet.h"

#include "WorkDay.h"

namespace Model
{
	Timesheet::Timesheet( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	Timesheet::Timesheet( TWorkDays workDays_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: QObject( pParent_ ), m_workDays( workDays_ )
	{
	}

	const TWorkDays Timesheet::GetWorkDays() const
	{
		return m_workDays;
	}

	void Timesheet::SetWorkDays( TWorkDays workDays_ )
	{
		m_workDays = workDays_;
	}
} // namespace Model
