#include "EventsSniffer.h"

#include "Event.h"
#include "QueryParser.h"

#include <QDebug>
#include <QObject>
#include <QString>

#include <string>
#include <windows.h>
#include <winevt.h>

namespace Model
{
	EventsSniffer::EventsSniffer(
		const std::wstring& channel_, const std::wstring& query_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: QObject( pParent_ ), m_channel( channel_ ), m_query( query_ )
	{
	}

	bool EventsSniffer::Sniff( TEvents& events_ )
	{
		DWORD status = ERROR_SUCCESS;

		const QueryParser parser( this );

		// First argument is nullptr because we want to make a query on the local computer.
		EVT_HANDLE results = EvtQuery( nullptr, m_channel.c_str(), m_query.c_str(), EvtQueryChannelPath );
		QString errorMessage( "" );
		if ( results == nullptr )
		{
			status = GetLastError();
			switch ( status )
			{
			case ERROR_EVT_CHANNEL_NOT_FOUND:
				errorMessage = "The channel was not found.";
				break;
			case ERROR_EVT_INVALID_QUERY:
				errorMessage = "The query is not valid.";
				break;
			case ERROR_EVT_CHANNEL_CANNOT_ACTIVATE:
				errorMessage = "The channel failed to activate.";
				break;
			default:
				errorMessage = "An error occurred with the event query.";
			}

			qCritical() << errorMessage;
		}

		// If there is no error in the query, lets process the result to retrieve a human readable message.
		if ( errorMessage.isEmpty() )
		{
			status = parser.ParseToEvents( results, events_ );
			parser.ApplyEventsFilter( QueryParser::EventsFilter::E_CURRENT_WEEK_EVENTS, events_ );
		}

		// No matter if there is an error or not, we need to cleanup.
		if ( results )
		{
			EvtClose( results );
		}

		return status == ERROR_SUCCESS; // If there is no message it means there is no errors.

	} // namespace Model
} // namespace Model
