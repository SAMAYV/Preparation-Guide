from enum import Enum

class GameState(Enum):
    IN_PROGRESS = 1
    WON = 2
    DRAW = 3

class Board:
    def place_mark(self, row: int, col: int, mark: str) -> bool:
        # Place mark logic
        return True

    def check_win(self, row: int, col: int) -> bool:
        # Check win logic
        return False

    def is_full(self) -> bool:
        # Check if board is full
        return False

class Player:
    def __init__(self, mark: str):
        self.mark = mark

    def get_mark(self) -> str:
        return self.mark

class Game:
    def __init__(self):
        self.board = Board()
        self.player_x = Player("X")
        self.player_o = Player("O")
        self.current_player = self.player_x
        self.state = GameState.IN_PROGRESS

    def make_move(self, row: int, col: int) -> bool:
        # Coordinates board, player, and state logic
        # Caller doesn't need to understand internal details
        if self.state != GameState.IN_PROGRESS:
            return False
        if not self.board.place_mark(row, col, self.current_player.get_mark()):
            return False

        if self.board.check_win(row, col):
            self.state = GameState.WON
        elif self.board.is_full():
            self.state = GameState.DRAW
        else:
            self.current_player = (
                self.player_o if self.current_player == self.player_x
                else self.player_x
            )
        return True

# Usage - simple interface hides all the coordination
game = Game()
game.make_move(0, 0)
game.make_move(1, 1)

