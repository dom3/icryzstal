#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSearchLayer.hpp>

#define LEVEL_ID 33759558

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
    bool init(const int type) {
        if (!LevelSearchLayer::init(type)) {
            return false;
        }

        auto* otherFilterMenu = this->getChildByID("other-filter-menu");

        auto* btnSprite = CircleButtonSprite::createWithSprite("cube_30.png"_spr);
        btnSprite->getTopNode()->setScale(0.8f);
        btnSprite->getTopNode()->updateTransform();
        btnSprite->setScale(0.8f);
        

        auto* btn = CCMenuItemSpriteExtra::create(
            btnSprite,
            this,
            menu_selector(MyLevelSearchLayer::onBtnClick)
            );

        otherFilterMenu->addChild(btn);
        otherFilterMenu->updateLayout();

        return true;
    }

    void onBtnClick(CCObject*) {
        log::info("Opening npesta menu :)");
    }
};