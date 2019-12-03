#ifndef  _UI_READER_CreatorReader_H_
#define  _UI_READER_CreatorReader_H_

#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

#include "ui/CocosGUI.h"
#include "Macros.h"
#include "CreatorReader_generated.h"

NS_CCR_BEGIN

class CreatorReader: public cocos2d::Ref
{
public:
    static CreatorReader* createWithFilename(const std::string& filename);

    /**
     Returns the scenegraph contained in the .ccreator file
     @return A `Node*`
     */
    cocos2d::Node* getNodeTree() const;

    /**
     Returns the FlatBuffers Schema version.
     @return a string containing the flatbuffer's schema version
     */
    std::string getVersion() const;

protected:
    CreatorReader();
    ~CreatorReader();
    bool initWithFilename(const std::string& filename);

    cocos2d::Node* createTree(const buffers::NodeTree* treeBuffer) const;

    cocos2d::Scene* createScene(const buffers::Scene* sceneBuffer) const;
    void parseScene(cocos2d::Scene* scene, const buffers::Scene* sceneBuffer) const;

    cocos2d::Node* createNode(const buffers::Node* nodeBuffer) const;
    void parseNode(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;
    //void parseNodeAnimation(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;
    //void parseColliders(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;

    cocos2d::Sprite* createSprite(const buffers::Sprite* spriteBuffer) const;
    void parseSprite(cocos2d::Sprite* sprite, const buffers::Sprite* spriteBuffer) const;

    cocos2d::TMXTiledMap* createTileMap(const buffers::TileMap* tilemapBuffer) const;
    void parseTilemap(cocos2d::TMXTiledMap* tilemap, const buffers::TileMap* tilemapBuffer) const;

    cocos2d::Label* createLabel(const buffers::Label* labelBuffer) const;
    void parseLabel(cocos2d::Label* label, const buffers::Label* labelBuffer) const;

    cocos2d::ui::RichText* createRichText(const buffers::RichText* richTextBuffer) const;
    void parseRichText(cocos2d::ui::RichText* richText, const buffers::RichText* richTextBuffer) const;

    cocos2d::ParticleSystemQuad* createParticle(const buffers::Particle* particleBuffer) const;
    void parseParticle(cocos2d::ParticleSystemQuad* partile, const buffers::Particle* particleBuffer) const;

    cocos2d::ui::ScrollView* createScrollView(const buffers::ScrollView* scrollViewBuffer) const;
    void parseScrollView(cocos2d::ui::ScrollView* scrollView, const buffers::ScrollView* scrollViewBuffer) const;

    cocos2d::ui::LoadingBar* createProgressBar(const buffers::ProgressBar* progressBarBuffer) const;
    void parseProgressBar(cocos2d::ui::LoadingBar* progressBar, const buffers::ProgressBar* progressBarBuffer) const;

    cocos2d::ui::EditBox* createEditBox(const buffers::EditBox* editBoxBuffer) const;
    void parseEditBox(cocos2d::ui::EditBox* editBox, const buffers::EditBox* editBoxBuffer) const;

    cocos2d::ui::Button* createButton(const buffers::Button* buttonBuffer) const;
    void parseButton(cocos2d::ui::Button* button, const buffers::Button* buttonBuffer) const;

    spine::SkeletonAnimation* createSpineSkeleton(const buffers::SpineSkeleton* spineBuffer) const;
    void parseSpineSkeleton(spine::SkeletonAnimation* button, const buffers::SpineSkeleton* spineBuffer) const;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    cocos2d::experimental::ui::VideoPlayer* createVideoPlayer(const buffers::VideoPlayer* videoPlayerBuffer) const;
    void parseVideoPlayer(cocos2d::experimental::ui::VideoPlayer* videoPlayer, const buffers::VideoPlayer* videoPlayerBuffer) const;
    
    cocos2d::experimental::ui::WebView* createWebView(const buffers::WebView* webViewBuffer) const;
    void parseWebView(cocos2d::experimental::ui::WebView* webView, const buffers::WebView* webViewBuffer) const;
#endif
    
    cocos2d::ui::Slider* createSlider(const buffers::Slider* sliderBuffer) const;
    void parseSlider(cocos2d::ui::Slider* slider, const buffers::Slider* sliderBuffer) const;
    
    cocos2d::ui::CheckBox* createToggle(const buffers::Toggle* toggleBuffer) const;
    void parseToggle(cocos2d::ui::CheckBox* checkBox, const buffers::Toggle* toggleBuffer) const;
    
    cocos2d::ui::RadioButtonGroup* createToggleGroup(const buffers::ToggleGroup* toggleGroupBuffer) const;
    void parseToggleGroup(cocos2d::ui::RadioButtonGroup* radioGroup, const buffers::ToggleGroup* toggleGroupBuffer) const;
    
    cocos2d::ui::PageView* createPageView(const buffers::PageView* pageViewBuffer) const;
    void parsePageView(cocos2d::ui::PageView* pageview, const buffers::PageView* pageViewBuffer) const;
    
    cocos2d::ClippingNode* createMask(const buffers::Mask* maskBuffer) const;
    void parseMask(cocos2d::ClippingNode* mask, const buffers::Mask* maskBuffer) const;
    
//    dragonBones::CCArmatureDisplay* createArmatureDisplay(const buffers::DragonBones* dragonBonesBuffer) const;
//    void parseArmatureDisplay(dragonBones::CCArmatureDisplay* armatureDisplay, const buffers::DragonBones* dragonBonesBuffer) const;
    
    cocos2d::MotionStreak* createMotionStreak(const buffers::MotionStreak* motionStreakBuffer) const;
    void parseMotionStreak(cocos2d::MotionStreak* motionStreak, const buffers::MotionStreak* motionStreakBuffer) const;
    
    void setupSpriteFrames();
//    void setupCollisionMatrix();


    /** Creator uses parent's anchorpoint for child positioning.
     cocos2d-x uses parent's (0,0) for child positioning
     this function adjust that */
    void adjustPosition(cocos2d::Node* node) const;

    // variables
    cocos2d::Data _data;
    std::string _version;
    
    // AnimationManager *_animationManager;
    // ColliderManager *_collisionManager;
    
    // creator will make scene at the center of screen when apply design solution strategy, cocos2d-x doesn't do it like this
    // this value record the diff
    //cocos2d::Vec2 _positionDiffDesignResolution;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(CreatorReader);
};

NS_CCR_END

#endif
