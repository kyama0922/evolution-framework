#include "../evolution_gameobject_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;



FrameworkResult::_RESULT EVOLUTION::FUNCTION::CreateAxis(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command){
    *pp_mesh = nullptr;
    VertexProperty* vertex_property = NEW VertexProperty();

    EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::_PROPERTY work[] = {
        EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT3,//POSITION
        EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT3,//NORMAL
        EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT4,//COLOR
    };
    vertex_property->Create(work, EVOLUTION_ARRAYSIZE(work));

    Mesh* mesh = NEW Mesh();

    struct _WORK_VERTEX{
        Vector3 position;
        Vector3 normal;
        Color   color;
    };

    _WORK_VERTEX work_vertex[] = {
        { Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Color(0.0f, 1.0f, 0.0f, 1.0f) },
        { Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Color(0.0f, 1.0f, 0.0f, 1.0f) },
        { Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Color(0.0f, 0.0f, 0.0f, 1.0f) },
        { Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 1.0f, 1.0f) },
        { Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 1.0f, 1.0f) },
    };

    //頂点の作成
    if (EVOLUTION_FAILED(mesh->Create(graphic_factory, command, vertex_property, work_vertex, EVOLUTION_ARRAYSIZE(work_vertex))))
    {
        EVOLUTION_RELEASE(vertex_property);
        EVOLUTION_RELEASE(mesh);
        return FrameworkResult::CREATE_FAILED;
    }
    EVOLUTION_RELEASE(vertex_property);

    mesh->SetPrimitiveTopology(EVOLUTION::GRAPHIC::PRIMITIVE_TOPOLOGY::_LINESTRIP);

    *pp_mesh = mesh;
    return FrameworkResult::RESULT_OK;
}