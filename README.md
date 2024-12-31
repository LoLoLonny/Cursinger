# Cursinger
A simple hardware cursor management plugin for Unreal Engine.

## Why

Unreal Engine allows you to overwrite the system hardware cursors on Windows. However, there are only 13 cursors to replace, which might not be enough for cursor-heavy games like RTS games. Another issue is that cursor types like `EMouseCursor::TextEditBeam` can be confusing when used in different game contexts. For instance, using `EMouseCursor::Hand` for units to attack feels just wrong.

Cursinger uses Gameplay Tags to manage hardware cursors, allowing you to use as many as you want. They all overwrite `EMouseCursor::Default` in the background, providing a more comprehensible way to refer to the cursors.

### Example:

- Hovering above enemy: `Cursor.Enemy.Interact`
- Attacking enemy: `Cursor.Enemy.Attack`
- Hovering above dead enemy: `Cursor.Enemy.Dead`

The plugin is based on a world subsystem that manages a cursor stack. You can push a cursor to the stack or pop it. Pushing a cursor returns a handle that allows you to switch a cursor within the stack.

How cursors relate to a cursor texture is defined with a DataAsset (`CursingerDefinitionAsset`) that can be set in the project settings. There, you can register a file path with a tag. The file path must point to a file in your content directory, without specifying the file extension, as hardware cursors don't use `.uasset` files. Check the [docs for further info](https://dev.epicgames.com/community/learning/tutorials/lwXR/unreal-engine-full-process-of-hardware-cursor-setup#whyuseahardwarecursor).

The plugin is simple and a work in progress. It's currently used in a single stealth tactics prototype and works well in that context.
