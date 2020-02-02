#pragma once

#include <QObject>

namespace Model
{
	class EventsSniffer : public QObject
	{
		Q_OBJECT

	public:
		EventsSniffer( QObject* parent = Q_NULLPTR );
	};
} // namespace Model
