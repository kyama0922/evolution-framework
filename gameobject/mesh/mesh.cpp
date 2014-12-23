#include "../evolution_gameobject_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;

//IUnknown
u32 Mesh::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Mesh::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    //if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    //{
    //    *ppvObject = static_cast<IUnknown *>(this);
    //    this->AddRef();
    //}
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

u32 Mesh::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

Mesh::Mesh(){

}

Mesh::~Mesh(){
    EVOLUTION_RELEASE(this->mp_vertex_property);
    EVOLUTION_RELEASE(this->mp_vertex_buffer);
}

FrameworkResult::_RESULT Mesh::Create(EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command, IVertexProperty* vertex_property, void* vertex_buffer , u32 vertex_count){
    this->mp_vertex_property = vertex_property;
    this->mp_vertex_property->AddRef();

    if (EVOLUTION::FUNCTION::IsGraphicFailed(graphic_factory->CreateVertexBuffer(&this->mp_vertex_buffer, command, vertex_buffer, vertex_count, this->mp_vertex_property->GetTotalSize())))
    {
        return FrameworkResult::CREATE_FAILED;
    }
    return FrameworkResult::RESULT_OK;
}

FrameworkResult::_RESULT Mesh::Create(EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command, const u16* index_buffer, u32 vertex_count){
    if (EVOLUTION_FAILED(graphic_factory->CreateIndexBuffer(&this->mp_index_buffer, command, index_buffer, vertex_count)))
    {
        return FrameworkResult::CREATE_FAILED;
    }
    return FrameworkResult::RESULT_OK;
}

FrameworkResult::_RESULT Mesh::Create(EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command, const u32* index_buffer, u32 vertex_count){
    if (EVOLUTION_FAILED(graphic_factory->CreateIndexBuffer(&this->mp_index_buffer, command, index_buffer, vertex_count)))
    {
        return FrameworkResult::CREATE_FAILED;
    }
    return FrameworkResult::RESULT_OK;
}

void Mesh::GetVertexProperty(IVertexProperty** vertex_property){
    *vertex_property = this->mp_vertex_property;
    this->mp_vertex_property->AddRef();
}
void Mesh::GetVertexBuffer(EVOLUTION::GRAPHIC::IBuffer** vertex_buffer){
    this->mp_vertex_buffer->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IBuffer, (void**)vertex_buffer);
}

void Mesh::GetIndexBuffer(EVOLUTION::GRAPHIC::IBuffer** index_buffer){
    this->mp_index_buffer->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_IBuffer, (void**)index_buffer);
}