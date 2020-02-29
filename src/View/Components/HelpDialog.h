#pragma once

#include "ui_HelpDialog.h"

#include <QDialog>
#include <QWidget>

namespace View
{
	class HelpDialog : public QDialog
	{
		Q_OBJECT

	public:
		HelpDialog( QWidget* pParent_ = Q_NULLPTR );

	private:
		Ui::HelpDialog m_ui;
	};

} // namespace View
