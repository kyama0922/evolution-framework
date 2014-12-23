#ifndef __EVOLUTION_GAMEOBJECT_VERTEX_PROPERTY_H__
#define __EVOLUTION_GAMEOBJECT_VERTEX_PROPERTY_H__

#include "../evolution_gameobject_interface.h"

namespace EVOLUTION{
    namespace FRAMEWORK{
        namespace GAMEOBJECT{

            struct VERTEX_PROPERTY{
                enum _PROPERTY{
                    SINT,
                    SINT2,
                    SINT3,
                    SINT4,
                    UINT,
                    UINT2,
                    UINT3,
                    UINT4,
                    FLOAT,
                    FLOAT2,
                    FLOAT3,
                    FLOAT4,
                };
            };

            class IVertexProperty : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IVertexProperty);
            public:
                virtual u32 GetPropertyCount() = 0;
                virtual u32 GetPropertySize(u32 index) = 0;
                virtual u32 GetTotalSize() = 0;
            };

            class VertexProperty :public IVertexProperty{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                u32* mp_vertex_property;
                u32 m_property_count;
                u32 m_total_size;
                u32 GetSize(VERTEX_PROPERTY::_PROPERTY _property);
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                VertexProperty();
                ~VertexProperty();

                FrameworkResult::_RESULT Create(VERTEX_PROPERTY::_PROPERTY vertex_property[], u32 count_property);

                u32 GetPropertyCount();
                u32 GetPropertySize(u32 index);
                u32 GetTotalSize();
            };

        }
    }
}

#endif