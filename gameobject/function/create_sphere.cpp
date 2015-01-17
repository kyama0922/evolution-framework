#include "../evolution_gameobject_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::GRAPHIC;
using namespace EVOLUTION::FRAMEWORK;
using namespace EVOLUTION::FRAMEWORK::GAMEOBJECT;



FrameworkResult::_RESULT EVOLUTION::FUNCTION::CreateSphere(FRAMEWORK::GAMEOBJECT::IMesh** pp_mesh, f32 Radius, u32 Slices, u32 Stacks, EVOLUTION::GRAPHIC::IGraphicFactory* graphic_factory, EVOLUTION::GRAPHIC::IGraphicCommand* command){

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
    if (Slices <= 2)
    {
        Slices = 3;
    }
    if (Stacks <= 1)
    {
        Stacks = 3;
    }
    u32 vertex_count = (Slices + 1) * (Stacks + 1);
    _WORK_VERTEX* work_vertex = NEW _WORK_VERTEX[vertex_count];
    //u32 vertex_count = 12;
    //_WORK_VERTEX work_vertex[12] /*= new _WORK_VERTEX[vertex_count]*/;

    //	頂点設定
    for (u32 y = 0; y < Stacks + 1; y++)
    {
        f32 ph = EVOLUTION::MATH::PI_F * (f32)y / (f32)Stacks;
        f32 py = EVOLUTION::MATH::cosf(ph) * Radius;
        f32 r = EVOLUTION::MATH::sinf(ph);
        for (u32 x = 0; x < Slices + 1; x++)
        {
            int index = (y * (Slices + 1)) + x;
            f32 th = EVOLUTION::MATH::PI_F2 * (f32)x / (f32)Slices;
            f32 px = r * EVOLUTION::MATH::cosf(th) * Radius;
            f32 pz = r * EVOLUTION::MATH::sinf(th) * Radius;
            work_vertex[index].position.x = px;
            work_vertex[index].position.y = py;
            work_vertex[index].position.z = pz;
            work_vertex[index].normal = work_vertex[index].position;
            work_vertex[index].normal.Normalize();
            work_vertex[index].color = Color(work_vertex[index].normal);
            work_vertex[index].color.a = 1.0f;
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
    u32 index_count = Slices * Stacks * 6;
    u32* indexes = new u32[index_count];

    //u32 index_count = 12 * 3;
    //u32 indexes[12 * 3];

    u32* work_index = indexes;
    for (u32 j = 0; j < Stacks; ++j) {
        for (u32 i = 0; i < Slices; ++i) {
            u32 count = (Slices + 1) * j + i;

            *work_index++ = count;
            *work_index++ = count + 1;
            *work_index++ = count + Slices + 2;

            *work_index++ = count;
            *work_index++ = count + Slices + 2;
            *work_index++ = count + Slices + 1;
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