#include "HelpDialog.h"

namespace View
{
	HelpDialog::HelpDialog( QWidget* pParent_ ) : QDialog( pParent_ )
	{
		m_ui.setupUi( this );
		setWindowFlag( Qt::WindowContextHelpButtonHint, false );
	}

} // namespace View
