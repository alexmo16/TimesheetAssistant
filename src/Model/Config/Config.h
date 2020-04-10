#pragma once

#include <QObject>
#include <QSettings>

namespace Model
{
	class Config : public QObject
	{
		Q_OBJECT

	public:
		Config( std::unique_ptr<QSettings> pSettings_, QObject* pParent_ = Q_NULLPTR );
		~Config() = default;

		enum class Keys
		{
			UNLOCKED_ACTIVATED,
			LOCKED_ACTIVATED,
			LOGON_ACTIVATED,
			LOGOFF_ACTIVATED,
		};
		Q_ENUM( Keys )

		void set( Keys key_, const QVariant& value_ );
		QVariant get( Keys key_ ) const;

	private:
		std::unique_ptr<QSettings> m_pSettings;
	};

	void loadDefault( Config& config_ );
} // namespace Model
