#include "SettingsDialog.h"

#include <QWidget>

namespace View
{
	SettingsDialog::SettingsDialog( QWidget* pParent_ ) : QDialog( pParent_ )
	{
		m_ui.setupUi( this );
		setWindowFlag( Qt::WindowContextHelpButtonHint, false );
	}
} // namespace View
