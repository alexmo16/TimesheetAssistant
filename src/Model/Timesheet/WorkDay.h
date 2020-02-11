#pragma once

#include <QDate>
#include <QObject>
#include <QString>
#include <QTime>

namespace Model
{
	class WorkDay : public QObject
	{
		Q_OBJECT

	public:
		WorkDay( const QDate& date_, QObject* pParent_ = Q_NULLPTR );

		QTime GetWorkTime();
		void SetWorkTime( const QTime& workTime_ );
		void SetWorkTime( const QString& workTime_, const QString& format_ );
		QDate GetDate()
		{
			return m_date;
		};

	private:
		QTime m_workedTime;
		QDate m_date;
	};

	typedef std::vector<std::shared_ptr<WorkDay>> TWorkDays;
} // namespace Model
