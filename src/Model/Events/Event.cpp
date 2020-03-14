#include "Event.h"

#include <QDateTime>
#include <QDebug>
#include <QString>
#include <QtXml/QDomDocument>

namespace Model
{
	Event::Event( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	Event::Event( const QString& xmlEvent_, QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ )
	{
		setInfoFromXml( xmlEvent_ );
	}

	void Event::setInfoFromXml( const QString& xmlEvent_ )
	{
		QDomDocument doc;
		doc.setContent( xmlEvent_ );

		const QDomElement& systemElement = doc.elementsByTagName( "System" ).at( 0 ).toElement();

		m_type = EventType( systemElement.elementsByTagName( "EventID" ).at( 0 ).toElement().text().toInt() );
		const QString& systemTime =
			systemElement.elementsByTagName( "TimeCreated" ).at( 0 ).toElement().attribute( "SystemTime" );

		const auto splittedTime = systemTime.split( "." );
		if ( splittedTime.isEmpty() )
		{
			Q_ASSERT( false );
			return;
		}

		const QString& timeWithoutMs = splittedTime.first();
		if ( !timeWithoutMs.isEmpty() )
		{
			m_dateTime = QDateTime::fromString( timeWithoutMs, "yyyy-MM-ddTHH:mm:ss" );
			m_dateTime.setTimeSpec( Qt::UTC );
			m_dateTime = m_dateTime.toLocalTime();
			Q_ASSERT( m_dateTime.isValid() );
		}
	}

	bool Event::isLoginEvent() const
	{
		return m_type == EventType::E_LOGON || m_type == EventType::E_UNLOCKED;
	}

	bool Event::isLogoutEvent() const
	{
		return m_type == EventType::E_LOCKED || m_type == EventType::E_LOGOFF;
	}

	QString getEventTargetUserName( const QString& xmlEvent_ )
	{
		QDomDocument doc;
		doc.setContent( xmlEvent_ );

		const QDomElement& eventDataElement = doc.elementsByTagName( "EventData" ).at( 0 ).toElement();
		const QDomNodeList& nodes = eventDataElement.elementsByTagName( "Data" );
		for ( int index = 0; index < nodes.size(); ++index )
		{
			const QDomElement& element = nodes.at( index ).toElement();
			if ( element.attribute( "Name" ) == "TargetUserName" )
			{
				return element.text();
			}
		}

		return QString();
	}

} // namespace Model
