#ifndef __EVOLUTION_FRAMEWORK_RESULT_H__
#define __EVOLUTION_FRAMEWORK_RESULT_H__


namespace EVOLUTION{
    namespace FRAMEWORK{

        struct FrameworkResult{
            enum _RESULT{
                //----------------------------成功----------------------------
                RESULT_OK = 0x00000000,//成功

                //----------------------------失敗----------------------------
                UNKNOWN_FAILED = 0x80000000, //失敗

                CREATE_FAILED,    //作成に失敗
            };
        };

    }
}

#endif // !__EVOLUTION_FRAMEWORK_RESULT_H__