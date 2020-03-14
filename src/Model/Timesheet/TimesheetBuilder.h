#pragma once

#include "Events/Event.h"

#include <QObject>

namespace Model
{
	class Timesheet;

	class TimesheetBuilder : public QObject
	{
		Q_OBJECT

	public:
		TimesheetBuilder( QObject* pParent_ = Q_NULLPTR );
		~TimesheetBuilder() = default;

		void build( const TEvents& events_, Timesheet& timesheet_ );
	};
} // namespace Model
