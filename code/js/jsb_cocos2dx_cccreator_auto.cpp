#include "scripting/js-bindings/auto/jsb_cocos2dx_cccreator_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "cccreator/CreatorReader.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_creator_CreatorReader_class;
JSObject *jsb_creator_CreatorReader_prototype;

bool js_cocos2dx_cccreator_CreatorReader_getVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    creator::CreatorReader* cobj = (creator::CreatorReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_cccreator_CreatorReader_getVersion : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getVersion();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_cccreator_CreatorReader_getVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_cccreator_CreatorReader_getNodeTree(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    creator::CreatorReader* cobj = (creator::CreatorReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_cccreator_CreatorReader_getNodeTree : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNodeTree();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_cccreator_CreatorReader_getNodeTree : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_cccreator_CreatorReader_createWithFilename(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_cccreator_CreatorReader_createWithFilename : Error processing arguments");

        auto ret = creator::CreatorReader::createWithFilename(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<creator::CreatorReader>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "creator::CreatorReader"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_cccreator_CreatorReader_createWithFilename : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_cccreator_CreatorReader(JSContext *cx, JS::HandleObject global) {
    jsb_creator_CreatorReader_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_creator_CreatorReader_class->name = "CreatorReader";
    jsb_creator_CreatorReader_class->addProperty = JS_PropertyStub;
    jsb_creator_CreatorReader_class->delProperty = JS_DeletePropertyStub;
    jsb_creator_CreatorReader_class->getProperty = JS_PropertyStub;
    jsb_creator_CreatorReader_class->setProperty = JS_StrictPropertyStub;
    jsb_creator_CreatorReader_class->enumerate = JS_EnumerateStub;
    jsb_creator_CreatorReader_class->resolve = JS_ResolveStub;
    jsb_creator_CreatorReader_class->convert = JS_ConvertStub;
    jsb_creator_CreatorReader_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getVersion", js_cocos2dx_cccreator_CreatorReader_getVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNodeTree", js_cocos2dx_cccreator_CreatorReader_getNodeTree, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFilename", js_cocos2dx_cccreator_CreatorReader_createWithFilename, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_creator_CreatorReader_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_creator_CreatorReader_class,
        dummy_constructor<creator::CreatorReader>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_creator_CreatorReader_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "CreatorReader"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<creator::CreatorReader>(cx, jsb_creator_CreatorReader_class, proto, JS::NullPtr());
}

void register_all_cocos2dx_cccreator(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "creator", &ns);

    js_register_cocos2dx_cccreator_CreatorReader(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
