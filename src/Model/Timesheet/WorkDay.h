#pragma once

#include <QObject>
#include <QString>
#include <QTime>

namespace Model
{
	class WorkDay : public QObject
	{
		Q_OBJECT

	public:
		WorkDay( QObject* pParent_ = Q_NULLPTR );

		QTime GetWorkTime();
		void SetWorkTime( const QTime& workTime_ );
		void SetWorkTime( const QString& workTime_, const QString& format_ );

	private:
		QTime m_workedTime;
	};

	typedef std::vector<std::shared_ptr<WorkDay>> TWorkDays;
} // namespace Model
