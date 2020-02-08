#pragma once

#include "Event.h"

#include <QObject>

#include <windows.h>
#include <winevt.h>

namespace Model
{
	class QueryParser : public QObject
	{
		Q_OBJECT

	public:
		QueryParser( QObject* pParent_ = Q_NULLPTR );

		DWORD ParseToEvents( const EVT_HANDLE& results_, Model::TEvents& xmlEvents_ ) const;
	};

} // namespace Model
