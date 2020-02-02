#pragma once

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

	private:
		bool m_isRunning = false;
	};
} // namespace Model
