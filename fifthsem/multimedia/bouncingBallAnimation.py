import pygame
pygame.init()

# Screen dimensions
width, height = 1000, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Bouncing Ball - Vertical Motion")
red, black = (255, 0, 0), (0, 0, 0)

# Ball properties
ball_x = width // 2
ball_y = 30
ball_radius = 30
ball_speed = 5
direction_flag = "DOWN"

clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Move FIRST
    if direction_flag == "DOWN":
        ball_y += ball_speed
    else:
        ball_y -= ball_speed

    # Proper boundary handling (no tickling)
    if ball_y >= height - ball_radius:
        ball_y = height - ball_radius
        direction_flag = "UP"

    elif ball_y <= ball_radius:
        ball_y = ball_radius
        direction_flag = "DOWN"

    # Clear screen
    screen.fill(black)

    # Draw ball
    pygame.draw.circle(screen, red, (ball_x, int(ball_y)), ball_radius)

    pygame.display.flip()
    clock.tick(20)

pygame.quit()