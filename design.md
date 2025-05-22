# Tekgin
A library to for making text adventure games.


## Scope
~~The engine will not have an editor, but is manually programmed using C++ with the libraries provided by the engine.~~
The engine will be split into a runtime and a "pseudo-editor". The editor parses configuration files written for the game and compiles them into a database and executable for the game using the runtime code.

There will be a possibility to run the game in terminal or in a GUI with bundled fonts

## Structure
Each character (player, NPC, enemies, etc.) is based on the same class (`Character`) and are convertible and share mostly the same structure.
All permanent (those that persist between scenes) characters have a unique ID that is defined by the order of definition. The properties that have changed are loaded from save files.
Transient characters are destroyed after the player moves to another scene, unless they have a residence set in any scene.
The residence of a character is where it exists in the world. All characters are self-aware of their residence and the specific location in the node.
In addition to the characters themselves knowing where they are, the scenes also know the location of each of its residents. Residents are also searchable from a map containing all characters and their residence scene.
The map is a 2d array with each position containing a scene (or a blocker).
Each scene may have locations (subscenes), interactable, residents, and hidden properties and elements.
Some properties every scene and subscene has are: owner (faction or character), events, and name

## Saving and loading the game
The save is a hierarchy of files that can be queried using the file names, which correspond to the object's UUID, which are fetched on access if the object is not yet loaded. Objects that go out of scope may be unloaded depending on the object to save memory (having the whole world loaded into memory at all times isn't really optimal or needed). This also means the player can edit the save as they wish, but a checksum could be implemented to check if the save has been tampered with, though why should the player be limited like that in a single player game?
