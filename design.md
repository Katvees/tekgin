# Tekgin
A library to for making text adventure games.


## Scope
The engine will not have an editor, but is manually programmed using C++ with the libraries provided by the engine.

There will be a possibility to run the game in terminal or in a GUI with bundled fonts

## Structure
Each character (player, NPC, enemies, etc.) is based on the same class (`Charcter`) and are convertible and share mostly the same structure.
All permanent (those that persist between scenes) characters have a unique ID that is defined by the order of definition. The properties that have changed are loaded from save files.
Transient characters are destroyed after the player moves to another scene, unless they have a residence set in any scene.
The residence of a character is where it exists in the world. All characters are self-aware of their residence and the specific location in the node.
In addition to the characters themselves knowing where they are, the scenes also know the location of each of its residents. Residents are also searchable from a map containing all characters and their residence scene.
The map is a 2d array with each position containing a scene (or a blocker).
Each scene may have locations (subscenes), interactable, residents, and hidden properties and elements.
Some properties every scene and subscene has are: owner (faction or character), events, and name
