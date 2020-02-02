#include "EventsSniffer.h"

#include <QObject>

#include <Windows.h>
#include <winevt.h>

namespace Model
{
	EventsSniffer::EventsSniffer( QObject* parent ) : QObject( parent ) {}

} // namespace Model
