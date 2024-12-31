# Cursinger
A simple hardware cursor management plugin for unreal

## Why

Unreal allows you to overwrite the system hardware cursors on Windows. The problem with this is that there are only 13 cursors to replace, which might not be enough for cursor heavy games like RTS games.
Another problem is that the cursor types like EMouseCursor::TextEditBeam are confusing when you use them in your game in another context.
If you set EMouseCursor::Hand for units to attack it feels just wrong.

Cursinger uses Gameplay Tags to manage hardware cursors. You can use as many as you want. They all just overwrite EMouseCursor::Default in the background.

Managing the cursors like this provides a way more comprehendable way to refer to the cursors.

Example:

- Hovering above enemy - Cursor.Enemy.Interact
- Attack enemy - Cursor.Enemy.Attack
- Hovering above dead enemy - Cursor.Enemy.Dead

The plugin is based on a world subsystem that manages a cursor stack. You can push a cursor to the stack or pop it. Pushing a cursor returns a handle that makes it possible to switch a cursor within the stack.

The plugin is very simple and a work in progress. It's used in a single stealth tactics prototype and works well in that context.

