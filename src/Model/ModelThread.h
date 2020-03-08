#pragma once
#pragma once

#include "Events/Event.h"
#include "Timesheet/Timesheet.h"

#include <QSharedPointer>
#include <QThread>

namespace Model
{
	class ModelThread : public QThread
	{
		Q_OBJECT

	public:
		ModelThread( QObject* pParent_ = Q_NULLPTR );
		~ModelThread() = default;

		void run() override;
		void stop();

	signals:
		void TimesheetUpdated( const QSharedPointer<Timesheet>& timesheet_ );

	private:
		bool m_isRunning = false;
	};
} // namespace Model
