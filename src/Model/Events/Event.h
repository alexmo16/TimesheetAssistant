#pragma once

#include <QObject>

class QString;
class QDomDocument;

namespace Model
{
	class Event : public QObject
	{
		Q_OBJECT

	public:
		enum class EventType
		{
			E_LOCKED = 4800,   // Real Windows id  for lock event
			E_UNLOCKED = 4801, // Real Windows id for unlock event
			E_NONE = -1
		};
		Q_ENUM( EventType )

		Event( QObject* pParent_ = Q_NULLPTR );
		Event( const QString& xmlEvent_, QObject* pParent_ = Q_NULLPTR );

		QString GetDateTime() const
		{
			return m_dateTime;
		}

		EventType GetEventType() const
		{
			return m_type;
		}

		void SetInfoFromXml( const QString& xmlEvent_ );

	private:
		QString m_dateTime = "";
		EventType m_type = EventType::E_NONE;
	};

	typedef std::vector<std::unique_ptr<Model::Event>> TEvents;

} // namespace Model
