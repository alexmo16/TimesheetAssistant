#pragma once
#pragma once

#include "Config/Config.h"
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
		ModelThread( QSharedPointer<Config> pConfig_, QObject* pParent_ = Q_NULLPTR );
		~ModelThread() = default;

		void run() override;
		void stop();

	signals:
		void timesheetUpdated( const QSharedPointer<Timesheet>& timesheet_ );

	private:
		QSharedPointer<Config> m_pConfig;
		bool m_isRunning = false;
	};
} // namespace Model
