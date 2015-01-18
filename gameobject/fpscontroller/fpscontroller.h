#ifndef __EVOLUTION_FPS_CONTROLLER_H__
#define __EVOLUTION_FPS_CONTROLLER_H__

#include "../evolution_gameobject_interface.h"

using namespace EVOLUTION::MATH;

namespace EVOLUTION{
    namespace FRAMEWORK{
        namespace GAMEOBJECT{
            class FPSController :public IFPSController{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                EVOLUTION::CORE::TIMER::IStopWatch* mp_stop_watch;

                f32 m_one_fps;
                s32 m_fps;
                f32 m_basetime;   //測定基準時間

                s32 m_count;      //フレーム数
                f32 m_framerate;  //フレームレート

                f32 m_oneframetime;
                f32 old_time;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                FPSController();
                ~FPSController();

                FrameworkResult::_RESULT Create(u32 fps);

                bool IsFrameCheck();

                f32 GetDeltaTime();
                f32 GetFPS(); 
                void SetFps(u32 fps);

            };
        }
    }
}

#endif //!__EVOLUTION_TEXTURE_MANAGER_H__