#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define LEVEL_ID 33759558

class CubeNode : public CCMenuItemSpriteExtra {
    private:
        std::string m_key;
        float m_timeout;
        CircleButtonSprite* m_btnSprite;

        void changeButton(bool on);
        void openLevel(GJGameLevel* level);
        void onBtnClick(CCObject* sender);

    public:
        CubeNode();

        static CubeNode* create();

        bool init();
        void update(float dt) override;
};