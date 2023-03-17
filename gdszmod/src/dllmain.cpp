#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <random>
#include "utils.hpp"

#include "mapped-hooks.hpp"
#include <MinHook.h>

bool write_bytes(
    const std::uintptr_t address,
    std::vector<uint8_t> const& bytes)
{
    return WriteProcessMemory(
        GetCurrentProcess(),
        reinterpret_cast<LPVOID>(address),
        bytes.data(),
        bytes.size(),
        nullptr);
}

#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;

#include "DiscordRpc.h"
Discord* g_Discord;

#include "termsOfUseLayer.hpp"
#include "PromoInterstitial.hpp"

const char* version = "1.0";

class MenuLayerMod {
public:
    void onTwitch(cocos2d::CCObject* pSender){CCApplication::sharedApplication()->openURL("https://www.twitch.tv/robtopgames");}
    void onDiscord(cocos2d::CCObject* pSender){CCApplication::sharedApplication()->openURL("https://discord.com/invite/geometrydash");}
    void termsOfUseLayerShow(cocos2d::CCObject* pSender) {
        if (!GameManager::sharedState()->getUGV("30")) {
            termsOfUseLayer::create()->show();
        }
    }
    void onLabel(cocos2d::CCObject* pSender) { CCApplication::sharedApplication()->openURL("https://github.com/user95401/gdsz"); }
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
        std::vector<char>* responseData = response->getResponseData();
        std::string responseString(responseData->begin(), responseData->end());
        if (responseString != version) {
            AchievementNotifier::sharedState()->notifyAchievement("Update available!", "You can download new version on GameJolt.", "GJ_downloadsIcon_001.png", true);
        }
    }
};
void __fastcall MenuLayer_onCreator(MenuLayer* self, void* a, cocos2d::CCObject* pSender) {
    PromoInterstitial::create()->show();
}
bool __fastcall MenuLayer_init(MenuLayer* self) {
    if (!MHook::getOriginal(MenuLayer_init)(self)) return false;
    CCMenu* socialsMenu = CCMenu::create();
    self->addChild(socialsMenu);
    socialsMenu->setPosition({ 50, 30 - 6 });

    auto robtopLogo = ModUtils::createWithSpriteFrameNameOrPlaceholder("robtoplogo_small.png");
    robtopLogo->setScale(0.8f);
    auto robtopExtra = CCMenuItemSpriteExtra::create(robtopLogo, self, menu_selector(CreatorLayer::onBack));
    socialsMenu->addChild(robtopExtra);

    auto facebookIcon = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_fbIcon_001.png");
    facebookIcon->setScale(0.8f);
    auto facebookExtra = CCMenuItemSpriteExtra::create(facebookIcon, self, menu_selector(MenuLayer::onFacebook));
    facebookExtra->setSizeMult(1.5f);
    socialsMenu->addChild(facebookExtra);

    auto twitterIcon = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_twIcon_001.png");
    twitterIcon->setScale(0.8f);
    auto twitterExtra = CCMenuItemSpriteExtra::create(twitterIcon, self, menu_selector(MenuLayer::onTwitter));
    twitterExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitterExtra);

    auto youtubeIcon = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_ytIcon_001.png");
    youtubeIcon->setScale(0.8f);
    auto youtubeExtra = CCMenuItemSpriteExtra::create(youtubeIcon, self, menu_selector(MenuLayer::onYouTube));
    youtubeExtra->setSizeMult(1.5f);
    socialsMenu->addChild(youtubeExtra);

    auto twitchIcon = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_twitchIcon_001.png");
    twitchIcon->setScale(0.8f);
    auto twitchExtra = CCMenuItemSpriteExtra::create(twitchIcon, self, menu_selector(MenuLayerMod::onTwitch));
    twitchExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitchExtra);

    auto discordIcon = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_discordIcon_001.png");
    discordIcon->setScale(0.8f);
    auto discordExtra = CCMenuItemSpriteExtra::create(discordIcon, self, menu_selector(MenuLayerMod::onDiscord));
    discordExtra->setSizeMult(1.5f);
    socialsMenu->addChild(discordExtra);

    facebookExtra->setPosition(socialsMenu->convertToNodeSpace(CCPoint({ CCDirector::sharedDirector()->getScreenLeft() + 22, CCDirector::sharedDirector()->getScreenBottom() + 55 })));
    twitterExtra->setPosition(facebookExtra->getPosition() + CCPoint({ 30, 0 }));
    youtubeExtra->setPosition(twitterExtra->getPosition() + CCPoint({ 30, 0 }));
    twitchExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, 0 }));
    discordExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, -29 }));

    auto logo = (CCSprite*)self->getChildren()->objectAtIndex(1);
    CCSprite* szLogo = ModUtils::createWithSpriteFrameNameOrPlaceholder("gj_subzeroLogo_001.png");
    szLogo->setAnchorPoint({ -1.520f, 0.950f });
    logo->addChild(szLogo);

    self->runAction(CCSequence::create(CCDelayTime::create(0.55f), CCCallFuncO::create(self, callfuncO_selector(MenuLayerMod::termsOfUseLayerShow), self), nullptr));

    CCMenuItemLabel* labelItem = CCMenuItemLabel::create(CCLabelBMFont::create("Recreation by user666", "gjFont06.fnt"), self, menu_selector(MenuLayerMod::onLabel));
    labelItem->setPosition({ 0, -(CCDirector::sharedDirector()->getWinSize().height / 2) + ((labelItem->getContentSize().height / 2) - 12) }); //fukn crazy hardcode
    labelItem->setOpacity(80);
    labelItem->setScale(0.3);
    self->addChild(CCMenu::createWithItem(labelItem));

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setUrl("http://pornhub.webq2e.ru/gdszlastver.inf");
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerMod::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    return true;
}

