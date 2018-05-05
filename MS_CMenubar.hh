#ifndef MS_CMENUBAR_HH
#define MS_CMENUBAR_HH

#include <QWidget>
#include <QMenuBar>
#include <QAction>

enum EMenuBarPossibility
{
    ENewGame=0,
    EPreferences,
    EHelp,
    EMaxMenuBarPossibility
};

class CMenuBar: public QMenuBar
{
    Q_OBJECT
public:
    CMenuBar(QWidget *parent = nullptr);
    ~CMenuBar();

signals:
    void SigOutMenuBar(EMenuBarPossibility);

private slots:
    void SfnNewGame();
    void SfnPreferences();
    void SfnHelp();

private:
    void fnCreateActions();
    void fnCreateMenus();

    QMenu * m_pQMenuFile;
    QMenu * m_pQMenuHelp;
    QAction* m_pQActionVector [EMaxMenuBarPossibility];
};

#endif // MS_CMENUBAR_HH
