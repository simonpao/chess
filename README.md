# Command line chess game

Simple command line chess application. Currently only supports two player games, as there is no AI implementation.

## Build

Compile all source code using Makefile.

```bash
$ make
$ ./chess.out
```

## Board

The chess board prints after every turn showing the current state of the chess board. It will print as an 8x8 grid with columns labeled A-H and rows labeled 1-8. Unoccupied spaces are marked with a hyphen (`-`).

```
       A B C D E F G H
 
   1   R K B X Q B K R   1
   2   P P P P P P P P   2
   3   - - - - - - - -   3
   4   - - - - - - - -   4
   5   - - - - - - - -   5
   6   - - - - - - - -   6
   7   p p p p p p p p   7
   8   r k b q x b k r   8
   
       A B C D E F G H
```

## Movement

Players move pieces by entering the current coordinates and the intended coordinates. For example, to move their left knight, player two would enter `8B 6C`. This translates to: `move the piece in row 8 column B to row 6 column C`.

```
    A B C D E F G H 

1   R K B X Q B K R   1
2   - P P P P P P P   2
3   - - - - - - - -   3
4   P - - - - - - -   4
5   - - - - - - - -   5
6   - - - - - - - -   6
7   p p p p p p p p   7
8   r k b q x b k r   8

    A B C D E F G H 
Player two, enter move: 8B 6C

    A B C D E F G H 

1   R K B X Q B K R   1
2   - P P P P P P P   2
3   - - - - - - - -   3
4   P - - - - - - -   4
5   - - - - - - - -   5
6   - - k - - - - -   6
7   p p p p p p p p   7
8   r - b q x b k r   8

    A B C D E F G H 
```