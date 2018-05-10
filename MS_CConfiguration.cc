#include "MS_CConfiguration.hh"
#include "MS_Traces.hh"
#include <QMessageBox>
#include <QLayout>

CConfiguration::CConfiguration()
{
    // Default values
    SlotEasySelected();

    fnUpdateConfiguration();

    fnDump();
}

void CConfiguration::SlotEasySelected()
{
    trace_info("Easy configuration selected");
    m_eLastConfigurationSelected = EEasy;
    m_uiNewNumberOfRow = 8;
    m_uiNewNumberOfColumn = 8;
    m_uiNewNumberOfMines = 10;
}

void CConfiguration::SlotIntermediateSelected()
{
    trace_info("Intermediate configuration selected");
    m_eLastConfigurationSelected = EIntermediate;
    m_uiNewNumberOfRow = 16;
    m_uiNewNumberOfColumn = 16;
    m_uiNewNumberOfMines = 40;
}

void CConfiguration::SlotExpertSelected()
{
    trace_info("Expert configuration selected");
    m_eLastConfigurationSelected = EExpert;
    m_uiNewNumberOfRow = 16;
    m_uiNewNumberOfColumn = 32;
    m_uiNewNumberOfMines = 99;
}

int CConfiguration::fnConfigure(QWidget *parent)
{
    int iReturnedExec = 0;
    uint32_t uiHorizontalOffset = C_PREFERENCES_MARGIN;
    trace_debug("Configuation");
    // Opening a Message Box to choose preferences
    Qt::WindowFlags oFlag = Qt::Dialog;//Qt::Dialog | Qt::WindowType_Mask;
    QMessageBox *poQPreferencesBox = new QMessageBox(QMessageBox::NoIcon,
                                              "Preferences",
                                              "",
                                              QMessageBox::Cancel | QMessageBox::Apply,
                                              parent,
                                              Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    // Adding the Easy / Intermediate / Expert Buttons
    CConfigurationButon * poConfigurationButtonTab[EMaxConfigurationPossibility];
    poConfigurationButtonTab[EEasy] = new CConfigurationButon("Easy",uiHorizontalOffset,poQPreferencesBox);
    uiHorizontalOffset += C_PREFERENCES_MARGIN + poConfigurationButtonTab[EEasy]->width();
    poConfigurationButtonTab[EIntermediate] = new CConfigurationButon("Intermediate",uiHorizontalOffset,poQPreferencesBox);
    uiHorizontalOffset += C_PREFERENCES_MARGIN + poConfigurationButtonTab[EIntermediate]->width();
    poConfigurationButtonTab[EExpert] = new CConfigurationButon("Expert",uiHorizontalOffset,poQPreferencesBox);
    uiHorizontalOffset += C_PREFERENCES_MARGIN + poConfigurationButtonTab[EExpert]->width();

    // FIXME : can't resize the QMessageBox so i tricked the size with the text ...
    poQPreferencesBox->setText("                                                                         ");

    /* should be something like this :
    poQPreferencesBox->setFixedWidth(uiHorizontalOffset);
    trace_debug("Preferences window width : " << poQPreferencesBox->width());
    */

    int iIt,iJt;
    // connecting buttons so only one button is selected at the time
    for (iIt = 0; iIt < EMaxConfigurationPossibility; ++iIt)
    {
        for (iJt = 0; iJt < EMaxConfigurationPossibility; ++iJt)
        {
            if(iIt != iJt)
            {
                QObject::connect(poConfigurationButtonTab[iIt], SIGNAL(SigSelected()), poConfigurationButtonTab[iJt], SLOT(fnOtherSelected()));
            }
        }
    }

    // connecting buttons to configuration
    QObject::connect(poConfigurationButtonTab[EEasy], SIGNAL(SigSelected()), this, SLOT(SlotEasySelected()));
    QObject::connect(poConfigurationButtonTab[EIntermediate], SIGNAL(SigSelected()), this, SLOT(SlotIntermediateSelected()));
    QObject::connect(poConfigurationButtonTab[EExpert], SIGNAL(SigSelected()), this, SLOT(SlotExpertSelected()));

    // Selected by default : the last selected
    poConfigurationButtonTab[m_eLastConfigurationSelected]->fnSetIsSelected(true);

    iReturnedExec = poQPreferencesBox->exec();

    for (iIt = 0; iIt < EMaxConfigurationPossibility; ++iIt)
    {
        delete poConfigurationButtonTab[iIt];
    }
    delete poQPreferencesBox;

    fnDump();

    return iReturnedExec;
}

void CConfiguration::fnDump()
{
    trace_debug("Number Of Row    : " << m_uiNumberOfRow);
    trace_debug("Number Of Column : " << m_uiNumberOfColumn);
    trace_debug("Number Of Mines : " << m_uiNumberOfMines);
}

void CConfiguration::fnUpdateConfiguration()
{
    m_uiNumberOfRow = m_uiNewNumberOfRow;
    m_uiNumberOfColumn = m_uiNewNumberOfColumn;
    m_uiNumberOfMines = m_uiNewNumberOfMines;
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


CConfigurationButon::CConfigurationButon(const QString &text, uint32_t uiHorizontalOffset, QWidget *parent): QPushButton(text,parent),
    m_bIsSelected(false)
{
    trace_debug("Construction of " << text << " configuration button");
    this->move(QPoint(uiHorizontalOffset,C_PREFERENCES_MARGIN));
    this->setCheckable(true);
    this->setCursor(Qt::PointingHandCursor);


    QObject::connect(this, SIGNAL(clicked()), this, SLOT(SlotSelected()));
}

void CConfigurationButon::fnOtherSelected()
{
    m_bIsSelected = false;
    if (this->isChecked())
    {
        this->toggle();
    }
}

void CConfigurationButon::fnSetIsSelected(bool bIsSelected)
{
    if(this->isChecked() != bIsSelected)
    {
        this->toggle();
    }
    m_bIsSelected = bIsSelected;
}

void CConfigurationButon::SlotSelected()
{
    fnSetIsSelected(true);
    emit SigSelected();
}
