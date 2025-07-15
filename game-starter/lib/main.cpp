#include <fern/fern.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace Fern;

// Game state
struct Player {
    float x = 400;
    float y = 300;
    float vx = 0;
    float vy = 0;
    float radius = 20;
    Color color = Colors::Blue;
};

struct Enemy {
    float x, y;
    float vx, vy;
    float radius = 15;
    Color color = Colors::Red;
    bool active = true;
};

struct Bullet {
    float x, y;
    float vx, vy;
    float radius = 3;
    Color color = Colors::Yellow;
    bool active = true;
};

Player player;
std::vector<Enemy> enemies;
std::vector<Bullet> bullets;
int score = 0;
float enemySpawnTimer = 0;
bool gameOver = false;

void spawnEnemy() {
    Enemy enemy;
    enemy.x = (rand() % 2 == 0) ? -50 : 850;
    enemy.y = rand() % 600;
    enemy.vx = (enemy.x < 0) ? 2 : -2;
    enemy.vy = (rand() % 3 - 1) * 0.5f;
    enemies.push_back(enemy);
}

void update() {
    if (gameOver) return;
    
    // Player movement
    if (Input::isKeyPressed(Key::A) || Input::isKeyPressed(Key::Left)) {
        player.vx = -5;
    } else if (Input::isKeyPressed(Key::D) || Input::isKeyPressed(Key::Right)) {
        player.vx = 5;
    } else {
        player.vx = 0;
    }
    
    if (Input::isKeyPressed(Key::W) || Input::isKeyPressed(Key::Up)) {
        player.vy = -5;
    } else if (Input::isKeyPressed(Key::S) || Input::isKeyPressed(Key::Down)) {
        player.vy = 5;
    } else {
        player.vy = 0;
    }
    
    // Shooting
    if (Input::isKeyPressed(Key::Space)) {
        Bullet bullet;
        bullet.x = player.x;
        bullet.y = player.y - player.radius;
        bullet.vy = -10;
        bullets.push_back(bullet);
    }
    
    // Update player position
    player.x += player.vx;
    player.y += player.vy;
    
    // Keep player in bounds
    player.x = std::max(player.radius, std::min(800 - player.radius, player.x));
    player.y = std::max(player.radius, std::min(600 - player.radius, player.y));
    
    // Update bullets
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->x += it->vx;
        it->y += it->vy;
        
        if (it->y < 0 || it->y > 600) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
    
    // Spawn enemies
    enemySpawnTimer += 0.016f; // Assuming 60 FPS
    if (enemySpawnTimer > 1.0f) {
        spawnEnemy();
        enemySpawnTimer = 0;
    }
    
    // Update enemies
    for (auto& enemy : enemies) {
        if (!enemy.active) continue;
        
        enemy.x += enemy.vx;
        enemy.y += enemy.vy;
        
        // Check collision with player
        float dx = enemy.x - player.x;
        float dy = enemy.y - player.y;
        float dist = sqrt(dx*dx + dy*dy);
        
        if (dist < enemy.radius + player.radius) {
            gameOver = true;
        }
        
        // Check collision with bullets
        for (auto& bullet : bullets) {
            if (!bullet.active) continue;
            
            float bdx = bullet.x - enemy.x;
            float bdy = bullet.y - enemy.y;
            float bdist = sqrt(bdx*bdx + bdy*bdy);
            
            if (bdist < bullet.radius + enemy.radius) {
                enemy.active = false;
                bullet.active = false;
                score += 10;
            }
        }
    }
    
    // Remove inactive entities
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
                                [](const Enemy& e) { return !e.active; }), 
                 enemies.end());
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), 
                                [](const Bullet& b) { return !b.active; }), 
                 bullets.end());
}

void draw() {
    // Clear background
    Draw::fill(Colors::Black);
    
    if (gameOver) {
        // Game over screen
        DrawText::drawText("GAME OVER!", 300, 250, 4, Colors::Red);
        DrawText::drawText("Score: " + std::to_string(score), 320, 320, 2, Colors::White);
        DrawText::drawText("Press R to restart", 280, 380, 1, Colors::Gray);
        return;
    }
    
    // Draw player
    Draw::circle(player.x, player.y, player.radius, player.color);
    
    // Draw enemies
    for (const auto& enemy : enemies) {
        if (enemy.active) {
            Draw::circle(enemy.x, enemy.y, enemy.radius, enemy.color);
        }
    }
    
    // Draw bullets
    for (const auto& bullet : bullets) {
        if (bullet.active) {
            Draw::circle(bullet.x, bullet.y, bullet.radius, bullet.color);
        }
    }
    
    // Draw UI
    DrawText::drawText("Score: " + std::to_string(score), 10, 10, 2, Colors::White);
    DrawText::drawText("WASD/Arrows: Move", 10, 550, 1, Colors::Gray);
    DrawText::drawText("Space: Shoot", 10, 570, 1, Colors::Gray);
}

int main() {
    std::cout << "🌿 Starting Game Starter - Simple Space Shooter..." << std::endl;
    
    // Initialize Fern
    Fern::initialize();
    
    // Set up callbacks
    Fern::setUpdateCallback(update);
    Fern::setDrawCallback(draw);
    
    // Start the game loop
    Fern::startRenderLoop();
    
    return 0;
}
