Project History
==========
The aim of this project is to provide a simple way of using Allegro 5 library. The idea was born when some programming teachers
from La Salle Barcelona decided to ask their students to implement a videogame as a mandatory exercice to pass the subject. Those 
teachers spent time deciding which graphics library to use. Finally, they chose to use Allegro 5 because of it's native simplicity. However,
they realised that a simplification of Allegro 5 must be implemented because many of the students from Programming I have never coded before
and some concepts from Allegro would sound very difficult for them. That's why LS_Allegro was born and since then this module has
been used by all the students of Programming I in La Salle Barcelona.

Developers and Maintainers
==========================
The developer of this project is Albert Lloveras (assistant teacher from La Salle) but other teachers, students and external coders have contributed to it.
The idea is to try to keep this project alive as much as we can because videogame development is always a good way to motivate
students to learn programming skills.

How to use
===========================
The project is cross-platform so it can be used under Windows, MacOS and Linux platforms. To work with this interface you should have installled Allegro 5 previously on your computer and follow those steps below:

Clone the repository

>git clone https://github.com/alloveras/LS_Allegro.git

Copy the LS_allegro.c and LS_allegro.h files to your videogame project.
 
Add the following flags to the compiler linker

##Linux / MacOS
  
  > allegro
  > allegro_main
  > allegro_primitives
  > allegro_color
  > allegro_ttf
  > allegro_image
  > allegro_acodec
  > allegro_audio
  > allegro_memfile

##Windows
    
  >liballegro-5.0.10-monolith-mt-debug.a

##Contact

If you have any doubts or questions feel free to send me an email!

> Albert Lloveras Carbonell
> alloveras@salleurl.edu

