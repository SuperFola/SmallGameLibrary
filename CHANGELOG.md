# Changelog

## 0.0.3
### Added
- added `Small/Core.hpp`, `Small/Graphics.hpp` and `Small/System.hpp` to include all the files from the specific folders
- the tilemap can be passed a new texture using `void Tilemap::use(sf::Texture*)`
- adding github actions to build the project after each commit/pull request
- added a `sgl::Graphics::TileView` to use tiles coordinates to place a view
- added an example of how to use `sgl::Graphics::TileView`
- adding a sgl::Scenes::Zone to handle zone transitions on a map
- added `Small/System.hpp` and `Small/Scenes.hpp` to `Small/All.hpp`

### Changed
- the tilemap has been updated to no longer hold the texture, and be able to modify the vertex array when needed
- the platform and sharedlibrary files have been moved the `Small/System/`
- by default, the debug mode is now turned off when creating the application
- the texture pointer of a tilemap is now sent only using `.use` method
- disabling warning when converting float to int, int to float in the tilemap/tileview
- all the sizes in the tileview are now using `sf::Vector2i`
- all the sizes in the tilemap are now using `sf::Vector2i`
- using integer to store the size of a tile in the tile view

### Removed
- removed the argument `sgl::SceneManager&` from the scene, now using an internal pointer to the scene manager, in the scene itself

## 0.0.2
### Added
- scenes can be put in a specified state using the `scm` argument in the `onUpdate` method of scenes, by doing a `scm[scene_id]->setState(State::Idle)`
- adding cross platform shared library loader
- adding platform identifier
- adding [imgui_widget_flamegraph](https://github.com/bwrsandman/imgui-flame-graph) and its profiler
- adding a tilemap renderer
- adding a tilemap example

### Changed
- updating `include/Small/All.hpp` to include the shared library loader
- updating `include/Small/All.hpp` to include the tilemap renderer

## 0.0.1
### Added
- adding `include/Small/All.hpp`, including all the files needed to start a project
- adding `include/Small/Core/Application.hpp`, handling the application, window, and scenes
- adding `include/Small/Core/SceneManager.hpp`, handling the scenes
- adding `include/Small/Core/Scene.hpp`, with a class to inherit from to create your own scenes for the application
- adding [termcolor](https://github.com/ikalnytskyi/termcolor)
- adding IMGUI SFML
- adding an example in examples/Basic
- adding a Doxyfile