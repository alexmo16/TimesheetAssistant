#include "EventsSniffer.h"

#include <QDebug>
#include <QObject>
#include <QString>

#include <string>
#include <windows.h>
#include <winevt.h>

#pragma comment( lib, "wevtapi.lib" )

namespace Model
{
	EventsSniffer::EventsSniffer( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	bool EventsSniffer::Sniff()
	{
		DWORD status = ERROR_SUCCESS;

		// First argument is nullptr because we want to make a query on the local computer.
		EVT_HANDLE hResults = EvtQuery( NULL, m_channel.c_str(), m_query.c_str(), EvtQueryTolerateQueryErrors );
		if ( !hResults )
		{
			status = ERROR;
		}

		// If there is no error in the query, lets process the result to retrieve a human readable message.
		if ( status != ERROR )
		{
			if ( PrintQueryStatuses( hResults ) == ERROR_SUCCESS ) {}
		}

		// No matter if there is an error or not, we need to cleanup.
		if ( hResults )
		{
			EvtClose( hResults );
		}

		return status == ERROR_SUCCESS;
	} // namespace Model

	DWORD EventsSniffer::PrintQueryStatuses( EVT_HANDLE hResults_ )
	{
		return ERROR_SUCCESS;
	}

	DWORD EventsSniffer::GetQueryStatusProperty(
		EVT_QUERY_PROPERTY_ID id_, EVT_HANDLE hResults_, PEVT_VARIANT& pProperty_ )
	{
		return ERROR_SUCCESS;
	}

	DWORD EventsSniffer::PrintResults( EVT_HANDLE hResults_ )
	{
		return ERROR_SUCCESS;
	}

} // namespace Model
