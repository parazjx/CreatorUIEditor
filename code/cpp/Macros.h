#ifndef  _UI_READER_MACRO_H_
#define  _UI_READER_MACRO_H_

#ifdef __cplusplus
#define NS_CCR_BEGIN                     namespace creator {
#define NS_CCR_END                       }
#define USING_NS_CCR                     using namespace creator
#else
#define NS_CC_BEGIN
#define NS_CC_END
#define USING_NS_CC
#define NS_CC
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
|| (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
    #define CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
        TypeName(const TypeName &) = delete; \
        TypeName& operator =(const TypeName &) = delete; \
        TypeName(TypeName &&) = delete; \
        TypeName& operator =(TypeName &&) = delete;
#else
    #define CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
        TypeName(const TypeName &); \
        TypeName& operator =(const TypeName &); \
        TypeName(TypeName &&); \
        TypeName& operator =(TypeName &&);
#endif

#endif
