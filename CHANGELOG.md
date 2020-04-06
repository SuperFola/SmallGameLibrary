# Changelog

## 0.0.2
### Added
- scenes can be put in a specified state using the `scm` argument in the `onUpdate` method of scenes, by doing a `scm[scene_id]->setState(State::Idle)
- adding cross platform shared library loader
- adding platform identifier

### Changed
- updating `include/Small/All.hpp` to include the shared library loader

### Removed

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