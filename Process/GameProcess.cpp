#include "GameProcess.h"
#include "Weapon.h"
#include "Aim.h"
#include "Food.h"
//-------------------------------------------------------------------------------------------------
GameProcess::GameProcess()
{

}
//-------------------------------------------------------------------------------------------------
GameProcess::~GameProcess()
{
  _vecObjects.clear();
}
//-------------------------------------------------------------------------------------------------
void GameProcess::vCreateObject(int iObjType, int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, double dParam)
{
  std::shared_ptr<Object> poObject;
  Const::EnObjType enObjType = static_cast<Const::EnObjType>(iObjType);

  switch(enObjType) {

    case Const::EnWeapon: {
      poObject = std::make_shared<Weapon>(iID, dStartX, dStartY, iWidth, iHeight, dV0, dParam);
      break;
    }

    case Const::EnAim: {
      poObject = std::make_shared<Aim>(iID, dStartX, dStartY, iWidth, iHeight, dV0, static_cast<int>(dParam));
      break;
    }

    case Const::EnFood: {
      poObject = std::make_shared<Food>(iID, dStartX, dStartY, iWidth, iHeight, dV0);
      break;
    }

    default:
      break;
  }

  if (poObject) {
    _vecObjects.push_back(poObject);
    connect(_vecObjects.back().get(), SIGNAL(sigSendCurrentCoord(int, double, double)), this, SLOT(slotCheckingCross(int, double, double)));
    connect(_vecObjects.back().get(), SIGNAL(sigSendCurrentCoord(int, double, double)), this, SIGNAL(sigSendCoordToQML(int, double, double)));
  }
}
//-------------------------------------------------------------------------------------------------
void GameProcess::vDeleteObject(int iID)
{
  // Поиск объекта в векторе
  auto predicate = [iID](const std::shared_ptr<Object>& poObject){
    return poObject->iGetID() == iID;
  };
  auto const& res = std::find_if(_vecObjects.begin(), _vecObjects.end(), predicate);

  // Удаление
  if (res != _vecObjects.end()) {
    disconnect(res->get(), SIGNAL(sigSendCurrentCoord(int, double, double)), this, SLOT(slotCheckingCross(int, double, double)));
    disconnect(res->get(), SIGNAL(sigSendCurrentCoord(int, double, double)), this, SIGNAL(sigSendCoordToQML(int, double, double)));
    _vecObjects.erase(res);
  }
}
//-------------------------------------------------------------------------------------------------
void GameProcess::slotCheckingCross(int ID,  double X, double Y)
{
  Q_UNUSED(X)
  Q_UNUSED(Y)

  // Поиск объекта в векторе
  auto predicate = [ID](const std::shared_ptr<Object>& poObject){
    return poObject->iGetID() == ID;
  };
  auto const& res = std::find_if(_vecObjects.begin(), _vecObjects.end(), predicate);

  // Проверка на пересечение с существующими орудиями
  if (res != _vecObjects.end() && res->get()->enGetType() == Const::EnAim) {

    std::shared_ptr<Aim> poAim = std::dynamic_pointer_cast<Aim>(*res);
    if (poAim && !poAim->bGetHitSign()) {
      for (const std::shared_ptr<Object>& croObject : _vecObjects) {
        if (croObject->enGetType() == Const::EnWeapon && bIsCrossing(*res, croObject)) { // Орудие попало в цель
          poAim->vSetHitSign(true);
          break;
        }
        else if (croObject->enGetType() == Const::EnFood && bIsCrossing(*res, croObject)) { // Цель съела еду
          emit sigFoodIsEaten(croObject->iGetID());
          break;
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------
bool GameProcess::bIsCrossing(const std::shared_ptr<Object>& croFirstObject, const std::shared_ptr<Object>& croSecondObject) const
{
  // Разность координат
  double dDiffX = croFirstObject.get()->croGetCoord().first - croSecondObject.get()->croGetCoord().first;
  double dDiffY = croFirstObject.get()->croGetCoord().second - croSecondObject.get()->croGetCoord().second;

  // Коэффициент учета неквадртаной формы
  const double cdCrossCoeff = 1.25;

  // Пересечение
  bool bIsCrossingLeft = (dDiffX < croSecondObject.get()->croGetSize().first / cdCrossCoeff);
  bool bIsCrossingRight = (dDiffX > -croFirstObject.get()->croGetSize().first / cdCrossCoeff);
  bool bIsCrossingUp = (dDiffY < croSecondObject.get()->croGetSize().second / cdCrossCoeff);
  bool bIsCrossingDown = (dDiffY > -croFirstObject.get()->croGetSize().second / cdCrossCoeff);

  return bIsCrossingLeft && bIsCrossingRight && bIsCrossingUp && bIsCrossingDown;
}
//-------------------------------------------------------------------------------------------------
