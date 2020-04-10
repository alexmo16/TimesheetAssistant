#include "Config.h"

namespace Model
{
	Config::Config( std::unique_ptr<QSettings> pSettings_, QObject* pParent_ )
		: m_pSettings( std::move( pSettings_ ) ), QObject( pParent_ )
	{
		m_pSettings->sync();
	}

	void Config::set( Keys key_, const QVariant& value_ )
	{
		m_pSettings->setValue( QVariant::fromValue( key_ ).toString(), value_ );
	}

	QVariant Config::get( Keys key_ ) const
	{
		return m_pSettings->value( QVariant::fromValue( key_ ).toString() );
	}

	void loadDefault( Config& config_ )
	{
		config_.set( Config::Keys::LOCKED_ACTIVATED, true );
		config_.set( Config::Keys::UNLOCKED_ACTIVATED, true );
		config_.set( Config::Keys::LOGON_ACTIVATED, true );
		config_.set( Config::Keys::LOGOFF_ACTIVATED, true );
	}
} // namespace Model
