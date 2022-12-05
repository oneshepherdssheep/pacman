# Pacman

## Introduction

This very simple/basic implementation of PACMAN.


## Design decisions

First of all, I want to describe how this PACMAN game was designed,
before going into the details of the implementation.

There are several distinct parts/modules/components in this PACMAN game.
Here is a listing of them all:
- **AI** : this module is responsible for the logic of the ghosts and the decisions they made when moving around
- **Assets** : this module contains all the assets, mainly the map.txt file
- **GameLogic** : this component contains the logic of the game, how to decide when the player wins or loses
- **GameObject** : this component defines all the GameObject of the game: Pacman, ghosts, food, walls, etc.
- **Graphics** : this component defines the means to draw the game on screen
- **Input** : this component handles the receiving and processing of user input (mainly typed characters)
- **Map** : this component is responsible for handling the Map, means to load it, to interact with it, etc.
- **Physics** : this component handles all the interaction, the movement between the objects of the game
- **Utils** : this component contains various types, functions, and procedures to perform different types of actions

By separating the game into several subcomponents, it's easier to reason about it, to change it, to develop it, and to
maintain it.

Always performing such work allows for developing with much ease.

## How was the development made?

The development was made component after component, module after module,
starting with the one which was the most important and also had the least amount of
dependencies.

It is much easier to start with the one which is the most independent because we will make
more progress than if we had to deal with two or three components simultaneously.

### 1. Map

The first component was Map because it was the most complex and the one that we were able to
develop without the others.

The first step was to open the **map.txt** file to check its structure.
The second step was to watch the videos indicated in the assignment.

By looking at those two elements, we can arrive at some conclusions:
1. The Map contains 2 spaces characters in between real spot
2. The PACMAN and GHOSTS don't move in-between spots but from spot to spot
3. The final Map (the one we play with) has surrounding walls

Let's take a look at each one of those elements individually.

#### Map layout

This is an essential element because it is not only in the map.txt but also in the accurate Map
drawn during the game.

This indicated that we had to take those into account.

So from one spot to another, we have two spaces.
This means that if we are at a spot (x,y)=(0,0), the next one on the same line is (x,y)(0,3).

It introduces the concept of line and column.
Basically, this is how I saw the Map:

(0,0)

    +-----------------------------------> x
    |
    |
    |
    |
    |
    |
    |
    |
    |
    |
    |
    v
    y

x coordinates represent the column, and y coordinates define the lines.

But another important of this layout is the dimensions.
By looking at the file _map.txt_, we can see that we have: 9 LINES and 9 COLUMN (with real content) and each COLUM is separated by 2 SPACES of usable characters (I purposely omitted the \n terminating the LINE because we will not import such character into the in-game Map).

So if we take all of this into account, a LINE contains: 9+(9-1)*2=9+16=25 characters.
So we have 25 characters per line to import from the map.txt file.

And if we look at the final Map (the one used during the game) we can see that we will have the following:
- LINE: 11 (9 from the map.txt + 2 Walls) characters separated by 2*(11-1) spaces plus 1 new line character (this time we need it because it serves during the display) = 32 characters per line
- COLUMN : 9 Line for the real map + 2 lines for outer wall = 11 characters.

So basically, our Map can be described as a Matrix under the form Map[11][32];

#### Movement on the Map by Pacman and the Ghosts

Understanding the layout of the Map is essential because it allows us to know
see how our movable element evolves in this setting.

Pacman and the ghosts can move UP, DOWN, LEFT, and RIGHT.
Each movement affects one of their coordinates.

Now we can see how each movement affects the coordinates.

- UP: affect the y coordinate negatively. An element at (x,y) moving UP arrives at (x,y-1)
- DOWN: affect the y coordinate positively. An element at (x,y) moving DOWN arrives at (x,y+1)
- LEFT : affect the x coordinate negatively. An element at (x,y) moving LEFT arrives at (x-3,y)
- RIGHT : affect the x coordinate positively. An element at (x,y) moving RIGHT arrives at (x+3,y)

Knowing this, we can then prepare our methods to move elements around.
But there is still one important point to take into account, boundaries.

