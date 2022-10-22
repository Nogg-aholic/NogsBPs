# NogsBPs

**This tool now maintained by Robb#6731, you can get support on the [Discord](http://discord.gg/zqp6U7Y7Nu)**

This is a set of editor utilities, not a game mod, that can be used to vastly expedite creation of various content for Satisfactory.

You may also find the [Icon Generator](https://docs.ficsit.app/satisfactory-modding/latest/CommunityResources/IconGenerator.html) editor plugin useful.

## Initial Setup

To use, put this in the Plugins directory of your project, regenerate visual studio files, and build development editor. That process is covered in the [main modding docs](https://docs.ficsit.app/satisfactory-modding/latest/index.html).

**Make sure you have the dependency plugin '[JsonStructs](https://github.com/Nogg-aholic/JsonStructs)' also written by Nog, else the plugin will not be able to compile.**

**Make sure you also have the base Unreal plugin "Editor Scripting Utilities" enabled, else you will get errors about nonexistent nodes or missing pins.**

## Tree Viewer (and editor)

This tool allows you to view and arrange tree nodes into research trees without the immense fiddling of manually setting node and road indexes and such.

To use it, launch the utility from the right click menu, then select a tree asset in the editor, and press Load within the UI. You can use mousewheel to scroll and left mouse to pan. You can grab nodes to move them around, and click one to set it as "selected." Once a node is selected, you can use the little buttons that appear by other nodes to Parent (set a must-research first dependency) and then create roads between nodes. You can also set Unhidden By (must research another node for it to become visible) dependencies. To apply changes made in the widget to the tree, select the tree asset again and press Write. In order to actually save changes, you must save the asset using the normal Unreal save dialog.

The visuals for node moving can sometimes get in the way of the position you want to drop the node - you might have to drop it somewhere further away, then drag it back to the actual intended location.

After creating a road connection, it will be a bit oddly offset; simply Write and Load again to view it in the correct place.

If you need to make significant changes to the layout, you can reset roads and connections, which will automatically write to the tree, so you can start connections again from scratch.

## Tree Node Generator

This tool allows you to automatically generate tree nodes (FGSchematics for use in Research Trees) from existing FGRecipes in an intelligent manner.

The tool will turn each selected FGRecipe into a node, setting its icon, name, description, and unlock costs based on the selected recipe.

It also allows you to update existing nodes if the recipes they unlock have changed.

SirDigby has also created a version that allows generating nodes from other FGSchematics, but those changes have not yet been brought into this repository - nag Robb and SirDigby if you want this.

Open the editor utility for more usage directions built into the widget.

### Extensibility

You can create your own version of this editor utility blueprint to specify a different parent class for generated nodes to use, and to implement per-node checking of if a certain field should be updated. Check out PowerSuit Modules (contact Robb#6731 on Discord) for an example of this in use.

## Tree Populator

This tool allows you to automatically add nodes to a new MAM tree, or update an existing MAM tree with nodes that it does not yet contain.

Open the editor utility for more usage directions built into the widget.

### Extensibility

You can create your own version of this editor utility blueprint to specify a different parent class for generated trees to use.
