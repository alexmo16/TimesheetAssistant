#pragma once

#include <QObject>

namespace Model
{
	class TimesheetBuilder : public QObject
	{
		Q_OBJECT

	public:
		TimesheetBuilder( QObject* pParent_ = Q_NULLPTR );
	};
} // namespace Model
