#ifndef MS_CCONFIGURATION_HH
#define MS_CCONFIGURATION_HH

#include <QPushButton>

#define C_PREFERENCES_MARGIN 10

#define C_SIZE_SQUARE 24
#define C_POINT_SIZE C_SIZE_SQUARE / 2
#define C_MAX_SIZE_NUMBER 32

#define C_INFO_BAR_HIGHT 50

enum EConfigurationPossibility
{
    EEasy=0,
    EIntermediate,
    EExpert,
    EMaxConfigurationPossibility
};

class CConfiguration : public QObject
{
    Q_OBJECT
public:
    CConfiguration();

    int fnConfigure(QWidget *parent = nullptr);
    void fnUpdateConfiguration();

    uint32_t fnGetNumberOfRow()const;
    uint32_t fnGetNumberOfColumn()const;
    uint32_t fnGetNumberOfMines()const;

private slots:
    void SlotEasySelected();
    void SlotIntermediateSelected();
    void SlotExpertSelected();

private:
    void fnDump();
    uint32_t m_uiNumberOfRow;
    uint32_t m_uiNumberOfColumn;
    uint32_t m_uiNumberOfMines;
    uint32_t m_uiNewNumberOfRow;
    uint32_t m_uiNewNumberOfColumn;
    uint32_t m_uiNewNumberOfMines;
    EConfigurationPossibility m_eLastConfigurationSelected;
};

class CConfigurationButon: public QPushButton
{
    Q_OBJECT
public:
    CConfigurationButon(const QString &text,uint32_t uiHorizontalOffset, QWidget *parent);
    void fnSetIsSelected(bool bIsSelected);

public slots:
    void fnOtherSelected();

private slots:
    void SlotSelected();

signals:
    void SigSelected();

private:

    bool m_bIsSelected;
};

#endif // MS_CCONFIGURATION_HH
