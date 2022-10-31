#include "Weapon.h"

#include <math.h>
//-------------------------------------------------------------------------------------------------
Weapon::Weapon(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, double dAlpha0):
  Object(iID, dStartX, dStartY, iWidth, iHeight, dV0)
{
  _enType = Const::EnWeapon;
  _dAlpha0 = dAlpha0;
}
//-------------------------------------------------------------------------------------------------
void Weapon::vUpdateCoord()
{
  Object::vUpdateCoord();

  // Бросание под углом к горизонту
  _oCurCoord.first = _oStartCoord.first + _dV0 * cos(_dAlpha0) * _dCurTime;
  _oCurCoord.second = _oStartCoord.second - _dV0 * sin(_dAlpha0) * _dCurTime + 0.5 * _cdCoeffG * pow(_dCurTime, 2);
}
//-------------------------------------------------------------------------------------------------
