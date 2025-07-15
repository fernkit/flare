# Game Starter - Space Shooter

A simple space shooter game built with Fern UI Framework. This template demonstrates basic game development concepts including:

## Features

- **Player Movement**: WASD or arrow keys to move
- **Shooting System**: Space bar to shoot bullets
- **Enemy AI**: Enemies spawn and move toward player
- **Collision Detection**: Bullets hit enemies, enemies hit player
- **Score System**: Earn points by destroying enemies
- **Game Over**: Restart functionality

## Game Mechanics

- **Player**: Blue circle controlled with keyboard
- **Enemies**: Red circles that spawn from screen edges
- **Bullets**: Yellow circles that destroy enemies
- **Scoring**: 10 points per enemy destroyed

## Controls

- **WASD** or **Arrow Keys**: Move player
- **Space**: Shoot bullets
- **R**: Restart game (when game over)

## Getting Started

```bash
cd game-starter
fern fire                 # Run the game
fern prepare web          # Build for web
fern prepare linux        # Build for Linux
```

## Code Structure

- `Player`, `Enemy`, `Bullet` structs for game entities
- `update()` function handles game logic
- `draw()` function renders everything
- Collision detection between all entities
- Simple AI for enemy movement

## Customization Ideas

- Add power-ups and special weapons
- Implement different enemy types
- Add sound effects and music
- Create levels with increasing difficulty
- Add particle effects for explosions
- Implement a high score system

This template provides a solid foundation for 2D games with Fern!
