#pragma once

#include "Timesheet/Timesheet.h"

#include <QThread>

namespace Model
{
	class ModelThread : public QThread
	{
		Q_OBJECT

	public:
		ModelThread( QObject* pParent_ = Q_NULLPTR );

		void run() override;
		void stop();

	signals:
		void TimesheetUpdated( const Timesheet& timesheet_ );

	private:
		bool m_isRunning = false;
	};
} // namespace Model
