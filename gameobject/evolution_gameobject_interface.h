#ifndef __EVOLUTION_GAMEOBJECT_INTERFACE_H__
#define __EVOLUTION_GAMEOBJECT_INTERFACE_H__

#include <evolution.h>
#include <evolution-graphic/evolution_graphic.h>

#include "../evolution_framework_result.h"

namespace EVOLUTION{
    namespace FRAMEWORK{
        namespace GAMEOBJECT{

            class IVertexProperty;
            class IMesh :public  IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IMesh);
            public:
                virtual void GetVertexProperty(IVertexProperty** vertex_property) = 0;
                virtual void GetVertexBuffer(EVOLUTION::GRAPHIC::IBuffer** buffer) = 0;
                virtual void GetIndexBuffer(EVOLUTION::GRAPHIC::IBuffer** index_buffer) = 0;
            };

        }
    }

    namespace FUNCTION{
        //ボックスの作成
        extern FRAMEWORK::FrameworkResult::_RESULT CreateBox(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, u32 width, u32 height, u32 depth, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command);
        //プレートの作成
        extern FRAMEWORK::FrameworkResult::_RESULT CreatePlate(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, f32 w, u32 h, u32 d, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command);
        //スフィアの作成
        extern FRAMEWORK::FrameworkResult::_RESULT CreateSphere(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, f32 Radius, u32 Slices, u32 Stacks, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command);

    }
}

#endif