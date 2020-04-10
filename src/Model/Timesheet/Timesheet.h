#pragma once

#include "Events/Event.h"
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

	void build( const TEvents& events_, Timesheet& timesheet_ );
} // namespace Model
