#pragma once

#include <QObject>

#include <windows.h>
#include <winevt.h>

namespace Model
{
	class EventsSniffer : public QObject
	{
		Q_OBJECT

	public:
		EventsSniffer( QObject* pParent_ = Q_NULLPTR );

		bool Sniff();

	private:
		const std::wstring m_channel = L"Security";
		// Event 4800 of Security is "Locked" and 4801 is "Unlocked" [System[(EventID=4800 or EventID=4801)]]
		const std::wstring m_query = L"Event/System[(EventID=4800 or EventID=4801)]";

		const size_t m_arraySize = 10;
		const int m_queryTimeout = 1000; // 1 second; Set and use in place of INFINITE in EvtNext call
	};
} // namespace Model
