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
		~Timesheet() = default;

		const TWorkDays getWorkDays() const;
		void setWorkDays( TWorkDays workDays_ );

	private:
		TWorkDays m_workDays;
	};

} // namespace Model
