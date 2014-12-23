#ifndef __EVOLUTION_TEXTURE_MANAGER_H__
#define __EVOLUTION_TEXTURE_MANAGER_H__

#include "../evolution_gameobject_interface.h"

using namespace EVOLUTION::MATH;

namespace EVOLUTION{
    namespace FRAMEWORK{
        namespace GAMEOBJECT{
            class TextureManager :public IUnknown{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                struct Container{
                    s32 m_id;
                    EVOLUTION::GRAPHIC::ITexture* mp_texture;
                };
                Container* mp_container;
                s32 m_max_count;
                s32 m_use_count;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                TextureManager();
                ~TextureManager();

                FrameworkResult::_RESULT Create(u32 texture_container_count);
            };
        }
    }
}

#endif //!__EVOLUTION_TEXTURE_MANAGER_H__