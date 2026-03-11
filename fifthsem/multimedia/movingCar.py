import pygame
pygame.init()

# Screen setup
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Moving Car Animation")
clock = pygame.time.Clock()

# Colors per algorithm
BLUE = (0, 0, 255)
LIGHTBLUE = (135, 206, 250)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 128, 0)

def draw_car(x, y):
    # Car body (100x50 rectangle)
    pygame.draw.rect(screen, BLUE, (x, y, 100, 50))
    
    # Car window (80x20 rectangle)
    pygame.draw.rect(screen, LIGHTBLUE, (x+10, y-20, 80, 20))
    
    # Window divider line
    pygame.draw.line(screen, WHITE, (x+50, y-20), (x+50, y), 3)
    
    # Left wheel (r=10)
    pygame.draw.circle(screen, BLACK, (x+20, y+50), 10)
    pygame.draw.circle(screen, WHITE, (x+20, y+50), 5)  # Rim
    
    # Right wheel (r=10)
    pygame.draw.circle(screen, BLACK, (x+80, y+50), 10)
    pygame.draw.circle(screen, WHITE, (x+80, y+50), 5)  # Rim

# Initial car properties
x = 50
y = 200
speed = 5

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT or event.type == pygame.KEYDOWN:
            running = False
    
    # Fill background green
    screen.fill(GREEN)
    
    # Draw road (black rectangle full width)
    pygame.draw.rect(screen, BLACK, (0, y+30, WIDTH, 80))
    
    # Draw car
    draw_car(x, y)
    
    # Move car
    x += speed
    
    # Screen wrapping
    if x > WIDTH:
        x = -100
    
    pygame.display.flip()
    clock.tick(33)  # ~30 FPS

pygame.quit()
