#ifndef MS_CCONFIGURATION_HH
#define MS_CCONFIGURATION_HH

#include <QDialog>
# include "stdint.h"

#define C_PREFERENCES_HIGHT 400
#define C_PREFERENCES_LENGTH 500

#define C_PREFERENCES_MARGIN 40

#define C_SIZE_SQUARE 20
#define C_POINT_SIZE C_SIZE_SQUARE / 2

#define C_MAX_SIZE_NUMBER 50
#define C_MAX_BOMB_NUMBER 20

class CConfiguration : public QObject
{
    Q_OBJECT
public:
    CConfiguration();

    void fnConfigure(QWidget *parent = nullptr);

    uint32_t fnGetNumberOfRow()const;
    uint32_t fnGetNumberOfColumn()const;
    uint32_t fnGetNumberOfMines()const;
    CConfiguration& operator=(const CConfiguration&);
private:
    void fnDump();
    uint32_t m_uiNumberOfRow;
    uint32_t m_uiNumberOfColumn;
    uint32_t m_uiNumberOfMines;
};

#endif // MS_CCONFIGURATION_HH
