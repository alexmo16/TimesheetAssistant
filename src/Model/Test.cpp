#include "Test.h"

namespace Model
{
	Test::Test( QObject* parent ) : QObject( parent ) {}

	QString Test::GetHelloWorld_Test()
	{
		return QString( "Hello World!" );
	}
} // namespace Model
