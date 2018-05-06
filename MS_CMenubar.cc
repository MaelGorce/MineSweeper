#include "MS_CMenubar.hh"
#include "MS_CConfiguration.hh"
#include "MS_Traces.hh"

CMenuBar::CMenuBar(QWidget *parent) : QMenuBar(parent),
  m_uiLenght(0)
{
    trace_debug("Construction of CMenuBar");

    fnCreateActions();
    fnCreateMenus();

    this->setMinimumWidth(m_uiLenght);

    trace_debug("End Construction of CMenuBar");
}

CMenuBar::~CMenuBar()
{
    trace_debug("Destruction of CMenuBar");

    uint8_t ucDestruction;
    for(ucDestruction=0; ucDestruction<EMaxMenuBarPossibility; ++ucDestruction)
    {
        delete m_pQActionVector[ucDestruction];
    }

    trace_debug("End Destruction of CMenuBar");
}

void CMenuBar::fnSetLength(uint32_t uiLenght)
{
    m_uiLenght = uiLenght;
    this->setMinimumWidth(m_uiLenght);
}

void CMenuBar::fnCreateActions()
{
    trace_debug("Creation of New Game Action");
    m_pQActionVector[ENewGame] = new QAction(tr("&NewGame"), this);
    m_pQActionVector[ENewGame]->setShortcuts(QKeySequence::New);
    connect(m_pQActionVector[ENewGame],&QAction::triggered, this,&CMenuBar::SfnNewGame);

    trace_debug("Creation of Preferences Action");
    m_pQActionVector[EPreferences] = new QAction(tr("&Preferences"), this);
    m_pQActionVector[EPreferences]->setShortcuts(QKeySequence::Preferences);
    connect(m_pQActionVector[EPreferences],&QAction::triggered, this,&CMenuBar::SfnPreferences);

    trace_debug("Creation of Help Action");
    m_pQActionVector[EHelp] = new QAction(tr("&Help"), this);
    m_pQActionVector[EHelp]->setShortcuts(QKeySequence::HelpContents);
    connect(m_pQActionVector[EHelp],&QAction::triggered, this,&CMenuBar::SfnHelp);
}

void CMenuBar::fnCreateMenus()
{
    trace_debug("Creation of the Menus");

    trace_debug("Creation of File Menu");
    m_pQMenuFile = this->addMenu(tr("&File"));
    m_pQMenuFile->addAction(m_pQActionVector[ENewGame]);
    m_pQMenuFile->addAction(m_pQActionVector[EPreferences]);

    trace_debug("Creation of Help Menu");
    m_pQMenuHelp = this->addMenu(tr("&Help"));
    m_pQMenuHelp->addAction(m_pQActionVector[EHelp]);
}

void CMenuBar::SfnNewGame()
{
    trace_info("New Game");
    emit SigOutMenuBar(ENewGame);
}

void CMenuBar::SfnPreferences()
{
    trace_info("Preferences");
    emit SigOutMenuBar(EPreferences);
}

void CMenuBar::SfnHelp()
{
    trace_info("Help");
    emit SigOutMenuBar(EHelp);
}
