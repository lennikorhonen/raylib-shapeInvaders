#include "raylib.h"

#define PLAYER_SIZE		  16

int main(void)
{
	// Set screen size variables so that it can be used for positioning
	const int screenWidth = 800;
	const int screenHeight = 450;
	// Set start variables
	int score = 0;
	int spawnBullet = 0;
	int bulletDestroyed = 0;
	float bulletTravelDist = 2.0f;
	float bulletDistanceTravelled = 0.0f;
	float bulletStartX = 0.0f;

	int enemyHit = 0;

	InitWindow(screenWidth, screenHeight, "ShapeInvaders the Game");

	// Initial player position
	Vector2 playerPosition = { (float)screenWidth/2, (float)screenHeight - (float)screenHeight/10 };

	Vector2 enemyPosition = { (float)screenWidth/2, (float)screenHeight/10 };

	Vector2 bulletSize = { 4, 12 };

	// Sets the game FPS to 60
	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) playerPosition.x += 2.0f;
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) playerPosition.x -= 2.0f;
		// Set spawnBullet to 1 so later we know that we should start drawing the bullet
		// Don't allow more than one bullet at a time
		if (IsKeyPressed(KEY_SPACE) && spawnBullet == 0) {
			spawnBullet = 1;
			bulletStartX = playerPosition.x+6;
		}

		// Check that we don't go out of bounds
		if (playerPosition.x < 0) playerPosition.x = 0;
		if (playerPosition.x > screenWidth-PLAYER_SIZE) playerPosition.x = screenWidth-PLAYER_SIZE;

		if (bulletDistanceTravelled > screenHeight-bulletSize.y) {
			bulletDestroyed = 1;
		}

		BeginDrawing();

			// Set background color to black
			ClearBackground(BLACK);

			// Draw Score text
			DrawText(TextFormat("SCORE: %i", score), 20, 20, 20, WHITE);

			// Draw player position
			DrawRectangleV(playerPosition, (Vector2){ PLAYER_SIZE, PLAYER_SIZE }, DARKGREEN);

			// Draw an enemy
			Rectangle enemy = { enemyPosition.x, enemyPosition.y, 16, 16 };
			
			if (enemyHit == 0) {
				DrawRectangleRec(enemy, RED);
			}
			
			Rectangle bullet = { bulletStartX, playerPosition.y-PLAYER_SIZE-bulletDistanceTravelled, bulletSize.x, bulletSize.y };
			// Shoot a bullet
			if (spawnBullet) {
				DrawRectangleRec(bullet, WHITE);
				bulletDistanceTravelled += bulletTravelDist;
				
				if (CheckCollisionRecs(enemy, bullet)) {
					bulletDestroyed = 1;
					score += 10;
					enemyHit = 1;
				}
				// Despawn bullet and reset its values if it collides with something or goes out of bounds
				if (bulletDestroyed) {
					bulletStartX = 0.0f;
					bulletDistanceTravelled = 0;
					spawnBullet = 0;
					bulletDestroyed = 0;
				}
			}
			
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
