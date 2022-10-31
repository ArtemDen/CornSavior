#include "Food.h"

#include <math.h>
//-------------------------------------------------------------------------------------------------
Food::Food(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0):
  Object(iID, dStartX, dStartY, iWidth, iHeight, dV0)
{
  _enType = Const::EnFood;
}
//-------------------------------------------------------------------------------------------------
void Food::vUpdateCoord()
{
  Object::vUpdateCoord();

  // "Колебание"
  _oCurCoord.second = _oStartCoord.second + 0.25 * _oSize.second * sin(10 * _dCurTime) ;
}
//-------------------------------------------------------------------------------------------------
