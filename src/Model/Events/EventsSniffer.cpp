#include "EventsSniffer.h"

#include <QDebug>
#include <QObject>
#include <QString>

#include <string>
#include <windows.h>
#include <winevt.h>
#pragma comment( lib, "wevtapi.lib" )

namespace // anonymous
{
#define ARRAY_SIZE 10
#define TIMEOUT 1000

	// Render a single event
	DWORD _RenderEvent( EVT_HANDLE event_, QString& xmlEvent_ )
	{
		xmlEvent_ = "";
		DWORD status = ERROR_SUCCESS;
		DWORD bufferSize = 0;
		DWORD bufferUsed = 0;
		DWORD propertyCount = 0;
		LPWSTR pRenderedContent = nullptr;

		const bool isOK =
			EvtRender( nullptr, event_, EvtRenderEventXml, bufferSize, pRenderedContent, &bufferUsed, &propertyCount );
		if ( !isOK )
		{
			status = GetLastError();
			if ( status == ERROR_INSUFFICIENT_BUFFER )
			{
				bufferSize = bufferUsed;
				pRenderedContent = ( LPWSTR )malloc( bufferSize );
				if ( pRenderedContent != nullptr )
				{
					EvtRender(
						nullptr, event_, EvtRenderEventXml, bufferSize, pRenderedContent, &bufferUsed, &propertyCount );
					status = GetLastError();
				}
				else
				{
					qCritical() << "malloc failed";
					status = ERROR_OUTOFMEMORY;
				}
			}
		}

		if ( status == ERROR_SUCCESS )
		{
			if ( pRenderedContent != 0 )
			{
				xmlEvent_ = QString::fromStdWString( pRenderedContent );
			}
		}
		else
		{
			qCritical() << "EvtRender failed with " << status;
		}

		if ( pRenderedContent != nullptr )
		{
			free( pRenderedContent );
		}

		return status;
	}

	// Enumerate all the events in the result set.
	DWORD _RenderResults( const EVT_HANDLE& results_, QVector<QString>& xmlEvents_ )
	{
		DWORD status = ERROR_SUCCESS;
		EVT_HANDLE events[ ARRAY_SIZE ];
		DWORD wordReturned = 0;

		// While there is no error do this.
		while ( status == ERROR_SUCCESS )
		{
			// Get a block of events from the result set.
			const bool isOK = EvtNext( results_, ARRAY_SIZE, events, TIMEOUT, 0, &wordReturned );
			if ( !isOK )
			{
				status = GetLastError();
				break;
			}

			// For each event, call the PrintEvent function which renders the event for display.
			QString tempXmlString;
			for ( DWORD i = 0; i < wordReturned; i++ )
			{
				status = _RenderEvent( events[ i ], tempXmlString );
				if ( status != ERROR_SUCCESS )
				{
					break;
				}
				if ( !tempXmlString.isEmpty() )
				{
					xmlEvents_.push_back( tempXmlString );
				}
				EvtClose( events[ i ] );
				events[ i ] = nullptr;
			}
		}

		// Make sure there nothing to clean.
		for ( DWORD i = 0; i < wordReturned; i++ )
		{
			if ( nullptr != events[ i ] )
			{
				EvtClose( events[ i ] );
				events[ i ] = nullptr;
			}
		}

		return status == ERROR_SUCCESS || status == ERROR_NO_MORE_ITEMS ? ERROR_SUCCESS : status;
	}
} // namespace

namespace Model
{
	EventsSniffer::EventsSniffer(
		const std::wstring& channel_, const std::wstring& query_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: QObject( pParent_ ), m_channel( channel_ ), m_query( query_ )
	{
	}

	bool EventsSniffer::Sniff( QVector<QString>& xmlEvents_ )
	{
		DWORD status = ERROR_SUCCESS;

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
			status = _RenderResults( results, xmlEvents_ );
		}

		// No matter if there is an error or not, we need to cleanup.
		if ( results )
		{
			EvtClose( results );
		}

		return status == ERROR_SUCCESS; // If there is no message it means there is no errors.

	} // namespace Model
} // namespace Model
