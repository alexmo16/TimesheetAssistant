#include "SettingsDialog.h"

#include "Model/Config/Config.h"

#include <QSharedPointer>
#include <QWidget>

namespace View
{
	SettingsDialog::SettingsDialog( QSharedPointer<Model::Config> pConfig_, QWidget* pParent_ )
		: m_pConfig( pConfig_ ), QDialog( pParent_ )
	{
		m_ui.setupUi( this );
		setWindowFlag( Qt::WindowContextHelpButtonHint, false );
		m_ui.restartWarningLabel->hide();

		m_ui.logoffCheckBox->setChecked( m_pConfig->get( Model::Config::Keys::LOGOFF_ACTIVATED ).toBool() );
		connect( m_ui.logoffCheckBox, &QCheckBox::clicked,
			[ this ]( bool /*state_*/ ) { onLogoffChanged( *m_ui.logoffCheckBox ); } );

		m_ui.logonCheckBox->setChecked( m_pConfig->get( Model::Config::Keys::LOGON_ACTIVATED ).toBool() );
		connect( m_ui.logonCheckBox, &QCheckBox::clicked,
			[ this ]( bool /*state_*/ ) { onLogonChanged( *m_ui.logonCheckBox ); } );

		m_ui.lockedCheckBox->setChecked( m_pConfig->get( Model::Config::Keys::LOCKED_ACTIVATED ).toBool() );
		connect( m_ui.lockedCheckBox, &QCheckBox::clicked,
			[ this ]( bool /*state_*/ ) { onLockedChanged( *m_ui.lockedCheckBox ); } );

		m_ui.unlockedCheckBox->setChecked( m_pConfig->get( Model::Config::Keys::UNLOCKED_ACTIVATED ).toBool() );
		connect( m_ui.unlockedCheckBox, &QCheckBox::clicked,
			[ this ]( bool /*state_*/ ) { onUnlockedChanged( *m_ui.unlockedCheckBox ); } );
	}

	void SettingsDialog::onLogonChanged( const QCheckBox& checkbox_ )
	{
		m_ui.restartWarningLabel->show();
		m_pConfig->set( Model::Config::Keys::LOGON_ACTIVATED, checkbox_.isChecked() );
	}

	void SettingsDialog::onLogoffChanged( const QCheckBox& checkbox_ )
	{
		m_ui.restartWarningLabel->show();
		m_pConfig->set( Model::Config::Keys::LOGOFF_ACTIVATED, checkbox_.isChecked() );
	}

	void SettingsDialog::onLockedChanged( const QCheckBox& checkbox_ )
	{
		m_ui.restartWarningLabel->show();
		m_pConfig->set( Model::Config::Keys::LOCKED_ACTIVATED, checkbox_.isChecked() );
	}

	void SettingsDialog::onUnlockedChanged( const QCheckBox& checkbox_ )
	{
		m_ui.restartWarningLabel->show();
		m_pConfig->set( Model::Config::Keys::UNLOCKED_ACTIVATED, checkbox_.isChecked() );
	}
} // namespace View
