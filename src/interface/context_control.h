#ifndef __CONTEXT_CONTROL_H__
#define __CONTEXT_CONTROL_H__

#include <wx/aui/auibook.h>
#include "state.h"

class wxAuiNotebookEx;
class CLocalListView;
class CLocalTreeView;
class CMainFrame;
class CRemoteListView;
class CRemoteTreeView;
class CView;
class CViewHeader;
class CSplitterWindowEx;
class CState;

class CContextControl : public wxSplitterWindow, public CStateEventHandler
{
public:
	struct _context_controls
	{
		// List of all windows and controls assorted with a context
		CView* pLocalTreeViewPanel;
		CView* pLocalListViewPanel;
		CLocalTreeView* pLocalTreeView;
		CLocalListView* pLocalListView;
		CView* pRemoteTreeViewPanel;
		CView* pRemoteListViewPanel;
		CRemoteTreeView* pRemoteTreeView;
		CRemoteListView* pRemoteListView;
		CViewHeader* pLocalViewHeader;
		CViewHeader* pRemoteViewHeader;
	
		CSplitterWindowEx* pViewSplitter; // Contains local and remote splitters
		CSplitterWindowEx* pLocalSplitter;
		CSplitterWindowEx* pRemoteSplitter;

		CState* pState;

		wxString title;

		int tab_index;

		struct _site_bookmarks
		{
			wxString path;
			std::list<wxString> bookmarks;
		};
		CSharedPointer<struct _site_bookmarks> site_bookmarks;
	};

	CContextControl(CMainFrame* pMainFrame, wxWindow* parent);
	virtual ~CContextControl();

	void CreateTab();
	bool CloseTab(int tab);

	struct _context_controls* GetControlsFromState(CState* pState);
	
	int GetCurrentTab() const;
	int GetTabCount() const;
	struct _context_controls* GetControlsFromTabIndex(int i);

	bool SelectTab(int i);

protected:
	
	void CreateContextControls(CState* pState);

public:
	std::vector<struct _context_controls> m_context_controls;
	size_t m_current_context_controls;

protected:
	wxAuiNotebookEx* m_tabs;
	int m_right_clicked_tab;
	CMainFrame* m_pMainFrame;

protected:
	DECLARE_EVENT_TABLE();
	void OnTabRefresh(wxCommandEvent& event);
	void OnTabChanged(wxAuiNotebookEvent& event);
	void OnTabClosing(wxAuiNotebookEvent& event);
	void OnTabClosing_Deferred(wxCommandEvent& event);
	void OnTabBgDoubleclick(wxAuiNotebookEvent& event);
	void OnTabRightclick(wxAuiNotebookEvent& event);
	void OnTabContextClose(wxCommandEvent& event);

	virtual void OnStateChange(CState* pState, enum t_statechange_notifications notification, const wxString& data, const void* data2);
};

#endif //__CONTEX_CONTROL_H__
