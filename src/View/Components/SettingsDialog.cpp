#include "SettingsDialog.h"

#include <QWidget>

namespace View
{
	SettingsDialog::SettingsDialog( QSharedPointer<QSettings> pSettings_, QWidget* pParent_ )
		: QDialog( pParent_ ), m_pSettings( std::move( pSettings_ ) )
	{
		m_ui.setupUi( this );
		setWindowFlag( Qt::WindowContextHelpButtonHint, false );
	}
} // namespace View
