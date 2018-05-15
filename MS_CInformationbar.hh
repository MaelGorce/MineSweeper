#ifndef MS_CINFORMATIONBAR_HH
#define MS_CINFORMATIONBAR_HH

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QTimer>

class CInformationBar : public QWidget
{
    Q_OBJECT
public:
    explicit CInformationBar(uint32_t uiVerticalOffset,QWidget *parent = nullptr);

    void fnSetLength(uint32_t uiLenght);

    int fnGetTimer();

signals:

public slots:
    void SlotSupposedMinesLeft(int iSupposedMinesLeft);
    void SlotResetTimer(bool bStartTimer);
    void SlotStopTimer();

private slots:
    void SlotAddOneSecond();

private:
    QLCDNumber *m_poLCDMinesLeft;
    QPushButton *m_poSmileyFace;
    QTimer *m_poTimer;
    int m_iNbSecondTimer;
    QLCDNumber *m_poLCDTime;
};

#endif // MS_CINFORMATIONBAR_HH
