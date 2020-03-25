# Text-Adventure
This is a variation of the game "Betrayal at House on the Hill". Some of the rules in the original board game do not apply and
the game is implemented as a text adventure game.

When starting the game, the charater starts in the starting room with no other room initialized on the "board". There are a total of 7-8
rooms that are shuffled randomly and pushed onto a stack. The avatar can go in 6 directions: North, East, West, Up, and Down, but cannot go 
South. When the avatar goes in a valid direction, if that direction is unexplored, a new room is popped from the stack and set to the
direction of the room. Keep in mind that the game has non-euclidean mechanics. For example, if avatar starts in starting room and goes 
East, Up, West, then Down, the avatar will not end up back into the starting room. To win, you need to have two items in you inventory
(there's a flashlight and crowbar in the game), pass through an omen room, pass through an event room, and end up back at the start. An omen
room is just a room that has a Omen in it. This is implemented as a boolean in the game. It does nothing. An event room is a room that contains
an event in which, when true, will cut off the room from the rest of the game board and have the north direction of the room point towards the 
startroom. The avatar dies when you keep on exploring unexplored areas and there are no more rooms on the stack.

