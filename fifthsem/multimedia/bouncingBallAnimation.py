import pygame
pygame.init()

# Screen dimensions
width, height = 1000, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Bouncing Ball - Vertical Motion")
red, black = (255, 0, 0), (0, 0, 0)

# Ball properties (EXACTLY per algorithm)
ball_x = width // 2        # Center horizontally
ball_y = 30               # Start near top
ball_radius = 30
ball_speed = 5
direction_flag = "DOWN"

clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    # EXACT boundary detection per pseudocode
    if ball_y >= (height - 30) or ball_y <= 30:
        if direction_flag == "DOWN":
            direction_flag = "UP"
        else:
            direction_flag = "DOWN"
    
    # Clear screen
    screen.fill(black)
    
    # Draw filled red circle (SOLID RED per pseudocode)
    pygame.draw.circle(screen, red, (ball_x, int(ball_y)), ball_radius)
    
    # Update position per direction
    if direction_flag == "DOWN":
        ball_y += ball_speed
    else:
        ball_y -= ball_speed
    
    pygame.display.flip()
    clock.tick(20)  # 50ms delay = 20 FPS

pygame.quit()