void __fastcall LoadingLayer_loadingFinished(LoadingLayer* self) {
    //game001Sheet platformer btns from other game :>
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game001Sheet.plist", "game001Sheet.png");
    //GJ_ParticleSheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GJ_ParticleSheet.plist", "GJ_ParticleSheet.png");
    //GJ_ParticleSheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PixelSheet_01.plist", "PixelSheet_01.png");
    //TreasureRoomSheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TreasureRoomSheet.plist", "TreasureRoomSheet.png");
    //TowerSheet
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TowerSheet.plist", "TowerSheet.png");
    MHook::getOriginal(LoadingLayer_loadingFinished)(self);
}

void __fastcall  LoadingLayer_loadAssets(LoadingLayer* self) {
    MHook::getOriginal(LoadingLayer_loadAssets)(self);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* fmodLogo = ModUtils::createWithSpriteFrameNameOrPlaceholder("fmodLogo.png");
    self->removeChildByTag(9230);
    fmodLogo->setTag(9230);
    fmodLogo->setPosition({ winSize.width - 35, 30 });
    fmodLogo->setColor(ccc3(1, 1, 1));
    fmodLogo->setScale({ 0.7f });
    self->addChild(fmodLogo);

    CCSprite* cocos2DxLogo = ModUtils::createWithSpriteFrameNameOrPlaceholder("cocos2DxLogo.png");
    self->removeChildByTag(1086);
    fmodLogo->setTag(1086);
    cocos2DxLogo->setPosition({ winSize.width - 35, 12 });
    cocos2DxLogo->setScale({ 0.7f });
    self->addChild(cocos2DxLogo);

    self->removeChildByTag(8549);
    CCSprite* gjLogo = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    self->addChild(gjLogo);
    gjLogo->setTag(8549);
    gjLogo->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f + 26.0f));

    self->removeChildByTag(34893);
    CCSprite* robTopLogo = CCSprite::createWithSpriteFrameName("RobTopLogoBig_001.png");
    self->addChild(robTopLogo);
    robTopLogo->setTag(34893);
    const CCPoint gjLogoPos = gjLogo->getPosition();
    const CCPoint logoPos2(0.0f, 80.0f);
    robTopLogo->setPosition(logoPos2 + gjLogoPos);

    self->removeChildByTag(2938);
    CCSprite* subZeroLogo = CCSprite::createWithSpriteFrameName("gj_subzeroLogo_001.png");
    self->addChild(subZeroLogo, 2);
    subZeroLogo->setTag(2938);
    const CCPoint logoPos3(140.0f, -46.0f);
    subZeroLogo->setPosition(logoPos3 + gjLogoPos);
}


