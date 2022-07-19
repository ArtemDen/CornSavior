#ifndef WEAPON_H
#define WEAPON_H
//-------------------------------------------------------------------------------------------------
#include "Object.h"
//-------------------------------------------------------------------------------------------------
/** Класс модели орудия */
class Weapon : public Object
{

public:

  /** Конструктор */
  Weapon(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, double dAlpha0);

protected slots:

  /** Расчет координат на текущий момент времени */
  void slotUpdateCoord() override;

private:

  /** Угол бросания, рад */
  double _dAlpha0;

};
//-------------------------------------------------------------------------------------------------
#endif // WEAPON_H