Because the walls limit Pacman and Ghosts, we need to make sure that they don't
traverse the walls.

This is why in the assignment, we have the function **isWall** to write to anticipate
if a particular move encounters a wall or not.

#### Reading _map.txt_

We have already established that the Map could be described as the following Matrix: Map[11][32].
So we will have first to initialize our Map to have the outer walls and fill the inside with spaces.

Then after that, we will read from map.txt and will have to only copy the element to the inside of our Map.

So the technique here will be to read each line of map.txt, and for each line, get actual usable characters such as 'P', 'W', 'G', and '.'.
As said, we will only be reading 25 characters per line, and as soon as we have reached 25, we can consider that another line has started
and keep repeating the process until we have finished reading the file.

In the end, we will have a map containing the following:
- the outer walls
- the content of the file map.txt

#### Finalization

But even though, as it is, the Map is good enough, we still have one last thing to do.
Extract the movable elements.

Because Ghosts and Pacman will move around during the game, we don't want to have them static but be able to move them dynamically.

This will be important for the drawing (talk about it later).

So we need to extract the movable elements (Ghosts and Pacman) from the Map but also store the position of those elements because it
corresponds to the initial part of Pacman and the Ghosts.

So we will have a mechanism that will allow us to :
1. extract the coordinates of the Pacman and the Ghosts
2. store those positions on data corresponding to the Pacman and Ghosts we will move around
3. remove those from the Map.

Once we have done that, we can move to the next step, which is linked to this last step: GameObject.

### 2. GameObject

GameObject is a term that corresponds to an object placed in the game.
For this assignment, I only considered: Pacman and Ghosts as GameObject.
I could have also considered the Walls and the Food as GameObject, but it would have been more work.

#### Pacman

So Pacman is defined by the coordinates of its current position (x,y).
But we will also have the coordinates of its last position (x,y).

I anticipate this here because when the Ghosts follow Pacman, they need to be placed just behind him all the time.
So we need to store such information.

So basically, Pacman will have the following:
- coordinates of its current position
- coordinates of its previous position

And of course, when initializing the game, its current position will be initialized with the element read from the Map.

#### Ghosts

The coordinate of their current position also defines ghosts, but they will also have other elements.
Ghosts have two distinct behavior, as we can see in the video.
They can CHASE the Pacman if they see it or act NORMAL by moving around according to their own will (a basic AI).

So on top of the current position, we will also have the current state of the Ghost: CHASE or NORMAL.