class GJOptionsLayerHook {
public:
    void onMenuMusicToggle(cocos2d::CCObject* pSender) {
        auto GM = GameManager::sharedState();
        if (GM->getGameVariable("0122")) {
            GM->setGameVariable("0122", false);
            GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
        }
        else {
            GM->setGameVariable("0122", true);
            GameSoundManager::sharedState()->stopBackgroundMusic();
        }
    }
};
void __fastcall  OptionsLayer_customSetup(GJDropDownLayer* self) {
    MHook::getOriginal(OptionsLayer_customSetup)(self);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    auto GM = GameManager::sharedState();
    auto m_pLayer = self->m_pLayer;
    auto m_pListLayer = self->m_pListLayer;

    CCMenu* m = CCMenu::create();
    m->setPosition({ (winSize.width / 2) + 140, (winSize.height / 2) - 75 });
    m->setAnchorPoint({ 0,0 });
    m->setScale({ 0.65f });
    m_pLayer->addChild(m);

    auto menuMusicToggle = CCMenuItemToggler::create(
        CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
        CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
        m,
        (cocos2d::SEL_MenuHandler)&GJOptionsLayerHook::onMenuMusicToggle
    );
    menuMusicToggle->toggle(bool(GM->getGameVariable("0122")));
    m->addChild(menuMusicToggle);
    auto label = CCLabelBMFont::create("Menu\nmusic", "bigFont.fnt", 90, kCCTextAlignmentLeft);
    label->setPosition({ 0, 38 });
    label->setScale({ 0.55f });
    m->addChild(label);
}

bool __fastcall MoreOptionsLayer_init(gd::MoreOptionsLayer* self) {
    if (!MHook::getOriginal(MoreOptionsLayer_init)(self)) return false;
    //ревёрс инженередсер
    self->addToggle("Music in Practice", "0125", "Normal music is played in sync when playing created levels in practice mode.");
    self->addToggle("Detailed Info", "0109", "More info in level");
    self->addToggle("Hide Attempts", "0135", nullptr);
    self->addToggle("Hide Attempts Practice", "0134", nullptr);
    self->addToggle("Extra LDM", "0136", "LDM also removes glow and enter effects. Levels without LDM show the option LDM Lite.");
    self->addToggle("Hide Portal Guide", "0129", "Toggles OFF the extra indicators on portals");
    self->addToggle("Show Orb Guide", "0130", "Toggles ON the extra indicators on orbs");
    return true;
}

//looool
bool __fastcall LevelEditorLayer_init(gd::LevelEditorLayer* self, int edx, gd::GJGameLevel* level) {
    if (!MHook::getOriginal(LevelEditorLayer_init)(self, edx, level)) return false;

    CCSprite* THE_LINE = CCSprite::create("square02b_001.png");
    THE_LINE->setPosition({ 0, 205 });
    THE_LINE->setOpacity(50);
    THE_LINE->setScaleX({ 50 }); THE_LINE->setScaleY({ 0.008f });
    self->addChild(THE_LINE);

    return true;
}

