Prerequisites: [Introduction to Game Theory](./intro.md)

This article discusses [partizan combinatorial games](./intro.md#partizan-combinatorial-games).

Unlike impartial combinatorial games where the available moves depend only on the position, in partizan games, the available moves for a player also depend on which player is to move. This fundamental difference makes partizan games more complex and difficult to analyze than impartial games.

## Notation

In impartial games, a position is denoted by a set of its successors. For partizan games, we need more precise notation to capture which player has the move.

???+ info "Notation"
    In this article, we use the notation:
    
    -   $G^L$: The set of positions that the Left player can move to from position $G$.
    -   $G^R$: The set of positions that the Right player can move to from position $G$.
    
    A position $G$ is then denoted as $G = \langle G^L \mid G^R \rangle$.

With this notation, an impartial game $*n$ can be written as $*n = \langle *0,*1,\cdots,*(n-1) \mid *0,*1,\cdots,*(n-1) \rangle$, meaning both Left and Right have the same available moves.

### Examples

???+ example "Example: Chess"
    In chess, from a given position, the set of moves available to White may differ from the set of moves available to Black. For instance, White can move pawns forward, while Black can move pawns backward (from White's perspective). This asymmetry is precisely what makes chess a partizan game.

???+ example "Example: Hackenbush"
    [Hackenbush](https://en.wikipedia.org/wiki/Hackenbush) is a classic example of a partizan game. In the simplest version, a stem with colored edges (red for Left, blue for Right) is attached to the ground. Left can cut and remove red edges, while Right can cut and remove blue edges. When an edge is removed, all edges not connected to the ground are also removed. The player who makes the last move wins.

## Outcome Classes

In impartial games, positions are classified as P-positions (previous player wins) or N-positions (next player wins). For partizan games, the classification is more nuanced because the player to move matters.

???+ abstract "Outcome Classes"
    A position $G$ can fall into one of four outcome classes:
    
    -   **Left wins** (symbolized $\mathcal{L}$): Left wins regardless of who moves next.
    -   **Right wins** (symbolized $\mathcal{R}$): Right wins regardless of who moves next.
    -   **First player wins** (symbolized $\mathcal{N}$): The player who moves first wins.
    -   **Second player wins** (symbolized $\mathcal{P}$): The player who moves second wins.

???+ note "Theorem"
    For a position $G = \langle G^L \mid G^R \rangle$:
    
    -   $G \in \mathcal{L}$ if and only if $G^R = \varnothing$ and for all $G^L \in G^L$, $G^L \in \mathcal{L}$.
    -   $G \in \mathcal{R}$ if and only if $G^L = \varnothing$ and for all $G^R \in G^R$, $G^R \in \mathcal{R}$.
    -   $G \in \mathcal{N}$ if and only if ($G^L \neq \varnothing$ or $G^R \neq \varnothing$) and not ($G \in \mathcal{L}$ or $G \in \mathcal{R}$ or $G \in \mathcal{P}$).
    -   $G \in \mathcal{P}$ if and only if for all $G^L \in G^L$, $G^L \in \mathcal{R}$, and for all $G^R \in G^R$, $G^R \in \mathcal{L}$.

??? note "Explanation"
    -   A position where Right has no moves and all Left's options lead to Left-winning positions is itself Left-winning.
    -   A position where Left has no moves and all Right's options lead to Right-winning positions is itself Right-winning.
    -   A position that is neither Left-winning, Right-winning, nor Second-player-winning, but has some move available, is First-player-winning.
    -   A position where all Left's options are Right-winning and all Right's options are Left-winning is Second-player-winning.

## Game Comparison and Ordering

In impartial games, the concept of equivalence is used. For partizan games, we need a notion of ordering to compare games.

???+ abstract "Game Ordering"
    For games $G$ and $H$, we say $G \ge H$ if Right cannot win when playing $H$ but can win when playing $G$, assuming both players have perfect information.
    
    More formally, $G \ge H$ if and only if for all $G^R \in G^R$, we have $G^R \not< H$, and for all $H^L \in H^L$, we have $G \not< H^L$.

The intuition is that $G \ge H$ means $G$ is at least as favorable to the player whose turn it is as $H$ is.

### Properties

???+ note "Properties"
    -   **Reflexivity**: $G \ge G$ for all games $G$.
    -   **Transitivity**: If $G \ge H$ and $H \ge K$, then $G \ge K$.
    -   **Antisymmetry**: If $G \ge H$ and $H \ge G$, then $G = H$ (where equality means $G \ge H$ and $H \ge G$).

With this ordering, the set of all partizan games forms a [partially ordered set](https://en.wikipedia.org/wiki/Partially_ordered_set).

## Game Sums

The sum of partizan games is defined similarly to impartial games, but the asymmetry must be preserved.

???+ note "Sum of Games"
    The sum of games $G$ and $H$ is defined as:
    
    $$
    G + H = \langle G^L + H, G + H^L \mid G^R + H, G + H^R \rangle.
    $$
    
    In each move, the player chooses one of the two component games and makes a move in it.

### Simplified Nim

One of the simplest non-impartial games is **simplified Nim** (also called **Dawson's Kayles** in some contexts):

???+ abstract "Simplified Nim"
    There are two piles of stones. Left can only remove stones from the first pile, and Right can only remove stones from the second pile. Each player must remove at least one stone when they move. The player who cannot move loses.

This game demonstrates how partizan games differ from impartial ones. The analysis requires considering who has the move.

## Temperature and Cooling

A central concept in the theory of partizan games is **temperature**, which measures how urgent a position is.

???+ abstract "Temperature"
    The temperature of a position $G$ is denoted $t(G)$. It is defined through the concept of **cold games** and **heated games**.
    
    A game is called **cold** if its temperature is $0$. A game is called **hot** if its temperature is positive.

The detailed definition of temperature involves analyzing the game tree and is beyond the scope of this introductory article. However, intuitively, hot positions are those where there is significant pressure to move, while cold positions allow for more leisurely play.

## References

-   [Partizan game - Wikipedia](https://en.wikipedia.org/wiki/Partizan_game)
-   [Combinatorial Game Theory - Academic Resources](https://www.gametheory.classicssoftware.net/)
-   [Winning Ways for Your Mathematical Plays](https://en.wikipedia.org/wiki/Winning_Ways_for_Your_Mathematical_Plays)
