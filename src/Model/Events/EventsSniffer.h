#pragma once

#include "Event.h"

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

		bool Sniff( TEvents& events_ );

	private:
		const std::wstring m_channel; // Channel to listen.
		const std::wstring m_query;	  // Query to do on the channel.
	};
} // namespace Model
