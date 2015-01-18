#include "fpscontroller.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;



//IUnknown
u32 FPSController::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT FPSController::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    //else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_BlendStateProperty))
    //{
    //    *ppvObject = static_cast<BlendStateProperty *>(this);
    //    this->AddRef();
    //}
    //else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 FPSController::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

FPSController::FPSController() :m_one_fps(1.0f / 60.0f), m_fps(60), m_framerate(60.0f), m_basetime(0.0f), m_count(0), old_time(0.0f){

}
FPSController::~FPSController(){

}

FrameworkResult::_RESULT FPSController::Create(u32 fps){
    this->SetFps(fps);
    if (EVOLUTION_FAILED(EVOLUTION::FUNCTION::CreateStopWatch(&this->mp_stop_watch)))
    {
        return FrameworkResult::CREATE_FAILED;
    }
    this->mp_stop_watch->Start();
    return FrameworkResult::RESULT_OK;
}

bool FPSController::IsFrameCheck(){
    f32 now_time = (f32)this->mp_stop_watch->GetMilliSecondU32() * 0.001f;
    this->m_oneframetime = now_time - old_time;
    if (this->m_one_fps > this->m_oneframetime){
        return false;
    }
    //1フレームのタイマーのリセット
    this->m_count++;
    //現在の時間を取得
    old_time = now_time;

    this->m_framerate = (f32) this->m_count / (f32)(now_time - m_basetime);
    if (now_time - this->m_basetime >= 1.0f) {       //１秒以上経過していれば
        this->m_count = 0;          //フレーム数をリセット
        this->m_basetime = now_time;
    }
    return true;
}

f32 FPSController::GetDeltaTime(){
    return (f32)this->m_fps / this->m_framerate;
}

f32 FPSController::GetFPS(){
    return this->m_framerate;
}

void FPSController::SetFps(u32 fps){
    this->m_fps = fps;
    this->m_one_fps = 1.0f / (float)fps;
}