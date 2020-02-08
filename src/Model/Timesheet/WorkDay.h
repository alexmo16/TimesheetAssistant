#pragma once

#include <QObject>

namespace Model
{
	class WorkDay : public QObject
	{
		Q_OBJECT

	public:
		WorkDay( QObject* pParent_ = Q_NULLPTR );
	};

	typedef std::vector<std::unique_ptr<WorkDay>> TWorkDays;
} // namespace Model
