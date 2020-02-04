// Copyright (c) 2020 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=4765074e73b5685fdd8274c0e86fd15e1e3aaa28$
//

#include "libcef_dll/ctocpp/cookie_manager_ctocpp.h"
#include "libcef_dll/cpptoc/completion_callback_cpptoc.h"
#include "libcef_dll/cpptoc/cookie_visitor_cpptoc.h"
#include "libcef_dll/cpptoc/delete_cookies_callback_cpptoc.h"
#include "libcef_dll/cpptoc/set_cookie_callback_cpptoc.h"
#include "libcef_dll/transfer_util.h"

// STATIC METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
CefRefPtr<CefCookieManager> CefCookieManager::GetGlobalManager(
    CefRefPtr<CefCompletionCallback> callback) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: callback

  // Execute
  cef_cookie_manager_t* _retval = cef_cookie_manager_get_global_manager(
      CefCompletionCallbackCppToC::Wrap(callback));

  // Return type: refptr_same
  return CefCookieManagerCToCpp::Wrap(_retval);
}

// VIRTUAL METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
void CefCookieManagerCToCpp::SetSupportedSchemes(
    const std::vector<CefString>& schemes,
    bool include_defaults,
    CefRefPtr<CefCompletionCallback> callback) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_supported_schemes))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: callback

  // Translate param: schemes; type: string_vec_byref_const
  cef_string_list_t schemesList = cef_string_list_alloc();
  DCHECK(schemesList);
  if (schemesList)
    transfer_string_list_contents(schemes, schemesList);

  // Execute
  _struct->set_supported_schemes(_struct, schemesList, include_defaults,
                                 CefCompletionCallbackCppToC::Wrap(callback));

  // Restore param:schemes; type: string_vec_byref_const
  if (schemesList)
    cef_string_list_free(schemesList);
}

NO_SANITIZE("cfi-icall")
bool CefCookieManagerCToCpp::VisitAllCookies(
    CefRefPtr<CefCookieVisitor> visitor) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, visit_all_cookies))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor.get());
  if (!visitor.get())
    return false;

  // Execute
  int _retval = _struct->visit_all_cookies(
      _struct, CefCookieVisitorCppToC::Wrap(visitor));

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
bool CefCookieManagerCToCpp::VisitUrlCookies(
    const CefString& url,
    bool includeHttpOnly,
    CefRefPtr<CefCookieVisitor> visitor) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, visit_url_cookies))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return false;
  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor.get());
  if (!visitor.get())
    return false;

  // Execute
  int _retval =
      _struct->visit_url_cookies(_struct, url.GetStruct(), includeHttpOnly,
                                 CefCookieVisitorCppToC::Wrap(visitor));

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
bool CefCookieManagerCToCpp::SetCookie(
    const CefString& url,
    const CefCookie& cookie,
    CefRefPtr<CefSetCookieCallback> callback) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_cookie))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return false;
  // Unverified params: callback

  // Execute
  int _retval = _struct->set_cookie(_struct, url.GetStruct(), &cookie,
                                    CefSetCookieCallbackCppToC::Wrap(callback));

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
bool CefCookieManagerCToCpp::DeleteCookies(
    const CefString& url,
    const CefString& cookie_name,
    CefRefPtr<CefDeleteCookiesCallback> callback) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, delete_cookies))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: url, cookie_name, callback

  // Execute
  int _retval =
      _struct->delete_cookies(_struct, url.GetStruct(), cookie_name.GetStruct(),
                              CefDeleteCookiesCallbackCppToC::Wrap(callback));

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
bool CefCookieManagerCToCpp::FlushStore(
    CefRefPtr<CefCompletionCallback> callback) {
  cef_cookie_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, flush_store))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: callback

  // Execute
  int _retval = _struct->flush_store(
      _struct, CefCompletionCallbackCppToC::Wrap(callback));

  // Return type: bool
  return _retval ? true : false;
}

// CONSTRUCTOR - Do not edit by hand.

CefCookieManagerCToCpp::CefCookieManagerCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

CefCookieManagerCToCpp::~CefCookieManagerCToCpp() {}

template <>
cef_cookie_manager_t*
CefCToCppRefCounted<CefCookieManagerCToCpp,
                    CefCookieManager,
                    cef_cookie_manager_t>::UnwrapDerived(CefWrapperType type,
                                                         CefCookieManager* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

template <>
CefWrapperType CefCToCppRefCounted<CefCookieManagerCToCpp,
                                   CefCookieManager,
                                   cef_cookie_manager_t>::kWrapperType =
    WT_COOKIE_MANAGER;