bool __fastcall PlayLayer_init(PlayLayer* self, void* a, GJGameLevel* level) {
    if (!MHook::getOriginal(PlayLayer_init)(self, a, level)) return false;
    //smoothFix
    if (gd::GameManager::sharedState()->getGameVariable("0023") == true) {
        gd::GameManager::sharedState()->setGameVariable("0023", false);
        self->onExit();
        AchievementNotifier::sharedState()->notifyAchievement("Do not enable Smooth Fix!", "just dont pls", "exMark_001.png", true);
        GameSoundManager::sharedState()->playSound("door001.ogg");
    }
    return true;
}
//Jaan❤️
inline CCSprite* (__cdecl* CCSprite_createOrg)(const char* name);
CCSprite* CCSprite_createHook(const char* name) {
    if (std::string(name) == "GJ_paletaBtn_001.png") {
        return ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_paintBtn_001.png");
    }
    if (std::string(name) == "GJ_lite_001.png" || std::string(name) == "groundSquareShadow_001.png" || std::string(name) == "emptyGlow.png" || std::string(name) == "no") {
        CCSprite* no = CCSprite::create();
        return no;
    }
    return CCSprite_createOrg(name);
}
inline CCSprite* (__cdecl* CCSprite_createWithSpriteFrameNameOrg)(const char* name);
CCSprite* CCSprite_createWithSpriteFrameNameHook(const char* name) {
    SetWindowTextW(FindWindowW(NULL, L"GD SZ 4893496"), L"Geometry Dash SubZero"); //псих
    if (GameManager::sharedState()->getGameVariable("0135") == true || GameManager::sharedState()->getGameVariable("0134") == true) {//псих//псих//псих//псих//псих
    //нихуя не робит
    }
    else{}

    //GJ_freeChestBtn_001.png GJ_dailyRewardBtn_001.png
    if (std::string(name) == "GJ_dailyRewardBtn_001.png") {
        return ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_freeChestBtn_001.png");
    }
    if (std::string(name) == "GJ_dailyBtn_001.png") {
        return ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_profileButton_001.png");
    }
    if (std::string(name) == "GJ_lite_001.png" ||
        std::string(name) == "groundSquareShadow_001.png" ||
        std::string(name) == "emptyGlow.png" ||
        std::string(name) == "no" ||
        std::string(name) == "NO NO NO NO!!!" ||
        std::string(name) == "gIcon_18_001.png" ||
        std::string(name) == "bgIcon_23_001.png" ||
        std::string(name) == "bgIcon_24_001.png") {
        CCSprite* no = CCSprite::create();
        no->setVisible(false);
        return no;
    }
    if (std::string(name) == "gIcon_18_001.png") {
        CCSprite* GJ_select_001 = ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_select_001.png");
        GJ_select_001->runAction(CCRepeatForever::create(CCEaseBackInOut::create(CCScaleTo::create(0.3, 0.9))));
        GJ_select_001->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(1.0, 190),CCFadeTo::create(1.0, 255), nullptr)));
        return GJ_select_001;
    }
    if (std::string(name) == "GJ_moreGamesBtn_001.png") {
        CCSprite* GJ_freeLevelsBtn_001 = ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_freeLevelsBtn_001.png");
        if (!GameManager::sharedState()->getGameVariable("seenMoreGamesLayer")) {
            CCScaleTo* scaleTo = CCScaleTo::create(0.5f, 1.1f);
            CCEaseInOut* easeInOut = CCEaseInOut::create(scaleTo, 2.0f);
            CCScaleTo* scaleTo2 = CCScaleTo::create(0.5f, 1.0f);
            CCEaseInOut* easeInOut2 = CCEaseInOut::create(scaleTo2, 2.0f);
            CCSequence* sequence = CCSequence::create(easeInOut, easeInOut2, nullptr);
            CCRepeatForever* repeatForever = CCRepeatForever::create(sequence);
            GJ_freeLevelsBtn_001->runAction(repeatForever);
        }
        return GJ_freeLevelsBtn_001;
    }
    return CCSprite_createWithSpriteFrameNameOrg(name);
}
inline CCLabelBMFont* (__cdecl* CCLabelBMFont_createOrg)(const char* str, const char* fntFile);
CCLabelBMFont* CCLabelBMFont_createHook(const char* str, const char* fntFile) {
    if (std::string(str) == "Mod developed by Sai") {
        return CCLabelBMFont_createOrg("     Color palette By Sai // Increase icons by Guschin", fntFile);
    }
    if (std::string(str) == "NO NO NO NO!!!" && std::string(fntFile) != "chatFont.fnt") {
        CCLabelBMFont* lbl = CCLabelBMFont::create("", "gjFont01.fnt");
        lbl->setVisible(false);
        lbl->setAnchorPoint({-999.0f,-999.0f});
        return lbl;
    }
    return CCLabelBMFont_createOrg(str, fntFile);
}

