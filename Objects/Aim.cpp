#include "Aim.h"

#include <QWindow>
#include <math.h>
//-------------------------------------------------------------------------------------------------
Aim::Aim(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, int iAmplidude):
  Object(iID, dStartX, dStartY, iWidth, iHeight, dV0),
  _iAmplitude(iAmplidude),
  _bIsHit(false)
{
  _enType = Const::EnAim;
}
//-------------------------------------------------------------------------------------------------
void Aim::slotUpdateCoord()
{
  Object::slotUpdateCoord();
  double dAttenuationCoeff = 0.05;

  if (!_bIsHit) { // Двжиение
    _oCurCoord.first = _oStartCoord.first - _dV0 * _dCurTime;
    _oCurCoord.second = _oStartCoord.second + _iAmplitude * sin(dAttenuationCoeff * _oCurCoord.first);
  }
  else { // Падение
    _oCurCoord.first += 5 * sin(50 * _dCurTime) ;
    _oCurCoord.second += dAttenuationCoeff * _cdCoeffG * pow(_dCurTime, 2);
  }
  emit sigSendCurrentCoord(_iID, _oCurCoord.first, _oCurCoord.second);
}
//-------------------------------------------------------------------------------------------------
