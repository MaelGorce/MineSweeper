#ifndef MS_TRACES_HH
#define MS_TRACES_HH

#include <QDebug>

typedef enum ETraceLevelE
{
    E_TRACE_ERROR = 0,
    E_TRACE_WARNING,
    E_TRACE_INFO,
    E_TRACE_DEBUG,
} ETraceLevel;

static ETraceLevel g_eTraceLevel = E_TRACE_DEBUG;
#define trace_error( fmt  )  if (g_eTraceLevel >= E_TRACE_ERROR)     {qDebug() << "(*) error   | "<<__FILE__<<" : "<<__FUNCTION__<<"( l."<<__LINE__<<") ~"<<fmt;}
#define trace_warning(fmt )  if (g_eTraceLevel >= E_TRACE_WARNING)   {qDebug() << "($) warning | "<<__FILE__<<" : "<<__FUNCTION__<<"( l."<<__LINE__<<") ~"<<fmt;}
#define trace_info(fmt    )  if (g_eTraceLevel >= E_TRACE_INFO)      {qDebug() << "(!) info    | "<<__FILE__<<" : "<<__FUNCTION__<<"( l."<<__LINE__<<") ~"<<fmt;}
#define trace_debug(fmt   )  if (g_eTraceLevel >= E_TRACE_DEBUG)     {qDebug() << "(#) debug   | "<<__FILE__<<" : "<<__FUNCTION__<<"( l."<<__LINE__<<") ~"<<fmt;}

#endif // MS_TRACES_HH
