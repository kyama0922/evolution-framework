#include "vertex_property.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;

//IUnknown
u32 VertexProperty::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT VertexProperty::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    //if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    //{
    //    *ppvObject = static_cast<IUnknown *>(this);
    //    this->AddRef();
    //}
    //else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_BlendStateProperty))
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

u32 VertexProperty::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

VertexProperty::VertexProperty() : mp_vertex_property(nullptr) , m_total_size(0) , m_property_count(0){

}

VertexProperty::~VertexProperty(){
    EVOLUTION_DELETE_ARRAY(this->mp_vertex_property);
}

FrameworkResult::_RESULT VertexProperty::Create(VERTEX_PROPERTY::_PROPERTY vertex_property[], u32 count_property){
    m_property_count = count_property;
    mp_vertex_property = NEW u32[count_property];

    for (u32 i = 0; i < count_property; i++)
    {
        mp_vertex_property[i] = this->GetSize(vertex_property[i]);
        m_total_size += mp_vertex_property[i];
    }
    return FrameworkResult::RESULT_OK;
}

u32 VertexProperty::GetPropertyCount(){
    return this->m_property_count;
}

u32 VertexProperty::GetPropertySize(u32 index){
    return this->mp_vertex_property[index];
}

u32 VertexProperty::GetTotalSize(){
    return this->m_total_size;
}

u32 VertexProperty::GetSize(VERTEX_PROPERTY::_PROPERTY _property){
    switch (_property)
    {
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::SINT:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::UINT:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT:
        return 4;
        break;
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::SINT2:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::UINT2:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT2:
        return 8;
        break;
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::SINT3:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::UINT3:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT3:
        return 12;
        break;
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::SINT4:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::UINT4:
    case EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT4:
        return 16;
        break;
    default:
        return 0;
    }
    return 0;
}