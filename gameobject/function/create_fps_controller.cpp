#include "../evolution_gameobject_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;

//FPSControllerの作成
FRAMEWORK::FrameworkResult::_RESULT EVOLUTION::FUNCTION::CreateFpsController(FRAMEWORK::GAMEOBJECT::IFPSController** pp_fps_controller, u32 fps){
    *pp_fps_controller = nullptr;
    FPSController* fps_controller = NEW FPSController();
    FrameworkResult::_RESULT ret = fps_controller->Create(fps);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(fps_controller);
    }
    *pp_fps_controller = fps_controller;
    return  ret;
}