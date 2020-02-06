#include "Event.h"

#include <QDebug>
#include <QString>
#include <QtXml/QDomDocument>

namespace Model
{
	Event::Event( QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ ) {}

	Event::Event( const QString& xmlEvent_, QObject* pParent_ /*= Q_NULLPTR*/ ) : QObject( pParent_ )
	{
		SetInfoFromXml( xmlEvent_ );
	}

	void Event::SetInfoFromXml( const QString& xmlEvent_ )
	{
		QDomDocument doc;
		doc.setContent( xmlEvent_ );

		const QDomElement& systemElement = doc.elementsByTagName( "System" ).at( 0 ).toElement();

		m_type = EventType( systemElement.elementsByTagName( "EventID" ).at( 0 ).toElement().text().toInt() );
		m_dateTime = systemElement.elementsByTagName( "TimeCreated" ).at( 0 ).toElement().attribute( "SystemTime" );
	}

} // namespace Model
