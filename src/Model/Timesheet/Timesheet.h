#pragma once

#include "WorkDay.h"

#include <QObject>

#include <vector>

namespace Model
{
	class Timesheet : public QObject
	{
		Q_OBJECT

	public:
		Timesheet( QObject* pParent_ = Q_NULLPTR );
		Timesheet( TWorkDays workDays_, QObject* pParent_ = Q_NULLPTR );

		const TWorkDays GetWorkDays() const;
		void SetWorkDays( TWorkDays workDays_ );

	private:
		TWorkDays m_workDays;
	};

} // namespace Model
