#pragma once

#include "Config/Config.h"
#include "Event.h"

#include <QObject>
#include <QSharedPointer>

#include <windows.h>
#include <winevt.h>

namespace Model
{
	class QueryParser : public QObject
	{
		Q_OBJECT

	public:
		enum class EventsFilter
		{
			E_CURRENT_WEEK_EVENTS,
			E_WEEKEND_EVENTS,
			E_NONE
		};
		Q_ENUM( EventsFilter )

		QueryParser( QSharedPointer<Config> pConfig_, QObject* pParent_ = Q_NULLPTR );

		DWORD parseToEvents( const EVT_HANDLE& results_, Model::TEvents& xmlEvents_ ) const;

		void applyEventsFilter( const EventsFilter filter_, Model::TEvents& events_ ) const;

	private:
		QSharedPointer<Config> m_pConfig;
	};

} // namespace Model
