#pragma once

#include <QObject>
#include <QString>

namespace Model
{
	class Test : public QObject
	{
		Q_OBJECT

	public:
		Test( QObject* parent = Q_NULLPTR );

		QString GetHelloWorld_Test();
	};
} // namespace Model