We will also have another element to help us determine where to go.
Because of the video, I've noticed that when a Ghost moves in a particular direction, it doesn't change until it encounters
a wall (I'm talking here about the NORMAL case, of course).

So we needed to keep track of the direction we were heading to continue go in this direction until the Ghost hit
the wall and then decide to do something else (turn around or move to the side).

So if we summarize, a Ghost is characterized by the following:
- coordinates of its current position
- its state (NORMAL or CHASE)
- the direction it is heading toward

That's all we can say for the GameObject.

### 3. Graphics

Okay, now that we have two components in place, let's try to draw the Map and the movable elements.
But there is one crucial element to consider here that we can see in the video.

When Pacman moves around, if he encounters food, he eats it, and the food is removed from the Map.
But when a Ghost encounter food, nothing happens; but the Ghost can be seen to be on top of it for a moment and
after the Ghost leaves that location, we see the food again.

So we need to know how to handle this situation.

The proposal I had was to have two maps.

One Map will keep the element as they are in life, and the other will be constructed for the sole purpose to
be displayed.

This way, we can have the drawn Map have the Ghost on top of the food without any issue because the real Map
will still have the real food placed on it.

This is a little trick that I have used for this drawing method.

So Basically, the draw method will:
- create a copy of the actual Map
- place Pacman and the Ghost in it
- displays it

So now the Graphics is done, we can move to something more fun, the Input part.

### 4. Input

The input part is pretty straightforward, we read the character typed by the user and interpret it as
a command to Pacman; either UP, DOWN, LEFT, or RIGHT.

I added a QUIT command, but that's not the assignment's focus.

The focus of the assignment is that when we read a character, we interpret it and decide to move in a particular
direction or not move.

The decision to move is based on the location of the Pacman.
If he is in front of a Wall and we go UP, nothing happens.

So to handle this, we need to have a sense of our PHYSICAL World; thus, we can head toward the Physical component.

### 5. Physical

The physical component will handle all the move action and is also responsible for handling potential collisions
and stuff like that.

So this Physical component will need to have the information about Pacman, his World, and the Ghost around him.
Of course we will also apply what we learn from above concerning the movement of the movable objects (+/-1 to y when moving DOWN/UP
and +/- to x when moving RIGHT/LEFT.

With that in account, we could quickly write our methods to move elements around.
It is true, at least for Pacman, because we control it ourselves.
But what about the Ghosts?
Because an "AI" controls it, we need to define how this AI will decide what the Ghost should do.

That's why we can move to the AI component.

### 6. AI

The AI component will be a simple machine.
We want to keep things as simple as they have been presented in the video.

To do such a thing, we will need to devise a plan to move the Ghosts and update their state.

#### Update Ghosts state

To update the Ghost's state, we need to consider their proximity to Pacman.
As soon as they are close to Pacman, the goal is to switch the CHASE mode.

When the Ghosts are no longer closer, we can return to NORMAL.

Unfortunately, in our case, Pacman cannot outspeed the Ghosts, so it is almost guaranteed that when a Ghost
follows you, He will follow you until the end of the current party.

#### How to decide where to move to?

For the NORMAL mode, however, we have to be cautious.
The steps I have considered are the following :
- Find out what are the possible direction we take (UP, DOWN, LEFT or RIGHT)
- Decide randomly on one direction
- Stick to that direction until we hit a wall
- And repeat the process

This way, we will be sure to have a coherent behavior (move toward a fixed direction until we cannot and then switch).

It will make our game much more interesting.

So now let's take a look at the last components.

### 7. Utils

This module is more a less a melting pot of various things that almost everyone can use.
We can have here the definition of some common types that are used everywhere or functions
that we could use without them being tied to a specific component.

The rule is, if it is not specific to another module, put it in Utils.

### 8. Assets

Finally, the assets module will only contain the map.txt file.
Later, if inventive, we can create a mechanism to switch Maps to have other terrains/mazes.

But that is out of the scope of this assignment.

With all those components clearly described, we can approach the implementation phase more confidently.

## Implementation

I will only explain a few things here because everything can be explained by voice while looking at the code.
But I'm going to stress a few important things.

### Code organization

This is an essential part of the success of developing such projects.
If the code is organized, it will be easier to work and maintain everything.

That's why I created a separate folder for each component.
It allows us to keep things where they are below and avoid confusion.

### Code writing

Because we use C, we don't have a lot of ways to segregate or group things neatly together, but we can still do
something about it.

I decided that on top of having elements put in their respective directories, I would add a prefix to the names
of the functions involved (GRAPHICS_xxxx).

So that when calling a particular function, you don't just type **printMap**, for example but rather **GRAPHICS_printMap**.
It's true that it can make function names very long, but better be clear and long than unclear and short.

### Defensive coding

I tried to apply this everywhere I could.
The principle is not just to assume things are going well all the time but rather the contrary.

So to apply defensive coding, you could for example:
- check the return of the functions (even those that are trivial)
- always check boundaries when dealing with arrays of stuff
- always check if a pointer is NULL or not before using it.
- etc.

There are many ways to keep letting bugs silently live in your code (even though it doesn't lead to an immediate crash/bug).
And as much as you can do that, do it; it will save you later on.

### Naming

Naming things is very difficult when dealing with software.
Sometimes we are lazy and rely on characters layer **i**,**j**,**k**, or **n** to define a variable.
But by doing this, you will eventually lose track of who is who and who is doing what.

So to avoid falling into this pit, better use names as explicitly as possible.
It is the case for variables but also for functions.

I tried to think about good names, and I believe it is an essential part of having a code base that is easy to understand,
easy to maintain, simple, and **elegant**.



