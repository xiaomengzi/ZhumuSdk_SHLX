//////////////////////////////////////////////////////////////////////////
//  Plog - portable and simple log for C++
//  Documentation and sources: https://github.com/SergiusTheBest/plog
//  License: MPL 2.0, http://mozilla.org/MPL/2.0/

#pragma once
#include <plog/Logger.h>
#include <plog/Init.h>
namespace plog
{
	//////////////////////////////////////////////////////////////////////////
	// Helper macros that get context info

#if defined(_MSC_VER) && _MSC_VER >= 1600 && !defined(__INTELLISENSE__) && !defined(__INTEL_COMPILER) // >= Visual Studio 2010, skip IntelliSense and Intel Compiler
#   define PLOG_GET_THIS()      __if_exists(this) { this } __if_not_exists(this) { 0 }
#else
#   define PLOG_GET_THIS()      0
#endif

#ifdef _MSC_VER
#   define PLOG_GET_FUNC()      __FUNCTION__
#elif defined(__BORLANDC__)
#   define PLOG_GET_FUNC()      __FUNC__
#else
#   define PLOG_GET_FUNC()      __PRETTY_FUNCTION__
#endif

#ifdef PLOG_CAPTURE_FILE
#   define PLOG_GET_FILE()      __FILE__
#else
#   define PLOG_GET_FILE()      ""
#endif

//////////////////////////////////////////////////////////////////////////
// Log severity level checker

#define IF_PLOG_(instance, severity)     if (!plog::get<instance>() || !plog::get<instance>()->checkSeverity(severity)) {;} else
#define IF_PLOG(severity)                IF_PLOG_(PLOG_DEFAULT_INSTANCE, severity)

//////////////////////////////////////////////////////////////////////////
// Main logging macros

#define PLOG_(instance, severity)        IF_PLOG_(instance, severity) (*plog::get<instance>()) += plog::Record(severity, PLOG_GET_FUNC(), __LINE__, PLOG_GET_FILE(), PLOG_GET_THIS())
#define PLOG_YSX(severity)                   PLOG_(PLOG_DEFAULT_INSTANCE, severity)

#define PLOG_VERBOSE                     PLOG_YSX(plog::verbose)
#define PLOG_DEBUG                       PLOG_YSX(plog::debug)
#define PLOG_INFO                        PLOG_YSX(plog::info)
#define PLOG_WARNING                     PLOG_YSX(plog::warning)
#define PLOG_ERROR                       PLOG_YSX(plog::error)
#define PLOG_FATAL                       PLOG_YSX(plog::fatal)
#define PLOG_NONE                        PLOG_YSX(plog::none)

#define LOG_VERBOSE_(instance)          PLOG_(instance, plog::verbose)
#define LOG_DEBUG_(instance)            PLOG_(instance, plog::debug)
#define LOG_INFO_(instance)             PLOG_(instance, plog::info)
#define LOG_WARNING_(instance)          PLOG_(instance, plog::warning)
#define LOG_ERROR_(instance)            PLOG_(instance, plog::error)
#define LOG_FATAL_(instance)            PLOG_(instance, plog::fatal)
#define LOG_NONE_(instance)             PLOG_(instance, plog::none)

#define LOGV                            PLOG_VERBOSE
#define LOGD                            PLOG_DEBUG
#define LOGI                            PLOG_INFO
#define LOGW                            PLOG_WARNING
#define LOGE                            PLOG_ERROR
#define LOGF                            PLOG_FATAL
#define LOGN                            PLOG_NONE

#define LOGV_(instance)                 LOG_VERBOSE_(instance)
#define LOGD_(instance)                 LOG_DEBUG_(instance)
#define LOGI_(instance)                 LOG_INFO_(instance)
#define LOGW_(instance)                 LOG_WARNING_(instance)
#define LOGE_(instance)                 LOG_ERROR_(instance)
#define LOGF_(instance)                 LOG_FATAL_(instance)
#define LOGN_(instance)                 LOG_NONE_(instance)

//////////////////////////////////////////////////////////////////////////
// Conditional logging macros

#define PLOG_IF_(instance, severity, condition)  if (!(condition)) {;} else PLOG_(instance, severity)
#define PLOG_IF_YSX(severity, condition)             PLOG_IF_(PLOG_DEFAULT_INSTANCE, severity, condition)

#define LOG_VERBOSE_IF(condition)               PLOG_IF_YSX(plog::verbose, condition)
#define LOG_DEBUG_IF(condition)                 PLOG_IF_YSX(plog::debug, condition)
#define LOG_INFO_IF(condition)                  PLOG_IF_YSX(plog::info, condition)
#define LOG_WARNING_IF(condition)               PLOG_IF_YSX(plog::warning, condition)
#define LOG_ERROR_IF(condition)                 PLOG_IF_YSX(plog::error, condition)
#define LOG_FATAL_IF(condition)                 PLOG_IF_YSX(plog::fatal, condition)
#define LOG_NONE_IF(condition)                  PLOG_IF_YSX(plog::none, condition)

#define LOG_VERBOSE_IF_(instance, condition)    PLOG_IF_(instance, plog::verbose, condition)
#define LOG_DEBUG_IF_(instance, condition)      PLOG_IF_(instance, plog::debug, condition)
#define LOG_INFO_IF_(instance, condition)       PLOG_IF_(instance, plog::info, condition)
#define LOG_WARNING_IF_(instance, condition)    PLOG_IF_(instance, plog::warning, condition)
#define LOG_ERROR_IF_(instance, condition)      PLOG_IF_(instance, plog::error, condition)
#define LOG_FATAL_IF_(instance, condition)      PLOG_IF_(instance, plog::fatal, condition)
#define LOG_NONE_IF_(instance, condition)       PLOG_IF_(instance, plog::none, condition)

#define LOGV_IF(condition)                      LOG_VERBOSE_IF(condition)
#define LOGD_IF(condition)                      LOG_DEBUG_IF(condition)
#define LOGI_IF(condition)                      LOG_INFO_IF(condition)
#define LOGW_IF(condition)                      LOG_WARNING_IF(condition)
#define LOGE_IF(condition)                      LOG_ERROR_IF(condition)
#define LOGF_IF(condition)                      LOG_FATAL_IF(condition)
#define LOGN_IF(condition)                      LOG_NONE_IF(condition)

#define LOGV_IF_(instance, condition)           LOG_VERBOSE_IF_(instance, condition)
#define LOGD_IF_(instance, condition)           LOG_DEBUG_IF_(instance, condition)
#define LOGI_IF_(instance, condition)           LOG_INFO_IF_(instance, condition)
#define LOGW_IF_(instance, condition)           LOG_WARNING_IF_(instance, condition)
#define LOGE_IF_(instance, condition)           LOG_ERROR_IF_(instance, condition)
#define LOGF_IF_(instance, condition)           LOG_FATAL_IF_(instance, condition)
#define LOGN_IF_(instance, condition)           LOG_NONE_IF_(instance, condition)
}