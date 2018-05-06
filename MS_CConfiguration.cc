#include "MS_CConfiguration.hh"
#include "MS_Traces.hh"
#include <QPushButton>

CConfiguration::CConfiguration()
{
    // Default values
    m_uiNumberOfRow = 10;
    m_uiNumberOfColumn = 12;
    m_uiNumberOfMines = 20;
    fnDump();
}


void CConfiguration::fnConfigure(QWidget *parent)
{
    trace_debug("Configuation");
    // TODO

    fnDump();
}

CConfiguration& CConfiguration::operator=(const CConfiguration& roConf)
{
    // We just need to copy the members values
    m_uiNumberOfRow = roConf.fnGetNumberOfRow();
    m_uiNumberOfColumn = roConf.fnGetNumberOfColumn();
    m_uiNumberOfMines = roConf.fnGetNumberOfMines();
    return *this;
}

void CConfiguration::fnDump()
{
    trace_debug("Number Of Row    : " << m_uiNumberOfRow);
    trace_debug("Number Of Column : " << m_uiNumberOfColumn);
    trace_debug("Number Of Mines : " << m_uiNumberOfMines);
}

uint32_t CConfiguration::fnGetNumberOfRow() const
{
    return m_uiNumberOfRow;
}

uint32_t CConfiguration::fnGetNumberOfColumn() const
{
    return m_uiNumberOfColumn;
}

uint32_t CConfiguration::fnGetNumberOfMines() const
{
    return m_uiNumberOfMines;
}
