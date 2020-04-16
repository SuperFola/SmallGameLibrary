# Changelog

## 0.0.3
### Added
- added `Small/Core.hpp`, `Small/Graphics.hpp` and `Small/System.hpp` to include all the files from the specific folders
- the tilemap can be passed a new texture using `void Tilemap::use(sf::Texture*)`
- adding github actions to build the project after each commit/pull request
- added a `sgl::Graphics::TileView` to use tiles coordinates to place a view

### Changed
- the tilemap has been updated to no longer hold the texture, and be able to modify the vertex array when needed
- the platform and sharedlibrary files have been moved the `Small/System/`

### Removed

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