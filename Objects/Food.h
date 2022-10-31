#ifndef FOOD_H
#define FOOD_H
//-------------------------------------------------------------------------------------------------
#include "Object.h"
//-------------------------------------------------------------------------------------------------
/** Класс модели еды */
class Food : public Object
{
public:

  /** Конструктор */
  Food(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0);

protected slots:

  /** Расчет координат на текущий момент времени */
  void vUpdateCoord() override;

};
//-------------------------------------------------------------------------------------------------
#endif // FOOD_H
