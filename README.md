# Roundie
Coding Assignment TiledMedia

Flatworld
Imagine a flat surface divided into 8 squares in the x – axis (horizontal direction) and
8 squares in the z axis (depth direction). In total there are 64 squares in this
‘Flatworld’. Every square can be uniquely identified by its (x,z) coordinate.
An example of a 4x4 flatworld is given below:
Flatworld is inhabited by the “Roundy” species, a ball like creature that can only
move in one direction once they start rolling and cannot stop by themselves. They
can roll horizontally (keeping the same x coordinate), vertically (keeping the same z
coordinate) or diagonally. Roundies fall off the world and die if they reach the end of
it when moving. If Roundy A moves around and hits another Roundy B, this Roundy B
will get the impulse to move in the same direction as the Roundy A that hit it. Roundy
A will stop and take B’s square in the Flatworld.
Roundies are very nervous about being hit by other Roundies, they like to stay in
squares where they cannot be struck by other Roundies.


Challenge
Your challenge is as follows:
- Create a visual representation of Flatworld
- Upon start, the app randomly places 7 Roundies in this Flatworld, the user
should see a graphical representation. E.g. in a 4x4 grid with 5 roundies.
- The application should now allow the user to place one additional Roundie in a
free spot on the grid.
- When all 8 Roundies are in their designated squares, the program will identify
the unhappy Roundies that could potentially be hit by other Roundies. The app
will change the shape of these unhappy Roundies to show the user which
Roundies are unhappy.
- After the user selects an unhappy Roundy it will start moving towards one of
the Roundies that it can hit, following the behaviour identified above. After
every ‘hit’ the program should pause and identify which Roundie was hit and
then progress following the behaviour above until all movement has stopped.
Additional information:
- If anything is unclear, just ask by sending a mail to arjen@tiledmedia.com or
frits@tiledmedia.com
- Functionality is more important than looks. Don’t spend too much time on
making it visually appealing, it only serves to make it clear to the user what is
happening.
- Algorithmic efficiency is worth extra points
- Clean code is appreciated
- Code should be handed in as part of a Github repo / zip file and an executable
program should be attached (Linux or Windows) that will show the expected
functionality.
