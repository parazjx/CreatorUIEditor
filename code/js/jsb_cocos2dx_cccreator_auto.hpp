#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef __cocos2dx_cccreator_h__
#define __cocos2dx_cccreator_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_creator_CreatorReader_class;
extern JSObject *jsb_creator_CreatorReader_prototype;

bool js_cocos2dx_cccreator_CreatorReader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_cccreator_CreatorReader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_cccreator_CreatorReader(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_cccreator(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_cccreator_CreatorReader_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_cccreator_CreatorReader_getNodeTree(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_cccreator_CreatorReader_createWithFilename(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_cccreator_h__
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
