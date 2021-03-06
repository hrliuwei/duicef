// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "Common.h"

namespace {

SimpleHandler* g_instance = NULL;

// Returns a data: URI with the specified contents.
std::string GetDataURI(const std::string& data, const std::string& mime_type) {
  return "data:" + mime_type + ";base64," +
         CefURIEncode(CefBase64Encode(data.data(), data.size()), false)
             .ToString();
}

}  // namespace

SimpleHandler::SimpleHandler(CMaindlg* main_frame, bool use_views)
    : use_views_(use_views), is_closing_(false) {
  DCHECK(!g_instance);
  g_instance = this;
  m_pMainFrame = main_frame;
}

SimpleHandler::~SimpleHandler() {
  g_instance = NULL;
}

// static
SimpleHandler* SimpleHandler::GetInstance() {
  return g_instance;
}

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString& title) {
  CEF_REQUIRE_UI_THREAD();
  ::SendMessage(m_pMainFrame->GetHWND(), WM_TITLE_CHANGE, (WPARAM)browser->GetHost()->GetWindowHandle(), 
	  (LPARAM)std::wstring(title).c_str());
  //if (use_views_) {
  //  // Set the title of the window using the Views framework.
  //  CefRefPtr<CefBrowserView> browser_view =
  //      CefBrowserView::GetForBrowser(browser);
  //  if (browser_view) {
  //    CefRefPtr<CefWindow> window = browser_view->GetWindow();
  //    if (window)
  //      window->SetTitle(title);
  //  }
  //} else {
  //  // Set the title of the window using platform APIs.
  //  PlatformTitleChange(browser, title);
  //}
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  HWND hWnd = browser->GetHost()->GetWindowHandle();
  DWORD dwNewStyle = (::GetWindowLong(hWnd, GWL_STYLE)&~(WS_POPUP|WS_CAPTION|WS_BORDER|WS_SIZEBOX|WS_SYSMENU)|WS_CHILD);
  ::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
  if (m_pMainFrame) {
	  ::SetParent(hWnd, m_pMainFrame->GetHWND());
	  ::PostMessage(m_pMainFrame->GetHWND(), WM_CREATE_NEW_PAGE, (WPARAM)hWnd, 0);
  }
  // Add to the list of existing browsers.
  browser_list_.push_back(browser);
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Closing the main window requires special handling. See the DoClose()
  // documentation in the CEF header for a detailed destription of this
  // process.
  if (browser_list_.size() == 1) {
    // Set a flag to indicate that the window close should be allowed.
    is_closing_ = true;
  }

  // Allow the close. For windowed browsers this will result in the OS close
  // event being sent.
  return false;
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Remove from the list of existing browsers.
  BrowserList::iterator bit = browser_list_.begin();
  for (; bit != browser_list_.end(); ++bit) {
    if ((*bit)->IsSame(browser)) {
      browser_list_.erase(bit);
      break;
    }
  }

  if (browser_list_.empty()) {
    // All browser windows have closed. Quit the application message loop.
    CefQuitMessageLoop();
  }
}

void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                ErrorCode errorCode,
                                const CefString& errorText,
                                const CefString& failedUrl) {
  CEF_REQUIRE_UI_THREAD();

  // Don't display an error for downloaded files.
  if (errorCode == ERR_ABORTED)
    return;

  // Display a load error message using a data: URI.
  std::stringstream ss;
  ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
     << std::string(failedUrl) << " with error " << std::string(errorText)
     << " (" << errorCode << ").</h2></body></html>";

  frame->LoadURL(GetDataURI(ss.str(), "text/html"));
}

void SimpleHandler::CloseAllBrowsers(bool force_close) {
  if (!CefCurrentlyOn(TID_UI)) {
    // Execute on the UI thread.
    CefPostTask(TID_UI, base::Bind(&SimpleHandler::CloseAllBrowsers, this,
                                   force_close));
    return;
  }

  if (browser_list_.empty())
    return;

  BrowserList::const_iterator it = browser_list_.begin();
  for (; it != browser_list_.end(); ++it)
    (*it)->GetHost()->CloseBrowser(force_close);
}

void SimpleHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	CefRefPtr<CefMenuModel> model)
{
	CEF_REQUIRE_UI_THREAD();
	model->Clear();
}

bool SimpleHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool user_gesture,
	bool is_redirect) {
	CefString str = request->GetURL();
	std::wstring strUrl = str.ToWString();

	if (strUrl.find(L"tencent://") != std::wstring::npos)
	{
		//return true;
	}
	return false;
}

void SimpleHandler::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	bool& allow_os_execution)
{
	allow_os_execution = true;
	HWND hWnd = browser->GetHost()->GetWindowHandle();
	::SetWindowText(hWnd, L"企业客户服务");
}
