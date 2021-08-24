# Losing chess AI

Two AI that plays the game losing chess, a variation of chess where the object is to lose all your pieces to an opponent who is forced to capture whenever possible

## AI 1 - random thinker

* If there are no capturing moves, this AI will perform a non capturing at random.

* If there are several capturing moves, the AI will perform one of them at random.

* If there is a pawn promotion, a random piece will be selected.

## AI 2 - thinks one step ahead. but defaults to random

* If there are no capturing moves

    * Check if any non-capturing move will force a capturing move for the opponent.

    * If not, play a random move.


* If there are several capturing moves
    
    * Check if any capturing move will force a capturing move for the opponent

    * If not, play a random capturing move.


* If there is a pawn promotion
    
    * If possible, pick a piece that can not capture on its next move.

    * If not possible, promote to a random piece.