DWORD WINAPI thread_func(void* hModule) {

    // initialize minhook
    MH_Initialize();

    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createHook, CCSprite_createOrg);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameNameHook, CCSprite_createWithSpriteFrameNameOrg);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_createHook, CCLabelBMFont_createOrg);

    std::random_device os_seed;
    const unsigned int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(250, 1000);
    int sleepMs = distribute(generator);
    Sleep(sleepMs);

    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    auto libcocos2d = (DWORD)GetModuleHandleA("libcocos2d.dll");

    MHook::registerHook(base + 0x1907b0, MenuLayer_init);
    MHook::registerHook(base + 0x191cd0, MenuLayer_onCreator);
    MHook::registerHook(base + 0x18C8E0, LoadingLayer_loadAssets);
    MHook::registerHook(base + 0x1dd420, OptionsLayer_customSetup);
    MHook::registerHook(base + 0x1DE8F0, MoreOptionsLayer_init);
    MHook::registerHook(base + 0x15EE00, LevelEditorLayer_init);
    MHook::registerHook(base + 0x1FB780, PlayLayer_init);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    g_Discord->Initialize();
    g_Discord->Update();

    SetWindowTextW(FindWindowW(NULL, L"GD SZ 4893496"), L"Geometry Dash SubZero");

    /*while (true) {
        if (GameManager::sharedState()->getGameVariable("0122")) {
            if (FMODAudioEngine::sharedEngine()->isBackgroundMusicPlaying(std::string("menuLoop.mp3"))) { GameSoundManager::sharedState()->stopBackgroundMusic(); }
        }
    }*/

    //anti icons hack
    write_bytes(base + 0xC50A8, { 0xE8, 0x7A, 0xCD, 0x19, 0x00 });
    //anti color hack
    write_bytes(base + 0xC54BA, { 0xE8, 0x68, 0xC9, 0x19, 0x00 });
    //Instant Mirror Portal
    write_bytes(base + 0x20ACA3, { 0xC7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00 });
    // Level Completion
    write_bytes(base + 0x1FD557, { 0xEB, 0x0C, });
    write_bytes(base + 0x1FD742, { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    write_bytes(base + 0x1FD756, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    write_bytes(base + 0x1FD79A, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    write_bytes(base + 0x1FD7AF, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    //Verify Hack
    write_bytes(base + 0x71D48, { 0xEB });
    // Load Failed
    write_bytes(base + 0x18B2B4, { 0xB0 , 0x01 });
    //Rotation Hack
    write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    //Allows you to scroll out the editor
    write_bytes(base + 0x8FAAC, { 0xEB });
    write_bytes(base + 0x8FA95, { 0xEB });
    write_bytes(base + 0x8FAC5, { 0xEB });
    write_bytes(base + 0x8FADC, { 0xEB });
    //Trail Bug Fix (Fixes trail cutting on high refresh rates)
    write_bytes(libcocos2d + 0xAE9BD, { 0xBB , 0xFF , 0x00 , 0x00 , 0x00 , 0x90 });

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}