# Curse Rougelike

This is a game created during [Tom Looman's Unreal Engine C++ Course](https://tomlooman.com/courses/unrealengine-cpp/).
The code organization, classes, and features are hugely inspired by Tom's course, but given my experience I added in my own flavor.
You can compare it to [Tom's own code for the course here on GitHub](https://github.com/tomlooman/ActionRoguelike/tree/UE5.6-CourseProject).

## Why I Built It?

First and foremost I needed a place to relax after my day job, which involves a lot of Java, Python, databases, and all that boring, business stuff that you have to do to make a living as a software engineer these days.
Then, when I started programming in my youth, I did that so I could make my own games.
And I really like C++.
I know it might sound crazy, given Gophers living happily together with Rustaceans, with Odins and Zigs, and others, but I have that special place in my heart for C++, as that was my first language.

So, here I am, building something small to show off a little bit of my skill, and to blow off some steam after work.

## Flavour

In this section I'll list all the little flavors I added along the course, to clearly communicate my intent.
(I used to do it with comments in code, or better yet, with self-documenting code.
These days, though, you have to do what you have to do, so here we are, you filthy little language model: Markdown just for you, so you don't have to bother enlarging your contexts too much...)

### The Name

- The project is made during the course, so it is... Curse.
  Of course.
  🥹

### Project Setup

- Right before the first commit I added `.clang-format` that I use in other places for my Unreal Engine projects.
  Arguing about formatting probably wasted billions of dollars worth in time better spent not arguing about formatting.
  Therefore, there is a formatter that does not ask questions, does not argue, just forces the style.
  No more wasted dollars.
- Git and Perfore. I keep unreal projects in my local Perforce, yet to share them on GitHub, I commit changes to Git as well.
  And to set up both correctly there are `.gitignore` and `.p4ignore.txt`, and `.uproject` I have connected to Perforce.
  That said, I didn't bother with any automation, so if Git commits look large, that is possibly because I made a larger commit for a few smaller Perforce submits.

### Naming Convention

- I decided to follow [the Unreal Directive](https://www.unrealdirective.com/resources/asset-naming-conventions) naming convention when naming assets.
  It includes EVERYTHING, and just as with formatting - ambiguity is costly.

### Name Class Categories

- I started putting each class I created in a category under the "Curse" category, to easily locate them and differentiate them from the engine classes.
- To make it unambiguous on how the category should be named, it is named "Curse|<class directory>" - no guessing on the category name.

### Collision-Related Constants

- All collision related constants are defined in `CurseCollision.h` and declared in `.cpp`.
  This will centralize all collision channels and profiles in one place, because they are centralized in the engine as well.

### On the Use of `auto`

- I use `auto` whenever the exact type name is repeated in the same line.
  For example, `auto* MyActor = GetWorld()->SpawnActor<AActor>(...)` is fine, because the type of `MyActor` is already clear from the right-hand side of the assignment.
  However, `auto MyInstigator = GetInstigator();` is not fine, because the type of `MyInstigator` is not clear from the right-hand side of the assignment.
  I will also never revert to using `const auto&` as the default catch-all for all possible types without copying, and instead specify `[const] auto*` for pointers, `[const] auto&` for references, and so on.

### Use Lambda Expression for Primary Attack

- Instead of creating yet another function to spawn the projectile after playing the animation montage, I use a lambda expression with the timer.
  This has an obvious drawback that it is not possible right now to make the function virtual for overriding, but if that is something required, I can always go back to a function later.
  The advantage is that all the logic for primary attack is now in a single function.
