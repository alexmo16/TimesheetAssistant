#pragma once

#include <QObject>
#include <QString>

namespace Model
{
	class WeekTime : public QObject
	{
		Q_OBJECT

	public:
		WeekTime( QObject* pParent_ = Q_NULLPTR );
		~WeekTime() = default;

		bool addTime( int timeMs_ );

		int getTime() const;

		void reset();

	private:
		int m_totalTimeMs = 0;
	};

	QString weekTimeToString( const WeekTime& weekTime_ );
} // namespace Model
