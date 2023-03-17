#include <cocos2d.h>
#include <gd.h>
#include <fstream>
#include "utils.hpp"
#include <array>

using namespace cocos2d;
using namespace gd;

CCSprite* ModUtils::createWithSpriteFrameNameOrPlaceholder(const char* name){
    auto sprite = CCSprite::createWithSpriteFrameName(name);
    if (sprite) return sprite;
    CCSprite* placeholder = createPlaceholder();

    auto placeholderLabel = CCLabelBMFont::create(name, "chatFont.fnt", 6, kCCTextAlignmentCenter);
    placeholderLabel->setPosition({ placeholder->getContentSize().width / 2, placeholder->getContentSize().height / 2 });
    placeholder->addChild(placeholderLabel);

    return placeholder;
}

CCSprite* ModUtils::createSpriteOrPlaceholder(const char* name){
    auto sprite = CCSprite::create(name);
    if (sprite) return sprite;
    CCSprite* placeholder = createPlaceholder();

    auto placeholderLabel = CCLabelBMFont::create(name, "chatFont.fnt", 6, kCCTextAlignmentCenter);
    placeholderLabel->setPosition({ placeholder->getContentSize().width / 2, placeholder->getContentSize().height / 2 });
    placeholder->addChild(placeholderLabel);

    return placeholder;
}

CCSprite* ModUtils::createPlaceholder(){
        auto sprite = CCSprite::create();

        auto subSprite1 = CCSprite::create("square02b_001.png");
        auto subSprite2 = CCSprite::create("square02b_001.png");
        auto subSprite3 = CCSprite::create("square02b_001.png");
        auto subSprite4 = CCSprite::create("square02b_001.png");

        std::array<CCSprite*, 4> sprites = {subSprite1, subSprite2, subSprite3, subSprite4};

        subSprite1->setAnchorPoint({0,0});
        subSprite2->setAnchorPoint({1,0});
        subSprite3->setAnchorPoint({0,1});
        subSprite4->setAnchorPoint({1,1});

        subSprite2->setColor({251,64,249});
        subSprite1->setColor({0,0,0});
        subSprite3->setColor({251,64,249});
        subSprite4->setColor({0,0,0});

        for(auto subSprite : sprites){
                subSprite->setScale(.25f);
                subSprite->setPosition(subSprite->getContentSize() / 2);
                sprite->addChild(subSprite);

        }

        sprite->setContentSize(subSprite1->getContentSize());

        return sprite;
}
/*
        Windows only code :D
*/
void ModUtils::copyToClipboard(const char* text){
        const size_t len = strlen(text) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), text, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
}

void ModUtils::copyToClipboard(const char* text, CCLayer* parent){
        copyToClipboard(text);
        parent->addChild(TextAlertPopup::create("Copied to clipboard", 0.5f, 0.6f), 100);
}

CCMenuItemSpriteExtra* ModUtils::createTextButton(CCLayer* parent, const char* text, cocos2d::SEL_MenuHandler handler, int width, float height, float scale){
    auto buttonSprite = gd::ButtonSprite::create(text, width, true, "bigFont.fnt", "GJ_button_01.png", height, scale);
    auto buttonButton = gd::CCMenuItemSpriteExtra::create(
        buttonSprite,
        parent,
        handler
    );
    buttonButton->setSizeMult(1.2f);

    return buttonButton;
}

void ModUtils::strToLower(std::string& str) {
        for(auto& c : str) c = tolower(c);
}