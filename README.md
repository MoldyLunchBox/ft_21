21 is part of a bigger project called 42. essentially what it is is a remake of shell coded from scratch. 
the parsing and execution and the read line plus a few builting commands like echo and cd are allcoded from scratch. when the user starts to type. the program takes
the input and stores it in a buffer and checks whether the input was a key pressed or just text. for example if the user presses the left arrow key. the program
will check the input against the left key condition which will be true in this case. so the program then will execute the functions that calculate the position of 
the cursor and moves the cursor once to the left. same thing hapens when the user presses enter. the line gets sent to the parsing and execution function which 
determins how it will be executed.