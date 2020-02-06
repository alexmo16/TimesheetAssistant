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
		EventsSniffer( const std::wstring& channel_, const std::wstring& query_, QObject* pParent_ = Q_NULLPTR );

		bool Sniff( std::vector<QString>& xmlEvents_ );

	private:
		const std::wstring m_channel; // Channel to listen.
		const std::wstring m_query;	  // Query to do on the channel.

		const size_t m_arraySize = 10;
		const int m_queryTimeout = 1000; // 1 second; Set and use in place of INFINITE in EvtNext call
	};
} // namespace Model
