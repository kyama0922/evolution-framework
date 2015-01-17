#include "../evolution_gameobject_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;



FrameworkResult::_RESULT EVOLUTION::FUNCTION::CreatePlate(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, f32 w, u32 h, u32 d, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command){

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

    u32 vertex_count = (d + 1) * (d + 1);
    _WORK_VERTEX* work_vertex = NEW _WORK_VERTEX[vertex_count];
    //u32 vertex_count = 4;
    //_WORK_VERTEX work_vertex[4] /*= new _WORK_VERTEX[vertex_count]*/;

    //	頂点設定
    const Vector3 normal(0, 1, 0);
    f32 width = (f32)w / 2.0f;
    f32 height = (f32)h / 2.0f;
    for (u32 z = 0; z < d + 1; z++)
    {
        f32 tmp_z = ((f32)z * (f32)h / (f32)d) - height;
        f32 tmp_w = (f32)w / (f32)d;
        for (u32 x = 0; x < d + 1; x++)
        {
            int index = (z * (d + 1)) + x;
            work_vertex[index].position.x = ((f32)x * tmp_w) - width;
            work_vertex[index].position.y = 0.0f;
            work_vertex[index].position.z = -tmp_z;
            work_vertex[index].normal = normal;
            work_vertex[index].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    //頂点の作成
    if (EVOLUTION_FAILED(mesh->Create(graphic_factory, command, vertex_property, work_vertex, vertex_count)))
    {
        EVOLUTION_RELEASE(vertex_property);
        EVOLUTION_RELEASE(mesh);
        return FrameworkResult::CREATE_FAILED;
    }
    EVOLUTION_RELEASE(vertex_property);

    //インデックスデータの作成
    u32 index_count = d * d * 6;
    u32* indexes = new u32[index_count];

    //u32 index_count = 6;
    //u32 indexes[6];
    u32* work_index = indexes;
    for (u32 j = 0; j < d; ++j) {
        for (u32 i = 0; i < d; ++i) {
            u32 count = (d + 1) * j + i;

            *work_index++ = count;
            *work_index++ = count + 1;
            *work_index++ = count + d + 2;

            *work_index++ = count;
            *work_index++ = count + d + 2;
            *work_index++ = count + d + 1;
        }
    }
    mesh->SetPrimitiveTopology(EVOLUTION::GRAPHIC::PRIMITIVE_TOPOLOGY::_TRIANGLELIST);
    //インデックスの作成
    if (EVOLUTION_FAILED(mesh->Create(graphic_factory, command, indexes, index_count)))
    {
        EVOLUTION_RELEASE(mesh);
        return FrameworkResult::CREATE_FAILED;
    }

    *pp_mesh = mesh;
    return FrameworkResult::RESULT_OK;
}