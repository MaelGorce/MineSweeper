#include "MS_CInformationbar.hh"
#include "MS_CConfiguration.hh"
#include "MS_Traces.hh"

CInformationBar::CInformationBar(uint32_t uiVerticalOffset, QWidget *parent) : QWidget(parent)
{
    // Positioning the Inormation Bar
    this->move(0,uiVerticalOffset);
    this->setFixedHeight(C_INFO_BAR_HIGHT);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    // Creating The LCD displaying the number of supposed remaining mines
    m_poLCDMinesLeft = new QLCDNumber(2,this);
    m_poLCDMinesLeft->setFixedHeight(C_INFO_BAR_HIGHT);

    // Creating the smiley button in the middle of the Info bar
    //m_poSmileyFace = new QPushButton(":)",this);

    // Creating the timer
    m_poTimer = new QTimer(this);
    m_iNbSecondTimer = 0;
    m_poLCDTime = new QLCDNumber(4,this);
    m_poLCDTime->setFixedHeight(C_INFO_BAR_HIGHT);
    connect(m_poTimer, SIGNAL(timeout()), this, SLOT(SlotAddOneSecond()));

    //this->setCursor(Qt::ForbiddenCursor);
    this->show();
}

void CInformationBar::fnSetLength(uint32_t uiLenght)
{
    trace_debug("Setting Info bar Width to : "<< uiLenght)
    this->setFixedWidth(uiLenght);
    m_poLCDTime->move(uiLenght-m_poLCDTime->width(),0);
    m_poLCDTime->show();
    this->show();
}

int CInformationBar::fnGetTimer()
{
    return m_iNbSecondTimer;
}

void CInformationBar::SlotSupposedMinesLeft(int iSupposedMinesLeft)
{
    QPalette oPalette;
    trace_info("iSupposedMinesLeft" << iSupposedMinesLeft);
    m_poLCDMinesLeft->display(iSupposedMinesLeft);

    oPalette = this->palette();

    if (iSupposedMinesLeft < 0)
    {
        oPalette.setColor(QPalette::Light,Qt::red);
    }
    else if (iSupposedMinesLeft == 0)
    {
        oPalette.setColor(QPalette::Light,Qt::yellow);
    }
    else
    {
        oPalette.setColor(QPalette::Light,Qt::black);
    }
    m_poLCDMinesLeft->setPalette(oPalette);
}

void CInformationBar::SlotResetTimer()
{
    trace_debug("Resetting Timer");
    m_poLCDTime->display(0);
    m_iNbSecondTimer = 0;
    m_poTimer->stop();
    m_poTimer->start(1000);
}

void CInformationBar::SlotStopTimer()
{
    trace_debug("Stop Timer");
    m_poTimer->stop();
}

void CInformationBar::SlotAddOneSecond()
{
    m_poLCDTime->display(++m_iNbSecondTimer);
}
