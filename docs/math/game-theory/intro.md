author: cutekibry, woruo27, Backl1ght, c-forrest

**Game theory** is a branch of economics that primarily studies the behaviors of individuals with competitive or antagonistic properties under specific rules. Game theory focuses on the expected and actual behaviors of individuals in a game and studies their optimal strategies.

In layman's terms, game theory mainly studies how multiple players in a game choose their strategies.

## Basic Concepts

This section briefly introduces some common concepts in game theory.

### Cooperative / Non-cooperative Games

A **cooperative game** is one in which participants can form alliances and cooperate. In such games, individual non-cooperative behavior is often punished by some external mechanism. In contrast, in a **non-cooperative game**, no such mechanism exists, so participants either cannot form alliances or can only maintain cooperation through credible threat mechanisms.

Compared to cooperative games, non-cooperative game research is more systematic and mature. All games discussed in this article are non-cooperative games.

### Symmetric / Asymmetric Games

In a **symmetric game**, different participants receive the same payoff when making the same move, meaning the payoff depends only on the move itself and not on the identity of the player. Games that do not satisfy this condition are called **asymmetric games**.

### Zero-sum / Non-zero-sum Games

Main page: [Zero-sum Games](./zero-sum-game.md)

A **zero-sum game** is one in which the sum of payoffs for all participants is always zero, regardless of what actions each participant takes. Typically, zero-sum games involve two participants, where one participant's gain is necessarily the other participant's loss. Conversely, **non-zero-sum games** allow multi-party win-win or lose-lose scenarios, including **positive-sum games** and **negative-sum games**.

### Simultaneous / Sequential Games

In a **simultaneous game**, all participants make decisions simultaneously without knowing others' choices. Rock-paper-scissors is a typical example of a simultaneous game. Such games are often represented with payoff matrices and usually do not involve the concept of time.

The opposite is a **sequential game**, where participants act in turn. Note that later players must be able to observe at least part of the earlier players' actions; otherwise, the order of play would be meaningless. Sequential games are typically represented using game trees.

### Perfect / Imperfect Information Games

**Perfect information** means that at any point when a participant makes a decision, they have complete knowledge of all previous events, including the game's initial state. Games like chess and go are examples of perfect information games; mahjong and poker are imperfect information games because players cannot see others' hands. Perfect information is typically used to describe sequential games; since players in simultaneous games cannot know each other's upcoming moves, simultaneous games are generally considered imperfect information games.

### Complete / Incomplete Information Games

**Complete information** means that all participants have complete knowledge of the game's structure itself (including each player's available actions and final payoffs), and this information is common knowledge. The opposite is incomplete information games, where some elements of the game (such as the opponent's available actions or payoff function) are unknown to the participants.

It is worth noting that "complete information" and "perfect information" are two independent concepts and neither subsumes the other. For example, mahjong is a complete information but imperfect information game because its rules and payoffs are public, but card information is not transparent; whereas some games with hidden objectives but fully observable actions belong to perfect information but incomplete information games.

## Combinatorial Game Theory

In algorithm competitions, the most common type of game is a **combinatorial game**. This term usually refers to games that are difficult to solve due to their enormous state spaces. Because general combinatorial games are quite complex, combinatorial game theory mainly focuses on the following types: two-player turn-based games with perfect information and no random elements. Chess and go are typical combinatorial games.

### Impartial Combinatorial Games

Main page: [Impartial Combinatorial Games](./impartial-game.md)

An **impartial game** is a combinatorial game satisfying the following conditions:

-   In any given state, all participants have exactly the same available moves, which depend only on the current state and not on the player's identity;
-   The same state in the game cannot be reached more than once, the game ends when a player cannot make a move, and the game must end in a finite number of moves without a draw.

Impartial games are always symmetric games.

### Partizan Combinatorial Games

Main page: [Partizan Combinatorial Games](./partizan-game.md)

The opposite concept to impartial games is **partizan games**, where the available moves for a participant in a given state depend on their identity. Most board games (such as chess, Chinese chess, go, Gomoku, etc.) are partizan games because participants can only move their own pieces.

### Normal / Misère Games

In combinatorial games, the usual winner is the last player to take an action before the game ends. This is called a **normal game**. The opposite is a **misère game**, where the last player to take an action before the game ends is the loser.

Both impartial and partizan combinatorial games can be normal or misère games.

## References

-   [Game theory - Wikipedia](https://en.wikipedia.org/wiki/Game_theory)
-   [Combinatorial game theory - Wikipedia](https://en.wikipedia.org/wiki/Combinatorial_game_theory)
-   [Impartial game - Wikipedia](https://en.wikipedia.org/wiki/Impartial_game)
-   [Misère - Wikipedia](https://en.wikipedia.org/wiki/Mis%C3%A8re)
