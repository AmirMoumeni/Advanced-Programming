#ifndef WINNERDISPLAY_H
#define WINNERDISPLAY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class WinnerDisplay {
private:
    sf::Texture winnerTexture;
    sf::Sprite winnerSprite;
    sf::Clock displayClock;  // برای زمان‌بندی نمایش برنده
    bool isDisplaying;   // وضعیت نمایش برنده

public:
    WinnerDisplay();  // کانستراکتور

    // بارگذاری و تنظیم تصویر برنده
    void loadWinnerImage(const std::string& imagePath);

    // شروع نمایش برنده
    void startDisplay();

    // بررسی اینکه آیا 3 ثانیه گذشته و باید تصویر برنده مخفی شود
    bool update();

    // رسم تصویر برنده
    void draw(sf::RenderWindow& window);
};

#endif
