#pragma once

#include <QObject>

#include <vector>

namespace Model
{
	class WorkDay;
	typedef std::vector<std::unique_ptr<WorkDay>> TWorkDays;

	class Timesheet : public QObject
	{
		Q_OBJECT

	public:
		Timesheet( TWorkDays workDays_, QObject* pParent_ = Q_NULLPTR );

	private:
		TWorkDays m_workDays;
	};

} // namespace Model
