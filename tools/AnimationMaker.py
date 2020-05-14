# coding: utf-8

import sys
import pygame

# constants
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480


class Main:
    def __init__(self, screen):
        self._screen = screen
        self._running = True

    def handleEvents(self):
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                self._running = False

    def update(self):
        pass

    def render(self):
        pass

    def draw(self, image, position):
        self._screen.blit(image, position)

    def run(self):
        while self._running:
            self.handleEvents()

            self.update()

            self.render()
            pygame.display.flip()


def main(*args):
    pygame.init()

    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("SmallGameLibrary - AnimationMaker")

    # image = pygame.image.load("monimage.png").convert_alpha()
    # pygame.display.set_icon(image)

    app = Main(screen)
    app.run()

    pygame.quit()
    return 0


if __name__ == '__main__':
    sys.exit(main(*sys.argv[1:]))