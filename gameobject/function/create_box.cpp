#include "../evolution_gameobject_implement.h"
using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;

FrameworkResult::_RESULT EVOLUTION::FUNCTION::CreateBox(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, u32 width, u32 height, u32 depth, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command){

    VertexProperty* vertex_property = NEW VertexProperty();

    EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::_PROPERTY work[] = {
        EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT3,//POSITION
        EVOLUTION::FRAMEWORK::GAMEOBJECT::VERTEX_PROPERTY::FLOAT3,//NORMAL
    };
    vertex_property->Create(work, EVOLUTION_ARRAYSIZE(work));

    Mesh* mesh = NEW Mesh();

    struct _WORK_VERTEX{
        Vector3 position;
        Vector3 normal;
    };

    Vector3 max, min;

    min.x = width / -2.0f;
    max.x = width / 2.0f;

    min.y = height / -2.0f;
    max.y = height / 2.0f;

    min.z = depth / -2.0f;
    max.z = depth / 2.0f;

    _WORK_VERTEX work_vertex[] = {
        { Vector3(min.x, max.y, min.z), Vector3(0.0f, 0.0f, -1.0f) },
        { Vector3(max.x, max.y, min.z), Vector3(0.0f, 0.0f, -1.0f) },
        { Vector3(min.x, min.y, min.z), Vector3(0.0f, 0.0f, -1.0f) },
        { Vector3(max.x, min.y, min.z), Vector3(0.0f, 0.0f, -1.0f) },

        { Vector3(max.x, max.y, max.z), Vector3(0.0f, 0.0f, 1.0f) },
        { Vector3(min.x, max.y, max.z), Vector3(0.0f, 0.0f, 1.0f) },
        { Vector3(max.x, min.y, max.z), Vector3(0.0f, 0.0f, 1.0f) },
        { Vector3(min.x, min.y, max.z), Vector3(0.0f, 0.0f, 1.0f) },

        { Vector3(max.x, max.y, min.z), Vector3(1.0f, 0.0f, 0.0f) },
        { Vector3(max.x, max.y, max.z), Vector3(1.0f, 0.0f, 0.0f) },
        { Vector3(max.x, min.y, min.z), Vector3(1.0f, 0.0f, 0.0f) },
        { Vector3(max.x, min.y, max.z), Vector3(1.0f, 0.0f, 0.0f) },

        { Vector3(min.x, max.y, max.z), Vector3(-1.0f, 0.0f, 0.0f) },
        { Vector3(min.x, max.y, min.z), Vector3(-1.0f, 0.0f, 0.0f) },
        { Vector3(min.x, min.y, max.z), Vector3(-1.0f, 0.0f, 0.0f) },
        { Vector3(min.x, min.y, min.z), Vector3(-1.0f, 0.0f, 0.0f) },

        { Vector3(min.x, max.y, max.z), Vector3(0.0f, 1.0f, 0.0f) },
        { Vector3(max.x, max.y, max.z), Vector3(0.0f, 1.0f, 0.0f) },
        { Vector3(min.x, max.y, min.z), Vector3(0.0f, 1.0f, 0.0f) },
        { Vector3(max.x, max.y, min.z), Vector3(0.0f, 1.0f, 0.0f) },

        { Vector3(min.x, min.y, min.z), Vector3(0.0f, -1.0f, 0.0f) },
        { Vector3(max.x, min.y, min.z), Vector3(0.0f, -1.0f, 0.0f) },
        { Vector3(min.x, min.y, max.z), Vector3(0.0f, -1.0f, 0.0f) },
        { Vector3(max.x, min.y, max.z), Vector3(0.0f, -1.0f, 0.0f) },
    };

    if (EVOLUTION_FAILED( mesh->Create(graphic_factory, command, vertex_property, work_vertex, EVOLUTION_ARRAYSIZE(work_vertex))))
    {
        EVOLUTION_RELEASE(mesh);
    }
    EVOLUTION_RELEASE(vertex_property);
    *pp_mesh = mesh;

    return FrameworkResult::RESULT_OK;
}

