#include "MainWindow.h"

#include "Model/Test.h"

namespace View
{
	MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
	{
		ui.setupUi( this );

		Model::Test testObject;
		const auto& message = testObject.GetHelloWorld_Test();
		ui.testInput->setText( message );
	}
} // namespace View
