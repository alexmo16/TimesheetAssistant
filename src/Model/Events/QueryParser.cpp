#include "QueryParser.h"

#include "Config/Config.h"
#include "Event.h"
#include "Utils/NotImplemented.h"

#include <QDebug>
#include <QtGlobal>
#include <windows.h>
#include <winevt.h>

namespace Model
{
	constexpr auto CHUNK_SIZE = 10;
	constexpr auto TIMEOUT = 1000;

	DWORD convertEvent( EVT_HANDLE event_, std::unique_ptr<Model::Event>& pXmlEvent_ )
	{
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
				const QString& xmlDocInString = QString::fromStdWString( pRenderedContent );
				if ( getEventTargetUserName( xmlDocInString ) == qgetenv( "USERNAME" ) )
				{
					pXmlEvent_ = std::make_unique<Model::Event>( xmlDocInString );
				}
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

	void keepCurrentWeekEvents( Model::TEvents& events_ )
	{
		Model::TEvents filteredEvents;

		for ( auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}

			// 1 = Monday and 7 = Sunday
			const int dayNumber = pEvent->getDateTime().date().dayOfWeek();
			// we compare to 5 because it is the last work day (friday).
			if ( ( dayNumber - 5 ) <= 0 )
			{
				filteredEvents.push_back( std::move( pEvent ) );
			}
		}

		events_ = std::move( filteredEvents );
	}

	void keepWeekendEvents( Model::TEvents& events_ )
	{

		Model::TEvents filteredEvents;

		for ( auto& pEvent : events_ )
		{
			if ( pEvent == nullptr )
			{
				continue;
			}

			// 1 = Monday and 7 = Sunday
			const int dayNumber = pEvent->getDateTime().date().dayOfWeek();
			// we compare to 5 because it is the last work day (friday).
			if ( ( dayNumber - 5 ) > 0 )
			{
				filteredEvents.push_back( std::move( pEvent ) );
			}
		}

		events_ = std::move( filteredEvents );
	}

	bool isEventActivated( const Config& config_, const Event::EventType eventType_ )
	{
		bool isActivated = false;

		switch ( eventType_ )
		{
		case Event::EventType::E_LOCKED:
			isActivated = config_.get( Config::Keys::LOCKED_ACTIVATED ).toBool();
			break;
		case Event::EventType::E_UNLOCKED:
			isActivated = config_.get( Config::Keys::UNLOCKED_ACTIVATED ).toBool();
			break;
		case Event::EventType::E_LOGOFF:
			isActivated = config_.get( Config::Keys::LOGOFF_ACTIVATED ).toBool();
			break;
		case Event::EventType::E_LOGON:
			isActivated = config_.get( Config::Keys::LOGON_ACTIVATED ).toBool();
			break;
		default:
			isActivated = false;
			break;
		}

		return isActivated;
	}

	QueryParser::QueryParser( QSharedPointer<Config> pConfig_, QObject* pParent_ /*= Q_NULLPTR*/ )
		: m_pConfig( pConfig_ ), QObject( pParent_ )
	{
	}

	// Enumerate all the events in the result set.
	DWORD QueryParser::parseToEvents( const EVT_HANDLE& results_, Model::TEvents& xmlEvents_ ) const
	{
		DWORD status = ERROR_SUCCESS;
		EVT_HANDLE events[ CHUNK_SIZE ];
		DWORD wordReturned = 0;

		// While there is no error do this.
		while ( status == ERROR_SUCCESS )
		{
			// Get a block of events from the result set.
			const bool isOK = EvtNext( results_, CHUNK_SIZE, events, TIMEOUT, 0, &wordReturned );
			if ( !isOK )
			{
				status = GetLastError();
				break;
			}

			// For each event, call the PrintEvent function which renders the event for display.
			std::unique_ptr<Model::Event> pTmpEvent;
			for ( DWORD i = 0; i < wordReturned; i++ )
			{
				status = convertEvent( events[ i ], pTmpEvent );
				if ( status != ERROR_SUCCESS )
				{
					break;
				}
				if ( pTmpEvent != nullptr && isEventActivated( *m_pConfig, pTmpEvent->getEventType() ) )
				{
					xmlEvents_.push_back( std::move( pTmpEvent ) );
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

	void QueryParser::applyEventsFilter( const EventsFilter filter_, Model::TEvents& events_ ) const
	{
		switch ( filter_ )
		{
		case EventsFilter::E_CURRENT_WEEK_EVENTS:
			keepCurrentWeekEvents( events_ );
			break;
		case EventsFilter::E_WEEKEND_EVENTS:
			keepWeekendEvents( events_ );
			break;
		default:
			Q_ASSERT_X( false, "ApplyEventsFilter", "Filter type not supported" );
		}
	}

} // namespace Model
