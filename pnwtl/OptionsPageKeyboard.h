/**
 * @file optionspagekeyboard.h
 * @brief Options Dialog Keyboard Page for Programmers Notepad 2
 * @author Simon Steele
 * @note Copyright (c) 2006 Simon Steele <s.steele@pnotepad.org>
 *
 * Programmers Notepad 2 : The license file (license.[txt|html]) describes 
 * the conditions under which this source may be modified / distributed.
 */
#ifndef optionspagekeyboard_h__included
#define optionspagekeyboard_h__included

#include "include/optionsdialog.h"

typedef enum { cdtCommand, cdtExtended } CommandDetailsType;

typedef struct CommandDetails_tag
{
	CommandDetailsType type;
	int command;
} CommandDetails;

typedef struct ExtendedCommandDetails_tag : CommandDetails
{
	tstring group;
	tstring name;
} ExtendedCommandDetails;

class COptionsPageKeyboard : public COptionsPageImpl<COptionsPageKeyboard>,
								public CWinDataExchange<COptionsPageKeyboard>
{
	public:
		COptionsPageKeyboard(CommandDispatch* dispatcher);
		~COptionsPageKeyboard();

		BEGIN_MSG_MAP(COptionsPageKeyboard)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
			
			COMMAND_HANDLER(IDC_KB_ADD, BN_CLICKED, OnAddClicked)
			COMMAND_HANDLER(IDC_KB_REMOVE, BN_CLICKED, OnRemoveClicked)
			COMMAND_HANDLER(IDC_KB_HOTKEY, EN_CHANGE, OnHotKeyChanged)
			COMMAND_HANDLER(IDC_KB_ASSIGNEDLIST, LBN_SELCHANGE, OnKeySelChanged)

			NOTIFY_HANDLER(IDC_KB_COMMANDS, LVN_ITEMCHANGED, OnListItemChanged)
			
			REFLECT_NOTIFICATIONS()
		END_MSG_MAP()
		enum { IDD = IDD_PAGE_KEYBOARD };

		BEGIN_DDX_MAP(COptionsPageKeyboard)
			
		END_DDX_MAP()

		virtual void OnOK();
		virtual void OnInitialise();
		virtual LPCTSTR GetTreePosition();
		virtual void OnCancel();
		
		bool IsDirty() const;

	protected:
		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

		LRESULT OnAddClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnRemoveClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnHotKeyChanged(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnListItemChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);
		LRESULT OnKeySelChanged(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

		int addItems(CSMenuHandle& menu, const char* group, int count = 0);
		void addExtensions();
		void clear();
		void enableButtons();
		std::string findCommandName(DWORD command);
		std::string findCommandName(const std::string& extcommand);
		void updateSelection();
		void showCommandSelection(CommandDetails* command);
		void showExtendedSelection(ExtendedCommandDetails* command);
		void cleanUp();
		bool currentIsExtended();

		CommandDetails* m_pCurrent;
		KeyMap*			m_pKeyMap;
		CommandDispatch*m_pDispatch;
		CListViewCtrl	m_list;
		CListBox		m_shortcutlist;
		CHotKeyCtrl		m_hotkey;
		bool			m_bDirty;
};

#endif