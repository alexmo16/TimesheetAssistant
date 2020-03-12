#include "AboutDialog.h"

#include <QDialog>
#include <QWidget>

namespace View
{
	AboutDialog::AboutDialog( QWidget* pParent_ ) : QDialog( pParent_ )
	{
		m_ui.setupUi( this );
		setWindowFlag( Qt::WindowContextHelpButtonHint, false );
	}
} // namespace View
