#pragma once

#include <QDate>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QTime>
#include <QVector>

namespace Model
{
	class WorkDay : public QObject
	{
		Q_OBJECT

	public:
		WorkDay( const QDate& date_, QObject* pParent_ = Q_NULLPTR );
		~WorkDay() = default;

		QTime GetWorkTime();
		void SetWorkTime( const QTime& workTime_ );
		void SetWorkTime( const QString& workTime_, const QString& format_ );
		void AddWorkTime( const QTime& workTime_ );
		QDate GetDate()
		{
			return m_date;
		};

	private:
		QTime m_workedTime;
		QDate m_date;
	};

	typedef QVector<QSharedPointer<WorkDay>> TWorkDays;
	Q_DECLARE_METATYPE( TWorkDays );
} // namespace Model
