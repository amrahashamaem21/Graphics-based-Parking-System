# Graphics-based-Parking-System
This is the graphical version of my console-based Parking Lot Management System. After finishing the console project entirely on my own, I wanted to try bringing it to life visually. I had never used SFML before, so I used AI assistance to learn and implement the graphics layer while working through the code to understand how each part functions.
The core parking logic (the parking_block class, memory management, slot operations)
is carried over from my original project. The rendering, event handling, and UI
components are where I was learning as I went.

The Working of this project
It gives you a window where you can see the parking block laid out visually. Each
slot is colour coded: green for empty, red for occupied, and yellow when selected.
You can interact with it through the panel on the right side of the screen.

You can park a car by typing a vehicle number and entering a row and slot, then
clicking Park Car. You can remove a car the same way. The search function highlights
the slot on screen and fills in the row and slot fields automatically. You can also
click directly on any slot in the grid and it will auto-fill the row and slot inputs
for you, which makes the whole thing feel a lot more natural to use. Resizing a row
and clearing a row are also available from the panel.

My learning through this project
The parking logic itself I was already comfortable with. The new things for me were
how SFML handles the window and event loop, how to draw shapes and text each frame,
and how to build basic UI components like input fields and buttons from scratch
without any library doing it for you. It took a while to get the input fields
working properly, especially the cursor and backspace behaviour.

The code is more complex visually than my console project but actually has fewer
features overall. The console version has smart allocation, block transfers, file
loading, and multi-block support. This version focuses on one block and makes the
interaction feel more immediate.

I want to be upfront: this project involved AI assistance, mainly for the SFML
parts I had not seen before. I went through the code carefully and understand how
it works, but I did not write every line independently the way I did with the
console version. If you want to see my core C++ and OOP work, the console parking
system repo is a better representation of that.

The execution of the Project:
You need SFML installed and linked to your project. The window is 1280 by 800.
You will also need a font file. The code currently points to a local path for
Nunito, so either place a font.ttf file in the same folder as the executable or
update the font path in main() to point to any .ttf font you have on your system.

The original Console Based Project:
The full-featured version of this project with multiple blocks, file loading,
smart allocation, block merging, and coordinate-based distance calculation is in
my other repository. That one is written entirely without AI assistance and covers
more of the OOP concepts I was working on for this course.
