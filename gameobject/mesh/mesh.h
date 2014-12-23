#ifndef __EVOLUTION_GAMEOBJECT_MESH_H__
#define __EVOLUTION_GAMEOBJECT_MESH_H__

#include "../evolution_gameobject_interface.h"

using namespace EVOLUTION::MATH;

namespace EVOLUTION{
    namespace FRAMEWORK{
        namespace GAMEOBJECT{

            class Mesh :public IMesh{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                IVertexProperty* mp_vertex_property;
                EVOLUTION::GRAPHIC::IBuffer* mp_vertex_buffer;

                EVOLUTION::GRAPHIC::IBuffer* mp_index_buffer;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                Mesh();
                ~Mesh();

                FrameworkResult::_RESULT Create(EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command, IVertexProperty* vertex_property, void* vertex_buffer, u32 vertex_count);

                void GetVertexProperty(IVertexProperty** vertex_property);
                void GetVertexBuffer(EVOLUTION::GRAPHIC::IBuffer** vertex_buffer);
                void GetIndexBuffer(EVOLUTION::GRAPHIC::IBuffer** index_buffer);
            };
        }
    }
}

#endif